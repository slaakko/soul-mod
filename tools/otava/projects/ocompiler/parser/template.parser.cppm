
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/template.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.templates;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::templates {

template<typename LexerT>
struct TemplateParser
{
    static std::expected<soul::parser::Match, int> TemplateDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TemplateHead(LexerT& lexer, otava::symbols::Context* context, bool begin);
    static std::expected<soul::parser::Match, int> TemplateParameterList(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TemplateParameter(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeParameter(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeParameterKey(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Typename(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Class(LexerT& lexer);
    static std::expected<soul::parser::Match, int> TemplateId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SimpleTemplateId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TemplateName(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TemplateArgumentList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* templateIdNode);
    static std::expected<soul::parser::Match, int> TemplateArgument(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* templateIdNode, int index);
    static std::expected<soul::parser::Match, int> TemplateArgNext(LexerT& lexer);
    static std::expected<soul::parser::Match, int> DeductionGuide(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Arrow(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ExplicitInstantiation(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ExplicitSpecialization(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Extern(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Template(LexerT& lexer);
};

} // namespace otava::parser::templates
