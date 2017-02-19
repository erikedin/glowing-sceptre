#pragma once

#include <vector>

using bytevector = std::vector<unsigned char>;

namespace gs
{
bytevector from(const char *s);
}
