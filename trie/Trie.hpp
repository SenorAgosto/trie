#pragma once 

#include <cstddef> 
#include <limits>
#include <type_traits>

#include <trie/details/NumBlocks.hpp>
#include <trie/traits/Traits.hpp>

namespace trie {
    
    // A fixed-size Trie
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    class TrieBase
    {
    public:
        typedef typename KeyTraits::KeyType KeyType;
        static const std::size_t KeySize = KeyTraits::size;
        
        TrieBase(const Value& value = Value());

        void insert(const KeyType (& key)[KeyLength], const Value& value);
        
        Value& operator[](const KeyType (& key)[KeyLength]);
        const Value& operator[](const KeyType (& key)[KeyLength]) const;

        void reset(const Value& value = Value());
        
    protected:
        std::size_t index(const KeyType* key, const std::size_t keyLength = KeyLength) const;
        
    protected:
        std::size_t levelOffset_[KeyLength];
    
        static const std::size_t size = details::NumBlocks<KeySize, KeyLength>::value * KeySize;
        Value trie_[size];
    };


    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    TrieBase<Value, KeyLength, KeyTraits>::TrieBase(const Value& value)
    {
        reset(value);
        
        static_assert(KeyLength >= 2, "A keysize of one doesn't make sense, use an array.");
        
        levelOffset_[0] = 0;
        levelOffset_[1] = KeySize;
        
        for(std::size_t i = 2; i < KeyLength; ++i)
        {
            levelOffset_[i] = ((levelOffset_[i - 1] - levelOffset_[i -2]) * KeySize) + levelOffset_[i - 1];
        }
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    void TrieBase<Value, KeyLength, KeyTraits>::insert(const KeyType (&key)[KeyLength], const Value& value)
    {
        const std::size_t spot = index(key);
        trie_[spot] = value;
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    Value& TrieBase<Value, KeyLength, KeyTraits>::operator[](const KeyType (& key)[KeyLength])
    {
        const std::size_t spot = index(key);
        return trie_[spot];
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    const Value& TrieBase<Value, KeyLength, KeyTraits>::operator[](const KeyType (& key)[KeyLength]) const
    {
        const std::size_t spot = index(key);
        return trie_[spot];
    }


    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    void TrieBase<Value, KeyLength, KeyTraits>::reset(const Value& value)
    {
        for(std::size_t i = 0; i < size; ++i)
        {
            trie_[i] = value;
        }
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    std::size_t TrieBase<Value, KeyLength, KeyTraits>::index(const KeyType* key, const std::size_t keyLength) const
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

    // This would be easier with enable if perhaps, but I want to support some older compilers that
    // don't have it.
    template<typename Value, std::size_t KeyLength, typename KeyTraits=traits::char_digits, bool EnableCharPtrInterface = std::is_same<KeyTraits, traits::char_digits>::value>
    class Trie : public TrieBase<Value, KeyLength, KeyTraits>
    {
    public:
        typedef TrieBase<Value, KeyLength, KeyTraits> base_t;
        
        Trie(const Value& value = Value())
            : base_t(value)
        {
        }
    };
    
    // A partial specialization in effect when the KeyTraits=traits::char_digits
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    class Trie<Value, KeyLength, KeyTraits, true>
        : public TrieBase<Value, KeyLength, KeyTraits>
    {
    public:
        typedef TrieBase<Value, KeyLength, KeyTraits> base_t;
        
        Trie(const Value& value = Value())
            : base_t(value)
        {
        }

        // NOTE: if length > KeyLength, extra chars will be *silently* ignored.
        void insert_charptr(const char* key, const std::size_t length, const Value& value);
        
        Value& find(const char* key, const std::size_t length);
        const Value& find(const char* key, const std::size_t length) const;
    };
    
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    void Trie<Value, KeyLength, KeyTraits, true>::insert_charptr(const char* key, const std::size_t length, const Value& value)
    {
        const std::size_t spot = this->index(key, length);
        this->trie_[spot] = value;
    }

    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    Value& Trie<Value, KeyLength, KeyTraits, true>::find(const char * key, const std::size_t length)
    {
        const std::size_t spot = this->index(key, length);
        return this->trie_[spot];
    }
    
    template<typename Value, std::size_t KeyLength, typename KeyTraits>
    const Value& Trie<Value, KeyLength, KeyTraits, true>::find(const char * key, const std::size_t length) const
    {
        const std::size_t spot = this->index(key, length);
        return this->trie_[spot];
    }
}
