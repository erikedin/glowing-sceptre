#include "gtest/gtest.h"

#include "primitive.h"

using namespace gs;

TEST(Primitive, InvalidXorArray) {
    EXPECT_THROW(xor_array(bytevector {}, bytevector { 0x00 }), std::invalid_argument);
    EXPECT_THROW(xor_array(bytevector { 0x00 }, bytevector {}), std::invalid_argument);
    EXPECT_THROW(xor_array(bytevector { 0x00 }, bytevector { 0x00, 0x01 }), std::invalid_argument);
    EXPECT_THROW(xor_array(bytevector { 0x00, 0x01 }, bytevector { 0x00 }), std::invalid_argument);
}

TEST(Primitive, XorArray) {
    bytevector v1 = bytevector { 0x00, 0x01, 0x02 };
    bytevector v2 = bytevector { 0x10, 0x01, 0x20 };
    bytevector r  = bytevector { 0x10, 0x00, 0x22 };
    EXPECT_EQ(r, xor_array(v1, v2));
}

TEST(Primitive, HammingDistance_EqualArrays_DistanceZero) {
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    EXPECT_EQ(0, hammingDistance(a, a));
}

TEST(Primitive, HammingDistance_OneElementMismatch_DistanceOne) {
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    std::array<int, 5> b = {1, 2, 3, 4, 6};
    EXPECT_EQ(1, hammingDistance(a, b));
}

TEST(Primitive, HammingDistance_EqualIterators_DistanceZero) {
    std::array<int, 5> a = {1, 2, 3, 4, 5};
    std::array<int, 5> b = {1, 2, 3, 4, 5};
    EXPECT_EQ(0, hammingDistance(a.begin(), a.end(), b.begin()));
}
