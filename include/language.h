#pragma once

#include <string>
#include <functional>
#include <algorithm>

namespace gs
{
class Language
{
public:
    explicit Language(const std::string &mostFrequenceCharacters);

    std::string mostFrequentCharacters() const { return m_mostFrequentCharacters; }

private: // Members
    std::string m_mostFrequentCharacters;
};

Language englishLanguage();

template <typename T>
class LanguageMatchAdapter
{
public:
    explicit LanguageMatchAdapter(T it, std::function<std::size_t (const std::string &)> scorer) :
        m_current(it), m_score(0), m_hasScore(false), m_scorer(scorer) {}

    std::size_t &operator*() {
        if (m_hasScore) return m_score;
        m_hasScore = true;
        m_score = m_scorer(*m_current);
        return m_score;
    }

    LanguageMatchAdapter &operator++() {
        m_current++;
        m_hasScore = false;
        m_score = 0;
        return *this;
    }

    LanguageMatchAdapter operator++(int) {
        LanguageMatchAdapter r = *this;
        m_current++;
        m_hasScore = false;
        m_score = 0;
        return r;
    }

    bool operator==(const LanguageMatchAdapter &other) const { return m_current == other.m_current; }
    bool operator!=(const LanguageMatchAdapter &other) const { return !(*this == other); }

    T getUnderlying() const { return m_current; }

private:
    T m_current;
    std::size_t m_score;
    bool m_hasScore;
    std::function<std::size_t (const std::string &)> m_scorer;
};

std::size_t languageMatchScore(const std::string &s, const Language &language);

template <typename T>
T findBestLanguageMatch(T begin, T end, const Language &language)
{
    auto scorer = [&language](auto s) { return languageMatchScore(s, language); };
    auto scoreBegin = LanguageMatchAdapter<T>(begin, scorer);
    auto scoreEnd = LanguageMatchAdapter<T>(end, scorer);
    return std::min_element(scoreBegin, scoreEnd).getUnderlying();
}
}
