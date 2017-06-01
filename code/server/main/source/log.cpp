#include "log.h"

//
boost::log::sources::severity_logger< E_SEVERITY_LEVEL > lg;

// �Զ����ӡ��־����
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

// ʹ���ļ����
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
    // ������init�ļ����
    boost::shared_ptr<boost::log::sinks::text_file_backend> ptrBackend = boost::make_shared<boost::log::sinks::text_file_backend>(
        // ��־�ļ���
        boost::log::keywords::file_name = "../../log/server-%Y.%m.%d-%H.%M.%S.log",
        // ������־�ļ���С����
        boost::log::keywords::rotation_size = 100 * 1024 * 1024,
        // ÿ��ָ��ʱ���ؽ����ļ�
        boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
        // ������С����
        boost::log::keywords::min_free_space = 3 * 1024 * 1024
        );

    // ʹ���ļ����������sink
    ptrSink = boost::make_shared<type_sink>(ptrBackend);

    ptrSink->set_formatter(
        // ��־��ʽ
        boost::log::expressions::format("[%1%] [%2%] | %3%| %4%")
        // ʱ�����ʽ
        % boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
        // �߳�ID
        % boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type >("ThreadID")
        // ��־����
        % boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity")
        // Ҫ��ӡ��log
        % boost::log::expressions::message
    );
    boost::log::core::get()->add_sink(ptrSink);
    boost::log::add_common_attributes();
}

void CLog::SetLogLevel(E_SEVERITY_LEVEL eLogLevel)
{
    // ͨ��sink������־���˵ȼ�
    ptrSink->set_filter(boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity") >= eLogLevel);
}