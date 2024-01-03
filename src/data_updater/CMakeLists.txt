add_library(data_updater STATIC data_updater.cpp)
target_link_libraries(data_updater PUBLIC cpr::cpr request_builder)
target_include_directories(data_updater PUBLIC
                                        ${CMAKE_SOURCE_DIR}/inc
                                        curl_wrapper
                                        api_utils
                                        )