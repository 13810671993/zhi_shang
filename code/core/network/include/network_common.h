#ifndef __NETWORK_COMMON_H__
#define __NETWORK_COMMON_H__

#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/pool/pool.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <boost/date_time.hpp>

#include "common/data_type.h"
#include "common/common_error.h"
#include "common/common_tool.h"
#include "common/common_define.h"

#include "mem_pool/mem_pool.h"

// 服务器头文件
#include "network/network_mgr.h"
#include "network/net_node_id_layer.h"

#include "net_inner.h"
#include "net_session.h"
#include "net_connection_mgr.h"
#include "network_mgr_imp.h"

#include "adpt/adpt.h"
#include "msg_mgr/msg_mgr.h"
#include "subscriber/sub_msg_handler.h"


#include "log/log.h"

#endif
