// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.common.token.parser;

import std;
import soul.lexer.token;
import soul.lexer.base;
import util.unicode;

export namespace soul::common::token::parser {

template<typename Char>
void ParseHexChar(const std::string& fileName, char32_t& value, const Char*& p, const Char* e, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    if (p != e)
    {
        Char s = *p;
        switch (s)
        {
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            {
                value = 16 * value + *p - '0';
                break;
            }
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            {
                value = 16 * value + 10 + *p - 'A';
                break;
            }
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            {
                value = 16 * value + 10 + *p - 'a';
                break;
            }
        }
        ++p;
    }
    else
    {
        throw std::runtime_error("hex character expected at " + fileName + ":" + std::to_string(token.line) + ": " + util::ToUtf8(token.match.ToString()));
    }
}

template<typename Char>
char32_t ParseEscape(const std::string& fileName, const Char*& p, const Char* e, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    char32_t value = '\0';
    if (p != e && (*p == 'x' || *p == 'X'))
    {
        ++p;
        while (p != e && ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F')))
        {
            ParseHexChar(fileName, value, p, e, token);
        }
    }
    else if (p != e && (*p == 'd' || *p == 'D'))
    {
        ++p;
        while (p != e && *p >= '0' && *p <= '9')
        {
            value = 10 * value + (*p - '0');
            ++p;
        }
    }
    else if (p != e && (*p >= '0' && *p <= '7'))
    {
        while (p != e && *p >= '0' && *p <= '7')
        {
            value = 8 * value + (*p - '0');
            ++p;
        }
    }
    else if (p != e && *p == 'u')
    {
        ++p;
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
    }
    else if (p != e && *p == 'U')
    {
        ++p;
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
        ParseHexChar(fileName, value, p, e, token);
    }
    else if (p != e)
    {
        Char s = *p;
        switch (s)
        {
            case 'a': value = '\a'; break;
            case 'b': value = '\b'; break;
            case 'f': value = '\f'; break;
            case 'n': value = '\n'; break;
            case 'r': value = '\r'; break;
            case 't': value = '\t'; break;
            case 'v': value = '\v'; break;
            default: value = s; break;
        }
        ++p;
    }
    return value;
}

template<typename Char>
char32_t ParseCharLiteral(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    char32_t charLit = '\0';
    const Char* p = token.match.begin;
    const Char* e = token.match.end;
    bool first = true;
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
                    charLit = ParseEscape(fileName, p, e, token);
                    first = false;
                }
                else
                {
                    throw std::runtime_error("invalid character literal at " + fileName + ":" + std::to_string(token.line) + ": " + util::ToUtf8(token.match.ToString()));
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
                    throw std::runtime_error("invalid character literal at " + fileName + ":" + std::to_string(token.line) + ": " + util::ToUtf8(token.match.ToString()));
                }
            }
        }
        if (p != e && *p == '\'')
        {
            ++p;
        }
        if (p != e)
        {
            throw std::runtime_error("invalid character literal at " + fileName + ":" + std::to_string(token.line) + ": " + util::ToUtf8(token.match.ToString()));
        }
    }
    else
    {
        throw std::runtime_error("invalid character literal at " + fileName + ":" + std::to_string(token.line) + ": " + util::ToUtf8(token.match.ToString()));
    }
    return charLit;
}

template<typename Char>
std::u32string ParseStringLiteral(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    std::u32string stringLiteral;
    const Char* p = token.match.begin;
    const Char* e = token.match.end;
    if (p != e && *p == '"')
    {
        ++p;
        while (p != e && *p != '\r' && *p != '\n' && *p != '"')
        {
            if (*p == '\\')
            {
                ++p;
                stringLiteral.append(1, ParseEscape(fileName, p, e, token));
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
            throw std::runtime_error("invalid string literal at " + fileName + ":" + std::to_string(token.line) + ": " + util::ToUtf8(token.match.ToString()));
        }
    }
    else
    {
        throw std::runtime_error("invalid string literal at " + fileName + ":" + std::to_string(token.line) + ": " + util::ToUtf8(token.match.ToString()));
    }
    return stringLiteral;
}

template<typename Char>
std::string MakeExprStringValue(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    std::u32string strValue;
    const Char* p = token.match.begin;
    const Char* e = token.match.end;
    if (p != e && *p == '"')
    {
        ++p;
    }
    while (p != e && *p != '\r' && *p != '\n' && *p != '"')
    {
        if (*p == '\\')
        {
            ++p;
            if (p != e && *p == '"')
            {
                strValue.append(1, '"');
                ++p;
            }
            else
            {
                strValue.append(1, '\\');
                strValue.append(1, *p);
                ++p;
            }
        }
        else
        {
            strValue.append(1, *p);
            ++p;
        }
    }
    if (p != e && *p == '"')
    {
        ++p;
    }
    if (p != e)
    {
        throw std::runtime_error("invalid expression string literal at " + fileName + ":" + std::to_string(token.line) + ": " + util::ToUtf8(token.match.ToString()));
    }
    return util::ToUtf8(strValue);
}

template<typename Char>
std::string MakeFilePath(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    std::u32string strValue;
    const Char* p = token.match.begin;
    const Char* e = token.match.end;
    if (p != e && *p == '<')
    {
        ++p;
    }
    while (p != e && *p != '>')
    {
        strValue.append(1, *p);
        ++p;
    }
    if (p != e && *p == '>')
    {
        ++p;
    }
    if (p != e)
    {
        throw std::runtime_error("invalid file path at " + fileName + ":" + std::to_string(token.line) + " : '" + util::ToUtf8(token.match.ToString()) + "'");
    }
    return util::ToUtf8(strValue);
}

} // namespace soul::common::token::parser
