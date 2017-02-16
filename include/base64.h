#pragma once

#include "types.h"
#include <string>

namespace gs
{
class Base64Encoder
{
public:
    Base64Encoder() = default;
    virtual ~Base64Encoder() = default;

    virtual std::string encode(const bytevector &v) const;
};
}