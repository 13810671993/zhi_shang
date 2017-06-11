set(ADPT_INC_DIR ${ADPT_DIR}/include)
include_directories(${ADPT_INC_DIR})
aux_source_directory(${ADPT_DIR}/source ADPT_SRC)
message("ADPT_SRC: " ${ADPT_SRC})
add_library(adpt STATIC ${ADPT_SRC})

