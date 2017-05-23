#include "logic_common.h"

boost::lockfree::queue<CLogicInnerMsg*, boost::lockfree::fixed_sized<FALSE>> g_LogicMsgQueue(0);

CLogicImp::CLogicImp() : m_pMsgMgr(NULL), m_bRun(FALSE)
{

}

CLogicImp::~CLogicImp()
{

}

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

UINT32 CLogicImp::RecvMessageFromSub(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN CHAR* pcMsg, IN UINT32 u32MsgLen)
{
    CLogicInnerMsg* pMsg = new CLogicInnerMsg(u32NodeID, u32MsgType, pcMsg, u32MsgLen);
    g_LogicMsgQueue.push(pMsg);
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
        for (UINT32 i = 0; i < 6; i++)
            threads.create_thread(boost::bind(&DealMessageThread, this, i));
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

VOID CLogicImp::DealMessageThread(CLogicImp* pThis, UINT32 u32ThreadNum)
{
    CLogicInnerMsg*   pMsg = NULL;

    while (1)
    {
        if (g_LogicMsgQueue.pop(pMsg) && pMsg != NULL)
        {
            std::cout << "u32ThreadNum: " << u32ThreadNum << " " << pMsg->GetMsgBuf() << std::endl;
            CMsgMgr::GetInstance()->PostMessage(pMsg->GetNodeID(), pMsg->GetMsgType(), pMsg->GetMsgLen(), pMsg->GetMsgBuf());
            delete pMsg;
            pMsg = NULL;
        }
        else
        {
            BOOST_SLEEP(100);
        }
    }
}

UINT32 CLogicImp::RegistMessageCB()
{
    UINT32  u32Ret = 0;
    UINT32  au32MsgType[] = {
                                0,
                                1111,
                            };
    for (auto i = 0; i < sizeof(au32MsgType) / sizeof(UINT32); i++)
    {
        do
        {
            u32Ret = m_pMsgMgr->SubscribeMessage(au32MsgType[i], this);
            CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "SubscribeMessage Failed. u32Ret = 0x%x\n", u32Ret);
        } while (0);
    }

    return u32Ret;
}

UINT32 CLogicImp::UnRegistMessageCB()
{
    UINT32  u32Ret = 0;

    return u32Ret;
}

