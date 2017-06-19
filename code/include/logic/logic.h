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
    virtual UINT32  Run() = 0;          // �߼��������
    virtual UINT32  Stop() = 0;         // �߼�ֹͣ���

};

#endif
