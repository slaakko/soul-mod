
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/oslg/expression_file.parser' using soul parser generator oespg version 5.0.0

export module soul.slg.expression.file.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::expression::file::parser {

template<typename LexerT>
struct ExpressionFileParser
{
    static std::expected<std::unique_ptr<soul::ast::slg::ExpressionFile>, int> Parse(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ExpressionFile(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Expression(LexerT& lexer);
};

} // namespace soul::slg::expression::file::parser
