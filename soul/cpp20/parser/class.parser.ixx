
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/class.parser' using soul parser generator spg version 4.0.0

export module soul.cpp20.parser.classes;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;
import soul.cpp20.ast;

using namespace soul::cpp20::symbols::context;
using namespace soul::cpp20::ast;

export namespace soul::cpp20::parser::classes {

template<typename Lexer>
struct ClassParser
{
    static soul::parser::Match ClassSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ClassHead(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ClassKey(Lexer& lexer);
    static soul::parser::Match ClassHeadName(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ClassName(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ClassVirtSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match VirtSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match VirtSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match OverrideKeyword(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match FinalKeyword(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Private(Lexer& lexer);
    static soul::parser::Match VirtualSpecifier(Lexer& lexer);
    static soul::parser::Match BaseClause(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match BaseSpecifierList(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match MemberSpecification(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
    static soul::parser::Match CtorInitializer(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match MemberInitializerList(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::classes
