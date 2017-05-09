#ifndef __MSG_MGR_COMMON_H__
#define __MSG_MGR_COMMON_H__

#include <iostream>
#include <string>

#include "common/data_type.h"
#include "common/link_lib.h"

#ifdef _WIN32

#elif _LINUX

#endif

#include "subscriber/sub_msg_handler.h"
#include "subscriber/subscriber.h"
#include "adpt/adpt.h"
#include "msg_transmit_imp.h"
#include "msg_mgr/msg_mgr.h"
#include "msg_mgr/msg_mgr_imp.h"

#endif
