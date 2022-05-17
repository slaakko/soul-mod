
// this file has been automatically generated from 'C:/work/soul-mod/soul/slg/common_parser.parser' using soul parser generator spg version 4.0.0

export module soul.slg.common.par;

import std.core;
import util;
import soul.lexer;
import soul.parser;
import soul.cpp.token;
import soul.punctuation.token;
import soul.ast.spg;
import soul.slg.token.par;

using namespace soul::cpp::token;
using namespace soul::punctuation::token;
using namespace soul::ast::spg;
using namespace soul::slg::token::par;

export namespace soul::slg::common::par {

template<typename Lexer>
struct CommonParser
{
    static soul::parser::Match QualifiedId(Lexer& lexer);
    static soul::parser::Match Import(Lexer& lexer);
    static soul::parser::Match ExprString(Lexer& lexer);
};

template<typename Lexer>
soul::parser::Match CommonParser<Lexer>::QualifiedId(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, util::ToUtf32("QualifiedId"));
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    std::string str = std::string();
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
                    soul::parser::Match match(false);
                    if (*lexer == ID)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        str.append(util::ToUtf8(lexer.GetToken(pos).ToString()));
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
                                        if (*lexer == DOT)
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
                                                soul::parser::Match match(false);
                                                if (*lexer == ID)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    str.append(1, '.').append(util::ToUtf8(lexer.GetToken(pos).ToString()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, util::ToUtf32("QualifiedId"));
                #endif // SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, util::ToUtf32("QualifiedId"));
        else soul::lexer::WriteFailureToLog(lexer, util::ToUtf32("QualifiedId"));
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match CommonParser<Lexer>::Import(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, util::ToUtf32("Import"));
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    std::unique_ptr<soul::parser::Value<std::string>> moduleName;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = CommonParser<Lexer>::QualifiedId(lexer);
        moduleName.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, util::ToUtf32("Import"));
                #endif // SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::ast::spg::Import(moduleName->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, util::ToUtf32("Import"));
        else soul::lexer::WriteFailureToLog(lexer, util::ToUtf32("Import"));
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match CommonParser<Lexer>::ExprString(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, util::ToUtf32("ExprString"));
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(true);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == STRING_LITERAL)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(STRING_LITERAL));
            }
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, util::ToUtf32("ExprString"));
                #endif // SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::parser::Value<std::string>(MakeExprStringValue(lexer.FileName(), lexer.GetToken(pos))));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, util::ToUtf32("ExprString"));
        else soul::lexer::WriteFailureToLog(lexer, util::ToUtf32("ExprString"));
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

} // namespace soul::slg::common::par
