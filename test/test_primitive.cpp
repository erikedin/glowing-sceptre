#include "gtest/gtest.h"

#include "primitive.h"

using namespace gs;

TEST(PrimitiveTest, InvalidXorArray)
{
    EXPECT_THROW(xor_array(bytevector {}, bytevector { 0x00 }), std::invalid_argument);
    EXPECT_THROW(xor_array(bytevector { 0x00 }, bytevector {}), std::invalid_argument);
    EXPECT_THROW(xor_array(bytevector { 0x00 }, bytevector { 0x00, 0x01 }), std::invalid_argument);
    EXPECT_THROW(xor_array(bytevector { 0x00, 0x01 }, bytevector { 0x00 }), std::invalid_argument);
}

TEST(PrimitiveTest, XorArray)
{
    bytevector v1 = bytevector { 0x00, 0x01, 0x02 };
    bytevector v2 = bytevector { 0x10, 0x01, 0x20 };
    bytevector r  = bytevector { 0x10, 0x00, 0x22 };
    EXPECT_EQ(r, xor_array(v1, v2));
}