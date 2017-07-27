#ifndef __SESSION_MGR_COMMON_H__
#define __SESSION_MGR_COMMON_H__

#pragma warning(disable:4996)

#ifdef _WIN32_
#include <winsock.h>
#elif _LINUX_
#endif

#include <string>
#include <vector>
#include <map>

#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>

#include "common/data_type.h"
#include "common/common_error.h"
#include "common/common_define.h"

#include "log/log.h"

#include "session_mgr/session_mgr.h"
#include "session_mgr_imp.h"

#endif // !__SESSION_MGR_COMMON_H__

