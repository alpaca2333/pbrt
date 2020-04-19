cmake_minimum_required(VERSION 3.15)
project(pbrt)

set(CMAKE_CXX_STANDARD 17)

add_executable(pbrt src/main.cpp)
target_link_libraries(pbrt
        core)

add_subdirectory(src/core)