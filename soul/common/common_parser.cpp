
// this file has been automatically generated from 'C:/work/soul-mod/soul/common/common_parser.parser' using soul parser generator spg version 4.0.0

module soul.common.common.par;

import util;
import soul.cpp.token;
import soul.punctuation.token;
import soul.tool.token;
import soul.lex.slg;
import soul.lex.spg;
import soul.common.token.par;

using namespace soul::cpp::token;
using namespace soul::punctuation::token;
using namespace soul::tool::token;
using namespace soul::lex::slg;
using namespace soul::lex::spg;
using namespace soul::common::token::par;

namespace soul::common::common::par {

template<typename Lexer>
soul::parser::Match CommonParser<Lexer>::QualifiedId(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "QualifiedId");
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "QualifiedId");
                #endif // SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "QualifiedId");
        else soul::lexer::WriteFailureToLog(lexer, "QualifiedId");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match CommonParser<Lexer>::ExportModule(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ExportModule");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    std::unique_ptr<soul::ast::common::ExportModule> exp = std::unique_ptr<soul::ast::common::ExportModule>();
    std::unique_ptr<soul::parser::Value<std::string>> moduleName;
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        if (*lexer == EXPORT)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == MODULE)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
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
                            soul::parser::Match match = CommonParser<Lexer>::QualifiedId(lexer);
                            moduleName.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                exp.reset(new soul::ast::common::ExportModule(moduleName->value));
                            }
                            *parentMatch7 = match;
                        }
                        *parentMatch6 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch8 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch9 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == SEMICOLON)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            *parentMatch9 = match;
                        }
                        else
                        {
                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(SEMICOLON));
                        }
                    }
                    *parentMatch8 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExportModule");
                #endif // SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, exp.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExportModule");
        else soul::lexer::WriteFailureToLog(lexer, "ExportModule");
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
        soul::lexer::WriteBeginRuleToLog(lexer, "Import");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    std::unique_ptr<soul::ast::common::Import> imp = std::unique_ptr<soul::ast::common::Import>();
    soul::ast::common::ImportPrefix prefix = soul::ast::common::ImportPrefix();
    std::unique_ptr<soul::parser::Value<soul::ast::common::ImportPrefix>> importPrefix;
    std::unique_ptr<soul::parser::Value<std::string>> moduleName;
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
                                    soul::parser::Match match = CommonParser<Lexer>::ImportPrefix(lexer);
                                    importPrefix.reset(static_cast<soul::parser::Value<soul::ast::common::ImportPrefix>*>(match.value));
                                    if (match.hit)
                                    {
                                        prefix = importPrefix->value;
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
                                                prefix = soul::ast::common::ImportPrefix::interfacePrefix;
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
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch10 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == IMPORT)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            *parentMatch10 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch11 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = CommonParser<Lexer>::QualifiedId(lexer);
                            moduleName.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                imp.reset(new soul::ast::common::Import(moduleName->value, prefix));
                            }
                            *parentMatch12 = match;
                        }
                        *parentMatch11 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch13 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch14 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == SEMICOLON)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            *parentMatch14 = match;
                        }
                        else
                        {
                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(SEMICOLON));
                        }
                    }
                    *parentMatch13 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Import");
                #endif // SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, imp.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Import");
        else soul::lexer::WriteFailureToLog(lexer, "Import");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match CommonParser<Lexer>::ImportPrefix(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ImportPrefix");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    soul::lexer::SourcePos sourcePos = lexer.GetSourcePos(pos);
    switch (*lexer)
    {
        case IMPLEMENTATION_PREFIX:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ImportPrefix");
                    #endif // SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::common::ImportPrefix>(soul::ast::common::ImportPrefix::implementationPrefix));
                }
            }
            break;
        }
        case INTERFACE_PREFIX:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ImportPrefix");
                    #endif // SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::common::ImportPrefix>(soul::ast::common::ImportPrefix::interfacePrefix));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ImportPrefix");
        else soul::lexer::WriteFailureToLog(lexer, "ImportPrefix");
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
        soul::lexer::WriteBeginRuleToLog(lexer, "ExprString");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
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
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExprString");
                #endif // SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::parser::Value<std::string>(MakeExprStringValue(lexer.FileName(), lexer.GetToken(pos))));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExprString");
        else soul::lexer::WriteFailureToLog(lexer, "ExprString");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match CommonParser<Lexer>::FilePath(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FilePath");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == FILEPATH)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FilePath");
                #endif // SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::parser::Value<std::string>(MakeFilePath(lexer.FileName(), lexer.GetToken(pos))));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FilePath");
        else soul::lexer::WriteFailureToLog(lexer, "FilePath");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct CommonParser<soul::lexer::Lexer<soul::lex::slg::SlgLexer<char32_t>, char32_t>>;
template struct CommonParser<soul::lexer::Lexer<soul::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul::common::common::par
