// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.regular.expression.parser;

import soul.lex.re;
import soul.re.parser;
import soul.lex;
import util;

namespace soul::slg {

std::expected<soul::ast::re::Nfa, int> RegularExpressionParser::Parse(const std::string& expression, soul::ast::re::LexerContext* lexerContext,
    const std::string& fileName, int line)
{
    auto u = util::ToUtf32(expression);
    if (!u) return std::unexpected<int>(u.error());
    std::u32string expr = *u;
    auto rv = soul::lex::re::MakeLexer(expr.c_str(), expr.c_str() + expr.length(), fileName);
    if (!rv) return std::unexpected<int>(rv.error());
    auto& lexer = std::move(*rv);
    using LexerType = decltype(lexer);
    std::expected<soul::ast::re::Nfa, int> prv = soul::re::parser::RegExParser<LexerType>::Parse(lexer, lexerContext);
    if (!prv)
    {
        return std::unexpected<int>(util::AllocateError("error parsing regular expression at " + fileName + ":" + std::to_string(line) + ": " +
            util::GetErrorMessage(prv.error())));
    }
    return std::expected<soul::ast::re::Nfa, int>(*prv);
}

} // namespace soul::slg
