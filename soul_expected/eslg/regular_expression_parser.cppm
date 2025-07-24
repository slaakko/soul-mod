// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.slg.regular.expression.parser;

import std;
import soul_expected.ast.re;

export namespace soul_expected::slg {

class RegularExpressionParser : public soul_expected::ast::re::ExprParser
{
public:
    std::expected<soul_expected::ast::re::Nfa, int> Parse(const std::string& expression, soul_expected::ast::re::LexerContext* lexerContext, 
        const std::string& fileName, int line) override;
};

} // namespace soul_expected::slg
