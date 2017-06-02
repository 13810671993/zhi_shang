#include "conf_common.h"

CConf :: CConf(const CHAR* pcFileName)
{
	FileLoad(pcFileName);
}

CConf :: ~CConf()
{
	FileFree();
}

CConf* CConf::m_pConf = NULL;

CConf* CConf::GetInstance(const CHAR* pcFileName)
{
    if (m_pConf == NULL)
        m_pConf = new CConf(pcFileName);
    return m_pConf;
}

VOID CConf::DestroyInstance()
{
    if (m_pConf != NULL)
    {
        delete m_pConf;
        m_pConf = NULL;
    }
}

//加载ini文件至内存
INT32 CConf :: FileLoad(const CHAR* pcFileName)
{
	FILE *file;
	INT32 len;

	FileFree();
	if (strlen(pcFileName) >= sizeof(m_acFileName))
		return 0;
	strcpy(m_acFileName, pcFileName);

	file = fopen(m_acFileName, "rb");
	if (file == NULL) 
		return 0;

	fseek(file, 0, SEEK_END);
	len = ftell(file);
	m_pcBuffer = (CHAR* )malloc(len);
	if (m_pcBuffer == NULL) {
		fclose(file);
		return 0;
	}

	fseek(file, 0, SEEK_SET);
	len = fread(m_pcBuffer, 1, len, file);
	fclose(file);
	m_iBufLen = len;
	return 1;
}

//释放ini文件所占资源
void CConf :: FileFree()
{
	if (m_pcBuffer != NULL) {
		free(m_pcBuffer);
		m_pcBuffer = 0;
		m_iBufLen = 0;
	}
}

//获取字符串，不带引号
INT32 CConf :: GetString(IN const CHAR *section, IN const CHAR *key, OUT CHAR *value, IN INT32 maxlen, IN const CHAR *defvalue) const
{
	INT32 ret;
	INT32 len;

	ret = GetValue(section, key, value, maxlen, defvalue);
	if (!ret)
		return ret;

	//去首尾空格
	len = strlen(value);
	if (value[0] == '\'' && value[len - 1] == '\'') {
		value[len - 1] = 0;
		memmove(value, value + 1, len - 1);
	} else
	if (value[0] == '\"' && value[len - 1] == '\"') {
		value[len - 1] = 0;
		memmove(value, value + 1, len - 1);
	}
	return ret;
}

//获取整数值
INT32 CConf :: GetInt(IN const CHAR *section, IN const CHAR *key, IN INT32 defvalue) const
{
	CHAR valstr[64];

	if (GetValue(section, key, valstr, sizeof(valstr), NULL))
	    return (INT32)strtol(valstr, NULL, 0);
	return defvalue;
}

//获取浮点数
double CConf :: GetDouble(IN const CHAR *section, IN const CHAR *key, IN double defvalue) const
{
	CHAR valstr[64];

	if (GetValue(section, key, valstr, sizeof(valstr), NULL))
	    return (INT32)atof(valstr);
	return defvalue;
}

//设置字符串：若value为NULL，则删除该key所在行，包括注释
INT32 CConf :: SetString(IN const CHAR *section, IN const CHAR *key, IN const CHAR *value)
{
	FILE *file;
	CHAR *sect1, *sect2, *cont1, *cont2, *nextsect;
	CHAR *p;
	INT32 len, type;
	CHAR content[SIZE_LINE];
	CHAR *key0, *value0;
	CHAR *rem1, *rem2, *nextline;


	if (m_pcBuffer == NULL) {
		return 0;
	}

	if (FindSection(section, &sect1, &sect2, &cont1, &cont2, &nextsect) == 0)
	{
		//未找到节

		//value无效则返回
		if (value == NULL) 
			return 0;

		//在文件尾部添加
		file = fopen(m_acFileName, "ab");
		if (file == NULL) 
			return 0;
		fprintf(file, "\n[%s]\n%s = %s\n", section, key, value);
		fclose(file);
		FileLoad(m_acFileName);
		return 1;
	}

	//找到节，则节内查找key
	p = cont1;
	len = (INT32)(cont2 - cont1);
	while (len > 0) {
		type = GetLine(p, len, content, &rem1, &rem2, &nextline);

		if (LINE_VALUE == type) {
			GetKeyValue(content, &key0, &value0);
			if (StriCmp(key0, key) == 0) {
				//找到key
				file = fopen(m_acFileName, "wb");
				if (file == NULL) 
					return 0;
				len = (INT32)(p - m_pcBuffer);
				fwrite(m_pcBuffer, 1, len, file);					//写入key之前部分
				if (value == NULL) {
					//value无效，删除
					len = (INT32)(nextline - m_pcBuffer);			//整行连同注释一并删除
				} else {
					//value有效，改写
					fprintf(file, "%s = %s", key, value);
					len = (INT32)(rem1 - m_pcBuffer);				//保留尾部原注释!
				}
				fwrite(m_pcBuffer + len, 1, m_iBufLen - len, file);	//写入key所在行含注释之后部分
				fclose(file);
				FileLoad(m_acFileName);
				return 1;
			}	
		}

		len -= (INT32)(nextline - p);
		p = nextline;
	}

	//未找到key

	//value无效则返回
	if (value == NULL) 
		return 0;

	//在文件尾部添加
	file = fopen(m_acFileName, "wb");
	if (file == NULL) 
		return 0;
	len = (INT32)(cont2 - m_pcBuffer);
	fwrite(m_pcBuffer, 1, len, file);					//写入key之前部分
	fprintf(file, "%s = %s\n", key, value);
	fwrite(m_pcBuffer + len, 1, m_iBufLen - len, file);	//写入key之后部分
	fclose(file);
	FileLoad(m_acFileName);
	return 1;
}

