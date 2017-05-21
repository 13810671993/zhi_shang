#ifndef __LOG_H__
#define __LOG_H__

// 日志级别
enum E_SEVERITY_LEVEL
{
	TRACE = 0,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	FATAL
};

//
static boost::log::sources::severity_logger< E_SEVERITY_LEVEL > lg;

// 按级别输出日志
#ifndef LogTrace
#define LogTrace	BOOST_LOG_SEV(lg, TRACE)
#endif

#ifndef LogDebug
#define LogDebug	BOOST_LOG_SEV(lg, DEBUG)
#endif

#ifndef LogInfo
#define LogInfo		BOOST_LOG_SEV(lg, INFO)
#endif

#ifndef LogWarning
#define LogWarning	BOOST_LOG_SEV(lg, WARNING)
#endif

#ifndef LogError
#define LogError	BOOST_LOG_SEV(lg, ERROR)
#endif

#ifndef LogFatal
#define LogFatal	BOOST_LOG_SEV(lg, FATAL)
#endif

class CLog
{
public:
	CLog() {}
	~CLog() {}

public:
	// 设置log基础环境
	static void InitLogBase();
	// 设置log过滤级别
	static void SetLogLevel(E_SEVERITY_LEVEL logLevel);

};

#endif
