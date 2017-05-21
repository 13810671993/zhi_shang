#include "log_common.h"


// ��ӡ��־����
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

boost::shared_ptr<type_sink> pSink;

// �Զ���sink
void CLog::InitLogBase()
{
	// ������init�ļ����
	boost::shared_ptr<boost::log::sinks::text_file_backend> pBackend = boost::make_shared<boost::log::sinks::text_file_backend>(
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
	// ͨ��sink������־���˵ȼ�
	pSink->set_filter(boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity") >= logLevel);
}
