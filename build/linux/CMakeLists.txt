project(zhishang)								# 工程名字 可以使用两个工程名相关的变量
cmake_minimum_required(VERSION 2.6)				# 版本声明,可以使用高级指令
set(BASE_DIR ${PROJECT_SOURCE_DIR}/../..)		# 项目根目录
message("BASE_DIR: " ${BASE_DIR})
set(INC_DIR ${BASE_DIR}/code/include)			# 头文件目录
include_directories(${INC_DIR})					# 所有项目包含头文件
set(SRC_DIR ${BASE_DIR}/code)					# 源文件根目录
set(CMAKE_CXX_COMPILER "g++")                   # 设置编译器为g++


##=================================================================================================#
# Debug\Release
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )                                    
    message("Debug:")
    add_definitions(-D_DEBUG_)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wno-unused-variable")
    set(LIBRARY_OUTPUT_PATH ${BASE_DIR}/lib/linux/Debug)	# 静态链接库生成目录
    set(EXECUTABLE_OUTPUT_PATH ${BASE_DIR}/bin/linux/Debug)	# 可执行文件生成目录
else( CMAKE_BUILD_TYPE STREQUAL "Release" )
    message("Release:")
    set(CMAKE_BUILD_TYPE "Release")                                        
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
    set(LIBRARY_OUTPUT_PATH ${BASE_DIR}/lib/linux/Release)	# 静态链接库生成目录
    set(EXECUTABLE_OUTPUT_PATH ${BASE_DIR}/bin/linux/Release)	# 可执行文件生成目录
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )          
##=================================================================================================#


##=================================================================================================#
# 配置模块 静态链接
set(CONF_DIR ${SRC_DIR}/core/conf)				# 配置模块cmake
include(${CONF_DIR}/linux/CMakeLists.txt)
##=================================================================================================#


##=================================================================================================#
## log模块 静态链接
set(LOG_DIR ${SRC_DIR}/core/log)				# log模块cmake
include(${LOG_DIR}/linux/CMakeLists.txt)
##=================================================================================================#


##=================================================================================================#
## 网络模块 静态链接
set(NET_DIR ${SRC_DIR}/core/network)			# 网络模块cmake
include(${NET_DIR}/linux/CMakeLists.txt)		# 使用这种方法不用创建独立文件夹 比add好用
#add_subdirectory(${NET_DIR}/linux network)		# 添加CMakeLists.txt文件 生成的内容放在log路径下
##=================================================================================================#


##=================================================================================================#
## 订阅模块 静态链接
set(SUB_DIR ${SRC_DIR}/core/subscriber)			# 订阅模块cmake
include(${SUB_DIR}/linux/CMakeLists.txt)		
##=================================================================================================#


##=================================================================================================#
## 消息管理模块 静态链接
set(MSG_MGR_DIR ${SRC_DIR}/core/msg_mgr)			# 消息管理模块cmake
include(${MSG_MGR_DIR}/linux/CMakeLists.txt)		
##=================================================================================================#


##=================================================================================================#
## 内存池模块 静态链接
set(MEM_POOL_DIR ${SRC_DIR}/core/mem_pool)			# 内存池模块cmake
include(${MEM_POOL_DIR}/linux/CMakeLists.txt)		
##=================================================================================================#


##=================================================================================================#
## 逻辑模块 静态链接
set(LOGIC_DIR ${SRC_DIR}/server/logic)			    # 逻辑模块cmake
include(${LOGIC_DIR}/linux/CMakeLists.txt)		
##=================================================================================================#


##=================================================================================================#
## 适配模块 静态链接
set(ADPT_DIR ${SRC_DIR}/server/svr_adpt)			# 适配模块cmake
include(${ADPT_DIR}/linux/CMakeLists.txt)		
##=================================================================================================#


##=================================================================================================#
## zhishang.exe 可执行文件
set(MAIN_DIR ${SRC_DIR}/server/main)			    # 可执行文件cmake
include(${MAIN_DIR}/linux/CMakeLists.txt)		
##=================================================================================================#


