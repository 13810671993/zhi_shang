#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

    /*********************************************************************************************************
    * 数据类型
    *********************************************************************************************************/
#ifndef _UINT32_TYPE_
#define _UINT32_TYPE_
#ifdef _WIN32_
    typedef signed      __int64		    INT64;
    typedef unsigned    __int64	        UINT64;
#else
    typedef signed	    long long	    INT64;
    typedef unsigned    long long	    UINT64;
#endif

    typedef  unsigned   int			    UINT32;
    typedef  signed     int				INT32;

    typedef  unsigned   short			UINT16;
    typedef  signed     short			INT16;

    typedef  unsigned   char			UINT8;
    typedef  signed     char		    INT8;
#endif //UINT32


#ifndef _LONG_TYPE_
#define _LONG_TYPE_	
    typedef long			            LONG;
    typedef unsigned long	            ULONG;
#endif


#ifdef _LINUX_
    typedef void* 			PVOID;
    typedef void* 			HANDLE;
    typedef void*			HWND;
#endif


#ifndef _FLOAT32_TYPE_
#define _FLOAT32_TYPE_
    typedef	float			FLOAT32;
    typedef double			FLOAT64;
#endif

#ifndef _CHAR_TYPE_
#define _CHAR_TYPE_
    typedef char            CHAR;
#endif

#ifndef _HAVE_TYPE_BOOL
#define _HAVE_TYPE_BOOL
    typedef int             BOOL;
#endif

#ifndef VOID
    typedef void VOID;
#endif

#ifdef _LINUX_
    typedef unsigned long       DWORD;
    typedef unsigned short      WORD;
    typedef UINT8       BYTE;
    typedef double              DOUBLE;
    typedef UINT8       byte;
#endif

/*********************************************************************************************************
* 函数接口相关
*********************************************************************************************************/
#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef IO
#define IO
#endif

#ifdef _LINUX_
#define HOWCALL
#else
#define HOWCALL __stdcall
#endif

/*********************************************************************************************************
* 布尔常量 和 空值
*********************************************************************************************************/
#ifndef    TRUE
#define    TRUE	1
#endif

#ifndef    FALSE
#define	   FALSE 0
#endif

#ifndef    NULL
#define	   NULL 0
#endif


#ifdef __cplusplus
}
#endif

#endif //__DATA_TYPE_H__
