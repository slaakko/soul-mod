// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.re.token.parser;

import std;
import util_expected;
import soul_expected.lexer.token;
import soul_expected.lexer.base;
import util_expected.unicode;

export namespace soul_expected::re::token::parser {

template<typename CharT>
std::expected<CharT, int> MakeEscapeValue(const std::string& fileName, const soul_expected::lexer::Token<CharT, soul_expected::lexer::LexerBase<CharT>>* token)
{
    const CharT* p = token->match.begin;
    std::expected<CharT, int> rv = util::ParseEscape(p, token->match.end, token->ToString());
    if (!rv)
    {
        int error = util::AllocateError(util::GetErrorMessage(rv.error()) + "\n(file=" + fileName + ", line=" + std::to_string(token->line) + ")");
        return std::unexpected<int>(error);
    }
    return *rv;
}

} // namespace soul_expected::re::token::parser
