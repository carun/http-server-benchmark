# mkdir build; cd build; cmake -G Ninja ..
project(biometrics-service)
cmake_minimum_required(VERSION 3.5.1)

cmake_policy(SET CMP0015 NEW)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Export compilation data-base
add_custom_target(fetch_packages)

# Open source libraries
find_package(Poco REQUIRED Foundation Util Net Crypto NetSSL)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
include(FetchContent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_subdirectory(src)
