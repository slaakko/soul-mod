
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/espg/parser_file.parser' using soul parser generator espg version 5.0.0

module soul_expected.spg.parser.file.parser;

import util_expected;
import soul_expected.ast.spg;
import soul_expected.ast.common;
import soul_expected.cpp.token;
import soul_expected.cpp.op.token;
import soul_expected.punctuation.token;
import soul_expected.tool.token;
import soul_expected.common.common.parser;
import soul_expected.spg.token.parser;
import soul_expected.cpp.declarator.parser;
import soul_expected.cpp.statement.parser;
import soul_expected.cpp.expression.parser;
import soul_expected.lex.spg;
import soul_expected.ast.cpp;
import soul_expected.common.token.parser;
import soul_expected.spg.error;

namespace soul_expected::spg::parser::file::parser {

template<typename LexerT>
std::expected<std::unique_ptr<soul_expected::ast::spg::ParserFile>, int> ParserFileParser<LexerT>::Parse(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    std::unique_ptr<soul_expected::ast::spg::ParserFile> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    auto a = ++lexer;
    if (!a) return std::unexpected<int>(a.error());
    std::expected<soul_expected::parser::Match, int> m = ParserFileParser<LexerT>::ParserFile(lexer, context);
    if (!m) return std::unexpected<int>(m.error());
    soul_expected::parser::Match match = *m;
    value.reset(static_cast<soul_expected::ast::spg::ParserFile*>(match.value));
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
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::ParserFile(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "ParserFile");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805697);
    std::unique_ptr<soul_expected::ast::spg::ParserFile> parserFile = std::unique_ptr<soul_expected::ast::spg::ParserFile>();
    std::unique_ptr<soul_expected::ast::common::ExportModule> exportModuleDeclaration;
    std::unique_ptr<soul_expected::ast::common::Import> importDeclaration;
    std::unique_ptr<soul_expected::ast::spg::GrammarParser> parser;
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
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(true);
                            if (match.hit)
                            {
                                parserFile.reset(new soul_expected::ast::spg::ParserFile(lexer.FileName()));
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch6 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch7 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::common::common::parser::CommonParser<LexerT>::ExportModule(lexer);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                exportModuleDeclaration.reset(static_cast<soul_expected::ast::common::ExportModule*>(match.value));
                                if (match.hit)
                                {
                                    auto rv = parserFile->SetExportModule(exportModuleDeclaration.release());
                                    if (!rv) return std::unexpected<int>(rv.error());
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch6 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch8 = &match;
                    {
                        soul_expected::parser::Match match(true);
                        soul_expected::parser::Match* parentMatch9 = &match;
                        {
                            while (true)
                            {
                                std::int64_t save = lexer.GetPos();
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch10 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch11 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            std::expected<soul_expected::parser::Match, int> m = soul_expected::common::common::parser::CommonParser<LexerT>::Import(lexer);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul_expected::parser::Match match = *m;
                                            importDeclaration.reset(static_cast<soul_expected::ast::common::Import*>(match.value));
                                            if (match.hit)
                                            {
                                                parserFile->AddImport(importDeclaration.release());
                                            }
                                            *parentMatch11 = match;
                                        }
                                        *parentMatch10 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch9 = match;
                                    }
                                    else
                                    {
                                        lexer.SetPos(save);
                                        break;
                                    }
                                }
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
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch12 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch13 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch14 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch15 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Parser(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        parser.reset(static_cast<soul_expected::ast::spg::GrammarParser*>(match.value));
                                        if (match.hit)
                                        {
                                            parserFile->AddParser(parser.release());
                                        }
                                        *parentMatch15 = match;
                                    }
                                    *parentMatch14 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch13 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                    break;
                                }
                            }
                        }
                    }
                    *parentMatch12 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParserFile");
                #endif
                return soul_expected::parser::Match(true, parserFile.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParserFile");
        else soul_expected::lexer::WriteFailureToLog(lexer, "ParserFile");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Parser(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Parser");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805698);
    std::unique_ptr<soul_expected::ast::spg::GrammarParser> parser = std::unique_ptr<soul_expected::ast::spg::GrammarParser>();
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
                            std::expected<soul_expected::parser::Match, int> m = soul_expected::common::common::parser::CommonParser<LexerT>::ParserKeyword(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul_expected::parser::Match match(false);
                                    if (*lexer == soul_expected::cpp::token::ID)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        auto u = lexer.TokenToUtf8(pos);
                                        if (!u) return std::unexpected<int>(u.error());
                                        parser.reset(new soul_expected::ast::spg::GrammarParser(*sp, *u));
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
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch8 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::punctuation::token::LBRACE)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch9 = &match;
                    {
                        soul_expected::parser::Match match(true);
                        soul_expected::parser::Match* parentMatch10 = &match;
                        {
                            while (true)
                            {
                                std::int64_t save = lexer.GetPos();
                                {
                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::ParserStatement(lexer, context, parser.get());
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    if (match.hit)
                                    {
                                        *parentMatch10 = match;
                                    }
                                    else
                                    {
                                        lexer.SetPos(save);
                                        break;
                                    }
                                }
                            }
                        }
                        *parentMatch9 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch11 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::punctuation::token::RBRACE)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch11 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Parser");
                #endif
                return soul_expected::parser::Match(true, parser.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Parser");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Parser");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::ParserStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "ParserStatement");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805699);
    std::unique_ptr<soul_expected::parser::Value<bool>> ruleStatement;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case soul_expected::cpp::token::ID:
            {
                std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::LexerStatement(lexer, context, parser);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case soul_expected::tool::token::MAIN:
            {
                std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::MainStatement(lexer, parser);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case soul_expected::cpp::token::USING:
            {
                std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::UsingStatement(lexer, parser);
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
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::RuleStatement(lexer, context, parser);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                ruleStatement.reset(static_cast<soul_expected::parser::Value<bool>*>(match.value));
                *parentMatch2 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParserStatement");
        else soul_expected::lexer::WriteFailureToLog(lexer, "ParserStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::LexerStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "LexerStatement");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805700);
    std::unique_ptr<soul_expected::ast::cpp::TypeIdNode> lexerTypeId;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::expected<soul_expected::parser::Match, int> m = soul_expected::common::common::parser::CommonParser<LexerT>::LexerKeyword(lexer);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::TypeId(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                lexerTypeId.reset(static_cast<soul_expected::ast::cpp::TypeIdNode*>(match.value));
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch3 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::punctuation::token::SEMICOLON)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    parser->AddLexer(lexerTypeId.release());
                }
                *parentMatch4 = match;
            }
            *parentMatch3 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LexerStatement");
        else soul_expected::lexer::WriteFailureToLog(lexer, "LexerStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::MainStatement(LexerT& lexer, soul_expected::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "MainStatement");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805701);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::tool::token::MAIN)
        {
            auto a = ++lexer;
            if (!a) return std::unexpected<int>(a.error());
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::punctuation::token::SEMICOLON)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    parser->SetMain();
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MainStatement");
        else soul_expected::lexer::WriteFailureToLog(lexer, "MainStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::UsingStatement(LexerT& lexer, soul_expected::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "UsingStatement");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805702);
    std::unique_ptr<soul_expected::parser::Value<std::string>> parserRuleId;
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
                    if (*lexer == soul_expected::cpp::token::USING)
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
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::common::common::parser::CommonParser<LexerT>::QualifiedId(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        parserRuleId.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
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
                    if (*lexer == soul_expected::punctuation::token::SEMICOLON)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch5 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            auto sp = lexer.GetSourcePos(pos);
            if (!sp) return std::unexpected<int>(sp.error());
            parser->AddUsing(*sp, parserRuleId->value);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UsingStatement");
        else soul_expected::lexer::WriteFailureToLog(lexer, "UsingStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::RuleStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "RuleStatement");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805703);
    std::unique_ptr<soul_expected::ast::spg::RuleParser> rule = std::unique_ptr<soul_expected::ast::spg::RuleParser>();
    std::unique_ptr<soul_expected::ast::cpp::TypeIdNode> returnType;
    std::unique_ptr<soul_expected::ast::spg::Parser> definition;
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
                                    std::int64_t pos = lexer.GetPos();
                                    soul_expected::parser::Match match(false);
                                    if (*lexer == soul_expected::cpp::token::ID)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        auto u = lexer.TokenToUtf8(pos);
                                        if (!u) return std::unexpected<int>(u.error());
                                        rule.reset(new soul_expected::ast::spg::RuleParser(*sp, *u));
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch8 = &match;
                                {
                                    soul_expected::parser::Match match(true);
                                    std::int64_t save = lexer.GetPos();
                                    soul_expected::parser::Match* parentMatch9 = &match;
                                    {
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::ParametersAndVariables(lexer, context, rule.get());
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        if (match.hit)
                                        {
                                            *parentMatch9 = match;
                                        }
                                        else
                                        {
                                            lexer.SetPos(save);
                                        }
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch10 = &match;
                            {
                                soul_expected::parser::Match match(true);
                                std::int64_t save = lexer.GetPos();
                                soul_expected::parser::Match* parentMatch11 = &match;
                                {
                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::ReturnType(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    returnType.reset(static_cast<soul_expected::ast::cpp::TypeIdNode*>(match.value));
                                    if (match.hit)
                                    {
                                        *parentMatch11 = match;
                                    }
                                    else
                                    {
                                        lexer.SetPos(save);
                                    }
                                }
                                *parentMatch10 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch12 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::punctuation::token::PRODUCES)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch12 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch13 = &match;
                    {
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::RuleBody(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        definition.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                        *parentMatch13 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch14 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::punctuation::token::SEMICOLON)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch14 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            rule->SetDefinition(definition.release());
            rule->SetReturnType(returnType.release());
            soul_expected::ast::spg::RuleParser *rulePtr = rule.get();
            bool succeeded = parser->AddRule(rule.release());
            if (!succeeded)
            {
                return std::unexpected<int>(soul_expected::spg::error::RuleNameNotUnique(lexer.FileName(), rulePtr));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleStatement");
        else soul_expected::lexer::WriteFailureToLog(lexer, "RuleStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::ParametersAndVariables(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::spg::RuleParser* rule)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "ParametersAndVariables");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805704);
    std::unique_ptr<soul_expected::ast::spg::ParamVar> paramOrVariable;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            if (*lexer == soul_expected::punctuation::token::LPAREN)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                soul_expected::parser::Match match(true);
                std::int64_t save = lexer.GetPos();
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
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::ParamOrVariable(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                paramOrVariable.reset(static_cast<soul_expected::ast::spg::ParamVar*>(match.value));
                                if (match.hit)
                                {
                                    rule->AddParamOrVariable(paramOrVariable.release());
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch7 = &match;
                            {
                                soul_expected::parser::Match match(true);
                                soul_expected::parser::Match* parentMatch8 = &match;
                                {
                                    while (true)
                                    {
                                        std::int64_t save = lexer.GetPos();
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch9 = &match;
                                            {
                                                soul_expected::parser::Match match(false);
                                                if (*lexer == soul_expected::punctuation::token::COMMA)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                *parentMatch9 = match;
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
                                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::ParamOrVariable(lexer, context);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul_expected::parser::Match match = *m;
                                                        paramOrVariable.reset(static_cast<soul_expected::ast::spg::ParamVar*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            rule->AddParamOrVariable(paramOrVariable.release());
                                                        }
                                                        *parentMatch11 = match;
                                                    }
                                                    *parentMatch10 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch8 = match;
                                            }
                                            else
                                            {
                                                lexer.SetPos(save);
                                                break;
                                            }
                                        }
                                    }
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch3 = match;
                    }
                    else
                    {
                        lexer.SetPos(save);
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch12 = &match;
        {
            soul_expected::parser::Match match(false);
            if (*lexer == soul_expected::punctuation::token::RPAREN)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            *parentMatch12 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParametersAndVariables");
        else soul_expected::lexer::WriteFailureToLog(lexer, "ParametersAndVariables");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::ParamOrVariable(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "ParamOrVariable");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805705);
    std::unique_ptr<soul_expected::ast::cpp::TypeIdNode> varType;
    std::unique_ptr<soul_expected::parser::Value<std::string>> varName;
    std::unique_ptr<soul_expected::ast::cpp::TypeIdNode> paramType;
    std::unique_ptr<soul_expected::parser::Value<std::string>> paramName;
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
                if (*lexer == soul_expected::tool::token::VAR)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::TypeId(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    varType.reset(static_cast<soul_expected::ast::cpp::TypeIdNode*>(match.value));
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::Declarator(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    varName.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParamOrVariable");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::spg::Variable(*sp, varType.release(), varName->value));
                        }
                    }
                    *parentMatch5 = match;
                }
                *parentMatch4 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch6 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch7 = &match;
                {
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::TypeId(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    paramType.reset(static_cast<soul_expected::ast::cpp::TypeIdNode*>(match.value));
                    *parentMatch7 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch8 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch9 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::Declarator(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            paramName.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                auto sp = lexer.GetSourcePos(pos);
                                if (!sp) return std::unexpected<int>(sp.error());
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParamOrVariable");
                                    #endif
                                    return soul_expected::parser::Match(true, new soul_expected::ast::spg::Parameter(*sp, paramType.release(), paramName->value));
                                }
                            }
                            *parentMatch9 = match;
                        }
                        *parentMatch8 = match;
                    }
                    *parentMatch7 = match;
                }
                *parentMatch6 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParamOrVariable");
        else soul_expected::lexer::WriteFailureToLog(lexer, "ParamOrVariable");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::ReturnType(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "ReturnType");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805706);
    std::unique_ptr<soul_expected::ast::cpp::TypeIdNode> typeId;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::punctuation::token::COLON)
        {
            auto a = ++lexer;
            if (!a) return std::unexpected<int>(a.error());
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::TypeId(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                typeId.reset(static_cast<soul_expected::ast::cpp::TypeIdNode*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ReturnType");
                        #endif
                        return soul_expected::parser::Match(true, typeId.release());
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ReturnType");
        else soul_expected::lexer::WriteFailureToLog(lexer, "ReturnType");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::RuleBody(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "RuleBody");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805707);
    std::unique_ptr<soul_expected::ast::spg::Parser> choice;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Choice(lexer, context);
        if (!m) return std::unexpected<int>(m.error());
        soul_expected::parser::Match match = *m;
        choice.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleBody");
                #endif
                return soul_expected::parser::Match(true, choice.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleBody");
        else soul_expected::lexer::WriteFailureToLog(lexer, "RuleBody");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Choice(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Choice");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805708);
    std::unique_ptr<soul_expected::ast::spg::Parser> value = std::unique_ptr<soul_expected::ast::spg::Parser>();
    std::unique_ptr<soul_expected::ast::spg::Parser> left;
    std::unique_ptr<soul_expected::ast::spg::Parser> right;
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
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Sequence(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                    if (match.hit)
                    {
                        value.reset(left.release());
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch6 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch7 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::punctuation::token::PIPE)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch8 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch9 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Sequence(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                right.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    value.reset(new soul_expected::ast::spg::ChoiceParser(*sp, value.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Choice");
                #endif
                return soul_expected::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Choice");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Choice");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Sequence(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Sequence");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805709);
    std::unique_ptr<soul_expected::ast::spg::Parser> value = std::unique_ptr<soul_expected::ast::spg::Parser>();
    std::unique_ptr<soul_expected::ast::spg::Parser> left;
    std::unique_ptr<soul_expected::ast::spg::Parser> right;
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
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Difference(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                    if (match.hit)
                    {
                        value.reset(left.release());
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch6 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch7 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Difference(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        right.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul_expected::ast::spg::SequenceParser(*sp, value.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Sequence");
                #endif
                return soul_expected::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Sequence");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Sequence");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Difference(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Difference");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805710);
    std::unique_ptr<soul_expected::ast::spg::Parser> value = std::unique_ptr<soul_expected::ast::spg::Parser>();
    std::unique_ptr<soul_expected::ast::spg::Parser> left;
    std::unique_ptr<soul_expected::ast::spg::Parser> right;
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
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::List(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                    if (match.hit)
                    {
                        value.reset(left.release());
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch6 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch7 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::cpp::op::token::MINUS)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch8 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch9 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::List(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                right.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    value.reset(new soul_expected::ast::spg::DifferenceParser(*sp, value.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Difference");
                #endif
                return soul_expected::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Difference");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Difference");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::List(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "List");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805711);
    std::unique_ptr<soul_expected::ast::spg::Parser> value = std::unique_ptr<soul_expected::ast::spg::Parser>();
    std::unique_ptr<soul_expected::ast::spg::Parser> left;
    std::unique_ptr<soul_expected::ast::spg::Parser> right;
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
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Prefix(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                    if (match.hit)
                    {
                        value.reset(left.release());
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch6 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch7 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                if (*lexer == soul_expected::cpp::op::token::REM)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                *parentMatch7 = match;
                            }
                            if (match.hit)
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch8 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch9 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Prefix(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        right.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul_expected::ast::spg::ListParser(*sp, value.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "List");
                #endif
                return soul_expected::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "List");
        else soul_expected::lexer::WriteFailureToLog(lexer, "List");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Prefix(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Prefix");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805712);
    std::unique_ptr<soul_expected::ast::spg::Parser> lookaheadp;
    std::unique_ptr<soul_expected::ast::spg::Parser> postfix;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case soul_expected::punctuation::token::AMP:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch1 = &match;
            {
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::punctuation::token::AMP)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                *parentMatch1 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch2 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch3 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Postfix(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        lookaheadp.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                        if (match.hit)
                        {
                            auto sp = lexer.GetSourcePos(pos);
                            if (!sp) return std::unexpected<int>(sp.error());
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Prefix");
                                #endif
                                return soul_expected::parser::Match(true, new soul_expected::ast::spg::LookaheadParser(*sp, lookaheadp.release()));
                            }
                        }
                        *parentMatch3 = match;
                    }
                    *parentMatch2 = match;
                }
                *parentMatch1 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case soul_expected::tool::token::EMPTY:
        case soul_expected::tool::token::ANY:
        case soul_expected::cpp::token::ID:
        case soul_expected::cpp::token::CHAR_LITERAL:
        case soul_expected::cpp::token::STRING_LITERAL:
        case soul_expected::punctuation::token::LPAREN:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Postfix(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                postfix.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Prefix");
                        #endif
                        return soul_expected::parser::Match(true, postfix.release());
                    }
                }
                *parentMatch4 = match;
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Prefix");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Prefix");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Postfix(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Postfix");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805713);
    std::unique_ptr<soul_expected::ast::spg::Parser> value = std::unique_ptr<soul_expected::ast::spg::Parser>();
    std::unique_ptr<soul_expected::ast::spg::Parser> primary;
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
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Primary(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    primary.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                    if (match.hit)
                    {
                        value.reset(primary.release());
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch6 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch7 = &match;
                            switch (*lexer)
                            {
                                case soul_expected::cpp::op::token::STAR:
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::cpp::op::token::STAR)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul_expected::ast::spg::KleeneParser(*sp, value.release()));
                                        }
                                        *parentMatch8 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch7 = match;
                                    }
                                    break;
                                }
                                case soul_expected::cpp::op::token::PLUS:
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch9 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::cpp::op::token::PLUS)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul_expected::ast::spg::PositiveParser(*sp, value.release()));
                                        }
                                        *parentMatch9 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch7 = match;
                                    }
                                    break;
                                }
                                case soul_expected::punctuation::token::QUEST:
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch10 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::punctuation::token::QUEST)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul_expected::ast::spg::OptionalParser(*sp, value.release()));
                                        }
                                        *parentMatch10 = match;
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Postfix");
                #endif
                return soul_expected::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Postfix");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Postfix");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Primary(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Primary");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805714);
    std::unique_ptr<soul_expected::ast::spg::Parser> value = std::unique_ptr<soul_expected::ast::spg::Parser>();
    std::unique_ptr<soul_expected::ast::spg::Parser> ruleCall;
    std::unique_ptr<soul_expected::ast::spg::Parser> primitive;
    std::unique_ptr<soul_expected::ast::spg::Parser> group;
    std::unique_ptr<soul_expected::ast::cpp::CompoundStatementNode> successCode;
    std::unique_ptr<soul_expected::ast::cpp::CompoundStatementNode> failureCode;
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
                        switch (*lexer)
                        {
                            case soul_expected::tool::token::EMPTY:
                            case soul_expected::tool::token::ANY:
                            case soul_expected::cpp::token::ID:
                            case soul_expected::cpp::token::CHAR_LITERAL:
                            case soul_expected::cpp::token::STRING_LITERAL:
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch6 = &match;
                                {
                                    std::int64_t save = lexer.GetPos();
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch7 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::RuleCall(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        ruleCall.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                                        if (match.hit)
                                        {
                                            value.reset(ruleCall.release());
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                    if (!match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch8 = &match;
                                        lexer.SetPos(save);
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch9 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Primitive(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                primitive.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                                                if (match.hit)
                                                {
                                                    value.reset(primitive.release());
                                                }
                                                *parentMatch9 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch6 = match;
                                    }
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                break;
                            }
                            case soul_expected::punctuation::token::LPAREN:
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch10 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Grouping(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    group.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
                                    if (match.hit)
                                    {
                                        value.reset(group.release());
                                    }
                                    *parentMatch10 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch5 = match;
                                }
                                break;
                            }
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch11 = &match;
                    {
                        soul_expected::parser::Match match(true);
                        std::int64_t save = lexer.GetPos();
                        soul_expected::parser::Match* parentMatch12 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch13 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch14 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul_expected::parser::Match match(false);
                                    if (*lexer == soul_expected::punctuation::token::EXCLAMATION)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        value.reset(new soul_expected::ast::spg::ExpectationParser(*sp, value.release()));
                                    }
                                    *parentMatch14 = match;
                                }
                                *parentMatch13 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch12 = match;
                            }
                            else
                            {
                                lexer.SetPos(save);
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
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch15 = &match;
                {
                    soul_expected::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul_expected::parser::Match* parentMatch16 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch17 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch18 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch19 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch20 = &match;
                                    {
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::statement::parser::StatementParser<LexerT>::CompoundStatement(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        successCode.reset(static_cast<soul_expected::ast::cpp::CompoundStatementNode*>(match.value));
                                        *parentMatch20 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch21 = &match;
                                        {
                                            soul_expected::parser::Match match(true);
                                            std::int64_t save = lexer.GetPos();
                                            soul_expected::parser::Match* parentMatch22 = &match;
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch23 = &match;
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch24 = &match;
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        if (*lexer == soul_expected::cpp::op::token::DIV)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        *parentMatch24 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch25 = &match;
                                                        {
                                                            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::statement::parser::StatementParser<LexerT>::CompoundStatement(lexer, context);
                                                            if (!m) return std::unexpected<int>(m.error());
                                                            soul_expected::parser::Match match = *m;
                                                            failureCode.reset(static_cast<soul_expected::ast::cpp::CompoundStatementNode*>(match.value));
                                                            *parentMatch25 = match;
                                                        }
                                                        *parentMatch24 = match;
                                                    }
                                                    *parentMatch23 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch22 = match;
                                                }
                                                else
                                                {
                                                    lexer.SetPos(save);
                                                }
                                            }
                                            *parentMatch21 = match;
                                        }
                                        *parentMatch20 = match;
                                    }
                                    *parentMatch19 = match;
                                }
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    value.reset(new soul_expected::ast::spg::ActionParser(*sp, value.release(), successCode.release(), failureCode.release()));
                                }
                                *parentMatch18 = match;
                            }
                            *parentMatch17 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch16 = match;
                        }
                        else
                        {
                            lexer.SetPos(save);
                        }
                    }
                    *parentMatch15 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primary");
                #endif
                return soul_expected::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primary");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Primary");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::RuleCall(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "RuleCall");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805715);
    std::string ruleName = std::string();
    std::int64_t nonterminalPos = std::int64_t();
    std::unique_ptr<soul_expected::ast::cpp::ExprListNode> args = std::unique_ptr<soul_expected::ast::cpp::ExprListNode>();
    std::unique_ptr<soul_expected::parser::Value<std::string>> nt;
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
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Nonterminal(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        nt.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            ruleName = nt->value;
                            nonterminalPos = pos;
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
                        soul_expected::parser::Match match(true);
                        std::int64_t save = lexer.GetPos();
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
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch10 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            bool pass = true;
                                            soul_expected::parser::Match match(false);
                                            if (*lexer == soul_expected::punctuation::token::LPAREN)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                auto t1 = lexer.GetToken(pos);
                                                if (!t1) return std::unexpected<int>(t1.error());
                                                auto t2 = lexer.GetToken(nonterminalPos);
                                                if (!t2) return std::unexpected<int>(t2.error());
                                                pass = soul_expected::lexer::NoWhiteSpaceBetweenTokens(**t2, **t1);
                                                auto sp = lexer.GetSourcePos(pos);
                                                if (!sp) return std::unexpected<int>(sp.error());
                                                args.reset(new soul_expected::ast::cpp::ExprListNode(*sp));
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
                                            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::expression::parser::ExpressionParser<LexerT>::ExpressionList(lexer, context, args.get());
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul_expected::parser::Match match = *m;
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
                                        if (*lexer == soul_expected::punctuation::token::RPAREN)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
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
                            }
                        }
                        *parentMatch5 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch13 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::punctuation::token::COLON)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch13 = match;
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
                soul_expected::parser::Match* parentMatch15 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::cpp::token::ID)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        auto u = lexer.TokenToUtf8(pos);
                        if (!u) return std::unexpected<int>(u.error());
                        std::string instanceName = *u;
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleCall");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::spg::NonterminalParser(*sp, ruleName, instanceName, args.release()));
                        }
                    }
                    *parentMatch15 = match;
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleCall");
        else soul_expected::lexer::WriteFailureToLog(lexer, "RuleCall");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Nonterminal(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Nonterminal");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805716);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            if (*lexer == soul_expected::cpp::token::ID)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            auto u = lexer.TokenToUtf8(pos);
            if (!u) return std::unexpected<int>(u.error());
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Nonterminal");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(*u));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Nonterminal");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Nonterminal");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Primitive(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Primitive");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805717);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case soul_expected::tool::token::EMPTY:
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch2 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::tool::token::EMPTY)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::spg::EmptyParser(*sp));
                        }
                    }
                    *parentMatch2 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case soul_expected::tool::token::ANY:
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::tool::token::ANY)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::spg::AnyParser(*sp));
                        }
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case soul_expected::cpp::token::ID:
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::cpp::token::ID)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        auto u = lexer.TokenToUtf8(pos);
                        if (!u) return std::unexpected<int>(u.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::spg::TokenParser(*sp, *u));
                        }
                    }
                    *parentMatch4 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case soul_expected::cpp::token::CHAR_LITERAL:
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch5 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::cpp::token::CHAR_LITERAL)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        auto t = lexer.GetToken(pos);
                        if (!t) return std::unexpected<int>(t.error());
                        auto cl = soul_expected::common::token::parser::ParseCharLiteral(lexer.FileName(), *t);
                        if (!cl) return std::unexpected<int>(cl.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::spg::CharParser(*sp, *cl));
                        }
                    }
                    *parentMatch5 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case soul_expected::cpp::token::STRING_LITERAL:
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch6 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::cpp::token::STRING_LITERAL)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        auto t = lexer.GetToken(pos);
                        if (!t) return std::unexpected<int>(t.error());
                        auto cs = soul_expected::spg::token::parser::ParseStringLiteralOrCharSet(lexer.FileName(), *t, *sp);
                        if (!cs) return std::unexpected<int>(cs.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul_expected::parser::Match(true, *cs);
                        }
                    }
                    *parentMatch6 = match;
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Primitive");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> ParserFileParser<LexerT>::Grouping(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Grouping");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 338853167099805718);
    std::unique_ptr<soul_expected::ast::spg::Parser> choice;
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
                    if (*lexer == soul_expected::punctuation::token::LPAREN)
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
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::spg::parser::file::parser::ParserFileParser<LexerT>::Choice(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        choice.reset(static_cast<soul_expected::ast::spg::Parser*>(match.value));
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
                    if (*lexer == soul_expected::punctuation::token::RPAREN)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch5 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            auto sp = lexer.GetSourcePos(pos);
            if (!sp) return std::unexpected<int>(sp.error());
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Grouping");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::ast::spg::GroupParser(*sp, choice.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Grouping");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Grouping");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct ParserFileParser<soul_expected::lexer::Lexer<soul_expected::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul_expected::spg::parser::file::parser
