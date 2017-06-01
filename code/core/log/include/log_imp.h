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

    // ʹ���ļ����
    typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> TypeSink;
private:
    //
    static boost::log::sources::severity_logger< E_SEVERITY_LEVEL > m_lg;
    boost::shared_ptr<TypeSink> m_ptrSink;

};


#endif // !__LOG_IMP_H__

