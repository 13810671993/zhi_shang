#include "mem_pool_common.h"

/*最大内存切片的尺寸*/
/** max memory node size. it can be changed to fit the memory consume more.  */
#define MAX_SLICE_SIZE       32768  /*32KB*/
/*最大内存切片的数目*/
/** max memory slice size. it can be changed to fit the memory consume more. */
#define MAX_SLICE_COUNT      64  /*64*/

#define ALIGN(size, boundary)     (((size) + ((boundary) - 1)) & ~((boundary) - 1)) 

/*! \brief memory node type.
 *
 */
typedef struct __T_MEM_NODE
{
    struct __T_INNER_MEM_POOL       *owner;
    struct __T_MEM_NODE       *prev;
    struct __T_MEM_NODE       *next;
	/*使用过的slice的数量*/
    UINT32                      u32UsedSliceCount;
    CHAR*                       pcFirstAvail;
} T_MEM_NODE;

typedef struct __T_MEM_SLICE
{
    struct __T_MEM_SLICE      *prev;
    struct __T_MEM_SLICE      *next;
	/*内存切片所属的内存节点*/
    T_MEM_NODE                *node;
	/*内切片的标签，初始值为0，每一次从内存池中取出和归还都会加1*/
	INT32                          tag;
} T_MEM_SLICE;

typedef struct __T_INNER_MEM_POOL
{
    struct __T_INNER_MEM_POOL       *parent;
    struct __T_INNER_MEM_POOL       *first_child;
    struct __T_INNER_MEM_POOL       *prev;
    struct __T_INNER_MEM_POOL       *next;
    UINT32                       slice_count;
    UINT32                       slice_size;
	UINT32                       object_size;
    UINT32                       node_size;
	/*所有elr_mem_node组成的链表*/
    T_MEM_NODE                *first_node;
	/*刚刚创建的elr_mem_node*/
    T_MEM_NODE                *newly_alloc_node;
	/*空闲的内存切片链表*/
    T_MEM_SLICE               *first_free_slice;
	/*容纳本内存池对象的内存切片的标签*/
	INT32                          slice_tag;
#ifdef USE_THREAD
    elr_mtx                                pool_mutex;
#endif // USE_THREAD
} T_INNER_MEM_POOL;


/*全局内存池*/
static T_INNER_MEM_POOL   g_mem_pool;

/*全局内存池引用计数*/
#ifdef USE_THREAD
static elr_atomic_t     g_mpl_refs = ELR_ATOMIC_ZERO;
#else
static LONG             g_mpl_refs = 0;
#endif // USE_THREAD


/*为内存池申请一个内存节点*/
VOID                               AllocMemNode(T_INNER_MEM_POOL *pool);
/*在内存池的刚刚创建的内存节点中分配一个内存切片*/
T_MEM_SLICE*                       SliceFromNode(T_INNER_MEM_POOL *pool);
/*在内存池中分配一个内存切片，该方法将会调用上述两方法*/
T_MEM_SLICE*                       SliceFromPool(T_INNER_MEM_POOL *pool);
/*销毁内存池，inter表示是否是内部调用*/
VOID                               InterMemPoolDestroy(T_INNER_MEM_POOL *pool, INT32 inter);

/*
** 初始化内存池，内部创建一个全局内存池。
** 该方法可以被重复调用。
** 如果内存池模块已经初始化，仅仅增加引用计数然后返回。
*/
INT32 MemPoolInit_API()
{
#ifdef USE_THREAD
	elr_counter_t refs = elr_atomic_inc(&g_mpl_refs);
	if(refs == 1)
	{
#else
	g_mpl_refs++;
	if(g_mpl_refs == 1)
	{
#endif // USE_THREAD
		g_mem_pool.parent = NULL;
		g_mem_pool.first_child = NULL;
		g_mem_pool.prev = NULL;
		g_mem_pool.next = NULL;
		g_mem_pool.object_size = sizeof(T_INNER_MEM_POOL);
		g_mem_pool.slice_size = ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32))
			+ ALIGN(sizeof(T_INNER_MEM_POOL),sizeof(INT32));
		g_mem_pool.slice_count = MAX_SLICE_COUNT;
		g_mem_pool.node_size = g_mem_pool.slice_size*g_mem_pool.slice_count 
			+ ALIGN(sizeof(T_MEM_NODE),sizeof(INT32));
		g_mem_pool.first_node = NULL;
		g_mem_pool.newly_alloc_node = NULL;
		g_mem_pool.first_free_slice = NULL;
		g_mem_pool.slice_tag = 0;
#ifdef USE_THREAD
		if(elr_mtx_init(&g_mem_pool.pool_mutex) == 0)
		{
			elr_atomic_dec(&g_mpl_refs);
			return 0;
		}

#endif // USE_THREAD
	}

	return 1;
}

