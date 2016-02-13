#pragma once 

#include <cstddef> 
#include <limits>
#include <type_traits>

#include <trie/details/NumBlocks.hpp>
#include <trie/traits/Traits.hpp>

namespace trie {

    // A fixed-size Trie
    template<typename Value, std::size_t KeyLength, typename KeyTraits=traits::char_digits>
    class Trie
    {
    public:
        typedef typename KeyTraits::KeyType KeyType;
        
        static const std::size_t KeySize = KeyTraits::size;
        static const std::size_t npos = std::numeric_limits<KeyType>::max();
        
        Trie(const Value& value = Value());

        void insert(const KeyType (& key)[KeyLength], const Value& value);
        void insert(const char * key, const Value& value);
        
        Value& operator[](const KeyType (& key)[KeyLength]);
        const Value& operator[](const KeyType (& key)[KeyLength]) const;

        Value& operator[](const char * key);
        const Value& operator[](const char * key) const;

    private:
        std::size_t index(const KeyType* key) const;
        
    private:
        static const std::size_t size = details::NumBlocks<KeySize, KeyLength>::value * KeySize;
        Value trie_[size];
    };


    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    Trie<Value, KeyLength, KeyTraits>::Trie(const Value& value)
    {
        for(std::size_t i = 0; i < size; ++i)
        {
            trie_[i] = value;
        }
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    void Trie<Value, KeyLength, KeyTraits>::insert(const KeyType (&key)[KeyLength], const Value& value)
    {
        const std::size_t spot = index(key);
        trie_[spot] = value;
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    void Trie<Value, KeyLength, KeyTraits>::insert(const char* key, const Value& value)
    {
        const std::size_t spot = index(key);
        trie_[spot] = value;
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    Value& Trie<Value, KeyLength, KeyTraits>::operator[](const KeyType (& key)[KeyLength])
    {
        const std::size_t spot = index(key);
        return trie_[spot];
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    const Value& Trie<Value, KeyLength, KeyTraits>::operator[](const KeyType (& key)[KeyLength]) const
    {
        const std::size_t spot = index(key);
        return trie_[spot];
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    Value& Trie<Value, KeyLength, KeyTraits>::operator[](const char * key)
    {
        const std::size_t spot = index(key);
        return trie_[spot];
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    const Value& Trie<Value, KeyLength, KeyTraits>::operator[](const char * key) const
    {
        const std::size_t spot = index(key);
        return trie_[spot];
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    std::size_t Trie<Value, KeyLength, KeyTraits>::index(const KeyType* key) const
    {
        // TODO: implement
        (void)key;
        return 0;
    }

    
}
