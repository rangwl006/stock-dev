#pragma once

#include <type_traits>

namespace utils
{
    template<typename TypeId_, typename ParameterName_>
    class NamedType final
    {
        public:
            using TypeId = TypeId_;

            explicit NamedType() = default;
            explicit NamedType(TypeId data):m_data(data){};
            ~NamedType() = default;

            TypeId& get() const
            {
                return m_data;
            }
        private:
            TypeId m_data;
    };
}