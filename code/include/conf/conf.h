#ifndef __CONF_H_INC__
#define __CONF_H_INC__

#define SIZE_LINE		1024	//每行最大长度
#define SIZE_FILENAME	256		//文件名最大长度

#define min(x, y)		((x) <= (y)) ? (x) : (y)

typedef enum _ELineType_ 
{
    LINE_IDLE,		//未处理行
	LINE_ERROR,		//错误行
	LINE_EMPTY,		//空白行或注释行
	LINE_SECTION,	//节定义行
	LINE_VALUE		//值定义行
} ELineType ;

class CConf
{
public:
    static CConf*   GetInstance(const CHAR* pcFileName);
    static VOID     DestroyInstance();

public:
	//获取字符串，不带引号
	INT32 GetString(IN const CHAR *section, IN const CHAR *key, OUT CHAR *value, IN INT32 size, IN const CHAR *defvalue) const;
	//获取整数值
	INT32 GetInt(IN const CHAR *section, IN const CHAR *key, IN INT32 defvalue) const;
	//获取浮点数
	double GetDouble(IN const CHAR *section, IN const CHAR *key, IN double defvalue) const;
	//设置字符串：若value为NULL，则删除该key所在行，包括注释
	INT32 SetString(IN const CHAR *section, IN const CHAR *key, IN const CHAR *value);
	//设置整数值：base取值10、16、8，分别表示10、16、8进制，缺省为10进制
	INT32 SetInt(IN const CHAR *section, IN const CHAR *key, IN INT32 value, IN INT32 base);

protected:
	CConf(const CHAR* pcFileName);
	~CConf();

private:
	//加载ini文件至内存
	INT32 FileLoad(const CHAR* pcFileName);
	//释放ini文件所占资源
	VOID FileFree();

	//去除串首尾空格，原串被改写
	CHAR* StrStrip(CHAR *s) const;
	//不区分大小写比较字符串
	INT32 StriCmp(const CHAR *s1, const CHAR *s2) const;
	//取一行
	INT32 GetLine(CHAR *buf, INT32 buflen, CHAR *content, CHAR **rem1, CHAR **rem2, CHAR **nextline) const;
	//取一节section
	INT32 FindSection(const CHAR *section, CHAR **sect1, CHAR **sect2, CHAR **cont1, CHAR **cont2, CHAR **nextsect) const;
	//从一行取键、值
	VOID GetKeyValue(CHAR *content, CHAR **key, CHAR **value) const;
	//读取值原始串
	INT32 GetValue(const CHAR *section, const CHAR *key, CHAR *value, INT32 maxlen, const CHAR *defvalue) const;

private:
    static CConf*    m_pConf;

	CHAR	    m_acFileName[SIZE_FILENAME];
	CHAR*	    m_pcBuffer;
	INT32		m_iBufLen;
};

#endif
