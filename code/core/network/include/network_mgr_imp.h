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
    UINT32          RegistAdpt(CAdpt* pAdpt);
    VOID            PostMessage(IN UINT32 u32NodeID, IN const std::string& strMsg);

private:
    // 面向连接
    UINT32          StartListen(IN UINT16 u16Port);
    static VOID     ListenThread(CNetworkMgrImp* pThis, UINT16 u16Port);
    static VOID     PushMessage2AdptThread(CNetworkMgrImp* pThis);

private:
    static CNetworkMgrImp*  m_pNetworkMgrImp;
    CAdpt*                  m_pAdpt;
    CNetConnectionMgr*      m_pNetConnectionMgr;

};

#endif
