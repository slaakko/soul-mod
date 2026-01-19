
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/class.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.classes;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::classes {

template<typename LexerT>
struct ClassParser
{
    static std::expected<soul::parser::Match, int> ClassSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ClassHead(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ClassKey(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ClassHeadName(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ClassName(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ClassVirtSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> VirtSpecifierSeq(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> VirtSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> OverrideKeyword(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> FinalKeyword(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> BaseClause(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> BaseSpecifierList(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> BaseSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ClassOrDeclType(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberSpecification(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static std::expected<soul::parser::Match, int> MemberDeclarationReset(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RBraceNext(LexerT& lexer);
    static std::expected<soul::parser::Match, int> MemberDeclSpecifiers(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RetMemberDeclSpecifiers(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberFunctionDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RetMemberFunctionDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberTemplateDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberDeclaratorList(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CtorInitializer(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CtorInitializerGuarded(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CtorInitializerUnguarded(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CtorInitializerSaved(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberInitializerList(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberInitializer(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MemberInitializerId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> PureSpecifier(LexerT& lexer);
    static std::expected<soul::parser::Match, int> AccessSpecifier(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Private(LexerT& lexer);
    static std::expected<soul::parser::Match, int> VirtualSpecifier(LexerT& lexer);
};

} // namespace otava::parser::classes
