#ifndef __LOG_H__
#define __LOG_H__

// ��־����
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

// �����������־
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
	// ����log��������
	static void InitLogBase();
	// ����log���˼���
	static void SetLogLevel(E_SEVERITY_LEVEL logLevel);

};

#endif