/*
** 创建一个内存池，并指定最大分配单元大小。
** 第一个参数表示父内存池，如果其为NULL，表示创建的内存池的父内存池是全局内存池。
*/
T_MEM_POOL MemPoolCreate_API(T_MEM_POOL* ptParentMemPool,UINT32 u32MemPoolSize)
{
	T_MEM_POOL      tMemPool = MEM_POOL_INITIALIZER;
	T_MEM_SLICE*    ptSlice = NULL;
    T_INNER_MEM_POOL*   ptInnerMemPool = NULL;

	assert(ptParentMemPool==NULL || MemPoolAvail_API(ptParentMemPool)!=0);

	if((ptSlice = SliceFromPool(&g_mem_pool)) == NULL)
		return tMemPool;
	ptInnerMemPool = (T_INNER_MEM_POOL*)((CHAR*)ptSlice
		+ ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32)));

	ptInnerMemPool->slice_tag = ptSlice->tag;
    ptInnerMemPool->first_child = NULL;
    ptInnerMemPool->parent = ptParentMemPool==NULL?&g_mem_pool:(T_INNER_MEM_POOL*)ptParentMemPool->pPool;

#ifdef USE_THREAD	
	if(ptInnerMemPool->slice_tag == 0)
	{
		if(elr_mtx_init(&ptInnerMemPool->pool_mutex)==0)
		{
			MemPoolFree_API(ptInnerMemPool);
			return tMemPool;
		}
	}

	elr_mtx_lock(&ptInnerMemPool->pool_mutex);
#endif // USE_THREAD
	ptInnerMemPool->object_size = u32MemPoolSize;
    ptInnerMemPool->slice_size = ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32))
		+ ALIGN(u32MemPoolSize,sizeof(INT32));
    if(ptInnerMemPool->slice_size < MAX_SLICE_SIZE)
        ptInnerMemPool->slice_count = MAX_SLICE_COUNT 
		- ptInnerMemPool->slice_size*(MAX_SLICE_COUNT-1)/MAX_SLICE_SIZE;
    else
        ptInnerMemPool->slice_count = 1;
    ptInnerMemPool->node_size = ptInnerMemPool->slice_size*ptInnerMemPool->slice_count 
		+ ALIGN(sizeof(T_MEM_NODE),sizeof(INT32));
    ptInnerMemPool->first_node = NULL;
    ptInnerMemPool->newly_alloc_node = NULL;
    ptInnerMemPool->first_free_slice = NULL;
#ifdef USE_THREAD
	elr_mtx_unlock(&ptInnerMemPool->pool_mutex);
#endif // USE_THREAD

#ifdef USE_THREAD
    elr_mtx_lock(&ptInnerMemPool->parent->pool_mutex);
#endif // USE_THREAD
    ptInnerMemPool->prev = NULL;
    ptInnerMemPool->next = ptInnerMemPool->parent->first_child;
    if(ptInnerMemPool->next != NULL)
        ptInnerMemPool->next->prev = ptInnerMemPool;
	ptInnerMemPool->parent->first_child = ptInnerMemPool;
#ifdef USE_THREAD
	elr_mtx_unlock(&ptInnerMemPool->parent->pool_mutex);
#endif // USE_THREAD

	tMemPool.pPool = ptInnerMemPool;
	tMemPool.n32Tag = ptInnerMemPool->slice_tag;

    return tMemPool;
}

/*
** 判断内存池是否是有效的，一般在创建完成后立即调用。
** 返回0表示无效
** pool不可为NULL
*/
INT32  MemPoolAvail_API(T_MEM_POOL* ptMempool)
{
	INT32               n32Ret = 1;
	T_MEM_SLICE*        ptSlice = NULL;

	if(ptMempool->pPool == NULL)
	{
		n32Ret = 0;
	}
	else
	{
		ptSlice = (T_MEM_SLICE*)((CHAR*)(ptMempool->pPool) 
			- ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32)));
		if (ptMempool->n32Tag != ptSlice->tag)
			n32Ret = 0;
	}

	return n32Ret;
}

