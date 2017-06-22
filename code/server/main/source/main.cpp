#include "main_common.h"

CMain::CMain()
{

}

CMain::~CMain()
{

}

CMain* CMain::m_pMain = NULL;

CMain* CMain::GetInstance()
{
    if (m_pMain == NULL)
        m_pMain = new CMain();
    return m_pMain;
}

VOID CMain::DestroyInstance()
{
    if (m_pMain != NULL)
    {
        delete m_pMain;
        m_pMain = NULL;
    }
}

UINT32 CMain::InitCommModule()
{
    UINT32  u32Ret = 0;
    do 
    {
        CConf* pConf = CConf::GetInstance("");
        CHECK_ERR_BREAK(pConf != NULL, COMERR_NULL_POINTER, "CConf::GetInstance Failed. u32Ret = 0x%x", u32Ret);
        CLog* pLog = CLog::GetInstance(E_LOG_LEVEL_DEBUG);
        CHECK_ERR_BREAK(pLog != NULL, COMERR_NULL_POINTER, "CLog::GetInstance Failed. u32Ret = 0x%x", u32Ret);
    } while (0);

    return u32Ret;
}

UINT32 CMain::InitNetworkModule()
{
    UINT32  u32Ret = COMERR_OK;
    do 
    {
        CNetworkMgr* pNetworkMgr = CNetworkMgr::GetInstance();
        CHECK_ERR_BREAK(pNetworkMgr != NULL, COMERR_NULL_POINTER, "CNetworkMgr::GetInstance Failed. u32Ret = 0x%x", u32Ret);
    } while (0);

    return u32Ret;
}

UINT32 CMain::InitMessageModule()
{
    UINT32  u32Ret = COMERR_OK;
    do 
    {
        CMsgMgr* pMsgMgr = CMsgMgr::GetInstance();
        CHECK_ERR_BREAK(pMsgMgr != NULL, COMERR_NULL_POINTER, "CMsgMgr::GetInstance Failed. u32Ret = 0x%x", u32Ret);

        CAdpt* pAdpt = CSvrAdpt::GetInstance();
        CHECK_ERR_BREAK(pAdpt != NULL, COMERR_NULL_POINTER, "CSvrAdpt::GetInstance Failed. u32Ret = 0x%x", u32Ret);

        u32Ret = pMsgMgr->AddAdpt(pAdpt);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "AddAdpt Failed. u32Ret = 0x%x", u32Ret);
        //u32Ret = pMsgMgr->StartLisen("127.0.0.1", 1993);
        //u32Ret = pMsgMgr->StartLisen("192.168.31.181", 1993);
        //u32Ret = pMsgMgr->StartLisen(1993);
        u32Ret = pMsgMgr->StartLisen(8080);
        CHECK_ERR_BREAK(u32Ret == 0, u32Ret, "StartListen Failed. u32Ret = 0x%x", u32Ret);

    } while (0);

    return u32Ret;
}

UINT32 CMain::InitLogicModule()
{
	UINT32	u32Ret = 0;
	do 
	{
		CLogic* pLogic = CLogic::GetInstance();
		CHECK_ERR_BREAK(pLogic != NULL, COMERR_NULL_POINTER, "CLogic::GetInstance Failed. u32Ret = 0x%x", u32Ret);
		pLogic->Run();
	} while (0);

	return u32Ret;
}

#if 0
#pragma warning(disable:4996)
#pragma warning(disable:4703)
#include <vector>

std::vector<CHAR> cDataVec;
std::vector<UINT32> u32TestVec;
std::string strTest;
CHAR pcTest[512];
CHAR* pTest;

CHAR* AssignInStack(CHAR** pcPoint2, CHAR* pcPoint1, CHAR*& pcRefer)
{
    CHAR cText = 'a';
    cDataVec.push_back(cText);
    cDataVec.push_back(++cText);

    CHAR buf[] = "test stack";
    strTest = buf;
    (*pcPoint2) = buf;
    //pcPoint1 = buf;
    pcPoint1 = new CHAR[250];
    strcpy(pcPoint1, buf);

    pcRefer = new CHAR[250];
    strcpy(pcRefer, buf);
#if 0
    std::string strTemp1(strTest);
    std::string strTemp2(strTemp1);
    std::string strTemp3 = strTemp2;

    LogDebug("&buf: 0x%x", buf);
    LogDebug("&strTest: 0x%x", (strTest.data()));
    LogDebug("&strTemp1: 0x%x", (strTemp1.data()));
    LogDebug("&strTemp2: 0x%x", (strTemp2.data()));
    LogDebug("&strTemp3: 0x%x", (strTemp3.data()));
#endif

    UINT32 u32Num = 1;
    u32TestVec.push_back(u32Num);
    u32TestVec.push_back(++u32Num);

    strcpy(pcTest, strTest.data());
    pTest = buf;

    return buf;
}

