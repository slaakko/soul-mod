
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/cpp_expected/identifier.parser' using soul parser generator espg version 5.0.0

export module soul_expected.cpp.identifier.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.cpp;

using namespace soul_expected::ast::cpp;

export namespace soul_expected::cpp::identifier::parser {

template<typename LexerT>
struct CppIdentifierParser
{
    static std::expected<soul_expected::parser::Match, int> CppIdentifier(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> QualifiedCppId(LexerT& lexer, soul_expected::ast::cpp::Context* context);
};

} // namespace soul_expected::cpp::identifier::parser
