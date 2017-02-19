#include "bytevector.h"
#include <algorithm>
#include <string>

bytevector
gs::from(const char *s)
{
    size_t len = std::char_traits<char>::length(s);
    bytevector v(len);
    std::copy(&s[0], &s[len], v.begin());
    return v;
}
