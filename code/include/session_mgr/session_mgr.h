#ifndef __SESSION_MGR_H__
#define __SESSION_MGR_H__

/*
* �Ự ��һ�ε�¼(login)���˳���¼Ϊһ���Ự
* NodeID���������ӵ�Ψһֵ �ǲ�Ӧ����Ϊ��ɻỰ��Ԫ��
* ���������������� ��session������ �������ظ���¼�ĳ���
* �������߼��� ÿ�������Ự�Ҷ��������Ҫ�ж�һ���Ƿ������ظ���¼
*/

typedef UINT32 TypeNetIP;

typedef struct
{
    TypeNetIP   tIP;
    UINT16      u16Port;
}T_NET_ADDR;

typedef struct _T_SESSION_UNIQUE_OBJ_ID
{
    CHAR    acObjID[APP_MAX_NAME_LEN];
    UINT32  u32NodeID;
    _T_SESSION_UNIQUE_OBJ_ID()
    {
        memset(acObjID, 0, sizeof(acObjID));
        u32NodeID = 0;
    }
}T_SESSION_UNIQUE_OBJ_ID;

typedef struct
{
    UINT32                  u32NodeID;
    T_NET_ADDR              tNetAddr;
    T_SESSION_UNIQUE_OBJ_ID tSessionUOID;
}T_SESSION;

class CSessionMgr
{
public:
    static CSessionMgr* GetInstance();
    static VOID         DestroyInstance();

protected:
    CSessionMgr();
    ~CSessionMgr();

public:
    virtual UINT32  SessionAdd(IN T_SESSION& tSession) = 0;
    virtual UINT32  SessionDel(IN UINT32 u32NodeID) = 0;
    virtual UINT32  SessionQueryByNodeID(IN UINT32 u32NodeID, OUT T_SESSION& tSession) = 0;
    virtual UINT32  SessionQueryByObjID(IN const CHAR* pcObjID, OUT T_SESSION& tSession) = 0;
    virtual UINT32  SessionGetNetNode(IN const T_SESSION& tSession, OUT UINT32& u32NodeID) = 0;
    virtual UINT32  SessionGet(OUT std::vector<T_SESSION>& tSessionVec) = 0;
};

#endif // !__SESSION_MGR_H__

