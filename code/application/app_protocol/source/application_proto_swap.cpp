#include "common/data_type.h"
#include "application/app_protocol/application_struct.h"
#include "application_struct.pb.h"
#include "application_proto_swap.h"
#include "application_proto_swap.h"

UINT32 StructToProto(const T_APP_FIRST_TEST_RSP& tStruct, application::T_APP_FIRST_TEST_RSP& proto)
{
	proto.set_u32result(tStruct.u32Result);
	proto.set_u32test(tStruct.u32Test);
	return TRUE;
}

UINT32 ProtoToStruct(const application::T_APP_FIRST_TEST_RSP& proto, T_APP_FIRST_TEST_RSP& tStruct)
{
	tStruct.u32Result = proto.u32result();
	tStruct.u32Test = proto.u32test();
	return TRUE;
}

UINT32 StructToProto(const T_APP_FIRST_TEST_REQ& tStruct, application::T_APP_FIRST_TEST_REQ& proto)
{
	proto.set_u32result(tStruct.u32Result);
	proto.set_u32test(tStruct.u32Test);
	return TRUE;
}

UINT32 ProtoToStruct(const application::T_APP_FIRST_TEST_REQ& proto, T_APP_FIRST_TEST_REQ& tStruct)
{
	tStruct.u32Result = proto.u32result();
	tStruct.u32Test = proto.u32test();
	return TRUE;
}

