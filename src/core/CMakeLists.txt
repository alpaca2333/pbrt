project(pbrt)

file(GLOB CORE_SOURCE_FILES 
        *.cpp
        concurrency/*.cpp 
        geometry/*.cpp
        math/*.cpp
        camera/*.cpp
        )

file(GLOB CORE_TEST_FILES
        test/*.cpp
        )

include_directories(
        concurrency
        geometry
        math
        )

add_library(core ${CORE_SOURCE_FILES})
add_executable(test_core ${CORE_SOURCE_FILES} ${CORE_TEST_FILES})

target_link_libraries(core pthread)
target_link_libraries(test_core pthread)