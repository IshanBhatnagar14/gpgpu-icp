# cmake
cmake_minimum_required(VERSION 2.8)

# project
set(TARGET_NAME gpgpu-icp)
project(${TARGET_NAME})

# compilations
set(CMAKE_CXX_COMPILER "nvcc")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_STANDARD 17)

# sources
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)
add_executable(${TARGET_NAME}
    cpu_src/main.cc
    cpu_src/log.cc
    cpu_src/points.cc
    cpu_src/matrix.cc
    cpu_src/alignment.cc
    cpu_src/icp.cc
)

# libs
#find_package (Eigen3 3.3 REQUIRED NO_MODULE)
#target_link_libraries(${TARGET_NAME} m Eigen3::Eigen)
