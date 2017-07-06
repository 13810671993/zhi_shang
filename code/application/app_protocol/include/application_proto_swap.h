#ifndef __APPLICATION_PROTO_SWAP_H__
#define __APPLICATION_PROTO_SWAP_H__
UINT32 StructToProto(const T_APP_FIRST_TEST_RSP& tStruct, application::T_APP_FIRST_TEST_RSP& proto);
UINT32 ProtoToStruct(const application::T_APP_FIRST_TEST_RSP& proto, T_APP_FIRST_TEST_RSP& tStruct);

UINT32 StructToProto(const T_APP_FIRST_TEST_REQ& tStruct, application::T_APP_FIRST_TEST_REQ& proto);
UINT32 ProtoToStruct(const application::T_APP_FIRST_TEST_REQ& proto, T_APP_FIRST_TEST_REQ& tStruct);

#endif