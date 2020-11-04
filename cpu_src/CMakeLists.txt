# cmake
cmake_minimum_required(VERSION 2.8)

# project
set(TARGET_NAME cpu-icp)
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
    main.cc
    log.cc
    points.cc
    matrix.cc
    alignment.cc
    icp.cc
)
