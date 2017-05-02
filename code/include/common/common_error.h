#ifndef __COMMON_ERROR_H__
#define __COMMON_ERROR_H__

#define COMERR_OK                   (UINT32)0

#define COMMON_ERRBASE			    (UINT32)0			                    //公共错误码基数
#define COMERR_UNKOWN			    (UINT32)(-1)							//未知错误
#define COMERR_NOT_INIT			    (UINT32)(COMMON_ERRBASE + 0x0001)		//没初始化
#define COMERR_ALREADY_INIT		    (UINT32)(COMMON_ERRBASE + 0x0002)		//已经初始化
#define COMERR_INVALID_PARAM	    (UINT32)(COMMON_ERRBASE + 0x0003)		//参数无效
#define COMERR_NULL_POINTER		    (UINT32)(COMMON_ERRBASE + 0x0004)		//指针为空
#define COMERR_TIMEOUT			    (UINT32)(COMMON_ERRBASE + 0x0005)		//超时
#define COMERR_INST_LIMIT           (UINT32)(COMMON_ERRBASE + 0x0006)		//无可用实例，能力限制
#define COMERR_INST_INVALID         (UINT32)(COMMON_ERRBASE + 0x0007)		//无效实例
#define COMERR_VERSION			    (UINT32)(COMMON_ERRBASE + 0x0008)		//版本不匹配
#define COMERR_NOT_SUPPORT		    (UINT32)(COMMON_ERRBASE + 0x0009)		//不支持的功能，暂未实现或指定环境下不支持
#define COMERR_ABILITY_LIMIT        (UINT32)(COMMON_ERRBASE + 0x0010)		//能力限制
#define COMERR_NOT_FOUND		    (UINT32)(COMMON_ERRBASE + 0x0011)		//指定数据或指定项不存在
#define COMERR_SEM_FAILED		    (UINT32)(COMMON_ERRBASE + 0x0012)		//信号量错误
#define COMERR_LOCK_FAILED		    (UINT32)(COMMON_ERRBASE + 0x0013)		//锁错误
#define COMERR_PORT_USED		    (UINT32)(COMMON_ERRBASE + 0x0014)		//端口被占用
#define COMERR_DB				    (UINT32)(COMMON_ERRBASE + 0x0015)		//通用数据库错误（包含数据库连接失败）
#define COMERR_XMLPARSE			    (UINT32)(COMMON_ERRBASE + 0x0016)		//XML解析失败
#define COMERR_PASSWORD			    (UINT32)(COMMON_ERRBASE + 0x0017)		//密码错误
#define COMERR_ISLOGIN			    (UINT32)(COMMON_ERRBASE + 0x0018)		//多次登录

#define COMERR_CYCLE			    (UINT32)(COMMON_ERRBASE + 0x0020)		//循环次数错
#define COMERR_SYSCALL			    (UINT32)(COMMON_ERRBASE + 0x0021)		//系统调用错
#define COMERR_MEMERR			    (UINT32)(COMMON_ERRBASE + 0x0022)		//内存错
#define COMERR_MEMLOW			    (UINT32)(COMMON_ERRBASE + 0x0023)		//内存不足
#define COMERR_TASKERR			    (UINT32)(COMMON_ERRBASE + 0x0025)		//任务出错
#define COMERR_STACKERR			    (UINT32)(COMMON_ERRBASE + 0x0026)		//堆栈出错



#endif
