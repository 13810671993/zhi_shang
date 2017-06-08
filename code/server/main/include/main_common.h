#ifndef __MAIN_COMMON_H__
#define __MAIN_COMMON_H__

#include "common/link_lib.h"
#include "common/data_type.h"
#include "common/common_error.h"
#include "common/common_tool.h"

#include <stdio.h>
#include <string>

#include "boost/thread.hpp"

#include "main.h"
#include "adpt/adpt.h"
#include "adpt/svr_adpt.h"
#include "network/network_mgr.h"
#include "subscriber/subscriber.h"
#include "msg_mgr/msg_mgr.h"
#include "conf/conf.h"
#include "logic/logic.h"

#include "log/log.h"

#ifdef _WIN32_
    #ifdef _DEBUG_
        #pragma comment(lib, LIB_DEBUG_IMPORT("subscriber_d.lib"))
        #pragma comment(lib, LIB_DEBUG_IMPORT("network_d.lib"))
        #pragma comment(lib, LIB_DEBUG_IMPORT("svr_adpt_d.lib"))
        #pragma comment(lib, LIB_DEBUG_IMPORT("msg_mgr_d.lib"))
        #pragma comment(lib, LIB_DEBUG_IMPORT("conf_d.lib"))
        #pragma comment(lib, LIB_DEBUG_IMPORT("logic_d.lib"))
        #pragma comment(lib, LIB_DEBUG_IMPORT("log_d.lib"))
        #pragma comment(lib, LIB_DEBUG_IMPORT("mem_pool_d.lib"))
    #else
        #pragma comment(lib, LIB_RELEASE_IMPORT("subscriber.lib"))
        #pragma comment(lib, LIB_RELEASE_IMPORT("network.lib"))
        #pragma comment(lib, LIB_RELEASE_IMPORT("svr_adpt.lib"))
        #pragma comment(lib, LIB_RELEASE_IMPORT("msg_mgr.lib"))
        #pragma comment(lib, LIB_RELEASE_IMPORT("conf.lib"))
        #pragma comment(lib, LIB_RELEASE_IMPORT("logic.lib"))
        #pragma comment(lib, LIB_RELEASE_IMPORT("log.lib"))

    #endif

#elif _LINUX_

#endif

#endif
