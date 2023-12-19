#pragma once

#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

namespace utils
{
    template<typename Key_, typename Value_>
    class insertion_order_map
    {
        using Key = Key_;
        using Value = Value_;
        using KeystoreType = std::vector<Key>;
        using ValuestoreType  = std::map<Key, Value>;
        using Iterator = typename KeystoreType::iterator;
        using ValuestoreIterator = typename ValuestoreType::iterator;

    public:
        insertion_order_map() = default;
        insertion_order_map(std::initializer_list<std::pair<Key, Value>> list)
        {
            for (const auto& [key, val] : list)
            {
                insert(key, val);
            }
        }
        ~insertion_order_map() = default;

        void insert(Key key, Value val)
        {
            if (auto it = m_map.find(key); it == m_map.end())
            {
                m_keys.push_back(key);
                m_map[key] = val;
            }
        }

        void remove(Key key)
        {
            if (auto it_keys = std::find(m_keys.begin(), m_keys.end(), key); it_keys != m_keys.end())
            {
                m_keys.erase(it_keys);
            }
            if (auto it_map = m_map.find(key); it_map != m_map.end())
            {
                m_map.erase(it_map);
            }
        }

        unsigned int size() const
        {
            return m_keys.size();
        }

        Iterator begin()
        {
            return m_keys.begin();
        }

        Iterator end()
        {
            return m_keys.end();
        }

        ValuestoreType::mapped_type& operator[](Key i)
        {
            return m_map[i];
        }

        void display() const
        {
            for(auto it = m_keys.begin(); it != m_keys.end(); ++it)
            {
                std::cout << *it << " : " << m_map[*it] << "\n";
            }
        }

    private:
        KeystoreType m_keys;
        ValuestoreType m_map;
    };
}