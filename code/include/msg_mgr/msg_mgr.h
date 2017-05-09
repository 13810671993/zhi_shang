#ifndef __MSG_MGR_H__
#define __MSG_MGR_H__

class CMsgMgr
{
public:
    static CMsgMgr* GetInstance();
    static VOID     DestroyInstance();
protected:
    CMsgMgr();
    ~CMsgMgr();

public:
    virtual VOID    AddAdpt(IN CAdpt* pAdpt) = 0;
    virtual VOID    SetMsgTransmit2Adpt() = 0;
    virtual UINT32  StartLisen(IN UINT16 u16Port) = 0;
    virtual VOID    PostMessage(IN UINT32 u32NodeID, IN const std::string& strMsg) = 0;
    virtual UINT32  SubscribeMessage(UINT32 u32MsgType, CSubMsgHandler* pSubMsgHandler) = 0;

private:
    static CMsgMgr* m_pMsgMgr;
};

#endif
