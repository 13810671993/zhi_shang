#ifndef __NETWORK_H__
#define __NETWORK_H__

class CNetworkMgr
{
public:
    static CNetworkMgr* GetInstance();
    static VOID         DestroyInstance();

public:
    virtual UINT32  RegistAdpt(CAdpt* pAdpt) = 0;
    virtual UINT32  StartListen(IN UINT16 u16Port) = 0;
    virtual VOID    PostMessage(IN UINT32 u32NodeID, IN const std::string& strMsg) = 0;

protected:
    CNetworkMgr();
    virtual ~CNetworkMgr();

private:
    static CNetworkMgr* m_pNetworkMgr;
};

#endif
