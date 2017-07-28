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
CLogicImp::CLogicImp() : m_pSessionMgr(NULL), m_pMsgMgr(NULL), m_bRun(FALSE)
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
    BOOL    bSessionMgr = FALSE, bMsgMgr = FALSE, bRegist = FALSE;

    if (m_bRun)
    {
        // 已经启动
        return 1;
    }

    do 
    {
        m_pSessionMgr = CSessionMgr::GetInstance();
        CHECK_ERR_BREAK(m_pSessionMgr != NULL, u32Ret, "CSessionMgr::GetInstance Failed. u32Ret = 0x%x", u32Ret);
        bSessionMgr = TRUE;
        m_pMsgMgr = CMsgMgr::GetInstance();
        CHECK_ERR_BREAK(m_pMsgMgr != NULL, u32Ret, "CMsgMgr::GetInstance Failed. u32Ret = 0x%x", u32Ret);
        bMsgMgr = TRUE;
        u32Ret = RegistMessageCB();
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "CMsgMgr::GetInstance Failed. u32Ret = 0x%x", u32Ret);
        bRegist = TRUE;
        m_pMsgMgr->SetConnectHandler(this);

    } while (0);

    if (u32Ret != 0)
    {
        if (bSessionMgr)    m_pSessionMgr = NULL;
        if (bMsgMgr)        m_pMsgMgr = NULL;
        if (bRegist)        UnRegistMessageCB();

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

UINT32 CLogicImp::Connected(IN UINT32 u32NodeID, IN const std::string& strIp, IN UINT16 u16Port)
{
    return COMERR_OK;
}

UINT32 CLogicImp::Disconnected(IN UINT32 u32NodeID)
{
    // 断开连接 会话终止 删除会话
    UINT32 u32Ret = 0;
    do
    {
        // 删除会话
        u32Ret = m_pSessionMgr->SessionDel(u32NodeID);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "DelSession Failed. u32Ret = 0x%x, u32NodeID = %d", u32Ret, u32NodeID);

        // 通知所有的客户端 最新会话列表
        std::vector<T_SESSION>  tSessionVec;
        u32Ret = m_pSessionMgr->SessionGet(tSessionVec);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "SessionGet Failed. u32Ret = 0x%x", u32Ret);
        T_APP_UPDATE_ONLINE_USER_NTF    tNtfy = { 0 };
        tNtfy.u32UserNum = tSessionVec.size();
        UINT32 i = 0;
        for (auto it = tSessionVec.begin(); it != tSessionVec.end(); ++it, ++i)
        {
            memcpy(tNtfy.atOnlineUser[i].acUserName, it->tSessionUOID.acObjID, sizeof(tNtfy.atOnlineUser[i].acUserName));
        }
        // 通知所有客户端在线用户
        u32Ret = NotifyClient(E_APP_MSG_UPDATE_ONLINE_USER_NTF, (CHAR*)&tNtfy, sizeof(tNtfy));
    } while (0);

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
                                E_APP_MSG_GET_ONLINE_USER_REQ,
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

UINT32 CLogicImp::NotifyClient(IN UINT32 u32MsgType, IN const CHAR* pcMsg, IN UINT32 u32MsgLen)
{
    UINT32  u32Ret = 0;
    std::vector<T_SESSION>  tSessionVec;
    do 
    {
        // 1. 获取所有session
        m_pSessionMgr->SessionGet(tSessionVec);
        // 2. 给所有用户发送通知
        for (auto it = tSessionVec.begin(); it != tSessionVec.end(); ++it)
        {
            m_pMsgMgr->PostMessage(it->u32NodeID, E_APP_MSG_UPDATE_ONLINE_USER_NTF, u32MsgLen, pcMsg);
        }
    } while (0);

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
    case E_APP_MSG_GET_ONLINE_USER_REQ:
        OnGetOnlineUserReq(u32NodeID, u32MsgLen, pcMsg);
        break;
    case E_APP_MSG_SEND_MESSAGE_REQ:
        OnSendMessageReq(u32NodeID, u32MsgLen, pcMsg);
        break;

    default:
        break;
    }

    return u32Ret;
}

