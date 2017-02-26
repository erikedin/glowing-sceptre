#include "gtest/gtest.h"
#include "language.h"

#include <vector>
#include <iterator>
#include <limits>

using namespace gs;

std::string bitError(const std::string &s, int bit)
{
  std::string result;
  result.resize(s.size());

  std::transform(s.begin(), s.end(), result.begin(),
    [bit](const char c){ return c ^ (1 << bit); });

  return result;
}

// Each single bit error introduced into an english text will cause its
// language score to be worse.
TEST(Language, Scoring_SingleBitManipulation_OriginalIsBest) {
    std::string englishText = R"(
      Hereupon Legrand arose, with a grave and stately air, and brought me the beetle
      from a glass case in which it was enclosed. It was a beautiful scarabaeus, and, at
      that time, unknown to naturalistsof course a great prize in a scientific point
      of view. There were two round black spots near one extremity of the back, and a
      long one near the other. The scales were exceedingly hard and glossy, with all the
      appearance of burnished gold. The weight of the insect was very remarkable, and,
      taking all things into consideration, I could hardly blame Jupiter for his opinion
      respecting it.
  )";

    std::vector<std::string> stringsWithBitFlips;
    std::array<int, 8> bits = { 0, 1, 2, 3, 4, 5, 6, 7 };
    stringsWithBitFlips.resize(bits.size());

    std::transform(bits.cbegin(), bits.cend(), stringsWithBitFlips.begin(),
      [&](int shift) { return bitError(englishText, shift); });

    // Introduce the actual english text as the last element.
    auto expected = stringsWithBitFlips.insert(stringsWithBitFlips.end(), englishText);

    auto english = englishLanguage();
    auto actual = findBestLanguageMatch(stringsWithBitFlips.cbegin(), stringsWithBitFlips.cend(), english);

    EXPECT_EQ(expected, actual);
}

TEST(Language, Scoring_NotEnoughCharacters_MaxSizeT) {
    std::string shortText = "abcdef";
    EXPECT_EQ(std::numeric_limits<std::size_t>::max(), languageMatchScore(shortText, englishLanguage()));
}
