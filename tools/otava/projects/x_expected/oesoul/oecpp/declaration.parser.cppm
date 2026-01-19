
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ocpp/declaration.parser' using soul parser generator ospg version 5.0.0

export module soul.cpp.declaration.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

export namespace soul::cpp::declaration::parser {

template<typename LexerT>
struct DeclarationParser
{
    static std::expected<soul::parser::Match, int> BlockDeclaration(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> SimpleDeclaration(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> DeclSpecifierSeq(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::SimpleDeclarationNode* declaration);
    static std::expected<soul::parser::Match, int> DeclSpecifier(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> StorageClassSpecifier(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> TypeSpecifier(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> SimpleTypeSpecifier(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> TypeName(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> TemplateArgumentList(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::TypeNameNode* typeName);
    static std::expected<soul::parser::Match, int> TemplateArgument(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Typedef(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> CVQualifier(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> NamespaceAliasDefinition(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> UsingDeclaration(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> UsingDirective(LexerT& lexer, soul::ast::cpp::Context* context);
};

} // namespace soul::cpp::declaration::parser
