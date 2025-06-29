// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.json.token.parser;

import std;
import util;
import soul.lexer.token;
import soul.lexer.base;

export namespace soul::json::token::parser {

template<typename Char>
void ParseHexChar(char32_t& value, const char32_t*& p, const char32_t* e, const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    if (p != e)
    {
        switch (static_cast<char32_t>(*p))
        {
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            {
                value = static_cast<char32_t>(16 * static_cast<int>(value) + static_cast<int>(*p) - static_cast<int>('0'));
                break;
            }
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            {
                value = static_cast<char32_t>(16 * static_cast<int>(value) + 10 + static_cast<int>(*p) - static_cast<int>('A'));
                break;
            }
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            {
                value = static_cast<char32_t>(16 * static_cast<int>(value) + 10 + static_cast<int>(*p) - static_cast<int>('a'));
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
char32_t ParseEscape(const char32_t*& p, const char32_t* e, const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    char32_t value = '\0';
    if (p != e && (*p == 'x' || *p == 'X'))
    {
        ++p;
        while (p != e && ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F')))
        {
            ParseHexChar(value, p, e, fileName, token);
        }
    }
    else if (p != e && (*p == 'd' || *p == 'D'))
    {
        ++p;
        while (p != e && *p >= '0' && *p <= '9')
        {
            value = static_cast<char32_t>(10 * static_cast<int>(value) + static_cast<int>(*p) - static_cast<int>('0'));
            ++p;
        }
    }
    else if (p != e && (*p >= '0' && *p <= '7'))
    {
        while (p != e && *p >= '0' && *p <= '7')
        {
            value = static_cast<char32_t>(8 * static_cast<int>(value) + static_cast<int>(*p) - static_cast<int>('0'));
            ++p;
        }
    }
    else if (p != e && *p == 'u')
    {
        ++p;
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
    }
    else if (p != e && *p == 'U')
    {
        ++p;
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
        ParseHexChar(value, p, e, fileName, token);
    }
    else if (p != e)
    {
        switch (static_cast<char32_t>(*p))
        {
        case 'a': value = '\a';
            break;
        case 'b': value = '\b';
            break;
        case 'f': value = '\f';
            break;
        case 'n': value = '\n';
            break;
        case 'r': value = '\r';
            break;
        case 't': value = '\t';
            break;
        case 'v': value = '\v';
            break;
        default: value = *p;
            break;
        }
        ++p;
    }
    return value;
}

template<typename Char>
double ParseNumber(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    double value = 0.0;
    const char32_t* p = token.match.begin;
    const char32_t* e = token.match.end;
    while (p != e && *p >= '0' && *p <= '9')
    {
        ++p;
    }
    if (p != e && *p == '.')
    {
        ++p;
    }
    while (p != e && *p >= '0' && *p <= '9')
    {
        ++p;
    }
    if (p != e && (*p == 'e' || *p == 'E'))
    {
        ++p;
    }
    if (p != e && (*p == '+' || *p == '-'))
    {
        ++p;
    }
    while (p != e && *p >= '0' && *p <= '9')
    {
        ++p;
    }
    if (token.match.begin != e)
    {
        std::string s = util::ToUtf8(std::basic_string<Char>(token.match.begin, p));
        std::stringstream sstream;
        sstream.str(s);
        sstream >> value;
        if (!sstream)
        {
            throw std::runtime_error("invalid floating point literal in '" + fileName + "' at line " + std::to_string(token.line) + ": " +
                util::ToUtf8(token.match.ToString()));
        }
    }
    if (p != e)
    {
        throw std::runtime_error("invalid floating point literal in '" + fileName + "' at line " + std::to_string(token.line) + ": " +
            util::ToUtf8(token.match.ToString()));
    }
    return value;
}

template<typename Char>
std::u32string ParseStringLiteral(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    std::u32string value;
    const char32_t* p = token.match.begin;
    const char32_t* e = token.match.end;
    if (p != e && *p == '"')
    {
        ++p;
    }
    while (p != e && *p != '"')
    {
        if (*p == '\\')
        {
            ++p;
            value.append(1, ParseEscape(p, e, fileName, token));
        }
        else
        {
            value.append(1, *p);
            ++p;
        }
    }
    if (p != e && *p == '"')
    {
        ++p;
    }
    if (p != e)
    {
        throw std::runtime_error("invalid string literal in '" + fileName + "' at line " + std::to_string(token.line) + ": " +
            util::ToUtf8(token.match.ToString()));
    }
    return value;
}

} // namespace soul::json::token::parser

