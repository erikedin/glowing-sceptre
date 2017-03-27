#pragma once

#include <string>
#include <functional>
#include <algorithm>

namespace
{

}

namespace gs
{
class Language
{
public:
};

Language englishLanguage();

double languageMatchScore(const bytevector &s, const Language &language);

template <typename T>
T findBestLanguageMatch(T begin, T end, const Language &language)
{
    auto scorer = [&language](auto s) { return languageMatchScore(s, language); };
    // TODO: Return the iterator with the minimum score.
}
}
