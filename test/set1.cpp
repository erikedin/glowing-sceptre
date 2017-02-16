#include "gtest/gtest.h"

#include "hex.h"
#include "base64.h"

using namespace gs;

TEST(Set1, Challenge1) {
    auto input = HexDecoder().decode("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
    EXPECT_EQ(std::string("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"), 
              Base64Encoder().encode(input));
}