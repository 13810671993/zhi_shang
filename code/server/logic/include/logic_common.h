#ifndef __LOGIC_COMMON_H__
#define __LOGIC_COMMON_H__

#include <iostream>

#include "boost/bind.hpp"
#include "boost/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/lockfree/queue.hpp"
//#include "boost/thread/thread_pool.hpp"

#include "common/data_type.h"
#include "common/link_lib.h"
#include "common/common_error.h"
#include "common/common_tool.h"

#include "subscriber/sub_msg_handler.h"
#include "adpt/adpt.h"

#include "msg_mgr/msg_mgr.h"

#include "logic_inner.h"
#include "logic/logic.h"
#include "logic_imp.h"

#include "log/log.h"
#endif
