
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/module_dependency.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.module_dependency;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::module_dependency {

template<typename LexerT>
struct ModuleDependencyParser
{
    static std::expected<std::unique_ptr<otava::ast::Node>, int> Parse(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ModuleUnit(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> GlobalModuleFragment(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DeclarationSeq(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Declaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ExportImportDeclaration(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::module_dependency
