#include "app_protocol_common.h"

#define APP_STRUCT_TO_PROTO(name) \
case E_APP_MSG_##name: \
    {\
    u32Ret = Struct2ProtoString<T_APP_##name, application::T_APP_##name>(pStruct, u32StructLen, u32MsgType, strProtoBuf); \
    if (u32Ret != COMERR_OK) \
        { \
        return u32Ret; \
        } \
    } \
    break;

#define APP_PROTO_TO_STRUCT(name) \
case E_APP_MSG_##name: \
    { \
    u32Ret = ProtoString2Struct<application::T_APP_##name, T_APP_##name>(strProtoBuf, strStructBuf); \
    if (u32Ret != COMERR_OK) \
        { \
        return u32Ret; \
        } \
    } \
    break;



#define APP_REQ_AND_RSP_TO_PROTO(name) \
    APP_STRUCT_TO_PROTO(name##_REQ) \
    APP_STRUCT_TO_PROTO(name##_RSP)

#define APP_PROTO_TO_REQ_AND_RSP(name) \
    APP_PROTO_TO_STRUCT(name##_REQ) \
    APP_PROTO_TO_STRUCT(name##_RSP)

#define APP_NTF_TO_PROTO(name)\
    APP_STRUCT_TO_PROTO(name##_NTF) \

#define APP_PROTO_TO_NTF(name) \
    APP_PROTO_TO_STRUCT(name##_NTF) \

#define APP_CMD_TO_PROTO(name)\
    APP_STRUCT_TO_PROTO(name##_CMD) \

#define APP_PROTO_TO_CMD(name) \
    APP_PROTO_TO_STRUCT(name##_CMD) \




CAppProtocol::CAppProtocol()
{

}

CAppProtocol::~CAppProtocol()
{

}

UINT32 CAppProtocol::Struct2ProtoBuf(IN UINT32 u32MsgType, IN VOID* pStruct, IN UINT32 u32StructLen, OUT std::string& strProtoBuf)
{
    UINT32 u32Ret = COMERR_OK;

    switch (u32MsgType)
    {
        APP_REQ_AND_RSP_TO_PROTO(FIRST_TEST)
    }

    return u32Ret;
}

UINT32 CAppProtocol::ProtoBuf2Struct(IN VOID* pProtoBuf, IN UINT32 u32ProtoBufLen, OUT UINT32& u32MsgType, OUT std::string& strStructBuf)
{
    UINT32 u32Ret = COMERR_OK;

    memcpy(&u32MsgType, pProtoBuf, sizeof(u32MsgType));
    std::string strProtoBuf;
    strProtoBuf.assign((CHAR*)pProtoBuf + sizeof(u32MsgType), u32ProtoBufLen - sizeof(u32MsgType));

    switch (u32MsgType)
    {
        APP_PROTO_TO_REQ_AND_RSP(FIRST_TEST)
    }

    return u32Ret;
}

template<typename TStruct, typename CProto>
UINT32 CAppProtocol::Struct2ProtoString(IN VOID* pStruct, IN UINT32 u32ProtoBufLen, IN UINT32 u32MsgType, OUT std::string& strProtoBuf)
{
    if (sizeof(TStruct) != u32ProtoBufLen)
    {
        return COMERR_INVALID_PARAM;
    }

    TStruct* ptStruct = (TStruct*)pStruct;
    CProto cProto;
    StructToProto(*ptStruct, cProto);

    std::string strTemProtoBuf;
    strTemProtoBuf = cProto.SerializeAsString();

    strProtoBuf.append((CHAR*)&u32MsgType, sizeof(u32MsgType));
    strProtoBuf.append(strTemProtoBuf.c_str(), strTemProtoBuf.size());
    return COMERR_OK;
}

template<typename CProto, typename TStruct>
UINT32 CAppProtocol::ProtoString2Struct(IN const std::string& strProtoBuf, OUT std::string& strStructBuf)
{
    CProto cProto;
    if (cProto.ParseFromString(strProtoBuf) != TRUE)
    {
        return COMERR_INVALID_PARAM;
    }

    TStruct tStruct = { 0 };
    ProtoToStruct(cProto, tStruct);
    strStructBuf.assign((CHAR*)&tStruct, sizeof(TStruct));

    return COMERR_OK;
}

