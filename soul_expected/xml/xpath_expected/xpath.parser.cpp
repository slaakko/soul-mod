
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/xml/xpath_expected/xpath.parser' using soul parser generator espg version 5.0.0

module soul_expected.xml.xpath.parser;

import util_expected;
import soul_expected.ast.spg;
import soul_expected.xml.dom_expected;
import soul_expected.xml.xpath.lexer;
import soul_expected.xml.xpath.token;
import soul_expected.xml.xpath.token.parser;

namespace soul_expected::xml::xpath::parser {

template<typename LexerT>
std::expected<std::unique_ptr<soul_expected::xml::xpath::expr::Expr>, int> XPathParser<LexerT>::Parse(LexerT& lexer)
{
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    auto a = ++lexer;
    if (!a) return std::unexpected<int>(a.error());
    std::expected<soul_expected::parser::Match, int> m = XPathParser<LexerT>::Expr(lexer);
    if (!m) return std::unexpected<int>(m.error());
    soul_expected::parser::Match match = *m;
    value.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
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
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::Expr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Expr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732545);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> orExpr;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::OrExpr(lexer);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            orExpr.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Expr");
                #endif
                return soul_expected::parser::Match(true, orExpr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Expr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Expr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::OrExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "OrExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732546);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> left;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AndExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
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
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::OrKeyword(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
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
                                                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AndExpr(lexer);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul_expected::xml::xpath::expr::BinaryExpr(soul_expected::xml::xpath::expr::Operator::or_, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OrExpr");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OrExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "OrExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AndExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AndExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732547);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> left;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::EqualityExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
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
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AndKeyword(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
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
                                                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::EqualityExpr(lexer);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul_expected::xml::xpath::expr::BinaryExpr(soul_expected::xml::xpath::expr::Operator::and_, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AndExpr");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AndExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AndExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::EqualityExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "EqualityExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732548);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> left;
    std::unique_ptr<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>> op;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::RelationalExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
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
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::EqualityOp(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        op.reset(static_cast<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>*>(match.value));
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
                                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::RelationalExpr(lexer);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul_expected::parser::Match match = *m;
                                                    right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        return lexer.ExpectationFailure(pos, "RelationalExpr");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul_expected::xml::xpath::expr::BinaryExpr(op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityExpr");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "EqualityExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::RelationalExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "RelationalExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732549);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> left;
    std::unique_ptr<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>> op;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AdditiveExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
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
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::RelationalOp(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        op.reset(static_cast<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>*>(match.value));
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
                                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AdditiveExpr(lexer);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul_expected::parser::Match match = *m;
                                                    right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        return lexer.ExpectationFailure(pos, "AdditiveExpr");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul_expected::xml::xpath::expr::BinaryExpr(op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalExpr");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "RelationalExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AdditiveExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AdditiveExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732550);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> left;
    std::unique_ptr<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>> op;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::MultiplicativeExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
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
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AdditiveOp(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        op.reset(static_cast<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>*>(match.value));
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
                                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::MultiplicativeExpr(lexer);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul_expected::parser::Match match = *m;
                                                    right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        return lexer.ExpectationFailure(pos, "MultiplicativeExpr");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul_expected::xml::xpath::expr::BinaryExpr(op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveExpr");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AdditiveExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::MultiplicativeExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "MultiplicativeExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732551);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> left;
    std::unique_ptr<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>> op;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::UnaryExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
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
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::MultiplicativeOp(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        op.reset(static_cast<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>*>(match.value));
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
                                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::UnaryExpr(lexer);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul_expected::parser::Match match = *m;
                                                    right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        return lexer.ExpectationFailure(pos, "UnaryExpr");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul_expected::xml::xpath::expr::BinaryExpr(op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeExpr");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "MultiplicativeExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::UnaryExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "UnaryExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732552);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> subject;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> unionExpr;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            if (*lexer == soul_expected::xml::xpath::token::MINUS)
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::UnaryExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    subject.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpr");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::UnaryExpr(soul_expected::xml::xpath::expr::Operator::minus, subject.release()));
                        }
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch4 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch5 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::UnionExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    unionExpr.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpr");
                            #endif
                            return soul_expected::parser::Match(true, unionExpr.release());
                        }
                    }
                    *parentMatch5 = match;
                }
                *parentMatch4 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "UnaryExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::UnionExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "UnionExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732553);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> left;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::PathExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
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
                                        if (*lexer == soul_expected::xml::xpath::token::UNION)
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
                                                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::PathExpr(lexer);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul_expected::xml::xpath::expr::BinaryExpr(soul_expected::xml::xpath::expr::Operator::union_, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnionExpr");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnionExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "UnionExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::PathExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "PathExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732554);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> locationPath;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> functionCall;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> filterExpr;
    std::unique_ptr<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>> op;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    std::int64_t save = lexer.GetPos();
                    {
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::LocationPath(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        locationPath.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t tmp = lexer.GetPos();
                            lexer.SetPos(save);
                            save = tmp;
                            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::FunctionCall(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            functionCall.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                            *parentMatch5 = match;
                        }
                        if (!match.hit)
                        {
                            lexer.SetPos(save);
                        }
                        *parentMatch4 = soul_expected::parser::Match(!match.hit, match.value);
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PathExpr");
                        #endif
                        return soul_expected::parser::Match(true, locationPath.release());
                    }
                }
                *parentMatch2 = match;
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
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch8 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch9 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::FilterExpr(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            filterExpr.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                            if (match.hit)
                            {
                                expr.reset(filterExpr.release());
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
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch12 = &match;
                                {
                                    soul_expected::parser::Match match(true);
                                    std::int64_t save = lexer.GetPos();
                                    soul_expected::parser::Match* parentMatch13 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch14 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch15 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch16 = &match;
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch17 = &match;
                                                    {
                                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::CombinePathOp(lexer);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul_expected::parser::Match match = *m;
                                                        op.reset(static_cast<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>*>(match.value));
                                                        *parentMatch17 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch18 = &match;
                                                        {
                                                            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::RelativeLocationPath(lexer);
                                                            if (!m) return std::unexpected<int>(m.error());
                                                            soul_expected::parser::Match match = *m;
                                                            right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                            *parentMatch18 = match;
                                                        }
                                                        *parentMatch17 = match;
                                                    }
                                                    *parentMatch16 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    switch (op->value)
                                                    {
                                                        case soul_expected::xml::xpath::expr::Operator::slash: {
                                                            {
                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PathExpr");
                                                                #endif
                                                                return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::BinaryExpr(soul_expected::xml::xpath::expr::Operator::slash, expr.release(), right.release()));
                                                            }
                                                        }
                                                        case soul_expected::xml::xpath::expr::Operator::slashSlash: {
                                                            {
                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PathExpr");
                                                                #endif
                                                                return soul_expected::parser::Match(true, soul_expected::xml::xpath::expr::MakeSlashSlashExpr(expr.release(), right.release()));
                                                            }
                                                        }
                                                    }
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
                                        }
                                    }
                                    *parentMatch12 = match;
                                }
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PathExpr");
                                        #endif
                                        return soul_expected::parser::Match(true, expr.release());
                                    }
                                }
                                *parentMatch11 = match;
                            }
                            *parentMatch10 = match;
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PathExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "PathExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::LocationPath(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "LocationPath");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732555);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> absoluteLocationPath;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> relativeLocationPath;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AbsoluteLocationPath(lexer);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            absoluteLocationPath.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LocationPath");
                    #endif
                    return soul_expected::parser::Match(true, absoluteLocationPath.release());
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::RelativeLocationPath(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    relativeLocationPath.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LocationPath");
                            #endif
                            return soul_expected::parser::Match(true, relativeLocationPath.release());
                        }
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LocationPath");
        else soul_expected::lexer::WriteFailureToLog(lexer, "LocationPath");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AbsoluteLocationPath(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AbsoluteLocationPath");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732556);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> abbreviatedAbsoluteLocationPath;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                case soul_expected::xml::xpath::token::SLASH_SLASH:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch3 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AbbreviatedAbsoluteLocationPath(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        abbreviatedAbsoluteLocationPath.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                        if (match.hit)
                        {
                            expr.reset(abbreviatedAbsoluteLocationPath.release());
                        }
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case soul_expected::xml::xpath::token::SLASH:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::xml::xpath::token::SLASH)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                expr.reset(new soul_expected::xml::xpath::expr::Root);
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
                            soul_expected::parser::Match match(true);
                            std::int64_t save = lexer.GetPos();
                            soul_expected::parser::Match* parentMatch7 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch8 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch9 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::RelativeLocationPath(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                        if (match.hit)
                                        {
                                            expr.reset(new soul_expected::xml::xpath::expr::BinaryExpr(soul_expected::xml::xpath::expr::Operator::slash, expr.release(), right.release()));
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
                                }
                            }
                            *parentMatch6 = match;
                        }
                        *parentMatch4 = match;
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbsoluteLocationPath");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbsoluteLocationPath");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AbsoluteLocationPath");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AbbreviatedAbsoluteLocationPath(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AbbreviatedAbsoluteLocationPath");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732557);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::SLASH_SLASH)
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
                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::RelativeLocationPath(lexer);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbbreviatedAbsoluteLocationPath");
                        #endif
                        return soul_expected::parser::Match(true, soul_expected::xml::xpath::expr::MakeSlashSlashExpr(new soul_expected::xml::xpath::expr::Root, right.release()));
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbbreviatedAbsoluteLocationPath");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AbbreviatedAbsoluteLocationPath");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::RelativeLocationPath(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "RelativeLocationPath");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732558);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> left;
    std::unique_ptr<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>> op;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> right;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Step(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    left.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
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
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch8 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch9 = &match;
                                            {
                                                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::CombinePathOp(lexer);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                op.reset(static_cast<soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>*>(match.value));
                                                *parentMatch9 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Step(lexer);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul_expected::parser::Match match = *m;
                                                    right.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                    *parentMatch10 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                        if (match.hit)
                                        {
                                            switch (op->value)
                                            {
                                                case soul_expected::xml::xpath::expr::Operator::slash: {
                                                    expr.reset(new soul_expected::xml::xpath::expr::BinaryExpr(soul_expected::xml::xpath::expr::Operator::slash, expr.release(), right.release()));
                                                    break;
                                                }
                                                case soul_expected::xml::xpath::expr::Operator::slashSlash: {
                                                    expr.reset(soul_expected::xml::xpath::expr::MakeSlashSlashExpr(expr.release(), right.release()));
                                                    break;
                                                }
                                            }
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelativeLocationPath");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelativeLocationPath");
        else soul_expected::lexer::WriteFailureToLog(lexer, "RelativeLocationPath");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::Step(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Step");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732559);
    std::unique_ptr<soul_expected::xml::xpath::expr::LocationStepExpr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::LocationStepExpr>();
    std::unique_ptr<soul_expected::parser::Value<soul_expected::xml::Axis>> axis;
    std::unique_ptr<soul_expected::xml::xpath::expr::NodeTest> nodeTest;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> predicate;
    std::unique_ptr<soul_expected::xml::xpath::expr::LocationStepExpr> abbreviatedStep;
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
                std::int64_t save = lexer.GetPos();
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AxisSpecifier(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        axis.reset(static_cast<soul_expected::parser::Value<soul_expected::xml::Axis>*>(match.value));
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
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::NodeTest(lexer);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                nodeTest.reset(static_cast<soul_expected::xml::xpath::expr::NodeTest*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(new soul_expected::xml::xpath::expr::LocationStepExpr(axis->value, nodeTest.release()));
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
                                        soul_expected::parser::Match* parentMatch10 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Predicate(lexer);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul_expected::parser::Match match = *m;
                                            predicate.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                            if (match.hit)
                                            {
                                                expr->AddPredicate(predicate.release());
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
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AbbreviatedStep(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            abbreviatedStep.reset(static_cast<soul_expected::xml::xpath::expr::LocationStepExpr*>(match.value));
                            if (match.hit)
                            {
                                expr.reset(abbreviatedStep.release());
                            }
                            *parentMatch12 = match;
                        }
                        *parentMatch11 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Step");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Step");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Step");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AxisSpecifier(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AxisSpecifier");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732560);
    std::unique_ptr<soul_expected::parser::Value<soul_expected::xml::Axis>> axis;
    std::unique_ptr<soul_expected::parser::Value<soul_expected::xml::Axis>> abbreviatedAxisSpecifier;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AxisName(lexer);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            axis.reset(static_cast<soul_expected::parser::Value<soul_expected::xml::Axis>*>(match.value));
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
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::xml::xpath::token::COLON_COLON)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisSpecifier");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(axis->value));
                        }
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch4 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch5 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::AbbreviatedAxisSpecifier(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    abbreviatedAxisSpecifier.reset(static_cast<soul_expected::parser::Value<soul_expected::xml::Axis>*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisSpecifier");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(abbreviatedAxisSpecifier->value));
                        }
                    }
                    *parentMatch5 = match;
                }
                *parentMatch4 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisSpecifier");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AxisSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AxisName(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AxisName");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732561);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        bool pass = true;
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::NAME)
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
            switch (lexer.GetKeywordToken(token->match))
            {
                case soul_expected::xml::xpath::token::ANCESTOR: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::ancestor));
                    }
                }
                case soul_expected::xml::xpath::token::ANCESTOR_OR_SELF: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::ancestorOrSelf));
                    }
                }
                case soul_expected::xml::xpath::token::ATTRIBUTE: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::attribute));
                    }
                }
                case soul_expected::xml::xpath::token::CHILD: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::child));
                    }
                }
                case soul_expected::xml::xpath::token::DESCENDANT: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::descendant));
                    }
                }
                case soul_expected::xml::xpath::token::DESCENDANT_OR_SELF: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::descendantOrSelf));
                    }
                }
                case soul_expected::xml::xpath::token::FOLLOWING: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::following));
                    }
                }
                case soul_expected::xml::xpath::token::FOLLOWING_SIBLING: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::followingSibling));
                    }
                }
                case soul_expected::xml::xpath::token::NAMESPACE: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::ns));
                    }
                }
                case soul_expected::xml::xpath::token::PARENT: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::parent));
                    }
                }
                case soul_expected::xml::xpath::token::PRECEDING: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::preceding));
                    }
                }
                case soul_expected::xml::xpath::token::PRECEDING_SIBLING: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::precedingSibling));
                    }
                }
                case soul_expected::xml::xpath::token::SELF: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::self));
                    }
                }
                default: {
                    pass = false;
                    break;
                }
            }
        }
        if (match.hit && !pass)
        {
            match = soul_expected::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AxisName");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AxisName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AbbreviatedAxisSpecifier(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AbbreviatedAxisSpecifier");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732562);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul_expected::parser::Match match(false);
            if (*lexer == soul_expected::xml::xpath::token::AT)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbbreviatedAxisSpecifier");
                    #endif
                    return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::attribute));
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(true);
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbbreviatedAxisSpecifier");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::Axis>(soul_expected::xml::Axis::child));
                        }
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbbreviatedAxisSpecifier");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AbbreviatedAxisSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::NodeTest(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "NodeTest");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732563);
    std::unique_ptr<soul_expected::xml::xpath::expr::Literal> pi;
    std::unique_ptr<soul_expected::xml::xpath::expr::NodeTest> nodeType;
    std::unique_ptr<soul_expected::xml::xpath::expr::NodeTest> nameTest;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
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
                    std::int64_t pos = lexer.GetPos();
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
                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::ProcessingInstructionKeyword(lexer);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::xml::xpath::token::LPAREN)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch9 = &match;
                                {
                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Literal(lexer);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    pi.reset(static_cast<soul_expected::xml::xpath::expr::Literal*>(match.value));
                                    *parentMatch9 = match;
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
                                soul_expected::parser::Match match(false);
                                if (*lexer == soul_expected::xml::xpath::token::RPAREN)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                *parentMatch10 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NodeTest");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::PILiteralNodeTest(pi.release()));
                        }
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                            soul_expected::parser::Match* parentMatch13 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch14 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch15 = &match;
                                    {
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::NodeType(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        nodeType.reset(static_cast<soul_expected::xml::xpath::expr::NodeTest*>(match.value));
                                        *parentMatch15 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch16 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            if (*lexer == soul_expected::xml::xpath::token::LPAREN)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            *parentMatch16 = match;
                                        }
                                        *parentMatch15 = match;
                                    }
                                    *parentMatch14 = match;
                                }
                                if (match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch17 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::xml::xpath::token::RPAREN)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch17 = match;
                                    }
                                    *parentMatch14 = match;
                                }
                                *parentMatch13 = match;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NodeTest");
                                    #endif
                                    return soul_expected::parser::Match(true, nodeType.release());
                                }
                            }
                            *parentMatch12 = match;
                        }
                        *parentMatch11 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch18 = &match;
                lexer.SetPos(save);
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch19 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch20 = &match;
                        {
                            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::NameTest(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            nameTest.reset(static_cast<soul_expected::xml::xpath::expr::NodeTest*>(match.value));
                            *parentMatch20 = match;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NodeTest");
                                #endif
                                return soul_expected::parser::Match(true, nameTest.release());
                            }
                        }
                        *parentMatch19 = match;
                    }
                    *parentMatch18 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NodeTest");
        else soul_expected::lexer::WriteFailureToLog(lexer, "NodeTest");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::Literal(LexerT& lexer)
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
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732564);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case soul_expected::xml::xpath::token::DQ_STRING:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::DQ_STRING)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    auto t = lexer.GetToken(pos);
                    if (!t) return std::unexpected<int>(t.error());
                    auto s = soul_expected::xml::xpath::token::parser::ParseDQString(lexer.FileName(), *t);
                    if (!s) return std::unexpected<int>(s.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::Literal(*s));
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
        case soul_expected::xml::xpath::token::SQ_STRING:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::SQ_STRING)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    auto t = lexer.GetToken(pos);
                    if (!t) return std::unexpected<int>(t.error());
                    auto s = soul_expected::xml::xpath::token::parser::ParseSQString(lexer.FileName(), *t);
                    if (!s) return std::unexpected<int>(s.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::Literal(*s));
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

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::NodeType(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "NodeType");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732565);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        bool pass = true;
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::NAME)
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
            switch (lexer.GetKeywordToken(token->match))
            {
                case soul_expected::xml::xpath::token::COMMENT: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NodeType");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::NodeTest(soul_expected::xml::xpath::expr::NodeTestKind::commentNodeTest));
                    }
                }
                case soul_expected::xml::xpath::token::TEXT: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NodeType");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::NodeTest(soul_expected::xml::xpath::expr::NodeTestKind::textNodeTest));
                    }
                }
                case soul_expected::xml::xpath::token::PROCESSING_INSTRUCTION: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NodeType");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::NodeTest(soul_expected::xml::xpath::expr::NodeTestKind::piNodeTest));
                    }
                }
                case soul_expected::xml::xpath::token::NODE: {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NodeType");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::NodeTest(soul_expected::xml::xpath::expr::NodeTestKind::anyNodeTest));
                    }
                }
                default: {
                    pass = false;
                    break;
                }
            }
        }
        if (match.hit && !pass)
        {
            match = soul_expected::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NodeType");
        else soul_expected::lexer::WriteFailureToLog(lexer, "NodeType");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::NameTest(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "NameTest");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732566);
    std::unique_ptr<soul_expected::parser::Value<std::string>> ncname;
    std::unique_ptr<soul_expected::parser::Value<std::string>> qname;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case soul_expected::xml::xpath::token::STAR:
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch2 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::xml::xpath::token::STAR)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NameTest");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::NodeTest(soul_expected::xml::xpath::expr::NodeTestKind::principalNodeTest));
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
            case soul_expected::xml::xpath::token::NAME:
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::NCName(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        ncname.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::xml::xpath::token::COLON)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
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
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch6 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch7 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::xml::xpath::token::STAR)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NameTest");
                                    #endif
                                    return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::PrefixNodeTest(ncname->value));
                                }
                            }
                            *parentMatch7 = match;
                        }
                        *parentMatch6 = match;
                    }
                    *parentMatch3 = match;
                }
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
            soul_expected::parser::Match* parentMatch8 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch9 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::QName(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    qname.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NameTest");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::NameNodeTest(qname->value));
                        }
                    }
                    *parentMatch9 = match;
                }
                *parentMatch8 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NameTest");
        else soul_expected::lexer::WriteFailureToLog(lexer, "NameTest");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::NCName(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "NCName");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732567);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::NAME)
        {
            auto a = ++lexer;
            if (!a) return std::unexpected<int>(a.error());
            match.hit = true;
        }
        if (match.hit)
        {
            auto u = lexer.TokenToUtf8(pos);
            if (!u) return std::unexpected<int>(u.error());
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NCName");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(*u));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NCName");
        else soul_expected::lexer::WriteFailureToLog(lexer, "NCName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::QName(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "QName");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732568);
    std::unique_ptr<soul_expected::parser::Value<std::string>> prefixedName;
    std::unique_ptr<soul_expected::parser::Value<std::string>> unprefixedName;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::PrefixedName(lexer);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            prefixedName.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "QName");
                    #endif
                    return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(prefixedName->value));
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::UnprefixedName(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    unprefixedName.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "QName");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(unprefixedName->value));
                        }
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "QName");
        else soul_expected::lexer::WriteFailureToLog(lexer, "QName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::PrefixedName(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "PrefixedName");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732569);
    std::unique_ptr<soul_expected::parser::Value<std::string>> prefix;
    std::unique_ptr<soul_expected::parser::Value<std::string>> localPart;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Prefix(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    prefix.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        if (*lexer == soul_expected::xml::xpath::token::COLON)
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::LocalPart(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    localPart.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                    *parentMatch5 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrefixedName");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(prefix->value + ":" + localPart->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrefixedName");
        else soul_expected::lexer::WriteFailureToLog(lexer, "PrefixedName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::Prefix(LexerT& lexer)
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
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732570);
    std::unique_ptr<soul_expected::parser::Value<std::string>> ncname;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::NCName(lexer);
        if (!m) return std::unexpected<int>(m.error());
        soul_expected::parser::Match match = *m;
        ncname.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Prefix");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(ncname->value));
            }
        }
        *parentMatch0 = match;
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
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::UnprefixedName(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "UnprefixedName");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732571);
    std::unique_ptr<soul_expected::parser::Value<std::string>> localPart;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::LocalPart(lexer);
        if (!m) return std::unexpected<int>(m.error());
        soul_expected::parser::Match match = *m;
        localPart.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnprefixedName");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(localPart->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnprefixedName");
        else soul_expected::lexer::WriteFailureToLog(lexer, "UnprefixedName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::LocalPart(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "LocalPart");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732572);
    std::unique_ptr<soul_expected::parser::Value<std::string>> ncname;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::NCName(lexer);
        if (!m) return std::unexpected<int>(m.error());
        soul_expected::parser::Match match = *m;
        ncname.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LocalPart");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(ncname->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LocalPart");
        else soul_expected::lexer::WriteFailureToLog(lexer, "LocalPart");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::Predicate(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Predicate");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732573);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr;
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
                    if (*lexer == soul_expected::xml::xpath::token::LBRACKET)
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
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Expr(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        expr.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
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
                    if (*lexer == soul_expected::xml::xpath::token::RBRACKET)
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
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Predicate");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Predicate");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Predicate");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AbbreviatedStep(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AbbreviatedStep");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732574);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case soul_expected::xml::xpath::token::DOT_DOT:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::DOT_DOT)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbbreviatedStep");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::LocationStepExpr(soul_expected::xml::Axis::parent, new soul_expected::xml::xpath::expr::NodeTest(soul_expected::xml::xpath::expr::NodeTestKind::anyNodeTest)));
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
        case soul_expected::xml::xpath::token::DOT:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::DOT)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbbreviatedStep");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::LocationStepExpr(soul_expected::xml::Axis::self, new soul_expected::xml::xpath::expr::NodeTest(soul_expected::xml::xpath::expr::NodeTestKind::anyNodeTest)));
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbbreviatedStep");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AbbreviatedStep");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::FunctionCall(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "FunctionCall");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732575);
    std::unique_ptr<soul_expected::xml::xpath::expr::FunctionCall> functionCall = std::unique_ptr<soul_expected::xml::xpath::expr::FunctionCall>();
    std::unique_ptr<soul_expected::parser::Value<std::string>> functionName;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> arg;
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
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::FunctionName(lexer);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        functionName.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
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
                                soul_expected::parser::Match match(false);
                                if (*lexer == soul_expected::xml::xpath::token::LPAREN)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    functionCall.reset(new soul_expected::xml::xpath::expr::FunctionCall(functionName->value));
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
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch11 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Argument(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        arg.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                        if (match.hit)
                                        {
                                            functionCall->AddArgument(arg.release());
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch10 = match;
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
                                                        if (*lexer == soul_expected::xml::xpath::token::COMMA)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        *parentMatch14 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch15 = &match;
                                                        {
                                                            soul_expected::parser::Match match(false);
                                                            soul_expected::parser::Match* parentMatch16 = &match;
                                                            {
                                                                std::int64_t pos = lexer.GetPos();
                                                                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Argument(lexer);
                                                                if (!m) return std::unexpected<int>(m.error());
                                                                soul_expected::parser::Match match = *m;
                                                                arg.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    functionCall->AddArgument(arg.release());
                                                                }
                                                                *parentMatch16 = match;
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
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch17 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::xml::xpath::token::RPAREN)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch17 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionCall");
                #endif
                return soul_expected::parser::Match(true, functionCall.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionCall");
        else soul_expected::lexer::WriteFailureToLog(lexer, "FunctionCall");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::FunctionName(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "FunctionName");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732576);
    std::unique_ptr<soul_expected::parser::Value<std::string>> qname;
    std::unique_ptr<soul_expected::xml::xpath::expr::NodeTest> nodeType;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            std::int64_t save = lexer.GetPos();
            {
                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::QName(lexer);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                qname.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t tmp = lexer.GetPos();
                    lexer.SetPos(save);
                    save = tmp;
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::NodeType(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    nodeType.reset(static_cast<soul_expected::xml::xpath::expr::NodeTest*>(match.value));
                    *parentMatch3 = match;
                }
                if (!match.hit)
                {
                    lexer.SetPos(save);
                }
                *parentMatch2 = soul_expected::parser::Match(!match.hit, match.value);
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionName");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(qname->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionName");
        else soul_expected::lexer::WriteFailureToLog(lexer, "FunctionName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::Argument(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Argument");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732577);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Expr(lexer);
        if (!m) return std::unexpected<int>(m.error());
        soul_expected::parser::Match match = *m;
        expr.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Argument");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Argument");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Argument");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::FilterExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "FilterExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732578);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::unique_ptr<soul_expected::xml::xpath::expr::Expr>();
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> primaryExpr;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> predicate;
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::PrimaryExpr(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    primaryExpr.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(primaryExpr.release());
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
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Predicate(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        predicate.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                        if (match.hit)
                                        {
                                            expr.reset(new soul_expected::xml::xpath::expr::FilterExpr(expr.release(), predicate.release()));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FilterExpr");
                #endif
                return soul_expected::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FilterExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "FilterExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::PrimaryExpr(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "PrimaryExpr");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732579);
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> functionCall;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> variableReference;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr;
    std::unique_ptr<soul_expected::xml::xpath::expr::Literal> literal;
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> number;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case soul_expected::xml::xpath::token::NAME:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::FunctionCall(lexer);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                functionCall.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
                        #endif
                        return soul_expected::parser::Match(true, functionCall.release());
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
        case soul_expected::xml::xpath::token::DOLLAR:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::VariableReference(lexer);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                variableReference.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
                        #endif
                        return soul_expected::parser::Match(true, variableReference.release());
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
        case soul_expected::xml::xpath::token::LPAREN:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                            if (*lexer == soul_expected::xml::xpath::token::LPAREN)
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
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Expr(lexer);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                expr.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                                *parentMatch7 = match;
                            }
                            *parentMatch6 = match;
                        }
                        *parentMatch5 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch8 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::xml::xpath::token::RPAREN)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch5 = match;
                    }
                    *parentMatch4 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::UnaryExpr(soul_expected::xml::xpath::expr::Operator::parens, expr.release()));
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
        case soul_expected::xml::xpath::token::DQ_STRING:
        case soul_expected::xml::xpath::token::SQ_STRING:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch9 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Literal(lexer);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                literal.reset(static_cast<soul_expected::xml::xpath::expr::Literal*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
                        #endif
                        return soul_expected::parser::Match(true, literal.release());
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
        case soul_expected::xml::xpath::token::NUMBER:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch10 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::Number(lexer);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                number.reset(static_cast<soul_expected::xml::xpath::expr::Expr*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
                        #endif
                        return soul_expected::parser::Match(true, number.release());
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpr");
        else soul_expected::lexer::WriteFailureToLog(lexer, "PrimaryExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::VariableReference(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "VariableReference");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732580);
    std::unique_ptr<soul_expected::parser::Value<std::string>> qname;
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
                if (*lexer == soul_expected::xml::xpath::token::DOLLAR)
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
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::QName(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    qname.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VariableReference");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::VariableReference(qname->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VariableReference");
        else soul_expected::lexer::WriteFailureToLog(lexer, "VariableReference");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::Number(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Number");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732581);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::NUMBER)
        {
            auto a = ++lexer;
            if (!a) return std::unexpected<int>(a.error());
            match.hit = true;
        }
        if (match.hit)
        {
            auto d = lexer.TokenToDouble(pos);
            if (!d) return std::unexpected<int>(d.error());
            double number = *d;
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Number");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::xml::xpath::expr::NumberExpr(number));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Number");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Number");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::EqualityOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "EqualityOp");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732582);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case soul_expected::xml::xpath::token::EQ:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::EQ)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::equal));
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
        case soul_expected::xml::xpath::token::NEQ:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::NEQ)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::notEqual));
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityOp");
        else soul_expected::lexer::WriteFailureToLog(lexer, "EqualityOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::RelationalOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "RelationalOp");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732583);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case soul_expected::xml::xpath::token::LESS:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::LESS)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::less));
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
        case soul_expected::xml::xpath::token::GREATER:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::GREATER)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::greater));
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
        case soul_expected::xml::xpath::token::LEQ:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::LEQ)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::lessOrEqual));
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
        case soul_expected::xml::xpath::token::GEQ:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::GEQ)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::greaterOrEqual));
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
        else soul_expected::lexer::WriteFailureToLog(lexer, "RelationalOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AdditiveOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AdditiveOp");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732584);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case soul_expected::xml::xpath::token::PLUS:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::PLUS)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::plus));
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
        case soul_expected::xml::xpath::token::MINUS:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::MINUS)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::minus));
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveOp");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AdditiveOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::MultiplicativeOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "MultiplicativeOp");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732585);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case soul_expected::xml::xpath::token::STAR:
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch2 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == soul_expected::xml::xpath::token::STAR)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeOp");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::mul));
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
            case soul_expected::xml::xpath::token::NAME:
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::DivKeyword(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeOp");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::div));
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
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch4 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch5 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::xml::xpath::parser::XPathParser<LexerT>::ModKeyword(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeOp");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::mod));
                        }
                    }
                    *parentMatch5 = match;
                }
                *parentMatch4 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeOp");
        else soul_expected::lexer::WriteFailureToLog(lexer, "MultiplicativeOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::CombinePathOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "CombinePathOp");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732586);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case soul_expected::xml::xpath::token::SLASH:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::SLASH)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CombinePathOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::slash));
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
        case soul_expected::xml::xpath::token::SLASH_SLASH:
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                if (*lexer == soul_expected::xml::xpath::token::SLASH_SLASH)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CombinePathOp");
                        #endif
                        return soul_expected::parser::Match(true, new soul_expected::parser::Value<soul_expected::xml::xpath::expr::Operator>(soul_expected::xml::xpath::expr::Operator::slashSlash));
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CombinePathOp");
        else soul_expected::lexer::WriteFailureToLog(lexer, "CombinePathOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::OrKeyword(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "OrKeyword");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732587);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        bool pass = true;
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::NAME)
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
            pass = lexer.GetKeywordToken(token->match) == soul_expected::xml::xpath::token::OR;
        }
        if (match.hit && !pass)
        {
            match = soul_expected::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OrKeyword");
        else soul_expected::lexer::WriteFailureToLog(lexer, "OrKeyword");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::AndKeyword(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AndKeyword");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732588);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        bool pass = true;
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::NAME)
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
            pass = lexer.GetKeywordToken(token->match) == soul_expected::xml::xpath::token::AND;
        }
        if (match.hit && !pass)
        {
            match = soul_expected::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AndKeyword");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AndKeyword");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::DivKeyword(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "DivKeyword");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732589);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        bool pass = true;
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::NAME)
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
            pass = lexer.GetKeywordToken(token->match) == soul_expected::xml::xpath::token::DIV;
        }
        if (match.hit && !pass)
        {
            match = soul_expected::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DivKeyword");
        else soul_expected::lexer::WriteFailureToLog(lexer, "DivKeyword");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::ModKeyword(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "ModKeyword");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732590);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        bool pass = true;
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::NAME)
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
            pass = lexer.GetKeywordToken(token->match) == soul_expected::xml::xpath::token::MOD;
        }
        if (match.hit && !pass)
        {
            match = soul_expected::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ModKeyword");
        else soul_expected::lexer::WriteFailureToLog(lexer, "ModKeyword");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> XPathParser<LexerT>::ProcessingInstructionKeyword(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "ProcessingInstructionKeyword");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8096769971578732591);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        bool pass = true;
        soul_expected::parser::Match match(false);
        if (*lexer == soul_expected::xml::xpath::token::NAME)
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
            pass = lexer.GetKeywordToken(token->match) == soul_expected::xml::xpath::token::PROCESSING_INSTRUCTION;
        }
        if (match.hit && !pass)
        {
            match = soul_expected::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ProcessingInstructionKeyword");
        else soul_expected::lexer::WriteFailureToLog(lexer, "ProcessingInstructionKeyword");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct XPathParser<soul_expected::lexer::Lexer<soul_expected::xml::xpath::lexer::XPathLexer<char32_t>, char32_t>>;

} // namespace soul_expected::xml::xpath::parser