/*
** 从内存池中申请内存。
*/
VOID*  MemPoolAlloc_API(T_MEM_POOL* ptMemPool)
{
	T_MEM_SLICE *pslice = NULL;
	assert(ptMemPool != NULL  && MemPoolAvail_API(ptMemPool)!=0);
	pslice = SliceFromPool((T_INNER_MEM_POOL*)ptMemPool->pPool);

    if(pslice == NULL)
        return NULL;
    else
        return (CHAR*)pslice
		+ ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32));
}


/*
** 获取从内存池中申请的内存块的尺寸。
*/
UINT32 MemPoolSize_API(VOID* pMem)
{
    T_MEM_SLICE *pslice = (T_MEM_SLICE*)((CHAR*)pMem
		- ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32)));
    return pslice->node->owner->object_size;
}

/*
** 将内存退回给内存池。执行该方法也可能将内存退回给系统。
*/
VOID  MemPoolFree_API(VOID* pMem)
{
    T_MEM_SLICE *pslice = (T_MEM_SLICE*)((CHAR*)pMem 
		- ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32)));
    T_MEM_NODE* pnode = pslice->node;
    T_INNER_MEM_POOL* pool = pnode->owner;

#ifdef USE_THREAD
    elr_mtx_lock(&pool->pool_mutex);
#endif // USE_THREAD
	pslice->tag++;
    pslice->next = pool->first_free_slice;
    if (pool->first_free_slice != NULL)
    {
        pool->first_free_slice->prev = pslice;
    }
    pool->first_free_slice = pslice;
#ifdef USE_THREAD
    elr_mtx_unlock(&pool->pool_mutex);
#endif // USE_THREAD
    return;
}

/*
** 销毁内存池和其子内存池。
*/
VOID MemPoolDestroy_API(T_MEM_POOL* ptMemPool)
{
    T_INNER_MEM_POOL  *pool = NULL;
	T_MEM_SLICE *pslice = NULL;
	INT32            flag = 0;

	assert(ptMemPool!=NULL && MemPoolAvail_API(ptMemPool)!=0);
	pool = (T_INNER_MEM_POOL*)ptMemPool->pPool;
	assert(pool->parent != NULL);

#ifdef USE_THREAD
	elr_mtx_lock(&pool->parent->pool_mutex);
    elr_mtx_lock(&pool->pool_mutex);
#endif // USE_THREAD

	pslice = (T_MEM_SLICE*)((CHAR*)pool 
		- ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32)));

	if(ptMemPool->n32Tag == pool->slice_tag)
		flag = 1;

	if(flag == 1)
	{
		if(pool->next != NULL)
			pool->next->prev = pool->prev;

		if(pool->prev == NULL)
			pool->parent->first_child = pool->next;
		else
			pool->prev->next = pool->next;
	}

#ifdef USE_THREAD
	elr_mtx_unlock(&pool->parent->pool_mutex);
#endif // USE_THREAD
	
	if(flag == 1)
		InterMemPoolDestroy(pool,0);

	ptMemPool->pPool = NULL;
	ptMemPool->n32Tag = 0;
#ifdef USE_THREAD
    elr_mtx_unlock(&pool->pool_mutex);
#endif // USE_THREAD    
}

