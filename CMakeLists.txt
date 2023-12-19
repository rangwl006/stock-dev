cmake_minimum_required(VERSION 3.26)
project(stock_dev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/get_cpm.cmake)

CPMAddPackage("gh:google/googletest#v1.14.0")
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

CPMAddPackage("gh:libcpr/cpr#1.10.5")

#find_package(CURL REQUIRED)
#add_executable (curl-demo convert.cpp)
#include_directories(${CURL_INCLUDE_DIR})
#target_link_libraries(curl-demo ${CURL_LIBRARIES})
add_subdirectory(test)

add_library(api_utils INTERFACE)
target_include_directories(api_utils INTERFACE ${CMAKE_SOURCE_DIR}/inc/utils)
add_library(curl_wrapper INTERFACE)
target_include_directories(curl_wrapper INTERFACE ${CMAKE_SOURCE_DIR}/inc/curl_wrappper)
target_link_libraries(curl_wrapper
        INTERFACE
        CURL::libcurl)
add_library(request_builder INTERFACE)
target_include_directories(request_builder
        INTERFACE
        ${CMAKE_SOURCE_DIR}/inc/request_builder)
target_link_libraries(request_builder
        INTERFACE
        api_utils)

add_subdirectory(src)