UINT32 CLogicImp::OnLoginReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
    T_APP_LOGIN_REQ*                ptReq = (T_APP_LOGIN_REQ*)pcMsg;
    T_APP_LOGIN_RSP                 tResp = { 0 };
    T_APP_UPDATE_ONLINE_USER_NTF    tNtfy = { 0 };
    UINT32  u32Ret = 0;

    LogInfo("OnLoginReq user : %s  passwd: %s", ptReq->acUserName, ptReq->acPasswd);

    do 
    {
        // 1. 获取远端ip port
        std::string strIp;
        UINT16      u16Port;
        u32Ret = m_pMsgMgr->GetRemoteNodeInfo(u32NodeID, strIp, u16Port);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "GetRemoteNodeInfo Failed. u32Ret = 0x%x, u32NodeID = %d", u32Ret, u32NodeID);

        // 2. 添加到session中
        T_SESSION tSession = { 0 };
        tSession.u32NodeID = u32NodeID;
        tSession.tNetAddr.tIP = inet_addr(strIp.c_str());
        tSession.tNetAddr.u16Port = u16Port;
        tSession.tSessionUOID.u32NodeID = u32NodeID;
        memcpy(tSession.tSessionUOID.acObjID, ptReq->acUserName, sizeof(ptReq->acUserName));
        u32Ret = m_pSessionMgr->SessionAdd(tSession);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "AddSession Failed. u32Ret = 0x%x", u32Ret);

        // 3. 构造tNtfy 获取所有session
        std::vector<T_SESSION>  tSessionVec;
        u32Ret = m_pSessionMgr->SessionGet(tSessionVec);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "SessionGet Failed. u32Ret = 0x%x", u32Ret);
        UINT32 i = 0;
        tNtfy.u32UserNum = tSessionVec.size();
        for (auto it = tSessionVec.begin(); it != tSessionVec.end(); ++it, ++i)
        {
            memcpy(tNtfy.atOnlineUser[i].acUserName, it->tSessionUOID.acObjID, sizeof(tNtfy.atOnlineUser[i].acUserName));
        }
    } while (0);
    tResp.u32Result = 0;
    tResp.u64Context = ptReq->u64Context;
    memcpy(tResp.acUserName, ptReq->acUserName, sizeof(tResp.acUserName));
    m_pMsgMgr->PostMessage(u32NodeID, E_APP_MSG_LOGIN_RSP, sizeof(tResp), (CHAR*)&tResp);
    //BOOST_SLEEP(500);

    if (u32Ret == 0)
    {
        // 通知所有客户端在线用户
        u32Ret = NotifyClient(E_APP_MSG_UPDATE_ONLINE_USER_NTF, (CHAR*)&tNtfy, sizeof(tNtfy));
    }

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

UINT32 CLogicImp::OnGetOnlineUserReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
    T_APP_GET_ONLINE_USER_REQ*  ptReq = (T_APP_GET_ONLINE_USER_REQ*)pcMsg;
    T_APP_GET_ONLINE_USER_RSP   tResp = { 0 };
    UINT32  u32Ret = 0;

    LogInfo("OnGetOnlineUserReq");

#if 0
    tResp.u32Result = 0;
    tResp.u64Context = ptReq->u64Context;
    tResp.u32UserNum = 15;
    CHAR a = 'a';
    for (auto i = 0; i < 15; ++i, ++a)
    {
        memcpy(tResp.atOnlineUser[i].acUserName, &a, sizeof(a));
    }
#else
    // 1. 获取所有session
    std::vector<T_SESSION> tSessionVec;
    m_pSessionMgr->SessionGet(tSessionVec);

    tResp.u32Result = 0;
    tResp.u64Context = ptReq->u64Context;
    tResp.u32UserNum = tSessionVec.size();
    UINT32 i = 0;
    for (auto it = tSessionVec.begin(); it != tSessionVec.end(); ++it, ++i)
    {
        memcpy(tResp.atOnlineUser[i].acUserName, it->tSessionUOID.acObjID, sizeof(tResp.atOnlineUser[i].acUserName));
    }
#endif

    m_pMsgMgr->PostMessage(u32NodeID, E_APP_MSG_GET_ONLINE_USER_RSP, sizeof(tResp), (CHAR*)&tResp);

    return u32Ret;
}

UINT32 CLogicImp::OnSendMessageReq(IN UINT32 u32NodeID, IN UINT32 u32MsgLen, IN CHAR* pcMsg)
{
    T_APP_SEND_MESSAGE_REQ* ptReq = (T_APP_SEND_MESSAGE_REQ*)pcMsg;
    T_APP_SEND_MESSAGE_RSP  tResp = { 0 };
    T_APP_TRANSMIT_MESSAGE_ACT  tAct = { 0 };
    UINT32  u32Ret = 0;

    do 
    {
        // 1. 获取接收者session
        T_SESSION   tSessionRecver = { 0 };
        u32Ret = m_pSessionMgr->SessionQueryByObjID(ptReq->acObjID, tSessionRecver);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "SessionQueryByObjID Failed. u32Ret = 0x%x, acObjID: %s", u32Ret, ptReq->acObjID);

        // 2. 将消息打包
        T_SESSION   tSessionSender = { 0 };
        // 通过NodeID获取发送者session
        u32Ret = m_pSessionMgr->SessionQueryByNodeID(u32NodeID, tSessionSender);
        memcpy(tAct.acFrmID, tSessionSender.tSessionUOID.acObjID, sizeof(tAct.acFrmID));
        memcpy(tAct.acMessage, ptReq->acMessage, sizeof(tAct.acMessage));

        // 3. 发送消息到接收者
        // session中含有接收者NodeID
        m_pMsgMgr->PostMessage(tSessionRecver.u32NodeID, E_APP_MSG_TRANSMIT_MESSAGE_ACT, sizeof(tAct), (CHAR*)&tAct);
        //BOOST_SLEEP(500);

        // 4. 回复发送者执行结果
    } while (0);

    tResp.u32Result = u32Ret;
    tResp.u64Context = ptReq->u64Context;
    memcpy(tResp.acObjID, ptReq->acObjID, sizeof(tResp.acObjID));
    m_pMsgMgr->PostMessage(u32NodeID, E_APP_MSG_SEND_MESSAGE_RSP, sizeof(tResp), (CHAR*)&tResp);

    return u32Ret;
}

