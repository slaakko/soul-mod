
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/test/eslg_test/lexer_file.parser' using soul parser generator espg version 5.0.0

module soul_expected.slg.lexer.file.parser;

import util_expected;
import soul_expected.ast.spg;
import soul_expected.cpp.token;
import soul_expected.cpp.op.token;
import soul_expected.punctuation.token;
import soul_expected.tool.token;
import soul_expected.common.common.parser;
import soul_expected.common.token.parser;
import soul_expected.cpp.statement.parser;
import soul_expected.cpp.declarator.parser;
import soul_expected.ast.cpp;
import soul_expected.ast.common;
import soul_expected.lex.slg;

using namespace soul_expected::cpp::token;
using namespace soul_expected::cpp::op::token;
using namespace soul_expected::punctuation::token;
using namespace soul_expected::tool::token;
using namespace soul_expected::common::common::parser;
using namespace soul_expected::common::token::parser;
using namespace soul_expected::cpp::statement::parser;
using namespace soul_expected::cpp::declarator::parser;
using namespace soul_expected::ast::cpp;
using namespace soul_expected::ast::common;
using namespace soul_expected::lex::slg;

namespace soul_expected::slg::lexer::file::parser {

template<typename LexerT>
std::expected<std::unique_ptr<soul_expected::ast::slg::LexerFile>, int> LexerFileParser<LexerT>::Parse(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    std::unique_ptr<soul_expected::ast::slg::LexerFile> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    auto a = ++lexer;
    if (!a) return std::unexpected<int>(a.error());
    std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::LexerFile(lexer, context);
    if (!m) return std::unexpected<int>(m.error());
    soul_expected::parser::Match match = *m;
    value.reset(static_cast<soul_expected::ast::slg::LexerFile*>(match.value));
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->DecIndent();
        lexer.Log()->WriteEndRule("parse");
    }
    #endif
    if (match.hit)
    {
        if (*lexer == soul_expected::lexer::END_TOKEN)
        {
            return value;
        }
        else
        {
            return lexer.FarthestError();
        }
    }
    else
    {
        return lexer.FarthestError();
    }
    return value;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LexerFileParser<LexerT>::LexerFile(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "LexerFile");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4642344667512307713);
    std::unique_ptr<soul_expected::ast::slg::LexerFile> lexerFile = std::unique_ptr<soul_expected::ast::slg::LexerFile>();
    std::unique_ptr<soul_expected::ast::slg::Lexer> lxr = std::unique_ptr<soul_expected::ast::slg::Lexer>();
    std::unique_ptr<soul_expected::ast::common::ExportModule> exportModule;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch9 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul_expected::parser::Match match(true);
                                            if (match.hit)
                                            {
                                                lexerFile.reset(new soul_expected::ast::slg::LexerFile(lexer.FileName()));
                                            }
                                            *parentMatch9 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch10 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch11 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul_expected::parser::Match, int> m = CommonParser<LexerT>::ExportModule(lexer);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                exportModule.reset(static_cast<soul_expected::ast::common::ExportModule*>(match.value));
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
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch12 = &match;
                                    {
                                        std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::Imports(lexer, lexerFile.get());
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        *parentMatch12 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch13 = &match;
                                {
                                    std::expected<soul_expected::parser::Match, int> m = CommonParser<LexerT>::LexerKeyword(lexer);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    *parentMatch13 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch14 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch15 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul_expected::parser::Match match(false);
                                    if (*lexer == ID)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto rv = lexer.TokenToUtf8(pos);
                                        if (!rv) return std::unexpected<int>(rv.error());
                                        lxr.reset(new soul_expected::ast::slg::Lexer(*rv));
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
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch16 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == LBRACE)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch16 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch17 = &match;
                    {
                        soul_expected::parser::Match match(true);
                        soul_expected::parser::Match* parentMatch18 = &match;
                        {
                            while (true)
                            {
                                std::int64_t save = lexer.GetPos();
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch19 = &match;
                                    {
                                        std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::LexerContent(lexer, context, lxr.get());
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        *parentMatch19 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch18 = match;
                                    }
                                    else
                                    {
                                        lexer.SetPos(save);
                                        break;
                                    }
                                }
                            }
                        }
                        *parentMatch17 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch20 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == RBRACE)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch20 = match;
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LexerFile");
                #endif
                return soul_expected::parser::Match(true, lexerFile.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LexerFile");
        else soul_expected::lexer::WriteFailureToLog(lexer, "LexerFile");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LexerFileParser<LexerT>::Imports(LexerT& lexer, soul_expected::ast::slg::LexerFile* lexerFile)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Imports");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4642344667512307714);
    std::unique_ptr<soul_expected::ast::common::Import> imp;
    soul_expected::parser::Match match(true);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        while (true)
        {
            std::int64_t save = lexer.GetPos();
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch1 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch2 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = CommonParser<LexerT>::Import(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        imp.reset(static_cast<soul_expected::ast::common::Import*>(match.value));
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Imports");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Imports");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LexerFileParser<LexerT>::LexerContent(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::slg::Lexer* lxr)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "LexerContent");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4642344667512307715);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case RULES:
            {
                std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::Rules(lexer, context, lxr);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case VARIABLES:
            {
                std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::Variables(lexer, context, lxr);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case ACTIONS:
            {
                std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::Actions(lexer, context, lxr);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LexerContent");
        else soul_expected::lexer::WriteFailureToLog(lexer, "LexerContent");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LexerFileParser<LexerT>::Rules(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::slg::Lexer* lxr)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Rules");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4642344667512307716);
    std::unique_ptr<soul_expected::ast::slg::Rule> rl;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == RULES)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        if (*lexer == LBRACE)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
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
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch5 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch6 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::Rule(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        rl.reset(static_cast<soul_expected::ast::slg::Rule*>(match.value));
                                        if (match.hit)
                                        {
                                            lxr->AddRule(rl.release());
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch6 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch5 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch9 = &match;
            {
                soul_expected::parser::Match match(false);
                if (*lexer == RBRACE)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                *parentMatch9 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Rules");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Rules");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LexerFileParser<LexerT>::Rule(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Rule");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4642344667512307717);
    int line = int();
    std::unique_ptr<soul_expected::parser::Value<std::string>> expr;
    std::unique_ptr<soul_expected::parser::Value<int>> action;
    std::unique_ptr<soul_expected::ast::cpp::CompoundStatementNode> code;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = CommonParser<LexerT>::ExprString(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        expr.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            auto t = lexer.GetToken(pos);
                            if (!t) return std::unexpected<int>(t.error());
                            auto token = *t;
                            line = token->line;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::Action(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        action.reset(static_cast<soul_expected::parser::Value<int>*>(match.value));
                        *parentMatch5 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch6 = &match;
                {
                    std::expected<soul_expected::parser::Match, int> m = StatementParser<LexerT>::CompoundStatement(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    code.reset(static_cast<soul_expected::ast::cpp::CompoundStatementNode*>(match.value));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Rule");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::ast::slg::Rule(expr->value, code.release(), action->value, line));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Rule");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Rule");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LexerFileParser<LexerT>::Variables(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::slg::Lexer* lxr)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Variables");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4642344667512307718);
    std::unique_ptr<soul_expected::ast::slg::Variable> variable;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == VARIABLES)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        if (*lexer == LBRACE)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
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
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch5 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch6 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::Variable(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        variable.reset(static_cast<soul_expected::ast::slg::Variable*>(match.value));
                                        if (match.hit)
                                        {
                                            lxr->AddVariable(variable.release());
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch6 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch5 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch9 = &match;
            {
                soul_expected::parser::Match match(false);
                if (*lexer == RBRACE)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                *parentMatch9 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Variables");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Variables");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LexerFileParser<LexerT>::Variable(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Variable");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4642344667512307719);
    std::string name = std::string();
    std::unique_ptr<soul_expected::ast::cpp::TypeIdNode> type;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::expected<soul_expected::parser::Match, int> m = DeclaratorParser<LexerT>::TypeId(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    type.reset(static_cast<soul_expected::ast::cpp::TypeIdNode*>(match.value));
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            if (*lexer == ID)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                auto rv = lexer.TokenToUtf8(pos);
                                if (!rv) return std::unexpected<int>(rv.error());
                                name = *rv;
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
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch6 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == SEMICOLON)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Variable");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::ast::slg::Variable(type.release(), name));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Variable");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Variable");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LexerFileParser<LexerT>::Actions(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::slg::Lexer* lxr)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Actions");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4642344667512307720);
    int actionId = int();
    std::unique_ptr<soul_expected::parser::Value<int>> action;
    std::unique_ptr<soul_expected::ast::cpp::CompoundStatementNode> stmt;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == ACTIONS)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        if (*lexer == LBRACE)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
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
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch5 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch6 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch9 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch10 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                bool pass = true;
                                                std::expected<soul_expected::parser::Match, int> m = LexerFileParser<LexerT>::Action(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                action.reset(static_cast<soul_expected::parser::Value<int>*>(match.value));
                                                if (match.hit)
                                                {
                                                    actionId = action->value;
                                                    pass = actionId != -1;
                                                }
                                                if (match.hit && !pass)
                                                {
                                                    match = soul_expected::parser::Match(false);
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch11 = &match;
                                            {
                                                soul_expected::parser::Match match(false);
                                                if (*lexer == ASSIGN)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            *parentMatch9 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch12 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch13 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul_expected::parser::Match, int> m = StatementParser<LexerT>::CompoundStatement(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                stmt.reset(static_cast<soul_expected::ast::cpp::CompoundStatementNode*>(match.value));
                                                if (match.hit)
                                                {
                                                    lxr->AddAction(new soul_expected::ast::slg::Action(actionId, stmt.release()));
                                                }
                                                *parentMatch13 = match;
                                            }
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch6 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch5 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch14 = &match;
            {
                soul_expected::parser::Match match(false);
                if (*lexer == RBRACE)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                *parentMatch14 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Actions");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Actions");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LexerFileParser<LexerT>::Action(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Action");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4642344667512307721);
    int actionId = int();
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == DOLLAR)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        if (*lexer == LPAREN)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
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
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch5 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch6 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == INTEGER_LITERAL)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            auto rv = lexer.TokenToInt(pos);
                            if (!rv) return std::unexpected<int>(rv.error());
                            actionId = *rv;
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
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch7 = &match;
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch8 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == RPAREN)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Action");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<int>(actionId));
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
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch9 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch10 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(true);
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Action");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<int>(-1));
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Action");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Action");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct LexerFileParser<soul_expected::lexer::Lexer<soul_expected::lex::slg::SlgLexer<char32_t>, char32_t>>;

} // namespace soul_expected::slg::lexer::file::parser
