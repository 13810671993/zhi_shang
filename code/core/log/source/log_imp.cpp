#include "log_common.h"

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

CLogImp::CLogImp(E_SEVERITY_LEVEL eLogLevel)
{
    InitLogBase();
    SetLogLevel(eLogLevel);
}

CLogImp::~CLogImp()
{

}

boost::log::sources::severity_logger< E_SEVERITY_LEVEL > CLogImp::m_lg;

VOID CLogImp::PrintLog(E_SEVERITY_LEVEL eLogLevel, CHAR* pLogMessage)
{
    BOOST_LOG_SEV(m_lg, eLogLevel) << pLogMessage;
}

CLogImp* CLogImp::m_pLogImp = NULL;

CLogImp* CLogImp::GetInstance(E_SEVERITY_LEVEL eLogLevel)
{
    if (m_pLogImp == NULL)
        m_pLogImp = new CLogImp(eLogLevel);
    return m_pLogImp;
}

VOID CLogImp::DestroyInstance()
{
    if (m_pLogImp != NULL)
    {
        delete m_pLogImp;
        m_pLogImp = NULL;
    }
}

// 自定义sink
VOID CLogImp::InitLogBase()
{
	// 创建并init文件后端
	boost::shared_ptr<boost::log::sinks::text_file_backend> ptrBackend = boost::make_shared<boost::log::sinks::text_file_backend>(
		// 日志文件名
		boost::log::keywords::file_name = "../../../../log/server-%Y.%m.%d-%H.%M.%S.log",
		// 单个日志文件大小限制
		boost::log::keywords::rotation_size = 100 * 1024 * 1024,
		// 每隔指定时间重建新文件
		boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
		// 磁盘最小容量
		boost::log::keywords::min_free_space = 3 * 1024 * 1024
		);

#ifdef _DEBUG
    // 立即写日志
    ptrBackend->auto_flush(TRUE);
#endif
	// 使用文件后端来创建sink
	m_ptrSink = boost::make_shared<TypeSink>(ptrBackend);

	m_ptrSink->set_formatter(
        // 日志格式
		boost::log::expressions::format("[%1%] [%2%] | %3%| %4%")
        // 时间戳格式 debug下不打印data以上的时间
#ifdef _DEBUG
		% boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%H:%M:%S.%f")
#else
		% boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
#endif
        // 线程ID
		% boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type >("ThreadID")
        // 日志级别
		% boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity")
        // 要打印的log
		% boost::log::expressions::message
	);
	boost::log::core::get()->add_sink(m_ptrSink);
	boost::log::add_common_attributes();
}

VOID CLogImp::SetLogLevel(E_SEVERITY_LEVEL eLogLevel)
{
	// 通过sink设置日志过滤等级
	m_ptrSink->set_filter(boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity") >= eLogLevel);
}
