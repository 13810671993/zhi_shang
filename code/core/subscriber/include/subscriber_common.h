#ifndef __SUBSCRIBER_COMMON_H__
#define __SUBSCRIBER_COMMON_H__

#ifndef SUB_MESSAGE_MAX_SIZE
#define SUB_MESSAGE_MAX_SIZE (1 * 1024)
#endif

#include <map>
#include <vector>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/pool/singleton_pool.hpp>

#include "common/data_type.h"
#include "common/common_error.h"

#include "mem_pool/mem_pool.h"
#include "common/common_define.h"

#include "subscriber/sub_msg_handler.h"
#include "subscriber/subscriber.h"
#include "sub_inner.h"
#include "subscriber_imp.h"
#include "subscribers_map.h"

#include "log/log.h"

#endif
