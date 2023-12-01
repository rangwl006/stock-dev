#pragma once
//#define ENABLE_DEBUG_LOGGING
#ifdef ENABLE_DEBUG_LOGGING
#include <iostream>

template<typename First>
void print(First string)
{
    std::cout << string << " ";
}

template <typename First, typename ... Last>
void print(First head, Last ... tail)
{
    print(head);
    print(tail...);
};
#define DEBUG_LOG(...) print(__VA_ARGS__)
#else
#define DEBUG_LOG(...)
#endif