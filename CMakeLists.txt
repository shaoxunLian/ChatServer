#要求Cmake的最低版本
cmake_minimum_required(VERSION 3.0)
#这个工程的名字叫main，不是可执行文件的名字
project(chat)

#配置编译选项（下面括号里面表示在CMAKE_CXX_FLAGS变量的基础上再加一个-g的选项）
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#配置最终的头文件的可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)


#指定搜索的子目录
add_subdirectory(src)