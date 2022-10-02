
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/guard.parser' using soul parser generator spg version 4.1.0

export module otava.parser.guard;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::guard {

template<typename Lexer>
struct GuardParser
{
    static soul::parser::Match ConceptGuard(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NotDefiningTypeSpecifierGuard(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AssumeTypeGuard(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberFunctionGuard(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match SavedMemberFunctionBodyGuard(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoDeclSpecFunctionDeclarationGuard(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoDeclSpecFunctionDefinitionGuard(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::guard
