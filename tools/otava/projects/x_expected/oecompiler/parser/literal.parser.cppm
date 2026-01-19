
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/literal.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.literal;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

export namespace otava::parser::literal {

template<typename LexerT>
struct LiteralParser
{
    static std::expected<soul::parser::Match, int> Literal(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UserDefinedLiteral(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UdSuffix(LexerT& lexer);
    static std::expected<soul::parser::Match, int> LiteralOperatorId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> StringLiteral(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::literal
