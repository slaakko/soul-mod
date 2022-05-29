// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.common.token.parser;

import std.core;

import soul.lexer.token;
import soul.lexer.base;
import util.unicode;

using namespace util;

export namespace soul::common::token::parser {

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
        throw std::runtime_error("invalid expression string literal at " + fileName + ":" + std::to_string(token.line) + ": " + ToUtf8(token.match.ToString()));
    }
    return ToUtf8(strValue);
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
        throw std::runtime_error("invalid file path at " + fileName + ":" + std::to_string(token.line) + " : '" + ToUtf8(token.match.ToString()) + "'");
    }
    return ToUtf8(strValue);
}

} // namespace soul::common::token::parser
