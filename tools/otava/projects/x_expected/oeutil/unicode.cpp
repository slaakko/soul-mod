// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.unicode;

import util.path;
import util.text.util;
import util.error;
import util.file.stream;
import util.buffered.stream;
import util.memory.stream;
import std;

namespace util {

std::string SoulVersionStr()
{
    return "5.0.0";
}

std::expected<std::string, int> SoulRoot()
{
    std::string soulRoot;
    const char* soulRootEnv = std::getenv("SOUL_ROOT");
    if (soulRootEnv)
    {
        soulRoot = soulRootEnv;
    }
    if (soulRoot.empty())
    {
        return std::unexpected<int>(AllocateError("please set 'SOUL_ROOT' environment variable to contain / path / to / soul directory."));
    }
    return std::expected<std::string, int>(soulRoot);
}

std::expected<std::string, int> SoulUcdFilePath()
{
    std::expected<std::string, int> rv = SoulRoot();
    if (!rv) return rv;
    std::string p = *rv;
    std::string s = util::Path::Combine(util::Path::Combine(p, "unicode"), "soul_ucd.bin");
    return std::expected<std::string, int>(s);
}

std::unexpected<int> InvalidUtf8Sequence()
{
    return std::unexpected<int>(AllocateError("invalid UTF-8 sequence"));
}

std::unexpected<int> UnicodeError(const std::string& message_)
{
    return std::unexpected<int>(AllocateError(message_));
}

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
                b1 = static_cast<std::uint8_t>(b1 >> 1u);
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b0 = x;
            for (std::uint8_t i = 0u; i < 5u; ++i)
            {
                std::uint8_t bit = b0 & 1u;
                b0 = static_cast<std::uint8_t>(b0 >> 1u);
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
                std::uint8_t bit = static_cast<std::uint8_t>(b2 & 1u);
                b2 = static_cast<std::uint8_t>(b2 >> 1u);
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
                std::uint8_t bit = static_cast<std::uint8_t>(b1 & 1u);
                b1 = static_cast<std::uint8_t>(b1 >> 1u);
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b0 = x;
            for (std::uint8_t i = 0u; i < 4u; ++i)
            {
                std::uint8_t bit = static_cast<std::uint8_t>(b0 & 1u);
                b0 = static_cast<std::uint8_t>(b0 >> 1u);
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
                std::uint8_t bit = static_cast<std::uint8_t>(b3 & 1u);
                b3 = static_cast<std::uint8_t>(b3 >> 1u);
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
                std::uint8_t bit = static_cast<std::uint8_t>(b2 & 1u);
                b2 = static_cast<std::uint8_t>(b2 >> 1u);
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
                std::uint8_t bit = static_cast<std::uint8_t>(b1 & 1u);
                b1 = static_cast<std::uint8_t>(b1 >> 1u);
                u = static_cast<char32_t>(static_cast<std::uint32_t>(u) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b0 = x;
            for (std::uint8_t i = 0u; i < 3u; ++i)
            {
                std::uint8_t bit = static_cast<std::uint8_t>(b0 & 1u);
                b0 = static_cast<std::uint8_t>(b0 >> 1u);
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

std::expected<std::u32string, int> ToUtf32(const std::u32string& utf32Str)
{
    std::expected<std::u32string, int> s(utf32Str);
    return s;
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
            if (static_cast<std::uint32_t>(u) >= 0xD800U && static_cast<std::uint32_t>(u) <= 0xDFFFU)
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

std::expected<std::u16string, int> ToUtf16(const std::u16string& utf16Str)
{
    std::expected<std::u16string, int> s(utf16Str);
    return s;
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

std::expected<std::string, int> ToUtf8(const std::string& utf8Str)
{
    std::expected<std::string, int> s(utf8Str);
    return s;
}

Utf8ToUtf32Engine::Utf8ToUtf32Engine() : state(0), resultReady(false), result(U'\0')
{
    bytes.push_back(static_cast<std::uint8_t>(0));
    bytes.push_back(static_cast<std::uint8_t>(0));
    bytes.push_back(static_cast<std::uint8_t>(0));
    bytes.push_back(static_cast<std::uint8_t>(0));
}

std::expected<bool, int> Utf8ToUtf32Engine::Put(std::uint8_t x)
{
    switch (state)
    {
    case 0:
    {
        resultReady = false;
        if ((x & 0x80u) == 0u)
        {
            result = static_cast<char32_t>(x);
            resultReady = true;
        }
        else if ((x & 0xE0u) == 0xC0u)
        {
            bytes[0] = x;
            state = 1;
        }
        else if ((x & 0xF0u) == 0xE0u)
        {
            bytes[0] = x;
            state = 2;
        }
        else if ((x & 0xF8u) == 0xF0u)
        {
            bytes[0] = x;
            state = 4;
        }
        else
        {
            return InvalidUtf8Sequence();
        }
        break;
    }
    case 1:
    {
        result = static_cast<char32_t>(0);
        bytes[1] = x;
        std::uint8_t b1 = bytes[1];
        if ((b1 & 0xC0u) != 0x80u)
        {
            return InvalidUtf8Sequence();
        }
        std::uint8_t shift = 0u;
        for (std::uint8_t i = 0u; i < 6u; ++i)
        {
            std::uint8_t bit = static_cast<std::uint8_t>(b1 & 1u);
            b1 = static_cast<std::uint8_t>(b1 >> 1u);
            result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
            ++shift;
        }
        std::uint8_t b0 = bytes[0];
        for (std::uint8_t i = 0u; i < 5u; ++i)
        {
            std::uint8_t bit = static_cast<std::uint8_t>(b0 & 1u);
            b0 = static_cast<std::uint8_t>(b0 >> 1u);
            result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
            ++shift;
        }
        resultReady = true;
        state = 0;
        break;
    }
    case 2:
    {
        bytes[1] = x;
        state = 3;
        break;
    }
    case 3:
    {
        bytes[2] = x;
        result = static_cast<char32_t>(0);
        std::uint8_t b2 = bytes[2];
        if ((b2 & 0xC0u) != 0x80u)
        {
            return InvalidUtf8Sequence();
        }
        std::uint8_t shift = 0u;
        for (std::uint8_t i = 0u; i < 6u; ++i)
        {
            std::uint8_t bit = static_cast<std::uint8_t>(b2 & 1u);
            b2 = static_cast<std::uint8_t>(b2 >> 1u);
            result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
            ++shift;
        }
        std::uint8_t b1 = bytes[1];
        if ((b1 & 0xC0u) != 0x80u)
        {
            return InvalidUtf8Sequence();
        }
        for (std::uint8_t i = 0u; i < 6u; ++i)
        {
            std::uint8_t bit = static_cast<std::uint8_t>(b1 & 1u);
            b1 = static_cast<std::uint8_t>(b1 >> 1u);
            result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
            ++shift;
        }
        std::uint8_t b0 = bytes[0];
        for (std::uint8_t i = 0u; i < 4u; ++i)
        {
            std::uint8_t bit = static_cast<std::uint8_t>(b0 & 1u);
            b0 = static_cast<std::uint8_t>(b0 >> 1u);
            result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
            ++shift;
        }
        resultReady = true;
        state = 0;
        break;
    }
    case 4:
    {
        bytes[1] = x;
        state = 5;
        break;
    }
    case 5:
    {
        bytes[2] = x;
        state = 6;
        break;
    }
    case 6:
    {
        bytes[3] = x;
        result = static_cast<char32_t>(0);
        std::uint8_t b3 = bytes[3];
        if ((b3 & 0xC0u) != 0x80u)
        {
            return InvalidUtf8Sequence();
        }
        std::uint8_t shift = 0u;
        for (std::uint8_t i = 0u; i < 6u; ++i)
        {
            std::uint8_t bit = static_cast<std::uint8_t>(b3 & 1u);
            b3 = static_cast<std::uint8_t>(b3 >> 1u);
            result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
            ++shift;
        }
        std::uint8_t b2 = bytes[2];
        if ((b2 & 0xC0u) != 0x80u)
        {
            return InvalidUtf8Sequence();
        }
        for (std::uint8_t i = 0u; i < 6u; ++i)
        {
            std::uint8_t bit = static_cast<std::uint8_t>(b2 & 1u);
            b2 = static_cast<std::uint8_t>(b2 >> 1u);
            result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
            ++shift;
        }
        std::uint8_t b1 = bytes[1];
        if ((b1 & 0xC0u) != 0x80u)
        {
            return InvalidUtf8Sequence();
        }
        for (std::uint8_t i = 0u; i < 6u; ++i)
        {
            std::uint8_t bit = static_cast<std::uint8_t>(b1 & 1u);
            b1 = static_cast<std::uint8_t>(b1 >> 1u);
            result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
            ++shift;
        }
        std::uint8_t b0 = bytes[0];
        for (std::uint8_t i = 0u; i < 3u; ++i)
        {
            std::uint8_t bit = static_cast<std::uint8_t>(b0 & 1u);
            b0 = static_cast<std::uint8_t>(b0 >> 1u);
            result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
            ++shift;
        }
        resultReady = true;
        state = 0;
        break;
    }
    }
    return std::expected<bool, int>(true);
}

std::expected<std::u32string, int> ToUpper(const std::u32string& s)
{
    std::u32string upper;
    for (char32_t c : s)
    {
        std::expected<char32_t, int> rv = ToUpper(c);
        if (!rv) return std::unexpected<int>(rv.error());
        upper.append(1, *rv);
    }
    return std::expected<std::u32string, int>(upper);
}

std::expected<std::u16string, int> ToUpper(const std::u16string& s)
{
    std::expected<std::u32string, int> utf32rv = ToUtf32(s);
    if (!utf32rv) return std::unexpected<int>(utf32rv.error());
    std::expected<std::u32string, int> upperrv = ToUpper(*utf32rv);
    if (!upperrv) return std::unexpected<int>(upperrv.error());
    return ToUtf16(*upperrv);
}

std::expected<std::string, int> ToUpper(const std::string& s)
{
    std::expected<std::u32string, int> utf32rv = ToUtf32(s);
    if (!utf32rv) return std::unexpected<int>(utf32rv.error());
    std::expected<std::u32string, int> upperrv = ToUpper(*utf32rv);
    if (!upperrv) return std::unexpected<int>(upperrv.error());
    return ToUtf8(*upperrv);
}

std::expected<std::u32string, int> ToLower(const std::u32string& s)
{
    std::u32string lower;
    for (char32_t c : s)
    {
        std::expected<char32_t, int> rv = ToLower(c);
        if (!rv) return std::unexpected<int>(rv.error());
        lower.append(1, *rv);
    }
    return std::expected<std::u32string, int>(lower);
}

std::expected<std::u16string, int> ToLower(const std::u16string& s)
{
    std::expected<std::u32string, int> utf32rv = ToUtf32(s);
    if (!utf32rv) return std::unexpected<int>(utf32rv.error());
    std::expected<std::u32string, int> lowerrv = ToLower(*utf32rv);
    if (!lowerrv) return std::unexpected<int>(lowerrv.error());
    return ToUtf16(*lowerrv);
}

std::expected<std::string, int> ToLower(const std::string& s)
{
    std::expected<std::u32string, int> utf32rv = ToUtf32(s);
    if (!utf32rv) return std::unexpected<int>(utf32rv.error());
    std::expected<std::u32string, int> lowerrv = ToLower(*utf32rv);
    if (!lowerrv) return std::unexpected<int>(lowerrv.error());
    return ToUtf8(*lowerrv);
}

std::string MakeCanonicalPropertyName(const std::string& s)
{
    std::string propertyName;
    for (char c : s)
    {
        if (c != '_' && c != ' ' && c != '-')
        {
            propertyName.append(1, c);
        }
    }
    return ToLowerNarrow(propertyName);
}

BinaryProperty::BinaryProperty(BinaryPropertyId id_, const std::string& shortName_, const std::string& longName_) : id(id_), shortName(shortName_), longName(longName_)
{
}

BinaryPropertyTable& BinaryPropertyTable::Instance()
{
    static BinaryPropertyTable instance;
    return instance;
}

BinaryPropertyTable::BinaryPropertyTable()
{
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::asciiHexDigit, "AHex", "Ascii Hex Digit"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::alphabetic, "Alpha", "Alphabetic"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::bidiControl, "Bidi C", "Bidi Control"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::bidiMirrored, "Bidi M", "Bidi Mirrored"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::cased, "Cased", "Cased"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::compositionExclusion, "CE", "Composition Exclusion"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::caseIgnorable, "CI", "Case Ignorable"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::fullCompositionExclusion, "Comp Ex", "Full Composition Exclusion"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::changesWhenCasefolded, "CWCF", "Changes When Casefolded"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::changesWhenCaseMapped, "CWCM", "Changes When Casemapped"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::changesWhenNFKCCasefolded, "CWKCF", "Changes When NFKC Casefolded"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::changesWhenLowercased, "CWL", "Changes When Lowercased"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::changesWhenTitlecased, "CWT", "Changes When Titlecased"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::changesWhenUppercased, "CWU", "Changes When Uppercased"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::dash, "Dash", "Dash"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::deprecated, "Dep", "Deprecated"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::defaultIgnorableCodePoint, "DI", "Default Ignorable Code Point"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::diacritic, "Dia", "Diacritic"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::extender, "Ext", "Extender"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::graphemeBase, "Gr Base", "Grapheme Base"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::graphemeExtend, "Gr Ext", "Grapheme Extend"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::graphemeLink, "Gr Link", "Grapheme Link"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::hexDigit, "Hex", "Hex Digit"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::hyphen, "Hyphen", "Hyphen"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::idContinue, "IDC", "ID Continue"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::ideographic, "Ideo", "Ideographic"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::idStart, "IDS", "ID Start"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::idsBinaryOperator, "IDSB", "IDS Binary Operator"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::idsTrinaryOperator, "IDST", "IDS Trinary Operator"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::joinControl, "Join C", "Join Control"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::logicalOrderException, "LOE", "Logical Order Exception"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::lowercase, "Lower", "Lowercase"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::math, "Math", "Math"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::noncharacterCodePoint, "NChar", "Noncharacter Code Point"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::otherAlphabetic, "OAlpha", "Other Alphabetic"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::otherDefaultIgnorableCodePoint, "ODI", "Other Default Ignorable Code Point"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::otherGraphemeExtend, "OGr Ext", "Other Grapheme Extend"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::otherIdContinue, "OIDC", "Other ID Continue"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::otherIdStart, "OIDS", "Other ID Start"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::otherLowercase, "OLower", "Other Lowercase"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::otherMath, "OMath", "Other Math"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::otherUppercase, "OUpper", "Other Uppercase"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::patternSyntax, "Pat Syn", "Pattern Syntax"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::patternWhiteSpace, "Pat WS", "Pattern White Space"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::prependedConcatenationMark, "PCM", "Prepended Concatenation Mark"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::quotationMark, "QMark", "Quotation Mark"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::radical, "Radical", "Radical"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::softDotted, "SD", "Soft Dotted"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::sentenceterminal, "STerm", "Sentence Terminal"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::terminalPunctuation, "Term", "Terminal Punctuation"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::unifiedIdeograph, "UIdeo", "Unified Ideograph"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::uppercase, "Upper", "Uppercase"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::variationSelector, "VS", "Variation Selector"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::whiteSpace, "WSpace", "White Space"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::xidContinue, "XIDC", "XID Continue"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::xidStart, "XIDS", "XID Start"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::expandsOnNFC, "XO NFC", "Expands On NFC"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::expandsOnNFD, "XO NFD", "Expands On NFD"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::expandsOnNFKC, "XO NFKC", "Expands On NFKC"));
    binaryProperties.push_back(BinaryProperty(BinaryPropertyId::expandsOnNFKD, "XO NFKD", "Expands On NFKD"));

    for (const BinaryProperty& binaryProperty : binaryProperties)
    {
        binaryPropertyIdMap[binaryProperty.Id()] = &binaryProperty;
        shortNameMap[MakeCanonicalPropertyName(binaryProperty.ShortName())] = &binaryProperty;
        longNameMap[MakeCanonicalPropertyName(binaryProperty.LongName())] = &binaryProperty;
    }
}

std::expected<const BinaryProperty*, int> BinaryPropertyTable::GetBinaryProperty(BinaryPropertyId binaryPropertyId) const
{
    auto it = binaryPropertyIdMap.find(binaryPropertyId);
    if (it != binaryPropertyIdMap.end())
    {
        return std::expected<const BinaryProperty*, int>(it->second);
    }
    else
    {
        std::string msg("binary property ");
        msg.append(std::to_string(static_cast<std::uint8_t>(binaryPropertyId)));
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

bool BinaryPropertyTable::IsBinaryProperty(const std::string& shortName) const
{
    return shortNameMap.find(MakeCanonicalPropertyName(shortName)) != shortNameMap.end();
}

std::expected<const BinaryProperty*, int> BinaryPropertyTable::GetBinaryPropertyByShortName(const std::string& shortName) const
{
    auto it = shortNameMap.find(MakeCanonicalPropertyName(shortName));
    if (it != shortNameMap.end())
    {
        return std::expected<const BinaryProperty*, int>(it->second);
    }
    else
    {
        std::string msg("binary property '");
        msg.append(shortName);
        msg.append("' not found");
        return UnicodeError(msg);
    }
}

std::expected<const BinaryProperty*, int> BinaryPropertyTable::GetBinaryPropertyByLongName(const std::string& longName) const
{
    auto it = longNameMap.find(MakeCanonicalPropertyName(longName));
    if (it != longNameMap.end())
    {
        return std::expected<const BinaryProperty*, int>(it->second);
    }
    else
    {
        std::string msg("binary property '");
        msg.append(longName);
        msg.append("' not found");
        return UnicodeError(msg);
    }
}

Block::Block(BlockId id_, const std::string& shortName_, const std::string& longName_, char32_t start_, char32_t end_) : id(id_), shortName(shortName_), longName(longName_), start(start_), end(end_)
{
}

BlockTable& BlockTable::Instance()
{
    static BlockTable instance;
    return instance;
}

BlockTable::BlockTable()
{
    blocks.push_back(Block(BlockId::ascii, "ASCII", "Basic Latin", 0x0000, 0x007F));
    blocks.push_back(Block(BlockId::latin1Sup, "Latin 1 Sup", "Latin-1 Supplement", 0x0080, 0x00FF));
    blocks.push_back(Block(BlockId::latinExtA, "Latin Ext A", "Latin Extended-A", 0x0100, 0x017F));
    blocks.push_back(Block(BlockId::latinExtB, "Latin Ext B", "Latin Extended-B", 0x0180, 0x0024F));
    blocks.push_back(Block(BlockId::ipaExt, "IPA Ext", "IPA Extensions", 0x0250, 0x02AF));
    blocks.push_back(Block(BlockId::modifierLetters, "Modifier Letters", "Spacing Modifier Letters", 0x02B0, 0x02FF));
    blocks.push_back(Block(BlockId::diacriticals, "Diacriticals", "Combining Diacritical Marks", 0x0300, 0x036F));
    blocks.push_back(Block(BlockId::greek, "Greek", "Greek and Coptic", 0x0370, 0x03FF));
    blocks.push_back(Block(BlockId::cyrillic, "Cyrillic", "Cyrillic", 0x0400, 0x04FF));
    blocks.push_back(Block(BlockId::cyrillicSup, "Cyrillic Sup", "Cyrillic Supplement", 0x0500, 0x052F));
    blocks.push_back(Block(BlockId::armenian, "Armenian", "Armenian", 0x0530, 0x058F));
    blocks.push_back(Block(BlockId::hebrew, "Hebrew", "Hebrew", 0x0590, 0x05FF));
    blocks.push_back(Block(BlockId::arabic, "Arabic", "Arabic", 0x0600, 0x06FF));
    blocks.push_back(Block(BlockId::syriac, "Syriac", "Syriac", 0x0700, 0x074F));
    blocks.push_back(Block(BlockId::arabicSup, "Arabic Sup", "Arabic Supplement", 0x0750, 0x077F));
    blocks.push_back(Block(BlockId::thaana, "Thaana", "Thaana", 0x0780, 0x07BF));
    blocks.push_back(Block(BlockId::nko, "Nko", "Nko", 0x07C0, 0x07FF));
    blocks.push_back(Block(BlockId::samaritan, "Samaritan", "Samaritan", 0x0800, 0x083F));
    blocks.push_back(Block(BlockId::mandaic, "Mandaic", "Mandaic", 0x0840, 0x085F));
    blocks.push_back(Block(BlockId::syriacSup, "Syriac Sup", "Syriac Supplement", 0x0860, 0x086F));
    blocks.push_back(Block(BlockId::arabicExtA, "Arabic Ext A", "Arabic Extended-A", 0x08A0, 0x08FF));
    blocks.push_back(Block(BlockId::devanagari, "Devanagari", "Devanagari", 0x0900, 0x097F));
    blocks.push_back(Block(BlockId::bengali, "Bengali", "Bengali", 0x0980, 0x09FF));
    blocks.push_back(Block(BlockId::gurmukhi, "Gurmukhi", "Gurmukhi", 0x0A00, 0x0A7F));
    blocks.push_back(Block(BlockId::gujarati, "Gujarati", "Gujarati", 0x0A80, 0x0AFF));
    blocks.push_back(Block(BlockId::oriya, "Oriya", "Oriya", 0x0B00, 0x0B7F));
    blocks.push_back(Block(BlockId::tamil, "Tamil", "Tamil", 0x0B80, 0x0BFF));
    blocks.push_back(Block(BlockId::telugu, "Telugu", "Telugu", 0x0C00, 0x0C7F));
    blocks.push_back(Block(BlockId::kannada, "Kannada", "Kannada", 0x0C80, 0x0CFF));
    blocks.push_back(Block(BlockId::malayalam, "Malayalam", "Malayalam", 0x0D00, 0x0D7F));
    blocks.push_back(Block(BlockId::sinhala, "Sinhala", "Sinhala", 0x0D80, 0x0DFF));
    blocks.push_back(Block(BlockId::thai, "Thai", "Thai", 0x0E00, 0x0E7F));
    blocks.push_back(Block(BlockId::lao, "Lao", "Lao", 0x0E80, 0x0EFF));
    blocks.push_back(Block(BlockId::tibetan, "Tibetan", "Tibetan", 0x0F00, 0x0FFF));
    blocks.push_back(Block(BlockId::myanmar, "Myanmar", "Myanmar", 0x1000, 0x109F));
    blocks.push_back(Block(BlockId::georgian, "Georgian", "Georgian", 0x10A0, 0x10FF));
    blocks.push_back(Block(BlockId::jamo, "Jamo", "Hangul Jamo", 0x1100, 0x11FF));
    blocks.push_back(Block(BlockId::ethiopic, "Ethiopic", "Ethiopic", 0x1200, 0x137F));
    blocks.push_back(Block(BlockId::ethiopicSup, "Ethiopic Sup", "Ethiopic Supplement", 0x1380, 0x139F));
    blocks.push_back(Block(BlockId::cherokee, "Cherokee", "Cherokee", 0x13A0, 0x13FF));
    blocks.push_back(Block(BlockId::ucas, "UCAS", "Unified Canadian Aboriginal Syllabics", 0x1400, 0x167F));
    blocks.push_back(Block(BlockId::ogham, "Ogham", "Ogham", 0x1680, 0x169F));
    blocks.push_back(Block(BlockId::runic, "Runic", "Runic", 0x16A0, 0x16FF));
    blocks.push_back(Block(BlockId::tagalog, "Tagalog", "Tagalog", 0x1700, 0x171F));
    blocks.push_back(Block(BlockId::hanunoo, "Hanunoo", "Hanunoo", 0x1720, 0x173F));
    blocks.push_back(Block(BlockId::buhid, "Buhid", "Buhid", 0x1740, 0x175F));
    blocks.push_back(Block(BlockId::tagbanwa, "Tagbanwa", "Tagbanwa", 0x1760, 0x177F));
    blocks.push_back(Block(BlockId::khmer, "Khmer", "Khmer", 0x1780, 0x17FF));
    blocks.push_back(Block(BlockId::mongolian, "Mongolian", "Mongolian", 0x1800, 0x18AF));
    blocks.push_back(Block(BlockId::ucasExt, "UCAS Ext", "Unified Canadian Aboriginal Syllabics Extended", 0x18B0, 0x18FF));
    blocks.push_back(Block(BlockId::limbu, "Limbu", "Limbu", 0x1900, 0x194F));
    blocks.push_back(Block(BlockId::taiLe, "Tai Le", "Tai Le", 0x1950, 0x197F));
    blocks.push_back(Block(BlockId::newTaiLue, "New Tai Lue", "New Tai Lue", 0x1980, 0x19DF));
    blocks.push_back(Block(BlockId::khmerSymbols, "Khmer Symbols", "Khmer Symbols", 0x19E0, 0x19FF));
    blocks.push_back(Block(BlockId::buginese, "Buginese", "Buginese", 0x1A00, 0x1A1F));
    blocks.push_back(Block(BlockId::taiTham, "Tai Tham", "Tai Tham", 0x1A20, 0x1AAF));
    blocks.push_back(Block(BlockId::diacriticalsExt, "Diacriticals Ext", "Combining Diacritical Marks Extended", 0x1AB0, 0x1AFF));
    blocks.push_back(Block(BlockId::balinese, "Balinese", "Balinese", 0x1B00, 0x1B7F));
    blocks.push_back(Block(BlockId::sundanese, "Sundanese", "Sundanese", 0x1B80, 0x1BBF));
    blocks.push_back(Block(BlockId::batak, "Batak", "Batak", 0x1BC0, 0x1BFF));
    blocks.push_back(Block(BlockId::lepcha, "Lepcha", "Lepcha", 0x1C00, 0x1C4F));
    blocks.push_back(Block(BlockId::olChiki, "Ol Chiki", "Ol Chiki", 0x1C50, 0x1C7F));
    blocks.push_back(Block(BlockId::cyrillicExtC, "Cyrillic Ext C", "Cyrillic Extended-C", 0x1C80, 0x1C8F));
    blocks.push_back(Block(BlockId::georgianExt, "Georgian Ext", "Georgian Extended", 0x1C90, 0x1CBF));
    blocks.push_back(Block(BlockId::sundaneseSup, "Sundanese Sup", "Sundanese Supplement", 0x1CC0, 0x1CCF));
    blocks.push_back(Block(BlockId::vedicExt, "Vedic Ext", "Vedic Extensions", 0x1CD0, 0x1CFF));
    blocks.push_back(Block(BlockId::phoneticExt, "Phonetic Ext", "Phonetic Extensions", 0x1D00, 0x1D7F));
    blocks.push_back(Block(BlockId::phoneticExtSup, "Phonetic Ext Sup", "Phonetic Extensions Supplement", 0x1D80, 0x1DBF));
    blocks.push_back(Block(BlockId::diacriticalsSup, "Diacriticals Sup", "Combining Diacritical Marks Supplement", 0x1DC0, 0x1DFF));
    blocks.push_back(Block(BlockId::latinExtAdditional, "Latin Ext Additional", "Latin Extended Additional", 0x1E00, 0x1EFF));
    blocks.push_back(Block(BlockId::greekExt, "Greek Ext", "Greek Extended", 0x1F00, 0x1FFF));
    blocks.push_back(Block(BlockId::punctuation, "Punctuation", "General Punctuation", 0x2000, 0x206F));
    blocks.push_back(Block(BlockId::superAndSub, "Super And Sub", "Superscripts and Subscripts", 0x2070, 0x209F));
    blocks.push_back(Block(BlockId::currencySymbols, "Currency Symbols", "Currency Symbols", 0x20A0, 0x20CF));
    blocks.push_back(Block(BlockId::diariticalsForSymbols, "Diacriticals For Symbols", "Combining Diacritical Marks for Symbols", 0x20D0, 0x20FF));
    blocks.push_back(Block(BlockId::letterlikeSymbols, "Letterlike Symbols", "Letterlike Symbols", 0x2100, 0x214F));
    blocks.push_back(Block(BlockId::numberForms, "Number Forms", "Number Forms", 0x2150, 0x218F));
    blocks.push_back(Block(BlockId::arrows, "Arrows", "Arrows", 0x2190, 0x21FF));
    blocks.push_back(Block(BlockId::mathOperators, "Math Operators", "Mathematical Operators", 0x2200, 0x22FF));
    blocks.push_back(Block(BlockId::miscTechnical, "Misc Technical", "Miscellaneous Technical", 0x2300, 0x23FF));
    blocks.push_back(Block(BlockId::controlPictures, "Control Pictures", "Control Pictures", 0x2400, 0x243F));
    blocks.push_back(Block(BlockId::ocr, "OCR", "Optical Character Regognition", 0x2440, 0x245F));
    blocks.push_back(Block(BlockId::enclosedAlphanum, "Enclosed Alphanum", "Enclosed Alphanumerics", 0x2460, 0x24FF));
    blocks.push_back(Block(BlockId::boxDrawing, "Box Drawing", "Box Drawing", 0x2500, 0x257F));
    blocks.push_back(Block(BlockId::blockElements, "Block Elements", "Block Elements", 0x2580, 0x259F));
    blocks.push_back(Block(BlockId::geometricShapes, "Geometric Shapes", "Geometric Shapes", 0x25A0, 0x25FF));
    blocks.push_back(Block(BlockId::miscSymbols, "Misc Symbols", "Miscellaneous Symbols", 0x2600, 0x26FF));
    blocks.push_back(Block(BlockId::dingbats, "Dingbats", "Dingbats", 0x2700, 0x27BF));
    blocks.push_back(Block(BlockId::miscMathSymbolsA, "Misc Math Symbols A", "Miscellaneous Mathematical Symbols - A", 0x27C0, 0x27EF));
    blocks.push_back(Block(BlockId::supArrowsA, "Sup Arrows A", "Supplemental Arrows-A", 0x27F0, 0x27FF));
    blocks.push_back(Block(BlockId::braille, "Braille", "Braille Patterns", 0x2800, 0x28FF));
    blocks.push_back(Block(BlockId::supArrowsB, "Sup Arrows B", "Supplemental Arrows-B", 0x2900, 0x297F));
    blocks.push_back(Block(BlockId::miscMathSymbolsB, "Misc Math Symbols B", "Miscellaneous Mathematical Symbols-B", 0x2980, 0x29FF));
    blocks.push_back(Block(BlockId::supMathOperators, "Sup Math Operators", "Supplemental Mathematical Operators", 0x2A00, 0x2AFF));
    blocks.push_back(Block(BlockId::miscArrows, "Misc Arrows", "Miscellaneous Symbols and Arrows", 0x2B00, 0x2BFF));
    blocks.push_back(Block(BlockId::glagolitic, "Glagolitic", "Glagolitic", 0x2C00, 0x2C5F));
    blocks.push_back(Block(BlockId::latinExtC, "Latin Ext C", "Latin Extended-C", 0x2C60, 0x2C7F));
    blocks.push_back(Block(BlockId::coptic, "Coptic", "Coptic", 0x2C80, 0x2CFF));
    blocks.push_back(Block(BlockId::georgianSup, "Georgian Sup", "Georgian Supplement", 0x2D00, 0x2D2F));
    blocks.push_back(Block(BlockId::tifinagh, "Tifinagh", "Tifinagh", 0x2D30, 0x2D7F));
    blocks.push_back(Block(BlockId::ethiopicExt, "Ethiopic Ext", "Ethiopic Extended", 0x2D80, 0x2DDF));
    blocks.push_back(Block(BlockId::cyrillicExtA, "Cyrillic Ext A", "Cyrillic Extended-A", 0x2DE0, 0x2DFF));
    blocks.push_back(Block(BlockId::supPunctuation, "Sup Punctuation", "Supplemental Punctuation", 0x2E00, 0x2E7F));
    blocks.push_back(Block(BlockId::cjkRadicalsSup, "CJK Radicals Sup", "CJK Radicals Supplement", 0x2E80, 0x2EFF));
    blocks.push_back(Block(BlockId::kangxi, "Kangxi", "Kangxi Radicals", 0x2F00, 0x2FDF));
    blocks.push_back(Block(BlockId::idc, "IDC", "Ideographic Description Characters", 0x2FF0, 0x2FFF));
    blocks.push_back(Block(BlockId::cjkSymbols, "CJK Symbols", "CJK Symbols and Punctuation", 0x3000, 0x303F));
    blocks.push_back(Block(BlockId::hiragana, "Hiragana", "Hiragana", 0x3040, 0x309F));
    blocks.push_back(Block(BlockId::katakana, "Katakana", "Katakana", 0x30A0, 0x30FF));
    blocks.push_back(Block(BlockId::bopomofo, "Bopomofo", "Bopomofo", 0x3100, 0x312F));
    blocks.push_back(Block(BlockId::compatJamo, "Compat Jamo", "Hangul Compatibility Jamo", 0x3130, 0x318F));
    blocks.push_back(Block(BlockId::kanbun, "Kanbun", "Kanbun", 0x3190, 0x319F));
    blocks.push_back(Block(BlockId::bopomofoExt, "Bopomofo Ext", "Bopomofo Extended", 0x31A0, 0x31BF));
    blocks.push_back(Block(BlockId::cjkStrokes, "CJK Strokes", "CJK Strokes", 0x31C0, 0x31EF));
    blocks.push_back(Block(BlockId::katakanaExt, "Katakana Ext", "Katakana Phonetic Extensions", 0x31F0, 0x31FF));
    blocks.push_back(Block(BlockId::enclosedCjk, "Enclosed CJK", "Enclosed CJK Letters and Months", 0x3200, 0x32FF));
    blocks.push_back(Block(BlockId::cjkCompat, "CJK Compat", "CJK Compatibility", 0x3300, 0x33FF));
    blocks.push_back(Block(BlockId::cjkExtA, "CJK Ext A", "CJK Unified Ideographic Extension A", 0x3400, 0x4DBF));
    blocks.push_back(Block(BlockId::yijing, "Yijing", "Yijing Hexagram Symbols", 0x4DC0, 0x4DFF));
    blocks.push_back(Block(BlockId::cjk, "CJK", "CJK Unified Ideographs", 0x4E00, 0x9FFF));
    blocks.push_back(Block(BlockId::yiSyllables, "Yi Syllables", "Yi Syllables", 0xA000, 0xA48F));
    blocks.push_back(Block(BlockId::yiRadicals, "Yi Radicals", "Yi Radicals", 0xA090, 0xA4CF));
    blocks.push_back(Block(BlockId::lisu, "Lisu", "Lisu", 0xA0D0, 0xA4FF));
    blocks.push_back(Block(BlockId::vai, "Vai", "Vai", 0xA500, 0xA63F));
    blocks.push_back(Block(BlockId::cyrillicExtB, "Cyrillic Ext B", "Cyrillic Extended-B", 0xA640, 0xA69F));
    blocks.push_back(Block(BlockId::bamum, "Bamum", "Bamum", 0xA6A0, 0xA6FF));
    blocks.push_back(Block(BlockId::modifierToneLetters, "Modifier Tone Letters", "Modifier Tone Letters", 0xA700, 0xA71F));
    blocks.push_back(Block(BlockId::latinExtD, "Latin Ext D", "Latin Extended-D", 0xA720, 0xA7FF));
    blocks.push_back(Block(BlockId::sylotiNagri, "Syloti Nagri", "Syloti Nagri", 0xA800, 0xA82F));
    blocks.push_back(Block(BlockId::indicNumberForms, "Indic Number Forms", "Common Indic Number Forms", 0xA830, 0xA83F));
    blocks.push_back(Block(BlockId::phagsPa, "Phags Pa", "Phags-Pa", 0xA840, 0xA87F));
    blocks.push_back(Block(BlockId::saurashtra, "Saurashtra", "Saurashtra", 0xA880, 0xA8DF));
    blocks.push_back(Block(BlockId::devanagariExt, "Devanagari Ext", "Devanagari Extended", 0xA8E0, 0xA8FF));
    blocks.push_back(Block(BlockId::kayahLi, "Kayah Li", "Kayah Li", 0xA900, 0xA92F));
    blocks.push_back(Block(BlockId::rejang, "Rejang", "Rejang", 0xA930, 0xA95F));
    blocks.push_back(Block(BlockId::jamoExtA, "Jamo Ext A", "Hangul Jamo Extended-A", 0xA960, 0xA97F));
    blocks.push_back(Block(BlockId::javanese, "Javanese", "Javanese", 0xA980, 0xA9DF));
    blocks.push_back(Block(BlockId::myanmarExtB, "Myanmar Ext B", "Myanmar Extended - B", 0xA9E0, 0xA9FF));
    blocks.push_back(Block(BlockId::cham, "Cham", "Cham", 0xAA00, 0xAA5F));
    blocks.push_back(Block(BlockId::myanmarExtA, "Myanmar Ext A", "Myanmar Extended-A", 0xAA60, 0xAA7F));
    blocks.push_back(Block(BlockId::taiViet, "Tai Viet", "Tai Viet", 0xAA80, 0xAADF));
    blocks.push_back(Block(BlockId::meeteiMayekExt, "Meetei Mayek Ext", "Meetei Mayek Extensions", 0xAAE0, 0xAAFF));
    blocks.push_back(Block(BlockId::ethiopicExtA, "Ethiopic Ext A", "Ethiopic Extended-A", 0xAB00, 0xAB2F));
    blocks.push_back(Block(BlockId::latinExtE, "Latin Ext E", "Latin Extended-E", 0xAB30, 0xAB6F));
    blocks.push_back(Block(BlockId::cherokeeSup, "Cherokee Sup", "Cherokee Supplement", 0xAB70, 0xABBF));
    blocks.push_back(Block(BlockId::meeteiMayek, "Meetei Mayek", "Meetei Mayek", 0xABC0, 0xABFF));
    blocks.push_back(Block(BlockId::hangul, "Hangul", "Hangul Syllables", 0xAC00, 0xD7AF));
    blocks.push_back(Block(BlockId::jamoExtB, "Jamo Ext B", "Hangul Jamo Extended-B", 0xD7B0, 0xD7FF));
    blocks.push_back(Block(BlockId::highSurrogates, "High Surrogates", "High Surrogates", 0xD800, 0xDB7F));
    blocks.push_back(Block(BlockId::highPuSurrogates, "High PU Surrogates", "High Private Use Surrogates", 0xDB80, 0xDBFF));
    blocks.push_back(Block(BlockId::lowSurrogates, "Low Surrogates", "Low Surrogates", 0xDC00, 0xDFFF));
    blocks.push_back(Block(BlockId::pua, "PUA", "Private Use Area", 0xE000, 0xF8FF));
    blocks.push_back(Block(BlockId::cjkCompatIdeographs, "CJK Compat Ideographs", "CJK Compatibility Ideographs", 0xF900, 0xFAFF));
    blocks.push_back(Block(BlockId::alphabeticPf, "Alphabetic PF", "Alphabetic Presentations Forms", 0xFB00, 0xFB4F));
    blocks.push_back(Block(BlockId::arabicPfA, "Arabic PF A", "Arabic Presentation Forms-A", 0xFB50, 0xFDFF));
    blocks.push_back(Block(BlockId::vs, "VS", "Variation Selectors", 0xFE00, 0xFE0F));
    blocks.push_back(Block(BlockId::verticalForms, "Vertical Forms", "Vertical Forms", 0xFE10, 0xFE1F));
    blocks.push_back(Block(BlockId::halfMarks, "Half Marks", "Combining Half Marks", 0xFE20, 0xFE2F));
    blocks.push_back(Block(BlockId::cjkCompatForms, "CJK Compat Forms", "CJK Compatibility Forms", 0xFE30, 0xFE4F));
    blocks.push_back(Block(BlockId::smallForms, "Small Forms", "Small Form Variants", 0xFE50, 0xFE6F));
    blocks.push_back(Block(BlockId::arabicPfB, "Arabic PF B", "Arabic Presentation Forms-B", 0xFE70, 0xFEFF));
    blocks.push_back(Block(BlockId::halfAndFullForms, "Half And Full Forms", "Halfwidth and Fullwidth Forms", 0xFF00, 0xFFEF));
    blocks.push_back(Block(BlockId::specials, "Specials", "Specials", 0xFFF0, 0xFFFF));
    blocks.push_back(Block(BlockId::linearBSyllabary, "Linear B Syllabary", "Linear B Syllabary", 0x10000, 0x1007F));
    blocks.push_back(Block(BlockId::linearBIdeograms, "Linear B Ideograms", "Linear B Ideograms", 0x10080, 0x100FF));
    blocks.push_back(Block(BlockId::aegeanNumbers, "Aegean Numbers", "Aegean Numbers", 0x10100, 0x1013F));
    blocks.push_back(Block(BlockId::ancientGreekNumbers, "Ancient Greek Numbers", "Ancient Greek Numbers", 0x10140, 0x1018F));
    blocks.push_back(Block(BlockId::ancientSymbols, "Ancient Symbols", "Ancient Symbols", 0x10190, 0x101CF));
    blocks.push_back(Block(BlockId::phaistos, "Phaistos", "Phaistos Disc", 0x101D0, 0x101FF));
    blocks.push_back(Block(BlockId::lycian, "Lycian", "Lycian", 0x10280, 0x1029F));
    blocks.push_back(Block(BlockId::carian, "Carian", "Carian", 0x102A0, 0x102DF));
    blocks.push_back(Block(BlockId::copticEpactNumbers, "Coptic Epact Numbers", "Coptic Epact Numbers", 0x102E0, 0x102FF));
    blocks.push_back(Block(BlockId::oldItalic, "Old Italic", "Old Italic", 0x10300, 0x1032F));
    blocks.push_back(Block(BlockId::gothic, "Gothic", "Gothic", 0x10330, 0x1034F));
    blocks.push_back(Block(BlockId::oldPermic, "Old Permic", "Old Permic", 0x10350, 0x1037F));
    blocks.push_back(Block(BlockId::ugaritic, "Ugaritic", "Ugaritic", 0x10380, 0x1039F));
    blocks.push_back(Block(BlockId::oldPersian, "Old Persian", "Old Persian", 0x103A0, 0x103DF));
    blocks.push_back(Block(BlockId::deseret, "Deseret", "Deseret", 0x10400, 0x1044F));
    blocks.push_back(Block(BlockId::shavian, "Shavian", "Shavian", 0x10450, 0x1047F));
    blocks.push_back(Block(BlockId::osmanya, "Osmanya", "Osmanya", 0x10480, 0x104AF));
    blocks.push_back(Block(BlockId::osage, "Osage", "Osage", 0x104B0, 0x104FF));
    blocks.push_back(Block(BlockId::elbasan, "Elbasan", "Elbasan", 0x10500, 0x1052F));
    blocks.push_back(Block(BlockId::caucasianAlbanian, "Caucasian Albanian", "Caucasian Albanian", 0x10530, 0x1056F));
    blocks.push_back(Block(BlockId::linearA, "Linear A", "Linear A", 0x10600, 0x1077F));
    blocks.push_back(Block(BlockId::cypriotSyllabary, "Cypriot Syllabary", "Cypriot Syllabary", 0x10800, 0x1083F));
    blocks.push_back(Block(BlockId::imperialAramaic, "Imperial Aramaic", "Imperial Aramaic", 0x10840, 0x1085F));
    blocks.push_back(Block(BlockId::palmyrene, "Palmyrene", "Palmyrene", 0x10860, 0x1087F));
    blocks.push_back(Block(BlockId::nabataean, "Nabataean", "Nabataean", 0x10880, 0x108AF));
    blocks.push_back(Block(BlockId::hatran, "Hatran", "Hatran", 0x108E0, 0x108FF));
    blocks.push_back(Block(BlockId::phoenician, "Phoenician", "Phoenician", 0x10900, 0x1091F));
    blocks.push_back(Block(BlockId::lydian, "Lydian", "Lydian", 0x10920, 0x1093F));
    blocks.push_back(Block(BlockId::meroiticHieroglyphs, "Meroitic Hieroglyphs", "Meroitic Hieroglyphs", 0x10980, 0x1099F));
    blocks.push_back(Block(BlockId::meroiticCursive, "Meroitic Cursive", "Meroitic Cursive", 0x109A0, 0x109FF));
    blocks.push_back(Block(BlockId::kharoshthi, "Kharoshthi", "Kharoshthi", 0x10A00, 0x10A5F));
    blocks.push_back(Block(BlockId::oldSouthArabian, "Old South Arabian", "Old South Arabian", 0x10A60, 0x10A7F));
    blocks.push_back(Block(BlockId::oldNorthArabian, "Old North Arabian", "Old North Arabian", 0x10A80, 0x10A9F));
    blocks.push_back(Block(BlockId::manichean, "Manichaean", "Manichaean", 0x10AC0, 0x10AFF));
    blocks.push_back(Block(BlockId::avestan, "Avestan", "Avestan", 0x10B00, 0x10B3F));
    blocks.push_back(Block(BlockId::inscriptionalParthian, "Inscriptional Parthian", "Inscriptional Parthian", 0x10B40, 0x10B5F));
    blocks.push_back(Block(BlockId::inscriptionalPahlavi, "Inscriptional Pahlavi", "Inscriptional Pahlavi", 0x10B60, 0x10B7F));
    blocks.push_back(Block(BlockId::psalterPahlavi, "Psalter Pahlavi", "Psalter Pahlavi", 0x10B80, 0x10BAF));
    blocks.push_back(Block(BlockId::oldTurkic, "Old Turkic", "Old Turkic", 0x10C00, 0x10C4F));
    blocks.push_back(Block(BlockId::oldHungarian, "Old Hungarian", "Old Hungarian", 0x10C80, 0x10CFF));
    blocks.push_back(Block(BlockId::hanifiRohingya, "Hanifi Rohingya", "Hanifi Rohingya", 0x10D00, 0x10D3F));
    blocks.push_back(Block(BlockId::rumi, "Rumi", "Rumi Numeral Symbols", 0x10E60, 0x10E7F));
    blocks.push_back(Block(BlockId::oldSogdian, "Old Sogdian", "Old Sogdian", 0x10F00, 0x10F2F));
    blocks.push_back(Block(BlockId::sogdian, "Sogdian", "Sogdian", 0x10F30, 0x10F6F));
    blocks.push_back(Block(BlockId::elymaic, "Elymaic", "Elymaic", 0x10FE0, 0x10FFF)); // 12.0
    blocks.push_back(Block(BlockId::brahmi, "Brahmi", "Brahmi", 0x11000, 0x1107F));
    blocks.push_back(Block(BlockId::kaithi, "Kaithi", "Kaithi", 0x11080, 0x110CF));
    blocks.push_back(Block(BlockId::soraSompeng, "Sora Sompeng", "Sora Sompeng", 0x110D0, 0x110FF));
    blocks.push_back(Block(BlockId::chakma, "Chakma", "Chakma", 0x11100, 0x1114F));
    blocks.push_back(Block(BlockId::mahajani, "Mahajani", "Mahajani", 0x11150, 0x1117F));
    blocks.push_back(Block(BlockId::sharada, "Sharada", "Sharada", 0x11180, 0x111DF));
    blocks.push_back(Block(BlockId::sinhalaArchaicNumbers, "Sinhala Archaic Numbers", "Sinhala Archaic Numbers", 0x111E0, 0x111FF));
    blocks.push_back(Block(BlockId::khojki, "Khojki", "Khojki", 0x11200, 0x1124F));
    blocks.push_back(Block(BlockId::multani, "Multani", "Multani", 0x11280, 0x112AF));
    blocks.push_back(Block(BlockId::khudawadi, "Khudawadi", "Khudawadi", 0x112B0, 0x112FF));
    blocks.push_back(Block(BlockId::grantha, "Grantha", "Grantha", 0x11300, 0x1137F));
    blocks.push_back(Block(BlockId::newa, "Newa", "Newa", 0x11400, 0x1147F));
    blocks.push_back(Block(BlockId::tirhuta, "Tirhuta", "Tirhuta", 0x11480, 0x114DF));
    blocks.push_back(Block(BlockId::siddham, "Siddham", "Siddham", 0x11580, 0x115FF));
    blocks.push_back(Block(BlockId::modi, "Modi", "Modi", 0x11600, 0x1165F));
    blocks.push_back(Block(BlockId::mongolianSup, "Mongolian Sup", "Mongolian Supplement", 0x11660, 0x1167F));
    blocks.push_back(Block(BlockId::takri, "Takri", "Takri", 0x11680, 0x116CF));
    blocks.push_back(Block(BlockId::ahom, "Ahom", "Ahom", 0x11700, 0x1173F));
    blocks.push_back(Block(BlockId::dogra, "Dogra", "Dogra", 0x11800, 0x1184F));
    blocks.push_back(Block(BlockId::warangCiti, "Warang Citi", "Warang Citi", 0x118A0, 0x118FF));
    blocks.push_back(Block(BlockId::nandinagari, "Nandinagari", "Nandinagari", 0x119A0, 0x119FF)); // 12.0
    blocks.push_back(Block(BlockId::zanabazarSquare, "Zanabazar Square", "Zanabazar Square", 0x11A00, 0x11A4FF));
    blocks.push_back(Block(BlockId::soyombo, "Soyombo", "Soyombo", 0x11A50, 0x11AAF));
    blocks.push_back(Block(BlockId::pauCinHau, "Pau Cin Hau", "Pau Cin Hau", 0x11AC0, 0x11AFF));
    blocks.push_back(Block(BlockId::bhaisuki, "Bhaiksuki", "Bhaiksuki", 0x11C00, 0x11C6F));
    blocks.push_back(Block(BlockId::marchen, "Marchen", "Marchen", 0x11C70, 0x11CBF));
    blocks.push_back(Block(BlockId::masaramGondi, "Masaram Gondi", "Masaram Gondi", 0x11D00, 0x11D5F));
    blocks.push_back(Block(BlockId::gunjalaGondi, "Gunjala Gondi", "Gunjala Gondi", 0x11D60, 0x11DAF));
    blocks.push_back(Block(BlockId::makasar, "Makasar", "Makasar", 0x11EE0, 0x11EFF));
    blocks.push_back(Block(BlockId::tamilSup, "Tamil Sup", "Tamil Sup", 0x11FC0, 0x11FFE)); // 12.0
    blocks.push_back(Block(BlockId::cuneiform, "Cuneiform", "Cuneiform", 0x12000, 0x123FF));
    blocks.push_back(Block(BlockId::cuneiformNumbers, "Cuneiform Numbers", "Cuneiform Numbers and Punctuation", 0x12400, 0x1247F));
    blocks.push_back(Block(BlockId::earlyDynasticCuneiform, "Early Dynastic Cuneiform", "Early Dynastic Cuneiform", 0x12480, 0x1254F));
    blocks.push_back(Block(BlockId::egyptianHieroglyphs, "Egyptian Hieroglyphs", "Egyptian Hieroglyphs", 0x13000, 0x1342F));
    blocks.push_back(Block(BlockId::egyptianHieroglyphFormatControls, "Egyptian Hieroglyph Format Controls", "Egyptian Hieroglyph Format Controls", 0x13430, 0x1343F)); // 12.0
    blocks.push_back(Block(BlockId::anatolianHieroglyphs, "Anatolian Hieroglyphs", "Anatolian Hieroglyphs", 0x14400, 0x1467F));
    blocks.push_back(Block(BlockId::bamumSup, "Bamum Sup", "Bamum Supplement", 0x16800, 0x16A3F));
    blocks.push_back(Block(BlockId::mro, "Mro", "Mro", 0x16A40, 0x16A6F));
    blocks.push_back(Block(BlockId::bassaVah, "Bassa Vah", "Bassa Vah", 0x16AD0, 0x16AFF));
    blocks.push_back(Block(BlockId::pahawhHmong, "Pahawh Hmong", "Pahawh Hmong", 0x16B00, 0x16B8F));
    blocks.push_back(Block(BlockId::medefaidrin, "Medefaidrin", "Medefaidrin", 0x16E40, 0x16E9F));
    blocks.push_back(Block(BlockId::miao, "Miao", "Miao", 0x16F00, 0x16F9F));
    blocks.push_back(Block(BlockId::ideographicSymbols, "Ideographic Symbols", "Ideographic Symbols and Punctuation", 0x16FE0, 0x16FFF));
    blocks.push_back(Block(BlockId::tangut, "Tangut", "Tangut", 0x17000, 0x187FF));
    blocks.push_back(Block(BlockId::tangutComponents, "Tangut Components", "Tangut Components", 0x18800, 0x18AFF));
    blocks.push_back(Block(BlockId::kanaSup, "Kana Sup", "Kana Supplement", 0x1B000, 0x1B0FF));
    blocks.push_back(Block(BlockId::kanaExtA, "Kana Ext A", "Kana Extended-A", 0x1B100, 0x1B12F));
    blocks.push_back(Block(BlockId::smallKanaExt, "Small Kana Ext", "Small Kana Extension", 0x1B130, 0x1B16F)); // 12.0
    blocks.push_back(Block(BlockId::nushu, "Nushu", "Nushu", 0x1B170, 0x1B2FF));
    blocks.push_back(Block(BlockId::duployan, "Duployan", "Duployan", 0x1BC00, 0x1BC9F));
    blocks.push_back(Block(BlockId::shorthandFormatControls, "Shorthand Format Controls", "Shorthand Format Controls", 0x1BCA0, 0x1BCAF));
    blocks.push_back(Block(BlockId::byzantineMusic, "Byzantine Music", "Byzantine Musical Symbols", 0x1D000, 0x1D0FF));
    blocks.push_back(Block(BlockId::music, "Music", "Musical Symbols", 0x1D100, 0x1D1FF));
    blocks.push_back(Block(BlockId::ancientGreekMusic, "Ancient Greek Music", "Ancient Greek Musical Notation", 0x1D200, 0x1D24F));
    blocks.push_back(Block(BlockId::mayanNumerals, "Mayan Numerals", "Mayan Numerals", 0x1D2E0, 0x1D2FF));
    blocks.push_back(Block(BlockId::taiXuanJing, "Tai Xuan Jing", "Tai Xuan Jing Symbols", 0x1D300, 0x1D35F));
    blocks.push_back(Block(BlockId::countingRod, "Counting Rod", "Counting Rod Numerals", 0x1D360, 0x1D37F));
    blocks.push_back(Block(BlockId::mathAlphanum, "Math Alphanum", "Mathematical Alphanumeric Symbols", 0x1D400, 0x1D7FF));
    blocks.push_back(Block(BlockId::suttonSignWriting, "Sutton SignWriting", "Sutton SignWriting", 0x1D800, 0x1DAAF));
    blocks.push_back(Block(BlockId::glagoliticSup, "Glagolitic Sup", "Glagolitic Supplement", 0x1E000, 0x1E02F));
    blocks.push_back(Block(BlockId::nyiakengPuachueHmong, "Nyiakeng Puachue Hmong", "Nyiakeng Puachue Hmong", 0x1E100, 0x1E14F)); // 12.0
    blocks.push_back(Block(BlockId::wancho, "Wancho", "Wancho", 0x1E2C0, 0x1E2FF)); // 12.0
    blocks.push_back(Block(BlockId::mendeKikakui, "Mende Kikakui", "Mende Kikakui", 0x1E800, 0x1E8DF));
    blocks.push_back(Block(BlockId::adlam, "Adlam", "Adlam", 0x1E900, 0x1E95F));
    blocks.push_back(Block(BlockId::indicSiyaqNumbers, "Indic Siyaq Numbers", "Indic Siyaq Numbers", 0x1EC70, 0x1ECBF));
    blocks.push_back(Block(BlockId::ottomanSiyaqNumbers, "Ottoman Siyaq Numbers", "Ottoman Siyaq Numbers", 0x1ED00, 0x1ED4F)); // 12.0
    blocks.push_back(Block(BlockId::arabicMath, "Arabic Math", "Arabic Mathematical Alphabetic Symbols", 0x1EE00, 0x1EEFF));
    blocks.push_back(Block(BlockId::mahjong, "Mahjong", "Mahjong Tiles", 0x1F000, 0x1F02F));
    blocks.push_back(Block(BlockId::domino, "Domino", "Domino Tiles", 0x1F030, 0x1F09F));
    blocks.push_back(Block(BlockId::playingCards, "Playing Cards", "Playing Cards", 0x1F0A0, 0x1F0FF));
    blocks.push_back(Block(BlockId::enclosedAlphanumSup, "Enclosed Alphanum Sup", "Enclosed Alphanumeric Supplement", 0x1F100, 0x1F1FF));
    blocks.push_back(Block(BlockId::enclosedIdeographicSup, "Enclosed Ideographic Sup", "Enclosed Ideographic Supplement", 0x1F200, 0x1F2FF));
    blocks.push_back(Block(BlockId::miscPictographs, "Misc Pictographs", "Miscellaneous Symbols and Pictographs", 0x1F300, 0x1F5FF));
    blocks.push_back(Block(BlockId::emoticons, "Emoticons", "Emoticons", 0x1F600, 0x1F64F));
    blocks.push_back(Block(BlockId::ornamentalDingbats, "Ornamental Dingbats", "Ornamental Dingbats", 0x1F650, 0x1F67F));
    blocks.push_back(Block(BlockId::transportAndMap, "Transport And Map", "Transport and Map Symbols", 0x1F680, 0x1F6FF));
    blocks.push_back(Block(BlockId::alchemical, "Alchemical", "Alchemical Symbols", 0x1F700, 0x1F77F));
    blocks.push_back(Block(BlockId::geometricShapesExt, "Geometric Shapes Ext", "Geometric Shapes Extended", 0x1F780, 0x1F7FF));
    blocks.push_back(Block(BlockId::supArrowsC, "Sup Arrows C", "Supplemental Arrows-C", 0x1F800, 0x1F8FF));
    blocks.push_back(Block(BlockId::supSymbolsAndPictographs, "Sup Symbols And Pictographs", "Supplemental Symbols and Pictographs", 0x1F900, 0x1F9FF));
    blocks.push_back(Block(BlockId::chessSymbols, "Chess Symbols", "Chess Symbols", 0x1FA00, 0x1FA6F));
    blocks.push_back(Block(BlockId::symbolsAndPictographsExtA, "Symbols And Pictographs Ext A", "Symbols And Pictographs Extended A", 0x1FA70, 0x1FAFF)); // 12.0
    blocks.push_back(Block(BlockId::cjkExtB, "CJK Ext B", "CJK Unified Ideographs Extension B", 0x20000, 0x2A6DF));
    blocks.push_back(Block(BlockId::cjkExtC, "CJK Ext C", "CJK Unified Ideographs Extension C", 0x2A700, 0x2B73F));
    blocks.push_back(Block(BlockId::cjkExtD, "CJK Ext D", "CJK Unified Ideographs Extension D", 0x2B740, 0x2B81F));
    blocks.push_back(Block(BlockId::cjkExtE, "CJK Ext E", "CJK Unified Ideographs Extension E", 0x2B820, 0x2CEAF));
    blocks.push_back(Block(BlockId::cjkExtF, "CJK Ext F", "CJK Unified Ideographs Extension F", 0x2CEB0, 0x2EBEF));
    blocks.push_back(Block(BlockId::cjkCompatIdeographsSup, "CJK Compat Ideographs Sup", "CJK Compatibility Ideographs Supplement", 0x2F800, 0x2FA1F));
    blocks.push_back(Block(BlockId::tags, "Tags", "Tags", 0xE0000, 0xE007F));
    blocks.push_back(Block(BlockId::vsSup, "VS Sup", "Variation Selectors Supplement", 0xE0100, 0xE01EF));
    blocks.push_back(Block(BlockId::supPuaA, "Sup PUA A", "Supplementary Private Use Area-A", 0xF0000, 0xFFFFF));
    blocks.push_back(Block(BlockId::supPuaB, "Sup PUA B", "Supplementary Private Use Area-B", 0x100000, 0x10FFFF));

    for (const Block& block : blocks)
    {
        blockIdMap[block.Id()] = &block;
        shortNameMap[MakeCanonicalPropertyName(block.ShortName())] = &block;
        longNameMap[MakeCanonicalPropertyName(block.LongName())] = &block;
    }
}

std::expected<const Block*, int> BlockTable::GetBlock(BlockId blockId) const
{
    auto it = blockIdMap.find(blockId);
    if (it != blockIdMap.end())
    {
        return std::expected<const Block*, int>(it->second);
    }
    else
    {
        std::string msg("block id ");
        msg.append(std::to_string(static_cast<std::uint16_t>(blockId)));
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const Block*, int> BlockTable::GetBlockByShortName(const std::string& shortName) const
{
    auto it = shortNameMap.find(MakeCanonicalPropertyName(shortName));
    if (it != shortNameMap.end())
    {
        return std::expected<const Block*, int>(it->second);
    }
    else
    {
        std::string msg("block id ");
        msg.append(shortName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const Block*, int> BlockTable::GetBlockByLongName(const std::string& longName) const
{
    auto it = longNameMap.find(MakeCanonicalPropertyName(longName));
    if (it != longNameMap.end())
    {
        return std::expected<const Block*, int>(it->second);
    }
    else
    {
        std::string msg("block id ");
        msg.append(longName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

GeneralCategory::GeneralCategory(GeneralCategoryId id_, const std::string& shortName_, const std::string& longName_) : id(id_), shortName(shortName_), longName(longName_)
{
}

GeneralCategoryTable& GeneralCategoryTable::Instance()
{
    static GeneralCategoryTable instance;
    return instance;
}

GeneralCategoryTable::GeneralCategoryTable()
{
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Lu, "Lu", "Uppercase Letter"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Lu, "Ll", "Lowercase Letter"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Lt, "Lt", "Titlecase Letter"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::LC, "LC", "Cased Letter"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Lm, "Lm", "Modifier Letter"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Lo, "Lo", "Other Letter"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::L, "L", "Letter"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Mn, "Mn", "Nonspacing Mark"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Mc, "Mc", "Spacing Mark"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Me, "Me", "Enclosing Mark"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::M, "M", "Mark"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Nd, "Nd", "Decimal Number"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Nl, "Nl", "Letter Number"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::No, "No", "Other Number"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::N, "N", "Number"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Pc, "Pc", "Connector Punctuation"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Pd, "Pd", "Dash Punctuation"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Ps, "Ps", "Open Punctuation"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Pe, "Pe", "Close Punctuation"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Pi, "Pi", "Initial Punctuation"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Pf, "Pf", "Final Punctuation"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Po, "Po", "Other Punctuation"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::P, "P", "Punctuation"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Sm, "Sm", "Math Symbol"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Sc, "Sc", "Currency Symbol"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Sk, "Sk", "Modifier Symbol"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::So, "So", "Other Symbol"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::S, "S", "Symbol"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Zs, "Zs", "Space Separator"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Zl, "Zl", "Line Separator"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Zp, "Zp", "Paragraph Separator"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Z, "Z", "Separator"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Cc, "Cc", "Control"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Cf, "Cf", "Format"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Cs, "Cs", "Surrogate"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Co, "Co", "Private Use"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::Cn, "Cn", "Unassigned"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::C, "C", "Other"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::G, "G", "Graphic"));
    generalCategories.push_back(GeneralCategory(GeneralCategoryId::B, "B", "Base"));
    for (const GeneralCategory& generalCategory : generalCategories)
    {
        generalCategoryIdMap[generalCategory.Id()] = &generalCategory;
        shortNameMap[MakeCanonicalPropertyName(generalCategory.ShortName())] = &generalCategory;
        longNameMap[MakeCanonicalPropertyName(generalCategory.LongName())] = &generalCategory;
    }
}

std::expected<const GeneralCategory*, int> GeneralCategoryTable::GetGeneralCategory(GeneralCategoryId generalCategoryId) const
{
    auto it = generalCategoryIdMap.find(generalCategoryId);
    if (it != generalCategoryIdMap.end())
    {
        return std::expected<const GeneralCategory*, int>(it->second);
    }
    else
    {
        std::string msg("general category ");
        msg.append(std::to_string(static_cast<std::int32_t>(generalCategoryId)));
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const GeneralCategory*, int> GeneralCategoryTable::GetGeneralCategoryByShortName(const std::string& shortName) const
{
    auto it = shortNameMap.find(MakeCanonicalPropertyName(shortName));
    if (it != shortNameMap.end())
    {
        return std::expected<const GeneralCategory*, int>(it->second);
    }
    else
    {
        std::string msg("general category ");
        msg.append(shortName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const GeneralCategory*, int> GeneralCategoryTable::GetGeneralCategoryByLongName(const std::string& longName) const
{
    auto it = longNameMap.find(MakeCanonicalPropertyName(longName));
    if (it != longNameMap.end())
    {
        return std::expected<const GeneralCategory*, int>(it->second);
    }
    else
    {
        std::string msg("general category ");
        msg.append(longName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

Age::Age(AgeId id_, const std::string& version_) : id(id_), version(version_)
{
}

AgeTable& AgeTable::Instance()
{
    static AgeTable instance;
    return instance;
}

AgeTable::AgeTable()
{
    ages.push_back(Age(AgeId::age_1_1, "1.1"));
    ages.push_back(Age(AgeId::age_2_0, "2.0"));
    ages.push_back(Age(AgeId::age_2_1, "2.1"));
    ages.push_back(Age(AgeId::age_3_0, "3.0"));
    ages.push_back(Age(AgeId::age_3_1, "3.1"));
    ages.push_back(Age(AgeId::age_3_2, "3.2"));
    ages.push_back(Age(AgeId::age_4_0, "4.0"));
    ages.push_back(Age(AgeId::age_4_1, "4.1"));
    ages.push_back(Age(AgeId::age_5_0, "5.0"));
    ages.push_back(Age(AgeId::age_5_1, "5.1"));
    ages.push_back(Age(AgeId::age_5_2, "5.2"));
    ages.push_back(Age(AgeId::age_6_0, "6.0"));
    ages.push_back(Age(AgeId::age_6_1, "6.1"));
    ages.push_back(Age(AgeId::age_6_2, "6.2"));
    ages.push_back(Age(AgeId::age_6_3, "6.3"));
    ages.push_back(Age(AgeId::age_7_0, "7.0"));
    ages.push_back(Age(AgeId::age_8_0, "8.0"));
    ages.push_back(Age(AgeId::age_9_0, "9.0"));
    ages.push_back(Age(AgeId::age_10_0, "10.0"));
    ages.push_back(Age(AgeId::age_11_0, "11.0"));
    ages.push_back(Age(AgeId::age_12_0, "12.0"));
    ages.push_back(Age(AgeId::age_12_1, "12.1"));
    for (const Age& age : ages)
    {
        ageIdMap[age.Id()] = &age;
        versionMap[age.Version()] = &age;
    }
}

std::expected<const Age*, int> AgeTable::GetAge(AgeId id) const
{
    auto it = ageIdMap.find(id);
    if (it != ageIdMap.end())
    {
        return std::expected<const Age*, int>(it->second);
    }
    else
    {
        std::string msg("Unicode age ");
        msg.append(std::to_string(static_cast<std::uint8_t>(id)));
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const Age*, int> AgeTable::GetAge(const std::string& version) const
{
    auto it = versionMap.find(version);
    if (it != versionMap.end())
    {
        return std::expected<const Age*, int>(it->second);
    }
    else
    {
        std::string msg("Unicode age ");
        msg.append(version);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

Script::Script(ScriptId id_, const std::string& shortName_, const std::string& longName_) : id(id_), shortName(shortName_), longName(longName_)
{
}

ScriptTable& ScriptTable::Instance()
{
    static ScriptTable instance;
    return instance;
}

ScriptTable::ScriptTable()
{
    scripts.push_back(Script(ScriptId::adlm, "Adlm", "Adlam"));
    scripts.push_back(Script(ScriptId::aghb, "Aghb", "Caucasian Albanian"));
    scripts.push_back(Script(ScriptId::ahom, "Ahom", "Ahom"));
    scripts.push_back(Script(ScriptId::arab, "Arab", "Arabic"));
    scripts.push_back(Script(ScriptId::armi, "Armi", "Imperial Aramaic"));
    scripts.push_back(Script(ScriptId::armn, "Armn", "Armenian"));
    scripts.push_back(Script(ScriptId::avst, "Avst", "Avestan"));
    scripts.push_back(Script(ScriptId::bali, "Bali", "Balinese"));
    scripts.push_back(Script(ScriptId::bamu, "Bamu", "Bamum"));
    scripts.push_back(Script(ScriptId::bass, "Bass", "Bassa Vah"));
    scripts.push_back(Script(ScriptId::batk, "Batk", "Batak"));
    scripts.push_back(Script(ScriptId::beng, "Beng", "Bengali"));
    scripts.push_back(Script(ScriptId::bhks, "Bhks", "Bhaisuki"));
    scripts.push_back(Script(ScriptId::bopo, "Bopo", "Bopomofo"));
    scripts.push_back(Script(ScriptId::brah, "Brah", "Brahmi"));
    scripts.push_back(Script(ScriptId::brai, "Brai", "Braille"));
    scripts.push_back(Script(ScriptId::bugi, "Bugi", "Buginese"));
    scripts.push_back(Script(ScriptId::buhd, "Buhd", "Buhid"));
    scripts.push_back(Script(ScriptId::cakm, "Cakm", "Chakma"));
    scripts.push_back(Script(ScriptId::cans, "Cans", "Canadian Aboriginal"));
    scripts.push_back(Script(ScriptId::cari, "Cari", "Carian"));
    scripts.push_back(Script(ScriptId::cham, "Cham", "Cham"));
    scripts.push_back(Script(ScriptId::cher, "Cher", "Cherokee"));
    scripts.push_back(Script(ScriptId::copt, "Copt", "Coptic"));
    scripts.push_back(Script(ScriptId::cprt, "Cprt", "Cypriot"));
    scripts.push_back(Script(ScriptId::cyrl, "Cyrl", "Cyrillic"));
    scripts.push_back(Script(ScriptId::deva, "Deva", "Devanagari"));
    scripts.push_back(Script(ScriptId::dogr, "Dogr", "Dogra"));
    scripts.push_back(Script(ScriptId::dsrt, "Dsrt", "Deseret"));
    scripts.push_back(Script(ScriptId::dupl, "Dupl", "Duployan"));
    scripts.push_back(Script(ScriptId::egyp, "Egyp", "Egyptian Hieroglyphs"));
    scripts.push_back(Script(ScriptId::elba, "Elba", "Elbasan"));
    scripts.push_back(Script(ScriptId::elym, "Elym", "Elymaic")); // 12.0
    scripts.push_back(Script(ScriptId::ethi, "Ethi", "Ethiopian"));
    scripts.push_back(Script(ScriptId::geor, "Geor", "Georgian"));
    scripts.push_back(Script(ScriptId::glag, "Glag", "Glagolitic"));
    scripts.push_back(Script(ScriptId::gong, "Gong", "Gunjala Gondi"));
    scripts.push_back(Script(ScriptId::gonm, "Gonm", "Masaram Gondi"));
    scripts.push_back(Script(ScriptId::goth, "Goth", "Gothic"));
    scripts.push_back(Script(ScriptId::gran, "Gran", "Grantha"));
    scripts.push_back(Script(ScriptId::grek, "Grek", "Greek"));
    scripts.push_back(Script(ScriptId::gujr, "Gujr", "Gujarati"));
    scripts.push_back(Script(ScriptId::guru, "Guru", "Gurmukhi"));
    scripts.push_back(Script(ScriptId::hang, "Hang", "Hangul"));
    scripts.push_back(Script(ScriptId::hani, "Hani", "Han"));
    scripts.push_back(Script(ScriptId::hano, "Hano", "Hanunoo"));
    scripts.push_back(Script(ScriptId::hatr, "Hatr", "Hatran"));
    scripts.push_back(Script(ScriptId::hebr, "Hebr", "Hebrew"));
    scripts.push_back(Script(ScriptId::hira, "Hira", "Hiragana"));
    scripts.push_back(Script(ScriptId::hluw, "Hluw", "Anatolian Hieroglyphs"));
    scripts.push_back(Script(ScriptId::hmng, "Hmng", "Pahawh Hmong"));
    scripts.push_back(Script(ScriptId::hmnp, "Hmnp", "Nyiakeng Puachue Hmong")); // 12.0
    scripts.push_back(Script(ScriptId::hrkt, "Hrkt", "Katakana Or Hiragana"));
    scripts.push_back(Script(ScriptId::hung, "Hung", "Old Hungarian"));
    scripts.push_back(Script(ScriptId::ital, "Ital", "Old Italic"));
    scripts.push_back(Script(ScriptId::java, "Java", "Javanese"));
    scripts.push_back(Script(ScriptId::kali, "Kali", "Kayah Li"));
    scripts.push_back(Script(ScriptId::kana, "Kana", "Katakana"));
    scripts.push_back(Script(ScriptId::khar, "Khar", "Kharoshthi"));
    scripts.push_back(Script(ScriptId::khmr, "Khmr", "Khmer"));
    scripts.push_back(Script(ScriptId::khoj, "Khoj", "Khojki"));
    scripts.push_back(Script(ScriptId::knda, "Knda", "Kannada"));
    scripts.push_back(Script(ScriptId::kthi, "Kthi", "Kaithi"));
    scripts.push_back(Script(ScriptId::lana, "Lana", "Tai Tham"));
    scripts.push_back(Script(ScriptId::laoo, "Laoo", "Lao"));
    scripts.push_back(Script(ScriptId::latn, "Latn", "Latin"));
    scripts.push_back(Script(ScriptId::lepc, "Lepc", "Lepcha"));
    scripts.push_back(Script(ScriptId::limb, "Limb", "Limbu"));
    scripts.push_back(Script(ScriptId::lina, "Lina", "Linear A"));
    scripts.push_back(Script(ScriptId::linb, "Linb", "Linear B"));
    scripts.push_back(Script(ScriptId::lisu, "Lisu", "Lisu"));
    scripts.push_back(Script(ScriptId::lyci, "Lyci", "Lycian"));
    scripts.push_back(Script(ScriptId::lydi, "Lydi", "Lydian"));
    scripts.push_back(Script(ScriptId::mahj, "Mahj", "Mahajani"));
    scripts.push_back(Script(ScriptId::maka, "Maka", "Makasar"));
    scripts.push_back(Script(ScriptId::mand, "Mand", "Mandaic"));
    scripts.push_back(Script(ScriptId::mani, "Mani", "Manichaean"));
    scripts.push_back(Script(ScriptId::marc, "Marc", "Marchen"));
    scripts.push_back(Script(ScriptId::medf, "Medf", "Medefaidrin"));
    scripts.push_back(Script(ScriptId::mend, "Mend", "Mende Kikakui"));
    scripts.push_back(Script(ScriptId::merc, "Merc", "Meroitic Cursive"));
    scripts.push_back(Script(ScriptId::mero, "Mero", "Meroitic Hieroglyphs"));
    scripts.push_back(Script(ScriptId::mlym, "Mlym", "Malayalam"));
    scripts.push_back(Script(ScriptId::modi, "Modi", "Modi"));
    scripts.push_back(Script(ScriptId::mong, "Mong", "Mongolian"));
    scripts.push_back(Script(ScriptId::mroo, "Mroo", "Mro"));
    scripts.push_back(Script(ScriptId::mtei, "Mtei", "Meetei Mayak"));
    scripts.push_back(Script(ScriptId::mult, "Mult", "Multani"));
    scripts.push_back(Script(ScriptId::mymr, "Mymr", "Myanmar"));
    scripts.push_back(Script(ScriptId::nand, "Nand", "Nandinagari")); // 12.0
    scripts.push_back(Script(ScriptId::narb, "Narb", "Old North Arabian"));
    scripts.push_back(Script(ScriptId::nbat, "Nbat", "Nabataean"));
    scripts.push_back(Script(ScriptId::newa, "Newa", "Newa"));
    scripts.push_back(Script(ScriptId::nkoo, "Nkoo", "Nko"));
    scripts.push_back(Script(ScriptId::nshu, "Nshu", "Nushu"));
    scripts.push_back(Script(ScriptId::ogam, "Ogam", "Ogham"));
    scripts.push_back(Script(ScriptId::olck, "Olck", "Ol Chiki"));
    scripts.push_back(Script(ScriptId::orkh, "Orkh", "Old Turkic"));
    scripts.push_back(Script(ScriptId::orya, "Orya", "Oriya"));
    scripts.push_back(Script(ScriptId::osge, "Osge", "Osage"));
    scripts.push_back(Script(ScriptId::osma, "Osma", "Osmanya"));
    scripts.push_back(Script(ScriptId::palm, "Palm", "Palmyrene"));
    scripts.push_back(Script(ScriptId::pauc, "Pauc", "Pau Cin Hau"));
    scripts.push_back(Script(ScriptId::perm, "Perm", "Old Permic"));
    scripts.push_back(Script(ScriptId::phag, "Phag", "Phags Pa"));
    scripts.push_back(Script(ScriptId::phli, "Phli", "Inscriptional Pahlavi"));
    scripts.push_back(Script(ScriptId::phlp, "Phlp", "Psalter Pahlavi"));
    scripts.push_back(Script(ScriptId::phnx, "Phnx", "Phoenician"));
    scripts.push_back(Script(ScriptId::plrd, "Plrd", "Miao"));
    scripts.push_back(Script(ScriptId::prti, "Prti", "Inscriptional Parthian"));
    scripts.push_back(Script(ScriptId::rjng, "Rjng", "Rejang"));
    scripts.push_back(Script(ScriptId::rohg, "Rohg", "Hanifi Rohingya"));
    scripts.push_back(Script(ScriptId::runr, "Runr", "Runic"));
    scripts.push_back(Script(ScriptId::samr, "Samr", "Samaritan"));
    scripts.push_back(Script(ScriptId::sarb, "Sarb", "Old South Arabian"));
    scripts.push_back(Script(ScriptId::saur, "Saur", "Saurashtra"));
    scripts.push_back(Script(ScriptId::sgnw, "Sgnw", "SignWriting"));
    scripts.push_back(Script(ScriptId::shaw, "Shaw", "Shawian"));
    scripts.push_back(Script(ScriptId::shrd, "Shrd", "Sharada"));
    scripts.push_back(Script(ScriptId::sidd, "Sidd", "Shiddham"));
    scripts.push_back(Script(ScriptId::sind, "Sind", "Khudawadi"));
    scripts.push_back(Script(ScriptId::sinh, "Sinh", "Sinhala"));
    scripts.push_back(Script(ScriptId::sogd, "Sogd", "Sogdian"));
    scripts.push_back(Script(ScriptId::sogo, "Sogo", "Old Sogdian"));
    scripts.push_back(Script(ScriptId::sora, "Sora", "Sora Sompeng"));
    scripts.push_back(Script(ScriptId::soyo, "Soyo", "Soyombo"));
    scripts.push_back(Script(ScriptId::sund, "Sund", "Sundanese"));
    scripts.push_back(Script(ScriptId::sylo, "Sylo", "Syloti Nagri"));
    scripts.push_back(Script(ScriptId::syrc, "Syrc", "Syriac"));
    scripts.push_back(Script(ScriptId::tagb, "Tagb", "Tagbanwa"));
    scripts.push_back(Script(ScriptId::takr, "Takr", "Takri"));
    scripts.push_back(Script(ScriptId::tale, "Tale", "Tai Le"));
    scripts.push_back(Script(ScriptId::talu, "Talu", "New Tai Lue"));
    scripts.push_back(Script(ScriptId::taml, "Taml", "Tamil"));
    scripts.push_back(Script(ScriptId::tang, "Tang", "Tangut"));
    scripts.push_back(Script(ScriptId::tavt, "Tavt", "Tai Viet"));
    scripts.push_back(Script(ScriptId::telu, "Telu", "Telugu"));
    scripts.push_back(Script(ScriptId::tfng, "Tfng", "Tifinag"));
    scripts.push_back(Script(ScriptId::tglg, "Tglg", "Tagalog"));
    scripts.push_back(Script(ScriptId::thaa, "Thaa", "Thaana"));
    scripts.push_back(Script(ScriptId::thai, "Thai", "Thai"));
    scripts.push_back(Script(ScriptId::tibt, "Tibt", "Tibetan"));
    scripts.push_back(Script(ScriptId::tirh, "Tirh", "Tirhuta"));
    scripts.push_back(Script(ScriptId::ugar, "Ugar", "Ugaritic"));
    scripts.push_back(Script(ScriptId::vaii, "Vaii", "Vai"));
    scripts.push_back(Script(ScriptId::wara, "Wara", "Warang Citi"));
    scripts.push_back(Script(ScriptId::wcho, "Wcho", "Wcho")); // 12.0
    scripts.push_back(Script(ScriptId::xpeo, "Xpeo", "Old Persian"));
    scripts.push_back(Script(ScriptId::xsux, "Xsux", "Cuneiform"));
    scripts.push_back(Script(ScriptId::yiii, "Yiii", "Yi"));
    scripts.push_back(Script(ScriptId::zanb, "Zanb", "Zanabazar Square"));
    scripts.push_back(Script(ScriptId::zinh, "Zinh", "Inherited"));
    scripts.push_back(Script(ScriptId::zyyy, "Zyyy", "Common"));
    scripts.push_back(Script(ScriptId::zzzz, "Zzzz", "Unknown"));

    for (const Script& script : scripts)
    {
        scriptIdMap[script.Id()] = &script;
        shortNameMap[MakeCanonicalPropertyName(script.ShortName())] = &script;
        longNameMap[MakeCanonicalPropertyName(script.LongName())] = &script;
    }
}

std::expected<const Script*, int> ScriptTable::GetScript(ScriptId id) const
{
    auto it = scriptIdMap.find(id);
    if (it != scriptIdMap.end())
    {
        return std::expected<const Script*, int>(it->second);
    }
    else
    {
        std::string msg("script id ");
        msg.append(std::to_string(static_cast<std::uint8_t>(id)));
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const Script*, int> ScriptTable::GetScriptByShortName(const std::string& shortName) const
{
    auto it = shortNameMap.find(MakeCanonicalPropertyName(shortName));
    if (it != shortNameMap.end())
    {
        return std::expected<const Script*, int>(it->second);
    }
    else
    {
        std::string msg("script ");
        msg.append(shortName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const Script*, int> ScriptTable::GetScriptByLongName(const std::string& longName) const
{
    auto it = longNameMap.find(MakeCanonicalPropertyName(longName));
    if (it != longNameMap.end())
    {
        return std::expected<const Script*, int>(it->second);
    }
    else
    {
        std::string msg("script ");
        msg.append(longName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

CharacterInfo::CharacterInfo() :
    binaryProperties(0),
    generalCategory(GeneralCategoryId::none),
    upper(static_cast<char32_t>(0)),
    lower(static_cast<char32_t>(0)),
    title(static_cast<char32_t>(0)),
    folding(static_cast<char32_t>(0)),
    block(),
    age(),
    script()
{
}

std::expected<bool, int> CharacterInfo::Write(BinaryStreamWriter& writer)
{
    std::expected<bool, int> rv = writer.Write(binaryProperties);
    if (!rv) return rv;
    rv = writer.Write(static_cast<std::int32_t>(generalCategory));
    if (!rv) return rv;
    rv = writer.Write(upper);
    if (!rv) return rv;
    rv = writer.Write(lower);
    if (!rv) return rv;
    rv = writer.Write(title);
    if (!rv) return rv;
    rv = writer.Write(folding);
    if (!rv) return rv;
    rv = writer.Write(static_cast<std::uint16_t>(block));
    if (!rv) return rv;
    rv = writer.Write(static_cast<std::uint8_t>(age));
    if (!rv) return rv;
    rv = writer.Write(static_cast<std::uint8_t>(script));
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CharacterInfo::Read(BinaryStreamReader& reader)
{
    std::expected<std::uint64_t, int> rv = reader.ReadULong();
    if (!rv) return std::unexpected<int>(rv.error());
    binaryProperties = *rv;
    std::expected<std::int32_t, int> rvi = reader.ReadInt();
    if (!rvi) return std::unexpected<int>(rvi.error());
    int32_t i = *rvi;
    generalCategory = static_cast<GeneralCategoryId>(i);
    std::expected<char32_t, int> rvu = reader.ReadUChar();
    if (!rvu) return std::unexpected<int>(rvu.error());
    upper = *rvu;
    std::expected<char32_t, int> rvl = reader.ReadUChar();
    if (!rvl) return std::unexpected<int>(rvl.error());
    lower = *rvl;
    std::expected<char32_t, int> rvt = reader.ReadUChar();
    if (!rvt) return std::unexpected<int>(rvt.error());
    title = *rvt;
    std::expected<char32_t, int> rvf = reader.ReadUChar();
    if (!rvf) return std::unexpected<int>(rvf.error());
    folding = *rvf;
    std::expected<std::uint16_t, int> rvs = reader.ReadUShort();
    if (!rvs) return std::unexpected<int>(rvs.error());
    std::uint16_t bi = *rvs;
    block = static_cast<BlockId>(bi);
    std::expected<std::uint8_t, int> rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    std::uint8_t ai = *rvb;
    age = static_cast<AgeId>(ai);
    rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    ai = *rvb;
    script = static_cast<ScriptId>(ai);
    return std::expected<bool, int>(true);
}

NumericType::NumericType(NumericTypeId id_, const std::string& shortName_, const std::string& longName_) : id(id_), shortName(shortName_), longName(longName_)
{
}

NumericTypeTable& NumericTypeTable::Instance()
{
    static NumericTypeTable instance;
    return instance;
}

NumericTypeTable::NumericTypeTable()
{
    numericTypes.push_back(NumericType(NumericTypeId::none, "None", "None"));
    numericTypes.push_back(NumericType(NumericTypeId::de, "De", "Decimal"));
    numericTypes.push_back(NumericType(NumericTypeId::di, "Di", "Digit"));
    numericTypes.push_back(NumericType(NumericTypeId::nu, "Nu", "Numeric"));
    for (const NumericType& numericType : numericTypes)
    {
        numericTypeMap[numericType.Id()] = &numericType;
        shortNameMap[MakeCanonicalPropertyName(numericType.ShortName())] = &numericType;
        longNameMap[MakeCanonicalPropertyName(numericType.LongName())] = &numericType;;
    }
}

std::expected<const NumericType*, int> NumericTypeTable::GetNumericType(NumericTypeId id) const
{
    auto it = numericTypeMap.find(id);
    if (it != numericTypeMap.end())
    {
        return std::expected<const NumericType*, int>(it->second);
    }
    else
    {
        std::string msg("numeric type ");
        msg.append(std::to_string(static_cast<std::uint8_t>(id)));
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const NumericType*, int> NumericTypeTable::GetNumericTypeByShortName(const std::string& shortName) const
{
    auto it = shortNameMap.find(MakeCanonicalPropertyName(shortName));
    if (it != shortNameMap.end())
    {
        return std::expected<const NumericType*, int>(it->second);
    }
    else
    {
        std::string msg("numeric type ");
        msg.append(shortName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const NumericType*, int> NumericTypeTable::GetNumericTypeByLongName(const std::string& longName) const
{
    auto it = longNameMap.find(MakeCanonicalPropertyName(longName));
    if (it != longNameMap.end())
    {
        return std::expected<const NumericType*, int>(it->second);
    }
    else
    {
        std::string msg("numeric type ");
        msg.append(longName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

BidiClass::BidiClass(BidiClassId id_, const std::string& shortName_, const std::string& longName_) : id(id_), shortName(shortName_), longName(longName_)
{
}

BidiClassTable& BidiClassTable::Instance()
{
    static BidiClassTable instance;
    return instance;
}

BidiClassTable::BidiClassTable()
{
    bidiClasses.push_back(BidiClass(BidiClassId::al, "AL", "Arabic Letter"));
    bidiClasses.push_back(BidiClass(BidiClassId::an, "AN", "Arabic Number"));
    bidiClasses.push_back(BidiClass(BidiClassId::b, "B", "Paragraph Separator"));
    bidiClasses.push_back(BidiClass(BidiClassId::bn, "BN", "Boundary Neutral"));
    bidiClasses.push_back(BidiClass(BidiClassId::cs, "CS", "Common Separator"));
    bidiClasses.push_back(BidiClass(BidiClassId::en, "EN", "European Number"));
    bidiClasses.push_back(BidiClass(BidiClassId::es, "ES", "European Separator"));
    bidiClasses.push_back(BidiClass(BidiClassId::et, "ET", "European Terminator"));
    bidiClasses.push_back(BidiClass(BidiClassId::fsi, "FSI", "First Strong Isolate"));
    bidiClasses.push_back(BidiClass(BidiClassId::l, "L", "Left To Right"));
    bidiClasses.push_back(BidiClass(BidiClassId::lre, "LRE", "Left To Right Embedding"));
    bidiClasses.push_back(BidiClass(BidiClassId::lri, "LRI", "Left To Right Isolate"));
    bidiClasses.push_back(BidiClass(BidiClassId::lro, "LRO", "Left To Right Override"));
    bidiClasses.push_back(BidiClass(BidiClassId::nsm, "NSM", "Nonspacing Mark"));
    bidiClasses.push_back(BidiClass(BidiClassId::on, "ON", "Other Neutral"));
    bidiClasses.push_back(BidiClass(BidiClassId::pdf, "PDF", "Pop Directional Format"));
    bidiClasses.push_back(BidiClass(BidiClassId::pdi, "PDI", "Pop Directional Isolate"));
    bidiClasses.push_back(BidiClass(BidiClassId::r, "R", "Right To Left"));
    bidiClasses.push_back(BidiClass(BidiClassId::rle, "RLE", "Right To Left Embedding"));
    bidiClasses.push_back(BidiClass(BidiClassId::rli, "RLI", "Right To Left Isolate"));
    bidiClasses.push_back(BidiClass(BidiClassId::rlo, "RLO", "Right To Left Override"));
    bidiClasses.push_back(BidiClass(BidiClassId::s, "S", "Segment Separator"));
    bidiClasses.push_back(BidiClass(BidiClassId::ws, "WS", "White Space"));

    for (const BidiClass& bidiClass : bidiClasses)
    {
        bidiClassMap[bidiClass.Id()] = &bidiClass;
        shortNameMap[MakeCanonicalPropertyName(bidiClass.ShortName())] = &bidiClass;
        longNameMap[MakeCanonicalPropertyName(bidiClass.LongName())] = &bidiClass;
    }
}

std::expected<const BidiClass*, int> BidiClassTable::GetBidiClass(BidiClassId id) const
{
    auto it = bidiClassMap.find(id);
    if (it != bidiClassMap.end())
    {
        return std::expected<const BidiClass*, int>(it->second);
    }
    else
    {
        std::string msg("bidi class ");
        msg.append(std::to_string(static_cast<std::uint8_t>(id)));
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const BidiClass*, int> BidiClassTable::GetBidiClassByShortName(const std::string& shortName) const
{
    auto it = shortNameMap.find(MakeCanonicalPropertyName(shortName));
    if (it != shortNameMap.end())
    {
        return std::expected<const BidiClass*, int>(it->second);
    }
    else
    {
        std::string msg("bidi class ");
        msg.append(shortName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const BidiClass*, int> BidiClassTable::GetBidiClassByLongName(const std::string& longName) const
{
    auto it = longNameMap.find(MakeCanonicalPropertyName(longName));
    if (it != longNameMap.end())
    {
        return std::expected<const BidiClass*, int>(it->second);
    }
    else
    {
        std::string msg("bidi class ");
        msg.append(longName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

BidiPairedBracketType::BidiPairedBracketType(BidiPairedBracketTypeId id_, const std::string& shortName_, const std::string& longName_) : id(id_), shortName(shortName_), longName(longName_)
{
}

BidiPairedBracketTypeTable& BidiPairedBracketTypeTable::Instance()
{
    static BidiPairedBracketTypeTable instance;
    return instance;
}

BidiPairedBracketTypeTable::BidiPairedBracketTypeTable()
{
    bidiPairedBracketTypes.push_back(BidiPairedBracketType(BidiPairedBracketTypeId::o, "O", "Open"));
    bidiPairedBracketTypes.push_back(BidiPairedBracketType(BidiPairedBracketTypeId::c, "C", "Close"));
    bidiPairedBracketTypes.push_back(BidiPairedBracketType(BidiPairedBracketTypeId::none, "N", "None"));
    for (const BidiPairedBracketType& type : bidiPairedBracketTypes)
    {
        typeMap[type.Id()] = &type;
        shortNameMap[MakeCanonicalPropertyName(type.ShortName())] = &type;
        longNameMap[MakeCanonicalPropertyName(type.LongName())] = &type;
    }
}

std::expected<const BidiPairedBracketType*, int> BidiPairedBracketTypeTable::GetBidiPairedBracketType(BidiPairedBracketTypeId id) const
{
    auto it = typeMap.find(id);
    if (it != typeMap.end())
    {
        return std::expected<const BidiPairedBracketType*, int>(it->second);
    }
    else
    {
        std::string msg("Bidi paired bracket type ");
        msg.append(std::to_string(static_cast<std::uint8_t>(id)));
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const BidiPairedBracketType*, int> BidiPairedBracketTypeTable::GetBidiPairedBracketTypeByShortName(const std::string& shortName) const
{
    auto it = shortNameMap.find(MakeCanonicalPropertyName(shortName));
    if (it != shortNameMap.end())
    {
        return std::expected<const BidiPairedBracketType*, int>(it->second);
    }
    else
    {
        std::string msg("Bidi paired bracket type ");
        msg.append(shortName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const BidiPairedBracketType*, int> BidiPairedBracketTypeTable::GetBidiPairedBracketTypeByLongName(const std::string& longName) const
{
    auto it = longNameMap.find(MakeCanonicalPropertyName(longName));
    if (it != longNameMap.end())
    {
        return std::expected<const BidiPairedBracketType*, int>(it->second);
    }
    else
    {
        std::string msg("Bidi paired bracket type ");
        msg.append(longName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

AliasType::AliasType(AliasTypeId id_, const std::string& name_) : id(id_), name(name_)
{
}

AliasTypeTable& AliasTypeTable::Instance()
{
    static AliasTypeTable instance;
    return instance;
}

AliasTypeTable::AliasTypeTable()
{
    aliasTypes.push_back(AliasType(AliasTypeId::abbreviation, "abbreviation"));
    aliasTypes.push_back(AliasType(AliasTypeId::alternate, "alternate"));
    aliasTypes.push_back(AliasType(AliasTypeId::control, "control"));
    aliasTypes.push_back(AliasType(AliasTypeId::correction, "correction"));
    aliasTypes.push_back(AliasType(AliasTypeId::figment, "figment"));
    for (const AliasType& aliasType : aliasTypes)
    {
        aliasTypeMap[aliasType.Id()] = &aliasType;
        typeNameMap[aliasType.Name()] = &aliasType;
    }
}

std::expected<const AliasType*, int> AliasTypeTable::GetAliasType(AliasTypeId id) const
{
    auto it = aliasTypeMap.find(id);
    if (it != aliasTypeMap.end())
    {
        return std::expected<const AliasType*, int>(it->second);
    }
    else
    {
        std::string msg("alias type ");
        msg.append(std::to_string(static_cast<std::uint8_t>(id)));
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

std::expected<const AliasType*, int> AliasTypeTable::GetAliasType(const std::string& typeName) const
{
    auto it = typeNameMap.find(MakeCanonicalPropertyName(typeName));
    if (it != typeNameMap.end())
    {
        return std::expected<const AliasType*, int>(it->second);
    }
    else
    {
        std::string msg("alias type ");
        msg.append(typeName);
        msg.append(" not found");
        return UnicodeError(msg);
    }
}

Alias::Alias() : typeId(), name()
{
}

Alias::Alias(AliasTypeId typeId_, const std::string& name_) : typeId(typeId_), name(name_)
{
}

std::expected<bool, int> Alias::Write(BinaryStreamWriter& writer)
{
    std::expected<bool, int> rv = writer.Write(static_cast<std::uint8_t>(typeId));
    if (!rv) return rv;
    rv = writer.Write(name);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Alias::Read(BinaryStreamReader& reader)
{
    std::expected<std::uint8_t, int> rv = reader.ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t ai = *rv;
    typeId = static_cast<AliasTypeId>(ai);
    std::expected<std::string, int> srv = reader.ReadUtf8String();
    if (!srv) return std::unexpected<int>(srv.error());
    name = *srv;
    return std::expected<bool, int>(true);
}

ExtendedCharacterInfo::ExtendedCharacterInfo() :
    characterName(), unicode1Name(), canonicalCombiningClass(0), fullUpper(), fullLower(), fullTitle(), fullFolding(), bidiClass(),
    numericType(), numericValue(), bidiPairedBracketType(), bidiMirroringGlyph(0), bidiPairedBracket(0)
{
}

void ExtendedCharacterInfo::SetCharacterName(const std::string& characterName_)
{
    characterName = characterName_;
}

void ExtendedCharacterInfo::SetUnicode1Name(const std::string& unicode1Name_)
{
    unicode1Name = unicode1Name_;
}

std::expected<bool, int> ExtendedCharacterInfo::Write(BinaryStreamWriter& writer)
{
    std::expected<bool, int> rv = writer.Write(characterName);
    if (!rv) return rv;
    rv = writer.Write(unicode1Name);
    if (!rv) return rv;
    rv = writer.Write(static_cast<std::uint8_t>(canonicalCombiningClass));
    if (!rv) return rv;
    std::uint8_t nu = static_cast<std::uint8_t>(fullUpper.length());
    rv = writer.Write(nu);
    if (!rv) return rv;
    for (std::uint8_t i = 0; i < nu; ++i)
    {
        rv = writer.Write(fullUpper[i]);
        if (!rv) return rv;
    }
    std::uint8_t nl = static_cast<std::uint8_t>(fullLower.length());
    rv = writer.Write(nl);
    if (!rv) return rv;
    for (std::uint8_t i = 0; i < nl; ++i)
    {
        rv = writer.Write(fullLower[i]);
        if (!rv) return rv;
    }
    std::uint8_t nt = static_cast<std::uint8_t>(fullTitle.length());
    rv = writer.Write(nt);
    if (!rv) return rv;
    for (std::uint8_t i = 0; i < nt; ++i)
    {
        rv = writer.Write(fullTitle[i]);
        if (!rv) return rv;
    }
    std::uint8_t nf = static_cast<std::uint8_t>(fullFolding.length());
    rv = writer.Write(nf);
    if (!rv) return rv;
    for (std::uint8_t i = 0; i < nf; ++i)
    {
        rv = writer.Write(fullFolding[i]);
        if (!rv) return rv;
    }
    rv = writer.Write(static_cast<std::uint8_t>(bidiClass));
    if (!rv) return rv;
    rv = writer.Write(static_cast<std::uint8_t>(numericType));
    if (!rv) return rv;
    rv = writer.Write(numericValue);
    if (!rv) return rv;
    std::uint8_t na = static_cast<std::uint8_t>(aliases.size());
    rv = writer.Write(na);
    if (!rv) return rv;
    for (std::uint8_t i = 0; i < na; ++i)
    {
        rv = aliases[i].Write(writer);
        if (!rv) return rv;
    }
    rv = writer.Write(bidiMirroringGlyph);
    if (!rv) return rv;
    rv = writer.Write(static_cast<std::uint8_t>(bidiPairedBracketType));
    if (!rv) return rv;
    rv = writer.Write(bidiPairedBracket);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExtendedCharacterInfo::Read(BinaryStreamReader& reader)
{
    std::expected<std::string, int> rvs = reader.ReadUtf8String();
    if (!rvs) return std::unexpected<int>(rvs.error());
    characterName = *rvs;
    rvs = reader.ReadUtf8String();
    if (!rvs) return std::unexpected<int>(rvs.error());
    unicode1Name = *rvs;
    std::expected<uint8_t, int> rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    canonicalCombiningClass = *rvb;
    rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    std::uint8_t nu = *rvb;
    for (std::uint8_t i = 0; i < nu; ++i)
    {
        std::expected<char32_t, int> rvu = reader.ReadUChar();
        if (!rvu) return std::unexpected<int>(rvu.error());
        fullUpper.append(1, *rvu);
    }
    rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    std::uint8_t nl = *rvb;
    for (std::uint8_t i = 0; i < nl; ++i)
    {
        std::expected<char32_t, int> rvu = reader.ReadUChar();
        if (!rvu) return std::unexpected<int>(rvu.error());
        fullLower.append(1, *rvu);
    }
    rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    std::uint8_t nt = *rvb;
    for (std::uint8_t i = 0; i < nt; ++i)
    {
        std::expected<char32_t, int> rvu = reader.ReadUChar();
        if (!rvu) return std::unexpected<int>(rvu.error());
        fullTitle.append(1, *rvu);
    }
    rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    std::uint8_t nf = *rvb;
    for (std::uint8_t i = 0; i < nf; ++i)
    {
        std::expected<char32_t, int> rvu = reader.ReadUChar();
        if (!rvu) return std::unexpected<int>(rvu.error());
        fullFolding.append(1, *rvu);
    }
    rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    std::uint8_t bi = *rvb;
    bidiClass = static_cast<BidiClassId>(bi);
    rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    bi = *rvb;
    numericType = static_cast<NumericTypeId>(bi);
    rvs = reader.ReadUtf8String();
    if (!rvs) return std::unexpected<int>(rvs.error());
    numericValue = *rvs;
    rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    std::uint8_t na = *rvb;
    for (std::uint8_t i = 0; i < na; ++i)
    {
        Alias alias;
        std::expected<bool, int> rv = alias.Read(reader);
        if (!rv) return std::unexpected<int>(rv.error());
        aliases.push_back(alias);
    }
    std::expected<char32_t, int> rvu = reader.ReadUChar();
    if (!rvu) return std::unexpected<int>(rvu.error());
    bidiMirroringGlyph = *rvu;
    rvb = reader.ReadByte();
    if (!rvb) return std::unexpected<int>(rvb.error());
    bi = *rvb;
    bidiPairedBracketType = static_cast<BidiPairedBracketTypeId>(bi);
    rvu = reader.ReadUChar();
    if (!rvu) return std::unexpected<int>(rvu.error());
    bidiPairedBracket = *rvu;
    return std::expected<bool, int>(true);
}

CharacterInfoPage::CharacterInfoPage()
{
    characterInfos.resize(numInfosInPage);
}

std::expected<const CharacterInfo*, int> CharacterInfoPage::GetCharacterInfo(int index) const
{
    if (index < 0 || index > characterInfos.size())
    {
        return UnicodeError("invalid character info index");
    }
    return std::expected<const CharacterInfo*, int>(&characterInfos[index]);
}

std::expected<CharacterInfo*, int> CharacterInfoPage::GetCharacterInfo(int index)
{
    if (index < 0 || index > characterInfos.size())
    {
        return UnicodeError("invalid character info index");
    }
    return std::expected<CharacterInfo*, int>(&characterInfos[index]);
}

std::expected<bool, int> CharacterInfoPage::Write(BinaryStreamWriter& writer)
{
    for (int i = 0; i < characterInfos.size(); ++i)
    {
        CharacterInfo& info = characterInfos[i];
        std::expected<bool, int> rv = info.Write(writer);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CharacterInfoPage::Read(BinaryStreamReader& reader)
{
    for (int i = 0; i < characterInfos.size(); ++i)
    {
        CharacterInfo& info = characterInfos[i];
        std::expected<bool, int> rv = info.Read(reader);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

ExtendedCharacterInfoPage::ExtendedCharacterInfoPage()
{
    extendedCharacterInfos.resize(numInfosInPage);
}

std::expected<const ExtendedCharacterInfo*, int> ExtendedCharacterInfoPage::GetExtendedCharacterInfo(int index) const
{
    if (index < 0 || index > extendedCharacterInfos.size())
    {
        return UnicodeError("invalid extended character info index");
    }
    return std::expected<const ExtendedCharacterInfo*, int>(&extendedCharacterInfos[index]);
}

std::expected<ExtendedCharacterInfo*, int> ExtendedCharacterInfoPage::GetExtendedCharacterInfo(int index)
{
    if (index < 0 || index > extendedCharacterInfos.size())
    {
        return UnicodeError("invalid extended character info index");
    }
    return std::expected<ExtendedCharacterInfo*, int>(&extendedCharacterInfos[index]);
}

std::expected<bool, int> ExtendedCharacterInfoPage::Write(BinaryStreamWriter& writer)
{
    int n = static_cast<int>(extendedCharacterInfos.size());
    for (int i = 0; i < n; ++i)
    {
        std::expected<bool, int> rv = extendedCharacterInfos[i].Write(writer);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExtendedCharacterInfoPage::Read(BinaryStreamReader& reader)
{
    int n = static_cast<int>(extendedCharacterInfos.size());
    for (int i = 0; i < n; ++i)
    {
        std::expected<bool, int> rv = extendedCharacterInfos[i].Read(reader);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

void ExtendedCharacterInfoHeader::AllocatePages(int numExtendedPages)
{
    extendedPageStarts.resize(numExtendedPages);
}

std::expected<bool, int> ExtendedCharacterInfoHeader::Write(BinaryStreamWriter& writer)
{
    std::int32_t n = static_cast<int32_t>(extendedPageStarts.size());
    std::expected<bool, int> rv = writer.Write(n);
    if (!rv) return rv;
    for (std::int32_t i = 0; i < n; ++i)
    {
        std::expected<bool, int> rv = writer.Write(extendedPageStarts[i]);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExtendedCharacterInfoHeader::Read(BinaryStreamReader& reader)
{
    std::expected<std::uint32_t, int> rv = reader.ReadUInt();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint32_t nn = *rv;
    std::int32_t n = static_cast<std::int32_t>(nn);
    for (std::int32_t i = 0; i < n; ++i)
    {
        rv = reader.ReadUInt();
        if (!rv) return std::unexpected<int>(rv.error());
        std::uint32_t start = *rv;
        extendedPageStarts.push_back(start);
    }
    return std::expected<bool, int>(true);
}

std::expected<std::uint32_t, int> ExtendedCharacterInfoHeader::GetPageStart(int pageIndex) const
{
    if (pageIndex < 0 || pageIndex >= extendedPageStarts.size())
    {
        std::string msg("invalid extended page index");
        msg.append(std::to_string(pageIndex));
        return UnicodeError(msg);
    }
    return std::expected<std::uint32_t, int>(extendedPageStarts[pageIndex]);
}

std::expected<bool, int> ExtendedCharacterInfoHeader::SetPageStart(int pageIndex, std::uint32_t extendedPageStart)
{
    if (pageIndex < 0 || pageIndex >= extendedPageStarts.size())
    {
        std::string msg("invalid extended page index");
        msg.append(std::to_string(pageIndex));
        return UnicodeError(msg);
    }
    extendedPageStarts[pageIndex] = extendedPageStart;
    return std::expected<bool, int>(true);
}

std::vector<std::uint8_t> headerMagic;

struct InitHeaderMagic
{
    InitHeaderMagic();
};

InitHeaderMagic::InitHeaderMagic()
{
    headerMagic.resize(8);
    headerMagic[0] = 'S';
    headerMagic[1] = 'O';
    headerMagic[2] = 'U';
    headerMagic[3] = 'L';
    headerMagic[4] = 'U';
    headerMagic[5] = 'C';
    headerMagic[6] = 'D';
    int version = current_soul_ucd_version;
    headerMagic[7] = static_cast<char>('0' + version);
}

InitHeaderMagic initHeaderMagic;

CharacterTable& CharacterTable::Instance()
{
    static CharacterTable instance;
    return instance;
}

CharacterTable::CharacterTable() :
    dataSource(CharacterTableDataSource::file), data(nullptr), size(0), headerRead(false), extendedHeaderStart(0), extendedHeaderEnd(0), extendedHeaderRead(false), headerSize(4096)
{
}

std::expected<std::string, int> CharacterTable::FilePath() const
{
    std::expected<std::string, int> rv = SoulUcdFilePath();
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<std::string, int>(*rv);;
}

std::expected<std::string, int> CharacterTable::DeflateFilePath() const
{
    std::expected<std::string, int> rv = FilePath();
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<std::string, int>(Path::ChangeExtension(*rv, ".deflate.bin"));
}

void CharacterTable::SetData(std::uint8_t* data_, std::int64_t size_)
{
    data = data_;
    size = size_;
    dataSource = CharacterTableDataSource::memory;
}

std::expected<std::int64_t, int> CharacterTable::GetUncompressedFileSize() const
{
    std::expected<std::string, int> rv = FilePath();
    if (!rv) return std::unexpected<int>(rv.error());
    std::string ucdFilePath = *rv;
    return std::expected<std::int64_t, int>(ort_file_size(ucdFilePath.c_str()));
}

std::expected<Streams, int> CharacterTable::GetReadStreams()
{
    Streams streams;
    if (dataSource == CharacterTableDataSource::file)
    {
        std::expected<std::string, int> rv = FilePath();
        if (!rv) return std::unexpected<int>(rv.error());
        std::string ucdFilePath = *rv;
        FileStream* fs = new FileStream(ucdFilePath, OpenMode::read | OpenMode::binary);
        if (!fs->Valid()) return std::unexpected<int>(fs->Error());
        streams.Add(fs);
        std::expected<Stream*, int> backRv = streams.Back();
        if (!backRv) return std::unexpected<int>(backRv.error());
        Stream* s = *backRv;
        BufferedStream* bs = new BufferedStream(*s);
        streams.Add(bs);
    }
    else if (dataSource == CharacterTableDataSource::memory)
    {
        streams.Add(new MemoryStream(data, size));
    }
    return std::expected<Streams, int>(std::move(streams));
}

std::expected<bool, int> CharacterTable::Write()
{
    std::expected<std::string, int> fpr = FilePath();
    if (!fpr) return std::unexpected<int>(fpr.error());
    std::string ucdFilePath = *fpr;
    FileStream file(ucdFilePath, OpenMode::write | OpenMode::binary);
    if (!file.Valid()) return std::unexpected<int>(file.Error());
    BufferedStream bufferedFile(file);
    BinaryStreamWriter writer(bufferedFile);
    std::expected<bool, int> rv = WriteHeader(writer);
    if (!rv) return rv;
    rv = writer.GetStream().Seek(headerSize, Origin::seekSet);
    if (!rv) return rv;
    int n = static_cast<int>(pages.size());
    for (int i = 0; i < n; ++i)
    {
        CharacterInfoPage* page = pages[i].get();
        rv = page->Write(writer);
        if (!rv) return rv;
    }
    extendedHeaderStart = static_cast<std::uint32_t>(writer.Position());
    int nx = static_cast<int>(extendedPages.size());
    extendedHeader.AllocatePages(nx);
    rv = extendedHeader.Write(writer);
    if (!rv) return rv;
    extendedHeaderEnd = static_cast<std::uint32_t>(writer.Position());
    for (int i = 0; i < nx; ++i)
    {
        std::expected<bool, int> rv = extendedHeader.SetPageStart(i, static_cast<std::uint32_t>(writer.Position()));
        if (!rv) return rv;
        ExtendedCharacterInfoPage* extendedPage = extendedPages[i].get();
        rv = extendedPage->Write(writer);
        if (!rv) return rv;
    }
    rv = writer.GetStream().Seek(extendedHeaderStart, Origin::seekSet);
    if (!rv) return rv;
    rv = extendedHeader.Write(writer);
    if (!rv) return rv;
    rv = writer.GetStream().Seek(0, Origin::seekSet);
    if (!rv) return rv;
    rv = WriteHeader(writer);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CharacterTable::WriteHeader(BinaryStreamWriter& writer)
{
    for (int i = 0; i < 8; ++i)
    {
        std::expected<bool, int> rv = writer.Write(headerMagic[i]);
        if (!rv) return rv;
    }
    std::expected<bool, int> rv = writer.Write(std::uint32_t(extendedHeaderStart));
    if (!rv) return rv;
    rv = writer.Write(std::uint32_t(extendedHeaderEnd));
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CharacterTable::ReadHeader(BinaryStreamReader& reader)
{
    headerRead = true;
    std::uint8_t magic[8];
    for (int i = 0; i < 8; ++i)
    {
        std::expected<uint8_t, int> rv = reader.ReadByte();
        if (!rv) return std::unexpected<int>(rv.error());
        magic[i] = *rv;
    }
    for (int i = 0; i < 7; ++i)
    {
        if (magic[i] != headerMagic[i])
        {
            return UnicodeError("invalid soul_ucd.bin header magic: 'SOULUCD' expected");
        }
    }
    if (magic[7] != headerMagic[7])
    {
        std::string msg("invalid soul_ucd.bin version: version ");
        msg.append(std::string(1, headerMagic[7]));
        msg.append(" expected, version ");
        msg.append(std::string(1, magic[7]));
        msg.append(" read");
        return UnicodeError(msg);
    }
    std::expected<uint32_t, int> urv = reader.ReadUInt();
    if (!urv) return std::unexpected<int>(urv.error());
    extendedHeaderStart = *urv;
    urv = reader.ReadUInt();
    if (!urv) return std::unexpected<int>(urv.error());
    extendedHeaderEnd = *urv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CharacterTable::ReadExtendedHeader(BinaryStreamReader& reader)
{
    extendedHeaderRead = true;
    std::expected<bool, int> rv = extendedHeader.Read(reader);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::mutex mtx;

std::expected<const CharacterInfo*, int> CharacterTable::GetCharacterInfo(char32_t codePoint) const
{
    if (codePoint > char32_t(0x10FFFFu))
    {
        std::string msg("invalid Unicode code point ");
        msg.append(std::to_string(codePoint));
        return UnicodeError(msg);
    }
    int pageIndex = static_cast<int>(codePoint) / numInfosInPage;
    if (pages.size() <= pageIndex)
    {
        std::lock_guard<std::mutex> lock(mtx);
        while (pages.size() <= pageIndex)
        {
            pages.push_back(std::unique_ptr<CharacterInfoPage>());
        }
    }
    CharacterInfoPage* page = pages[pageIndex].get();
    if (!page)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (!page)
        {
            std::expected<Streams, int> rvs = GetReadStreams();
            if (!rvs) return std::unexpected<int>(rvs.error());
            Streams streams = std::move(*rvs);
            std::expected<Stream*, int> srv = streams.Back();
            if (!srv) return std::unexpected<int>(srv.error());
            Stream* s = *srv;
            BinaryStreamReader reader(*s);
            std::uint32_t pageStart = static_cast<std::uint32_t>(headerSize + characterInfoPageSize * pageIndex);
            if (!headerRead)
            {
                std::expected<bool, int> rv = ReadHeader(reader);
                if (!rv) return std::unexpected<int>(rv.error());
            }
            std::expected<bool, int> rv = reader.GetStream().Seek(pageStart, Origin::seekSet);
            if (!rv) return std::unexpected<int>(rv.error());
            page = new CharacterInfoPage();
            rv = page->Read(reader);
            if (!rv) return std::unexpected<int>(rv.error());
            pages[pageIndex] = std::move(std::unique_ptr<CharacterInfoPage>(page));
        }
    }
    int infoIndex = static_cast<int>(codePoint) % numInfosInPage;
    const CharacterInfoPage* constPage = page;
    std::expected<const CharacterInfo*, int> rv = constPage->GetCharacterInfo(infoIndex);
    if (!rv) return std::unexpected<int>(rv.error());
    return rv;
}

std::expected<CharacterInfo*, int> CharacterTable::CreateCharacterInfo(char32_t codePoint)
{
    if (codePoint > char32_t(0x10FFFFu))
    {
        std::string msg("invalid Unicode code point ");
        msg.append(std::to_string(codePoint));
        return UnicodeError(msg);
    }
    int pageIndex = static_cast<int>(codePoint) / numInfosInPage;
    while (pages.size() <= pageIndex)
    {
        pages.push_back(std::unique_ptr<CharacterInfoPage>(new CharacterInfoPage()));
    }
    int infoIndex = static_cast<int>(codePoint) % numInfosInPage;
    CharacterInfoPage* page = pages[pageIndex].get();
    return page->GetCharacterInfo(infoIndex);
}

std::expected<const ExtendedCharacterInfo*, int> CharacterTable::GetExtendedCharacterInfo(char32_t codePoint) const
{
    if (codePoint > char32_t(0x10FFFFu))
    {
        std::string msg("invalid Unicode code point ");
        msg.append(std::to_string(codePoint));
        return UnicodeError(msg);
    }
    int pageIndex = static_cast<int>(codePoint) / numInfosInPage;
    if (extendedPages.size() <= pageIndex)
    {
        std::lock_guard<std::mutex> lock(mtx);
        while (extendedPages.size() <= pageIndex)
        {
            extendedPages.push_back(std::unique_ptr<ExtendedCharacterInfoPage>());
        }
    }
    ExtendedCharacterInfoPage* extendedPage = extendedPages[pageIndex].get();
    if (!extendedPage)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (!extendedPage)
        {
            std::expected<Streams, int> srv = GetReadStreams();
            if (!srv) return std::unexpected<int>(srv.error());
            Streams streams = std::move(*srv);
            std::expected<Stream*, int> brv = streams.Back();
            if (!brv) return std::unexpected<int>(brv.error());
            Stream* back = *brv;
            BinaryStreamReader reader(*back);
            if (!headerRead)
            {
                std::expected<bool, int> rv = ReadHeader(reader);
                if (!rv) return std::unexpected<int>(rv.error());
            }
            if (!extendedHeaderRead)
            {
                std::expected<bool, int> rv = reader.GetStream().Seek(extendedHeaderStart, Origin::seekSet);
                if (!rv) return std::unexpected<int>(rv.error());
                rv = ReadExtendedHeader(reader);
                if (!rv) return std::unexpected<int>(rv.error());
            }
            std::expected<std::uint32_t, int> prv = extendedHeader.GetPageStart(pageIndex);
            if (!prv) return std::unexpected<int>(prv.error());
            std::uint32_t pageStart = *prv;
            std::expected<bool, int> rv = reader.GetStream().Seek(pageStart, Origin::seekSet);
            if (!rv) return std::unexpected<int>(rv.error());
            extendedPage = new ExtendedCharacterInfoPage();
            rv = extendedPage->Read(reader);
            if (!rv) return std::unexpected<int>(rv.error());
            extendedPages[pageIndex] = std::move(std::unique_ptr<ExtendedCharacterInfoPage>(extendedPage));
        }
    }
    int infoIndex = static_cast<int>(codePoint) % numInfosInPage;
    const ExtendedCharacterInfoPage* constExtendedPage = extendedPage;
    std::expected<const ExtendedCharacterInfo*, int> rv = constExtendedPage->GetExtendedCharacterInfo(infoIndex);
    if (!rv) return std::unexpected<int>(rv.error());
    return rv;
}

std::expected<ExtendedCharacterInfo*, int> CharacterTable::CreateExtendedCharacterInfo(char32_t codePoint)
{
    if (codePoint > char32_t(0x10FFFFu))
    {
        std::string msg("invalid Unicode code point ");
        msg.append(std::to_string(codePoint));
        return UnicodeError(msg);
    }
    int pageIndex = static_cast<int>(codePoint) / numInfosInPage;
    while (extendedPages.size() <= pageIndex)
    {
        extendedPages.push_back(std::unique_ptr<ExtendedCharacterInfoPage>(new ExtendedCharacterInfoPage()));
    }
    int infoIndex = static_cast<int>(codePoint) % numInfosInPage;
    ExtendedCharacterInfoPage* extendedPage = extendedPages[pageIndex].get();
    std::expected<ExtendedCharacterInfo*, int> rv = extendedPage->GetExtendedCharacterInfo(infoIndex);
    if (!rv) return std::unexpected<int>(rv.error());
    ExtendedCharacterInfo* info = *rv;
    return std::expected<ExtendedCharacterInfo*, int>(info);
}

bool IsAsciiDigit(char32_t c)
{
    if (c < char32_t(256u))
    {
        return std::isdigit(static_cast<int>(static_cast<unsigned char>(c)));
    }
    return false;
}

std::expected<GeneralCategoryId, int> GetGeneralCategory(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<GeneralCategoryId, int>(info->GetGeneralCategory());
}

std::expected<bool, int> HasGeneralCategory(char32_t c, GeneralCategoryId generalCategory)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->HasGeneralCategory(generalCategory));
}

std::expected<bool, int> IsUpperLetter(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Lu);
}

std::expected<bool, int> IsLowerLetter(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Ll);
}

std::expected<bool, int> IsTitleLetter(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Lt);
}

std::expected<bool, int> IsModifierLetter(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Lm);
}

std::expected<bool, int> IsOtherLetter(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Lo);
}

std::expected<bool, int> IsNonspacingMark(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Mn);
}

std::expected<bool, int> IsSpacingMark(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Mc);
}

std::expected<bool, int> IsEnclosingMark(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Me);
}

std::expected<bool, int> IsDecimalNumber(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Nd);
}

std::expected<bool, int> IsLetterNumber(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Nl);
}

std::expected<bool, int> IsOtherNumber(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::No);
}

std::expected<bool, int> IsConnectorPunctuation(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Pc);
}

std::expected<bool, int> IsDashPunctuation(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Pd);
}

std::expected<bool, int> IsOpenPunctuation(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Ps);
}

std::expected<bool, int> IsClosePunctuation(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Pe);
}

std::expected<bool, int> IsInitialPunctuation(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Pi);
}

std::expected<bool, int> IsFinalPunctuation(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Pf);
}

std::expected<bool, int> IsOtherPunctuation(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Po);
}

std::expected<bool, int> IsMathSymbol(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Sm);
}

std::expected<bool, int> IsCurrencySymbol(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Sc);
}

std::expected<bool, int> IsModifierSymbol(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Sk);
}

std::expected<bool, int> IsOtherSymbol(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::So);
}

std::expected<bool, int> IsSpaceSeparator(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Zs);
}

std::expected<bool, int> IsLineSeparator(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Zl);
}

std::expected<bool, int> IsParagraphSeparator(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Zp);
}

std::expected<bool, int> IsControl(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Cc);
}

std::expected<bool, int> IsFormat(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Cf);
}

std::expected<bool, int> IsSurrogate(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Cs);
}

std::expected<bool, int> IsPrivateUse(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Co);
}

std::expected<bool, int> IsUnassigned(char32_t c)
{
    std::expected<GeneralCategoryId, int> rv = GetGeneralCategory(c);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<bool, int>(*rv == GeneralCategoryId::Cn);
}

std::expected<char32_t, int> ToUpper(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<char32_t, int>(info->Upper());
}

std::expected<char32_t, int> ToLower(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<char32_t, int>(info->Lower());
}

std::expected<char32_t, int> ToTitle(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<char32_t, int>(info->Title());
}

std::expected<char32_t, int> ToFolding(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<char32_t, int>(info->Folding());
}

std::expected<std::u32string, int> FullUpper(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<std::u32string, int>(info->FullUpper());
}

std::expected<std::u32string, int> FullLower(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<std::u32string, int>(info->FullLower());
}

std::expected<std::u32string, int> FullTitle(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<std::u32string, int>(info->FullTitle());
}

std::expected<std::u32string, int> FullFolding(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<std::u32string, int>(info->FullFolding());
}

std::expected<bool, int> IsWhiteSpace(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::whiteSpace));
}

std::expected<bool, int> IsAlphabetic(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::alphabetic));
}

std::expected<bool, int> IsAsciiHexDigit(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::asciiHexDigit));
}

std::expected<bool, int> IsUppercase(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::uppercase));
}

std::expected<bool, int> IsLowercase(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::lowercase));
}

std::expected<bool, int> IsIdStart(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::idStart));
}

std::expected<bool, int> IsIdCont(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::idContinue));
}

std::expected<bool, int> IsGraphemeBase(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::graphemeBase));
}

std::expected<bool, int> IsGraphemeExtender(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::graphemeExtend));
}

std::expected<bool, int> IsOtherLower(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::otherLowercase));
}

std::expected<bool, int> IsOtherUpper(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::otherUppercase));
}

std::expected<std::string, int> GetCharacterName(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<std::string, int>(info->CharacterName());
}

std::expected<std::string, int> GetUnicode1Name(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<std::string, int>(info->Unicode1Name());
}

std::expected<NumericTypeId, int> GetNumericType(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<NumericTypeId, int>(info->GetNumericType());
}

std::expected<std::string, int> GetNumericValue(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<std::string, int>(info->GetNumericValue());
}

std::expected<bool, int> IsBidiMirrored(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::bidiMirrored));
}

std::expected<bool, int> IsBidiControl(char32_t c)
{
    std::expected<const CharacterInfo*, int> rv = GetCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const CharacterInfo* info = *rv;
    return std::expected<bool, int>(info->GetBinaryProperty(BinaryPropertyId::bidiControl));
}

std::expected<char32_t, int> GetBidiMirroringGlyph(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<char32_t, int>(info->GetBidiMirroringGlyph());
}

std::expected<BidiPairedBracketTypeId, int> GetBidiPairedBracketType(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<BidiPairedBracketTypeId, int>(info->GetBidiPairedBracketType());
}

std::expected<char32_t, int> GetBidiPairedBracket(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<char32_t, int>(info->GetBidiPairedBracket());
}

std::expected<std::vector<Alias>, int> Aliases(char32_t c)
{
    std::expected<const ExtendedCharacterInfo*, int> rv = GetExtendedCharacterInfo(c);
    if (!rv) return std::unexpected<int>(rv.error());
    const ExtendedCharacterInfo* info = *rv;
    return std::expected<std::vector<Alias>, int>(info->Aliases());
}

} // util
