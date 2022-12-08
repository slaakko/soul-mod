
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/class.parser' using soul parser generator spg version 4.1.0

export module otava.parser.classes;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

using namespace otava::symbols::context;
using namespace otava::ast;

export namespace otava::parser::classes {

template<typename Lexer>
struct ClassParser
{
    static soul::parser::Match ClassSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ClassHead(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ClassKey(Lexer& lexer);
    static soul::parser::Match ClassHeadName(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ClassName(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ClassVirtSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match VirtSpecifierSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match VirtSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match OverrideKeyword(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match FinalKeyword(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match BaseClause(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match BaseSpecifierList(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match BaseSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ClassOrDeclType(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberSpecification(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match MemberDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RBraceNext(Lexer& lexer);
    static soul::parser::Match MemberDeclSpecifiers(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RetMemberDeclSpecifiers(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberFunctionDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RetMemberFunctionDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberTemplateDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberDeclaratorList(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CtorInitializer(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CtorInitializerGuarded(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CtorInitializerUnguarded(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CtorInitializerSaved(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberInitializerList(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberInitializer(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MemberInitializerId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match PureSpecifier(Lexer& lexer);
    static soul::parser::Match AccessSpecifier(Lexer& lexer);
    static soul::parser::Match Private(Lexer& lexer);
    static soul::parser::Match VirtualSpecifier(Lexer& lexer);
};

} // namespace otava::parser::classes
