#include "hex.h"

#include <string>
#include <sstream>

using namespace gs;

// TODO: Validate input
// TODO: Better exception
// TODO: Unit tests

namespace
{
unsigned char hex2nibble(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 0xA;
    if (c >= 'A' && c <= 'F') return c - 'A' + 0xA;

    std::ostringstream oss;
    oss << "Invalid nibble '" << c << "'";
    throw decode_exception(oss.str());
}
}

decode_exception::decode_exception(const std::string &s) : std::runtime_error(s) {}
decode_exception::decode_exception(const char *s) : std::runtime_error(s) {}

bytevector
HexDecoder::decode(const std::string &s) const
{
    if (s.size() % 2 != 0)
    {
        std::ostringstream oss;
        oss << "Hex string size must be even, but was " << s.size();
        throw decode_exception(oss.str());
    }
    bytevector v(s.size() / 2);

    for (auto i = 0; i < v.size(); ++i)
    {
        v[i] = hex2nibble(s[2 * i]) << 4 | hex2nibble(s[2 * i + 1]);
    }

    return v;
}