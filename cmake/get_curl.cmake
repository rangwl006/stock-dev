CPMAddPackage("gh:curl/curl#curl-8_4_0")
set(CURL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/cmake_build_debug/_deps/curl-src/include")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})