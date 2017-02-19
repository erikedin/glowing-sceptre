#include "gtest/gtest.h"

#include <array>
#include <utility>

#include "hex.h"

using namespace gs;

static const std::array<std::string, 4> INVALID_HEX_INPUT = {
    // Invalid length (odd)
    "0",
    "aaa",
    "aaaaa",

    // Invalid character
    "0z",
};

static const std::array<std::pair<std::string, bytevector>, 7> HEX_DECODING = {
    std::pair<std::string, bytevector> {"",        { }},
    {"00",      { 0x00 }},
    {"0011",    { 0x00, 0x11 }},
    {"001122",  { 0x00, 0x11, 0x22 }},
    {"00AB",    { 0x00, 0xAB }},
    {"00ab",    { 0x00, 0xAB }},
    {"00abCd",  { 0x00, 0xAB, 0xCD }}
};

TEST(HexDecoderTest, InvalidArguments)
{
    for (const auto &h: INVALID_HEX_INPUT)
    {
        EXPECT_THROW(HexDecoder().decode(h), gs::decode_exception);
    }
}

TEST(HexDecoderTest, Valid)
{
    for (const auto &h: HEX_DECODING)
    {
        EXPECT_EQ(h.second, HexDecoder().decode(std::string(h.first)));
    }
}