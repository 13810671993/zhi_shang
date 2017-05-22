#include "log.h"

//
boost::log::sources::severity_logger< E_SEVERITY_LEVEL > lg;

// 自定义打印日志级别
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& stream, E_SEVERITY_LEVEL level)
{
    static const char* const strLevel[] =
    {
        "TRACE  ",
        "DEBUG  ",
        "INFO   ",
        "WARNING",
        "ERROR  ",
        "FATAL  "
    };
    if (static_cast<std::size_t>(level) < (sizeof(strLevel) / sizeof(*strLevel)))
        stream << strLevel[level];
    else
        stream << static_cast<int>(level);
    return stream;
}

// 使用文件后端
typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> type_sink;

boost::shared_ptr<type_sink> ptrSink;

CLog::CLog(E_SEVERITY_LEVEL eLogLevel)
{
    InitLogBase();
    SetLogLevel(eLogLevel);
}

CLog::~CLog()
{
}

void CLog::PrintLog(E_SEVERITY_LEVEL eLogLevel, char* format, ...)
{
    va_list arg;
    va_start(arg, format);
    std::vector<char> cLogMessageVec(strlen(format) + 1, 0);
    snprintf(cLogMessageVec.data(), strlen(format) + 1, format, arg);
    va_end(arg);

    std::string strLog = cLogMessageVec.data();
    BOOST_LOG_SEV(lg, eLogLevel) << cLogMessageVec.data();
    BOOST_LOG_SEV(lg, eLogLevel) << strLog;
    BOOST_LOG_SEV(lg, DEBUG) << strLog;
}

void CLog::InitLogBase()
{
    // 创建并init文件后端
    boost::shared_ptr<boost::log::sinks::text_file_backend> ptrBackend = boost::make_shared<boost::log::sinks::text_file_backend>(
        // 日志文件名
        boost::log::keywords::file_name = "../log/server-%Y.%m.%d-%H.%M.%S.log",
        // 单个日志文件大小限制
        boost::log::keywords::rotation_size = 100 * 1024 * 1024,
        // 每隔指定时间重建新文件
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        // 磁盘最小容量
        boost::log::keywords::min_free_space = 3 * 1024 * 1024
        );

    // 使用文件后端来创建sink
    ptrSink = boost::make_shared<type_sink>(ptrBackend);

    ptrSink->set_formatter(
        // 日志格式
        boost::log::expressions::format("[%1%] [%2%] | %3%| %4%")
        // 时间戳格式
        % boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
        // 线程ID
        % boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type >("ThreadID")
        // 日志级别
        % boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity")
        // 要打印的log
        % boost::log::expressions::message
    );
    boost::log::core::get()->add_sink(ptrSink);
    boost::log::add_common_attributes();
}

void CLog::SetLogLevel(E_SEVERITY_LEVEL eLogLevel)
{
    // 通过sink设置日志过滤等级
    ptrSink->set_filter(boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity") >= eLogLevel);
}
