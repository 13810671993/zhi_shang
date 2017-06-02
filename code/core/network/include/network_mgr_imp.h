#ifndef __NETWORK_IMP_H__
#define __NETWORK_IMP_H__

class CNetworkMgrImp : public CNetworkMgr
{
public:
    static CNetworkMgrImp*  GetInstance();
    static VOID             DestroyInstance();

protected:
    CNetworkMgrImp();
    ~CNetworkMgrImp();

public:
    VOID            SendMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);
    UINT32          RegistAdpt(IN CAdpt* pAdpt);

private:
    // 面向连接
    UINT32          StartListen(IN UINT16 u16Port);
    static VOID     ListenThread(IN CNetworkMgrImp* pThis, IN UINT16 u16Port);
    static VOID     PushMessage2AdptThread(IN CNetworkMgrImp* pThis);
private:
    static CNetworkMgrImp*  m_pNetworkMgrImp;
    CNetConnectionMgr*      m_pNetConnectionMgr;
    CAdpt*                  m_pAdpt;

};

#endif
