#ifndef __APP_SDK_H__
#define __APP_SDK_H__

// __stdcallʹ��C/C++�������ܹ�����API
// extern "C" //ԭ������
// __declspec( dllexport ) __declspec( dllimport )��win���ṩ���뵼������
// linux��û��Ҳ����Ҫ
// ֮���Զ�̬��ʹ��C������C++ ����ΪABI������ �����������ͬ ֱ��ԭ��Ҳ���Ǻ����� �������þ�����
// win����Ϊ�е��뵼������ ʹ��C++������̬�⵹�ǿ��Ե� linux����

#ifdef _WIN32_
    #ifdef SDK_EXPORTS
        #define SDK_API __declspec( dllexport )
    #else
        #define SDK_API __declspec( dllimport )
#endif // SDK_EXPORTS

#elif _LINUX_
    #define SDK_API
#endif // _WIN32_

// ���º����ӿ� ���ṩ��clientʹ�õ�
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
