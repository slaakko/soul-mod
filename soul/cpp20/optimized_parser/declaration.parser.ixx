
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_parser/declaration.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.declaration;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;
import soul.cpp20.ast;

using namespace soul::cpp20::symbols::context;
using namespace soul::cpp20::ast;

export namespace soul::cpp20::parser::declaration {

template<typename Lexer>
struct DeclarationParser
{
    static soul::parser::Match DeclarationSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NamespaceDeclarationSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match RBraceNext(Lexer& lexer);
    static soul::parser::Match Declaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match BlockDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NoDeclSpecFunctionDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match EmptyDeclaration(Lexer& lexer);
    static soul::parser::Match SimpleDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AsmDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Asm(Lexer& lexer);
    static soul::parser::Match LinkageSpecification(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NamespaceDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NamedNamespaceDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UnnamedNamespaceDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NestedNamespaceDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NamespaceAliasDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match QualifiedNamespaceSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NamespaceBody(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NestedNamespaceSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
    static soul::parser::Match Namespace(Lexer& lexer);
    static soul::parser::Match NamespaceName(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UsingDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Using(Lexer& lexer);
    static soul::parser::Match UsingDeclaratorList(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UsingDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UsingEnumDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UsingDirective(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match StaticAssertDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match StaticAssert(Lexer& lexer);
    static soul::parser::Match AliasDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DeclSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Inline(Lexer& lexer);
    static soul::parser::Match DeclSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match StorageClassSpecifier(Lexer& lexer);
    static soul::parser::Match FunctionSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExplicitSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match InitDeclaratorList(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match InitDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DeclaratorPushClassScope(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Declarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match PtrDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NoPtrDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context, bool trailingDecl);
    static soul::parser::Match ParametersAndQualifiers(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TrailingReturnType(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match PtrOperator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AbstractDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NoPtrAbstractDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context, bool trailingDecl);
    static soul::parser::Match PtrAbstractDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AbstractPackDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NoPtrAbstractPackDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DeclaratorId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Ptr(Lexer& lexer);
    static soul::parser::Match LvalueRef(Lexer& lexer);
    static soul::parser::Match RvalueRef(Lexer& lexer);
    static soul::parser::Match RefQualifier(Lexer& lexer);
    static soul::parser::Match CVQualifierSeq(Lexer& lexer);
    static soul::parser::Match CVQualifier(Lexer& lexer);
    static soul::parser::Match NoexceptSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ThrowSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AttributeDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::declaration
