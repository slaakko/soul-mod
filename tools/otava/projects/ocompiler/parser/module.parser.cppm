
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/module.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.modules;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

export namespace otava::parser::modules {

template<typename LexerT>
struct ModuleParser
{
    static std::expected<soul::parser::Match, int> ModuleDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ModuleName(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ExportDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ImportDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ModulePartition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ExportKeyword(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ImportKeyword(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ModuleKeyword(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> GlobalModuleFragment(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> PrivateModuleFragment(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> HeaderName(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::modules
