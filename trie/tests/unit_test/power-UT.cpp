#include "./platform/UnitTestSupport.hpp"
#include <trie/details/Power.hpp>

namespace {

    TEST(verifyPowerTemplateMetaProgram)
    {
        CHECK_EQUAL(1U,  (trie::details::Power<3, 0>::value));
        CHECK_EQUAL(3U,  (trie::details::Power<3, 1>::value));
        CHECK_EQUAL(9U,  (trie::details::Power<3, 2>::value));
        CHECK_EQUAL(27U, (trie::details::Power<3, 3>::value));
        CHECK_EQUAL(81U, (trie::details::Power<3, 4>::value));
    }
}
