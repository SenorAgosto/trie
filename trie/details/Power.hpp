#pragma once 
#include <cstddef> 

namespace trie { namespace details {

    // Raise base by exponent
    template<std::size_t base, std::size_t exponent>
    struct Power
    {
        enum { value = Power<base, exponent - 1>::value * base };
    };

    template<std::size_t base>
    struct Power<base, 1>
    {
        enum { value = base };
    };
    
    template<std::size_t base>
    struct Power<base, 0>
    {
        enum { value = 1 };
    };

}}
