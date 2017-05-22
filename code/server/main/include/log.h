#ifndef __LOG_H__
#define __LOG_H__

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

// ���ɴ�ӡ��־
#include <boost/log/trivial.hpp>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

// �����־���ļ�
#include <boost/log/utility/setup/file.hpp>

// init log
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>

// ����sink
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

#include <stdarg.h>
#include <string>
#include <vector>


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

// �����������־
#ifndef LogTrace

#define LogTrace(format, ...)\
	CLog::PrintLog(TRACE, format, ##__VA_ARGS__);\

#endif // !LogTrace

#ifndef LogDebug

#define LogDebug(format, ...)\
	CLog::PrintLog(DEBUG, format, ##__VA_ARGS__);\

#endif

#ifndef LogInfo

#define LogInfo(format, ...)\
	CLog::PrintLog(INFO, format, ##__VA_ARGS__);\

#endif


#ifndef LogWarning

#define LogWarning(format, ...)\
	CLog::PrintLog(WARNING, format, ##__VA_ARGS__);\


#endif

#ifndef LogError

#define LogError(format, ...)\
	CLog::PrintLog(ERROR, format, ##__VA_ARGS__);\


#endif

#ifndef LogFatal

#define LogFatal(format, ...)\
	CLog::PrintLog(FATAL, format, ##__VA_ARGS__);\


#endif


class CLog
{
public:
    CLog(E_SEVERITY_LEVEL eLogLevel);
    ~CLog();

public:
    static void PrintLog(E_SEVERITY_LEVEL eLogLevel, char* format, ...);

    // ����log��������
    void InitLogBase();
    // ����log���˼��� ֧�������ж�̬�޸�
    void SetLogLevel(E_SEVERITY_LEVEL eLogLevel);


};

#endif // !__LOG_H__

