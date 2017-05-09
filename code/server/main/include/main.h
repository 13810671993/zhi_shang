#ifndef __MAIN_H__
#define __MAIN_H__

//œﬂ≥Ã–›√ﬂ£¨∫¡√Îº∂  
#define  BOOST_SLEEP(n)  boost::thread::sleep(boost::get_system_time()+boost::posix_time::millisec(n))

class CMain
{
public:
    static CMain*   GetInstance();
    static VOID     DestroyInstance();

public:
    UINT32 InitCommModule();
    UINT32 InitNetworkModule();
    UINT32 InitMessageModule();
    UINT32 InitLogicModule();

private:
    CMain();
    ~CMain();

private:
    static CMain*   m_pMain;
};

#endif
