#ifndef __MSG_MGR_H__
#define __MSG_MGR_H__

class CAdpt;
class CLogic;
class CSubMsgHandler;

class CMsgMgr
{
public:
    static CMsgMgr* GetInstance();
    static VOID     DestroyInstance();
protected:
    CMsgMgr();
    ~CMsgMgr();

public:
    virtual UINT32  AddAdpt(IN CAdpt* pAdpt) = 0;
    virtual UINT32  StartLisen(IN UINT16 u16Port) = 0;
    virtual VOID    PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg) = 0;
    virtual UINT32  SubscribeMessage(IN UINT32 u32MsgType, IN CSubMsgHandler* pSubMsgHandler) = 0;
    virtual UINT32  SetConnectHandler(IN CLogic* pLogic) = 0;
    virtual UINT32  GetRemoteNodeInfo(IN UINT32 u32NodeID, OUT std::string& strIp, OUT UINT16& u16Port) = 0;

};

#endif
