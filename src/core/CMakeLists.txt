project(pbrt)

set(CORE_SOURCE_FILES
        math/vector.cpp
        multi-thread/thread_pool.cpp)

add_library(core ${CORE_SOURCE_FILES})