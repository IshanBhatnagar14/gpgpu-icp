# cmake
cmake_minimum_required(VERSION 2.8)
project(cmake_and_cuda LANGUAGES CXX CUDA)

# project
set(TARGET_NAME gpu-icp)
# project(${TARGET_NAME})

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
    main.cu
    log.cu
    points.cu
    matrix.cu
    alignment.cu
    icp.cu
)
