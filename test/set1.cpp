#include "gtest/gtest.h"

#include "hex.h"
#include "base64.h"
#include "primitive.h"

using namespace gs;

TEST(Set1, Challenge1) 
{
    auto input = HexDecoder().decode("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
    EXPECT_EQ(std::string("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"), 
              Base64Encoder().encode(input));
}

TEST(Set1, Challenge2)
{
    auto h = HexDecoder();
    auto s1 = h.decode("1c0111001f010100061a024b53535009181c");
    auto s2 = h.decode("686974207468652062756c6c277320657965");
    auto expected = h.decode("746865206b696420646f6e277420706c6179");

    EXPECT_EQ(expected, xor_array(s1, s2));
}