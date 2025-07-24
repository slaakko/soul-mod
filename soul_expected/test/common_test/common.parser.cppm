
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/test/common_test/common.parser' using soul parser generator espg version 5.0.0

export module soul_expected.common.common.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.common;

using namespace soul_expected::ast::common;

export namespace soul_expected::common::common::parser {

template<typename LexerT>
struct CommonParser
{
    static std::expected<soul_expected::parser::Match, int> QualifiedId(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ExportModule(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Import(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ImportPrefix(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ExprString(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> FilePath(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ExportKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ModuleKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ImportKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ImplementationPrefix(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> InterfacePrefix(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ImplementationKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> InterfaceKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ParserKeyword(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> LexerKeyword(LexerT& lexer);
};

} // namespace soul_expected::common::common::parser
