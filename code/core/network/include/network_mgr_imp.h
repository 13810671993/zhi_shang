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

private:
    // ��������
    UINT32          StartListen(IN UINT16 u16Port);

private:
    static CNetworkMgrImp*  m_pNetworkMgrImp;
    CAdpt*                  m_pAdpt;
    CNetConnectionMgr*      m_pNetConnectionMgr;

};

#endif
