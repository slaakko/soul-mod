// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.re.token.parser;

import std;
import util;
import soul.lexer.token;
import soul.lexer.base;

export namespace soul::re::token::parser {

template<typename CharT>
std::expected<CharT, int> MakeEscapeValue(const std::string& fileName, const soul::lexer::Token<CharT, soul::lexer::LexerBase<CharT>>* token)
{
    const CharT* p = token->match.begin;
    const CharT* e = token->match.end;
    if (p != e && *p == '\\')
    {
        ++p;
    }
    std::expected<CharT, int> rv = util::ParseEscape(p, e, token->ToString());
    if (!rv)
    {
        int error = util::AllocateError(util::GetErrorMessage(rv.error()) + "\n(file=" + fileName + ", line=" + std::to_string(token->line) + ")");
        return std::unexpected<int>(error);
    }
    return *rv;
}

} // namespace soul::re::token::parser
