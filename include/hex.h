#pragma once

#include <string>
#include <stdexcept>

#include "types.h"


namespace gs
{
class decode_exception : public std::runtime_error
{
public:
    explicit decode_exception(const std::string &s);
    explicit decode_exception(const char *s);
};

class HexDecoder
{
public:
    HexDecoder() = default;
    virtual ~HexDecoder() = default;

    virtual bytevector decode(const std::string &s) const;    
};
}