// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.token.parser;

import util.unicode;

namespace otava::token::parser {

otava::ast::Suffix ParseIntegerSuffix(const char32_t*& p, const char32_t* e)
{
    otava::ast::Suffix suffix = otava::ast::Suffix::none;
    if (p != e && (*p == 'u' || *p == 'U'))
    {
        suffix = suffix | otava::ast::Suffix::u;
        ++p;
    }
    if (p != e && (*p == 'l' || *p == 'L'))
    {
        ++p;
        if (p != e && (*p == 'l' || *p == 'L'))
        {
            suffix = suffix | otava::ast::Suffix::ll;
            ++p;
        }
        else
        {
            suffix = suffix | otava::ast::Suffix::l;
        }
        if (p != e && (*p == 'u' || *p == 'U'))
        {
            suffix = suffix | otava::ast::Suffix::u;
            ++p;
        }
    }
    if (p != e && (*p == 'z' || *p == 'Z'))
    {
        if ((suffix & (otava::ast::Suffix::l | otava::ast::Suffix::ll)) == otava::ast::Suffix::none)
        {
            suffix = suffix | otava::ast::Suffix::z;
            ++p;
            if (p != e && (*p == 'u' || *p == 'U'))
            {
                suffix = suffix | otava::ast::Suffix::u;
                ++p;
            }
        }
    }
    return suffix;
}

otava::ast::Suffix ParseFloatingSuffix(const char32_t*& p, const char32_t* e)
{
    otava::ast::Suffix suffix = otava::ast::Suffix::none;
    if (p != e && (*p == 'l' || *p == 'L'))
    {
        suffix = suffix | otava::ast::Suffix::l;
        ++p;
    }
    else if (p != e && (*p == 'f' || *p == 'F'))
    {
        suffix = suffix | otava::ast::Suffix::f;
        ++p;
    }
    return suffix;
}

otava::ast::EncodingPrefix ParseEncodingPrefix(const char32_t*& p, const char32_t* e)
{
    otava::ast::EncodingPrefix encodingPrefix = otava::ast::EncodingPrefix::none;
    if (p != e && ((*p == 'u') || (*p == 'U') || (*p == 'L')))
    {
        char32_t c = *p;
        ++p;
        if (p != e && *p == '8')
        {
            ++p;
            encodingPrefix = otava::ast::EncodingPrefix::u8;
        }
        else if (c == 'u')
        {
            encodingPrefix = otava::ast::EncodingPrefix::u;
        }
        else if (c == 'U')
        {
            encodingPrefix = otava::ast::EncodingPrefix::U;
        }
        else if (c == 'L')
        {
            encodingPrefix = otava::ast::EncodingPrefix::L;
        }
    }
    return encodingPrefix;
}

bool IsHexChar(char32_t c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

std::uint64_t ParseHexChar(char32_t c)
{
    if (c >= '0' && c <= '9')
    {
        return static_cast<std::uint64_t>(c) - static_cast<std::uint64_t>('0');
    }
    else if (c >= 'a' && c <= 'f')
    {
        return static_cast<std::uint64_t>(10) + static_cast<std::uint64_t>(c) - static_cast<std::uint64_t>('a');
    }
    else if (c >= 'A' && c <= 'F')
    {
        return static_cast<std::uint64_t>(10) + static_cast<std::uint64_t>(c) - static_cast<std::uint64_t>('A');
    }
    return 0;
}

char32_t ParseEscape(const char32_t*& p, const char32_t* e, bool& valid)
{
    char32_t value = '\0';
    valid = true;
    if (p != e)
    {
        char32_t c = *p;
        switch (c)
        {
            case '\'':
            {
                ++p;
                value = '\'';
                break;
            }
            case '\"':
            {
                ++p;
                value = '\"';
                break;
            }
            case '\?':
            {
                ++p;
                value = '\?';
                break;
            }
            case '\\':
            {
                ++p;
                value = '\\';
                break;
            }
            case 'a':
            {
                ++p;
                value = '\a';
                break;
            }
            case 'b':
            {
                ++p;
                value = '\b';
                break;
            }
            case 'f':
            {
                ++p;
                value = '\f';
                break;
            }
            case 'n':
            {
                ++p;
                value = '\n';
                break;
            }
            case 'r':
            {
                ++p;
                value = '\r';
                break;
            }
            case 't':
            {
                ++p;
                value = '\t';
                break;
            }
            case 'v':
            {
                ++p;
                value = '\v';
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            {
                value = static_cast<char32_t>(static_cast<int>(*p) - static_cast<int>('0'));
                ++p;
                if (p != e && *p >= '0' && *p <= '7')
                {
                    value = static_cast<char32_t>(static_cast<int>(8) * static_cast<int>(value) + static_cast<int>(*p) - static_cast<int>('0'));
                    ++p;
                    if (p != e && *p >= '0' && *p <= '7')
                    {
                        value = static_cast<char32_t>(static_cast<int>(8) * static_cast<int>(value) + static_cast<int>(*p) - static_cast<int>('0'));
                        ++p;
                    }
                }
                break;
            }
            case 'x':
            {
                ++p;
                valid = false;
                while (p != e && IsHexChar(*p))
                {
                    value = static_cast<char32_t>(static_cast<std::uint64_t>(16) * static_cast<std::uint64_t>(value) + ParseHexChar(*p));
                    ++p;
                    valid = true;
                }
                break;
            }
            case 'u':
            {
                ++p;
                for (int i = 0; i < 4; ++i)
                {
                    if (p != e && IsHexChar(*p))
                    {
                        value = static_cast<char32_t>(static_cast<std::uint64_t>(16) * static_cast<std::uint64_t>(value) + ParseHexChar(*p));
                    }
                    else
                    {
                        valid = false;
                        break;
                    }
                    ++p;
                }
                break;
            }
            case 'U':
            {
                ++p;
                for (int i = 0; i < 8; ++i)
                {
                    if (p != e && IsHexChar(*p))
                    {
                        value = static_cast<char32_t>(static_cast<std::uint64_t>(16) * static_cast<std::uint64_t>(value) + ParseHexChar(*p));
                    }
                    else
                    {
                        valid = false;
                        break;
                    }
                    ++p;
                }
                break;
            }
            default:
            {
                value = *p;
                ++p;
                break;
            }
        }
    }
    return value;
}

std::expected<otava::ast::IntegerLiteralNode*, int> ParseIntegerLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token)
{
    std::uint64_t value = 0;
    otava::ast::Base base = otava::ast::Base::decimal;
    otava::ast::Suffix suffix = otava::ast::Suffix::none;
    const char32_t* p = token.match.begin;
    const char32_t* e = token.match.end;
    bool firstWasSingleQuote = false;
    bool lastWasSingleQuote = false;
    bool first = true;
    if (p != e && *p == '0')
    {
        ++p;
        if (p != e && (*p == 'b' || *p == 'B'))
        {
            base = otava::ast::Base::binary;
            ++p;
            while (p != e && (*p == '0' || *p == '1' || *p == '\''))
            {
                if (first)
                {
                    first = false;
                    if (*p == '\'')
                    {
                        firstWasSingleQuote = true;
                    }
                }
                if (*p == '0' || *p == '1')
                {
                    std::uint64_t bit = static_cast<std::uint64_t>(*p) - static_cast<std::uint64_t>('0');
                    value = static_cast<std::uint64_t>(2) * value + bit;
                    lastWasSingleQuote = false;
                }
                else if (*p == '\'')
                {
                    lastWasSingleQuote = true;
                }
                ++p;
            }
            suffix = ParseIntegerSuffix(p, e);
        }
        else if (p != e && (*p == 'x' || *p == 'X'))
        {
            base = otava::ast::Base::hexadecimal;
            ++p;
            while (p != e && (IsHexChar(*p) || *p == '\''))
            {
                if (first)
                {
                    first = false;
                    if (*p == '\'')
                    {
                        firstWasSingleQuote = true;
                    }
                }
                if (*p != '\'')
                {
                    value = static_cast<std::uint64_t>(16) * value + ParseHexChar(*p);
                    lastWasSingleQuote = false;
                }
                else
                {
                    lastWasSingleQuote = true;
                }
                ++p;
            }
            suffix = ParseIntegerSuffix(p, e);
        }
        else
        {
            if (first)
            {
                first = false;
                if (*p == '\'')
                {
                    firstWasSingleQuote = true;
                }
            }
            base = otava::ast::Base::octal;
            while (p != e && ((*p >= '0' && *p <= '7') || *p == '\''))
            {
                if (*p != '\'')
                {
                    value = static_cast<std::uint64_t>(8) * value + static_cast<std::uint64_t>(*p) - static_cast<std::uint64_t>('0');
                    lastWasSingleQuote = false;
                }
                else
                {
                    lastWasSingleQuote = true;
                }
                ++p;
            }
            suffix = ParseIntegerSuffix(p, e);
        }
    }
    else if (p != e && (*p >= '1' && *p <= '9'))
    {
        if (first)
        {
            first = false;
            if (*p == '\'')
            {
                firstWasSingleQuote = true;
            }
        }
        value = *p - '0';
        ++p;
        while (p != e && ((*p >= '0' && *p <= '9') || *p == '\''))
        {
            if (*p != '\'')
            {
                value = static_cast<std::uint64_t>(10) * value + static_cast<std::uint64_t>(*p) - static_cast<std::uint64_t>('0');
                lastWasSingleQuote = false;
            }
            else
            {
                lastWasSingleQuote = true;
            }
            ++p;
        }
        suffix = ParseIntegerSuffix(p, e);
    }
    if (firstWasSingleQuote)
    {
        auto rv = util::ToUtf8(token.ToString());
        if (!rv) return std::unexpected<int>(rv.error());
        std::string tokenStr = *rv;
        std::string errorMessage("invalid integer literal in '" + fileName + "' at line " + std::to_string(sourcePos.line) + ", literal begins with single quote: " +
            tokenStr);
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    else if (lastWasSingleQuote)
    {
        auto rv = util::ToUtf8(token.ToString());
        if (!rv) return std::unexpected<int>(rv.error());
        std::string tokenStr = *rv;
        std::string errorMessage("invalid integer literal in '" + fileName + "' at line " + std::to_string(sourcePos.line) + ", literal ends with single quote: " +
            tokenStr);
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    else if (p != e)
    {
        auto rv = util::ToUtf8(token.ToString());
        if (!rv) return std::unexpected<int>(rv.error());
        std::string tokenStr = *rv;
        std::string errorMessage("invalid integer literal in '" + fileName + "' at line " + std::to_string(sourcePos.line) + ": " + tokenStr);
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    else
    {
        return std::expected<otava::ast::IntegerLiteralNode*, int>(new otava::ast::IntegerLiteralNode(sourcePos, value, suffix, base, token.ToString()));
    }
}

std::expected<otava::ast::FloatingLiteralNode*, int> ParseFloatingLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token)
{
    std::string s;
    double value = 0.0;
    Suffix suffix = Suffix::none;
    Base base = Base::decimal;
    const char32_t* p = token.match.begin;
    const char32_t* e = token.match.end;
    if (p != e && *p == '0')
    {
        s.append(1, static_cast<char>(*p));
        ++p;
        if (p != e && (*p == 'x' || *p == 'X'))
        {
            base = Base::hexadecimal;
            s.append(1, static_cast<char>(*p));
            ++p;
            while (p != e && ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F') || *p == '\''))
            {
                if (*p != '\'')
                {
                    s.append(1, static_cast<char>(*p));
                }
                ++p;
            }
            if (p != e && *p == '.')
            {
                s.append(1, static_cast<char>(*p));
                ++p;
            }
            while (p != e && ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F') || *p == '\''))
            {
                if (*p != '\'')
                {
                    s.append(1, static_cast<char>(*p));
                }
                ++p;
            }
            if (p != e && (*p == 'p' || *p == 'P'))
            {
                s.append(1, static_cast<char>(*p));
                ++p;
            }
            if (p != e && (*p == '-' || *p == '+'))
            {
                s.append(1, static_cast<char>(*p));
                ++p;
            }
            while (p != e && ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F') || *p == '\''))
            {
                if (*p != '\'')
                {
                    s.append(1, static_cast<char>(*p));
                }
                ++p;
            }
        }
    }
    if (base == Base::decimal)
    {
        while (p != e && ((*p >= '0' && *p <= '9') || *p == '\''))
        {
            if (*p != '\'')
            {
                s.append(1, static_cast<char>(*p));
            }
            ++p;
        }
        if (p != e && *p == '.')
        {
            s.append(1, static_cast<char>(*p));
            ++p;
        }
        while (p != e && ((*p >= '0' && *p <= '9') || *p == '\''))
        {
            if (*p != '\'')
            {
                s.append(1, static_cast<char>(*p));
            }
            ++p;
        }
        if (p != e && (*p == 'e' || *p == 'E'))
        {
            s.append(1, static_cast<char>(*p));
            ++p;
        }
        if (p != e && (*p == '-' || *p == '+'))
        {
            s.append(1, static_cast<char>(*p));
            ++p;
        }
        while (p != e && ((*p >= '0' && *p <= '9') || *p == '\''))
        {
            if (*p != '\'')
            {
                s.append(1, static_cast<char>(*p));
            }
            ++p;
        }
    }
    value = std::strtod(s.c_str(), nullptr);
    suffix = ParseFloatingSuffix(p, e);
    if (p != e)
    {
        auto rv = util::ToUtf8(token.ToString());
        if (!rv) return std::unexpected<int>(rv.error());
        std::string tokenStr = *rv;
        return std::unexpected<int>(util::AllocateError("invalid floating literal in '" + fileName + "' at line " + std::to_string(sourcePos.line) + ": " + tokenStr));
    }
    return std::expected<otava::ast::FloatingLiteralNode*, int>(new otava::ast::FloatingLiteralNode(sourcePos, value, suffix, base, token.ToString()));
}

std::expected<otava::ast::CharacterLiteralNode*, int> ParseCharacterLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token)
{
    bool valid = false;
    bool hasMultipleCharacters = false;
    char32_t value = '\0';
    const char32_t* p = token.match.begin;
    const char32_t* e = token.match.end;
    EncodingPrefix encodingPrefix = ParseEncodingPrefix(p, e);
    bool valueParsed = false;
    if (p != e && '\'')
    {
        ++p;
        while (p != e && *p != '\'')
        {
            if (p != e && *p == '\\')
            {
                ++p;
                bool escapeValid = false;
                value = ParseEscape(p, e, escapeValid);
                if (escapeValid)
                {
                    valueParsed = true;
                }
            }
            else if (p != e && *p != '\'' && *p != '\\' && *p != '\n')
            {
                if (value == '\0')
                {
                    value = *p;
                    valueParsed = true;
                }
                else
                {
                    hasMultipleCharacters = true;
                }
                ++p;
            }
        }
        if (p != e && valueParsed && *p == '\'')
        {
            ++p;
            valid = true;
        }
    }
    if (p != e || !valid)
    {
        auto rv = util::ToUtf8(token.ToString());
        if (!rv) return std::unexpected<int>(rv.error());
        std::string tokenStr = *rv;
        return std::unexpected<int>(util::AllocateError("invalid character literal in '" + fileName + "' at line " + std::to_string(sourcePos.line) + 
            ": " + tokenStr));
    }
    return std::expected<otava::ast::CharacterLiteralNode*, int>(new otava::ast::CharacterLiteralNode(sourcePos, value, encodingPrefix, 
        token.ToString(), hasMultipleCharacters));
}

