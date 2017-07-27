#ifndef __LOGIC_H__
#define __LOGIC_H__

class CLogic
{
public:
    static CLogic*  GetInstance();
    static VOID     DestroyInstance();

protected:
    CLogic();
    virtual ~CLogic();

public:
    virtual UINT32  Run() = 0;          // 逻辑触发入口
    virtual UINT32  Stop() = 0;         // 逻辑停止入口

    virtual UINT32  Connected(IN UINT32 u32NodeID, IN const std::string& strIp, IN UINT16 u16Port) = 0;
    virtual UINT32  Disconnected(IN UINT32 u32NodeID) = 0;
};

#endif
