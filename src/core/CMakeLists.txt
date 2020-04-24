project(pbrt)

set(CORE_SOURCE_FILES
        math/vector3.cpp
        concurrency/thread_pool.cpp
        math/matrix.cpp)

add_library(core ${CORE_SOURCE_FILES})