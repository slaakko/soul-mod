
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ocpp/identifier.parser' using soul parser generator oespg version 5.0.0

export module soul.cpp.identifier.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::identifier::parser {

template<typename LexerT>
struct CppIdentifierParser
{
    static std::expected<soul::parser::Match, int> CppIdentifier(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> QualifiedCppId(LexerT& lexer, soul::ast::cpp::Context* context);
};

} // namespace soul::cpp::identifier::parser
