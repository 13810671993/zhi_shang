#ifndef __NETWORK_H__
#define __NETWORK_H__

class CNetworkMgr
{
public:
    static CNetworkMgr* GetInstance();
    static VOID         DestroyInstance();

public:
    virtual UINT32  StartListen(IN const CHAR* pcIpAddr, IN UINT32 u32Port) = 0;

protected:
    CNetworkMgr();
    virtual ~CNetworkMgr();

private:
    static CNetworkMgr* m_pNetworkMgr;
};

#endif
