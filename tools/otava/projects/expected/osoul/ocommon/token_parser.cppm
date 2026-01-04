// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.common.token.parser;

import std;
import util;
import soul.lexer.token;
import soul.lexer.base;

export namespace soul::common::token::parser {

template<typename CharT>
std::expected<CharT, int> ParseCharLiteral(const std::string& fileName, const soul::lexer::Token<CharT, soul::lexer::LexerBase<CharT>>* token)
{
    std::expected<CharT, int> u = util::ParseCharLiteral(token->ToString());
    if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(token->line) + ")"));
    return u;
}

template<typename CharT>
std::expected<std::basic_string<CharT>, int> ParseStringLiteral(const std::string& fileName,
    const soul::lexer::Token<CharT, soul::lexer::LexerBase<CharT>>* token)
{
    std::expected<CharT, int> u = util::ParseStringLiteral(token->ToString());
    if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(token->line) + ")"));
    return u;
}

template<typename CharT>
std::expected<std::string, int> MakeExprStringValue(const std::string& fileName, const soul::lexer::Token<CharT, soul::lexer::LexerBase<CharT>>* token)
{
    std::basic_string<CharT> strValue;
    const CharT* p = token->match.begin;
    const CharT* e = token->match.end;
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
        std::expected<std::string, int> u = util::ToUtf8(token->match.ToString());
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(
            util::AllocateError("expression string cannot be parsed from string \"" + *u + "\":\n(file='" + fileName + "', line=" + std::to_string(token->line) + ")"));
    }
    return util::ToUtf8(strValue);
}

template<typename CharT>
std::expected<std::string, int> MakeFilePath(const std::string& fileName, const soul::lexer::Token<CharT, soul::lexer::LexerBase<CharT>>* token)
{
    std::basic_string<CharT> strValue;
    const CharT* p = token->match.begin;
    const CharT* e = token->match.end;
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
        std::expected<std::string, int> u = util::ToUtf8(token->match.ToString());
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(
            util::AllocateError("file path cannot be parsed from string \"" + *u + "\":\n(file='" + fileName + "', line=" + std::to_string(token->line) + ")"));
    }
    return util::ToUtf8(strValue);
}

} // namespace soul::common::token::parser
