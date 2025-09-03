// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.regular.expression.parser;

import std;
import soul.ast.re;

export namespace soul::slg {

class RegularExpressionParser : public soul::ast::re::ExprParser
{
public:
    std::expected<soul::ast::re::Nfa, int> Parse(const std::string& expression, soul::ast::re::LexerContext* lexerContext,
        const std::string& fileName, int line) override;
};

} // namespace soul::slg