std::expected<otava::ast::RawStringLiteralNode*, int> ParseRawStringLiteral(const soul::ast::SourcePos& sourcePos, soul::lexer::LexerBase<char32_t>& lexer)
{
    auto t = lexer.GetToken(lexer.GetPos());
    if (!t) return std::unexpected<int>(t.error());
    const auto* token = *t;
    const char32_t* start = token->match.begin;
    const char32_t* p = start;
    const char32_t* e = lexer.End();
    bool valid = false;
    bool stop = false;
    std::u32string value;
    std::u32string rep;
    EncodingPrefix encodingPrefix = ParseEncodingPrefix(p, e);
    rep.append(start, p);
    int state = 0;
    int index = 0;
    std::u32string dm;
    std::u32string tmp;
    while (p != e && !stop && !valid)
    {
        switch (state)
        {
            case 0:
            {
                if (*p == 'R')
                {
                    state = 1;
                }
                else
                {
                    stop = true;
                }
                break;
            }
            case 1:
            {
                if (*p == '"')
                {
                    state = 2;
                }
                else
                {
                    stop = true;
                }
                break;
            }
            case 2:
            {
                switch (*p)
                {
                case ' ': case ')': case '\\': case '\t': case '\v': case '\f': case '\n':
                {
                    stop = true;
                    break;
                }
                case '(':
                {
                    dm.append(1, '"');
                    state = 3;
                    break;
                }
                default:
                {
                    dm.append(1, *p);
                    break;
                }
                }
                break;
            }
            case 3:
            {
                switch (*p)
                {
                case ')':
                {
                    tmp = U")";
                    index = 0;
                    state = 4;
                    break;
                }
                case '\n':
                {
                    value.append(1, *p);
                    lexer.SetLine(lexer.Line() + 1);
                    break;
                }
                default:
                {
                    value.append(1, *p);
                    break;
                }
                }
                break;
            }
            case 4:
            {
                if (index == dm.length())
                {
                    valid = true;
                }
                else if (*p == dm[index])
                {
                    tmp.append(1, *p);
                    ++index;
                }
                else
                {
                    value.append(tmp);
                    switch (*p)
                    {
                    case ')':
                    {
                        tmp = U")";
                        index = 0;
                        break;
                    }
                    default:
                    {
                        value.append(1, *p);
                        state = 3;
                        break;
                    }
                    }
                }
                break;
            }
        }
        if (!valid)
        {
            rep.append(1, *p);
            ++p;
        }
    }
    if (state == 4 && index == dm.length())
    {
        valid = true;
    }
    if (valid)
    {
        lexer.CurrentToken().match.end = p;
        lexer.CurrentLexeme().end = p;
        lexer.SetCurrentMatchEnd(p);
        lexer.EraseTail();
        lexer.SetPos(p);
        std::expected<bool, int> rv = lexer.Increment();
        if (!rv) return std::unexpected<int>(rv.error());
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("invalid raw string literal in '" + lexer.FileName() + "' at line " + std::to_string(lexer.Line())));
    }
    return std::expected<otava::ast::RawStringLiteralNode*, int>(new otava::ast::RawStringLiteralNode(sourcePos, value, encodingPrefix, dm, rep));
}

