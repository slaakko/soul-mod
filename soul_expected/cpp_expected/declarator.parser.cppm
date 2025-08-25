
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/cpp_expected/declarator.parser' using soul parser generator espg version 5.0.0

export module soul_expected.cpp.declarator.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.cpp;

export namespace soul_expected::cpp::declarator::parser {

template<typename LexerT>
struct DeclaratorParser
{
    static std::expected<soul_expected::parser::Match, int> InitDeclaratorList(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> InitDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Declarator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> DirectDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> DeclaratorId(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> TypeId(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Type(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> TypeSpecifierSeq(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::TypeIdNode* typeId);
    static std::expected<soul_expected::parser::Match, int> AbstractDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> DirectAbstractDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> PtrOperator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> CVQualifierSeq(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Initializer(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> InitializerClause(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> InitializerList(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::AssignInitNode* init);
};

} // namespace soul_expected::cpp::declarator::parser
