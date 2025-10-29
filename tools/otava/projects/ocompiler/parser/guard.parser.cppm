
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/guard.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.guard;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

export namespace otava::parser::guard {

template<typename LexerT>
struct GuardParser
{
    static std::expected<soul::parser::Match, int> ConceptGuard(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NotDefiningTypeSpecifierGuard(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AssumeTypeGuard(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberFunctionGuard(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SavedMemberFunctionBodyGuard(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SavedCtorInitializerGuard(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NoDeclSpecFunctionDeclarationGuard(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NoDeclSpecFunctionDefinitionGuard(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::guard
