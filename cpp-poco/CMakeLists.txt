# mkdir build; cd build; cmake -G Ninja -D CMAKE_BUILD_TYPE=RelWithDbg -DNEOFACE_SECRET_KEY=0 -DNFV3_VERSION=3.1.3.0-cbp -DENABLE_LICENSE=ON ..
project(biometrics-service)
cmake_minimum_required(VERSION 3.5.1)

cmake_policy(SET CMP0015 NEW)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Export compilation data-base
add_custom_target(fetch_packages)

# Open source libraries
find_package(Poco REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_subdirectory(src)
