
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/declaration.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.declaration;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::declaration {

template<typename LexerT>
struct DeclarationParser
{
    static std::expected<soul::parser::Match, int> DeclarationSeq(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NamespaceDeclarationSeq(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RBraceNext(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Declaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> BlockDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NoDeclSpecFunctionDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> EmptyDeclaration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> SimpleDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AsmDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Asm(LexerT& lexer);
    static std::expected<soul::parser::Match, int> LinkageSpecification(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NamespaceDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NamedNamespaceDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UnnamedNamespaceDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NestedNamespaceDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NamespaceAliasDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> QualifiedNamespaceSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NamespaceBody(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NestedNamespaceSpecifier(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static std::expected<soul::parser::Match, int> Namespace(LexerT& lexer);
    static std::expected<soul::parser::Match, int> NamespaceName(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UsingDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Using(LexerT& lexer);
    static std::expected<soul::parser::Match, int> UsingDeclaratorList(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UsingDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UsingEnumDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UsingDirective(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> StaticAssertDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> StaticAssert(LexerT& lexer);
    static std::expected<soul::parser::Match, int> AliasDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DeclSpecifierSeq(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Inline(LexerT& lexer);
    static std::expected<soul::parser::Match, int> DeclSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> StorageClassSpecifier(LexerT& lexer);
    static std::expected<soul::parser::Match, int> FunctionSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ExplicitSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> InitDeclaratorList(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> InitDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DeclaratorPushClassScope(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Declarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> PtrDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NoPtrDeclarator(LexerT& lexer, otava::symbols::Context* context, bool trailingDecl);
    static std::expected<soul::parser::Match, int> ParametersAndQualifiers(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TrailingReturnType(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> PtrOperator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AbstractDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NoPtrAbstractDeclarator(LexerT& lexer, otava::symbols::Context* context, bool trailingDecl);
    static std::expected<soul::parser::Match, int> PtrAbstractDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AbstractPackDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NoPtrAbstractPackDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DeclaratorId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Ptr(LexerT& lexer);
    static std::expected<soul::parser::Match, int> LvalueRef(LexerT& lexer);
    static std::expected<soul::parser::Match, int> RvalueRef(LexerT& lexer);
    static std::expected<soul::parser::Match, int> RefQualifier(LexerT& lexer);
    static std::expected<soul::parser::Match, int> CVQualifierSeq(LexerT& lexer);
    static std::expected<soul::parser::Match, int> CVQualifier(LexerT& lexer);
    static std::expected<soul::parser::Match, int> NoexceptSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ThrowSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AttributeDeclaration(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::declaration
