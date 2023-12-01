cmake_minimum_required(VERSION 3.26)
project(stock_dev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/get_cpm.cmake)

CPMAddPackage("gh:google/googletest#v1.14.0")
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

#add_subdirectory(src)
add_subdirectory(test)
