#pragma once

#include <string>

#include "types.h"


namespace gs
{
class HexDecoder
{
public:
    HexDecoder() = default;
    virtual ~HexDecoder() = default;

    virtual bytevector decode(const std::string &s) const;    
};
}