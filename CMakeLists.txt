cmake_minimum_required(VERSION 3.10)
project(pbrt)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
)

add_executable(pbrt src/main.cpp)
target_link_libraries(pbrt
    core)

add_subdirectory(src/core)
