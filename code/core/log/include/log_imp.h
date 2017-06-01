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

	// 设置log基础环境
	VOID InitLogBase();
	// 设置log过滤级别 支持运行中动态修改
	VOID SetLogLevel(E_SEVERITY_LEVEL eLogLevel);

public:
    static CLogImp* m_pLogImp;

    // 使用文件后端
    typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> TypeSink;
private:
    //
    static boost::log::sources::severity_logger< E_SEVERITY_LEVEL > m_lg;
    boost::shared_ptr<TypeSink> m_ptrSink;

};


#endif // !__LOG_IMP_H__

