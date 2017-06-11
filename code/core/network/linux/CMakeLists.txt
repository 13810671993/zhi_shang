set(NET_INC_DIR ${NET_DIR}/include)
include_directories(${NET_INC_DIR})
aux_source_directory(${NET_DIR}/source NET_SRC)
message("NET_SRC: " ${NET_SRC})
add_library(network STATIC ${NET_SRC})

