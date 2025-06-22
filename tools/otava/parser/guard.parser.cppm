
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/guard.parser' using soul parser generator spg version 5.0.0

export module otava.parser.guard;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::guard {

template<typename LexerT>
struct GuardParser
{
    static soul::parser::Match ConceptGuard(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match NotDefiningTypeSpecifierGuard(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match AssumeTypeGuard(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberFunctionGuard(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match SavedMemberFunctionBodyGuard(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match SavedCtorInitializerGuard(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoDeclSpecFunctionDeclarationGuard(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoDeclSpecFunctionDefinitionGuard(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::guard
