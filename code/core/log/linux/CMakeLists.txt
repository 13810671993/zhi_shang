#message("LOG_DIR: "${LOG_DIR})
set(LOG_INC_DIR ${LOG_DIR}/include)
include_directories(${LOG_INC_DIR})
add_definitions(-DBOOST_LOG_DYN_LINK)
#message("LOG_INC_DIR: "${LOG_INC_DIR})
aux_source_directory(${LOG_DIR}/source LOG_SRC)
#message("LOG_SRC: "${LOG_SRC})
add_library(log STATIC ${LOG_SRC})

