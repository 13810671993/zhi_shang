set(LOGIC_INC_DIR ${LOGIC_DIR}/include)
include_directories(${LOGIC_INC_DIR})
aux_source_directory(${LOGIC_DIR}/source LOGIC_SRC)
message("LOGIC_SRC: " ${LOGIC_SRC})
add_library(logic STATIC ${LOGIC_SRC})

