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

/*******************************************************通    用***************************************************************/
public:
    typedef UINT32 (*PFUN_MESSAGE_CALLBACK)(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

    VOID            SendMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

private:
    static CNetworkMgrImp*  m_pNetworkMgrImp;
    CNetConnectionMgr*      m_pNetConnectionMgr;

/*******************************************************服务器用***************************************************************/
public:
    UINT32          RegistAdpt(CAdpt* pAdpt);

private:
    // 面向连接
    UINT32          StartListen(IN UINT16 u16Port);
    static VOID     ListenThread(CNetworkMgrImp* pThis, UINT16 u16Port);
    static VOID     PushMessage2AdptThread(CNetworkMgrImp* pThis);
private:
    CAdpt*                  m_pAdpt;
/*******************************************************服务器用***************************************************************/

};

#endif
