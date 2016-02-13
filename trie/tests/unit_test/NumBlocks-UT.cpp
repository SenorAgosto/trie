#include "./platform/UnitTestSupport.hpp"
#include <trie/details/NumBlocks.hpp>

namespace {

    TEST(verifyNumBlocks)
    {
        CHECK_EQUAL(1U,  (trie::details::NumBlocks<3U, 1U>::value));
        CHECK_EQUAL(3U,  (trie::details::NumBlocks<3U, 2U>::value));
        CHECK_EQUAL(9U,  (trie::details::NumBlocks<3U, 3U>::value));
        CHECK_EQUAL(27U, (trie::details::NumBlocks<3U, 4U>::value));
    }
}
