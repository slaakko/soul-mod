
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/translation_unit.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.translation.unit;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::translation::unit {

template<typename LexerT>
struct TranslationUnitParser
{
    static std::expected<std::unique_ptr<otava::ast::Node>, int> Parse(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TranslationUnit(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ModuleUnit(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::translation::unit
