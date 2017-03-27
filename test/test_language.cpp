#include "gtest/gtest.h"
#include "language.h"
#include "bytevector.h"
#include "primitive.h"

#include <vector>
#include <iterator>
#include <limits>

using namespace gs;

struct IndexSequence {
    char operator()() { return current++; }
    char current = 0;
};

bytevector stringToBytes(const std::string &s) {
    return bytevector(s.begin(), s.end());
}

// The english text, XOR encrypted with any non-zero key will cause its language score to be worse.
TEST(Language, Scoring_EncryptedWithXor_OriginalIsBest) {
    std::string originalText = R"(
      Hereupon Legrand arose, with a grave and stately air, and brought me the beetle
      from a glass case in which it was enclosed. It was a beautiful scarabaeus, and, at
      that time, unknown to naturalistsof course a great prize in a scientific point
      of view. There were two round black spots near one extremity of the back, and a
      long one near the other. The scales were exceedingly hard and glossy, with all the
      appearance of burnished gold. The weight of the insect was very remarkable, and,
      taking all things into consideration, I could hardly blame Jupiter for his opinion
      respecting it.
    )";
    auto originalBytes = stringToBytes(originalText);

    // Generate all keys.
    std::size_t textLength = originalText.size();
    bytevector keys(256);
    std::generate(std::begin(keys), std::end(keys), IndexSequence());

    // Encrypt all texts.
    std::vector<bytevector> encryptedTexts;
    std::transform(keys.begin(), keys.end(), std::back_inserter(encryptedTexts),
        [textLength,&originalBytes](unsigned char c) { return xor_array(originalBytes, bytevector(textLength, c)); });

    // Expect the first, with zero key, to be the best score.
    EXPECT_EQ(encryptedTexts.begin(), findBestLanguageMatch(encryptedTexts.begin(), encryptedTexts.end(), englishLanguage()));
}
