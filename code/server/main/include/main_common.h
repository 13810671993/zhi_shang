#ifndef __MAIN_COMMON_H__
#define __MAIN_COMMON_H__

#include "common/link_lib.h"
#include "common/data_type.h"
#include "common/common_error.h"
#include "common/common_tool.h"

#include <stdio.h>
#include <string>

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

#pragma comment(lib, LIB_DEBUG_IMPORT("sub_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("network_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("svr_adpt_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("msg_mgr_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("conf_d.lib"))
#pragma comment(lib, LIB_DEBUG_IMPORT("logic_d.lib"))

#else

#endif
#elif _LINUX
#endif

#endif
