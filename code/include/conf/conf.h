#ifndef __CONF_H_INC__
#define __CONF_H_INC__

#define SIZE_LINE		1024	//ÿ����󳤶�
#define SIZE_FILENAME	256		//�ļ�����󳤶�

#define min(x, y)		((x) <= (y)) ? (x) : (y)

typedef enum _ELineType_ 
{
    LINE_IDLE,		//δ������
	LINE_ERROR,		//������
	LINE_EMPTY,		//�հ��л�ע����
	LINE_SECTION,	//�ڶ�����
	LINE_VALUE		//ֵ������
} ELineType ;

class CConf
{
public:
    static CConf*   GetInstance(const CHAR* pcFileName);
    static VOID     DestroyInstance();

public:
	//��ȡ�ַ�������������
	INT32 GetString(IN const CHAR *section, IN const CHAR *key, OUT CHAR *value, IN INT32 size, IN const CHAR *defvalue) const;
	//��ȡ����ֵ
	INT32 GetInt(IN const CHAR *section, IN const CHAR *key, IN INT32 defvalue) const;
	//��ȡ������
	double GetDouble(IN const CHAR *section, IN const CHAR *key, IN double defvalue) const;
	//�����ַ�������valueΪNULL����ɾ����key�����У�����ע��
	INT32 SetString(IN const CHAR *section, IN const CHAR *key, IN const CHAR *value);
	//��������ֵ��baseȡֵ10��16��8���ֱ��ʾ10��16��8���ƣ�ȱʡΪ10����
	INT32 SetInt(IN const CHAR *section, IN const CHAR *key, IN INT32 value, IN INT32 base);

protected:
	CConf(const CHAR* pcFileName);
	~CConf();

private:
	//����ini�ļ����ڴ�
	INT32 FileLoad(const CHAR* pcFileName);
	//�ͷ�ini�ļ���ռ��Դ
	VOID FileFree();

	//ȥ������β�ո�ԭ������д
	CHAR* StrStrip(CHAR *s) const;
	//�����ִ�Сд�Ƚ��ַ���
	INT32 StriCmp(const CHAR *s1, const CHAR *s2) const;
	//ȡһ��
	INT32 GetLine(CHAR *buf, INT32 buflen, CHAR *content, CHAR **rem1, CHAR **rem2, CHAR **nextline) const;
	//ȡһ��section
	INT32 FindSection(const CHAR *section, CHAR **sect1, CHAR **sect2, CHAR **cont1, CHAR **cont2, CHAR **nextsect) const;
	//��һ��ȡ����ֵ
	VOID GetKeyValue(CHAR *content, CHAR **key, CHAR **value) const;
	//��ȡֵԭʼ��
	INT32 GetValue(const CHAR *section, const CHAR *key, CHAR *value, INT32 maxlen, const CHAR *defvalue) const;

private:
    static CConf*    m_pConf;

	CHAR	    m_acFileName[SIZE_FILENAME];
	CHAR*	    m_pcBuffer;
	INT32		m_iBufLen;
};

#endif
