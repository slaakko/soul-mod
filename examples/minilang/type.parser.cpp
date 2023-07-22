
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/type.parser' using soul parser generator spg version 5.0.0

module minilang.parser.type;

import util;
import soul.ast.spg;
import minilang.ast;
import minilang.lexer;
import minilang.token;

using namespace minilang::ast;
using namespace minilang::lexer;
using namespace minilang::token;

namespace minilang::parser::type {

template<typename LexerT>
soul::parser::Match TypeParser<LexerT>::Type(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Type");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1020028859917008897);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case INT:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Type");
                    #endif
                    return soul::parser::Match(true, new minilang::ast::IntNode);
                }
            }
            break;
        }
        case BOOL:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Type");
                    #endif
                    return soul::parser::Match(true, new minilang::ast::BoolNode);
                }
            }
            break;
        }
        case VOID:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Type");
                    #endif
                    return soul::parser::Match(true, new minilang::ast::VoidNode);
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Type");
        else soul::lexer::WriteFailureToLog(lexer, "Type");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct TypeParser<soul::lexer::Lexer<minilang::lexer::MinilangLexer<char32_t>, char32_t>>;

} // namespace minilang::parser::type
