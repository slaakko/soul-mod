
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/cpp_expected/literal.parser' using soul parser generator espg version 5.0.0

module soul_expected.cpp.literal.parser;

import util_expected;
import soul_expected.ast.spg;
import soul_expected.cpp.token;
import soul_expected.cpp.op.token;
import soul_expected.tool.token;
import soul_expected.punctuation.token;
import soul_expected.lex.slg;
import soul_expected.lex.spg;

using namespace soul_expected::cpp::token;
using namespace soul_expected::cpp::op::token;
using namespace soul_expected::tool::token;
using namespace soul_expected::punctuation::token;
using namespace soul_expected::lex::slg;
using namespace soul_expected::lex::spg;

namespace soul_expected::cpp::literal::parser {

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> LiteralParser<LexerT>::Literal(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Literal");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2217894173619519489);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t save = lexer.GetPos();
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t save = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t save = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t save = lexer.GetPos();
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
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    auto u = lexer.TokenToUtf8(pos);
                                    if (!u) return std::unexpected<int>(u.error());
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                                        #endif
                                        return soul_expected::parser::Match(true, new soul_expected::ast::cpp::LiteralNode(*sp, *u));
                                    }
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                            if (!match.hit)
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                lexer.SetPos(save);
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == FLOATING_LITERAL)
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
                                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                                                #endif
                                                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::LiteralNode(*sp, *u));
                                            }
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
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
                                    soul_expected::parser::Match match(false);
                                    if (*lexer == CHAR_LITERAL)
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
                                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                                            #endif
                                            return soul_expected::parser::Match(true, new soul_expected::ast::cpp::LiteralNode(*sp, *u));
                                        }
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch11 = &match;
                        lexer.SetPos(save);
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch12 = &match;
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
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    auto u = lexer.TokenToUtf8(pos);
                                    if (!u) return std::unexpected<int>(u.error());
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                                        #endif
                                        return soul_expected::parser::Match(true, new soul_expected::ast::cpp::LiteralNode(*sp, *u));
                                    }
                                }
                                *parentMatch12 = match;
                            }
                            *parentMatch11 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch13 = &match;
                    lexer.SetPos(save);
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch14 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            if (*lexer == TRUE)
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
                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                                    #endif
                                    return soul_expected::parser::Match(true, new soul_expected::ast::cpp::LiteralNode(*sp, *u));
                                }
                            }
                            *parentMatch14 = match;
                        }
                        *parentMatch13 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch15 = &match;
                lexer.SetPos(save);
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch16 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == FALSE)
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
                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                                #endif
                                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::LiteralNode(*sp, *u));
                            }
                        }
                        *parentMatch16 = match;
                    }
                    *parentMatch15 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch17 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch18 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == NULLPTR)
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
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::cpp::LiteralNode(*sp, *u));
                        }
                    }
                    *parentMatch18 = match;
                }
                *parentMatch17 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Literal");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct LiteralParser<soul_expected::lexer::Lexer<soul_expected::lex::slg::SlgLexer<char32_t>, char32_t>>;
template struct LiteralParser<soul_expected::lexer::Lexer<soul_expected::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul_expected::cpp::literal::parser
