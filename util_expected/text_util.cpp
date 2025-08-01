// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#ifdef _WIN32
#include <Windows.h>
#undef min
#undef max
#endif

module util_expected.text.util;

import util_expected.error;
import util_expected.unicode;

namespace util {

std::string Trim(const std::string& s)
{
    int b = 0;
    while (b < int(s.length()) && std::isspace(s[b])) ++b;
    int e = int(s.length()) - 1;
    while (e >= b && std::isspace(s[e])) --e;
    return s.substr(b, e - b + 1);
}

std::string TrimAll(const std::string& s)
{
    std::string result;
    result.reserve(s.length());
    int state = 0;
    std::string::const_iterator e = s.cend();
    for (std::string::const_iterator i = s.cbegin(); i != e; ++i)
    {
        char c = *i;
        switch (state)
        {
        case 0:
        {
            if (!std::isspace(c))
            {
                result.append(1, c);
                state = 1;
            }
            break;
        }
        case 1:
        {
            if (std::isspace(c))
            {
                state = 2;
            }
            else
            {
                result.append(1, c);
            }
            break;
        }
        case 2:
        {
            if (!std::isspace(c))
            {
                result.append(1, ' ');
                result.append(1, c);
                state = 1;
            }
            break;
        }
        }
    }
    return result;
}

std::expected<std::u32string, int> Trim(const std::u32string& s)
{
    int b = 0;
    while (b < int(s.length()))
    {
        auto ws = IsWhiteSpace(s[b]);
        if (!ws) return std::unexpected<int>(ws.error());
        if (!*ws) break;
        ++b;
    }
    int e = int(s.length()) - 1;
    while (e >= b)
    {
        auto ws = IsWhiteSpace(s[e]);
        if (!ws) return std::unexpected<int>(ws.error());
        if (!*ws) break;
        --e;
    }
    return std::expected<std::u32string, int>(s.substr(b, e - b + 1));
}

std::expected<std::u32string, int> TrimAll(const std::u32string& s)
{
    std::u32string result;
    result.reserve(s.length());
    int state = 0;
    std::u32string::const_iterator e = s.cend();
    for (std::u32string::const_iterator i = s.cbegin(); i != e; ++i)
    {
        char32_t c = *i;
        switch (state)
        {
            case 0:
            {
                auto ws = IsWhiteSpace(c);
                if (!ws) return std::unexpected<int>(ws.error());
                if (!*ws)
                {
                    result.append(1, c);
                    state = 1;
                }
                break;
            }
            case 1:
            {
                auto ws = IsWhiteSpace(c);
                if (!ws) return std::unexpected<int>(ws.error());
                if (*ws)
                {
                    state = 2;
                }
                else
                {
                    result.append(1, c);
                }
                break;
            }
            case 2:
            {
                auto ws = IsWhiteSpace(c);
                if (!ws) return std::unexpected<int>(ws.error());
                if (!*ws)
                {
                    result.append(1, ' ');
                    result.append(1, c);
                    state = 1;
                }
                break;
            }
        }
    }
    return std::expected<std::u32string, int>(result);
}

std::vector<std::string> Split(const std::string& s, char c)
{
    std::vector<std::string> v;
    int start = 0;
    int n = int(s.length());
    for (int i = 0; i < n; ++i)
    {
        if (s[i] == c)
        {
            v.push_back(s.substr(start, i - start));
            start = i + 1;
        }
    }
    if (start < n)
    {
        v.push_back(s.substr(start, n - start));
    }
    return v;
}

std::vector<std::string> Split(const std::string& s, const std::string& subString)
{
    std::vector<std::string> v;
    int start = 0;
    int n = int(s.length());
    for (int i = 0; i < n; ++i)
    {
        if (s.substr(i, subString.length()) == subString)
        {
            v.push_back(s.substr(start, i - start));
            start = static_cast<int>(i + subString.length());
            i += static_cast<int>(subString.length() - 1);
        }
    }
    if (start < n)
    {
        v.push_back(s.substr(start, n - start));
    }
    return v;
}

std::string Replace(const std::string& s, char oldChar, char newChar)
{
    std::string t(s);
    std::string::iterator e = t.end();
    for (std::string::iterator i = t.begin(); i != e; ++i)
    {
        if (*i == oldChar)
        {
            *i = newChar;
        }
    }
    return t;
}

std::string Replace(const std::string& s, const std::string& oldString, const std::string& newString)
{
    std::string r;
    std::string::size_type start = 0;
    std::string::size_type pos = s.find(oldString.c_str(), start);
    while (pos != std::string::npos)
    {
        r.append(s.substr(start, pos - start));
        r.append(newString);
        start = pos + oldString.length();
        pos = s.find(oldString.c_str(), start);
    }
    r.append(s.substr(start, s.length() - start));
    return r;
}

std::string HexEscape(char c)
{
    std::string s = "\\x";
    s.append(ToHexString(static_cast<unsigned char>(c)));
    return s;
}

std::expected<std::u32string, int> HexEscape(std::uint32_t c)
{
    std::string s = "\\x";
    s.append(ToHexString(c));
    return ToUtf32(s);
}

std::expected<std::u32string, int> CharHexEscape(char32_t c)
{
    std::string s = "\\U";
    s.append(ToHexString(static_cast<std::uint32_t>(c)));
    return ToUtf32(s);
}

std::expected<std::string, int> CharStr(char c)
{
    switch (c)
    {
        case '\'': return "\\'";
        case '\"': return "\\\"";
        case '\\': return "\\\\";
        case '\a': return "\\a";
        case '\b': return "\\b";
        case '\f': return "\\f";
        case '\n': return "\\n";
        case '\r': return "\\r";
        case '\t': return "\\t";
        case '\v': return "\\v";
        case '\0': return "\\0";
        default:
        {
            if (c >= 32 && c <= 126)
            {
                return std::expected<std::string, int>(std::string(1, c));
            }
            else
            {
                std::expected<std::u32string, int> rv = CharHexEscape(c);
                if (!rv) return std::unexpected<int>(rv.error());
                return ToUtf8(*rv);
            }
        }
    }
}

std::expected<std::u32string, int> CharStr(char32_t c)
{
    switch (c)
    {
        case U'\'': return U"\\'";
        case U'\"': return U"\\\"";
        case U'\\': return U"\\\\";
        case U'\a': return U"\\a";
        case U'\b': return U"\\b";
        case U'\f': return U"\\f";
        case U'\n': return U"\\n";
        case U'\r': return U"\\r";
        case U'\t': return U"\\t";
        case U'\v': return U"\\v";
        case U'\0': return U"\\0";
        default:
        {
            if (c >= 32 && c <= 126)
            {
                return std::expected<std::u32string, int>(std::u32string(1, c));
            }
            else
            {
                return CharHexEscape(c);
            }
        }
    }
}

std::expected<std::string, int> StringStr(const std::string& s)
{
    std::string r;
    int n = int(s.length());
    for (int i = 0; i < n; ++i)
    {
        std::expected<std::string, int> rv = CharStr(s[i]);
        if (!rv) return rv;
        r.append(*rv);
    }
    return std::expected<std::string, int>(r);
}

std::expected<std::u32string, int> StringStr(const std::u32string& s)
{
    std::u32string r;
    int n = int(s.length());
    for (int i = 0; i < n; ++i)
    {
        std::expected<std::u32string, int> rv = CharStr(s[i]);
        if (!rv) return rv;
        r.append(*rv);
    }
    return std::expected<std::u32string, int>(r);
}

std::expected<std::string, int> MakeStringLiteral(const std::string& s)
{
    std::string result = "\"";
    std::expected<std::string, int> rv = StringStr(s);
    if (!rv) return rv;
    result.append(*rv);
    result.append(1, '"');
    return std::expected<std::string, int>(result);
}

std::expected<std::u32string, int> MakeStringLiteral(const std::u32string& s)
{
    std::u32string result = U"\"";
    std::expected<std::u32string, int> rv = StringStr(s);
    if (!rv) return rv;
    result.append(*rv);
    result.append(1, '"');
    return std::expected<std::u32string, int>(result);
}

std::string QuotedPath(const std::string& path)
{
    if (path.find(' ') != std::string::npos)
    {
        std::string p("\"");
        p.append(path).append("\"");
        return p;
    }
    return path;
}

bool LastComponentsEqual(const std::string& s0, const std::string& s1, char componentSeparator)
{
    std::vector<std::string> c0 = Split(s0, componentSeparator);
    std::vector<std::string> c1 = Split(s1, componentSeparator);
    int n0 = int(c0.size());
    int n1 = int(c1.size());
    int n = std::min(n0, n1);
    for (int i = 0; i < n; ++i)
    {
        if (c0[n0 - i - 1] != c1[n1 - i - 1]) return false;
    }
    return true;
}

bool StartsWith(const std::string& s, const std::string& prefix)
{
    int n = int(prefix.length());
    return int(s.length()) >= n && s.substr(0, n) == prefix;
}

bool StartsWith(const std::u32string& s, const std::u32string& prefix)
{
    int n = int(prefix.length());
    return int(s.length()) >= n && s.substr(0, n) == prefix;
}

bool EndsWith(const std::string& s, const std::string& suffix)
{
    int n = int(suffix.length());
    int m = int(s.length());
    return m >= n && s.substr(m - n, n) == suffix;
}

bool EndsWith(const std::u32string& s, const std::u32string& suffix)
{
    int n = int(suffix.length());
    int m = int(s.length());
    return m >= n && s.substr(m - n, n) == suffix;
}

std::string NarrowString(const char* str, int length)
{
#if defined(__linux) || defined(__posix) || defined(__unix) || defined(OTAVA)
    return std::string(str, length);
#elif defined(_WIN32)
    std::string narrow;
    narrow.reserve(length);
    int state = 0;
    for (int i = 0; i < length; ++i)
    {
        char c = str[i];
        switch (state)
        {
        case 0:
        {
            if (c == '\r') state = 1; else narrow.append(1, c);
            break;
        }
        case 1:
        {
            if (c == '\n') narrow.append(1, '\n'); else narrow.append(1, '\r').append(1, c);
            state = 0;
            break;
        }
        }
    }
    return narrow;
#else
#error unknown platform
#endif
}

std::string ToUpperNarrow(const std::string& s)
{
    std::string result;
    int n = int(s.size());
    result.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        result.append(1, std::toupper(s[i]));
    }
    return result;
}

