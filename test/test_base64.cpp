#include "gtest/gtest.h"
#include "base64.h"

using namespace gs;

TEST(Base64EncoderTest, testVectors)
{
    EXPECT_EQ("", Base64Encoder().encode(from("")));
    EXPECT_EQ("Zg==", Base64Encoder().encode(from("f")));
    EXPECT_EQ("Zm8=", Base64Encoder().encode(from("fo")));
    EXPECT_EQ("Zm9v", Base64Encoder().encode(from("foo")));
    EXPECT_EQ("Zm9vYg==", Base64Encoder().encode(from("foob")));
    EXPECT_EQ("Zm9vYmE=", Base64Encoder().encode(from("fooba")));
    EXPECT_EQ("Zm9vYmFy", Base64Encoder().encode(from("foobar")));
}

TEST(Base64EncoderTest, WikiTest)
{
    auto quote = 
        "Man is distinguished, not only by his reason, but by this singular passion from "
        "other animals, which is a lust of the mind, that by a perseverance of delight "
        "in the continued and indefatigable generation of knowledge, exceeds the short "
        "vehemence of any carnal pleasure.";

    std::string encoded = 
        "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz"
        "IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg"
        "dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu"
        "dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"
        "ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";    
    
    EXPECT_EQ(encoded, Base64Encoder().encode(from(quote)));
}