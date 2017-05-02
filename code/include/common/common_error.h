#ifndef __COMMON_ERROR_H__
#define __COMMON_ERROR_H__

#define COMERR_OK                   (UINT32)0

#define COMMON_ERRBASE			    (UINT32)0			                    //�������������
#define COMERR_UNKOWN			    (UINT32)(-1)							//δ֪����
#define COMERR_NOT_INIT			    (UINT32)(COMMON_ERRBASE + 0x0001)		//û��ʼ��
#define COMERR_ALREADY_INIT		    (UINT32)(COMMON_ERRBASE + 0x0002)		//�Ѿ���ʼ��
#define COMERR_INVALID_PARAM	    (UINT32)(COMMON_ERRBASE + 0x0003)		//������Ч
#define COMERR_NULL_POINTER		    (UINT32)(COMMON_ERRBASE + 0x0004)		//ָ��Ϊ��
#define COMERR_TIMEOUT			    (UINT32)(COMMON_ERRBASE + 0x0005)		//��ʱ
#define COMERR_INST_LIMIT           (UINT32)(COMMON_ERRBASE + 0x0006)		//�޿���ʵ������������
#define COMERR_INST_INVALID         (UINT32)(COMMON_ERRBASE + 0x0007)		//��Чʵ��
#define COMERR_VERSION			    (UINT32)(COMMON_ERRBASE + 0x0008)		//�汾��ƥ��
#define COMERR_NOT_SUPPORT		    (UINT32)(COMMON_ERRBASE + 0x0009)		//��֧�ֵĹ��ܣ���δʵ�ֻ�ָ�������²�֧��
#define COMERR_ABILITY_LIMIT        (UINT32)(COMMON_ERRBASE + 0x0010)		//��������
#define COMERR_NOT_FOUND		    (UINT32)(COMMON_ERRBASE + 0x0011)		//ָ�����ݻ�ָ�������
#define COMERR_SEM_FAILED		    (UINT32)(COMMON_ERRBASE + 0x0012)		//�ź�������
#define COMERR_LOCK_FAILED		    (UINT32)(COMMON_ERRBASE + 0x0013)		//������
#define COMERR_PORT_USED		    (UINT32)(COMMON_ERRBASE + 0x0014)		//�˿ڱ�ռ��
#define COMERR_DB				    (UINT32)(COMMON_ERRBASE + 0x0015)		//ͨ�����ݿ���󣨰������ݿ�����ʧ�ܣ�
#define COMERR_XMLPARSE			    (UINT32)(COMMON_ERRBASE + 0x0016)		//XML����ʧ��
#define COMERR_PASSWORD			    (UINT32)(COMMON_ERRBASE + 0x0017)		//�������
#define COMERR_ISLOGIN			    (UINT32)(COMMON_ERRBASE + 0x0018)		//��ε�¼

#define COMERR_CYCLE			    (UINT32)(COMMON_ERRBASE + 0x0020)		//ѭ��������
#define COMERR_SYSCALL			    (UINT32)(COMMON_ERRBASE + 0x0021)		//ϵͳ���ô�
#define COMERR_MEMERR			    (UINT32)(COMMON_ERRBASE + 0x0022)		//�ڴ��
#define COMERR_MEMLOW			    (UINT32)(COMMON_ERRBASE + 0x0023)		//�ڴ治��
#define COMERR_TASKERR			    (UINT32)(COMMON_ERRBASE + 0x0025)		//�������
#define COMERR_STACKERR			    (UINT32)(COMMON_ERRBASE + 0x0026)		//��ջ����



#endif
