project(pbrt)

set(CORE_SOURCE_FILES
        concurrency/thread_pool.cpp
        math/vector.cpp
        math/matrix.cpp
        math/quaternion3.cpp)

add_library(core ${CORE_SOURCE_FILES})