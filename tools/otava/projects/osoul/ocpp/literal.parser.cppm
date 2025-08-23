
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ocpp/literal.parser' using soul parser generator oespg version 5.0.0

export module soul.cpp.literal.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::literal::parser {

template<typename LexerT>
struct LiteralParser
{
    static std::expected<soul::parser::Match, int> Literal(LexerT& lexer, soul::ast::cpp::Context* context);
};

} // namespace soul::cpp::literal::parser
