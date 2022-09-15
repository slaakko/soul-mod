
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_pp/pp.parser' using soul parser generator spg version 4.1.0

module soul.cpp20.pp.parser;

import util;
import soul.ast.spg;
import soul.cpp20.token;
import soul.cpp20.pp.lexer;

using namespace soul::cpp20::token;
using namespace soul::cpp20::pp::lexer;

namespace soul::cpp20::pp::parser {

template<typename Lexer>
void PPParser<Lexer>::Parse(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    ++lexer;
    soul::parser::Match match = PPParser<Lexer>::PPLIne(lexer, state);
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
            return;
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
    return;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::PPLIne(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PPLIne");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000449);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == HASH)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match = PPParser<Lexer>::PPCommand(lexer, state);
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PPLIne");
        else soul::lexer::WriteFailureToLog(lexer, "PPLIne");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::PPCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PPCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000450);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case IF:
            {
                soul::parser::Match match = PPParser<Lexer>::IfCommand(lexer, state);
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case ELIF:
            {
                soul::parser::Match match = PPParser<Lexer>::ElifCommand(lexer, state);
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case IFDEF:
            {
                soul::parser::Match match = PPParser<Lexer>::IfdefCommand(lexer, state);
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case IFNDEF:
            {
                soul::parser::Match match = PPParser<Lexer>::IfndefCommand(lexer, state);
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case ELSE:
            {
                soul::parser::Match match = PPParser<Lexer>::ElseCommand(lexer, state);
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case ENDIF:
            {
                soul::parser::Match match = PPParser<Lexer>::EndifCommand(lexer, state);
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case DEFINE:
            {
                soul::parser::Match match = PPParser<Lexer>::DefineCommand(lexer, state);
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case UNDEF:
            {
                soul::parser::Match match = PPParser<Lexer>::UndefCommand(lexer, state);
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case INCLUDE:
            {
                soul::parser::Match match = PPParser<Lexer>::IncludeCommand(lexer, state);
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(true);
                soul::parser::Match* parentMatch3 = &match;
                {
                    while (true)
                    {
                        int64_t save = lexer.GetPos();
                        {
                            soul::parser::Match match(false);
                            if (*lexer != soul::lexer::END_TOKEN)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                *parentMatch3 = match;
                            }
                            else
                            {
                                lexer.SetPos(save);
                                break;
                            }
                        }
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PPCommand");
        else soul::lexer::WriteFailureToLog(lexer, "PPCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::IfCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IfCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000451);
    std::unique_ptr<soul::parser::Value<int64_t>> value;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == IF)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = PPParser<Lexer>::Expression(lexer, state);
                value.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                if (match.hit)
                {
                    state->If(value->value != 0);
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IfCommand");
        else soul::lexer::WriteFailureToLog(lexer, "IfCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::ElifCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ElifCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000452);
    std::unique_ptr<soul::parser::Value<int64_t>> value;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == ELIF)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = PPParser<Lexer>::Expression(lexer, state);
                value.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                if (match.hit)
                {
                    state->Elif(value->value != 0);
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElifCommand");
        else soul::lexer::WriteFailureToLog(lexer, "ElifCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::IfdefCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IfdefCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000453);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == IFDEF)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == ID)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    state->Ifdef(util::ToUtf8(lexer.GetToken(pos).ToString()));
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IfdefCommand");
        else soul::lexer::WriteFailureToLog(lexer, "IfdefCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::IfndefCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IfndefCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000454);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == IFNDEF)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == ID)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    state->Ifndef(util::ToUtf8(lexer.GetToken(pos).ToString()));
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IfndefCommand");
        else soul::lexer::WriteFailureToLog(lexer, "IfndefCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::ElseCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ElseCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000455);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == ELSE)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            state->Else();
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElseCommand");
        else soul::lexer::WriteFailureToLog(lexer, "ElseCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::EndifCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "EndifCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000456);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == ENDIF)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            state->Endif();
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EndifCommand");
        else soul::lexer::WriteFailureToLog(lexer, "EndifCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::DefineCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DefineCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000457);
    std::string symbol = std::string();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == DEFINE)
            {
                ++lexer;
                match.hit = true;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == ID)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        symbol = util::ToUtf8(lexer.GetToken(pos).ToString());
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch4 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                {
                    int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch7 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == INTEGER_LITERAL)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            int64_t value = std::stoll(util::ToUtf8(lexer.GetToken(pos).ToString()));
                            state->Define(symbol, value);
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch8 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match(true);
                                if (match.hit)
                                {
                                    state->Define(symbol, 1);
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch6 = match;
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefineCommand");
        else soul::lexer::WriteFailureToLog(lexer, "DefineCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::UndefCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UndefCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000458);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == UNDEF)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == ID)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    state->Undef(util::ToUtf8(lexer.GetToken(pos).ToString()));
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UndefCommand");
        else soul::lexer::WriteFailureToLog(lexer, "UndefCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::IncludeCommand(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IncludeCommand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000459);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == INCLUDE)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = PPParser<Lexer>::Header(lexer);
                if (match.hit)
                {
                    state->Include();
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IncludeCommand");
        else soul::lexer::WriteFailureToLog(lexer, "IncludeCommand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::Header(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Header");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000460);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case ANGLE_HEADER_NAME:
        {
            soul::parser::Match match(false);
            if (*lexer == ANGLE_HEADER_NAME)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case QUOTE_HEADER_NAME:
        {
            soul::parser::Match match(false);
            if (*lexer == QUOTE_HEADER_NAME)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Header");
        else soul::lexer::WriteFailureToLog(lexer, "Header");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::Expression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Expression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000461);
    std::unique_ptr<soul::parser::Value<int64_t>> expr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = PPParser<Lexer>::LogicalOrExpr(lexer, state);
        expr.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Expression");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(expr->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Expression");
        else soul::lexer::WriteFailureToLog(lexer, "Expression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::LogicalOrExpr(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LogicalOrExpr");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000462);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> right;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::LogicalAndExpr(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == OR_OR)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = PPParser<Lexer>::LogicalAndExpr(lexer, state);
                                                right.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                if (match.hit)
                                                {
                                                    value = static_cast<int64_t>(value != 0 || right->value != 0);
                                                }
                                                *parentMatch9 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LogicalOrExpr");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LogicalOrExpr");
        else soul::lexer::WriteFailureToLog(lexer, "LogicalOrExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::LogicalAndExpr(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LogicalAndExpr");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000463);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> right;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::InclusiveOrExpression(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == AMP_AMP)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = PPParser<Lexer>::InclusiveOrExpression(lexer, state);
                                                right.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                if (match.hit)
                                                {
                                                    value = static_cast<int64_t>(value != 0 && right->value != 0);
                                                }
                                                *parentMatch9 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LogicalAndExpr");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LogicalAndExpr");
        else soul::lexer::WriteFailureToLog(lexer, "LogicalAndExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::InclusiveOrExpression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "InclusiveOrExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000464);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> right;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::ExclusiveOrExpression(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == OR)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = PPParser<Lexer>::ExclusiveOrExpression(lexer, state);
                                                right.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                if (match.hit)
                                                {
                                                    value = value | right->value;
                                                }
                                                *parentMatch9 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InclusiveOrExpression");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InclusiveOrExpression");
        else soul::lexer::WriteFailureToLog(lexer, "InclusiveOrExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::ExclusiveOrExpression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ExclusiveOrExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000465);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> right;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::AndExpression(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == XOR)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = PPParser<Lexer>::AndExpression(lexer, state);
                                                right.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                if (match.hit)
                                                {
                                                    value = value ^ right->value;
                                                }
                                                *parentMatch9 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExclusiveOrExpression");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExclusiveOrExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ExclusiveOrExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::AndExpression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AndExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000466);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> right;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::EqualityExpression(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == AMP)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = PPParser<Lexer>::EqualityExpression(lexer, state);
                                                right.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                if (match.hit)
                                                {
                                                    value = value & right->value;
                                                }
                                                *parentMatch9 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AndExpression");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AndExpression");
        else soul::lexer::WriteFailureToLog(lexer, "AndExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::EqualityExpression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "EqualityExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000467);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> rightEq;
    std::unique_ptr<soul::parser::Value<int64_t>> rightNeq;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::RelationalExpression(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    switch (*lexer)
                                    {
                                        case EQ:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch8 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == EQ)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch9 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch10 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::RelationalExpression(lexer, state);
                                                        rightEq.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = static_cast<int64_t>(value == rightEq->value);
                                                        }
                                                        *parentMatch10 = match;
                                                    }
                                                    *parentMatch9 = match;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case NEQ:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch11 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == NEQ)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch12 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch13 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::RelationalExpression(lexer, state);
                                                        rightNeq.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = static_cast<int64_t>(value != rightNeq->value);
                                                        }
                                                        *parentMatch13 = match;
                                                    }
                                                    *parentMatch12 = match;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityExpression");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityExpression");
        else soul::lexer::WriteFailureToLog(lexer, "EqualityExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::RelationalExpression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RelationalExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000468);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> rightLess;
    std::unique_ptr<soul::parser::Value<int64_t>> rightGreater;
    std::unique_ptr<soul::parser::Value<int64_t>> rightLessEq;
    std::unique_ptr<soul::parser::Value<int64_t>> rightGreaterEq;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::ShiftExpression(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    switch (*lexer)
                                    {
                                        case LANGLE:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch8 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == LANGLE)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch9 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch10 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::ShiftExpression(lexer, state);
                                                        rightLess.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = static_cast<int64_t>(value < rightLess->value);
                                                        }
                                                        *parentMatch10 = match;
                                                    }
                                                    *parentMatch9 = match;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case RANGLE:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch11 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == RANGLE)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch12 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch13 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::ShiftExpression(lexer, state);
                                                        rightGreater.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = static_cast<int64_t>(value > rightGreater->value);
                                                        }
                                                        *parentMatch13 = match;
                                                    }
                                                    *parentMatch12 = match;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case LEQ:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch14 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == LEQ)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch14 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch15 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch16 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::ShiftExpression(lexer, state);
                                                        rightLessEq.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = static_cast<int64_t>(value <= rightLessEq->value);
                                                        }
                                                        *parentMatch16 = match;
                                                    }
                                                    *parentMatch15 = match;
                                                }
                                                *parentMatch14 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case GEQ:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch17 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == GEQ)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch17 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch18 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch19 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::ShiftExpression(lexer, state);
                                                        rightGreaterEq.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = static_cast<int64_t>(value >= rightGreaterEq->value);
                                                        }
                                                        *parentMatch19 = match;
                                                    }
                                                    *parentMatch18 = match;
                                                }
                                                *parentMatch17 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalExpression");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalExpression");
        else soul::lexer::WriteFailureToLog(lexer, "RelationalExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::ShiftExpression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ShiftExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000469);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> rightLShift;
    std::unique_ptr<soul::parser::Value<int64_t>> rightRShift;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::AdditiveExpression(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    switch (*lexer)
                                    {
                                        case SHIFT_LEFT:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch8 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == SHIFT_LEFT)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch9 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch10 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::AdditiveExpression(lexer, state);
                                                        rightLShift.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = value << rightLShift->value;
                                                        }
                                                        *parentMatch10 = match;
                                                    }
                                                    *parentMatch9 = match;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case SHIFT_RIGHT:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch11 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == SHIFT_RIGHT)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch12 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch13 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::AdditiveExpression(lexer, state);
                                                        rightRShift.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = value >> rightRShift->value;
                                                        }
                                                        *parentMatch13 = match;
                                                    }
                                                    *parentMatch12 = match;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftExpression");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ShiftExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::AdditiveExpression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AdditiveExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000470);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> rightPlus;
    std::unique_ptr<soul::parser::Value<int64_t>> rightMinus;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::MultiplicativeExpression(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    switch (*lexer)
                                    {
                                        case PLUS:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch8 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == PLUS)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch9 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch10 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::MultiplicativeExpression(lexer, state);
                                                        rightPlus.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = value + rightPlus->value;
                                                        }
                                                        *parentMatch10 = match;
                                                    }
                                                    *parentMatch9 = match;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case MINUS:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch11 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == MINUS)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch12 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch13 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::MultiplicativeExpression(lexer, state);
                                                        rightMinus.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = value - rightMinus->value;
                                                        }
                                                        *parentMatch13 = match;
                                                    }
                                                    *parentMatch12 = match;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveExpression");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveExpression");
        else soul::lexer::WriteFailureToLog(lexer, "AdditiveExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::MultiplicativeExpression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MultiplicativeExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000471);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> left;
    std::unique_ptr<soul::parser::Value<int64_t>> rightMul;
    std::unique_ptr<soul::parser::Value<int64_t>> rightDiv;
    std::unique_ptr<soul::parser::Value<int64_t>> rightMod;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::UnaryExpression(lexer, state);
                    left.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        value = left->value;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    switch (*lexer)
                                    {
                                        case STAR:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch8 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == STAR)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch9 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch10 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::UnaryExpression(lexer, state);
                                                        rightMul.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = value * rightMul->value;
                                                        }
                                                        *parentMatch10 = match;
                                                    }
                                                    *parentMatch9 = match;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case DIV:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch11 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == DIV)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch12 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch13 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::UnaryExpression(lexer, state);
                                                        rightDiv.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = value / rightDiv->value;
                                                        }
                                                        *parentMatch13 = match;
                                                    }
                                                    *parentMatch12 = match;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case MOD:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch14 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == MOD)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch14 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch15 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch16 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PPParser<Lexer>::UnaryExpression(lexer, state);
                                                        rightMod.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            value = value / rightMod->value;
                                                        }
                                                        *parentMatch16 = match;
                                                    }
                                                    *parentMatch15 = match;
                                                }
                                                *parentMatch14 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeExpression");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeExpression");
        else soul::lexer::WriteFailureToLog(lexer, "MultiplicativeExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::UnaryExpression(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UnaryExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000472);
    int64_t value = int64_t();
    std::unique_ptr<soul::parser::Value<int64_t>> plusExpr;
    std::unique_ptr<soul::parser::Value<int64_t>> minusExpr;
    std::unique_ptr<soul::parser::Value<int64_t>> notExpr;
    std::unique_ptr<soul::parser::Value<int64_t>> complementExpr;
    std::unique_ptr<soul::parser::Value<int64_t>> primaryExpr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case PLUS:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch2 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == PLUS)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    *parentMatch2 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch3 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch4 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = PPParser<Lexer>::UnaryExpression(lexer, state);
                            plusExpr.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpression");
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<int64_t>(plusExpr->value));
                                }
                            }
                            *parentMatch4 = match;
                        }
                        *parentMatch3 = match;
                    }
                    *parentMatch2 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case MINUS:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch5 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == MINUS)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    *parentMatch5 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch6 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch7 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = PPParser<Lexer>::UnaryExpression(lexer, state);
                            minusExpr.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpression");
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<int64_t>(-minusExpr->value));
                                }
                            }
                            *parentMatch7 = match;
                        }
                        *parentMatch6 = match;
                    }
                    *parentMatch5 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case EXCLAMATION:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch8 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == EXCLAMATION)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    *parentMatch8 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch9 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch10 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = PPParser<Lexer>::UnaryExpression(lexer, state);
                            notExpr.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpression");
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<int64_t>(static_cast<int64_t>(!(notExpr->value != 0))));
                                }
                            }
                            *parentMatch10 = match;
                        }
                        *parentMatch9 = match;
                    }
                    *parentMatch8 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case TILDE:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch11 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == TILDE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    *parentMatch11 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch12 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch13 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = PPParser<Lexer>::UnaryExpression(lexer, state);
                            complementExpr.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpression");
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<int64_t>(~complementExpr->value));
                                }
                            }
                            *parentMatch13 = match;
                        }
                        *parentMatch12 = match;
                    }
                    *parentMatch11 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case DEFINED:
            case ID:
            case INTEGER_LITERAL:
            case LPAREN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch14 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = PPParser<Lexer>::PrimaryExpr(lexer, state);
                    primaryExpr.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpression");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<int64_t>(primaryExpr->value));
                        }
                    }
                    *parentMatch14 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpression");
        else soul::lexer::WriteFailureToLog(lexer, "UnaryExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::PrimaryExpr(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PrimaryExpr");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000473);
    std::unique_ptr<soul::parser::Value<int64_t>> defined;
    std::unique_ptr<soul::parser::Value<int64_t>> value;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case DEFINED:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = PPParser<Lexer>::DefinedExpr(lexer, state);
                defined.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int64_t>(defined->value));
                    }
                }
                *parentMatch1 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case LPAREN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == LPAREN)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match = PPParser<Lexer>::Expression(lexer, state);
                        value.reset(static_cast<soul::parser::Value<int64_t>*>(match.value));
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch5 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch6 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == RPAREN)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
                                #endif
                                return soul::parser::Match(true, new soul::parser::Value<int64_t>(value->value));
                            }
                        }
                        *parentMatch6 = match;
                    }
                    *parentMatch5 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case INTEGER_LITERAL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == INTEGER_LITERAL)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int64_t>(std::stoll(util::ToUtf8(lexer.GetToken(pos).ToString()))));
                    }
                }
                *parentMatch7 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case ID:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == ID)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int64_t>(state->GetSymbolValue(util::ToUtf8(lexer.GetToken(pos).ToString()))));
                    }
                }
                *parentMatch8 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
        else soul::lexer::WriteFailureToLog(lexer, "PrimaryExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match PPParser<Lexer>::DefinedExpr(Lexer& lexer, soul::cpp20::pp::state::State* state)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DefinedExpr");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 8694736574321000474);
    std::string symbol = std::string();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == DEFINED)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                switch (*lexer)
                {
                    case LPAREN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch4 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch5 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == LPAREN)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch5 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == ID)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            symbol = util::ToUtf8(lexer.GetToken(pos).ToString());
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                *parentMatch5 = match;
                            }
                            *parentMatch4 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch8 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch9 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == RPAREN)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        if (state->Defined(symbol))
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefinedExpr");
                                                #endif
                                                return soul::parser::Match(true, new soul::parser::Value<int64_t>(1));
                                            }
                                        }
                                        else
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefinedExpr");
                                                #endif
                                                return soul::parser::Match(true, new soul::parser::Value<int64_t>(0));
                                            }
                                        }
                                    }
                                    *parentMatch9 = match;
                                }
                                *parentMatch8 = match;
                            }
                            *parentMatch4 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case ID:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch10 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == ID)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                symbol = util::ToUtf8(lexer.GetToken(pos).ToString());
                                if (state->Defined(symbol))
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefinedExpr");
                                        #endif
                                        return soul::parser::Match(true, new soul::parser::Value<int64_t>(1));
                                    }
                                }
                                else
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefinedExpr");
                                        #endif
                                        return soul::parser::Match(true, new soul::parser::Value<int64_t>(0));
                                    }
                                }
                            }
                            *parentMatch10 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefinedExpr");
        else soul::lexer::WriteFailureToLog(lexer, "DefinedExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct PPParser<soul::lexer::Lexer<soul::cpp20::pp::lexer::Cpp20PPLexer<char32_t>, char32_t>>;

} // namespace soul::cpp20::pp::parser
