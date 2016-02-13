#pragma once 
#include <cstddef>
#include <trie/details/Power.hpp>

namespace trie { namespace details {

    template<std::size_t Size, std::size_t KeyLength>
    struct NumBlocks
    {
        enum { value = Power<Size, KeyLength - 1>::value };
    };
}}