//设置整数值：base取值10、16、8，分别表示10、16、8进制，缺省为10进制
INT32 CConf :: SetInt(IN const CHAR *section, IN const CHAR *key, IN INT32 value, IN INT32 base)
{
	CHAR valstr[64];

	switch (base) {
	case 16:
		sprintf(valstr, "0x%x", value);
		return SetString(section, key, valstr);
	case 8:
		sprintf(valstr, "0%o", value);
		return SetString(section, key, valstr);
	default:	//10
		sprintf(valstr, "%d", value);
		return SetString(section, key, valstr);
	}
}

//去除串首尾空格，原串被改写
CHAR* CConf :: StrStrip(CHAR *s) const
{
	size_t size;
	CHAR *p1, *p2;

	size = strlen(s);
	if (!size)
		return s;

	p2 = s + size - 1;

	while ((p2 >= s) && isspace(*p2))
		--p2;
	*(p2 + 1) = '\0';

	p1 = s;
	while (*p1 && isspace(*p1))
		++p1;
	if (s != p1)
		memmove(s, p1, p2 - p1 + 2);
	return s;
}

//不区分大小写比较字符串
INT32 CConf :: StriCmp(const CHAR *s1, const CHAR *s2) const
{
	INT32 ch1, ch2;
	do
	{
		ch1 = (UINT8)*(s1++);
		if ((ch1 >= 'A') && (ch1 <= 'Z'))
			ch1 += 0x20;

		ch2 = (UINT8)*(s2++);
		if ((ch2 >= 'A') && (ch2 <= 'Z'))
			ch2 += 0x20;
	} while ( ch1 && (ch1 == ch2) );
	return(ch1 - ch2);
}

//取一行
//输入：数据区(指针及长度)
//输出：行类型、有效内容串(去首尾空格)、注释首、注释尾、下一行首(行尾与下一行首间为换行符)
//      有效内容位置为[buf, rem1)
INT32 CConf :: GetLine(CHAR *buf, INT32 buflen, CHAR *content, CHAR **rem1, CHAR **rem2, CHAR **nextline) const
{
	CHAR *cont1, *cont2;
	INT32 cntblank, cntCR, cntLF;		//连续空格、换行符数量
	CHAR isQuot1, isQuot2;			//引号
	INT32 i;
	CHAR *p;

	//首先断行断注释，支持如下换行符：\r、\n、\r\n、\n\r
	cntblank = 0;
	cntCR = cntLF = 0;
	isQuot1 = isQuot2 = 0;
	cont1 = *rem1 = 0;
	content[0] = 0;
	for (i = 0, p = buf; i < buflen; ++i, ++p)
	{
		if (*p == 0) {
			++p;
			break;
		}
		//2个CR或LF，行结束
		if (cntCR == 2 || cntLF == 2) {
			--p;	//回溯1
			break;
		}
		//CR或LF各1个之后任意字符，行结束
		if (cntCR + cntLF >= 2) {
			break;
		}
		//CR或LF之后出现其它字符，行结束
		if ((cntCR || cntLF) && *p != '\r' && *p != '\n')
			break;

		switch (*p) {
		case '\r':
			++cntCR;
			break;
		case '\n':
			++cntLF;
			break;
		case '\'':
			if (!isQuot2)
				isQuot1 = 1 - isQuot1;
			break;
		case '\"':
			if (!isQuot1)
				isQuot2 = 1 - isQuot2;
			break;
		case ';':
		case '#':
			if (isQuot1 || isQuot2)
				break;
			if (*rem1 == NULL)
				*rem1 = p - cntblank;
			break;
		default:
			if (isspace((UINT8)*p)) {
				++cntblank;
			} else {
				cntblank = 0;
				if ((*rem1 == NULL) && (cont1 == NULL))
					cont1 = p;
			}
			break;
		}
	}

	*nextline = p;
	*rem2 = p - cntCR - cntLF;
	if (*rem1 == NULL)
		*rem1 = *rem2;
	cont2 = *rem1 - cntblank;

	if (cont1 == NULL) {
		cont1 = cont2;
		return LINE_EMPTY;
	}

	i = (INT32)(cont2 - cont1);
	if (i >= SIZE_LINE)
		return LINE_ERROR;

	//内容头尾已无空格
	memcpy(content, cont1, i);
	content[i] = 0;

	if (content[0] == '[' && content[i - 1] == ']')
		return LINE_SECTION;
	if (strchr(content, '=') != NULL)
		return LINE_VALUE;
	
	return LINE_ERROR;
}

