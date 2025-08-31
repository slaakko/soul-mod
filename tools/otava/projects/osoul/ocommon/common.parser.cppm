
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ocommon/common.parser' using soul parser generator ospg version 5.0.0

export module soul.common.common.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.common;

export namespace soul::common::common::parser {

template<typename LexerT>
struct CommonParser
{
    static std::expected<soul::parser::Match, int> QualifiedId(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ExportModule(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Import(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ImportPrefix(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ExprString(LexerT& lexer);
    static std::expected<soul::parser::Match, int> FilePath(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ExportKeyword(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ModuleKeyword(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ImportKeyword(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ImplementationPrefix(LexerT& lexer);
    static std::expected<soul::parser::Match, int> InterfacePrefix(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ImplementationKeyword(LexerT& lexer);
    static std::expected<soul::parser::Match, int> InterfaceKeyword(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ParserKeyword(LexerT& lexer);
    static std::expected<soul::parser::Match, int> LexerKeyword(LexerT& lexer);
};

} // namespace soul::common::common::parser
