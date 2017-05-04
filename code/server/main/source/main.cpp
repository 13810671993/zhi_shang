#include "main_common.h"

CMain::CMain()
{

}

CMain::~CMain()
{

}

CMain* CMain::m_pMain = NULL;

CMain* CMain::GetInstance()
{
    if (m_pMain == NULL)
        m_pMain = new CMain();
    return m_pMain;
}

VOID CMain::DestroyInstance()
{
    if (m_pMain != NULL)
    {
        delete m_pMain;
        m_pMain = NULL;
    }
}

UINT32 CMain::InitCommModule()
{
    UINT32  u32Ret = 0;
    do 
    {
        CConf* pConf = CConf::GetInstance("");
        CHECK_ERR_BREAK(pConf != NULL, COMERR_NULL_POINTER, "CConf::GetInstance failed. u32Ret = 0x%x\n", u32Ret);
    } while (0);

    return u32Ret;
}

UINT32 CMain::InitNetworkModule()
{
    UINT32  u32Ret = COMERR_OK;
    do 
    {
        CNetworkMgr* pNetworkMgr = CNetworkMgr::GetInstance();
        CHECK_ERR_BREAK(pNetworkMgr != NULL, COMERR_NULL_POINTER, "CNetworkMgr::GetInstance failed. u32Ret = 0x%x\n", u32Ret);
    } while (0);

    return u32Ret;
}

UINT32 CMain::InitMessageModule()
{
    UINT32  u32Ret = COMERR_OK;
    do 
    {
        CMsgMgr* pMsgMgr = CMsgMgr::GetInstance();
        CHECK_ERR_BREAK(pMsgMgr != NULL, COMERR_NULL_POINTER, "CMsgMgr::GetInstance failed. u32Ret = 0x%x\n", u32Ret);

        CAdpt* pAdpt = CSvrAdpt::GetInstance();
        CHECK_ERR_BREAK(pAdpt != NULL, COMERR_NULL_POINTER, "CSvrAdpt::GetInstance failed. u32Ret = 0x%x\n", u32Ret);

        pMsgMgr->AddAdpt(pAdpt);
        //u32Ret = pMsgMgr->StartLisen("127.0.0.1", 1993);
        //u32Ret = pMsgMgr->StartLisen("192.168.31.181", 1993);
        u32Ret = pMsgMgr->StartLisen(1993);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "StartListen failed. u32Ret = 0x%x\n", u32Ret);

    } while (0);

    return u32Ret;
}

UINT32 CMain::InitLogicModule()
{
	UINT32	u32Ret = 0;
	do 
	{
		CLogic* pLogic = CLogic::GetInstance();
		CHECK_ERR_BREAK(pLogic != NULL, COMERR_NULL_POINTER, "CLogic::GetInstance failed. u32Ret = 0x%x\n", u32Ret);
		pLogic->Run();
	} while (0);

	return u32Ret;
}

int main()
{
    CMain* pMain = CMain::GetInstance();

    pMain->InitCommModule();
    pMain->InitNetworkModule();
    pMain->InitMessageModule();
    pMain->InitLogicModule();
    getchar();
    CMain::DestroyInstance();
}
