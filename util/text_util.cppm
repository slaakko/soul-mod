// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.text.util;

import std;
import util.stream;

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
std::u32string Trim(const std::u32string& s);
std::u32string TrimAll(const std::u32string& s);
std::vector<std::string> Split(const std::string& s, char c);
std::vector<std::string> Split(const std::string& s, const std::string& subString);
std::string Replace(const std::string& s, char oldChar, char newChar);
std::string Replace(const std::string& s, const std::string& oldString, const std::string& newString);
std::string HexEscape(char c);
std::u32string HexEscape(std::uint32_t c);
std::string CharStr(char c);
std::u32string CharStr(char32_t c);
std::string StringStr(const std::string& s);
std::u32string StringStr(const std::u32string& s);
std::string MakeStringLiteral(const std::string& s);
std::u32string MakeStringLiteral(const std::u32string& s);
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
std::u32string FormatNumber(int n, int numDigits);
std::string CurrentThreadIdStr();
std::string Format(const std::string& s, int width);
std::string Format(const std::string& s, int width, FormatJustify justify);
std::string Format(const std::string& s, int width, FormatWidth fw);
std::string Format(const std::string& s, int width, FormatWidth fw, FormatJustify justify);
std::string Format(const std::string& s, int width, FormatWidth fw, FormatJustify justify, char fillChar);
std::string PlatformStringToUtf8(const std::string& platformString);
std::string Utf8StringToPlatformString(const std::string& utf8String);

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
            start = i + subString.length();
            i += subString.length() - 1;
        }
    }
    if (start < n)
    {
        v.push_back(s.substr(start, n - start));
    }
    return v;
}

} // util