std::string ToLowerNarrow(const std::string& s)
{
    std::string result;
    int n = int(s.size());
    result.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        result.append(1, std::tolower(s[i]));
    }
    return result;
}

std::string ToString(double x)
{
    return ToString(x, 15);
}

std::string ToString(double x, int maxNumDecimals)
{
    return ToString(x, 0, maxNumDecimals);
}

std::string ToString(double x, int minNumDecimals, int maxNumDecimals)
{
    std::string result;
    if (x < 0)
    {
        x = -x;
        result.append(1, '-');
    }
    result.append(std::to_string(static_cast<int>(x)));
    double d = x - static_cast<int>(x);
    if (d > 0 || minNumDecimals > 0)
    {
        result.append(1, '.');
        for (int i = 0; (d > 0 || i < minNumDecimals) && i < maxNumDecimals; ++i)
        {
            d = 10 * d;
            int digit = static_cast<int>(d) % 10;
            result.append(1, static_cast<char>(static_cast<int>('0') + digit));
            d = d - static_cast<int>(d);
        }
    }
    return result;
}

inline char HexNibble(std::uint8_t n)
{
    const char* h = "0123456789ABCDEF";
    return h[n];
}

std::string ToHexString(std::uint8_t x)
{
    std::string s;
    s.append(1, HexNibble(x >> 4)).append(1, HexNibble(x & 0x0F));
    return s;
}

