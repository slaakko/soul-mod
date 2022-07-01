
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/template.parser' using soul parser generator spg version 4.0.0

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
    static soul::parser::Match TemplateId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match SimpleTemplateId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DeductionGuide(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExplicitInstantiation(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExplicitSpecialization(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Extern(Lexer& lexer);
    static soul::parser::Match Template(Lexer& lexer);
    static soul::parser::Match Typename(Lexer& lexer);
};

} // namespace soul::cpp20::parser::templates
