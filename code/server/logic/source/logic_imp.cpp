#include "logic_common.h"

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

UINT32 CLogicImp::RecvMessageFromSub()
{
    UINT32  u32Ret = 0;

    return u32Ret;
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

    // 资源准备完毕 启动逻辑线程
    do 
    {
        boost::thread threadImp(boost::bind(DealMessageThread, (VOID*)this));
        //threadImp.join();
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

VOID* CLogicImp::DealMessageThread(VOID* pParam)
{
    VOID*   pMsg = NULL;

    while (1)
    {
        if (msgQueue.pop(pMsg))
        {
        }
        else
            BOOST_SLEEP(100);
    }
    return NULL;
}

UINT32 CLogicImp::RegistMessageCB()
{
    UINT32  u32Ret = 0;
    UINT32  au32MsgType[] = {
                                0,
                            };
    for (auto i = 0; i < sizeof(au32MsgType) / sizeof(UINT32); i++)
    {
        u32Ret = m_pMsgMgr->SubscribeMessage(au32MsgType[i], this);
        if (u32Ret != 0)
        {
            ;
        }
    }

    return u32Ret;
}

UINT32 CLogicImp::UnRegistMessageCB()
{
    UINT32  u32Ret = 0;

    return u32Ret;
}

