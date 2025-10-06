
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ospg/parser_file.parser' using soul parser generator ospg version 5.0.0

module soul.spg.parser.file.parser;

import util;
import soul.ast.spg;
import soul.ast.common;
import soul.ast.common;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.punctuation.token;
import soul.tool.token;
import soul.common.common.parser;
import soul.spg.token.parser;
import soul.cpp.declarator.parser;
import soul.cpp.statement.parser;
import soul.cpp.expression.parser;
import soul.lex.spg;
import soul.ast.cpp;
import soul.common.token.parser;
import soul.spg.error;

namespace soul::spg::parser::file::parser {

template<typename LexerT>
std::expected<std::unique_ptr<soul::ast::spg::ParserFile>, int> ParserFileParser<LexerT>::Parse(LexerT& lexer, soul::ast::cpp::Context* context)
{
    std::unique_ptr<soul::ast::spg::ParserFile> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    auto a = ++lexer;
    if (!a) return std::unexpected<int>(a.error());
    std::expected<soul::parser::Match, int> m = ParserFileParser<LexerT>::ParserFile(lexer, context);
    if (!m) return std::unexpected<int>(m.error());
    soul::parser::Match match = *m;
    value.reset(static_cast<soul::ast::spg::ParserFile*>(match.value));
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
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::ParserFile(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParserFile");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920193);
    std::unique_ptr<soul::ast::spg::ParserFile> parserFile = std::unique_ptr<soul::ast::spg::ParserFile>();
    std::unique_ptr<soul::ast::common::ExportModule> exportModuleDeclaration;
    std::unique_ptr<soul::ast::common::Import> importDeclaration;
    std::unique_ptr<soul::ast::spg::GrammarParser> parser;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
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
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(true);
                            if (match.hit)
                            {
                                parserFile.reset(new soul::ast::spg::ParserFile(lexer.FileName()));
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = soul::common::common::parser::CommonParser<LexerT>::Export(lexer);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                exportModuleDeclaration.reset(static_cast<soul::ast::common::ExportModule*>(match.value));
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch8 = &match;
                    {
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch9 = &match;
                        {
                            while (true)
                            {
                                std::int64_t save = lexer.GetPos();
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch10 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch11 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            std::expected<soul::parser::Match, int> m = soul::common::common::parser::CommonParser<LexerT>::Import(lexer);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            importDeclaration.reset(static_cast<soul::ast::common::Import*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch12 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch13 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch14 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch15 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Parser(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        parser.reset(static_cast<soul::ast::spg::GrammarParser*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParserFile");
                #endif
                return soul::parser::Match(true, parserFile.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParserFile");
        else soul::lexer::WriteFailureToLog(lexer, "ParserFile");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Parser(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Parser");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920194);
    std::unique_ptr<soul::ast::spg::GrammarParser> parser = std::unique_ptr<soul::ast::spg::GrammarParser>();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
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
                            std::expected<soul::parser::Match, int> m = soul::common::common::parser::CommonParser<LexerT>::ParserKeyword(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
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
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == soul::cpp::token::ID)
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
                                        parser.reset(new soul::ast::spg::GrammarParser(*sp, *u));
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
                            if (*lexer == soul::punctuation::token::LBRACE)
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch9 = &match;
                    {
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch10 = &match;
                        {
                            while (true)
                            {
                                std::int64_t save = lexer.GetPos();
                                {
                                    std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::ParserStatement(lexer, context, parser.get());
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch11 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == soul::punctuation::token::RBRACE)
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Parser");
                #endif
                return soul::parser::Match(true, parser.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Parser");
        else soul::lexer::WriteFailureToLog(lexer, "Parser");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::ParserStatement(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParserStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920195);
    std::unique_ptr<soul::parser::Value<bool>> ruleStatement;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case soul::cpp::token::ID:
            {
                std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::LexerStatement(lexer, context, parser);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case soul::tool::token::MAIN:
            {
                std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::MainStatement(lexer, parser);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case soul::cpp::token::USING:
            {
                std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::UsingStatement(lexer, parser);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
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
                std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::RuleStatement(lexer, context, parser);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                ruleStatement.reset(static_cast<soul::parser::Value<bool>*>(match.value));
                *parentMatch2 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParserStatement");
        else soul::lexer::WriteFailureToLog(lexer, "ParserStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::LexerStatement(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LexerStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920196);
    std::unique_ptr<soul::ast::cpp::TypeIdNode> lexerTypeId;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::expected<soul::parser::Match, int> m = soul::common::common::parser::CommonParser<LexerT>::LexerKeyword(lexer);
            if (!m) return std::unexpected<int>(m.error());
            soul::parser::Match match = *m;
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::expected<soul::parser::Match, int> m = soul::cpp::declarator::parser::DeclaratorParser<LexerT>::TypeId(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                lexerTypeId.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch3 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == soul::punctuation::token::SEMICOLON)
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LexerStatement");
        else soul::lexer::WriteFailureToLog(lexer, "LexerStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::MainStatement(LexerT& lexer, soul::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MainStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920197);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == soul::tool::token::MAIN)
        {
            auto a = ++lexer;
            if (!a) return std::unexpected<int>(a.error());
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
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == soul::punctuation::token::SEMICOLON)
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MainStatement");
        else soul::lexer::WriteFailureToLog(lexer, "MainStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::UsingStatement(LexerT& lexer, soul::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UsingStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920198);
    std::unique_ptr<soul::parser::Value<std::string>> parserRuleId;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
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
                    if (*lexer == soul::cpp::token::USING)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::expected<soul::parser::Match, int> m = soul::common::common::parser::CommonParser<LexerT>::QualifiedId(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        parserRuleId.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
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
                    if (*lexer == soul::punctuation::token::SEMICOLON)
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UsingStatement");
        else soul::lexer::WriteFailureToLog(lexer, "UsingStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::RuleStatement(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::spg::GrammarParser* parser)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RuleStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920199);
    std::unique_ptr<soul::ast::spg::RuleParser> rule = std::unique_ptr<soul::ast::spg::RuleParser>();
    std::unique_ptr<soul::ast::cpp::TypeIdNode> returnType;
    std::unique_ptr<soul::ast::spg::Parser> definition;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
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
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == soul::cpp::token::ID)
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
                                        rule.reset(new soul::ast::spg::RuleParser(*sp, *u));
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    soul::parser::Match match(true);
                                    std::int64_t save = lexer.GetPos();
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::ParametersAndVariables(lexer, context, rule.get());
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch10 = &match;
                            {
                                soul::parser::Match match(true);
                                std::int64_t save = lexer.GetPos();
                                soul::parser::Match* parentMatch11 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::ReturnType(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    returnType.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == soul::punctuation::token::PRODUCES)
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch13 = &match;
                    {
                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::RuleBody(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        definition.reset(static_cast<soul::ast::spg::Parser*>(match.value));
                        *parentMatch13 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch14 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == soul::punctuation::token::SEMICOLON)
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
            soul::ast::spg::RuleParser *rulePtr = rule.get();
            bool succeeded = parser->AddRule(rule.release());
            if (!succeeded)
            {
                return std::unexpected<int>(soul::spg::RuleNameNotUnique(lexer.FileName(), rulePtr));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleStatement");
        else soul::lexer::WriteFailureToLog(lexer, "RuleStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::ParametersAndVariables(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::spg::RuleParser* rule)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParametersAndVariables");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920200);
    std::unique_ptr<soul::ast::spg::ParamVar> paramOrVariable;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == soul::punctuation::token::LPAREN)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(true);
                std::int64_t save = lexer.GetPos();
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
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::ParamOrVariable(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                paramOrVariable.reset(static_cast<soul::ast::spg::ParamVar*>(match.value));
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    while (true)
                                    {
                                        std::int64_t save = lexer.GetPos();
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == soul::punctuation::token::COMMA)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                *parentMatch9 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch11 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::ParamOrVariable(lexer, context);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul::parser::Match match = *m;
                                                        paramOrVariable.reset(static_cast<soul::ast::spg::ParamVar*>(match.value));
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
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch12 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == soul::punctuation::token::RPAREN)
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParametersAndVariables");
        else soul::lexer::WriteFailureToLog(lexer, "ParametersAndVariables");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::ParamOrVariable(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParamOrVariable");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920201);
    std::unique_ptr<soul::ast::cpp::TypeIdNode> varType;
    std::unique_ptr<soul::parser::Value<std::string>> varName;
    std::unique_ptr<soul::ast::cpp::TypeIdNode> paramType;
    std::unique_ptr<soul::parser::Value<std::string>> paramName;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                if (*lexer == soul::tool::token::VAR)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::expected<soul::parser::Match, int> m = soul::cpp::declarator::parser::DeclaratorParser<LexerT>::TypeId(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    varType.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch5 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = soul::cpp::declarator::parser::DeclaratorParser<LexerT>::Declarator(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    varName.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParamOrVariable");
                            #endif
                            return soul::parser::Match(true, new soul::ast::spg::Variable(*sp, varType.release(), varName->value));
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch7 = &match;
                {
                    std::expected<soul::parser::Match, int> m = soul::cpp::declarator::parser::DeclaratorParser<LexerT>::TypeId(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    paramType.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
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
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul::parser::Match, int> m = soul::cpp::declarator::parser::DeclaratorParser<LexerT>::Declarator(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            paramName.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                auto sp = lexer.GetSourcePos(pos);
                                if (!sp) return std::unexpected<int>(sp.error());
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParamOrVariable");
                                    #endif
                                    return soul::parser::Match(true, new soul::ast::spg::Parameter(*sp, paramType.release(), paramName->value));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParamOrVariable");
        else soul::lexer::WriteFailureToLog(lexer, "ParamOrVariable");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::ReturnType(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ReturnType");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920202);
    std::unique_ptr<soul::ast::cpp::TypeIdNode> typeId;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == soul::punctuation::token::COLON)
        {
            auto a = ++lexer;
            if (!a) return std::unexpected<int>(a.error());
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
                std::int64_t pos = lexer.GetPos();
                std::expected<soul::parser::Match, int> m = soul::cpp::declarator::parser::DeclaratorParser<LexerT>::TypeId(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                typeId.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ReturnType");
                        #endif
                        return soul::parser::Match(true, typeId.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ReturnType");
        else soul::lexer::WriteFailureToLog(lexer, "ReturnType");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::RuleBody(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RuleBody");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920203);
    std::unique_ptr<soul::ast::spg::Parser> choice;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Choice(lexer, context);
        if (!m) return std::unexpected<int>(m.error());
        soul::parser::Match match = *m;
        choice.reset(static_cast<soul::ast::spg::Parser*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleBody");
                #endif
                return soul::parser::Match(true, choice.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleBody");
        else soul::lexer::WriteFailureToLog(lexer, "RuleBody");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Choice(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Choice");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920204);
    std::unique_ptr<soul::ast::spg::Parser> value = std::unique_ptr<soul::ast::spg::Parser>();
    std::unique_ptr<soul::ast::spg::Parser> left;
    std::unique_ptr<soul::ast::spg::Parser> right;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Sequence(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::spg::Parser*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == soul::punctuation::token::PIPE)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
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
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Sequence(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::spg::Parser*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    value.reset(new soul::ast::spg::ChoiceParser(*sp, value.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Choice");
                #endif
                return soul::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Choice");
        else soul::lexer::WriteFailureToLog(lexer, "Choice");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Sequence(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Sequence");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920205);
    std::unique_ptr<soul::ast::spg::Parser> value = std::unique_ptr<soul::ast::spg::Parser>();
    std::unique_ptr<soul::ast::spg::Parser> left;
    std::unique_ptr<soul::ast::spg::Parser> right;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Difference(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::spg::Parser*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Difference(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        right.reset(static_cast<soul::ast::spg::Parser*>(match.value));
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul::ast::spg::SequenceParser(*sp, value.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Sequence");
                #endif
                return soul::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Sequence");
        else soul::lexer::WriteFailureToLog(lexer, "Sequence");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Difference(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Difference");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920206);
    std::unique_ptr<soul::ast::spg::Parser> value = std::unique_ptr<soul::ast::spg::Parser>();
    std::unique_ptr<soul::ast::spg::Parser> left;
    std::unique_ptr<soul::ast::spg::Parser> right;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::List(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::spg::Parser*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == soul::cpp::op::token::MINUS)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
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
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::List(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::spg::Parser*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    value.reset(new soul::ast::spg::DifferenceParser(*sp, value.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Difference");
                #endif
                return soul::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Difference");
        else soul::lexer::WriteFailureToLog(lexer, "Difference");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::List(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "List");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920207);
    std::unique_ptr<soul::ast::spg::Parser> value = std::unique_ptr<soul::ast::spg::Parser>();
    std::unique_ptr<soul::ast::spg::Parser> left;
    std::unique_ptr<soul::ast::spg::Parser> right;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Prefix(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::spg::Parser*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == soul::cpp::op::token::REM)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
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
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Prefix(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        right.reset(static_cast<soul::ast::spg::Parser*>(match.value));
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul::ast::spg::ListParser(*sp, value.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "List");
                #endif
                return soul::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "List");
        else soul::lexer::WriteFailureToLog(lexer, "List");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Prefix(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Prefix");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920208);
    std::unique_ptr<soul::ast::spg::Parser> lookaheadp;
    std::unique_ptr<soul::ast::spg::Parser> postfix;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case soul::punctuation::token::AMP:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                soul::parser::Match match(false);
                if (*lexer == soul::punctuation::token::AMP)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
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
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Postfix(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        lookaheadp.reset(static_cast<soul::ast::spg::Parser*>(match.value));
                        if (match.hit)
                        {
                            auto sp = lexer.GetSourcePos(pos);
                            if (!sp) return std::unexpected<int>(sp.error());
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Prefix");
                                #endif
                                return soul::parser::Match(true, new soul::ast::spg::LookaheadParser(*sp, lookaheadp.release()));
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
        case soul::punctuation::token::LPAREN:
        case soul::tool::token::EMPTY:
        case soul::tool::token::ANY:
        case soul::cpp::token::ID:
        case soul::cpp::token::CHAR_LITERAL:
        case soul::cpp::token::STRING_LITERAL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Postfix(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                postfix.reset(static_cast<soul::ast::spg::Parser*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Prefix");
                        #endif
                        return soul::parser::Match(true, postfix.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Prefix");
        else soul::lexer::WriteFailureToLog(lexer, "Prefix");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Postfix(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Postfix");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920209);
    std::unique_ptr<soul::ast::spg::Parser> value = std::unique_ptr<soul::ast::spg::Parser>();
    std::unique_ptr<soul::ast::spg::Parser> primary;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Primary(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    primary.reset(static_cast<soul::ast::spg::Parser*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            switch (*lexer)
                            {
                                case soul::cpp::op::token::STAR:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == soul::cpp::op::token::STAR)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul::ast::spg::KleeneParser(*sp, value.release()));
                                        }
                                        *parentMatch8 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch7 = match;
                                    }
                                    break;
                                }
                                case soul::cpp::op::token::PLUS:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == soul::cpp::op::token::PLUS)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul::ast::spg::PositiveParser(*sp, value.release()));
                                        }
                                        *parentMatch9 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch7 = match;
                                    }
                                    break;
                                }
                                case soul::punctuation::token::QUEST:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch10 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == soul::punctuation::token::QUEST)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            value.reset(new soul::ast::spg::OptionalParser(*sp, value.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Postfix");
                #endif
                return soul::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Postfix");
        else soul::lexer::WriteFailureToLog(lexer, "Postfix");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Primary(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Primary");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920210);
    std::unique_ptr<soul::ast::spg::Parser> value = std::unique_ptr<soul::ast::spg::Parser>();
    std::unique_ptr<soul::ast::spg::Parser> ruleCall;
    std::unique_ptr<soul::ast::spg::Parser> primitive;
    std::unique_ptr<soul::ast::spg::Parser> group;
    std::unique_ptr<soul::ast::cpp::CompoundStatementNode> successCode;
    std::unique_ptr<soul::ast::cpp::CompoundStatementNode> failureCode;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
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
                        switch (*lexer)
                        {
                            case soul::tool::token::EMPTY:
                            case soul::tool::token::ANY:
                            case soul::cpp::token::ID:
                            case soul::cpp::token::CHAR_LITERAL:
                            case soul::cpp::token::STRING_LITERAL:
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    std::int64_t save = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::RuleCall(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        ruleCall.reset(static_cast<soul::ast::spg::Parser*>(match.value));
                                        if (match.hit)
                                        {
                                            value.reset(ruleCall.release());
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
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Primitive(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                primitive.reset(static_cast<soul::ast::spg::Parser*>(match.value));
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
                            case soul::punctuation::token::LPAREN:
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Grouping(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    group.reset(static_cast<soul::ast::spg::Parser*>(match.value));
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch11 = &match;
                    {
                        soul::parser::Match match(true);
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch13 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch14 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == soul::punctuation::token::EXCLAMATION)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        value.reset(new soul::ast::spg::ExpectationParser(*sp, value.release()));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch15 = &match;
                {
                    soul::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch16 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch17 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch18 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch19 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch20 = &match;
                                    {
                                        std::expected<soul::parser::Match, int> m = soul::cpp::statement::parser::StatementParser<LexerT>::CompoundStatement(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        successCode.reset(static_cast<soul::ast::cpp::CompoundStatementNode*>(match.value));
                                        *parentMatch20 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch21 = &match;
                                        {
                                            soul::parser::Match match(true);
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match* parentMatch22 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch23 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch24 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        if (*lexer == soul::cpp::op::token::DIV)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        *parentMatch24 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch25 = &match;
                                                        {
                                                            std::expected<soul::parser::Match, int> m = soul::cpp::statement::parser::StatementParser<LexerT>::CompoundStatement(lexer, context);
                                                            if (!m) return std::unexpected<int>(m.error());
                                                            soul::parser::Match match = *m;
                                                            failureCode.reset(static_cast<soul::ast::cpp::CompoundStatementNode*>(match.value));
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
                                    value.reset(new soul::ast::spg::ActionParser(*sp, value.release(), successCode.release(), failureCode.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primary");
                #endif
                return soul::parser::Match(true, value.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primary");
        else soul::lexer::WriteFailureToLog(lexer, "Primary");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::RuleCall(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RuleCall");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920211);
    std::string ruleName = std::string();
    std::int64_t nonterminalPos = std::int64_t();
    std::unique_ptr<soul::ast::cpp::ExprListNode> args = std::unique_ptr<soul::ast::cpp::ExprListNode>();
    std::unique_ptr<soul::parser::Value<std::string>> nt;
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
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Nonterminal(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        nt.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        soul::parser::Match match(true);
                        std::int64_t save = lexer.GetPos();
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
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            bool pass = true;
                                            soul::parser::Match match(false);
                                            if (*lexer == soul::punctuation::token::LPAREN)
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
                                                pass = soul::lexer::NoWhiteSpaceBetweenTokens(**t2, **t1);
                                                auto sp = lexer.GetSourcePos(pos);
                                                if (!sp) return std::unexpected<int>(sp.error());
                                                args.reset(new soul::ast::cpp::ExprListNode(*sp));
                                            }
                                            if (match.hit && !pass)
                                            {
                                                match = soul::parser::Match(false);
                                            }
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch11 = &match;
                                        {
                                            std::expected<soul::parser::Match, int> m = soul::cpp::expression::parser::ExpressionParser<LexerT>::ExpressionList(lexer, context, args.get());
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            *parentMatch11 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch12 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == soul::punctuation::token::RPAREN)
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch13 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == soul::punctuation::token::COLON)
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch14 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch15 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == soul::cpp::token::ID)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleCall");
                            #endif
                            return soul::parser::Match(true, new soul::ast::spg::NonterminalParser(*sp, ruleName, instanceName, args.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RuleCall");
        else soul::lexer::WriteFailureToLog(lexer, "RuleCall");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Nonterminal(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Nonterminal");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920212);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == soul::cpp::token::ID)
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Nonterminal");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<std::string>(*u));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Nonterminal");
        else soul::lexer::WriteFailureToLog(lexer, "Nonterminal");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Primitive(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Primitive");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920213);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case soul::tool::token::EMPTY:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch2 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == soul::tool::token::EMPTY)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul::parser::Match(true, new soul::ast::spg::EmptyParser(*sp));
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
            case soul::tool::token::ANY:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == soul::tool::token::ANY)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul::parser::Match(true, new soul::ast::spg::AnyParser(*sp));
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
            case soul::cpp::token::ID:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == soul::cpp::token::ID)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul::parser::Match(true, new soul::ast::spg::TokenParser(*sp, *u));
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
            case soul::cpp::token::CHAR_LITERAL:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch5 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == soul::cpp::token::CHAR_LITERAL)
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
                        auto cl = soul::common::token::parser::ParseCharLiteral(lexer.FileName(), *t);
                        if (!cl) return std::unexpected<int>(cl.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul::parser::Match(true, new soul::ast::spg::CharParser(*sp, *cl));
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
            case soul::cpp::token::STRING_LITERAL:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == soul::cpp::token::STRING_LITERAL)
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
                        auto cs = soul::spg::token::parser::ParseStringLiteralOrCharSet(lexer.FileName(), *t, *sp);
                        if (!cs) return std::unexpected<int>(cs.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
                            #endif
                            return soul::parser::Match(true, *cs);
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primitive");
        else soul::lexer::WriteFailureToLog(lexer, "Primitive");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ParserFileParser<LexerT>::Grouping(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Grouping");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 6146011665574920214);
    std::unique_ptr<soul::ast::spg::Parser> choice;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
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
                    if (*lexer == soul::punctuation::token::LPAREN)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::expected<soul::parser::Match, int> m = soul::spg::parser::file::parser::ParserFileParser<LexerT>::Choice(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        choice.reset(static_cast<soul::ast::spg::Parser*>(match.value));
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
                    if (*lexer == soul::punctuation::token::RPAREN)
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Grouping");
                #endif
                return soul::parser::Match(true, new soul::ast::spg::GroupParser(*sp, choice.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Grouping");
        else soul::lexer::WriteFailureToLog(lexer, "Grouping");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct ParserFileParser<soul::lexer::Lexer<soul::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul::spg::parser::file::parser
