#include "logic_common.h"

boost::lockfree::queue<CLogicInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_LogicMsgQueue(0);

#ifdef _MEM_POOL_
CLogicImp::CLogicImp() : m_pMsgMgr(NULL), m_bRun(FALSE), m_tMemPool(MEM_POOL_INITIALIZER)
{
    MemPoolInit_API();
    m_tMemPool = MemPoolCreate_API(NULL, NET_MESSAGE_BODY_MAX_SIZE);
}

CLogicImp::~CLogicImp()
{
    // 确保内存池销毁前 所有内存都归还给内存池
    BOOST_SLEEP(1 * 1000);
    MemPoolDestroy_API(&m_tMemPool);
    MemPoolFinalize_API();
}
#else
CLogicImp::CLogicImp() : m_pMsgMgr(NULL), m_bRun(FALSE)
{

}

CLogicImp::~CLogicImp()
{

}
#endif

CLogicImp* CLogicImp::m_pLogicImp = NULL;

CLogicImp* CLogicImp::GetInstance()
{
    if (m_pLogicImp == NULL)
        m_pLogicImp = new CLogicImp();
    return m_pLogicImp;
}

VOID CLogicImp::DestroyInstance()
{
    if (m_pLogicImp != NULL)
    {
        delete m_pLogicImp;
        m_pLogicImp = NULL;
    }
}

UINT32 CLogicImp::RecvMessageFromSub(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
#ifdef _MEM_POOL_
    CLogicInnerMsg* pMsg = new CLogicInnerMsg(u32NodeID, u32MsgType, u32MsgLen, pcMsg, &m_tMemPool);
#else
    CLogicInnerMsg* pMsg = new CLogicInnerMsg(u32NodeID, u32MsgType, u32MsgLen, pcMsg);
#endif
    if (!g_LogicMsgQueue.push(pMsg))
    {
        delete pMsg;
    }
    return COMERR_OK;
}

UINT32 CLogicImp::Run()
{
    UINT32  u32Ret = 0;
    BOOL    bMsgMgr = FALSE, bRegist = FALSE;

    if (m_bRun)
    {
        // 已经启动
        return 1;
    }

    do 
    {
        m_pMsgMgr = CMsgMgr::GetInstance();
        if (m_pMsgMgr == NULL)      break;
        bMsgMgr = TRUE;
        u32Ret = 1;

        u32Ret = RegistMessageCB();
        if (u32Ret != 0)            break;
        bRegist = TRUE;
    } while (0);

    if (u32Ret != 0)
    {
        if (bMsgMgr)    m_pMsgMgr = NULL;
        if (bRegist)    UnRegistMessageCB();

        return u32Ret;
    }

    // 资源准备完毕 启动逻辑线程(池)
    do 
    {
        boost::thread_group threads;
        for (UINT32 i = 0; i < 6; ++i)
        {
            threads.create_thread(boost::bind(&DealMessageThread, this, i));
            LogInfo("DealMessageThread start. ThreadNum = %d", i);
        }
    } while (0);

    return u32Ret;

}

UINT32 CLogicImp::Stop()
{
    UINT32  u32Ret = 0;

    if (m_bRun)
    {
        m_bRun = FALSE;
        m_pMsgMgr = NULL;
    }

    return u32Ret;

}

VOID CLogicImp::DealMessageThread(IN CLogicImp* pThis, IN UINT32 u32ThreadNum)
{
    CLogicInnerMsg*   pMsg = NULL;

    while (1)
    {
        if (g_LogicMsgQueue.pop(pMsg) && pMsg != NULL)
        {
#ifdef _DEBUG_
            T_APP_FIRST_TEST_REQ* ptReq = (T_APP_FIRST_TEST_REQ*)(pMsg->GetMsgBuf());

            //std::cout << "u32ThreadNum: " << u32ThreadNum << " " << pMsg->GetMsgType() << " " << ptReq->u32Result << " " << ptReq->u32Test << std::endl;
#endif
            if (pMsg->GetMsgBuf() != NULL)
            {
                //CMsgMgr::GetInstance()->PostMessage(pMsg->GetNodeID(), pMsg->GetMsgType(), pMsg->GetMsgLen(), pMsg->GetMsgBuf());
                pThis->OnDealMessage(pMsg->GetNodeID(), pMsg->GetMsgType(), pMsg->GetMsgLen(), pMsg->GetMsgBuf());
            }
            delete pMsg;
            pMsg = NULL;
        }
        else
        {
            BOOST_SLEEP(1);
        }
    }
}

