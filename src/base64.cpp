#include "base64.h"

#include <algorithm>
#include <array>
#include <functional>

using namespace gs;

template <size_t N, size_t... I>
std::array<char, N - 1> to_array_impl(const char (&a)[N], std::index_sequence<I...>)
{
    return {{a[I]...}};
}

template <size_t N>
std::array<char, N - 1> to_array(const char (&a)[N])
{
    return to_array_impl(a, std::make_index_sequence<N - 1>());
}

static const std::array<char, 65> BASE64_ALPHABET = to_array("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=");

namespace
{
class Base64Emitter
{
public:
    Base64Emitter(const std::array<char, 65> &alphabet,
                  std::function<void (char)> receiver);

    void handle(unsigned char c);

    template <typename T>
    void encode(T&& begin, T&& end);

private: // Functions
    void emit(uint8_t c);
    void pad();

private: // Members
    uint8_t m_state;
    size_t m_bitsInState;
    size_t m_requiredPadding;
    const std::array<char, 65> m_alphabet;
    std::function<void (char)> m_receiver;
};

Base64Emitter::Base64Emitter(const std::array<char, 65> &alphabet,
                             std::function<void (char)> receiver) :
    m_state(0),
    m_bitsInState(0),
    m_requiredPadding(0),
    m_alphabet(alphabet),
    m_receiver(receiver)
{}

void
Base64Emitter::handle(unsigned char c)
{
    uint16_t bits = static_cast<uint16_t>(m_state) << 8 | c;
    size_t availableBits = m_bitsInState + 8;

    m_requiredPadding = 
        m_requiredPadding == 0 ?
        m_requiredPadding = 2 :
        m_requiredPadding - 1; 

    while (availableBits >= 6)
    {
        size_t shift = availableBits - 6;
        uint8_t next = static_cast<uint8_t>(bits >> shift);
        availableBits -= 6;
        uint16_t restMask = 0xFFFF ^ (0x3F << shift);
        bits &= restMask;

        emit(next);
    }

    m_state = static_cast<uint8_t>(bits);
    m_bitsInState = availableBits;
}

void
Base64Emitter::emit(uint8_t c)
{
    m_receiver(m_alphabet[c]);
}

void
Base64Emitter::pad()
{
    if (m_requiredPadding > 0)
    {
        uint8_t next = m_state << (6 - m_bitsInState);
        emit(next);
        for (auto i = 0; i < m_requiredPadding; ++i)
        {
            emit(64);
        }
    }

    m_state = 0;
    m_bitsInState = 0;
    m_requiredPadding = 0;
}

template <typename T>
void
Base64Emitter::encode(T&& begin, T&& end)
{
    std::for_each(begin, end,
        [&](uint8_t c) { handle(c); });
    pad();
}

}

std::string
Base64Encoder::encode(const bytevector &v) const
{
    std::string result;
    Base64Emitter emitter(BASE64_ALPHABET,
        [&](uint8_t c) { result.push_back(c); });

    emitter.encode(v.begin(), v.end());
    return result;
}