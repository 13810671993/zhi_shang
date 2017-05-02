#ifndef __MAIN_COMMON_H__
#define __MAIN_COMMON_H__

//#include "ZeroMQ 4.0.4/zmq.h"
//#include "ZeroMQ 4.0.4/zmq_utils.h"

#include "common/link_lib.h"
#include "common/data_type.h"
#include "common/common_error.h"

//#include "boost/regex.hpp"

#include <stdio.h>

#include "main.h"
#include "adpt/adpt.h"
#include "adpt/svr_adpt.h"
#include "network/network_mgr.h"
#include "sub/sub_msg_handler.h"
#include "sub/subscriber.h"
#include "msg_mgr/msg_mgr.h"
#include "conf/conf.h"

#include "logic/logic.h"

#ifdef _WIN32
#ifdef _DEBUG
//#pragma comment(lib, LIB_THIRD_IMPORT("libevent-2.0.22-stable/libevent.lib"))
//#pragma comment(lib, LIB_THIRD_IMPORT("libevent-2.0.22-stable/libevent_core.lib"))
//#pragma comment(lib, LIB_THIRD_IMPORT("libevent-2.0.22-stable/libevent_extras.lib"))

#pragma comment(lib, LIB_DEBUG_IMPORT("sub_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("network_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("svr_adpt_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("msg_mgr_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("conf_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("logic_d.lib"))

//#pragma comment(lib, LIB_THIRD_IMPORT("ZeroMQ 4.0.4/libzmq-v100-mt-gd-4_0_4.lib"))

#else

#endif
#elif _LINUX
#endif

#define CHECK_ERR_BREAK(bRet, result, format, ...)\
    if( !(bRet) )\
{\
    printf(format, ##__VA_ARGS__);\
    u32Ret = result; \
    break; \
}\

#endif