std::expected<otava::ast::StringLiteralNode*, int> ParseStringLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token)
{
    bool valid = false;
    std::u32string value;
    const char32_t* p = token.match.begin;
    const char32_t* e = token.match.end;
    EncodingPrefix encodingPrefix = ParseEncodingPrefix(p, e);
    if (p != e && *p == '"')
    {
        ++p;
        while (p != e)
        {
            if (*p == '\\')
            {
                ++p;
                bool escapeValid = false;
                char32_t escapeValue = ParseEscape(p, e, escapeValid);
                if (escapeValid)
                {
                    value.append(1, escapeValue);
                }
                else
                {
                    break;
                }
            }
            else if (*p != '"' && *p != '\\' && *p != '\n')
            {
                value.append(1, *p);
                ++p;
            }
            else
            {
                break;
            }
        }
        if (p != e && *p == '"')
        {
            ++p;
            valid = true;
        }
    }
    if (p != e || !valid)
    {
        auto rv = util::ToUtf8(token.ToString());
        if (!rv) return std::unexpected<int>(rv.error());
        std::string tokenStr = *rv;
        return std::unexpected<int>(util::AllocateError("invalid string literal in '" + fileName + "' at line " + std::to_string(sourcePos.line) + ": " +
            tokenStr));
    }
    return std::expected<otava::ast::StringLiteralNode*, int>(new otava::ast::StringLiteralNode(sourcePos, value, encodingPrefix, token.ToString()));
}

