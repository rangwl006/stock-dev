add_library(data_storage STATIC DataStorageInterface.cpp)
target_include_directories(data_storage PUBLIC
                                        ${CMAKE_SOURCE_DIR}/inc
                                        )