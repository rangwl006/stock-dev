add_executable(test_insertion_order_map test_insertion_order_map.cpp
        ../../inc/twelvedata/ApiData.h
        ../../inc/utils/strong_types.h)
target_include_directories(test_insertion_order_map PUBLIC ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(test_insertion_order_map PUBLIC gtest GTest::gtest_main)