#ifndef __LOG_H__
#define __LOG_H__

#ifndef MAX_LOG_SIZE
#define MAX_LOG_SIZE 2048

#endif

// 日志级别
typedef enum 
{
    E_LOG_LEVEL_TRACE = 0,
    E_LOG_LEVEL_DEBUG,
    E_LOG_LEVEL_INFO,
    E_LOG_LEVEL_WARNING,
    E_LOG_LEVEL_ERROR,
    E_LOG_LEVEL_FATAL,
}E_SEVERITY_LEVEL;


// 按级别输出日志
#ifndef LogTrace

#define LogTrace(format, ...)\
	CLog::PrintLog(E_LOG_LEVEL_TRACE, format, ##__VA_ARGS__);\

#endif // !LogTrace

#ifndef LogDebug

#define LogDebug(format, ...)\
	CLog::PrintLog(E_LOG_LEVEL_DEBUG, format, ##__VA_ARGS__);\

#endif

#ifndef LogInfo

#define LogInfo(format, ...)\
	CLog::PrintLog(E_LOG_LEVEL_INFO, format, ##__VA_ARGS__);\

#endif


#ifndef LogWarning

#define LogWarning(format, ...)\
	CLog::PrintLog(E_LOG_LEVEL_WARNING, format, ##__VA_ARGS__);\


#endif

#ifndef LogError

#define LogError(format, ...)\
	CLog::PrintLog(E_LOG_LEVEL_ERROR, format, ##__VA_ARGS__);\


#endif

#ifndef LogFatal

#define LogFatal(format, ...)\
	CLog::PrintLog(E_LOG_LEVEL_FATAL, format, ##__VA_ARGS__);\


#endif

class CLog
{
public:
    static CLog*    GetInstance(E_SEVERITY_LEVEL eLogLevel = E_LOG_LEVEL_TRACE);
    VOID            DestroyInstance();
protected:
    CLog();
    ~CLog();

public:
    static VOID PrintLog(E_SEVERITY_LEVEL eLogLevel, CHAR* format, ...);

	// 设置log基础环境
	virtual VOID InitLogBase() = 0;
	// 设置log过滤级别 支持运行中动态修改
	virtual VOID SetLogLevel(E_SEVERITY_LEVEL logLevel) = 0;

};

#endif