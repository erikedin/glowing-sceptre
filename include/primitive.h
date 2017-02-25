#pragma once

#include <stdexcept>
#include <algorithm>

#include "bytevector.h"

namespace gs
{
bytevector xor_array(const bytevector& v1, const bytevector& v2);

template <typename It>
std::size_t hammingDistance(It leftBegin, It leftEnd, It rightBegin)
{
    return std::inner_product(leftBegin, leftEnd, rightBegin, 0,
        std::plus<std::size_t>(), [](auto x, auto y) { return x == y ? 0 : 1; });
}

template <typename T>
std::size_t hammingDistance(T left, T right)
{
    return hammingDistance(std::begin(left), std::end(left),
                           std::begin(right));
}
}
