#ifndef __LOG_COMMON_H__
#define __LOG_COMMON_H__

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

// 生成打印日志
#include <boost/log/trivial.hpp>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

// 输出日志到文件
#include <boost/log/utility/setup/file.hpp>

// init log
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>

// 创建sink
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

#include <stdarg.h>
#include <string>
#include <vector>

#include "common/data_type.h"
#include "log/log.h"
#include "log_imp.h"

#endif
