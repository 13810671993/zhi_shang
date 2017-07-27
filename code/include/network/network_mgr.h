#ifndef __NETWORK_H__
#define __NETWORK_H__

class CAdpt;
class CNetSession;

class CNetworkMgr
{
public:
    static CNetworkMgr* GetInstance();
    static VOID         DestroyInstance();

public:
    virtual UINT32  RegistAdpt(IN CAdpt* pAdpt) = 0;
    virtual UINT32  StartListen(IN UINT16 u16Port) = 0;
    //virtual UINT32  Connected(IN boost::shared_ptr<CNetSession>& ptrSession, OUT UINT32 u32NodeID) = 0;
    virtual UINT32  Disconnected(IN UINT32 u32NodeID) = 0;
    virtual VOID    PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg) = 0;
    virtual UINT32  GetRemoteNodeInfo(IN UINT32 u32NodeID, OUT std::string& strIp, OUT UINT16& u16Port) = 0;

protected:
    CNetworkMgr();
    virtual ~CNetworkMgr();

};

#endif
