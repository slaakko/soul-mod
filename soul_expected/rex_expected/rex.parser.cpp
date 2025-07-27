
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/rex_expected/rex.parser' using soul parser generator espg version 5.0.0

module soul_expected.rex.parser;

import util_expected;
import soul_expected.ast.spg;
import soul_expected.rex.token;
import soul_expected.rex.lexer;
import soul_expected.rex.token.parser;
import soul_expected.rex.symbol;

using namespace soul_expected::rex::token;
using namespace soul_expected::rex::lexer;
using namespace soul_expected::rex::token::parser;
using namespace soul_expected::rex::symbol;

namespace soul_expected::rex::parser {

template<typename LexerT>
std::expected<soul_expected::rex::nfa::Nfa, int> RexParser<LexerT>::Parse(LexerT& lexer, soul_expected::rex::context::Context* context)
{
    std::unique_ptr<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    auto a = ++lexer;
    if (!a) return std::unexpected<int>(a.error());
    std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::RegularExpression(lexer, context);
    if (!m) return std::unexpected<int>(m.error());
    soul_expected::parser::Match match = *m;
    value.reset(static_cast<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>*>(match.value));
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
            return value->value;
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
    return value->value;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> RexParser<LexerT>::RegularExpression(LexerT& lexer, soul_expected::rex::context::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "RegularExpression");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1058390567207043073);
    std::unique_ptr<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>> alternative;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Alternative(lexer, context);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            alternative.reset(static_cast<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>*>(match.value));
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RegularExpression");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>(alternative->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RegularExpression");
        else soul_expected::lexer::WriteFailureToLog(lexer, "RegularExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> RexParser<LexerT>::Alternative(LexerT& lexer, soul_expected::rex::context::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Alternative");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1058390567207043074);
    soul_expected::rex::nfa::Nfa value = soul_expected::rex::nfa::Nfa();
    std::unique_ptr<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>> left;
    std::unique_ptr<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>> right;
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
                    std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Catenation(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>*>(match.value));
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
                                        if (*lexer == ALT)
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
                                                soul_expected::parser::Match match(true);
                                                soul_expected::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Catenation(lexer, context);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul_expected::parser::Match match = *m;
                                                    right.reset(static_cast<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        return lexer.ExpectationFailure(pos, "Catenation");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    value = soul_expected::rex::nfa::Alt(*context, value, right->value);
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Alternative");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Alternative");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Alternative");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> RexParser<LexerT>::Catenation(LexerT& lexer, soul_expected::rex::context::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Catenation");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1058390567207043075);
    soul_expected::rex::nfa::Nfa value = soul_expected::rex::nfa::Nfa();
    std::unique_ptr<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>> left;
    std::unique_ptr<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>> right;
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
                    std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Repetition(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>*>(match.value));
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
                                        std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Repetition(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        right.reset(static_cast<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>*>(match.value));
                                        if (match.hit)
                                        {
                                            value = soul_expected::rex::nfa::Cat(value, right->value);
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Catenation");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Catenation");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Catenation");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> RexParser<LexerT>::Repetition(LexerT& lexer, soul_expected::rex::context::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Repetition");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1058390567207043076);
    soul_expected::rex::nfa::Nfa value = soul_expected::rex::nfa::Nfa();
    std::unique_ptr<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>> left;
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
                    std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Primary(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>*>(match.value));
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
                                case STAR:
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == STAR)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            value = soul_expected::rex::nfa::Kleene(*context, value);
                                        }
                                        *parentMatch8 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch7 = match;
                                    }
                                    break;
                                }
                                case PLUS:
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch9 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == PLUS)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            value = soul_expected::rex::nfa::Pos(*context, value);
                                        }
                                        *parentMatch9 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch7 = match;
                                    }
                                    break;
                                }
                                case QUEST:
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch10 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == QUEST)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            value = soul_expected::rex::nfa::Opt(*context, value);
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Repetition");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>(value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Repetition");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Repetition");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> RexParser<LexerT>::Primary(LexerT& lexer, soul_expected::rex::context::Context* context)
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
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1058390567207043077);
    soul_expected::rex::nfa::Nfa value = soul_expected::rex::nfa::Nfa();
    std::unique_ptr<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>> alt;
    std::unique_ptr<soul_expected::rex::symbol::Class> cls;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            switch (*lexer)
            {
                case LPAREN:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch3 = &match;
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
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch5 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch6 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul_expected::parser::Match match(true);
                                    soul_expected::parser::Match* parentMatch7 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Alternative(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        alt.reset(static_cast<soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>*>(match.value));
                                        if (match.hit)
                                        {
                                            *parentMatch7 = match;
                                        }
                                        else
                                        {
                                            return lexer.ExpectationFailure(pos, "Alternative");
                                        }
                                    }
                                    if (match.hit)
                                    {
                                        value = alt->value;
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
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch8 = &match;
                        {
                            soul_expected::parser::Match match(true);
                            soul_expected::parser::Match* parentMatch9 = &match;
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
                                    *parentMatch9 = match;
                                }
                                else
                                {
                                    return lexer.ExpectationFailure(pos, lexer.GetTokenInfo(RPAREN));
                                }
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case ESCAPE:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch10 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == ESCAPE)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            auto t = lexer.GetToken(pos);
                            if (!t) return std::unexpected<int>(t.error());
                            auto token = *t;
                            auto esc = soul_expected::rex::token::parser::MakeEscapeValue(lexer.FileName(), token);
                            if (!esc) return std::unexpected<int>(esc.error());
                            value = soul_expected::rex::nfa::MakeNfa(*context, context->MakeChar(*esc));
                        }
                        *parentMatch10 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case INVERSE:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch11 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == INVERSE)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            value = soul_expected::rex::nfa::MakeNfa(*context, context->MakeChar('^'));
                        }
                        *parentMatch11 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case MINUS:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch12 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == MINUS)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            value = soul_expected::rex::nfa::MakeNfa(*context, context->MakeChar('-'));
                        }
                        *parentMatch12 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case CHAR:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch13 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == CHAR)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            auto t = lexer.GetToken(pos);
                            if (!t) return std::unexpected<int>(t.error());
                            auto token = *t;
                            value = soul_expected::rex::nfa::MakeNfa(*context, context->MakeChar(token->Chr()));
                        }
                        *parentMatch13 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case DOT:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch14 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == DOT)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            value = soul_expected::rex::nfa::MakeNfa(*context, context->MakeAny());
                        }
                        *parentMatch14 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case LBRACKET:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch15 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Class(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        cls.reset(static_cast<soul_expected::rex::symbol::Class*>(match.value));
                        if (match.hit)
                        {
                            value = soul_expected::rex::nfa::MakeNfa(*context, cls.release());
                        }
                        *parentMatch15 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Primary");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::rex::nfa::Nfa>(value));
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
std::expected<soul_expected::parser::Match, int> RexParser<LexerT>::Class(LexerT& lexer, soul_expected::rex::context::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Class");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1058390567207043078);
    soul_expected::rex::symbol::Class* cls = nullptr;
    std::unique_ptr<soul_expected::rex::symbol::Symbol> r;
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
                        soul_expected::parser::Match match(false);
                        if (*lexer == LBRACKET)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            cls = context->MakeClass();
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
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch6 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch7 = &match;
                            {
                                soul_expected::parser::Match match(true);
                                std::int64_t save = lexer.GetPos();
                                soul_expected::parser::Match* parentMatch8 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch9 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch10 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul_expected::parser::Match match(false);
                                            if (*lexer == INVERSE)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                cls->SetInverse();
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
                                    }
                                }
                                *parentMatch7 = match;
                            }
                            if (match.hit)
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch11 = &match;
                                {
                                    soul_expected::parser::Match match(true);
                                    soul_expected::parser::Match* parentMatch12 = &match;
                                    {
                                        while (true)
                                        {
                                            std::int64_t save = lexer.GetPos();
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch13 = &match;
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch14 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Range(lexer, context);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul_expected::parser::Match match = *m;
                                                        r.reset(static_cast<soul_expected::rex::symbol::Symbol*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            cls->AddSymbol(r.release());
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
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    *parentMatch11 = match;
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch6 = match;
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
                soul_expected::parser::Match* parentMatch15 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch16 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == RBRACKET)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            *parentMatch16 = match;
                        }
                        else
                        {
                            return lexer.ExpectationFailure(pos, lexer.GetTokenInfo(RBRACKET));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Class");
                #endif
                return soul_expected::parser::Match(true, cls);
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Class");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Class");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> RexParser<LexerT>::Range(LexerT& lexer, soul_expected::rex::context::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Range");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1058390567207043079);
    soul_expected::rex::symbol::Symbol* symbol = nullptr;
    std::unique_ptr<soul_expected::parser::Value<char32_t>> s;
    std::unique_ptr<soul_expected::parser::Value<char32_t>> e;
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
                std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Char(lexer);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                s.reset(static_cast<soul_expected::parser::Value<char32_t>*>(match.value));
                *parentMatch2 = match;
            }
            if (match.hit)
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
                            std::int64_t save = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                if (*lexer == MINUS)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                *parentMatch6 = match;
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
                                        std::expected<soul_expected::parser::Match, int> m = RexParser<LexerT>::Char(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        e.reset(static_cast<soul_expected::parser::Value<char32_t>*>(match.value));
                                        if (match.hit)
                                        {
                                            symbol = context->MakeRange(s->value, e->value);
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
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
                                            symbol = context->MakeChar(s->value);
                                        }
                                        *parentMatch10 = match;
                                    }
                                    *parentMatch9 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Range");
                #endif
                return soul_expected::parser::Match(true, symbol);
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Range");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Range");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> RexParser<LexerT>::Char(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Char");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1058390567207043080);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case LPAREN:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == LPAREN)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>('('));
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
        case RPAREN:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
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
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>(')'));
                    }
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case LBRACKET:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == LBRACKET)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>('['));
                    }
                }
                *parentMatch3 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case ALT:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == ALT)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>('|'));
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
        case STAR:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch5 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == STAR)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>('*'));
                    }
                }
                *parentMatch5 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case PLUS:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch6 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == PLUS)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>('+'));
                    }
                }
                *parentMatch6 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case QUEST:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch7 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == QUEST)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>('?'));
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
        case DOT:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch8 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == DOT)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>('.'));
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
        case ESCAPE:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch9 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == ESCAPE)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    auto t = lexer.GetToken(pos);
                    if (!t) return std::unexpected<int>(t.error());
                    auto token = *t;
                    auto esc = soul_expected::rex::token::parser::MakeEscapeValue(lexer.FileName(), token);
                    if (!esc) return std::unexpected<int>(esc.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>(*esc));
                    }
                }
                *parentMatch9 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case INVERSE:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch10 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == INVERSE)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>('^'));
                    }
                }
                *parentMatch10 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case MINUS:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch11 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == MINUS)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>('-'));
                    }
                }
                *parentMatch11 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case CHAR:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch12 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == CHAR)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    auto t = lexer.GetToken(pos);
                    if (!t) return std::unexpected<int>(t.error());
                    auto token = *t;
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<char32_t>(token->Chr()));
                    }
                }
                *parentMatch12 = match;
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Char");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Char");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct RexParser<soul_expected::lexer::Lexer<soul_expected::rex::lexer::RexLexer<char32_t>, char32_t>>;

} // namespace soul_expected::rex::parser
