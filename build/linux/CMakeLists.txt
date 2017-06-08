PROJECT(zhishang C CXX)	# 工程名字 可以使用两个工程名相关的变量
cmake_minimum_required(VERSION 2.6)	# 版本声明,可以使用高级指令
set(BASE_DIR ${PROJECT_SOURCE_DIR}/../..)
message(${BASE_DIR})
set(INC_DIR ${BASE_DIR}/code/include)
set(SRC_DIR ${BASE_DIR}/code)
set(CONF_DIR ${SRC_DIR}/core/conf/linux)
message(${CONF_DIR}/)
add_subdirectory(${CONF_DIR}/ linux.out)
#message("hello world")
#message(${PROJECT_SOURCE_DIR})
#message(${PROJECT_BINARY_DIR})

