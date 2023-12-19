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
            explicit NamedType(TypeId data):_data(data){};
            ~NamedType() = default;

            const TypeId& get()
            {
                return _data;
            }

        private:
            TypeId _data;
    };
}