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
        
        Value& operator[](const KeyType (& key)[KeyLength]);
        const Value& operator[](const KeyType (& key)[KeyLength]) const;

    private:
        std::size_t index(const KeyType* key, const std::size_t keyLength = KeyLength) const;
        
    private:
        std::size_t levelOffset_[KeyLength];
    
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
        
        static_assert(KeyLength >= 2, "A keysize of one doesn't make sense, use an array.");
        
        levelOffset_[0] = 0;
        levelOffset_[1] = KeySize;
        
        for(std::size_t i = 2; i < KeyLength; ++i)
        {
            levelOffset_[i] = ((levelOffset_[i - 1] - levelOffset_[i -2]) * KeySize) + levelOffset_[i - 1];
        }
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    void Trie<Value, KeyLength, KeyTraits>::insert(const KeyType (&key)[KeyLength], const Value& value)
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


/*
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    void Trie<Value, KeyLength, KeyTraits>::insert(const char* key, const Value& value)
    {
        const std::size_t spot = index(key);
        trie_[spot] = value;
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
*/

    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    std::size_t Trie<Value, KeyLength, KeyTraits>::index(const KeyType* key, const std::size_t keyLength) const
    {
        const std::size_t length = std::min(keyLength, KeyLength) - 1;
        std::size_t index = levelOffset_[length];
        
        for(std::size_t i = 0; i < length; ++i)
        {
            index += KeyTraits::map(key[i]) * KeySize;
        }
        
        // last spot in the key doesn't jump us forward.
        index += KeyTraits::map(key[length]);
        return index;
    }
}
