#ifndef __MSG_MGR_COMMON_H__
#define __MSG_MGR_COMMON_H__

#include <iostream>
#include <vector>
#include <map>

#include "common/data_type.h"
#include "common/link_lib.h"

#ifdef _WIN32

#elif _LINUX

#endif

#include "sub/sub_msg_handler.h"
#include "sub/subscribers_map.h"
#include "sub/subscriber.h"
#include "adpt/adpt.h"
#include "msg_transmit_imp.h"
#include "msg_mgr/msg_mgr.h"
#include "msg_mgr/msg_mgr_imp.h"

#endif
