#pragma once

#include <string>
#include <fstream>

namespace utils
{
    std::string get_api_key(const std::string& key_file)
    {
        std::ifstream file(key_file);
        std::string key;
        std::getline(file, key);
        return key;
    }
}