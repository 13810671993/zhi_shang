message(${CONF_DIR})
set(MODULE_INC_DIR ${CONF_DIR}/../include)
include_directories($INC_DIR)
include_directories(MODULE_INC_DIR)
message(${MODULE_INC_DIR})
set(SRC_LIB ${CONF_DIR}/../source/conf.cpp)
message(${SRC_LIB})
add_library(test ${BASE_DIR})

