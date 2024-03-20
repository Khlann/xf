cmake_minimum_required(VERSION 3.16.0)

project(cnshe_robot_xiaohai)

set(target cnshe_robot_xiaohai.out)

add_definitions("-Wall -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu/")

add_definitions("-std=c++11")

file(GLOB_RECURSE
    FOLLOW_SYMLINKS
)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/LLog)
include_directories(${PROJECT_SOURCE_DIR}/src/common/work_base)
include_directories(${PROJECT_SOURCE_DIR}/src/robots/xiaohai_robot)
include_directories(${PROJECT_SOURCE_DIR}/src/common/tcp_client)

aux_source_directory(${PROJECT_SOURCE_DIR} DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/LLog DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/common/work_base DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/robots/xiaohai_robot DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/common/tcp_client DIR_SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(${target} ${DIR_SRCS})

target_link_libraries(${target} pthread)