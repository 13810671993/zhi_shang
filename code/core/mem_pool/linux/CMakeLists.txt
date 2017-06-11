set(MEM_POOL_INC_DIR ${MEM_POOL_DIR}/include)
include_directories(${MEM_POOL_INC_DIR})
aux_source_directory(${MEM_POOL_DIR}/source MEM_POOL_SRC)
message("MEM_POOL_SRC: " ${MEM_POOL_SRC})
add_library(mempool STATIC ${MEM_POOL_SRC})

