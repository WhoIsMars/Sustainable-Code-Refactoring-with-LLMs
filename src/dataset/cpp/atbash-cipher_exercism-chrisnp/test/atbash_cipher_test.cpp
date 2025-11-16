#include "atbash_cipher.h"
#ifdef EXERCISM_TEST_SUITE
#include <catch2/catch.hpp>
#else
#include "test/catch.hpp"
#endif

TEST_CASE("encode_yes")
{
    REQUIRE("bvh" == atbash_cipher::encode("yes"));
}

#if defined(EXERCISM_RUN_ALL_TESTS)
TEST_CASE("encode_no")
{
    REQUIRE("ml" == atbash_cipher::encode("no"));
}

TEST_CASE("encode_OMG")
{
    REQUIRE("lnt" == atbash_cipher::encode("OMG"));
}

TEST_CASE("encode_spaces")
{
    REQUIRE("lnt" == atbash_cipher::encode("O M G"));
}

TEST_CASE("encode_mindblowingly")
{
    REQUIRE("nrmwy oldrm tob" == atbash_cipher::encode("mindblowingly"));
}

TEST_CASE("encode_numbers")
{
    REQUIRE("gvhgr mt123 gvhgr mt" == atbash_cipher::encode("Testing,1 2 3, testing."));
}

TEST_CASE("encode_deep_thought")
{
    REQUIRE("gifgs rhurx grlm" == atbash_cipher::encode("Truth is fiction."));
}

TEST_CASE("encode_all_the_letters")
{
    REQUIRE("gsvjf rxpyi ldmul cqfnk hlevi gsvoz abwlt" ==
                        atbash_cipher::encode("The quick brown fox jumps over the lazy dog."));
}

TEST_CASE("decode_exercism")
{
    REQUIRE("exercism" == atbash_cipher::decode("vcvix rhn"));
}

TEST_CASE("decode_a_sentence")
{
    REQUIRE("anobstacleisoftenasteppingstone" ==
                        atbash_cipher::decode("zmlyh gzxov rhlug vmzhg vkkrm thglm v"));
}

TEST_CASE("decode_numbers")
{
    REQUIRE("testing123testing" == atbash_cipher::decode("gvhgr mt123 gvhgr mt"));
}

TEST_CASE("decode_all_the_letters")
{
    REQUIRE("thequickbrownfoxjumpsoverthelazydog" ==
                        atbash_cipher::decode("gsvjf rxpyi ldmul cqfnk hlevi gsvoz abwlt"));
}

TEST_CASE("encode_numbers_only")
{
    REQUIRE("12345 67890 98765 4321" == atbash_cipher::encode("123,456,789,0! 98.765 4,321"));
}

TEST_CASE("decode_numbers_only")
{
    REQUIRE("1234567890987654321" == atbash_cipher::decode("12345 67890 98765 4321"));
}

TEST_CASE("non-alphanumeric_character_in_a_ciphertext_is_an_error") 
{
    REQUIRE_THROWS_AS(
        atbash_cipher::decode("gsvjf rxpyi ldm!l c;fnk hlevi gsvoz abwlt"), 
        std::domain_error
    );
}
#endif
