
// this file has been automatically generated from 'C:/work/soul-mod/soul/spg/spg_file_parser.parser' using soul parser generator spg version 4.0.0

module soul.spg.spg.file.parser;

import util;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.punctuation.token;
import soul.tool.token;
import soul.common.common.parser;
import soul.lex.spg;

using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::punctuation::token;
using namespace soul::tool::token;
using namespace soul::common::common::parser;
using namespace soul::lex::spg;

namespace soul::spg::spg::file::parser {

template<typename Lexer>
std::unique_ptr<soul::ast::spg::SpgFile> SpgFileParser<Lexer>::Parse(Lexer& lexer)
{
    std::unique_ptr<soul::ast::spg::SpgFile> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    ++lexer;
    soul::parser::Match match = SpgFileParser<Lexer>::SpgFile(lexer);
    value.reset(static_cast<soul::ast::spg::SpgFile*>(match.value));
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->DecIndent();
        lexer.Log()->WriteEndRule("parse");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (match.hit)
    {
        if (*lexer == soul::lexer::END_TOKEN)
        {
            return value;
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
    return value;
}

template<typename Lexer>
soul::parser::Match SpgFileParser<Lexer>::SpgFile(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SpgFile");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8393744626267193345);
    std::unique_ptr<soul::ast::spg::SpgFile> spgFile = std::unique_ptr<soul::ast::spg::SpgFile>();
    std::unique_ptr<soul::parser::Value<std::string>> projectName;
    std::unique_ptr<soul::ast::spg::SpgFileDeclaration> declaration;
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
                        if (*lexer == PROJECT)
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
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = CommonParser<Lexer>::QualifiedId(lexer);
                                    projectName.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                                    if (match.hit)
                                    {
                                        *parentMatch7 = match;
                                    }
                                    else
                                    {
                                        lexer.ThrowExpectationFailure(pos, "QualifiedId");
                                    }
                                }
                                if (match.hit)
                                {
                                    spgFile.reset(new soul::ast::spg::SpgFile(lexer.FileName(), projectName->value));
                                }
                                *parentMatch6 = match;
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
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch10 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch11 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch12 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch13 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = SpgFileParser<Lexer>::SpgFileDeclaration(lexer);
                                        declaration.reset(static_cast<soul::ast::spg::SpgFileDeclaration*>(match.value));
                                        if (match.hit)
                                        {
                                            spgFile->AddDeclaration(declaration.release());
                                        }
                                        *parentMatch13 = match;
                                    }
                                    *parentMatch12 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch11 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch10 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SpgFile");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, spgFile.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SpgFile");
        else soul::lexer::WriteFailureToLog(lexer, "SpgFile");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match SpgFileParser<Lexer>::SpgFileDeclaration(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SpgFileDeclaration");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8393744626267193346);
    std::unique_ptr<soul::ast::spg::ParserFileDeclaration> parserFileDeclaration;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = SpgFileParser<Lexer>::ParserFileDeclaration(lexer);
        parserFileDeclaration.reset(static_cast<soul::ast::spg::ParserFileDeclaration*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SpgFileDeclaration");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, parserFileDeclaration.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SpgFileDeclaration");
        else soul::lexer::WriteFailureToLog(lexer, "SpgFileDeclaration");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match SpgFileParser<Lexer>::ParserFileDeclaration(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParserFileDeclaration");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8393744626267193347);
    bool external = bool();
    std::unique_ptr<soul::parser::Value<std::string>> filePath;
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
                                    soul::parser::Match match(false);
                                    if (*lexer == EXTERN)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        external = true;
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
                                                external = false;
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
                            soul::parser::Match match = CommonParser<Lexer>::ParserKeyword(lexer);
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
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = CommonParser<Lexer>::FilePath(lexer);
                            filePath.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                *parentMatch12 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, "FilePath");
                            }
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParserFileDeclaration");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::ast::spg::ParserFileDeclaration(lexer.GetSourcePos(pos), filePath->value, external));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParserFileDeclaration");
        else soul::lexer::WriteFailureToLog(lexer, "ParserFileDeclaration");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct SpgFileParser<soul::lexer::Lexer<soul::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul::spg::spg::file::parser
