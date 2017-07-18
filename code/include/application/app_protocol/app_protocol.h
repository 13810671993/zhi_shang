#ifndef __APP_PROTOCOL_H__
#define __APP_PROTOCOL_H__

class CAppProtocol
{
public:
    CAppProtocol();
    ~CAppProtocol();

    static UINT32 Struct2ProtoBuf(IN UINT32 u32MsgType, IN const VOID* pStruct, IN UINT32 u32StructLen, OUT std::string& strProtoBuf);
    static UINT32 ProtoBuf2Struct(IN const VOID* pProtoBuf, IN UINT32 u32ProtoBufLen, OUT UINT32& u32MsgType, OUT std::string& strStructBuf);

private:
    template<typename TStruct, typename CProto>
    static UINT32 Struct2ProtoString(IN const VOID* pStruct, IN UINT32 u32ProtoBufLen, IN UINT32 u32MsgType, OUT std::string& strProtoBuf);
    
    template<typename CProto, typename TStruct>
    static UINT32 ProtoString2Struct(IN const std::string& strProtoBuf, OUT std::string& strStructBuf);
};
#endif // !__APP_PROTOCOL_H__

