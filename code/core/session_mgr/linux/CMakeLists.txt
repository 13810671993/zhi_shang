set(SUB_INC_DIR ${SUB_DIR}/include)
include_directories(${SUB_INC_DIR})
aux_source_directory(${SUB_DIR}/source SUB_SRC)
message("SUB_SRC: " ${SUB_SRC})
add_library(subscriber STATIC ${SUB_SRC})

