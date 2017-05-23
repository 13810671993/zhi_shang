#ifndef __COMMON_TOOL_H__
#define __COMMON_TOOL_H__

#ifndef CHECK_ERR_BREAK

#define CHECK_ERR_BREAK(bRet, result, format, ...)\
    if( !(bRet) )\
{\
    printf(format, ##__VA_ARGS__);\
    LogError(format, ##__VA_ARGS__);\
    u32Ret = result; \
    break; \
}\


#endif


#endif
