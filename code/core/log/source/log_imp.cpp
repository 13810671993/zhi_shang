#include "log_common.h"

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

// �Զ���sink
VOID CLogImp::InitLogBase()
{
	// ������init�ļ����
	boost::shared_ptr<boost::log::sinks::text_file_backend> ptrBackend = boost::make_shared<boost::log::sinks::text_file_backend>(
		// ��־�ļ���
		boost::log::keywords::file_name = "../../../../log/server-%Y.%m.%d-%H.%M.%S.log",
		// ������־�ļ���С����
		boost::log::keywords::rotation_size = 100 * 1024 * 1024,
		// ÿ��ָ��ʱ���ؽ����ļ�
		boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
		// ������С����
		boost::log::keywords::min_free_space = 3 * 1024 * 1024
		);

#ifdef _DEBUG
    // ����д��־
    ptrBackend->auto_flush(TRUE);
#endif
	// ʹ���ļ����������sink
	m_ptrSink = boost::make_shared<TypeSink>(ptrBackend);

	m_ptrSink->set_formatter(
        // ��־��ʽ
		boost::log::expressions::format("[%1%] [%2%] | %3%| %4%")
        // ʱ�����ʽ debug�²���ӡdata���ϵ�ʱ��
#ifdef _DEBUG
		% boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%H:%M:%S.%f")
#else
		% boost::log::expressions::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
#endif
        // �߳�ID
		% boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type >("ThreadID")
        // ��־����
		% boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity")
        // Ҫ��ӡ��log
		% boost::log::expressions::message
	);
	boost::log::core::get()->add_sink(m_ptrSink);
	boost::log::add_common_attributes();
}

VOID CLogImp::SetLogLevel(E_SEVERITY_LEVEL eLogLevel)
{
	// ͨ��sink������־���˵ȼ�
	m_ptrSink->set_filter(boost::log::expressions::attr< E_SEVERITY_LEVEL >("Severity") >= eLogLevel);
}
