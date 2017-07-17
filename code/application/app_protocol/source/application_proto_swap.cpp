#include "common/data_type.h"
#include "common/common_define.h"
#include "application/app_protocol/application_struct.h"
#include "application_struct.pb.h"
#include "application_proto_swap.h"
#include "application_proto_swap.h"

UINT32 StructToProto(const T_APP_LOGIN_REQ& tStruct, application::T_APP_LOGIN_REQ& proto)
{
	proto.set_u64context(tStruct.u64Context);
	proto.set_acusername(tStruct.acUserName, APP_MAX_NAME_LEN);
	proto.set_acpasswd(tStruct.acPasswd, APP_MAX_PASSWD_LEN);
	return TRUE;
}

UINT32 ProtoToStruct(const application::T_APP_LOGIN_REQ& proto, T_APP_LOGIN_REQ& tStruct)
{
	tStruct.u64Context = proto.u64context();
	memcpy(tStruct.acUserName, proto.acusername().c_str(), APP_MAX_NAME_LEN);
	memcpy(tStruct.acPasswd, proto.acpasswd().c_str(), APP_MAX_PASSWD_LEN);
	return TRUE;
}

UINT32 StructToProto(const T_APP_REGIST_USER_RSP& tStruct, application::T_APP_REGIST_USER_RSP& proto)
{
	proto.set_u64context(tStruct.u64Context);
	proto.set_u32result(tStruct.u32Result);
	return TRUE;
}

UINT32 ProtoToStruct(const application::T_APP_REGIST_USER_RSP& proto, T_APP_REGIST_USER_RSP& tStruct)
{
	tStruct.u64Context = proto.u64context();
	tStruct.u32Result = proto.u32result();
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

UINT32 StructToProto(const T_APP_MODIFY_PASSWD_REQ& tStruct, application::T_APP_MODIFY_PASSWD_REQ& proto)
{
	proto.set_u64context(tStruct.u64Context);
	proto.set_acusername(tStruct.acUserName, APP_MAX_NAME_LEN);
	proto.set_acoldpasswd(tStruct.acOldPasswd, APP_MAX_PASSWD_LEN);
	proto.set_acnewpasswd(tStruct.acNewPasswd, APP_MAX_PASSWD_LEN);
	return TRUE;
}

UINT32 ProtoToStruct(const application::T_APP_MODIFY_PASSWD_REQ& proto, T_APP_MODIFY_PASSWD_REQ& tStruct)
{
	tStruct.u64Context = proto.u64context();
	memcpy(tStruct.acUserName, proto.acusername().c_str(), APP_MAX_NAME_LEN);
	memcpy(tStruct.acOldPasswd, proto.acoldpasswd().c_str(), APP_MAX_PASSWD_LEN);
	memcpy(tStruct.acNewPasswd, proto.acnewpasswd().c_str(), APP_MAX_PASSWD_LEN);
	return TRUE;
}

UINT32 StructToProto(const T_APP_MODIFY_PASSWD_RSP& tStruct, application::T_APP_MODIFY_PASSWD_RSP& proto)
{
	proto.set_u64context(tStruct.u64Context);
	proto.set_u32result(tStruct.u32Result);
	return TRUE;
}

UINT32 ProtoToStruct(const application::T_APP_MODIFY_PASSWD_RSP& proto, T_APP_MODIFY_PASSWD_RSP& tStruct)
{
	tStruct.u64Context = proto.u64context();
	tStruct.u32Result = proto.u32result();
	return TRUE;
}

UINT32 StructToProto(const T_APP_LOGIN_RSP& tStruct, application::T_APP_LOGIN_RSP& proto)
{
	proto.set_u64context(tStruct.u64Context);
	proto.set_u32result(tStruct.u32Result);
	return TRUE;
}

UINT32 ProtoToStruct(const application::T_APP_LOGIN_RSP& proto, T_APP_LOGIN_RSP& tStruct)
{
	tStruct.u64Context = proto.u64context();
	tStruct.u32Result = proto.u32result();
	return TRUE;
}

UINT32 StructToProto(const T_APP_REGIST_USER_REQ& tStruct, application::T_APP_REGIST_USER_REQ& proto)
{
	proto.set_u64context(tStruct.u64Context);
	proto.set_acusername(tStruct.acUserName, APP_MAX_NAME_LEN);
	proto.set_acpasswd(tStruct.acPasswd, APP_MAX_PASSWD_LEN);
	proto.set_u32sex(tStruct.u32Sex);
	return TRUE;
}

UINT32 ProtoToStruct(const application::T_APP_REGIST_USER_REQ& proto, T_APP_REGIST_USER_REQ& tStruct)
{
	tStruct.u64Context = proto.u64context();
	memcpy(tStruct.acUserName, proto.acusername().c_str(), APP_MAX_NAME_LEN);
	memcpy(tStruct.acPasswd, proto.acpasswd().c_str(), APP_MAX_PASSWD_LEN);
	tStruct.u32Sex = proto.u32sex();
	return TRUE;
}

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

