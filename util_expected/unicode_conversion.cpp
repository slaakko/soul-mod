// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util_expected.unicode;

import util_expected.error;
import std;

namespace util {

std::expected<std::u32string, int> ToUtf32(const std::string& utf8Str)
{
    std::u32string result;
    const char* p = utf8Str.c_str();
    int bytesRemaining = int(utf8Str.length());
    while (bytesRemaining > 0)
    {
        char8_t c = *p;
        std::uint8_t x = static_cast<std::uint8_t>(c);
        if ((x & 0x80u) == 0u)
        {
            result.append(1, static_cast<char32_t>(static_cast<std::uint32_t>(x)));
            --bytesRemaining;
            ++p;
        }
        else if ((x & 0xE0u) == 0xC0u)
        {
            if (bytesRemaining < 2)
            {
                return InvalidUtf8Sequence();
            }
            char32_t u = static_cast<char32_t>(static_cast<std::uint32_t>(0u));
            std::uint8_t b1 = static_cast<std::uint8_t>(p[1]);
            if ((b1 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            std::uint8_t shift = 0u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b1 & 1u;
                b1 = b1 >> 1u;
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b0 = x;
            for (std::uint8_t i = 0u; i < 5u; ++i)
            {
                std::uint8_t bit = b0 & 1u;
                b0 = b0 >> 1u;
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            result.append(1, u);
            bytesRemaining = bytesRemaining - 2;
            p = p + 2;
        }
        else if ((x & 0xF0u) == 0xE0u)
        {
            if (bytesRemaining < 3)
            {
                return InvalidUtf8Sequence();
            }
            char32_t u = static_cast<char32_t>(static_cast<std::uint32_t>(0u));
            std::uint8_t b2 = static_cast<std::uint8_t>(p[2]);
            if ((b2 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            std::uint8_t shift = 0u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b2 & 1u;
                b2 = b2 >> 1u;
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b1 = static_cast<std::uint8_t>(p[1]);
            if ((b1 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b1 & 1u;
                b1 = b1 >> 1u;
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b0 = x;
            for (std::uint8_t i = 0u; i < 4u; ++i)
            {
                std::uint8_t bit = b0 & 1u;
                b0 = b0 >> 1u;
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            result.append(1, u);
            bytesRemaining = bytesRemaining - 3;
            p = p + 3;
        }
        else if ((x & 0xF8u) == 0xF0u)
        {
            if (bytesRemaining < 4)
            {
                return InvalidUtf8Sequence();
            }
            char32_t u = static_cast<char32_t>(static_cast<std::uint32_t>(0u));
            std::uint8_t b3 = static_cast<std::uint8_t>(p[3]);
            if ((b3 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            std::uint8_t shift = 0u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b3 & 1u;
                b3 = b3 >> 1u;
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b2 = static_cast<std::uint8_t>(p[2]);
            if ((b2 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b2 & 1u;
                b2 = b2 >> 1u;
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b1 = static_cast<std::uint8_t>(p[1]);
            if ((b1 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b1 & 1u;
                b1 = b1 >> 1u;
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b0 = x;
            for (std::uint8_t i = 0u; i < 3u; ++i)
            {
                std::uint8_t bit = b0 & 1u;
                b0 = b0 >> 1u;
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            result.append(1, u);
            bytesRemaining = bytesRemaining - 4;
            p = p + 4;
        }
        else
        {
            return InvalidUtf8Sequence();
        }
    }
    return std::expected<std::u32string, int>(result);
}

std::expected<std::u32string, int> ToUtf32(const std::u16string& utf16Str)
{
    std::u32string result;
    const char16_t* w = utf16Str.c_str();
    int remaining = int(utf16Str.length());
    while (remaining > 0)
    {
        char16_t w1 = *w++;
        --remaining;
        if (static_cast<std::uint16_t>(w1) < 0xD800u || static_cast<std::uint16_t>(w1) > 0xDFFFu)
        {
            result.append(1, w1);
        }
        else
        {
            if (static_cast<std::uint16_t>(w1) < 0xD800u || static_cast<std::uint16_t>(w1) > 0xDBFFu)
            {
                return UnicodeError("invalid UTF-16 sequence");
            }
            if (remaining > 0)
            {
                char16_t w2 = *w++;
                --remaining;
                if (static_cast<std::uint16_t>(w2) < 0xDC00u || static_cast<std::uint16_t>(w2) > 0xDFFFu)
                {
                    return UnicodeError("invalid UTF-16 sequence");
                }
                else
                {
                    char32_t uprime = static_cast<char32_t>(((0x03FFu & static_cast<std::uint32_t>(w1)) << 10u) | (0x03FFu & static_cast<std::uint32_t>(w2)));
                    char32_t u = static_cast<char32_t>(static_cast<std::uint32_t>(uprime) + 0x10000u);
                    result.append(1, u);
                }
            }
            else
            {
                return UnicodeError("invalid UTF-16 sequence");
            }
        }
    }
    return std::expected<std::u32string, int>(result);
}

std::expected<std::u16string, int> ToUtf16(const std::u32string& utf32Str)
{
    std::u16string result;
    for (char32_t u : utf32Str)
    {
        if (static_cast<std::uint32_t>(u) > 0x10FFFFu)
        {
            return UnicodeError("invalid UTF-32 code point");
        }
        if (static_cast<std::uint32_t>(u) < 0x10000u)
        {
            if (static_cast<std::uint32_t>(u) >= 0xD800 && static_cast<std::uint32_t>(u) <= 0xDFFF)
            {
                return UnicodeError("invalid UTF-32 code point (reserved for UTF-16)");
            }
            char16_t x = static_cast<char16_t>(u);
            result.append(1, x);
        }
        else
        {
            char32_t uprime = static_cast<char32_t>(static_cast<std::uint32_t>(u) - 0x10000u);
            char16_t w1 = static_cast<char16_t>(0xD800u);
            char16_t w2 = static_cast<char16_t>(0xDC00u);
            for (std::uint16_t i = 0u; i < 10u; ++i)
            {
                std::uint16_t bit = static_cast<std::uint16_t>(static_cast<std::uint32_t>(uprime) & (static_cast<std::uint32_t>(0x1u) << i));
                w2 = static_cast<char16_t>(static_cast<std::uint16_t>(w2) | bit);
            }
            for (std::uint16_t i = 10u; i < 20u; ++i)
            {
                std::uint16_t bit = static_cast<std::uint16_t>((static_cast<std::uint32_t>(uprime) & (static_cast<std::uint32_t>(0x1u) << i)) >> 10u);
                w1 = static_cast<char16_t>(static_cast<std::uint16_t>(w1) | bit);
            }
            result.append(1, w1);
            result.append(1, w2);
        }
    }
    return std::expected<std::u16string, int>(result);

}

std::expected<std::u16string, int> ToUtf16(const std::string& utf8Str)
{
    std::expected<std::u32string, int> rv = ToUtf32(utf8Str);
    if (!rv) return std::unexpected<int>(rv.error());
    return ToUtf16(*rv);
}

std::expected<std::string, int> ToUtf8(const std::u32string& utf32Str)
{
    std::string result;
    for (char32_t c : utf32Str)
    {
        std::uint32_t x = static_cast<std::uint32_t>(c);
        if (x < 0x80u)
        {
            result.append(1, static_cast<char>(x & 0x7Fu));
        }
        else if (x < 0x800u)
        {
            std::uint8_t b1 = 0x80u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                b1 = b1 | (static_cast<std::uint8_t>(x & 1u) << i);
                x = x >> 1u;
            }
            std::uint8_t b0 = 0xC0u;
            for (std::uint8_t i = 0u; i < 5u; ++i)
            {
                b0 = b0 | (static_cast<std::uint8_t>(x & 1u) << i);
                x = x >> 1u;
            }
            result.append(1, static_cast<char8_t>(b0));
            result.append(1, static_cast<char8_t>(b1));
        }
        else if (x < 0x10000u)
        {
            std::uint8_t b2 = 0x80u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                b2 = b2 | (static_cast<std::uint8_t>(x & 1u) << i);
                x = x >> 1u;
            }
            std::uint8_t b1 = 0x80u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                b1 = b1 | (static_cast<std::uint8_t>(x & 1u) << i);
                x = x >> 1u;
            }
            std::uint8_t b0 = 0xE0u;
            for (std::uint8_t i = 0u; i < 4u; ++i)
            {
                b0 = b0 | (static_cast<std::uint8_t>(x & 1u) << i);
                x = x >> 1u;
            }
            result.append(1, static_cast<char8_t>(b0));
            result.append(1, static_cast<char8_t>(b1));
            result.append(1, static_cast<char8_t>(b2));
        }
        else if (x < 0x110000u)
        {
            std::uint8_t b3 = 0x80u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                b3 = b3 | (static_cast<std::uint8_t>(x & 1u) << i);
                x = x >> 1u;
            }
            std::uint8_t b2 = 0x80u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                b2 = b2 | (static_cast<std::uint8_t>(x & 1u) << i);
                x = x >> 1u;
            }
            std::uint8_t b1 = 0x80u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                b1 = b1 | (static_cast<std::uint8_t>(x & 1u) << i);
                x = x >> 1u;
            }
            std::uint8_t b0 = 0xF0u;
            for (std::uint8_t i = 0u; i < 3u; ++i)
            {
                b0 = b0 | (static_cast<std::uint8_t>(x & 1u) << i);
                x = x >> 1u;
            }
            result.append(1, static_cast<char8_t>(b0));
            result.append(1, static_cast<char8_t>(b1));
            result.append(1, static_cast<char8_t>(b2));
            result.append(1, static_cast<char8_t>(b3));
        }
        else
        {
            return UnicodeError("invalid UTF-32 code point");
        }
    }
    return std::expected<std::string, int>(result);
}

std::expected<std::string, int> ToUtf8(const std::u16string& utf16Str)
{
    std::expected<std::u32string, int> rv = ToUtf32(utf16Str);
    if (!rv) return std::unexpected<int>(rv.error());
    return ToUtf8(*rv);
}

} // util
