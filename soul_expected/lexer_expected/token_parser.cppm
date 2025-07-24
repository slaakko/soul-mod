// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.token.parser;

import std;
import util_expected;

export namespace soul_expected::lexer {

template<typename CharT>
constexpr std::expected<std::string, int> ToString(const CharT* begin, const CharT* end)
{
    return util::ToUtf8(std::basic_string<CharT>(begin, end));
}

constexpr std::expected<std::string, int> ToString(const char8_t* begin, const char8_t* end)
{
    return std::expected<std::string, int>(std::string(begin, end));
}

constexpr std::expected<std::string, int> ToString(const char* begin, const char* end)
{
    return std::expected<std::string, int>(std::string(begin, end));
}

// ParseSigned: parses an integral value from character range [begin, end[ in format ('+'|'-')?[0-9]+
// returns true if successful, false otherwise

template<typename CharT, typename Value>
    requires std::integral<Value>
bool ParseSigned(const CharT* begin, const CharT* end, Value& value)
{
    value = 0;
    if (begin == end)
    {
        return false;
    }
    bool negative = false;
    int state = 0;
    while (begin != end)
    {
        CharT ch = *begin;
        switch (state)
        {
        case 0:
        {
            if (ch == '+')
            {
                state = 1;
            }
            else if (ch == '-')
            {
                negative = true;
                state = 1;
            }
            else if (ch >= '0' && ch <= '9')
            {
                value = static_cast<Value>(ch) - static_cast<Value>('0');
                state = 1;
            }
            else
            {
                return false;
            }
            break;
        }
        case 1:
        {
            if (ch >= '0' && ch <= '9')
            {
                value = 10 * value + static_cast<Value>(ch) - static_cast<Value>('0');
            }
            else
            {
                return false;
            }
            break;
        }
        }
        ++begin;
    }
    if (state != 1)
    {
        return false;
    }
    else
    {
        if (negative)
        {
            value = -value;
        }
        return true;
    }
}

// ParseUnsigned: parses an integral value from character range [begin, end[ in format ('+')?[0-9]+
// returns true if successful, false otherwise

template<typename CharT, typename Value>
    requires std::integral<Value>
bool ParseUnsigned(const CharT* begin, const CharT* end, Value& value)
{
    value = 0;
    if (begin == end)
    {
        return false;
    }
    int state = 0;
    while (begin != end)
    {
        CharT ch = *begin;
        switch (state)
        {
        case 0:
        {
            if (ch == '+')
            {
                state = 1;
            }
            else if (ch >= '0' && ch <= '9')
            {
                value = static_cast<Value>(ch) - static_cast<Value>('0');
                state = 1;
            }
            else
            {
                return false;
            }
            break;
        }
        case 1:
        {
            if (ch >= '0' && ch <= '9')
            {
                value = 10 * value + static_cast<Value>(ch) - static_cast<Value>('0');
            }
            else
            {
                return false;
            }
            break;
        }
        }
        ++begin;
    }
    if (state != 1)
    {
        return false;
    }
    return true;
}

// ParseHex: parses an integral value from character range [begin, end[ in format [0-9a-fA-F]+
// returns true if successful, false otherwise

template<typename CharT, typename Value>
    requires std::integral<Value>
bool ParseHex(const CharT* begin, const CharT* end, Value& value)
{
    value = 0;
    if (begin == end)
    {
        return false;
    }
    while (begin != end)
    {
        CharT ch = *begin;
        if (ch >= '0' && ch <= '9')
        {
            value = 16 * value + static_cast<Value>(ch) - static_cast<Value>('0');
        }
        else if (ch >= 'a' && ch <= 'f')
        {
            value = 16 * value + 10 + static_cast<Value>(ch) - static_cast<Value>('a');
        }
        else if (ch >= 'A' && ch <= 'F')
        {
            value = 16 * value + 10 + static_cast<Value>(ch) - static_cast<Value>('A');
        }
        else
        {
            return false;
        }
        ++begin;
    }
    return true;
}

template<typename CharT, typename Value>
    requires std::integral<Value>
bool ParseOctal(const CharT* begin, const CharT* end, Value& value)
{
    value = 0;
    if (begin == end)
    {
        return false;
    }
    while (begin != end)
    {
        if (*begin >= '0' && *begin <= '7')
        {
            value = 8 * value + static_cast<int>(*begin) - static_cast<int>('0');
        }
        else
        {
            return false;
        }
        ++begin;
    }
    return true;
}

template<typename CharT, typename Value>
    requires std::floating_point<Value>
bool ParseFloating(const CharT* begin, const CharT* end, Value& value)
{
    value = 0.0;
    if (begin == end)
    {
        return false;
    }
    bool negative = false;
    if (*begin == '+')
    {
        ++begin;
    }
    else if (*begin == '-')
    {
        negative = true;
        ++begin;
    }
    int state = 0;
    Value d = 10.0;
    int exponent = 0;
    bool negativeExponent = false;
    if (begin == end)
    {
        return false;
    }
    while (begin != end)
    {
        CharT ch = *begin;
        switch (state)
        {
        case 0:
        {
            if (ch >= '0' && ch <= '9')
            {
                value = 10 * value + static_cast<int>(ch) - static_cast<int>('0');
            }
            else if (ch == '.')
            {
                state = 1;
            }
            else if (ch == 'e' || ch == 'E')
            {
                state = 2;
            }
            else
            {
                return false;
            }
            break;
        }
        case 1:
        {
            if (ch >= '0' && ch <= '9')
            {
                value = 10 * value + (static_cast<int>(ch) - static_cast<int>('0')) / d;
                d = 10 * d;
            }
            else if (ch == 'e' || ch == 'E')
            {
                state = 2;
            }
            else
            {
                return false;
            }
            break;
        }
        case 2:
        {
            if (ch == '+')
            {
                state = 3;
            }
            else if (ch == '-')
            {
                negativeExponent = true;
                state = 3;
            }
            else if (ch >= '0' && ch <= '9')
            {
                exponent = static_cast<int>(ch) - static_cast<int>('0');
                state = 3;
            }
            else
            {
                return false;
            }
            break;
        }
        case 3:
        {
            if (ch >= '0' && ch <= '9')
            {
                exponent = 10 * exponent + static_cast<int>(ch) - static_cast<int>('0');
            }
            else
            {
                return false;
            }
            break;
        }
        }
        ++begin;
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
        value = value * static_cast<Value>(std::pow(10.0, exponent));
    }
    return true;
}

template<typename CharT, typename LexerBaseT>
std::expected<std::int8_t, int> ParseSByte(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::int8_t value = 0;
    if (ParseSigned(begin, end, value))
    {
        return std::expected<std::int8_t, int>(value);
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("sbyte token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" + 
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
std::uint8_t ParseByte(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::uint8_t value = 0;
    if (ParseUnsigned(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("byte token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" +
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
std::int16_t ParseShort(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::int16_t value = 0;
    if (ParseSigned(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("short token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" + 
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
std::uint16_t ParseUShort(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::uint16_t value = 0;
    if (ParseUnsigned(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("ushort token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" + 
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
std::int32_t ParseInt(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::int32_t value = 0;
    if (ParseSigned(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("integer token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" +
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
std::uint32_t ParseUInt(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::uint32_t value = 0;
    if (ParseUnsigned(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("uint token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" +
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
std::int64_t ParseLong(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::int64_t value = 0;
    if (ParseSigned(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("long long token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" +
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
std::uint64_t ParseULong(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::uint64_t value = 0;
    if (ParseUnsigned(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("unsigned long long token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" +
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
std::uint64_t ParseHexULong(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::uint64_t value = 0;
    if (ParseHex(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("hexadecimal unsigned long long token expected in '" + lexer->FileName() + "' line " + 
            std::to_string(line) + ": (" + *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
std::uint64_t ParseOctalULong(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::uint64_t value = 0;
    if (ParseOctal(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("octal unsigned long long token expected in '" + lexer->FileName() + "' line " + 
            std::to_string(line) + ": (" + 
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
float ParseFloat(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    float value = 0.0f;
    if (ParseFloating<CharT, float>(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("float token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" + 
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
double ParseDouble(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    double value = 0.0;
    if (ParseFloating<CharT, double>(begin, end, value))
    {
        return value;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("double token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" + 
            *s + ")"));
    }
}

template<typename CharT, typename LexerBaseT>
bool ParseBool(const CharT* begin, const CharT* end, LexerBaseT* lexer, int line)
{
    std::string s = soul_expected::lexer::ToString(begin, end);
    if (s == "true")
    {
        return true;
    }
    else if (s == "false")
    {
        return false;
    }
    else
    {
        auto s = soul_expected::lexer::ToString(begin, end);
        if (!s) return std::unexpected<int>(s.error());
        return std::unexpected<int>(util::AllocateError("Boolean token expected in '" + lexer->FileName() + "' line " + std::to_string(line) + ": (" + 
            *s + ")"));
    }
}

} // namespace soul_expected::lexer