/*
** 终止内存池模块，会销毁全局内存池及其子内存池。
** 程序中创建的其它内存池如果没有显示的释放，执行此操作后也会被释放。
*/
VOID MemPoolFinalize_API()
{
#ifdef USE_THREAD
	elr_counter_t   refs = 1;
    elr_mtx_lock(&g_mem_pool.pool_mutex);
	refs = elr_atomic_dec(&g_mpl_refs);
    if(refs == 0)
    {
#else
	g_mpl_refs--;
	if(g_mpl_refs == 0)
	{
#endif // USE_THREAD
		InterMemPoolDestroy(&g_mem_pool,0);
    }

#ifdef USE_THREAD
    elr_mtx_unlock(&g_mem_pool.pool_mutex);
#endif // USE_THREAD
}


VOID AllocMemNode(T_INNER_MEM_POOL *pool)
{
    T_MEM_NODE* pnode = (T_MEM_NODE*)malloc(pool->node_size);
    if(pnode == NULL)
        return;
    pool->newly_alloc_node = pnode;
    pnode->owner = pool;
    pnode->pcFirstAvail = (CHAR*)pnode
		+ ALIGN(sizeof(T_MEM_NODE),sizeof(INT32));

    pnode->u32UsedSliceCount = 0;

    if(pool->first_node == NULL)
    {
        pool->first_node = pnode;
        pnode->next = NULL;
		pnode->prev = NULL;
    }
    else
    {
        pnode->next = pool->first_node;
        pool->first_node->prev = pnode;
        pool->first_node = pnode;
    }
}

T_MEM_SLICE* SliceFromNode(T_INNER_MEM_POOL *pool)
{
    T_MEM_SLICE *pslice = NULL;

    if(pool->newly_alloc_node != NULL)
    {
        pool->newly_alloc_node->u32UsedSliceCount++;
        pslice = (T_MEM_SLICE*)pool->newly_alloc_node->pcFirstAvail;
		memset(pslice,0,pool->slice_size);
		pslice->next = NULL;
		pslice->prev = NULL;
		pslice->tag = 0;
        pool->newly_alloc_node->pcFirstAvail += pool->slice_size;
        pslice->node = pool->newly_alloc_node;
        if(pool->newly_alloc_node->u32UsedSliceCount == pool->slice_count)
            pool->newly_alloc_node = NULL;
    }

    return pslice;
}

/*
** 从内存池中申请内存。
*/
T_MEM_SLICE* SliceFromPool(T_INNER_MEM_POOL* pool)

{
    T_MEM_SLICE *pslice = NULL;

	assert(pool != NULL);

#ifdef USE_THREAD
    elr_mtx_lock(&pool->pool_mutex);
#endif // USE_THREAD

    if(pool->first_free_slice != NULL)
    {
        pslice = pool->first_free_slice;
        pool->first_free_slice = pslice->next;
		pslice->next = NULL;
		pslice->prev = NULL;
		pslice->tag++;
    }
    else
    {
        if(pool->newly_alloc_node == NULL)
            AllocMemNode(pool);
        pslice = SliceFromNode(pool);
    }
#ifdef USE_THREAD
    elr_mtx_unlock(&pool->pool_mutex);
#endif // USE_THREAD

	return pslice;
}


VOID InterMemPoolDestroy(T_INNER_MEM_POOL *pool,INT32 inter)
{
    T_INNER_MEM_POOL   *temp_pool = NULL;
    T_MEM_NODE  *temp_node = NULL;
	UINT32                  index = 0;

#ifdef USE_THREAD
	if(inter==1)
        elr_mtx_lock(&pool->pool_mutex);
#endif // USE_THREAD	

	temp_pool = pool->first_child;

    while(temp_pool != NULL)
    {
		pool->first_child = temp_pool->next;
		temp_pool->parent = NULL;
		temp_pool->slice_tag = -1;

		InterMemPoolDestroy(temp_pool,1);
		
        temp_pool = pool->first_child;
	}

	temp_node = pool->first_node;
	while(temp_node != NULL)
	{		
		pool->first_node = temp_node->next;

#ifdef USE_THREAD
		if(pool == &g_mem_pool)
		{
			index = 0;
			temp_pool = (T_INNER_MEM_POOL*)((CHAR*)temp_node
				+ ALIGN(sizeof(T_MEM_NODE),sizeof(INT32))
				+ ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32)));
			while(index < temp_node->u32UsedSliceCount)
			{
				elr_mtx_finalize(&pool->pool_mutex);
				temp_pool = (T_INNER_MEM_POOL*)((CHAR*)pool+g_mem_pool.slice_size);
				index++;
			}
		}
#endif // USE_THREAD

		free(temp_node);
		temp_node = pool->first_node ;
	}

	/*如果不是根节点*/
	if(pool != &g_mem_pool)
		MemPoolFree_API(pool);

#ifdef USE_THREAD
	if(inter==1)
        elr_mtx_unlock(&pool->pool_mutex);
#endif // USE_THREAD
}
