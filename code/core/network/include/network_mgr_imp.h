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

/*******************************************************ͨ    ��***************************************************************/
public:
    typedef UINT32 (*PFUN_MESSAGE_CALLBACK)(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

    VOID            SendMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

private:
    static CNetworkMgrImp*  m_pNetworkMgrImp;
    CNetConnectionMgr*      m_pNetConnectionMgr;

/*******************************************************��������***************************************************************/
public:
    UINT32          RegistAdpt(CAdpt* pAdpt);

private:
    // ��������
    UINT32          StartListen(IN UINT16 u16Port);
    static VOID     ListenThread(CNetworkMgrImp* pThis, UINT16 u16Port);
    static VOID     PushMessage2AdptThread(CNetworkMgrImp* pThis);
private:
    CAdpt*                  m_pAdpt;
/*******************************************************��������***************************************************************/

};

#endif
