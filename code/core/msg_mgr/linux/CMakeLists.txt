set(MSG_MGR_INC_DIR ${MSG_MGR_DIR}/include)
include_directories(${MSG_MGR_INC_DIR})
aux_source_directory(${MSG_MGR_DIR}/source MSG_MGR_SRC)
message("MSG_MGR_SRC: " ${MSG_MGR_SRC})
add_library(msgmgr STATIC ${MSG_MGR_SRC})

