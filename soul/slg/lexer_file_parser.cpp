
// this file has been automatically generated from 'C:/work/soul-mod/soul/slg/lexer_file_parser.parser' using soul parser generator spg version 4.0.0

module soul.slg.lexer.file.parser;

import util;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.punctuation.token;
import soul.tool.token;
import soul.common.common.parser;
import soul.slg.token.parser;
import soul.cpp.statement.parser;
import soul.cpp.declarator.parser;
import soul.ast.cpp;
import soul.lex.slg;

using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::punctuation::token;
using namespace soul::tool::token;
using namespace soul::common::common::parser;
using namespace soul::slg::token::parser;
using namespace soul::cpp::statement::parser;
using namespace soul::cpp::declarator::parser;
using namespace soul::ast::cpp;
using namespace soul::lex::slg;

namespace soul::slg::lexer::file::parser {

template<typename Lexer>
std::unique_ptr<soul::ast::slg::LexerFile> LexerFileParser<Lexer>::Parse(Lexer& lexer)
{
    std::unique_ptr<soul::ast::slg::LexerFile> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    ++lexer;
    soul::parser::Match match = LexerFileParser<Lexer>::LexerFile(lexer);
    value.reset(static_cast<soul::ast::slg::LexerFile*>(match.value));
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
soul::parser::Match LexerFileParser<Lexer>::LexerFile(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LexerFile");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8883513078608560129);
    std::unique_ptr<soul::ast::slg::LexerFile> lexerFile = std::unique_ptr<soul::ast::slg::LexerFile>();
    std::unique_ptr<soul::ast::slg::Lexer> lxr = std::unique_ptr<soul::ast::slg::Lexer>();
    std::unique_ptr<soul::ast::common::ExportModule> exportModule;
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch9 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(true);
                                            if (match.hit)
                                            {
                                                lexerFile.reset(new soul::ast::slg::LexerFile(lexer.FileName()));
                                            }
                                            *parentMatch9 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch11 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = CommonParser<Lexer>::ExportModule(lexer);
                                                exportModule.reset(static_cast<soul::ast::common::ExportModule*>(match.value));
                                                if (match.hit)
                                                {
                                                    lexerFile->SetExportModule(exportModule.release());
                                                }
                                                *parentMatch11 = match;
                                            }
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch12 = &match;
                                    {
                                        soul::parser::Match match = LexerFileParser<Lexer>::Imports(lexer, lexerFile.get());
                                        *parentMatch12 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch13 = &match;
                                {
                                    soul::parser::Match match = CommonParser<Lexer>::LexerKeyword(lexer);
                                    *parentMatch13 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch14 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch15 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch16 = &match;
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
                                            *parentMatch16 = match;
                                        }
                                        else
                                        {
                                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(ID));
                                        }
                                    }
                                    if (match.hit)
                                    {
                                        lxr.reset(new soul::ast::slg::Lexer(util::ToUtf8(lexer.GetToken(pos).ToString())));
                                    }
                                    *parentMatch15 = match;
                                }
                                *parentMatch14 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch17 = &match;
                        {
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch18 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == LBRACE)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    *parentMatch18 = match;
                                }
                                else
                                {
                                    lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LBRACE));
                                }
                            }
                            *parentMatch17 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch19 = &match;
                    {
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch20 = &match;
                        {
                            while (true)
                            {
                                int64_t save = lexer.GetPos();
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch21 = &match;
                                    {
                                        soul::parser::Match match = LexerFileParser<Lexer>::LexerContent(lexer, lxr.get());
                                        *parentMatch21 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch20 = match;
                                    }
                                    else
                                    {
                                        lexer.SetPos(save);
                                        break;
                                    }
                                }
                            }
                        }
                        *parentMatch19 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch22 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch23 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == RBRACE)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            *parentMatch23 = match;
                        }
                        else
                        {
                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RBRACE));
                        }
                    }
                    *parentMatch22 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            lexerFile->SetLexer(lxr.release());
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LexerFile");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, lexerFile.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LexerFile");
        else soul::lexer::WriteFailureToLog(lexer, "LexerFile");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match LexerFileParser<Lexer>::Imports(Lexer& lexer, soul::ast::slg::LexerFile* lexerFile)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Imports");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8883513078608560130);
    std::unique_ptr<soul::ast::common::Import> imp;
    soul::parser::Match match(true);
    soul::parser::Match* parentMatch0 = &match;
    {
        while (true)
        {
            int64_t save = lexer.GetPos();
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch1 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch2 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = CommonParser<Lexer>::Import(lexer);
                        imp.reset(static_cast<soul::ast::common::Import*>(match.value));
                        if (match.hit)
                        {
                            lexerFile->AddImport(imp.release());
                        }
                        *parentMatch2 = match;
                    }
                    *parentMatch1 = match;
                }
                if (match.hit)
                {
                    *parentMatch0 = match;
                }
                else
                {
                    lexer.SetPos(save);
                    break;
                }
            }
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Imports");
        else soul::lexer::WriteFailureToLog(lexer, "Imports");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match LexerFileParser<Lexer>::LexerContent(Lexer& lexer, soul::ast::slg::Lexer* lxr)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LexerContent");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8883513078608560131);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t save = lexer.GetPos();
                soul::parser::Match match = LexerFileParser<Lexer>::Rules(lexer, lxr);
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch3 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match = LexerFileParser<Lexer>::Variables(lexer, lxr);
                        *parentMatch3 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match = LexerFileParser<Lexer>::Actions(lexer, lxr);
                    *parentMatch4 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LexerContent");
        else soul::lexer::WriteFailureToLog(lexer, "LexerContent");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match LexerFileParser<Lexer>::Rules(Lexer& lexer, soul::ast::slg::Lexer* lxr)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Rules");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8883513078608560132);
    std::unique_ptr<soul::ast::slg::Rule> rl;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
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
                    if (*lexer == RULES)
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
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == LBRACE)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                *parentMatch5 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LBRACE));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch7 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = LexerFileParser<Lexer>::Rule(lexer);
                                        rl.reset(static_cast<soul::ast::slg::Rule*>(match.value));
                                        if (match.hit)
                                        {
                                            lxr->AddRule(rl.release());
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch7 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch6 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch10 = &match;
            {
                soul::parser::Match match(true);
                soul::parser::Match* parentMatch11 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == RBRACE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        *parentMatch11 = match;
                    }
                    else
                    {
                        lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RBRACE));
                    }
                }
                *parentMatch10 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Rules");
        else soul::lexer::WriteFailureToLog(lexer, "Rules");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match LexerFileParser<Lexer>::Rule(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Rule");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8883513078608560133);
    int line = int();
    std::unique_ptr<soul::parser::Value<std::string>> expr;
    std::unique_ptr<soul::parser::Value<int>> action;
    std::unique_ptr<soul::ast::cpp::CompoundStatementNode> code;
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = CommonParser<Lexer>::ExprString(lexer);
                        expr.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            line = lexer.GetToken(pos).line;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        soul::parser::Match match = LexerFileParser<Lexer>::Action(lexer);
                        action.reset(static_cast<soul::parser::Value<int>*>(match.value));
                        *parentMatch5 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                {
                    soul::parser::Match match = StatementParser<Lexer>::CompoundStatement(lexer);
                    code.reset(static_cast<soul::ast::cpp::CompoundStatementNode*>(match.value));
                    *parentMatch6 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Rule");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::ast::slg::Rule(expr->value, code.release(), action->value, line));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Rule");
        else soul::lexer::WriteFailureToLog(lexer, "Rule");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match LexerFileParser<Lexer>::Variables(Lexer& lexer, soul::ast::slg::Lexer* lxr)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Variables");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8883513078608560134);
    std::unique_ptr<soul::ast::slg::Variable> variable;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
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
                    if (*lexer == VARIABLES)
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
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == LBRACE)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                *parentMatch5 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LBRACE));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch7 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = LexerFileParser<Lexer>::Variable(lexer);
                                        variable.reset(static_cast<soul::ast::slg::Variable*>(match.value));
                                        if (match.hit)
                                        {
                                            lxr->AddVariable(variable.release());
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch7 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch6 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch10 = &match;
            {
                soul::parser::Match match(true);
                soul::parser::Match* parentMatch11 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == RBRACE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        *parentMatch11 = match;
                    }
                    else
                    {
                        lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RBRACE));
                    }
                }
                *parentMatch10 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Variables");
        else soul::lexer::WriteFailureToLog(lexer, "Variables");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match LexerFileParser<Lexer>::Variable(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Variable");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8883513078608560135);
    std::string name = std::string();
    std::unique_ptr<soul::ast::cpp::TypeIdNode> type;
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
                    soul::parser::Match match = DeclaratorParser<Lexer>::TypeId(lexer);
                    type.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
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
                                name = util::ToUtf8(lexer.GetToken(pos).ToString());
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch7 = &match;
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
                            *parentMatch7 = match;
                        }
                        else
                        {
                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(SEMICOLON));
                        }
                    }
                    *parentMatch6 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Variable");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::ast::slg::Variable(type.release(), name));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Variable");
        else soul::lexer::WriteFailureToLog(lexer, "Variable");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match LexerFileParser<Lexer>::Actions(Lexer& lexer, soul::ast::slg::Lexer* lxr)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Actions");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8883513078608560136);
    int actionId = int();
    std::unique_ptr<soul::parser::Value<int>> action;
    std::unique_ptr<soul::ast::cpp::CompoundStatementNode> stmt;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
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
                    if (*lexer == ACTIONS)
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
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == LBRACE)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                *parentMatch5 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LBRACE));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch7 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch11 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                bool pass = true;
                                                soul::parser::Match match = LexerFileParser<Lexer>::Action(lexer);
                                                action.reset(static_cast<soul::parser::Value<int>*>(match.value));
                                                if (match.hit)
                                                {
                                                    actionId = action->value;
                                                    pass = actionId != -1;
                                                }
                                                if (match.hit && !pass)
                                                {
                                                    match = soul::parser::Match(false);
                                                }
                                                *parentMatch11 = match;
                                            }
                                            *parentMatch10 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch12 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == ASSIGN)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch12 = match;
                                            }
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch13 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch14 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = StatementParser<Lexer>::CompoundStatement(lexer);
                                                stmt.reset(static_cast<soul::ast::cpp::CompoundStatementNode*>(match.value));
                                                if (match.hit)
                                                {
                                                    lxr->AddAction(new soul::ast::slg::Action(actionId, stmt.release()));
                                                }
                                                *parentMatch14 = match;
                                            }
                                            *parentMatch13 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch7 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch6 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch15 = &match;
            {
                soul::parser::Match match(true);
                soul::parser::Match* parentMatch16 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == RBRACE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        *parentMatch16 = match;
                    }
                    else
                    {
                        lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RBRACE));
                    }
                }
                *parentMatch15 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Actions");
        else soul::lexer::WriteFailureToLog(lexer, "Actions");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match LexerFileParser<Lexer>::Action(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Action");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8883513078608560137);
    int actionId = int();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
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
                    if (*lexer == DOLLAR)
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
                        soul::parser::Match match(false);
                        if (*lexer == LPAREN)
                        {
                            ++lexer;
                            match.hit = true;
                        }
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
                        if (*lexer == INTEGER_LITERAL)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            actionId = lexer.GetToken(pos).ToInt();
                        }
                        *parentMatch6 = match;
                    }
                    *parentMatch5 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch8 = &match;
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Action");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
                            return soul::parser::Match(true, new soul::parser::Value<int>(actionId));
                        }
                    }
                    *parentMatch8 = match;
                }
                *parentMatch7 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch9 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch10 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(true);
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Action");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
                            return soul::parser::Match(true, new soul::parser::Value<int>(-1));
                        }
                    }
                    *parentMatch10 = match;
                }
                *parentMatch9 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Action");
        else soul::lexer::WriteFailureToLog(lexer, "Action");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct LexerFileParser<soul::lexer::Lexer<soul::lex::slg::SlgLexer<char32_t>, char32_t>>;

} // namespace soul::slg::lexer::file::parser
