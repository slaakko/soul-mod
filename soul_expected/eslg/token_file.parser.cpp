
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/eslg/token_file.parser' using soul parser generator espg version 5.0.0

module soul_expected.slg.token.file.parser;

import util_expected;
import soul_expected.ast.spg;
import soul_expected.cpp.token;
import soul_expected.cpp.op.token;
import soul_expected.punctuation.token;
import soul_expected.tool.token;
import soul_expected.common.common.parser;
import soul_expected.common.token.parser;
import soul_expected.lex.slg;

using namespace soul_expected::cpp::token;
using namespace soul_expected::cpp::op::token;
using namespace soul_expected::punctuation::token;
using namespace soul_expected::tool::token;
using namespace soul_expected::common::common::parser;
using namespace soul_expected::common::token::parser;
using namespace soul_expected::lex::slg;

namespace soul_expected::slg::token::file::parser {

template<typename LexerT>
std::expected<std::unique_ptr<soul_expected::ast::slg::TokenFile>, int> TokenFileParser<LexerT>::Parse(LexerT& lexer)
{
    std::unique_ptr<soul_expected::ast::slg::TokenFile> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    auto a = ++lexer;
    if (!a) return std::unexpected<int>(a.error());
    std::expected<soul_expected::parser::Match, int> m = TokenFileParser<LexerT>::TokenFile(lexer);
    if (!m) return std::unexpected<int>(m.error());
    soul_expected::parser::Match match = *m;
    value.reset(static_cast<soul_expected::ast::slg::TokenFile*>(match.value));
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
std::expected<soul_expected::parser::Match, int> TokenFileParser<LexerT>::TokenFile(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "TokenFile");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8683044195872538625);
    std::unique_ptr<soul_expected::ast::slg::TokenFile> tokenFile = std::unique_ptr<soul_expected::ast::slg::TokenFile>();
    std::unique_ptr<soul_expected::ast::slg::TokenCollection> tokenCollection = std::unique_ptr<soul_expected::ast::slg::TokenCollection>();
    std::unique_ptr<soul_expected::parser::Value<std::string>> tokenCollectionName;
    std::unique_ptr<soul_expected::ast::slg::Token> token;
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
                                std::int64_t pos = lexer.GetPos();
                                soul_expected::parser::Match match(false);
                                if (*lexer == TOKENS)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    tokenFile.reset(new soul_expected::ast::slg::TokenFile(lexer.FileName()));
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
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch8 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul_expected::parser::Match, int> m = CommonParser<LexerT>::QualifiedId(lexer);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    tokenCollectionName.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                    if (match.hit)
                                    {
                                        tokenCollection.reset(new soul_expected::ast::slg::TokenCollection(tokenCollectionName->value));
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch9 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == LBRACE)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch9 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
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
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch12 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch13 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch14 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = TokenFileParser<LexerT>::Token(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        token.reset(static_cast<soul_expected::ast::slg::Token*>(match.value));
                                        if (match.hit)
                                        {
                                            tokenCollection->AddToken(token.release());
                                        }
                                        *parentMatch14 = match;
                                    }
                                    *parentMatch13 = match;
                                }
                                if (match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch15 = &match;
                                    {
                                        soul_expected::parser::Match match(true);
                                        soul_expected::parser::Match* parentMatch16 = &match;
                                        {
                                            while (true)
                                            {
                                                std::int64_t save = lexer.GetPos();
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch17 = &match;
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        if (*lexer == COMMA)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        *parentMatch17 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch18 = &match;
                                                        {
                                                            soul_expected::parser::Match match(false);
                                                            soul_expected::parser::Match* parentMatch19 = &match;
                                                            {
                                                                std::int64_t pos = lexer.GetPos();
                                                                std::expected<soul_expected::parser::Match, int> m = TokenFileParser<LexerT>::Token(lexer);
                                                                if (!m) return std::unexpected<int>(m.error());
                                                                soul_expected::parser::Match match = *m;
                                                                token.reset(static_cast<soul_expected::ast::slg::Token*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    tokenCollection->AddToken(token.release());
                                                                }
                                                                *parentMatch19 = match;
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
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        *parentMatch15 = match;
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
                            }
                        }
                        *parentMatch10 = match;
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
            tokenFile->SetTokenCollection(tokenCollection.release());
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TokenFile");
                #endif
                return soul_expected::parser::Match(true, tokenFile.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TokenFile");
        else soul_expected::lexer::WriteFailureToLog(lexer, "TokenFile");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> TokenFileParser<LexerT>::Token(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Token");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8683044195872538626);
    std::string name = std::string();
    std::string info = std::string();
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
                            if (*lexer == LPAREN)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
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
                            if (*lexer == COMMA)
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
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch10 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            if (*lexer == STRING_LITERAL)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                auto rv = lexer.TokenToStringLiteral(pos);
                                if (!rv) return std::unexpected<int>(rv.error());
                                auto u = util::ToUtf8(*rv);
                                if (!u) return std::unexpected<int>(u.error());
                                info = *u;
                            }
                            *parentMatch10 = match;
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
                    if (*lexer == RPAREN)
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Token");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::ast::slg::Token(name, info));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Token");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Token");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct TokenFileParser<soul_expected::lexer::Lexer<soul_expected::lex::slg::SlgLexer<char32_t>, char32_t>>;

} // namespace soul_expected::slg::token::file::parser
