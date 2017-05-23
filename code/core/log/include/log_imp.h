#ifndef __LOG_IMP_H__
#define __LOG_IMP_H__


class CLogImp : public CLog
{
public:
    static CLogImp* GetInstance(E_SEVERITY_LEVEL eLogLevel);
    static VOID     DestroyInstance();

protected:
    CLogImp(E_SEVERITY_LEVEL eLogLevel);
    ~CLogImp();

public:
    static VOID PrintLog(E_SEVERITY_LEVEL eLogLevel, CHAR* pLogMessage);

	// ����log��������
	VOID InitLogBase();
	// ����log���˼��� ֧�������ж�̬�޸�
	VOID SetLogLevel(E_SEVERITY_LEVEL eLogLevel);

public:
    static CLogImp* m_pLogImp;

};


#endif // !__LOG_IMP_H__