std::expected<otava::ast::IdentifierNode*, int> ParseIdentifier(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token)
{
    std::u32string s;
    const char32_t* p = token.match.begin;
    const char32_t* e = token.match.end;
    bool valid = true;
    while (p != e && valid)
    {
        char32_t value = '\0';
        if (*p == '\\')
        {
            ++p;
            if (p != e)
            {
                if (*p == 'u')
                {
                    ++p;
                    for (int i = 0; i < 4; ++i)
                    {
                        if (p != e && IsHexChar(*p))
                        {
                            value = static_cast<char32_t>(16 * static_cast<int>(value) + ParseHexChar(*p));
                        }
                        else
                        {
                            valid = false;
                            break;
                        }
                        ++p;
                    }
                }
                else if (*p == 'U')
                {
                    ++p;
                    for (int i = 0; i < 8; ++i)
                    {
                        if (p != e && IsHexChar(*p))
                        {
                            value = static_cast<char32_t>(16 * static_cast<int>(value) + ParseHexChar(*p));
                        }
                        else
                        {
                            valid = false;
                            break;
                        }
                        ++p;
                    }
                }
            }
        }
        else
        {
            value = *p;
            ++p;
        }
        s.append(1, value);
    }
    if (p != e || !valid)
    {
        auto rv = util::ToUtf8(token.ToString());
        if (!rv) return std::unexpected<int>(rv.error());
        std::string tokenStr = *rv;
        return std::unexpected<int>(util::AllocateError("invalid identifier in '" + fileName + "' at line " + std::to_string(sourcePos.line) + ": " + tokenStr));
    }
    return std::expected<otava::ast::IdentifierNode*, int>(new otava::ast::IdentifierNode(sourcePos, s));
}

} // namespace otava::token::parser
