#include "language.h"

#include <iterator>
#include <unordered_map>
#include <limits>

#include <iostream>

#include "primitive.h"

using namespace gs;

Language::Language(const std::string &mostFrequentCharacters) :
    m_mostFrequentCharacters(mostFrequentCharacters)
{

}

Language gs::englishLanguage()
{
    return Language("etaoinshrdlu");
}

namespace
{
class LetterFrequency
{
public:
    LetterFrequency &operator+(char c);

    std::string mostCommon(std::size_t n);

private: // Members
    std::unordered_map<char, std::size_t> m_frequencies;
};

LetterFrequency &
LetterFrequency::operator+(char c)
{
    // Ignore non-alpha characters.
    // Lowercase all characters.
    if (std::isalpha(c))
    {
        char normalized = std::tolower(c);
        m_frequencies[normalized]++;
    }
    return *this;
}

std::string
LetterFrequency::mostCommon(std::size_t n)
{
    // Get all keys from the m_frequencies map. That is, a list of all chars
    // occuring in the text.
    std::string letters;
    std::transform(m_frequencies.begin(), m_frequencies.end(),
        std::back_inserter(letters),
        [](auto p) { return p.first; });

    // Sort the characters by frequency. Note that we're sorting them so that
    // the highest frequencies are first.
    auto cmp = [this](char a, char b) { return m_frequencies[a] > m_frequencies[b]; };
    std::sort(letters.begin(), letters.end(), cmp);

    // Return at most the first n letters.
    return letters.substr(0, n);
}
}

std::size_t gs::languageMatchScore(const std::string &s, const Language &lang)
{
    // Calculate letter frequencies from string s.
    LetterFrequency frequency = std::accumulate(s.begin(), s.end(), LetterFrequency());

    // Validate that we have enough characters to score.
    auto expectedMostCommon = lang.mostFrequentCharacters();
    std::string mostCommon = frequency.mostCommon(expectedMostCommon.size());

    if (mostCommon.size() != expectedMostCommon.size())
    {
        return std::numeric_limits<std::size_t>::max();
    }

    // Calculate the score as the Hamming distance between the two strings containing
    // the most frequent characters.
    auto distance = hammingDistance(mostCommon.begin(), mostCommon.end(), expectedMostCommon.begin());

    std::cout << "Most common: " << mostCommon << std::endl;
    std::cout << "\tDistance: " << distance << std::endl;
    std::cout << std::endl;

    return distance;
}
