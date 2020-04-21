project(pbrt)

set(CORE_SOURCE_FILES
        math/vec3.cpp
        multi-thread/thread_pool.cpp)

add_library(core ${CORE_SOURCE_FILES})