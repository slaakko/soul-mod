
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/translation_unit.parser' using soul parser generator spg version 5.0.0

export module otava.parser.translation.unit;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

using namespace otava::symbols::context;
using namespace otava::ast;

export namespace otava::parser::translation::unit {

template<typename LexerT>
struct TranslationUnitParser
{
    static std::unique_ptr<otava::ast::Node> Parse(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match TranslationUnit(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match ModuleUnit(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::translation::unit
