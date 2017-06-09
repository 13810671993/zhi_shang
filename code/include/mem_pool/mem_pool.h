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
** 初始化内存池，内部创建一个全局内存池。
** 该方法可以被重复调用，如果内存池模块已经初始化，该方法直接返回。
** 全局内存池中不容纳内存块，用于容纳所有创建的内存池。
** 返回0表示初始化失败
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
** 创建一个内存池，并指定分配单元大小。
** 第一个参数表示父内存池，如果其为NULL，表示创建的内存池的父内存池是全局内存池。
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
** 判断内存池是否是有效的，一般在创建完成后立即调用。
** 返回0表示无效
** pool不可为NULL
*/
INT32  MemPoolAvail_API(T_MEM_POOL* pool);

/*
** 从内存池中申请内存，其大小为内存池的分配单元大小。
** pool不可为NULL
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
** 获取从内存池中申请的内存块的尺寸。
*/
/*! \brief get the size of a memory block from a memory pool.
 *  \param mem pointer to a memory block from a memory pool.
 *  \retval size of the memory block.
 */
UINT32 MemPoolSize_API(VOID* mem);

/*
** 将内存退回给内存池。
*/
/*! \brief give back a memory block to it`s from memory pool.
 */
VOID MemPoolFree_API(VOID* mem);

/*
** 销毁内存池和其子内存池。
*/
/*! \brief destroy a memory pool and it`s child pools.
 */
VOID MemPoolDestroy_API(T_MEM_POOL* pool);

/*
** 终止内存池模块，会销毁全局内存池及其子内存池。
** 程序中创建的其它内存池如果没有显示的释放，执行此操作后也会被释放。
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
