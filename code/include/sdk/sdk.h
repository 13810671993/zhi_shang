#ifndef __APP_SDK_H__
#define __APP_SDK_H__

// __stdcall使非C/C++语言内能够调用API
// extern "C" //原样编译
// __declspec( dllexport ) __declspec( dllimport )是win下提供导入导出工具
// linux下没有也不需要
// 之所以动态库使用C而不是C++ 是因为ABI不兼容 函数描述风格不同 直击原因也不是很明白 反正不用就是了
// win下因为有导入导出工具 使用C++创建动态库倒是可以的 linux不行

#ifdef _WIN32_
    #ifdef SDK_EXPORTS
        #define SDK_API __declspec( dllexport )
    #else
        #define SDK_API __declspec( dllimport )
#endif // SDK_EXPORTS

#elif _LINUX_
    #define SDK_API
#endif // _WIN32_

// 以下函数接口 是提供给client使用的
#ifdef __cplusplus
extern "C" {
#endif

typedef VOID(*PFN_SDK_MESSAGE_CALLBACK)(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);

SDK_API UINT32 Sdk_Init();
SDK_API UINT32 Sdk_Connect(IN const CHAR* pcIpAddr, IN UINT16 u16Port, OUT UINT32& u32NodeID);
SDK_API UINT32 Sdk_PostMessage(IN UINT32 u32NodeID, IN UINT32 u32MsgType, IN UINT32 u32MsgLen, IN const CHAR* pcMsg);
SDK_API UINT32 Sdk_RegistRecvMsgCallBack(PFN_SDK_MESSAGE_CALLBACK pFunMsgCB);



#ifdef __cplusplus
}
#endif

#endif
