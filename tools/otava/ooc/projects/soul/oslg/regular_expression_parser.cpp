// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.regular.expression.parser;

import soul.lex.re;
import soul.re.parser;
import util;

namespace soul::slg {

soul::ast::re::Nfa* TryParse(const std::string& expression, soul::ast::re::LexerContext* lexerContext, const std::string& fileName, int line)
{
    std::u32string expr = util::ToUtf32(expression);
    auto lxr = soul::lex::re::MakeLexer(expr.c_str(), expr.c_str() + expr.length(), fileName);
    using LexerType = soul::lexer::Lexer<soul::lex::re::RegExLexer<char32_t>, char32_t>;
    soul::ast::re::Nfa nfa = soul::re::parser::RegExParser<LexerType>::Parse(lxr, lexerContext);
    return new soul::ast::re::Nfa(nfa.Start(), nfa.End());
}

soul::ast::re::Nfa* RegularExpressionParser::Parse(const std::string& expression, soul::ast::re::LexerContext* lexerContext, const std::string& fileName, int line)
{
    try
    {
        return TryParse(expression, lexerContext, fileName, line);
    }
    catch (const std::exception& ex)
    {
        throw std::runtime_error("error parsing regular expression at " + fileName + ":" + std::to_string(line) + ": " + ex.what());
    }
}

} // namespace soul::slg
