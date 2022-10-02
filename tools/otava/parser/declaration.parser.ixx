
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/declaration.parser' using soul parser generator spg version 4.1.0

export module otava.parser.declaration;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

using namespace otava::symbols::context;
using namespace otava::ast;

export namespace otava::parser::declaration {

template<typename Lexer>
struct DeclarationParser
{
    static soul::parser::Match DeclarationSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NamespaceDeclarationSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RBraceNext(Lexer& lexer);
    static soul::parser::Match Declaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match BlockDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoDeclSpecFunctionDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match EmptyDeclaration(Lexer& lexer);
    static soul::parser::Match SimpleDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AsmDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Asm(Lexer& lexer);
    static soul::parser::Match LinkageSpecification(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NamespaceDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NamedNamespaceDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UnnamedNamespaceDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NestedNamespaceDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NamespaceAliasDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match QualifiedNamespaceSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NamespaceBody(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NestedNamespaceSpecifier(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match Namespace(Lexer& lexer);
    static soul::parser::Match NamespaceName(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UsingDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Using(Lexer& lexer);
    static soul::parser::Match UsingDeclaratorList(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UsingDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UsingEnumDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UsingDirective(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match StaticAssertDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match StaticAssert(Lexer& lexer);
    static soul::parser::Match AliasDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DeclSpecifierSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Inline(Lexer& lexer);
    static soul::parser::Match DeclSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match StorageClassSpecifier(Lexer& lexer);
    static soul::parser::Match FunctionSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ExplicitSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match InitDeclaratorList(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match InitDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DeclaratorPushClassScope(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Declarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match PtrDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoPtrDeclarator(Lexer& lexer, otava::symbols::Context* context, bool trailingDecl);
    static soul::parser::Match ParametersAndQualifiers(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TrailingReturnType(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match PtrOperator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AbstractDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoPtrAbstractDeclarator(Lexer& lexer, otava::symbols::Context* context, bool trailingDecl);
    static soul::parser::Match PtrAbstractDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AbstractPackDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoPtrAbstractPackDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DeclaratorId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Ptr(Lexer& lexer);
    static soul::parser::Match LvalueRef(Lexer& lexer);
    static soul::parser::Match RvalueRef(Lexer& lexer);
    static soul::parser::Match RefQualifier(Lexer& lexer);
    static soul::parser::Match CVQualifierSeq(Lexer& lexer);
    static soul::parser::Match CVQualifier(Lexer& lexer);
    static soul::parser::Match NoexceptSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ThrowSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeDeclaration(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::declaration
