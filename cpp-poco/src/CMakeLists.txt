aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_LIST)
if(CMAKE_VERBOSE)
    message (STATUS "Sources: ${SRC_LIST}")
endif()

include_directories(SYSTEM ${Poco_INCLUDE_DIRS})

link_directories(${Poco_LIBRARIES})

add_executable(poco-http-perf ${SRC_LIST})

target_link_libraries(poco-http-perf ${Poco_LIBRARIES})

