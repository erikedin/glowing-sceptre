#include "primitive.h"

#include <algorithm>
#include <functional>

using namespace gs;

bytevector gs::xor_array(const bytevector &v1, const bytevector &v2)
{
    if (v1.size() != v2.size())
    {
        throw std::invalid_argument("Arguments must have same sizes");
    }

    bytevector result;
    result.resize(v1.size());
    std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), result.begin(),
                   std::bit_xor<uint8_t>());

    return result;
}