UINT32 CLogicImp::RegistMessageCB()
{
    UINT32  u32Ret = 0;
    UINT32  au32MsgType[] = {
                                E_APP_MSG_LOGIN_REQ,
                                E_APP_MSG_REGIST_USER_REQ,
                                E_APP_MSG_MODIFY_PASSWD_REQ,
                            };
    for (auto i = 0; i < sizeof(au32MsgType) / sizeof(UINT32); ++i)
    {
        do
        {
            u32Ret = m_pMsgMgr->SubscribeMessage(au32MsgType[i], this);
            CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "SubscribeMessage Failed. u32Ret = 0x%x", u32Ret);

        } while (0);
    }

    return u32Ret;
}

UINT32 CLogicImp::UnRegistMessageCB()
{
    UINT32  u32Ret = 0;

    return u32Ret;
}

UINT32 CLogicImp::OnDealMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
    UINT32 u32Ret = 0;
    switch (u32MsgType)
    {
    case E_APP_MSG_LOGIN_REQ:
        OnLoginReq(u32NodeID, u32MsgLen, pcMsg);
        break;
    case E_APP_MSG_REGIST_USER_REQ:
        OnRegistUserReq(u32NodeID, u32MsgLen, pcMsg);
        break;
    case E_APP_MSG_MODIFY_PASSWD_REQ:
        OnModifyPasswdReq(u32NodeID, u32MsgLen, pcMsg);
        break;

    default:
        break;
    }

    return u32Ret;
}

UINT32 CLogicImp::OnLoginReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
    T_APP_LOGIN_REQ*    ptReq = (T_APP_LOGIN_REQ*)pcMsg;
    T_APP_LOGIN_RSP     tResp = { 0 };
    UINT32  u32Ret = 0;

    LogInfo("OnLoginReq user : %s  passwd: %s", ptReq->acUserName, ptReq->acPasswd);

    tResp.u32Result = 0;
    tResp.u64Context = ptReq->u64Context;
    m_pMsgMgr->PostMessage(u32NodeID, E_APP_MSG_LOGIN_RSP, sizeof(tResp), (CHAR*)&tResp);

    return u32Ret;
}

UINT32 CLogicImp::OnRegistUserReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
    T_APP_REGIST_USER_REQ*  ptReq = (T_APP_REGIST_USER_REQ*)pcMsg;
    T_APP_REGIST_USER_RSP   tResp = { 0 };
    UINT32 u32Ret = 0;

    LogInfo("OnRegistUserReq user: %s  passwd: %s", ptReq->acUserName, ptReq->acPasswd);

    tResp.u32Result = 0;
    tResp.u64Context = ptReq->u64Context;
    m_pMsgMgr->PostMessage(u32NodeID, E_APP_MSG_REGIST_USER_RSP, sizeof(tResp), (CHAR*)&tResp);

    return u32Ret;
}

UINT32 CLogicImp::OnModifyPasswdReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
    T_APP_MODIFY_PASSWD_REQ*    ptReq = (T_APP_MODIFY_PASSWD_REQ*)pcMsg;
    T_APP_MODIFY_PASSWD_RSP     tResp = { 0 };
    UINT32  u32Ret = 0;

    LogInfo("OnModifyPasswdReq user: %s  old passwd: %s  new passwd: %s", ptReq->acUserName, ptReq->acOldPasswd, ptReq->acNewPasswd);

    tResp.u32Result = 0;
    tResp.u64Context = ptReq->u64Context;
    m_pMsgMgr->PostMessage(u32NodeID, E_APP_MSG_MODIFY_PASSWD_RSP, sizeof(tResp), (CHAR*)&tResp);

    return u32Ret;
}

