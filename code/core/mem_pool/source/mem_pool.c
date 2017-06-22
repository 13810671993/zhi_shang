#include "mem_pool_common.h"

/*����ڴ���Ƭ�ĳߴ�*/
/** max memory node size. it can be changed to fit the memory consume more.  */
#define MAX_SLICE_SIZE       32768  /*32KB*/
/*����ڴ���Ƭ����Ŀ*/
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
	/*ʹ�ù���slice������*/
    UINT32                      u32UsedSliceCount;
    CHAR*                       pcFirstAvail;
} T_MEM_NODE;

typedef struct __T_MEM_SLICE
{
    struct __T_MEM_SLICE      *prev;
    struct __T_MEM_SLICE      *next;
	/*�ڴ���Ƭ�������ڴ�ڵ�*/
    T_MEM_NODE                *node;
	/*����Ƭ�ı�ǩ����ʼֵΪ0��ÿһ�δ��ڴ����ȡ���͹黹�����1*/
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
	/*����elr_mem_node��ɵ�����*/
    T_MEM_NODE                *first_node;
	/*�ոմ�����elr_mem_node*/
    T_MEM_NODE                *newly_alloc_node;
	/*���е��ڴ���Ƭ����*/
    T_MEM_SLICE               *first_free_slice;
	/*���ɱ��ڴ�ض�����ڴ���Ƭ�ı�ǩ*/
	INT32                          slice_tag;
#ifdef USE_THREAD
    elr_mtx                                pool_mutex;
#endif // USE_THREAD
} T_INNER_MEM_POOL;


/*ȫ���ڴ��*/
static T_INNER_MEM_POOL   g_mem_pool;

/*ȫ���ڴ�����ü���*/
#ifdef USE_THREAD
static elr_atomic_t     g_mpl_refs = ELR_ATOMIC_ZERO;
#else
static LONG             g_mpl_refs = 0;
#endif // USE_THREAD


/*Ϊ�ڴ������һ���ڴ�ڵ�*/
VOID                               AllocMemNode(T_INNER_MEM_POOL *pool);
/*���ڴ�صĸոմ������ڴ�ڵ��з���һ���ڴ���Ƭ*/
T_MEM_SLICE*                       SliceFromNode(T_INNER_MEM_POOL *pool);
/*���ڴ���з���һ���ڴ���Ƭ���÷��������������������*/
T_MEM_SLICE*                       SliceFromPool(T_INNER_MEM_POOL *pool);
/*�����ڴ�أ�inter��ʾ�Ƿ����ڲ�����*/
VOID                               InterMemPoolDestroy(T_INNER_MEM_POOL *pool, INT32 inter);

/*
** ��ʼ���ڴ�أ��ڲ�����һ��ȫ���ڴ�ء�
** �÷������Ա��ظ����á�
** ����ڴ��ģ���Ѿ���ʼ���������������ü���Ȼ�󷵻ء�
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
** ����һ���ڴ�أ���ָ�������䵥Ԫ��С��
** ��һ��������ʾ���ڴ�أ������ΪNULL����ʾ�������ڴ�صĸ��ڴ����ȫ���ڴ�ء�
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
** �ж��ڴ���Ƿ�����Ч�ģ�һ���ڴ�����ɺ��������á�
** ����0��ʾ��Ч
** pool����ΪNULL
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
** ���ڴ���������ڴ档
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
** ��ȡ���ڴ����������ڴ��ĳߴ硣
*/
UINT32 MemPoolSize_API(VOID* pMem)
{
    T_MEM_SLICE *pslice = (T_MEM_SLICE*)((CHAR*)pMem
		- ALIGN(sizeof(T_MEM_SLICE),sizeof(INT32)));
    return pslice->node->owner->object_size;
}

/*
** ���ڴ��˻ظ��ڴ�ء�ִ�и÷���Ҳ���ܽ��ڴ��˻ظ�ϵͳ��
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
** �����ڴ�غ������ڴ�ء�
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
** ��ֹ�ڴ��ģ�飬������ȫ���ڴ�ؼ������ڴ�ء�
** �����д����������ڴ�����û����ʾ���ͷţ�ִ�д˲�����Ҳ�ᱻ�ͷš�
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
** ���ڴ���������ڴ档
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

	/*������Ǹ��ڵ�*/
	if(pool != &g_mem_pool)
		MemPoolFree_API(pool);

#ifdef USE_THREAD
	if(inter==1)
        elr_mtx_unlock(&pool->pool_mutex);
#endif // USE_THREAD
}
