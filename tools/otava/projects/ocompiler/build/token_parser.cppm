// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.token_parser;

import std;
import soul.lexer.base;
import soul.lexer.token;
import util.unicode;

export namespace otava::token_parser {

template<typename Char>
std::expected<std::string, int> ParseFilePath(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
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
        auto m = util::ToUtf8(token.match.ToString());
        if (!m) return std::unexpected<int>(m.error());
        return std::unexpected<int>(util::AllocateError("invalid file path at " + fileName + ":" +
            std::to_string(token.line) + " : '" + *m + "'"));
    }
    return util::ToUtf8(strValue);
}

} // namespace otava::token_parser