std::string ToHexString(std::uint16_t x)
{
    std::string s;
    s.append(ToHexString(std::uint8_t((x >> 8) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x & 0xFF))));
    return s;
}

std::string ToHexString(std::uint32_t x)
{
    std::string s;
    s.append(ToHexString(std::uint8_t((x >> 24) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x >> 16) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x >> 8) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x & 0xFF))));
    return s;
}

std::string ToHexString(std::uint64_t x)
{
    std::string s;
    s.append(ToHexString(std::uint8_t((x >> 56) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x >> 48) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x >> 40) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x >> 32) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x >> 24) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x >> 16) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x >> 8) & 0xFF)));
    s.append(ToHexString(std::uint8_t((x & 0xFF))));
    return s;
}

std::uint8_t ParseHexByte(const std::string& hexByteStr)
{
    return static_cast<std::uint8_t>(std::stoi(hexByteStr, nullptr, 16));
}

std::uint64_t ParseHexULong(const std::string& hexByteStr)
{
    return std::stoull(hexByteStr, nullptr, 16);
}

std::int32_t ParseOctal(const std::string& octalDigitStr)
{
    return std::stoi(octalDigitStr, nullptr, 8);
}

std::string ToOctalString(std::int32_t value, int numDigits)
{
    std::string str;
    for (int i = 0; i < numDigits; ++i)
    {
        int digit = value & 7;
        str.append(1, ('0' + digit));
        value = value >> 3;
    }
    std::reverse(str.begin(), str.end());
    return str;
}

