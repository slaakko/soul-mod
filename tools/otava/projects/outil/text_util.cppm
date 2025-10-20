// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.text.util;

import std;
import util.error;
import util.stream;
import util.unicode;

export namespace util {

enum class FormatWidth
{
    exact, min
};

enum class FormatJustify
{
    left, right
};

std::string Trim(const std::string& s);
std::string TrimAll(const std::string& s);
std::expected<std::u32string, int> Trim(const std::u32string& s);
std::expected<std::u32string, int> TrimAll(const std::u32string& s);
std::vector<std::string> Split(const std::string& s, char c);
std::vector<std::string> Split(const std::string& s, const std::string& subString);
std::string Replace(const std::string& s, char oldChar, char newChar);
std::string Replace(const std::string& s, const std::string& oldString, const std::string& newString);
std::string HexEscape(char c);
std::expected<std::u32string, int> HexEscape(std::uint32_t c);
std::expected<std::string, int> CharStr(char c);
std::expected<std::u32string, int> CharStr(char32_t c);
std::expected<std::string, int> StringStr(const std::string& s);
std::expected<std::u32string, int> StringStr(const std::u32string& s);
std::expected<std::string, int> MakeStringLiteral(const std::string& s);
std::expected<std::u32string, int> MakeStringLiteral(const std::u32string& s);
std::string QuotedPath(const std::string& path);
bool LastComponentsEqual(const std::string& s0, const std::string& s1, char componentSeparator);
bool StartsWith(const std::string& s, const std::string& prefix);
bool StartsWith(const std::u32string& s, const std::u32string& prefix);
bool EndsWith(const std::string& s, const std::string& suffix);
bool EndsWith(const std::u32string& s, const std::u32string& suffix);
std::string NarrowString(const char* str, int length);
std::string ToUpperNarrow(const std::string& s);
std::string ToLowerNarrow(const std::string& s);
std::string ToString(double x);
std::string ToString(double x, int maxNumDecimals);
std::string ToString(double x, int minNumDecimals, int maxNumDecimals);
std::string ToHexString(std::uint8_t x);
std::string ToHexString(std::uint16_t x);
std::string ToHexString(std::uint32_t x);
std::string ToHexString(std::uint64_t x);
std::uint8_t ParseHexByte(const std::string& hexByteStr);
std::uint64_t ParseHexULong(const std::string& hexByteStr);
std::int32_t ParseOctal(const std::string& octalDigitStr);
std::string ToOctalString(std::int32_t value, int numDigits);
int Log10(int n);
std::expected<std::u32string, int> FormatNumber(int n, int numDigits);
std::string CurrentThreadIdStr();
std::string Format(const std::string& s, int width);
std::string Format(const std::string& s, int width, FormatJustify justify);
std::string Format(const std::string& s, int width, FormatWidth fw);
std::string Format(const std::string& s, int width, FormatWidth fw, FormatJustify justify);
std::string Format(const std::string& s, int width, FormatWidth fw, FormatJustify justify, char fillChar);
std::expected<std::string, int> PlatformStringToUtf8(const std::string& platformString);
std::expected<std::string, int> Utf8StringToPlatformString(const std::string& utf8String);

template<typename StringT>
std::vector<StringT> Split(const StringT& s, typename StringT::value_type c)
{
    std::vector<StringT> v;
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

template<typename StringT>
std::vector<StringT> Split(const StringT& s, const StringT& subString)
{
    std::vector<StringT> v;
    int start = 0;
    int n = int(s.length());
    for (int i = 0; i < n; ++i)
    {
        if (s.substr(i, subString.length()) == subString)
        {
            v.push_back(s.substr(start, i - start));
            start = i + static_cast<int>(subString.length());
            i += static_cast<int>(subString.length()) - 1;
        }
    }
    if (start < n)
    {
        v.push_back(s.substr(start, n - start));
    }
    return v;
}

template<typename T, typename CharT>
std::expected<T, int> ParseSigned(const std::basic_string<CharT>& s, const std::string& valueKindStr)
{
    bool negative = false;
    bool cannotParse = false;
    T value = 0;
    auto it = s.begin();
    auto end = s.end();
    if (it != end)
    {
        if (*it == '-')
        {
            negative = true;
            ++it;
        }
        else if (*it == '+')
        {
            ++it;
        }
    }
    if (it != end)
    {
        while (it != end)
        {
            CharT c = *it++;
            if (c >= '0' && c <= '9')
            {
                value = static_cast<T>(10) * value + static_cast<T>(c) - static_cast<T>('0');
            }
            else
            {
                cannotParse = true;
                break;
            }
        }
    }
    else
    {
        cannotParse = true;
    }
    if (cannotParse)
    {
        auto u = ToUtf8(s);
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(AllocateError(valueKindStr + " value cannot be parsed from string \"" + *u + "\""));
    }
    if (negative)
    {
        value = -value;
    }
    return std::expected<T, int>(value);
}

template<typename T, typename CharT>
std::expected<T, int> ParseUnsigned(const std::basic_string<CharT>& s, const std::string& valueKindStr)
{
    bool cannotParse = false;
    T value = 0;
    auto it = s.begin();
    auto end = s.end();
    if (it != end)
    {
        if (*it == '+')
        {
            ++it;
        }
    }
    if (it != end)
    {
        while (it != end)
        {
            CharT c = *it++;
            if (c >= '0' && c <= '9')
            {
                value = static_cast<T>(10) * static_cast<T>(value) + static_cast<T>(c) - static_cast<T>('0');
            }
            else
            {
                cannotParse = true;
                break;
            }
        }
    }
    else
    {
        cannotParse = true;
    }
    if (cannotParse)
    {
        auto u = ToUtf8(s);
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(AllocateError(valueKindStr + " value cannot be parsed from string \"" + *u + "\""));
    }
    return std::expected<T, int>(value);
}

template<typename T, typename CharT>
std::expected<T, int> ParseFloating(const std::basic_string<CharT>& s, const std::string& valueKindStr)
{
    bool negative = false;
    bool negativeExponent = false;
    bool cannotParse = false;
    T value = 0;
    T d = 10;
    int exponent = 0;
    auto it = s.begin();
    auto end = s.end();
    if (it != end)
    {
        if (*it == '-')
        {
            negative = true;
            ++it;
        }
        else if (*it == '+')
        {
            ++it;
        }
    }
    if (it == end)
    {
        cannotParse = true;
    }
    int state = 0;
    while (it != end && !cannotParse)
    {
        CharT c = *it++;
        switch (state)
        {
        case 0:
        {
            if (c >= '0' && c <= '9')
            {
                value = static_cast<T>(10) * static_cast<T>(value) + static_cast<T>(c) - static_cast<T>('0');
            }
            else if (c == '.')
            {
                state = 1;
            }
            else if (c == 'e' || c == 'E')
            {
                state = 2;
            }
            else
            {
                cannotParse = true;
            }
            break;
        }
        case 1:
        {
            if (c >= '0' && c <= '9')
            {
                value += (static_cast<T>(c) - static_cast<T>('0')) / d;
                d *= 10;
            }
            else if (c == 'e' || c == 'E')
            {
                state = 2;
            }
            else
            {
                cannotParse = true;
            }
            break;
        }
        case 2:
        {
            if (c == '+')
            {
                state = 3;
            }
            else if (c == '-')
            {
                negativeExponent = true;
                state = 3;
            }
            else if (c >= '0' && c <= '9')
            {
                exponent = static_cast<int>(c) - static_cast<int>('0');
                state = 3;
            }
            else
            {
                cannotParse = true;
            }
            break;
        }
        case 3:
        {
            if (c >= '0' && c <= '9')
            {
                exponent = 10 * exponent + static_cast<int>(c) - static_cast<int>('0');
            }
            else
            {
                cannotParse = true;
            }
            break;
        }
        }
    }
    if (cannotParse)
    {
        std::expected<std::string, int> u = util::ToUtf8(s);
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(AllocateError(valueKindStr + " value cannot be parsed from string \"" + *u + "\""));
    }
    if (negative)
    {
        value = -value;
    }
    if (exponent != 0)
    {
        if (negativeExponent)
        {
            exponent = -exponent;
        }
        value *= static_cast<T>(std::pow(10.0, exponent));
    }
    return std::expected<T, int>(value);
}

template<typename CharT>
std::expected<std::int8_t, int> ParseSByte(const std::basic_string<CharT>& s)
{
    return ParseSigned<std::int8_t>(s, "sbyte");
}

template<typename CharT>
std::expected<std::uint8_t, int> ParseByte(const std::basic_string<CharT>& s)
{
    return ParseUnsigned<std::uint8_t>(s, "byte");
}

template<typename CharT>
std::expected<std::int16_t, int> ParseShort(const std::basic_string<CharT>& s)
{
    return ParseSigned<std::int16_t>(s, "short");
}

template<typename CharT>
std::expected<std::uint16_t, int> ParseUShort(const std::basic_string<CharT>& s)
{
    return ParseUnsigned<std::uint16_t>(s, "ushort");
}

template<typename CharT>
std::expected<std::int32_t, int> ParseInt(const std::basic_string<CharT>& s)
{
    return ParseSigned<std::int32_t>(s, "int");
}

template<typename CharT>
std::expected<std::uint32_t, int> ParseUInt(const std::basic_string<CharT>& s)
{
    return ParseUnsigned<std::uint32_t>(s, "uint");
}

template<typename CharT>
std::expected<std::int64_t, int> ParseLong(const std::basic_string<CharT>& s)
{
    return ParseSigned<std::int64_t>(s, "long");
}

template<typename CharT>
std::expected<std::uint64_t, int> ParseULong(const std::basic_string<CharT>& s)
{
    return ParseUnsigned<std::uint64_t>(s, "ulong");
}

template<typename CharT>
std::expected<float, int> ParseFloat(const std::basic_string<CharT>& s)
{
    return ParseFloating<float>(s, "float");
}

template<typename CharT>
std::expected<double, int> ParseDouble(const std::basic_string<CharT>& s)
{
    return ParseFloating<double>(s, "double");
}

template<typename CharT>
std::expected<bool, int> ParseHexChar(CharT& value, const CharT*& p, const CharT* e, const std::basic_string<CharT>& tokenStr)
{
    if (p != e)
    {
        CharT s = *p;
        switch (s)
        {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        {
            value = static_cast<CharT>(16 * static_cast<int>(value) + static_cast<int>(s) - static_cast<int>('0'));
            break;
        }
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        {
            value = static_cast<CharT>(16 * static_cast<int>(value) + 10 + static_cast<int>(s) - static_cast<int>('A'));
            break;
        }
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        {
            value = static_cast<CharT>(16 * static_cast<int>(value) + 10 + static_cast<int>(s) - static_cast<int>('a'));
            break;
        }
        }
        ++p;
    }
    else
    {
        std::expected<std::string, int> u = util::ToUtf8(tokenStr);
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(AllocateError("hex character cannot be parsed from string '" + *u + "'"));
    }
    return std::expected<bool, int>(true);
}

template<typename CharT>
std::expected<CharT, int> ParseEscape(const CharT*& p, const CharT* e, const std::basic_string<CharT>& tokenStr)
{
    CharT value = '\0';
    if (p != e && (*p == 'x' || *p == 'X'))
    {
        ++p;
        while (p != e && ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F')))
        {
            std::expected<bool, int> x = ParseHexChar(value, p, e, tokenStr);
            if (!x) return std::unexpected<int>(x.error());
        }
    }
    else if (p != e && (*p == 'd' || *p == 'D'))
    {
        ++p;
        while (p != e && *p >= '0' && *p <= '9')
        {
            value = static_cast<CharT>(10 * static_cast<int>(value) + (static_cast<int>(*p) - static_cast<int>('0')));
            ++p;
        }
    }
    else if (p != e && (*p >= '0' && *p <= '7'))
    {
        while (p != e && *p >= '0' && *p <= '7')
        {
            value = static_cast<CharT>(8 * static_cast<int>(value) + (static_cast<int>(*p) - static_cast<int>('0')));
            ++p;
        }
    }
    else if (p != e && *p == 'u')
    {
        ++p;
        std::expected<bool, int> x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
    }
    else if (p != e && *p == 'U')
    {
        ++p;
        std::expected<bool, int> x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
        x = ParseHexChar(value, p, e, tokenStr);
        if (!x) return std::unexpected<int>(x.error());
    }
    else if (p != e)
    {
        CharT s = *p;
        switch (s)
        {
        case 'a': { value = '\a'; break; }
        case 'b': { value = '\b'; break; }
        case 'f': { value = '\f'; break; }
        case 'n': { value = '\n'; break; }
        case 'r': { value = '\r'; break; }
        case 't': { value = '\t'; break; }
        case 'v': { value = '\v'; break; }
        default: { value = s; break; }
        }
        ++p;
    }
    return std::expected<CharT, int>(value);
}

template<typename CharT>
std::expected<CharT, int> ParseCharLiteral(const std::basic_string<CharT>& s)
{
    CharT charLit = '\0';
    const CharT* p = s.c_str();
    const CharT* e = s.c_str() + s.length();
    bool first = true;
    bool cannotParse = false;
    if (p != e && *p == '\'')
    {
        ++p;
        while (p != e && *p != '\r' && *p != '\n' && *p != '\'')
        {
            if (*p == '\\')
            {
                ++p;
                if (first)
                {
                    std::expected<CharT, int> rv = ParseEscape(p, e, s);
                    if (!rv) return std::unexpected<int>(rv.error());
                    charLit = *rv;
                    first = false;
                }
                else
                {
                    cannotParse = true;
                    break;
                }
            }
            else
            {
                if (first)
                {
                    charLit = *p;
                    first = false;
                    ++p;
                }
                else
                {
                    cannotParse = true;
                    break;
                }
            }
        }
        if (p != e && *p == '\'')
        {
            ++p;
        }
        if (p != e)
        {
            cannotParse = true;
        }
    }
    else
    {
        cannotParse = true;
    }
    if (cannotParse)
    {
        std::expected<std::string, int> u = ToUtf8(s);
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(AllocateError("character literal cannot be parsed from string \"" + *u + "\""));
    }
    return std::expected<CharT, int>(charLit);
}

template<typename CharT>
std::expected<std::basic_string<CharT>, int> ParseStringLiteral(const std::basic_string<CharT>& s)
{
    bool cannotParse = false;
    std::basic_string<CharT> stringLiteral;
    const CharT* p = s.c_str();
    const CharT* e = s.c_str() + s.length();
    if (p != e && *p == '"')
    {
        ++p;
        while (p != e && *p != '\r' && *p != '\n' && *p != '"')
        {
            if (*p == '\\')
            {
                ++p;
                std::expected<CharT, int> u = ParseEscape(p, e, s);
                if (!u) return std::unexpected<int>(u.error());
                stringLiteral.append(1, *u);
            }
            else
            {
                stringLiteral.append(1, *p);
                ++p;
            }
        }
        if (p != e && *p == '"')
        {
            ++p;
        }
        if (p != e)
        {
            cannotParse = true;
        }
    }
    else
    {
        cannotParse = true;
    }
    if (cannotParse)
    {
        std::expected<std::string, int> u = ToUtf8(s);
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(AllocateError("string literal cannot be parsed from string \"" + *u + "\""));
    }
    return std::expected<std::basic_string<CharT>, int>(stringLiteral);
}

} // util
