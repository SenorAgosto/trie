#pragma once 

namespace trie { namespace traits {

    // use when our input values will be values 0 - 9
    struct digits
    {
        typedef std::uint8_t KeyType;
        enum { size = 10 };
        
        inline std::size_t map(const KeyType key) const { return key; }
    };
    
    // use when our input values will be character digits '0'-'9'
    struct char_digits
    {
        typedef char KeyType;
        enum { size = 10 };
        
        inline std::size_t map(const KeyType key) const { return key ^ '0'; }
    };
    
    // use when our input values will be ASCII characters
    struct alpha_numeric
    {
        typedef char KeyType;
        enum { size = 256 };
        
        inline std::size_t map(const KeyType key) const { return key; }
    };
    
}}
