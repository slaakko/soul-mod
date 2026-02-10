
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/initialization.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.initialization;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::initialization {

template<typename LexerT>
struct InitializationParser
{
    static std::expected<soul::parser::Match, int> Initializer(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> InitializerClause(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> InitializerList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static std::expected<soul::parser::Match, int> DesignatedInitializerList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static std::expected<soul::parser::Match, int> DesignatedInitializerClause(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Designator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ExprOrBracedInitList(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> BraceOrEqualInitializer(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> BracedInitList(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::initialization
