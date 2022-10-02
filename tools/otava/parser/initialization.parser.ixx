
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/initialization.parser' using soul parser generator spg version 4.1.0

export module otava.parser.initialization;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

using namespace otava::symbols::context;
using namespace otava::ast;

export namespace otava::parser::initialization {

template<typename Lexer>
struct InitializationParser
{
    static soul::parser::Match Initializer(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match InitializerClause(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match InitializerList(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match DesignatedInitializerList(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match DesignatedInitializerClause(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Designator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ExprOrBracedInitList(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match BraceOrEqualInitializer(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match BracedInitList(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::initialization
