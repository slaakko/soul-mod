
// this file has been automatically generated from 'C:/work/soul-mod/soul/slg/expression_file.parser' using soul parser generator spg version 4.1.0

export module soul.slg.expression.file.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::expression::file::parser {

template<typename LexerT>
struct ExpressionFileParser
{
    static std::unique_ptr<soul::ast::slg::ExpressionFile> Parse(LexerT& lexer);
    static soul::parser::Match ExpressionFile(LexerT& lexer);
    static soul::parser::Match Expression(LexerT& lexer);
};

} // namespace soul::slg::expression::file::parser
