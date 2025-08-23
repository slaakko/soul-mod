
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ocpp/declarator.parser' using soul parser generator oespg version 5.0.0

export module soul.cpp.declarator.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::declarator::parser {

template<typename LexerT>
struct DeclaratorParser
{
    static std::expected<soul::parser::Match, int> InitDeclaratorList(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> InitDeclarator(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Declarator(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> DirectDeclarator(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> DeclaratorId(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> TypeId(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Type(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> TypeSpecifierSeq(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::TypeIdNode* typeId);
    static std::expected<soul::parser::Match, int> AbstractDeclarator(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> DirectAbstractDeclarator(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> PtrOperator(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> CVQualifierSeq(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Initializer(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> InitializerClause(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> InitializerList(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::AssignInitNode* init);
};

} // namespace soul::cpp::declarator::parser