CHAR*& AssignInStackRefer()
{
    CHAR buf[] = "test stack";

    CHAR* p = buf;
    return p;
}
#endif

#include <iostream>
#include <ctime>
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/singleton_pool.hpp>

const INT32 MAXLENGTH = 1000;

typedef struct
{
    CHAR test[512];
}test;

INT32 main()
{

#if 1
    CMain* pMain = CMain::GetInstance();

    pMain->InitCommModule();

#endif
#if 0
    int** vec3 = new int*[MAXLENGTH];
    getchar();
    MemPoolInit_API();
    T_MEM_POOL tMemPool = MemPoolCreate_API(NULL, 1024 * 100);
    for (int i = 0; i < MAXLENGTH; ++i)
    {
        vec3[i] = (int*)MemPoolAlloc_API(&tMemPool);
        LogDebug("size: %d", MemPoolSize_API(vec3[i]));
        BOOST_SLEEP(15);
    }

    for (int i = 0; i < MAXLENGTH; ++i)
    {
        MemPoolFree_API(vec3[i]);
    }
    //MemPoolDestroy_API(&tMemPool);
    //MemPoolFinalize_API();
    delete[] vec3;
    std::cout << "end" << std::endl;
#endif

#if 0
#if 1
    //boost::pool<> p(sizeof(int));
    boost::pool<> p(2048);

    int** vec1 = new int*[MAXLENGTH];
    int** vec2 = new int*[MAXLENGTH];
    int** vec3 = new int*[MAXLENGTH];

    clock_t clock_begin = clock();
    for (int i = 0; i < MAXLENGTH; ++i)
        vec1[i] = static_cast<int*>(p.malloc());

    for (int i = 0; i < MAXLENGTH; ++i)
        p.free(vec1[i]);

    clock_t clock_end = clock();
    std::cout << "boost::pool 程序运行了 " << clock_end - clock_begin << " 个系统时钟" << std::endl;

    clock_begin = clock();
    for (int i = 0; i < MAXLENGTH; ++i)
        vec2[i] = new int[250];

    for (int i = 0; i < MAXLENGTH; ++i)
        delete vec2[i];

    clock_end = clock();
    std::cout << "new/delete 程序运行了 " << clock_end - clock_begin << " 个系统时钟" << std::endl;


    MemPoolInit_API();
    T_MEM_POOL tMemPool = MemPoolCreate_API(NULL, 2048);
    clock_begin = clock();
    for (int i = 0; i < MAXLENGTH; ++i)
        vec3[i] = (int*)MemPoolAlloc_API(&tMemPool);

    for (int i = 0; i < MAXLENGTH; ++i)
        MemPoolFree_API(vec3[i]);

    clock_end = clock();
    std::cout << "MemPool 程序运行了 " << clock_end - clock_begin << " 个系统时钟" << std::endl;

#else
    boost::pool<> pl(2000);
    CHAR* pp1 = NULL;
    CHAR* pp2 = NULL;
    CHAR* temp = "0123456789";
    CHAR buf[2001] = { 0 };
    for (auto i = 0; i < 200; ++i)
    {
        memcpy(buf + strlen(temp) * i, temp, strlen(temp));
    }
    clock_t clock_begin = clock();
    for (INT32 i = 0; i < MAXLENGTH; ++i)
    {
        pp1 = (CHAR*)pl.malloc();
        memset(pp1, 0, 2000);
        memcpy(pp1, buf, 2000);
        pl.free(pp1);
    }
    clock_t clock_end = clock();
    std::cout << "内存池 程序运行了 " << clock_end - clock_begin << " 个系统时钟" << std::endl;

    clock_begin = clock();
    for (INT32 i = 0; i < MAXLENGTH; ++i)
    {
        pp2 = new CHAR[2000];
        memset(pp1, 0, 2000);
        memcpy(pp1, buf, 2000);
        delete[] pp2;
    }
    clock_end = clock();
    std::cout << "手动分配 程序运行了 " << clock_end - clock_begin << " 个系统时钟" << std::endl;
#endif

    CHAR** vec3 = new CHAR*[MAXLENGTH];
    MemPoolInit_API();
    T_MEM_POOL tMemPool = MemPoolCreate_API(NULL, 2048);
    while (1)
    {
        vec3[0] = (CHAR*)MemPoolAlloc_API(&tMemPool);
        memset(vec3[0], 0, 100);
        memcpy(vec3[0], "123456", 6);
        MemPoolFree_API(vec3[0]);
        BOOST_SLEEP(10);
    }
    
#endif
#if 1
    pMain->InitNetworkModule();
    pMain->InitMessageModule();
    pMain->InitLogicModule();

#endif
    while (1)
        BOOST_SLEEP(1000);
    CMain::DestroyInstance();
}
