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

//����ini�ļ����ڴ�
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

//�ͷ�ini�ļ���ռ��Դ
void CConf :: FileFree()
{
	if (m_pcBuffer != NULL) {
		free(m_pcBuffer);
		m_pcBuffer = 0;
		m_iBufLen = 0;
	}
}

//��ȡ�ַ�������������
INT32 CConf :: GetString(IN const CHAR *section, IN const CHAR *key, OUT CHAR *value, IN INT32 maxlen, IN const CHAR *defvalue) const
{
	INT32 ret;
	INT32 len;

	ret = GetValue(section, key, value, maxlen, defvalue);
	if (!ret)
		return ret;

	//ȥ��β�ո�
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

//��ȡ����ֵ
INT32 CConf :: GetInt(IN const CHAR *section, IN const CHAR *key, IN INT32 defvalue) const
{
	CHAR valstr[64];

	if (GetValue(section, key, valstr, sizeof(valstr), NULL))
	    return (INT32)strtol(valstr, NULL, 0);
	return defvalue;
}

//��ȡ������
double CConf :: GetDouble(IN const CHAR *section, IN const CHAR *key, IN double defvalue) const
{
	CHAR valstr[64];

	if (GetValue(section, key, valstr, sizeof(valstr), NULL))
	    return (INT32)atof(valstr);
	return defvalue;
}

//�����ַ�������valueΪNULL����ɾ����key�����У�����ע��
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
		//δ�ҵ���

		//value��Ч�򷵻�
		if (value == NULL) 
			return 0;

		//���ļ�β�����
		file = fopen(m_acFileName, "ab");
		if (file == NULL) 
			return 0;
		fprintf(file, "\n[%s]\n%s = %s\n", section, key, value);
		fclose(file);
		FileLoad(m_acFileName);
		return 1;
	}

	//�ҵ��ڣ�����ڲ���key
	p = cont1;
	len = (INT32)(cont2 - cont1);
	while (len > 0) {
		type = GetLine(p, len, content, &rem1, &rem2, &nextline);

		if (LINE_VALUE == type) {
			GetKeyValue(content, &key0, &value0);
			if (StriCmp(key0, key) == 0) {
				//�ҵ�key
				file = fopen(m_acFileName, "wb");
				if (file == NULL) 
					return 0;
				len = (INT32)(p - m_pcBuffer);
				fwrite(m_pcBuffer, 1, len, file);					//д��key֮ǰ����
				if (value == NULL) {
					//value��Ч��ɾ��
					len = (INT32)(nextline - m_pcBuffer);			//������ͬע��һ��ɾ��
				} else {
					//value��Ч����д
					fprintf(file, "%s = %s", key, value);
					len = (INT32)(rem1 - m_pcBuffer);				//����β��ԭע��!
				}
				fwrite(m_pcBuffer + len, 1, m_iBufLen - len, file);	//д��key�����к�ע��֮�󲿷�
				fclose(file);
				FileLoad(m_acFileName);
				return 1;
			}	
		}

		len -= (INT32)(nextline - p);
		p = nextline;
	}

	//δ�ҵ�key

	//value��Ч�򷵻�
	if (value == NULL) 
		return 0;

	//���ļ�β�����
	file = fopen(m_acFileName, "wb");
	if (file == NULL) 
		return 0;
	len = (INT32)(cont2 - m_pcBuffer);
	fwrite(m_pcBuffer, 1, len, file);					//д��key֮ǰ����
	fprintf(file, "%s = %s\n", key, value);
	fwrite(m_pcBuffer + len, 1, m_iBufLen - len, file);	//д��key֮�󲿷�
	fclose(file);
	FileLoad(m_acFileName);
	return 1;
}

//��������ֵ��baseȡֵ10��16��8���ֱ��ʾ10��16��8���ƣ�ȱʡΪ10����
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

//ȥ������β�ո�ԭ������д
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

//�����ִ�Сд�Ƚ��ַ���
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

//ȡһ��
//���룺������(ָ�뼰����)
//����������͡���Ч���ݴ�(ȥ��β�ո�)��ע���ס�ע��β����һ����(��β����һ���׼�Ϊ���з�)
//      ��Ч����λ��Ϊ[buf, rem1)
INT32 CConf :: GetLine(CHAR *buf, INT32 buflen, CHAR *content, CHAR **rem1, CHAR **rem2, CHAR **nextline) const
{
	CHAR *cont1, *cont2;
	INT32 cntblank, cntCR, cntLF;		//�����ո񡢻��з�����
	CHAR isQuot1, isQuot2;			//����
	INT32 i;
	CHAR *p;

	//���ȶ��ж�ע�ͣ�֧�����»��з���\r��\n��\r\n��\n\r
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
		//2��CR��LF���н���
		if (cntCR == 2 || cntLF == 2) {
			--p;	//����1
			break;
		}
		//CR��LF��1��֮�������ַ����н���
		if (cntCR + cntLF >= 2) {
			break;
		}
		//CR��LF֮����������ַ����н���
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

	//����ͷβ���޿ո�
	memcpy(content, cont1, i);
	content[i] = 0;

	if (content[0] == '[' && content[i - 1] == ']')
		return LINE_SECTION;
	if (strchr(content, '=') != NULL)
		return LINE_VALUE;
	
	return LINE_ERROR;
}

//ȡһ��section
//���룺������
//������ɹ���񡢽������ס�������β���������ס�������β(������)����һ����(��β����һ���׼�Ϊ���л�ע����)
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
			if (found || section == NULL) break;		//������һsection
			content[strlen(content) - 1] = 0;			//ȥβ��]
			StrStrip(content + 1);						//ȥ��β�ո�
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

//��һ��ȡ����ֵ
//���룺���ݴ�(������д)
//�����������ֵ��
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




//��ȡֵԭʼ��
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
			if (found || section == NULL) break;		//������һsection
			content[strlen(content) - 1] = 0;			//ȥβ��]
			StrStrip(content + 1);						//ȥ��β�ո�
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
				if (len == 0) break;		//��ֵ��Ϊ��Ч
				if (value != NULL) {
					len = min(len, maxlen - 1);
					strncpy(value, value0, len);
					value[len] = 0;
				}
				return 1;
			}
		}
	}
	
	//δ���ּ�ֵȡȱʡ
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

