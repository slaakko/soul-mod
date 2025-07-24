
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/cpp_expected/declaration.parser' using soul parser generator espg version 5.0.0

export module soul_expected.cpp.declaration.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.cpp;

using namespace soul_expected::ast::cpp;

export namespace soul_expected::cpp::declaration::parser {

template<typename LexerT>
struct DeclarationParser
{
    static std::expected<soul_expected::parser::Match, int> BlockDeclaration(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> SimpleDeclaration(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> DeclSpecifierSeq(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::SimpleDeclarationNode* declaration);
    static std::expected<soul_expected::parser::Match, int> DeclSpecifier(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> StorageClassSpecifier(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> TypeSpecifier(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> SimpleTypeSpecifier(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> TypeName(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> TemplateArgumentList(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::TypeNameNode* typeName);
    static std::expected<soul_expected::parser::Match, int> TemplateArgument(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Typedef(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> CVQualifier(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> NamespaceAliasDefinition(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> UsingDeclaration(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> UsingDirective(LexerT& lexer, soul_expected::ast::cpp::Context* context);
};

} // namespace soul_expected::cpp::declaration::parser
