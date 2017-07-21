#ifndef __GENERAL_PROTO_SWAP_H__
#define __GENERAL_PROTO_SWAP_H__
UINT32 StructToProto(const T_GNRL_ONLINE_USER& tStruct, general::T_GNRL_ONLINE_USER& proto);
UINT32 ProtoToStruct(const general::T_GNRL_ONLINE_USER& proto, T_GNRL_ONLINE_USER& tStruct);

#endif