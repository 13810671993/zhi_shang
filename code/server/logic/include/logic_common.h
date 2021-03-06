#ifndef __LOGIC_COMMON_H__
#define __LOGIC_COMMON_H__

#ifdef _WIN32_
#include <winsock.h>
#elif _LINUX_
#endif

#include <iostream>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/pool/singleton_pool.hpp>

#include "common/data_type.h"
#include "common/link_lib.h"
#include "common/common_error.h"
#include "common/common_tool.h"
#include "common/common_define.h"

#include "application/app_protocol/general_struct.h"
#include "application/app_protocol/application.h"
#include "application/app_protocol/application_struct.h"

#include "mem_pool/mem_pool.h"

#include "session_mgr/session_mgr.h"

#include "subscriber/sub_msg_handler.h"
#include "adpt/adpt.h"

#include "msg_mgr/msg_mgr.h"

#include "logic_inner.h"
#include "logic/logic.h"
#include "logic_imp.h"

#include "log/log.h"
#endif
