#ifndef __MEM_POOL_H__
#define __MEM_POOL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief memory pool type.
 *
 *  it is highly recommend that you declare a elr_mpl_t variable 
 *  with the following initializing statement.
 *  elr_mpl_t mpl = ELR_MPL_INITIALIZER;
 *  an elr_mpl_t variable is only valid when 
 *  it was initialized directly or indirectly by elr_mpl_create`s return value.
 *  don`t modify it`s members manualy.
 */
typedef struct
{
	VOID*   pPool; /*!< the actual handler of internal memory pool object. */
	INT32   n32Tag; /*!< the identity code of memory pool object. */
}T_MEM_POOL;


/*! \def ELR_MPL_INITIALIZER
 *  \brief elr_mpl_t constant for initializing.
 */
#define MEM_POOL_INITIALIZER   {NULL,0}

/*
** ��ʼ���ڴ�أ��ڲ�����һ��ȫ���ڴ�ء�
** �÷������Ա��ظ����ã�����ڴ��ģ���Ѿ���ʼ�����÷���ֱ�ӷ��ء�
** ȫ���ڴ���в������ڴ�飬�����������д������ڴ�ء�
** ����0��ʾ��ʼ��ʧ��
*/
/*! \brief initialize memory pool module.
 *  \retval zero if failed.
 *  
 *  this function can invoke many times in one process.
 *  bear in mind that one should invoke elr_mpl_finalize 
 *  the same times as invoke this function in one process
 *  when the process about to end.
 */
INT32 MemPoolInit_API();

/*
** ����һ���ڴ�أ���ָ�����䵥Ԫ��С��
** ��һ��������ʾ���ڴ�أ������ΪNULL����ʾ�������ڴ�صĸ��ڴ����ȫ���ڴ�ء�
*/
/*! \brief create a memory pool.
 *  \param fpool the parent pool of the about to created pool.
 *  \param obj_size the size of memory block can alloc from the pool.
 *  \retval NULL if failed.
 *
 *  in fact this memory pool is more like object pool.
 */
T_MEM_POOL MemPoolCreate_API(T_MEM_POOL* fpool,UINT32 obj_size);

/*
** �ж��ڴ���Ƿ�����Ч�ģ�һ���ڴ�����ɺ��������á�
** ����0��ʾ��Ч
** pool����ΪNULL
*/
INT32  MemPoolAvail_API(T_MEM_POOL* pool);

/*
** ���ڴ���������ڴ棬���СΪ�ڴ�صķ��䵥Ԫ��С��
** pool����ΪNULL
*/
/*! \brief alloc a memory block from a memory pool.
 *  \param pool  pointer to a elr_mpl_t type variable.
 *  \retval NULL if failed.
 *
 *  size of the memory block alloced is the second parameter
 *  of elr_mpl_create when create the pool.
 */
VOID* MemPoolAlloc_API(T_MEM_POOL* pool);

/*
** ��ȡ���ڴ����������ڴ��ĳߴ硣
*/
/*! \brief get the size of a memory block from a memory pool.
 *  \param mem pointer to a memory block from a memory pool.
 *  \retval size of the memory block.
 */
UINT32 MemPoolSize_API(VOID* mem);

/*
** ���ڴ��˻ظ��ڴ�ء�
*/
/*! \brief give back a memory block to it`s from memory pool.
 */
VOID MemPoolFree_API(VOID* mem);

/*
** �����ڴ�غ������ڴ�ء�
*/
/*! \brief destroy a memory pool and it`s child pools.
 */
VOID MemPoolDestroy_API(T_MEM_POOL* pool);

/*
** ��ֹ�ڴ��ģ�飬������ȫ���ڴ�ؼ������ڴ�ء�
** �����д����������ڴ�����û����ʾ���ͷţ�ִ�д˲�����Ҳ�ᱻ�ͷš�
*/
/*! \brief finalize memory pool module.
 * 
 *  when finalize is finished all memory pools will be destroyed.
 *  make sure that when finalize is in process all memory pool is not in using.
 *  so it is recommend that elr_mpl_finalize invoked only in the end of a process.
 */
VOID MemPoolFinalize_API();

#ifdef __cplusplus
}  /* end of the 'extern "C"' block */
#endif

#endif
