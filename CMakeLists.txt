cmake_minimum_required(VERSION 3.16.0)

project(cnshe_robot_xiaohai)

set(target cnshe_robot_xiaohai.out)

add_definitions("-Wall")

link_directories(/usr/local/lib)
link_directories(/usr/lib/x86_64-linux-gnu)

add_definitions("-std=c++11") 
# add_definitions("-lstdc++")

file(GLOB_RECURSE
    FOLLOW_SYMLINKS
)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/LLog)
include_directories(${PROJECT_SOURCE_DIR}/src/common/ini)
include_directories(${PROJECT_SOURCE_DIR}/src/common/work_base)
include_directories(${PROJECT_SOURCE_DIR}/src/robots/xiaohai_robot)
include_directories(${PROJECT_SOURCE_DIR}/src/common/tcp_client)
include_directories(${PROJECT_SOURCE_DIR}/src/common/udp_client)
include_directories(${PROJECT_SOURCE_DIR}/src/common/serial_communication)
include_directories(${PROJECT_SOURCE_DIR}/src/component/gas_detection)
include_directories(${PROJECT_SOURCE_DIR}/src/component/nuclear_radiation_measuring)
include_directories(${PROJECT_SOURCE_DIR}/src/component/robot_arm_device/dz_robot_arm/include)
include_directories(${PROJECT_SOURCE_DIR}/src/component/robot_arm_device/dz_robot_arm)
include_directories(${PROJECT_SOURCE_DIR}/src/component/chassis_device/yixin_chassis_device)
include_directories(${PROJECT_SOURCE_DIR}/src/component/xf)


aux_source_directory(${PROJECT_SOURCE_DIR} DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/LLog DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/common/ini DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/common/work_base DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/robots/xiaohai_robot DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/common/tcp_client DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/common/udp_client DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/common/serial_communication DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/component/gas_detection DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/component/nuclear_radiation_measuring DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/component/robot_arm_device/dz_robot_arm DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/component/chassis_device/yixin_chassis_device DIR_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/component/xf DIR_SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

link_directories(${PROJECT_SOURCE_DIR}/src/component/robot_arm_device/dz_robot_arm/lib)

add_executable(${target} ${DIR_SRCS})
# target_link_libraries(${target} /usr/local/lib/libHR_Pro.so)
target_link_libraries(${target} msc rt dl pthread asound stdc++ SDL2)
target_link_libraries(${target} HR_Pro)
target_link_libraries(${target} pthread)
target_link_libraries(${target} ${CMAKE_THREAD_LIBS_INIT})

