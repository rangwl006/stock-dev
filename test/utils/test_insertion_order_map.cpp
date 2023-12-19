#include <gtest/gtest.h>

#include "utils/insertion_order_map.h"

TEST(InsertionOrderMapTestSuite, InitializeMap)
{
    utils::insertion_order_map<std::string, std::string> map;
    EXPECT_NO_THROW(map);
}

TEST(InsertionOrderMapTestSuite, AddElementToMap)
{
    utils::insertion_order_map<std::string, std::string> map;
    EXPECT_NO_THROW(map.insert("Hello", "World"));
    EXPECT_EQ(map.size(), 1);
}

TEST(InsertionOrderMapTestSuite, RemoveElementFromMap)
{
    utils::insertion_order_map<std::string, std::string> map;
    EXPECT_NO_THROW(map.insert("Hello", "World"));
    map.remove("Hello");
    EXPECT_EQ(map.size(), 0);
}

TEST(InsertionOrderMapTestSuite, InitializeMapWithInitializerList)
{
    utils::insertion_order_map<std::string, std::string> map =
    {
            {"test", "suite"},
            {"hello", "world"}
    };

    EXPECT_EQ(map.size(), 2);
}