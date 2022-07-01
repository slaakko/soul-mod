
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/statement.parser' using soul parser generator spg version 4.0.0

module soul.cpp20.parser.statement;

import util;
import soul.ast.spg;
import soul.cpp20.ast;
import soul.cpp20.token;
import soul.cpp20.lexer;

using namespace soul::cpp20::ast;
using namespace soul::cpp20::token;
using namespace soul::cpp20::lexer;

namespace soul::cpp20::parser::statement {

template<typename Lexer>
soul::parser::Match StatementParser<Lexer>::CompoundStatement(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CompoundStatement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4943488507084537857);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        bool pass = true;
        soul::parser::Match match(true);
        if (match.hit)
        {
            pass = false;
        }
        if (match.hit && !pass)
        {
            match = soul::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatement");
        else soul::lexer::WriteFailureToLog(lexer, "CompoundStatement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match StatementParser<Lexer>::HandlerSeq(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "HandlerSeq");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4943488507084537858);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        bool pass = true;
        soul::parser::Match match(true);
        if (match.hit)
        {
            pass = false;
        }
        if (match.hit && !pass)
        {
            match = soul::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "HandlerSeq");
        else soul::lexer::WriteFailureToLog(lexer, "HandlerSeq");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct StatementParser<soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>>;

} // namespace soul::cpp20::parser::statement
