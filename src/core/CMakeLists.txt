project(pbrt)

set(CORE_SOURCE_FILES
        math/vector.cpp)
add_library(core ${CORE_SOURCE_FILES})