int Log10(int n)
{
    int log10 = 1;
    int m = n / 10;
    while (m > 0)
    {
        ++log10;
        m = m / 10;
    }
    return log10;
}

std::expected<std::u32string, int> FormatNumber(int n, int numDigits)
{
    std::u32string s(numDigits, ' ');
    int k = numDigits - 1;
    while (n > 0)
    {
        if (k < 0)
        {
            return std::unexpected<int>(AllocateError("invalid number of digits"));
        }
        int digit = n % 10;
        s[k] = digit + '0';
        --k;
        n = n / 10;
    }
    return std::expected<std::u32string, int>(s);
}

std::string CurrentThreadIdStr()
{
    std::stringstream s;
    s << std::this_thread::get_id();
    return s.str();
}

std::string Format(const std::string& s, int width)
{
    return Format(s, width, FormatWidth::exact, FormatJustify::left);
}

std::string Format(const std::string& s, int width, FormatJustify justify)
{
    return Format(s, width, FormatWidth::exact, justify);
}

std::string Format(const std::string& s, int width, FormatWidth fw)
{
    return Format(s, width, fw, FormatJustify::left);
}

std::string Format(const std::string& s, int width, FormatWidth fw, FormatJustify justify)
{
    return Format(s, width, fw, justify, ' ');
}

std::string Format(const std::string& s, int width, FormatWidth fw, FormatJustify justify, char fillChar)
{
    std::string result;
    int m = static_cast<int>(s.length());
    if (fw == FormatWidth::min)
    {
        width = std::max(width, m);
    }
    else if (fw == FormatWidth::exact)
    {
        m = std::min(m, width);
    }
    int n = std::max(0, width - m);
    if (justify == FormatJustify::right)
    {
        for (int i = 0; i < n; ++i)
        {
            result.append(1, fillChar);
        }
    }
    for (int i = 0; i < m; ++i)
    {
        result.append(1, s[i]);
    }
    if (justify == FormatJustify::left)
    {
        for (int i = 0; i < n; ++i)
        {
            result.append(1, fillChar);
        }
    }
    return result;
}


#if defined(_WIN32)

std::expected<std::string, int> PlatformStringToUtf8(const std::string& platformString)
{
    if (platformString.empty()) return std::string();
    int bufSize = 4096;
    std::unique_ptr<char16_t> wbuf(new char16_t[bufSize]);
    int result = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, platformString.c_str(), -1, (LPWSTR)wbuf.get(), bufSize);
    if (result == 0)
    {
        return platformString; // conversion failed, maybe it's UTF-8 already
    }
    return ToUtf8(wbuf.get());
}

#else // on Linux it will probably be UTF-8 already...

std::expected<std::string, int> PlatformStringToUtf8(const std::string& platformString)
{
    return std::expected<std::string, int>(platformString);
}

#endif

#if defined(_WIN32)

std::expected<std::string, int> Utf8StringToPlatformString(const std::string& utf8String)
{
    if (utf8String.empty()) return std::string();
    std::expected<std::u16string, int> rv = ToUtf16(utf8String);
    if (!rv) return std::unexpected<int>(rv.error());
    std::u16string utf16 = *rv;
    int bufSize = 4096;
    std::unique_ptr<char> buf(new char[bufSize]);
    int result = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)utf16.c_str(), -1, (LPSTR)buf.get(), bufSize, nullptr, nullptr);
    if (result == 0)
    {
        return utf8String;
    }
    return std::string(buf.get());
}

#else

std::expected<std::string, int> Utf8StringToPlatformString(const std::string& utf8String)
{
    return std::expected<std::string, int>(utf8String);
}

#endif

} // util
