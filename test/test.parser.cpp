
// this file has been automatically generated from 'C:/work/soul-mod/test/test.parser' using soul parser generator spg version 5.0.0

module test.parser;

import util;
import soul.ast.spg;
import test.token;
import test.lexer;

using namespace test::token;
using namespace test::lexer;

namespace test::parser {

template<typename LexerT>
int TestParser<LexerT>::Parse(LexerT& lexer)
{
    std::unique_ptr<soul::parser::Value<int>> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    ++lexer;
    soul::parser::Match match = TestParser<LexerT>::ClassKey(lexer);
    value.reset(static_cast<soul::parser::Value<int>*>(match.value));
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->DecIndent();
        lexer.Log()->WriteEndRule("parse");
    }
    #endif
    if (match.hit)
    {
        if (*lexer == soul::lexer::END_TOKEN)
        {
            return value->value;
        }
        else
        {
            lexer.ThrowFarthestError();
        }
    }
    else
    {
        lexer.ThrowFarthestError();
    }
    return value->value;
}

template<typename LexerT>
soul::parser::Match TestParser<LexerT>::ClassKey(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ClassKey");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 5305326204553789441);
    soul::parser::Match match(false);
    std::int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case CLASS:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
                    #endif
                    return soul::parser::Match(true, new soul::parser::Value<int>(1));
                }
            }
            break;
        }
        case STRUCT:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
                    #endif
                    return soul::parser::Match(true, new soul::parser::Value<int>(2));
                }
            }
            break;
        }
        case UNION:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
                    #endif
                    return soul::parser::Match(true, new soul::parser::Value<int>(3));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
        else soul::lexer::WriteFailureToLog(lexer, "ClassKey");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct TestParser<soul::lexer::Lexer<test::lexer::TestLexer<char32_t>, char32_t>>;

} // namespace test::parser