//取一节section
//输入：节名称
//输出：成功与否、节名称首、节名称尾、节内容首、节内容尾(含换行)、下一节首(节尾与下一节首间为空行或注释行)
INT32 CConf :: FindSection(const CHAR *section, CHAR **sect1, CHAR **sect2, CHAR **cont1, CHAR **cont2, CHAR **nextsect) const
{
	INT32 type;
	CHAR content[SIZE_LINE];
	CHAR *rem1, *rem2, *nextline;

	CHAR *p;
	CHAR *empty;
	INT32 uselen = 0;
	CHAR found = 0;

	if (m_pcBuffer == NULL) {
		return 0;
	}

	while (m_iBufLen - uselen > 0) {
		p = m_pcBuffer + uselen;
		type = GetLine(p, m_iBufLen - uselen, content, &rem1, &rem2, &nextline);
		uselen += (INT32)(nextline - p);

		if (LINE_SECTION == type) {
			if (found || section == NULL) break;		//发现另一section
			content[strlen(content) - 1] = 0;			//去尾部]
			StrStrip(content + 1);						//去首尾空格
			if (StriCmp(content + 1, section) == 0) {
				found = 1;
				*sect1 = p;
				*sect2 = rem1;
				*cont1 = nextline;
			}
			empty = nextline;
		} else
		if (LINE_VALUE == type) {
			if (!found && section == NULL) {
				found = 1;
				*sect1 = p;
				*sect2 = p;
				*cont1 = p;
			}
			empty = nextline;
		}
	}
	
	if (!found) return 0;

	*cont2 = empty;
	*nextsect = nextline;
	return 1;
}

//从一行取键、值
//输入：内容串(将被改写)
//输出：键串、值串
void CConf :: GetKeyValue(CHAR *content, CHAR **key, CHAR **value) const
{
	CHAR *p;

	p = strchr(content, '=');
	*p = 0;
	StrStrip(content);
	StrStrip(p + 1);
	*key = content;
	*value = p + 1;
}




//读取值原始串
INT32 CConf :: GetValue(const CHAR *section, const CHAR *key, CHAR *value, INT32 maxlen, const CHAR *defvalue) const
{
	INT32 type;
	CHAR content[SIZE_LINE];
	CHAR *rem1, *rem2, *nextline;
	CHAR *key0, *value0;

	CHAR *p;
	INT32 uselen = 0;
	CHAR found = 0;

	INT32 len;

	if (m_pcBuffer == NULL || key == NULL) {
		if (value != NULL)
			value[0] = 0;
		return 0;
	}

	while (m_iBufLen - uselen > 0) {
		p = m_pcBuffer + uselen;
		type = GetLine(p, m_iBufLen - uselen, content, &rem1, &rem2, &nextline);
		uselen += (INT32)(nextline - p);

		if (LINE_SECTION == type) {
			if (found || section == NULL) break;		//发现另一section
			content[strlen(content) - 1] = 0;			//去尾部]
			StrStrip(content + 1);						//去首尾空格
			if (StriCmp(content + 1, section) == 0) {
				found = 1;
			}
		} else
		if (LINE_VALUE == type) {
			if (!found && section == NULL) {
				found = 1;
			}
			if (!found)
				continue;
			GetKeyValue(content, &key0, &value0);
			if (StriCmp(key0, key) == 0) {
				len = strlen(value0);
				if (len == 0) break;		//空值视为无效
				if (value != NULL) {
					len = min(len, maxlen - 1);
					strncpy(value, value0, len);
					value[len] = 0;
				}
				return 1;
			}
		}
	}
	
	//未发现键值取缺省
	if (value != NULL) {
		if (defvalue != NULL) {
			len = min(strlen(defvalue), maxlen - 1);
			strncpy(value, defvalue, len);
			value[len] = 0;
		} else {
			value[0] = 0;
		}
	}
	return 0;
}

