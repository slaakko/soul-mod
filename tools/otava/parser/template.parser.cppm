
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/template.parser' using soul parser generator spg version 4.1.0

export module otava.parser.templates;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::templates {

template<typename Lexer>
struct TemplateParser
{
    static soul::parser::Match TemplateDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TemplateHead(Lexer& lexer, otava::symbols::Context* context, bool begin);
    static soul::parser::Match TemplateParameterList(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TemplateParameter(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeParameter(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeParameterKey(Lexer& lexer);
    static soul::parser::Match Typename(Lexer& lexer);
    static soul::parser::Match Class(Lexer& lexer);
    static soul::parser::Match TemplateId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match SimpleTemplateId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TemplateName(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TemplateArgumentList(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* templateIdNode);
    static soul::parser::Match TemplateArgument(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* templateIdNode, int index);
    static soul::parser::Match TemplateArgNext(Lexer& lexer);
    static soul::parser::Match DeductionGuide(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Arrow(Lexer& lexer);
    static soul::parser::Match ExplicitInstantiation(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ExplicitSpecialization(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Extern(Lexer& lexer);
    static soul::parser::Match Template(Lexer& lexer);
};

} // namespace otava::parser::templates
