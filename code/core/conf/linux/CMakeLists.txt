#message(${CONF_DIR})
set(CONF_INC_DIR ${CONF_DIR}/include)
include_directories(${CONF_INC_DIR})
#message(${CONF_INC_DIR})
#set(SRC_LIB ${CONF_DIR}/source/conf.cpp)
aux_source_directory(${CONF_DIR}/source CONF_SRC)
add_library(conf STATIC ${CONF_SRC})

