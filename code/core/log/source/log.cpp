#include "log_common.h"


// 打印日志级别
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

boost::shared_ptr<type_sink> pSink;

// 自定义sink
void CLog::InitLogBase()
{
	// 创建并init文件后端
	boost::shared_ptr<boost::log::sinks::text_file_backend> pBackend = boost::make_shared<boost::log::sinks::text_file_backend>(
		// 日志文件名
		boost::log::keywords::file_name = "../../log/server-%Y.%m.%d-%H.%M.%S.log",
		// 单个日志文件大小限制
		boost::log::keywords::rotation_size = 100 * 1024 * 1024,
		// 每隔指定时间重建新文件
		boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
		// 磁盘最小容量
		boost::log::keywords::min_free_space = 3 * 1024 * 1024
		);

	// 使用文件后端来创建sink
	pSink = boost::make_shared<type_sink>(pBackend);

	pSink->set_formatter(
		boost::log::expressions::format("[%1%] [%2%] | %3%| %4%")
		% boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
		% boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type >("ThreadID")
		% boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity")
		% boost::log::expressions::message
	);
	boost::log::core::get()->add_sink(pSink);
	boost::log::add_common_attributes();
}

void CLog::SetLogLevel(E_SEVERITY_LEVEL logLevel)
{
	// 通过sink设置日志过滤等级
	pSink->set_filter(boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity") >= logLevel);
}
