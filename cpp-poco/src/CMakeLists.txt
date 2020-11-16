aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_LIST)
if(CMAKE_VERBOSE)
    message (STATUS "Sources: ${SRC_LIST}")
endif()

include_directories(SYSTEM ${Poco_INCLUDE_DIRS})

link_directories(${Poco_LIBRARIES})

add_executable(poco-http-perf ${SRC_LIST})

target_link_libraries(poco-http-perf ${Poco_LIBRARIES})

if(ENABLE_COVERAGE)
    FetchContent_Declare(
        codecoverage
        GIT_REPOSITORY https://github.com/RWTH-HPC/CMake-codecov
        GIT_TAG        master
        )
    FetchContent_Populate(codecoverage)
    FetchContent_MakeAvailable(codecoverage)

    set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/_deps/codecoverage-src/cmake" ${CMAKE_MODULE_PATH})
    find_package(codecov)
    add_coverage(poco-http-perf)
endif()

