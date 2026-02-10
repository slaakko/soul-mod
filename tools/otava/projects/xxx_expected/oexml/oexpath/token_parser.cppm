// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.xpath.token.parser;

import std;
import util;
import soul.lexer.token;
import soul.lexer.base;

export namespace soul::xml::xpath::token::parser {

template<typename CharT>
std::expected<std::string, int> ParseDQString(const std::string& fileName, const soul::lexer::Token<CharT, soul::lexer::LexerBase<CharT>>* token)
{
    std::basic_string<CharT> stringLiteral;
    const CharT* p = token->match.begin;
    const CharT* e = token->match.end;
    if (p != e && *p == '"')
    {
        ++p;
        while (p != e && *p != '\r' && *p != '\n' && *p != '"')
        {
            if (*p == '\\')
            {
                ++p;
                auto esc = util::ParseEscape(p, e, token->ToString());
                if (!esc) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(esc.error()) +
                    "\n(file=" + fileName + ", line=" + std::to_string(token->line) + ")"));
                stringLiteral.append(1, *esc);
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
            auto u = util::ToUtf8(token->match.ToString());
            if (!u) return std::unexpected<int>(u.error());
            return std::unexpected<int>(util::AllocateError("invalid string literal at " + fileName + ":" + std::to_string(token->line) + ": " + *u));
        }
    }
    else
    {
        auto u = util::ToUtf8(token->match.ToString());
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(util::AllocateError("invalid string literal at " + fileName + ":" + std::to_string(token->line) + ": " + *u));
    }
    auto u = util::ToUtf8(stringLiteral);
    if (!u) return std::unexpected<int>(u.error());
    return std::expected<std::string, int>(*u);
}

template<typename CharT>
std::expected<std::string, int> ParseSQString(const std::string& fileName, const soul::lexer::Token<CharT, soul::lexer::LexerBase<CharT>>* token)
{
    std::basic_string<CharT> stringLiteral;
    const CharT* p = token->match.begin;
    const CharT* e = token->match.end;
    if (p != e && *p == '\'')
    {
        ++p;
        while (p != e && *p != '\r' && *p != '\n' && *p != '\'')
        {
            if (*p == '\\')
            {
                ++p;
                auto esc = util::ParseEscape(p, e, token->ToString());
                if (!esc) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(esc.error()) +
                    "\n(file=" + fileName + ", line=" + std::to_string(token->line) + ")"));
                stringLiteral.append(1, *esc);
            }
            else
            {
                stringLiteral.append(1, *p);
                ++p;
            }
        }
        if (p != e && *p == '\'')
        {
            ++p;
        }
        if (p != e)
        {
            auto u = util::ToUtf8(token->match.ToString());
            if (!u) return std::unexpected<int>(u.error());
            return std::unexpected<int>(util::AllocateError("invalid string literal at " + fileName + ":" + std::to_string(token->line) + ": " + *u));
        }
    }
    else
    {
        auto u = util::ToUtf8(token->match.ToString());
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(util::AllocateError("invalid string literal at " + fileName + ":" + std::to_string(token->line) + ": " + *u));
    }
    auto u = util::ToUtf8(stringLiteral);
    if (!u) return std::unexpected<int>(u.error());
    return std::expected<std::string, int>(*u);
}

} // namespace soul::xml::xpath::token::parser
