#ifndef __ADPT_H__
#define __ADPT_H__

class CSubscriber;

//   ≈‰∆˜ –Èª˘¿‡
class CAdpt
{
public:
    CAdpt()             {}
    virtual ~CAdpt()    {}

    virtual VOID    SetSubscriber(IN CSubscriber* pSubscriber) = 0;
    virtual UINT32  StartListen(IN UINT16 u16Port) = 0;
    virtual UINT32  RegistAdpt(IN CAdpt* pAdpt) = 0;
    virtual UINT32  PushMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN CHAR* pcMsg) = 0; 
    virtual VOID    PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg) = 0;
};

#endif

