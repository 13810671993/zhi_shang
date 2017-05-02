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
    virtual VOID    SetMsgTransmitLayer2Adpt() = 0;
    virtual UINT32  StartLisen(IN const CHAR* pcIpAddr, IN UINT16 u16Port) = 0;
    virtual UINT32  PostMessage() = 0;
    virtual UINT32  SubscribeMessage(UINT32 u32MsgType, CSubMsgHandler* pSubMsgHandler) = 0;

private:
    static CMsgMgr* m_pMsgMgr;
};

#endif
