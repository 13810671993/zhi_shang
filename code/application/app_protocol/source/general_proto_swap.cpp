#include "common/data_type.h"
#include "common/common_define.h"
#include "application/app_protocol/general_struct.h"
#include "general_struct.pb.h"
#include "general_proto_swap.h"

UINT32 StructToProto(const T_GNRL_ONLINE_USER& tStruct, general::T_GNRL_ONLINE_USER& proto)
{
	proto.set_acusername(tStruct.acUserName, APP_MAX_NAME_LEN);
	return TRUE;
}

UINT32 ProtoToStruct(const general::T_GNRL_ONLINE_USER& proto, T_GNRL_ONLINE_USER& tStruct)
{
	memcpy(tStruct.acUserName, proto.acusername().c_str(), APP_MAX_NAME_LEN);
	return TRUE;
}

