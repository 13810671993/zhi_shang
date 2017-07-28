#include "home/home_common.h"

CCtrlHome::CCtrlHome() : QObject()
{

}

CCtrlHome::~CCtrlHome()
{

}

CCtrlHome* CCtrlHome::m_pCtrlHome = NULL;
CCtrlHome *CCtrlHome::GetInstance()
{
    if (m_pCtrlHome == NULL)
        m_pCtrlHome = new CCtrlHome;
    return m_pCtrlHome;
}

VOID CCtrlHome::DestroyInstance()
{
    if (m_pCtrlHome != NULL)
    {
        delete m_pCtrlHome;
        m_pCtrlHome = NULL;
    }
}

VOID CCtrlHome::OnUpdateOnlineUserNtf(const CHAR *pcMsg, UINT32 u32MsgLen)
{
    T_APP_UPDATE_ONLINE_USER_NTF*	ptNtf = (T_APP_UPDATE_ONLINE_USER_NTF*)pcMsg;

    // 收集在线用户列表
    QList<T_GNRL_ONLINE_USER> tUserList;
    for (UINT32 i = 0; i < ptNtf->u32UserNum; ++i)
    {
        tUserList.push_back(ptNtf->atOnlineUser[i]);
    }
    emit SIGNAL_UpdateOnlineUser(tUserList);
}

VOID CCtrlHome::OnSendMessageRsp(const CHAR *pcMsg, UINT32 u32MsgLen)
{
    T_APP_SEND_MESSAGE_RSP*	ptRsp = (T_APP_SEND_MESSAGE_RSP*)pcMsg;
    if (ptRsp->u32Result == COMERR_NOT_FOUND)
    {
        // 对方已下线
        emit SIGNAL_SendMessageError(ptRsp->acObjID);
    }
}

VOID CCtrlHome::OnTransmitMessageAct(const CHAR *pcMsg, UINT32 u32MsgLen)
{
    T_APP_TRANSMIT_MESSAGE_ACT*	ptAct = (T_APP_TRANSMIT_MESSAGE_ACT*)pcMsg;
    qDebug() << ptAct->acFrmID << " - " << ptAct->acMessage;
    emit SIGNAL_TransmitMessage(ptAct->acFrmID, ptAct->acMessage);
}

