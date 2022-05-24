// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.regular.expression.parser;

import soul.lex.re;
import soul.re.par;
import util;

namespace soul::slg {

soul::ast::re::Nfa RegularExpressionParser::Parse(const std::string& expression, soul::ast::re::LexerContext* lexerContext, const std::string& fileName, int line)
{
    try
    {
        std::u32string expr = util::ToUtf32(expression);
        auto lexer = soul::lex::re::MakeLexer(expr.c_str(), expr.c_str() + expr.length(), fileName);
        using LexerType = decltype(lexer);
        return soul::re::par::RegExParser<LexerType>::Parse(lexer, lexerContext);
    }
    catch (const std::exception& ex)
    {
        throw std::runtime_error("error parsing regular expression at " + fileName + ":" + std::to_string(line) + ": " + ex.what());
    }

}

} // namespace soul::slg
