#include "./platform/UnitTestSupport.hpp"

#include <trie/Trie.hpp>
#include <trie/traits/Traits.hpp>

namespace {

    struct TrieFixture
    {
        typedef std::size_t ValueType;
        static const std::size_t keyLength = 4;
        
        typedef trie::traits::digits TrieTraits;
        typedef trie::Trie<ValueType, keyLength, TrieTraits> Trie;
        Trie trie;
    };
    
    TEST_FIXTURE(TrieFixture, verifyDefaultConstructor)
    {
    }

    TEST(verifyDefaultConstructorWithParameter)
    {
        static const std::size_t keyLength = 4;
        trie::Trie<std::size_t, keyLength, trie::traits::digits> trie(10);
    }

    TEST(verifyDefaultConstructorWithDefaultKeyTraits)
    {
        static const std::size_t keyLength = 4;
        trie::Trie<std::size_t, keyLength> trie;
    }

    TEST(verifyDefaultConstructorWithParameterDefaultKeyTraits)
    {
        static const std::size_t keyLength = 4;
        trie::Trie<std::size_t, keyLength> trie(11);
    }

    TEST_FIXTURE(TrieFixture, verifyInsertCanBeCalled)
    {
        trie::traits::digits::KeyType key[keyLength] = { 0, 1, 1, 5 };
        trie.insert(key, 100);
    }

    TEST_FIXTURE(TrieFixture, verifyBracketOperatorCanBeCalled)
    {
        TrieTraits::KeyType key[keyLength] = { 0, 0, 0, 0};
        trie.insert(key, 100);
        
        ValueType& value = trie[key];
        CHECK_EQUAL(100U, value);
    }
    
    TEST_FIXTURE(TrieFixture, verifyConstBracketOperatorCanBeCalled)
    {
        TrieTraits::KeyType key[keyLength] = { 0, 1, 1, 1 };
        trie.insert(key, 100);
        
        const Trie& constTrie = trie;
        const ValueType& value = constTrie[key];
        
        CHECK_EQUAL(100U, value);
    }
    
    struct TrieFixtureCharDigitsKey
    {
        typedef std::uint32_t ValueType;
        static const std::size_t keyLength = 4;
        
        typedef trie::traits::char_digits TrieTraits;
        typedef trie::Trie<ValueType, keyLength, TrieTraits> Trie;
        Trie trie;
    };

    TEST_FIXTURE(TrieFixtureCharDigitsKey, verifyInsertWithCharArray)
    {
        char key[] = "123";
        trie.insert(key, 10);
    }
    
    TEST_FIXTURE(TrieFixtureCharDigitsKey, verifyInsertWithCharPtrCanBeCalled)
    {
        const char* key = "123";
        trie.insert(key, 10);
    }
    
    TEST_FIXTURE(TrieFixtureCharDigitsKey, verifyCharDigitsTrieBracketOperatorCanBeCalled)
    {
        TrieTraits::KeyType key[] = "123";
        trie.insert(key, 100);
        
        ValueType& value = trie[key];
        CHECK_EQUAL(100U, value);
    }
    
    TEST_FIXTURE(TrieFixtureCharDigitsKey, verifyCharDigitsTrieConstBracketOperatorCanBeCalled)
    {
        TrieTraits::KeyType key[] = "123";
        trie.insert(key, 100);
        
        const Trie& constTrie = trie;
        const ValueType& value = constTrie[key];
        
        CHECK_EQUAL(100U, value);
    }

    TEST_FIXTURE(TrieFixtureCharDigitsKey, verifyCharDigitsTrieBracketOperatorCanBeCalledWithCharPtrKey)
    {
        const char* key = "123";
        trie.insert(key, 100);
        
        ValueType& value = trie[key];
        CHECK_EQUAL(100U, value);
    }
    
    TEST_FIXTURE(TrieFixtureCharDigitsKey, verifyCharDigitsTrieConstBracketOperatorCanBeCalledWithCharPtrKey)
    {
        const char* key = "123";
        trie.insert(key, 100);
        
        const Trie& constTrie = trie;
        const ValueType& value = constTrie[key];
        
        CHECK_EQUAL(100U, value);
    }
    
}
