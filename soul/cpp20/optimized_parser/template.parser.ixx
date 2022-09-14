
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_parser/template.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.templates;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::templates {

template<typename Lexer>
struct TemplateParser
{
    static soul::parser::Match TemplateDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TemplateHead(Lexer& lexer, soul::cpp20::symbols::Context* context, bool begin);
    static soul::parser::Match TemplateParameterList(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TemplateParameter(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeParameter(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeParameterKey(Lexer& lexer);
    static soul::parser::Match Typename(Lexer& lexer);
    static soul::parser::Match Class(Lexer& lexer);
    static soul::parser::Match TemplateId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match SimpleTemplateId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TemplateName(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TemplateArgumentList(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* templateIdNode);
    static soul::parser::Match TemplateArgument(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* templateIdNode, int index);
    static soul::parser::Match TemplateArgNext(Lexer& lexer);
    static soul::parser::Match DeductionGuide(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Arrow(Lexer& lexer);
    static soul::parser::Match ExplicitInstantiation(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExplicitSpecialization(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Extern(Lexer& lexer);
    static soul::parser::Match Template(Lexer& lexer);
};

} // namespace soul::cpp20::parser::templates
