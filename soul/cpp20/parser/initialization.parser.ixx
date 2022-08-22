
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/initialization.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.initialization;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;
import soul.cpp20.ast;

using namespace soul::cpp20::symbols::context;
using namespace soul::cpp20::ast;

export namespace soul::cpp20::parser::initialization {

template<typename Lexer>
struct InitializationParser
{
    static soul::parser::Match Initializer(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match InitializerClause(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match InitializerList(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
    static soul::parser::Match DesignatedInitializerList(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
    static soul::parser::Match ExprOrBracedInitList(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match BraceOrEqualInitializer(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match BracedInitList(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::initialization
