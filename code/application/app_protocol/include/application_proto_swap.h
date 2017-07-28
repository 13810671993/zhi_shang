#ifndef __APPLICATION_PROTO_SWAP_H__
#define __APPLICATION_PROTO_SWAP_H__
UINT32 StructToProto(const T_APP_LOGIN_REQ& tStruct, application::T_APP_LOGIN_REQ& proto);
UINT32 ProtoToStruct(const application::T_APP_LOGIN_REQ& proto, T_APP_LOGIN_REQ& tStruct);

UINT32 StructToProto(const T_APP_GET_ONLINE_USER_REQ& tStruct, application::T_APP_GET_ONLINE_USER_REQ& proto);
UINT32 ProtoToStruct(const application::T_APP_GET_ONLINE_USER_REQ& proto, T_APP_GET_ONLINE_USER_REQ& tStruct);

UINT32 StructToProto(const T_APP_REGIST_USER_RSP& tStruct, application::T_APP_REGIST_USER_RSP& proto);
UINT32 ProtoToStruct(const application::T_APP_REGIST_USER_RSP& proto, T_APP_REGIST_USER_RSP& tStruct);

UINT32 StructToProto(const T_APP_MODIFY_PASSWD_REQ& tStruct, application::T_APP_MODIFY_PASSWD_REQ& proto);
UINT32 ProtoToStruct(const application::T_APP_MODIFY_PASSWD_REQ& proto, T_APP_MODIFY_PASSWD_REQ& tStruct);

UINT32 StructToProto(const T_APP_SEND_MESSAGE_REQ& tStruct, application::T_APP_SEND_MESSAGE_REQ& proto);
UINT32 ProtoToStruct(const application::T_APP_SEND_MESSAGE_REQ& proto, T_APP_SEND_MESSAGE_REQ& tStruct);

UINT32 StructToProto(const T_APP_MODIFY_PASSWD_RSP& tStruct, application::T_APP_MODIFY_PASSWD_RSP& proto);
UINT32 ProtoToStruct(const application::T_APP_MODIFY_PASSWD_RSP& proto, T_APP_MODIFY_PASSWD_RSP& tStruct);

UINT32 StructToProto(const T_APP_LOGIN_RSP& tStruct, application::T_APP_LOGIN_RSP& proto);
UINT32 ProtoToStruct(const application::T_APP_LOGIN_RSP& proto, T_APP_LOGIN_RSP& tStruct);

UINT32 StructToProto(const T_APP_UPDATE_ONLINE_USER_NTF& tStruct, application::T_APP_UPDATE_ONLINE_USER_NTF& proto);
UINT32 ProtoToStruct(const application::T_APP_UPDATE_ONLINE_USER_NTF& proto, T_APP_UPDATE_ONLINE_USER_NTF& tStruct);

UINT32 StructToProto(const T_APP_TRANSMIT_MESSAGE_ACT& tStruct, application::T_APP_TRANSMIT_MESSAGE_ACT& proto);
UINT32 ProtoToStruct(const application::T_APP_TRANSMIT_MESSAGE_ACT& proto, T_APP_TRANSMIT_MESSAGE_ACT& tStruct);

UINT32 StructToProto(const T_APP_SEND_MESSAGE_RSP& tStruct, application::T_APP_SEND_MESSAGE_RSP& proto);
UINT32 ProtoToStruct(const application::T_APP_SEND_MESSAGE_RSP& proto, T_APP_SEND_MESSAGE_RSP& tStruct);

UINT32 StructToProto(const T_APP_REGIST_USER_REQ& tStruct, application::T_APP_REGIST_USER_REQ& proto);
UINT32 ProtoToStruct(const application::T_APP_REGIST_USER_REQ& proto, T_APP_REGIST_USER_REQ& tStruct);

UINT32 StructToProto(const T_APP_GET_ONLINE_USER_RSP& tStruct, application::T_APP_GET_ONLINE_USER_RSP& proto);
UINT32 ProtoToStruct(const application::T_APP_GET_ONLINE_USER_RSP& proto, T_APP_GET_ONLINE_USER_RSP& tStruct);

#endif