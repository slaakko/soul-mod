
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ocpp/expression.parser' using soul parser generator oespg version 5.0.0

module soul.cpp.expression.parser;

import util;
import soul.ast.spg;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.tool.token;
import soul.punctuation.token;
import soul.cpp.declarator.parser;
import soul.cpp.declaration.parser;
import soul.cpp.literal.parser;
import soul.cpp.identifier.parser;
import soul.lex;

using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::tool::token;
using namespace soul::punctuation::token;
using namespace soul::cpp::declarator::parser;
using namespace soul::cpp::declaration::parser;
using namespace soul::cpp::literal::parser;
using namespace soul::cpp::identifier::parser;
using namespace soul::lex;

namespace soul::cpp::expression::parser {

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::Expression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Expression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688193);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AssignmentExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        if (*lexer == COMMA)
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AssignmentExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, soul::ast::cpp::Operator::comma, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Expression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Expression");
        else soul::lexer::WriteFailureToLog(lexer, "Expression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::ConstantExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConstantExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688194);
    std::unique_ptr<soul::ast::cpp::Node> expr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::Expression(lexer, context);
        if (!m) return std::unexpected<int>(m.error());
        soul::parser::Match match = *m;
        expr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstantExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstantExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ConstantExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::AssignmentExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AssignmentExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688195);
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
    std::unique_ptr<soul::ast::cpp::Node> conditionalExpr;
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
                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::LogicalOrExpression(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AssignmentOp(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AssignmentExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentExpression");
                            #endif
                            return soul::parser::Match(true, new soul::ast::cpp::BinaryOpExprNode(*sp, op->value, left.release(), right.release()));
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
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ConditionalExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    conditionalExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentExpression");
                            #endif
                            return soul::parser::Match(true, conditionalExpr.release());
                        }
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentExpression");
        else soul::lexer::WriteFailureToLog(lexer, "AssignmentExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::AssignmentOp(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AssignmentOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688196);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                std::int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    std::int64_t save = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch9 = &match;
                                        {
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == ASSIGN)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    {
                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                                        #endif
                                                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::assign));
                                                    }
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
                                            if (!match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                lexer.SetPos(save);
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == MUL_ASSIGN)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            {
                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                                                #endif
                                                                return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::mulAssign));
                                                            }
                                                        }
                                                        *parentMatch12 = match;
                                                    }
                                                    *parentMatch11 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                        }
                                        *parentMatch8 = match;
                                        if (!match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch13 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch14 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == DIV_ASSIGN)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        {
                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                                            #endif
                                                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::divAssign));
                                                        }
                                                    }
                                                    *parentMatch14 = match;
                                                }
                                                *parentMatch13 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                    }
                                    *parentMatch7 = match;
                                    if (!match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch15 = &match;
                                        lexer.SetPos(save);
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch16 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == REM_ASSIGN)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    {
                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                                        #endif
                                                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::remAssign));
                                                    }
                                                }
                                                *parentMatch16 = match;
                                            }
                                            *parentMatch15 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                }
                                *parentMatch6 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch17 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch18 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == PLUS_ASSIGN)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                                    #endif
                                                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::plusAssign));
                                                }
                                            }
                                            *parentMatch18 = match;
                                        }
                                        *parentMatch17 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch19 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch20 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == MINUS_ASSIGN)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                                #endif
                                                return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::minusAssign));
                                            }
                                        }
                                        *parentMatch20 = match;
                                    }
                                    *parentMatch19 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
                        if (!match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch21 = &match;
                            lexer.SetPos(save);
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch22 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == SHIFT_LEFT_ASSIGN)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                            #endif
                                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftLeftAssign));
                                        }
                                    }
                                    *parentMatch22 = match;
                                }
                                *parentMatch21 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch23 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch24 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == SHIFT_RIGHT_ASSIGN)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                        #endif
                                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftRightAssign));
                                    }
                                }
                                *parentMatch24 = match;
                            }
                            *parentMatch23 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch25 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch26 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == AND_ASSIGN)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::andAssign));
                                }
                            }
                            *parentMatch26 = match;
                        }
                        *parentMatch25 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch27 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch28 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == XOR_ASSIGN)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                                #endif
                                return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::xorAssign));
                            }
                        }
                        *parentMatch28 = match;
                    }
                    *parentMatch27 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch29 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch30 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == OR_ASSIGN)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::orAssign));
                        }
                    }
                    *parentMatch30 = match;
                }
                *parentMatch29 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
        else soul::lexer::WriteFailureToLog(lexer, "AssignmentOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::ConditionalExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConditionalExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688197);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> thenExpr;
    std::unique_ptr<soul::ast::cpp::Node> elseExpr;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::LogicalOrExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == QUEST)
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
                                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::Expression(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            thenExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == COLON)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch11 = match;
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
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch13 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AssignmentExpression(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        elseExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            expr.reset(new soul::ast::cpp::ConditionalNode(*sp, expr.release(), thenExpr.release(), elseExpr.release()));
                                        }
                                        *parentMatch13 = match;
                                    }
                                    *parentMatch12 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConditionalExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConditionalExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ConditionalExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::LogicalOrExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LogicalOrExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688198);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::LogicalAndExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        if (*lexer == DISJUNCTION)
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::LogicalAndExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, soul::ast::cpp::Operator::or_, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LogicalOrExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LogicalOrExpression");
        else soul::lexer::WriteFailureToLog(lexer, "LogicalOrExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::LogicalAndExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LogicalAndExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688199);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::InclusiveOrExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        if (*lexer == AMP_AMP)
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::InclusiveOrExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, soul::ast::cpp::Operator::and_, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LogicalAndExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LogicalAndExpression");
        else soul::lexer::WriteFailureToLog(lexer, "LogicalAndExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::InclusiveOrExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "InclusiveOrExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688200);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ExclusiveOrExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        if (*lexer == PIPE)
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ExclusiveOrExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, soul::ast::cpp::Operator::bitor_, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InclusiveOrExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InclusiveOrExpression");
        else soul::lexer::WriteFailureToLog(lexer, "InclusiveOrExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::ExclusiveOrExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ExclusiveOrExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688201);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AndExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        if (*lexer == CARET)
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AndExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, soul::ast::cpp::Operator::bitxor, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExclusiveOrExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExclusiveOrExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ExclusiveOrExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::AndExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AndExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688202);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::EqualityExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        if (*lexer == AMP)
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::EqualityExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, soul::ast::cpp::Operator::bitand_, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AndExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AndExpression");
        else soul::lexer::WriteFailureToLog(lexer, "AndExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::EqualityExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "EqualityExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688203);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::RelationalExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::EqOp(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::RelationalExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityExpression");
        else soul::lexer::WriteFailureToLog(lexer, "EqualityExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::EqOp(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "EqOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688204);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == EQ)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqOp");
                    #endif
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::eq));
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == NEQ)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqOp");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::notEq));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqOp");
        else soul::lexer::WriteFailureToLog(lexer, "EqOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::RelationalExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RelationalExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688205);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ShiftExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::RelOp(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ShiftExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalExpression");
        else soul::lexer::WriteFailureToLog(lexer, "RelationalExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::RelOp(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RelOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688206);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == LANGLE)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::less));
                        }
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                bool pass = true;
                                soul::parser::Match match(true);
                                if (match.hit)
                                {
                                    pass = !context->ParsingTemplateId();
                                }
                                if (match.hit && !pass)
                                {
                                    match = soul::parser::Match(false);
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == RANGLE)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                                            #endif
                                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::greater));
                                        }
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch9 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == LEQ)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                                #endif
                                return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::lessOrEq));
                            }
                        }
                        *parentMatch10 = match;
                    }
                    *parentMatch9 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch12 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == GEQ)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::greaterOrEq));
                        }
                    }
                    *parentMatch12 = match;
                }
                *parentMatch11 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
        else soul::lexer::WriteFailureToLog(lexer, "RelOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::ShiftExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ShiftExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688207);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AdditiveExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ShiftOp(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AdditiveExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ShiftExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::ShiftOp(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ShiftOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688208);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == SHIFT_LEFT)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
                    #endif
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftLeft));
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == SHIFT_RIGHT)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftRight));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
        else soul::lexer::WriteFailureToLog(lexer, "ShiftOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::AdditiveExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AdditiveExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688209);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::MultiplicativeExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AddOp(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::MultiplicativeExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveExpression");
        else soul::lexer::WriteFailureToLog(lexer, "AdditiveExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::AddOp(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AddOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688210);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
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
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddOp");
                    #endif
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::plus));
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddOp");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::minus));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddOp");
        else soul::lexer::WriteFailureToLog(lexer, "AddOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::MultiplicativeExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MultiplicativeExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688211);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::PmExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::MulOp(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::PmExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeExpression");
        else soul::lexer::WriteFailureToLog(lexer, "MultiplicativeExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::MulOp(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MulOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688212);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::mul));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == DIV)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
                                #endif
                                return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::div));
                            }
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == REM)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::rem));
                        }
                    }
                    *parentMatch6 = match;
                }
                *parentMatch5 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
        else soul::lexer::WriteFailureToLog(lexer, "MulOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::PmExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PmExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688213);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::CastExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::PmOp(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
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
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::CastExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(*sp, op->value, expr.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmExpression");
        else soul::lexer::WriteFailureToLog(lexer, "PmExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::PmOp(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PmOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688214);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == DOT_STAR)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmOp");
                    #endif
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::dotStar));
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == ARROW_STAR)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmOp");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::arrowStar));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmOp");
        else soul::lexer::WriteFailureToLog(lexer, "PmOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::CastExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CastExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688215);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::TypeIdNode> typeId;
    std::unique_ptr<soul::ast::cpp::Node> castExpr;
    std::unique_ptr<soul::ast::cpp::Node> unaryExpr;
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
                std::int64_t save = lexer.GetPos();
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                std::expected<soul::parser::Match, int> m = DeclaratorParser<LexerT>::TypeId(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                typeId.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch7 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == RPAREN)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch7 = match;
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch9 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::CastExpression(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            castExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                            if (match.hit)
                            {
                                auto sp = lexer.GetSourcePos(pos);
                                if (!sp) return std::unexpected<int>(sp.error());
                                expr.reset(new soul::ast::cpp::CastNode(*sp, typeId.release(), castExpr.release()));
                            }
                            *parentMatch9 = match;
                        }
                        *parentMatch8 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch11 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::UnaryExpression(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            unaryExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                            if (match.hit)
                            {
                                expr.reset(unaryExpr.release());
                            }
                            *parentMatch11 = match;
                        }
                        *parentMatch10 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CastExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CastExpression");
        else soul::lexer::WriteFailureToLog(lexer, "CastExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::UnaryExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UnaryExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688216);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> postfixExpr;
    std::unique_ptr<soul::ast::cpp::Node> postCastExpr;
    std::unique_ptr<soul::ast::cpp::Node> u1;
    std::unique_ptr<soul::ast::cpp::Node> u2;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> castExpr;
    std::unique_ptr<soul::ast::cpp::TypeIdNode> typeId;
    std::unique_ptr<soul::ast::cpp::Node> u3;
    std::unique_ptr<soul::ast::cpp::Node> newExpr;
    std::unique_ptr<soul::ast::cpp::Node> deleteExpr;
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
                std::int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                std::int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    std::int64_t save = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch9 = &match;
                                        {
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::PostfixExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                postfixExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(postfixExpr.release());
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
                                            if (!match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                lexer.SetPos(save);
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::PostCastExpression(lexer, context);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul::parser::Match match = *m;
                                                        postCastExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            expr.reset(postCastExpr.release());
                                                        }
                                                        *parentMatch12 = match;
                                                    }
                                                    *parentMatch11 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                        }
                                        *parentMatch8 = match;
                                        if (!match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch13 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch14 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == PLUS_PLUS)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    *parentMatch14 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch15 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch16 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::UnaryExpression(lexer, context);
                                                            if (!m) return std::unexpected<int>(m.error());
                                                            soul::parser::Match match = *m;
                                                            u1.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                auto sp = lexer.GetSourcePos(pos);
                                                                if (!sp) return std::unexpected<int>(sp.error());
                                                                expr.reset(new soul::ast::cpp::PreIncrementNode(*sp, u1.release()));
                                                            }
                                                            *parentMatch16 = match;
                                                        }
                                                        *parentMatch15 = match;
                                                    }
                                                    *parentMatch14 = match;
                                                }
                                                *parentMatch13 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                    }
                                    *parentMatch7 = match;
                                    if (!match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch17 = &match;
                                        lexer.SetPos(save);
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch18 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == MINUS_MINUS)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                *parentMatch18 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch19 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch20 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::UnaryExpression(lexer, context);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul::parser::Match match = *m;
                                                        u2.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            auto sp = lexer.GetSourcePos(pos);
                                                            if (!sp) return std::unexpected<int>(sp.error());
                                                            expr.reset(new soul::ast::cpp::PreDecrementNode(*sp, u2.release()));
                                                        }
                                                        *parentMatch20 = match;
                                                    }
                                                    *parentMatch19 = match;
                                                }
                                                *parentMatch18 = match;
                                            }
                                            *parentMatch17 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                }
                                *parentMatch6 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch21 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch22 = &match;
                                        {
                                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::UnaryOperator(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
                                            *parentMatch22 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch23 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch24 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::CastExpression(lexer, context);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul::parser::Match match = *m;
                                                    castExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        auto sp = lexer.GetSourcePos(pos);
                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                        expr.reset(new soul::ast::cpp::UnaryOpExprNode(*sp, op->value, castExpr.release()));
                                                    }
                                                    *parentMatch24 = match;
                                                }
                                                *parentMatch23 = match;
                                            }
                                            *parentMatch22 = match;
                                        }
                                        *parentMatch21 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch25 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch26 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch27 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch28 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == SIZEOF)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                *parentMatch28 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch29 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == LPAREN)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    *parentMatch29 = match;
                                                }
                                                *parentMatch28 = match;
                                            }
                                            *parentMatch27 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch30 = &match;
                                            {
                                                std::expected<soul::parser::Match, int> m = DeclaratorParser<LexerT>::TypeId(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                typeId.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                                                *parentMatch30 = match;
                                            }
                                            *parentMatch27 = match;
                                        }
                                        *parentMatch26 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch31 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch32 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == RPAREN)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    expr.reset(new soul::ast::cpp::SizeOfNode(*sp, typeId.release(), true));
                                                }
                                                *parentMatch32 = match;
                                            }
                                            *parentMatch31 = match;
                                        }
                                        *parentMatch26 = match;
                                    }
                                    *parentMatch25 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
                        if (!match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch33 = &match;
                            lexer.SetPos(save);
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch34 = &match;
                                {
                                    soul::parser::Match match(false);
                                    if (*lexer == SIZEOF)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    *parentMatch34 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch35 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch36 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::UnaryExpression(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            u3.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                auto sp = lexer.GetSourcePos(pos);
                                                if (!sp) return std::unexpected<int>(sp.error());
                                                expr.reset(new soul::ast::cpp::SizeOfNode(*sp, u3.release(), false));
                                            }
                                            *parentMatch36 = match;
                                        }
                                        *parentMatch35 = match;
                                    }
                                    *parentMatch34 = match;
                                }
                                *parentMatch33 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch37 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch38 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::NewExpression(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                newExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(newExpr.release());
                                }
                                *parentMatch38 = match;
                            }
                            *parentMatch37 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch39 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch40 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::DeleteExpression(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            deleteExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                            if (match.hit)
                            {
                                expr.reset(deleteExpr.release());
                            }
                            *parentMatch40 = match;
                        }
                        *parentMatch39 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryExpression");
        else soul::lexer::WriteFailureToLog(lexer, "UnaryExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::UnaryOperator(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UnaryOperator");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688217);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
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
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::deref));
                                }
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                        if (!match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            lexer.SetPos(save);
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == AMP)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                                            #endif
                                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::addrOf));
                                        }
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
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
                                soul::parser::Match match(false);
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
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                                        #endif
                                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::plus));
                                    }
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch11 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
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
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::minus));
                                }
                            }
                            *parentMatch11 = match;
                        }
                        *parentMatch10 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch12 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch13 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == EXCLAMATION)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                                #endif
                                return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::not_));
                            }
                        }
                        *parentMatch13 = match;
                    }
                    *parentMatch12 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch14 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch15 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == TILDE)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                            #endif
                            return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::cpl));
                        }
                    }
                    *parentMatch15 = match;
                }
                *parentMatch14 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
        else soul::lexer::WriteFailureToLog(lexer, "UnaryOperator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::PostfixExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PostfixExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688218);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> primaryExpr;
    std::unique_ptr<soul::ast::cpp::Node> index;
    std::unique_ptr<soul::ast::cpp::Node> dotMember;
    std::unique_ptr<soul::ast::cpp::Node> arrowMember;
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::PrimaryExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    primaryExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                        std::int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                std::int64_t save = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t save = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch11 = &match;
                                                    {
                                                        std::int64_t save = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch12 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch13 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                if (*lexer == LBRACKET)
                                                                {
                                                                    auto a = ++lexer;
                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                    match.hit = true;
                                                                }
                                                                *parentMatch13 = match;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch14 = &match;
                                                                {
                                                                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::Expression(lexer, context);
                                                                    if (!m) return std::unexpected<int>(m.error());
                                                                    soul::parser::Match match = *m;
                                                                    index.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                                    *parentMatch14 = match;
                                                                }
                                                                *parentMatch13 = match;
                                                            }
                                                            *parentMatch12 = match;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch15 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch16 = &match;
                                                                {
                                                                    std::int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match(false);
                                                                    if (*lexer == RBRACKET)
                                                                    {
                                                                        auto a = ++lexer;
                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                        match.hit = true;
                                                                    }
                                                                    if (match.hit)
                                                                    {
                                                                        auto sp = lexer.GetSourcePos(pos);
                                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                                        expr.reset(new soul::ast::cpp::IndexExprNode(*sp, expr.release(), index.release()));
                                                                    }
                                                                    *parentMatch16 = match;
                                                                }
                                                                *parentMatch15 = match;
                                                            }
                                                            *parentMatch12 = match;
                                                        }
                                                        *parentMatch11 = match;
                                                        if (!match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch17 = &match;
                                                            lexer.SetPos(save);
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch18 = &match;
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch19 = &match;
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch20 = &match;
                                                                        {
                                                                            std::int64_t pos = lexer.GetPos();
                                                                            soul::parser::Match match(false);
                                                                            if (*lexer == LPAREN)
                                                                            {
                                                                                auto a = ++lexer;
                                                                                if (!a) return std::unexpected<int>(a.error());
                                                                                match.hit = true;
                                                                            }
                                                                            if (match.hit)
                                                                            {
                                                                                auto sp = lexer.GetSourcePos(pos);
                                                                                if (!sp) return std::unexpected<int>(sp.error());
                                                                                expr.reset(new soul::ast::cpp::InvokeNode(*sp, expr.release()));
                                                                            }
                                                                            *parentMatch20 = match;
                                                                        }
                                                                        *parentMatch19 = match;
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
                                                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ExpressionList(lexer, context, expr.get());
                                                                                if (!m) return std::unexpected<int>(m.error());
                                                                                soul::parser::Match match = *m;
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
                                                                        *parentMatch19 = match;
                                                                    }
                                                                    *parentMatch18 = match;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch23 = &match;
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        if (*lexer == RPAREN)
                                                                        {
                                                                            auto a = ++lexer;
                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                            match.hit = true;
                                                                        }
                                                                        *parentMatch23 = match;
                                                                    }
                                                                    *parentMatch18 = match;
                                                                }
                                                                *parentMatch17 = match;
                                                            }
                                                            *parentMatch11 = match;
                                                        }
                                                    }
                                                    *parentMatch10 = match;
                                                    if (!match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch24 = &match;
                                                        lexer.SetPos(save);
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch25 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                if (*lexer == DOT)
                                                                {
                                                                    auto a = ++lexer;
                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                    match.hit = true;
                                                                }
                                                                *parentMatch25 = match;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch26 = &match;
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch27 = &match;
                                                                    {
                                                                        std::int64_t pos = lexer.GetPos();
                                                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::IdExpression(lexer, context);
                                                                        if (!m) return std::unexpected<int>(m.error());
                                                                        soul::parser::Match match = *m;
                                                                        dotMember.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                                        if (match.hit)
                                                                        {
                                                                            auto sp = lexer.GetSourcePos(pos);
                                                                            if (!sp) return std::unexpected<int>(sp.error());
                                                                            expr.reset(new soul::ast::cpp::MemberAccessNode(*sp, expr.release(), dotMember.release()));
                                                                        }
                                                                        *parentMatch27 = match;
                                                                    }
                                                                    *parentMatch26 = match;
                                                                }
                                                                *parentMatch25 = match;
                                                            }
                                                            *parentMatch24 = match;
                                                        }
                                                        *parentMatch10 = match;
                                                    }
                                                }
                                                *parentMatch9 = match;
                                                if (!match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch28 = &match;
                                                    lexer.SetPos(save);
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch29 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            if (*lexer == ARROW)
                                                            {
                                                                auto a = ++lexer;
                                                                if (!a) return std::unexpected<int>(a.error());
                                                                match.hit = true;
                                                            }
                                                            *parentMatch29 = match;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch30 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch31 = &match;
                                                                {
                                                                    std::int64_t pos = lexer.GetPos();
                                                                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::IdExpression(lexer, context);
                                                                    if (!m) return std::unexpected<int>(m.error());
                                                                    soul::parser::Match match = *m;
                                                                    arrowMember.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        auto sp = lexer.GetSourcePos(pos);
                                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                                        expr.reset(new soul::ast::cpp::PtrMemberAccessNode(*sp, expr.release(), arrowMember.release()));
                                                                    }
                                                                    *parentMatch31 = match;
                                                                }
                                                                *parentMatch30 = match;
                                                            }
                                                            *parentMatch29 = match;
                                                        }
                                                        *parentMatch28 = match;
                                                    }
                                                    *parentMatch9 = match;
                                                }
                                            }
                                            *parentMatch8 = match;
                                            if (!match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch32 = &match;
                                                lexer.SetPos(save);
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch33 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == PLUS_PLUS)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            auto sp = lexer.GetSourcePos(pos);
                                                            if (!sp) return std::unexpected<int>(sp.error());
                                                            expr.reset(new soul::ast::cpp::PostIncrementNode(*sp, expr.release()));
                                                        }
                                                        *parentMatch33 = match;
                                                    }
                                                    *parentMatch32 = match;
                                                }
                                                *parentMatch8 = match;
                                            }
                                        }
                                        *parentMatch7 = match;
                                        if (!match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch34 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch35 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == MINUS_MINUS)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        auto sp = lexer.GetSourcePos(pos);
                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                        expr.reset(new soul::ast::cpp::PostDecrementNode(*sp, expr.release()));
                                                    }
                                                    *parentMatch35 = match;
                                                }
                                                *parentMatch34 = match;
                                            }
                                            *parentMatch7 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PostfixExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PostfixExpression");
        else soul::lexer::WriteFailureToLog(lexer, "PostfixExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::PostCastExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PostCastExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688219);
    std::unique_ptr<soul::ast::cpp::CppCastNode> cppCastNode = std::unique_ptr<soul::ast::cpp::CppCastNode>();
    std::unique_ptr<soul::ast::cpp::TypeIdNode> typeId;
    std::unique_ptr<soul::ast::cpp::Node> expr;
    std::unique_ptr<soul::ast::cpp::Node> typeIdExpr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
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
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                std::int64_t save = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    std::int64_t save = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == STATIC_CAST)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            auto sp = lexer.GetSourcePos(pos);
                                                            if (!sp) return std::unexpected<int>(sp.error());
                                                            cppCastNode.reset(new soul::ast::cpp::StaticCastNode(*sp));
                                                        }
                                                        *parentMatch12 = match;
                                                    }
                                                    *parentMatch11 = match;
                                                    if (!match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch13 = &match;
                                                        lexer.SetPos(save);
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch14 = &match;
                                                            {
                                                                std::int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match(false);
                                                                if (*lexer == DYNAMIC_CAST)
                                                                {
                                                                    auto a = ++lexer;
                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                    match.hit = true;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    auto sp = lexer.GetSourcePos(pos);
                                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                                    cppCastNode.reset(new soul::ast::cpp::DynamicCastNode(*sp));
                                                                }
                                                                *parentMatch14 = match;
                                                            }
                                                            *parentMatch13 = match;
                                                        }
                                                        *parentMatch11 = match;
                                                    }
                                                }
                                                *parentMatch10 = match;
                                                if (!match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch15 = &match;
                                                    lexer.SetPos(save);
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch16 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match(false);
                                                            if (*lexer == REINTERPRET_CAST)
                                                            {
                                                                auto a = ++lexer;
                                                                if (!a) return std::unexpected<int>(a.error());
                                                                match.hit = true;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                auto sp = lexer.GetSourcePos(pos);
                                                                if (!sp) return std::unexpected<int>(sp.error());
                                                                cppCastNode.reset(new soul::ast::cpp::ReinterpretCastNode(*sp));
                                                            }
                                                            *parentMatch16 = match;
                                                        }
                                                        *parentMatch15 = match;
                                                    }
                                                    *parentMatch10 = match;
                                                }
                                            }
                                            *parentMatch9 = match;
                                            if (!match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch17 = &match;
                                                lexer.SetPos(save);
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch18 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == CONST_CAST)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            auto sp = lexer.GetSourcePos(pos);
                                                            if (!sp) return std::unexpected<int>(sp.error());
                                                            cppCastNode.reset(new soul::ast::cpp::ConstCastNode(*sp));
                                                        }
                                                        *parentMatch18 = match;
                                                    }
                                                    *parentMatch17 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch19 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == LANGLE)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch19 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch20 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = DeclaratorParser<LexerT>::TypeId(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    typeId.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                                    *parentMatch20 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch21 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == RANGLE)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                *parentMatch21 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch22 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == LPAREN)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch22 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch23 = &match;
                    {
                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::Expression(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        expr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                        *parentMatch23 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch24 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch25 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == RPAREN)
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
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PostCastExpression");
                                #endif
                                return soul::parser::Match(true, new soul::ast::cpp::PostCastNode(*sp, cppCastNode.release(), typeId.release(), expr.release()));
                            }
                        }
                        *parentMatch25 = match;
                    }
                    *parentMatch24 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch26 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch27 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch28 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch29 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == TYPEID)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                *parentMatch29 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch30 = &match;
                                {
                                    soul::parser::Match match(false);
                                    if (*lexer == LPAREN)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    *parentMatch30 = match;
                                }
                                *parentMatch29 = match;
                            }
                            *parentMatch28 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch31 = &match;
                            {
                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::Expression(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                typeIdExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                *parentMatch31 = match;
                            }
                            *parentMatch28 = match;
                        }
                        *parentMatch27 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch32 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch33 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == RPAREN)
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
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PostCastExpression");
                                        #endif
                                        return soul::parser::Match(true, new soul::ast::cpp::TypeIdExprNode(*sp, typeIdExpr.release()));
                                    }
                                }
                                *parentMatch33 = match;
                            }
                            *parentMatch32 = match;
                        }
                        *parentMatch27 = match;
                    }
                    *parentMatch26 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PostCastExpression");
        else soul::lexer::WriteFailureToLog(lexer, "PostCastExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::ExpressionList(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::Node* owner)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ExpressionList");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688220);
    std::unique_ptr<soul::ast::cpp::Node> expr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AssignmentExpression(lexer, context);
            if (!m) return std::unexpected<int>(m.error());
            soul::parser::Match match = *m;
            expr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
            if (match.hit)
            {
                owner->Add(expr.release());
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch2 = &match;
        {
            soul::parser::Match match(true);
            soul::parser::Match* parentMatch3 = &match;
            {
                while (true)
                {
                    std::int64_t save = lexer.GetPos();
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch4 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == COMMA)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
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
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::AssignmentExpression(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    expr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        owner->Add(expr.release());
                                    }
                                    *parentMatch6 = match;
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
                            break;
                        }
                    }
                }
            }
            *parentMatch2 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExpressionList");
        else soul::lexer::WriteFailureToLog(lexer, "ExpressionList");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::PrimaryExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PrimaryExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688221);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::LiteralNode> literal;
    std::unique_ptr<soul::ast::cpp::Node> parenExpr;
    std::unique_ptr<soul::ast::cpp::Node> idExpr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = LiteralParser<LexerT>::Literal(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    literal.reset(static_cast<soul::ast::cpp::LiteralNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                            #endif
                            return soul::parser::Match(true, literal.release());
                        }
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == THIS)
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
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                                    #endif
                                    return soul::parser::Match(true, new soul::ast::cpp::ThisNode(*sp));
                                }
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch7 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch8 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == LPAREN)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch8 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::Expression(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                parenExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                *parentMatch9 = match;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
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
                                soul::parser::Match match(false);
                                if (*lexer == RPAREN)
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
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                                        #endif
                                        return soul::parser::Match(true, new soul::ast::cpp::ParenExprNode(*sp, parenExpr.release()));
                                    }
                                }
                                *parentMatch11 = match;
                            }
                            *parentMatch10 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch12 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch13 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::IdExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    idExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                            #endif
                            return soul::parser::Match(true, idExpr.release());
                        }
                    }
                    *parentMatch13 = match;
                }
                *parentMatch12 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
        else soul::lexer::WriteFailureToLog(lexer, "PrimaryExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::IdExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IdExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688222);
    std::string str = std::string();
    std::unique_ptr<soul::ast::cpp::TypeNameNode> typeName;
    std::unique_ptr<soul::parser::Value<std::string>> id1;
    std::unique_ptr<soul::parser::Value<std::string>> ofId1;
    std::unique_ptr<soul::parser::Value<std::string>> ofId2;
    std::unique_ptr<soul::parser::Value<std::string>> id2;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = DeclarationParser<LexerT>::TypeName(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        typeName.reset(static_cast<soul::ast::cpp::TypeNameNode*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                #endif
                                return soul::parser::Match(true, typeName.release());
                            }
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        lexer.SetPos(save);
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
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = CppIdentifierParser<LexerT>::QualifiedCppId(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        id1.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                                        if (match.hit)
                                        {
                                            str = id1->value;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == COLON_COLON)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
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
                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::OperatorFunctionId(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        ofId1.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            str.append("::").append(ofId1->value);
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                                #endif
                                                return soul::parser::Match(true, new soul::ast::cpp::IdExprNode(*sp, str));
                                            }
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch12 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch13 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch14 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch15 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(true);
                                    if (match.hit)
                                    {
                                        str.clear();
                                    }
                                    *parentMatch15 = match;
                                }
                                *parentMatch14 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch16 = &match;
                                {
                                    soul::parser::Match match(true);
                                    std::int64_t save = lexer.GetPos();
                                    soul::parser::Match* parentMatch17 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch18 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch19 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == COLON_COLON)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    str.append("::");
                                                }
                                                *parentMatch19 = match;
                                            }
                                            *parentMatch18 = match;
                                        }
                                        if (match.hit)
                                        {
                                            *parentMatch17 = match;
                                        }
                                        else
                                        {
                                            lexer.SetPos(save);
                                        }
                                    }
                                    *parentMatch16 = match;
                                }
                                *parentMatch14 = match;
                            }
                            *parentMatch13 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch20 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch21 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::OperatorFunctionId(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    ofId2.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        str.append(ofId2->value);
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                            #endif
                                            return soul::parser::Match(true, new soul::ast::cpp::IdExprNode(*sp, str));
                                        }
                                    }
                                    *parentMatch21 = match;
                                }
                                *parentMatch20 = match;
                            }
                            *parentMatch13 = match;
                        }
                        *parentMatch12 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch22 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch23 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = CppIdentifierParser<LexerT>::QualifiedCppId(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        id2.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            auto sp = lexer.GetSourcePos(pos);
                            if (!sp) return std::unexpected<int>(sp.error());
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                #endif
                                return soul::parser::Match(true, new soul::ast::cpp::IdExprNode(*sp, id2->value));
                            }
                        }
                        *parentMatch23 = match;
                    }
                    *parentMatch22 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
        else soul::lexer::WriteFailureToLog(lexer, "IdExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::TypeSpecifierOrTypeName(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeSpecifierOrTypeName");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688223);
    std::unique_ptr<soul::ast::cpp::TypeSpecifierNode> simpleTypeSpecifier;
    std::unique_ptr<soul::ast::cpp::TypeNameNode> typeName;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul::parser::Match, int> m = DeclarationParser<LexerT>::SimpleTypeSpecifier(lexer, context);
            if (!m) return std::unexpected<int>(m.error());
            soul::parser::Match match = *m;
            simpleTypeSpecifier.reset(static_cast<soul::ast::cpp::TypeSpecifierNode*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierOrTypeName");
                    #endif
                    return soul::parser::Match(true, simpleTypeSpecifier.release());
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = DeclarationParser<LexerT>::TypeName(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    typeName.reset(static_cast<soul::ast::cpp::TypeNameNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierOrTypeName");
                            #endif
                            return soul::parser::Match(true, typeName.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierOrTypeName");
        else soul::lexer::WriteFailureToLog(lexer, "TypeSpecifierOrTypeName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::NewExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688224);
    bool global = bool();
    std::unique_ptr<soul::ast::cpp::NewNode> newExprNode = std::unique_ptr<soul::ast::cpp::NewNode>();
    std::unique_ptr<soul::ast::cpp::TypeIdNode> newTypeId;
    std::unique_ptr<soul::ast::cpp::TypeIdNode> ti;
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
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch9 = &match;
                                        {
                                            soul::parser::Match match(true);
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == COLON_COLON)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            global = true;
                                                        }
                                                        *parentMatch12 = match;
                                                    }
                                                    *parentMatch11 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch10 = match;
                                                }
                                                else
                                                {
                                                    lexer.SetPos(save);
                                                }
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
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == NEW)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        auto sp = lexer.GetSourcePos(pos);
                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                        newExprNode.reset(new soul::ast::cpp::NewNode(*sp, global));
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
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch15 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch16 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                if (match.hit)
                                                {
                                                    newExprNode->BeginAddToPlacement();
                                                }
                                                *parentMatch16 = match;
                                            }
                                            *parentMatch15 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch17 = &match;
                                    {
                                        soul::parser::Match match(true);
                                        std::int64_t save = lexer.GetPos();
                                        soul::parser::Match* parentMatch18 = &match;
                                        {
                                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::NewPlacement(lexer, context, newExprNode.get());
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            if (match.hit)
                                            {
                                                *parentMatch18 = match;
                                            }
                                            else
                                            {
                                                lexer.SetPos(save);
                                            }
                                        }
                                        *parentMatch17 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch19 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch20 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(true);
                                        if (match.hit)
                                        {
                                            newExprNode->EndAddToPlacement();
                                        }
                                        *parentMatch20 = match;
                                    }
                                    *parentMatch19 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch21 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch22 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch23 = &match;
                                    {
                                        std::int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch24 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::NewTypeId(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            newTypeId.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                                            if (match.hit)
                                            {
                                                newExprNode->SetParens(false);
                                                newExprNode->SetTypeId(newTypeId.release());
                                            }
                                            *parentMatch24 = match;
                                        }
                                        *parentMatch23 = match;
                                        if (!match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch25 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch26 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch27 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        if (*lexer == LPAREN)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        *parentMatch27 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch28 = &match;
                                                        {
                                                            std::expected<soul::parser::Match, int> m = DeclaratorParser<LexerT>::TypeId(lexer, context);
                                                            if (!m) return std::unexpected<int>(m.error());
                                                            soul::parser::Match match = *m;
                                                            ti.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                                                            *parentMatch28 = match;
                                                        }
                                                        *parentMatch27 = match;
                                                    }
                                                    *parentMatch26 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch29 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch30 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match(false);
                                                            if (*lexer == RPAREN)
                                                            {
                                                                auto a = ++lexer;
                                                                if (!a) return std::unexpected<int>(a.error());
                                                                match.hit = true;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                newExprNode->SetParens(true);
                                                                newExprNode->SetTypeId(ti.release());
                                                            }
                                                            *parentMatch30 = match;
                                                        }
                                                        *parentMatch29 = match;
                                                    }
                                                    *parentMatch26 = match;
                                                }
                                                *parentMatch25 = match;
                                            }
                                            *parentMatch23 = match;
                                        }
                                    }
                                    *parentMatch22 = match;
                                }
                                *parentMatch21 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch31 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch32 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(true);
                                if (match.hit)
                                {
                                    newExprNode->BeginAddToInitializer();
                                }
                                *parentMatch32 = match;
                            }
                            *parentMatch31 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch33 = &match;
                    {
                        soul::parser::Match match(true);
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch34 = &match;
                        {
                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::NewInitializer(lexer, context, newExprNode.get());
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            if (match.hit)
                            {
                                *parentMatch34 = match;
                            }
                            else
                            {
                                lexer.SetPos(save);
                            }
                        }
                        *parentMatch33 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch35 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch36 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match(true);
                        if (match.hit)
                        {
                            newExprNode->EndAddToInitializer();
                        }
                        *parentMatch36 = match;
                    }
                    *parentMatch35 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewExpression");
                #endif
                return soul::parser::Match(true, newExprNode.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewExpression");
        else soul::lexer::WriteFailureToLog(lexer, "NewExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::NewPlacement(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::Node* owner)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewPlacement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688225);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == LPAREN)
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
                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ExpressionList(lexer, context, owner);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
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
            if (*lexer == RPAREN)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            *parentMatch3 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewPlacement");
        else soul::lexer::WriteFailureToLog(lexer, "NewPlacement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::NewTypeId(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewTypeId");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688226);
    std::unique_ptr<soul::ast::cpp::TypeIdNode> ti = std::unique_ptr<soul::ast::cpp::TypeIdNode>();
    std::unique_ptr<soul::ast::cpp::TypeNameNode> typeName;
    std::unique_ptr<soul::parser::Value<std::string>> newDeclarator;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match(true);
            if (match.hit)
            {
                ti.reset(new soul::ast::cpp::TypeIdNode(*lexer.GetSourcePos(pos)));
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                                std::int64_t save = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = DeclaratorParser<LexerT>::TypeSpecifierSeq(lexer, context, ti.get());
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                *parentMatch7 = match;
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
                                            std::expected<soul::parser::Match, int> m = DeclarationParser<LexerT>::TypeName(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            typeName.reset(static_cast<soul::ast::cpp::TypeNameNode*>(match.value));
                                            if (match.hit)
                                            {
                                                ti->Add(typeName.release());
                                            }
                                            *parentMatch9 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch12 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch13 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::NewDeclarator(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        newDeclarator.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                                        if (match.hit)
                                        {
                                            ti->SetDeclarator(newDeclarator->value);
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
                        *parentMatch5 = match;
                    }
                    *parentMatch4 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewTypeId");
                        #endif
                        return soul::parser::Match(true, ti.release());
                    }
                }
                *parentMatch3 = match;
            }
            *parentMatch2 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewTypeId");
        else soul::lexer::WriteFailureToLog(lexer, "NewTypeId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::NewDeclarator(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewDeclarator");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688227);
    std::string str = std::string();
    std::unique_ptr<soul::parser::Value<std::string>> ptrOperator;
    std::unique_ptr<soul::parser::Value<std::string>> newDeclarator;
    std::unique_ptr<soul::parser::Value<std::string>> directNewDeclarator;
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
                std::int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = DeclaratorParser<LexerT>::PtrOperator(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        ptrOperator.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            str.append(ptrOperator->value);
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
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::NewDeclarator(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    newDeclarator.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                                    if (match.hit)
                                    {
                                        str.append(newDeclarator->value);
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
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch9 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch10 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::DirectNewDeclarator(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            directNewDeclarator.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                str.append(directNewDeclarator->value);
                            }
                            *parentMatch10 = match;
                        }
                        *parentMatch9 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewDeclarator");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewDeclarator");
        else soul::lexer::WriteFailureToLog(lexer, "NewDeclarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::NewInitializer(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::Node* owner)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewInitializer");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688228);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == LPAREN)
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
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ExpressionList(lexer, context, owner);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
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
        soul::parser::Match* parentMatch4 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == RPAREN)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewInitializer");
        else soul::lexer::WriteFailureToLog(lexer, "NewInitializer");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::DirectNewDeclarator(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DirectNewDeclarator");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688229);
    std::string str = std::string();
    std::unique_ptr<soul::ast::cpp::Node> expr;
    std::unique_ptr<soul::ast::cpp::Node> constantExpr;
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
                            soul::parser::Match match(false);
                            if (*lexer == LBRACKET)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                str.append("[");
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
                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::Expression(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                expr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                if (match.hit)
                                {
                                    str.append(expr.release()->ToString());
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch9 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == RBRACKET)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                str.append("]");
                            }
                            *parentMatch9 = match;
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
                            std::int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch12 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch13 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch14 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            if (*lexer == LBRACKET)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            *parentMatch14 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch15 = &match;
                                            {
                                                std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::ConstantExpression(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                constantExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                *parentMatch15 = match;
                                            }
                                            *parentMatch14 = match;
                                        }
                                        *parentMatch13 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch16 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch17 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == RBRACKET)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    str.append("[").append(constantExpr.release()->ToString()).append("]");
                                                }
                                                *parentMatch17 = match;
                                            }
                                            *parentMatch16 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DirectNewDeclarator");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DirectNewDeclarator");
        else soul::lexer::WriteFailureToLog(lexer, "DirectNewDeclarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::DeleteExpression(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DeleteExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688230);
    bool global = bool();
    bool isArray = bool();
    std::unique_ptr<soul::ast::cpp::Node> ptr;
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
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == COLON_COLON)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        global = true;
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
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch8 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == DELETE)
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
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch10 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch11 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch12 = &match;
                                {
                                    soul::parser::Match match(false);
                                    if (*lexer == LBRACKET)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    *parentMatch12 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch13 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch14 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == RBRACKET)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                isArray = true;
                                            }
                                            *parentMatch14 = match;
                                        }
                                        *parentMatch13 = match;
                                    }
                                    *parentMatch12 = match;
                                }
                                *parentMatch11 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch10 = match;
                            }
                            else
                            {
                                lexer.SetPos(save);
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
                soul::parser::Match* parentMatch15 = &match;
                {
                    std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::CastExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    ptr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                    *parentMatch15 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeleteExpression");
                #endif
                return soul::parser::Match(true, new soul::ast::cpp::DeleteNode(*sp, global, isArray, ptr.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeleteExpression");
        else soul::lexer::WriteFailureToLog(lexer, "DeleteExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::OperatorFunctionId(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "OperatorFunctionId");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688231);
    std::string str = std::string();
    std::unique_ptr<soul::parser::Value<std::string>> op;
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
                    soul::parser::Match match(false);
                    if (*lexer == OPERATOR)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        str.append("operator");
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = ExpressionParser<LexerT>::Operator(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        op.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            str.append(op->value);
                        }
                        *parentMatch5 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OperatorFunctionId");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OperatorFunctionId");
        else soul::lexer::WriteFailureToLog(lexer, "OperatorFunctionId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> ExpressionParser<LexerT>::Operator(LexerT& lexer, soul::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Operator");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688232);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                std::int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    std::int64_t save = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch9 = &match;
                                        {
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                std::int64_t save = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    std::int64_t save = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        std::int64_t save = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch13 = &match;
                                                        {
                                                            std::int64_t save = lexer.GetPos();
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch14 = &match;
                                                            {
                                                                std::int64_t save = lexer.GetPos();
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch15 = &match;
                                                                {
                                                                    std::int64_t save = lexer.GetPos();
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch16 = &match;
                                                                    {
                                                                        std::int64_t save = lexer.GetPos();
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch17 = &match;
                                                                        {
                                                                            std::int64_t save = lexer.GetPos();
                                                                            soul::parser::Match match(false);
                                                                            soul::parser::Match* parentMatch18 = &match;
                                                                            {
                                                                                std::int64_t save = lexer.GetPos();
                                                                                soul::parser::Match match(false);
                                                                                soul::parser::Match* parentMatch19 = &match;
                                                                                {
                                                                                    std::int64_t save = lexer.GetPos();
                                                                                    soul::parser::Match match(false);
                                                                                    soul::parser::Match* parentMatch20 = &match;
                                                                                    {
                                                                                        std::int64_t save = lexer.GetPos();
                                                                                        soul::parser::Match match(false);
                                                                                        soul::parser::Match* parentMatch21 = &match;
                                                                                        {
                                                                                            std::int64_t save = lexer.GetPos();
                                                                                            soul::parser::Match match(false);
                                                                                            soul::parser::Match* parentMatch22 = &match;
                                                                                            {
                                                                                                std::int64_t save = lexer.GetPos();
                                                                                                soul::parser::Match match(false);
                                                                                                soul::parser::Match* parentMatch23 = &match;
                                                                                                {
                                                                                                    std::int64_t save = lexer.GetPos();
                                                                                                    soul::parser::Match match(false);
                                                                                                    soul::parser::Match* parentMatch24 = &match;
                                                                                                    {
                                                                                                        std::int64_t save = lexer.GetPos();
                                                                                                        soul::parser::Match match(false);
                                                                                                        soul::parser::Match* parentMatch25 = &match;
                                                                                                        {
                                                                                                            std::int64_t save = lexer.GetPos();
                                                                                                            soul::parser::Match match(false);
                                                                                                            soul::parser::Match* parentMatch26 = &match;
                                                                                                            {
                                                                                                                std::int64_t save = lexer.GetPos();
                                                                                                                soul::parser::Match match(false);
                                                                                                                soul::parser::Match* parentMatch27 = &match;
                                                                                                                {
                                                                                                                    std::int64_t save = lexer.GetPos();
                                                                                                                    soul::parser::Match match(false);
                                                                                                                    soul::parser::Match* parentMatch28 = &match;
                                                                                                                    {
                                                                                                                        std::int64_t save = lexer.GetPos();
                                                                                                                        soul::parser::Match match(false);
                                                                                                                        soul::parser::Match* parentMatch29 = &match;
                                                                                                                        {
                                                                                                                            std::int64_t save = lexer.GetPos();
                                                                                                                            soul::parser::Match match(false);
                                                                                                                            soul::parser::Match* parentMatch30 = &match;
                                                                                                                            {
                                                                                                                                std::int64_t save = lexer.GetPos();
                                                                                                                                soul::parser::Match match(false);
                                                                                                                                soul::parser::Match* parentMatch31 = &match;
                                                                                                                                {
                                                                                                                                    std::int64_t save = lexer.GetPos();
                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                    soul::parser::Match* parentMatch32 = &match;
                                                                                                                                    {
                                                                                                                                        std::int64_t save = lexer.GetPos();
                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                        soul::parser::Match* parentMatch33 = &match;
                                                                                                                                        {
                                                                                                                                            std::int64_t save = lexer.GetPos();
                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                            soul::parser::Match* parentMatch34 = &match;
                                                                                                                                            {
                                                                                                                                                std::int64_t save = lexer.GetPos();
                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                soul::parser::Match* parentMatch35 = &match;
                                                                                                                                                {
                                                                                                                                                    std::int64_t save = lexer.GetPos();
                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                    soul::parser::Match* parentMatch36 = &match;
                                                                                                                                                    {
                                                                                                                                                        std::int64_t save = lexer.GetPos();
                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                        soul::parser::Match* parentMatch37 = &match;
                                                                                                                                                        {
                                                                                                                                                            std::int64_t save = lexer.GetPos();
                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                            soul::parser::Match* parentMatch38 = &match;
                                                                                                                                                            {
                                                                                                                                                                std::int64_t save = lexer.GetPos();
                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                soul::parser::Match* parentMatch39 = &match;
                                                                                                                                                                {
                                                                                                                                                                    std::int64_t save = lexer.GetPos();
                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                    soul::parser::Match* parentMatch40 = &match;
                                                                                                                                                                    {
                                                                                                                                                                        std::int64_t save = lexer.GetPos();
                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                        soul::parser::Match* parentMatch41 = &match;
                                                                                                                                                                        {
                                                                                                                                                                            std::int64_t save = lexer.GetPos();
                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                            soul::parser::Match* parentMatch42 = &match;
                                                                                                                                                                            {
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                if (*lexer == LBRACKET)
                                                                                                                                                                                {
                                                                                                                                                                                    auto a = ++lexer;
                                                                                                                                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                                    match.hit = true;
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch42 = match;
                                                                                                                                                                            }
                                                                                                                                                                            if (match.hit)
                                                                                                                                                                            {
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                soul::parser::Match* parentMatch43 = &match;
                                                                                                                                                                                {
                                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                                    soul::parser::Match* parentMatch44 = &match;
                                                                                                                                                                                    {
                                                                                                                                                                                        std::int64_t pos = lexer.GetPos();
                                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                                        if (*lexer == RBRACKET)
                                                                                                                                                                                        {
                                                                                                                                                                                            auto a = ++lexer;
                                                                                                                                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                                            match.hit = true;
                                                                                                                                                                                        }
                                                                                                                                                                                        if (match.hit)
                                                                                                                                                                                        {
                                                                                                                                                                                            {
                                                                                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                                #endif
                                                                                                                                                                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("[]"));
                                                                                                                                                                                            }
                                                                                                                                                                                        }
                                                                                                                                                                                        *parentMatch44 = match;
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch43 = match;
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch42 = match;
                                                                                                                                                                            }
                                                                                                                                                                            *parentMatch41 = match;
                                                                                                                                                                            if (!match.hit)
                                                                                                                                                                            {
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                soul::parser::Match* parentMatch45 = &match;
                                                                                                                                                                                lexer.SetPos(save);
                                                                                                                                                                                {
                                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                                    soul::parser::Match* parentMatch46 = &match;
                                                                                                                                                                                    {
                                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                                        if (*lexer == LPAREN)
                                                                                                                                                                                        {
                                                                                                                                                                                            auto a = ++lexer;
                                                                                                                                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                                            match.hit = true;
                                                                                                                                                                                        }
                                                                                                                                                                                        *parentMatch46 = match;
                                                                                                                                                                                    }
                                                                                                                                                                                    if (match.hit)
                                                                                                                                                                                    {
                                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                                        soul::parser::Match* parentMatch47 = &match;
                                                                                                                                                                                        {
                                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                                            soul::parser::Match* parentMatch48 = &match;
                                                                                                                                                                                            {
                                                                                                                                                                                                std::int64_t pos = lexer.GetPos();
                                                                                                                                                                                                soul::parser::Match match(false);
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
                                                                                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                                        #endif
                                                                                                                                                                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("()"));
                                                                                                                                                                                                    }
                                                                                                                                                                                                }
                                                                                                                                                                                                *parentMatch48 = match;
                                                                                                                                                                                            }
                                                                                                                                                                                            *parentMatch47 = match;
                                                                                                                                                                                        }
                                                                                                                                                                                        *parentMatch46 = match;
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch45 = match;
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch41 = match;
                                                                                                                                                                            }
                                                                                                                                                                        }
                                                                                                                                                                        *parentMatch40 = match;
                                                                                                                                                                        if (!match.hit)
                                                                                                                                                                        {
                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                            soul::parser::Match* parentMatch49 = &match;
                                                                                                                                                                            lexer.SetPos(save);
                                                                                                                                                                            {
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                soul::parser::Match* parentMatch50 = &match;
                                                                                                                                                                                {
                                                                                                                                                                                    std::int64_t pos = lexer.GetPos();
                                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                                    if (*lexer == ARROW_STAR)
                                                                                                                                                                                    {
                                                                                                                                                                                        auto a = ++lexer;
                                                                                                                                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                                        match.hit = true;
                                                                                                                                                                                    }
                                                                                                                                                                                    if (match.hit)
                                                                                                                                                                                    {
                                                                                                                                                                                        {
                                                                                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                            #endif
                                                                                                                                                                                            return soul::parser::Match(true, new soul::parser::Value<std::string>("->*"));
                                                                                                                                                                                        }
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch50 = match;
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch49 = match;
                                                                                                                                                                            }
                                                                                                                                                                            *parentMatch40 = match;
                                                                                                                                                                        }
                                                                                                                                                                    }
                                                                                                                                                                    *parentMatch39 = match;
                                                                                                                                                                    if (!match.hit)
                                                                                                                                                                    {
                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                        soul::parser::Match* parentMatch51 = &match;
                                                                                                                                                                        lexer.SetPos(save);
                                                                                                                                                                        {
                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                            soul::parser::Match* parentMatch52 = &match;
                                                                                                                                                                            {
                                                                                                                                                                                std::int64_t pos = lexer.GetPos();
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                if (*lexer == ARROW)
                                                                                                                                                                                {
                                                                                                                                                                                    auto a = ++lexer;
                                                                                                                                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                                    match.hit = true;
                                                                                                                                                                                }
                                                                                                                                                                                if (match.hit)
                                                                                                                                                                                {
                                                                                                                                                                                    {
                                                                                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                        #endif
                                                                                                                                                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("->"));
                                                                                                                                                                                    }
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch52 = match;
                                                                                                                                                                            }
                                                                                                                                                                            *parentMatch51 = match;
                                                                                                                                                                        }
                                                                                                                                                                        *parentMatch39 = match;
                                                                                                                                                                    }
                                                                                                                                                                }
                                                                                                                                                                *parentMatch38 = match;
                                                                                                                                                                if (!match.hit)
                                                                                                                                                                {
                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                    soul::parser::Match* parentMatch53 = &match;
                                                                                                                                                                    lexer.SetPos(save);
                                                                                                                                                                    {
                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                        soul::parser::Match* parentMatch54 = &match;
                                                                                                                                                                        {
                                                                                                                                                                            std::int64_t pos = lexer.GetPos();
                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                            if (*lexer == COMMA)
                                                                                                                                                                            {
                                                                                                                                                                                auto a = ++lexer;
                                                                                                                                                                                if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                                match.hit = true;
                                                                                                                                                                            }
                                                                                                                                                                            if (match.hit)
                                                                                                                                                                            {
                                                                                                                                                                                {
                                                                                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                    #endif
                                                                                                                                                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(","));
                                                                                                                                                                                }
                                                                                                                                                                            }
                                                                                                                                                                            *parentMatch54 = match;
                                                                                                                                                                        }
                                                                                                                                                                        *parentMatch53 = match;
                                                                                                                                                                    }
                                                                                                                                                                    *parentMatch38 = match;
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                            *parentMatch37 = match;
                                                                                                                                                            if (!match.hit)
                                                                                                                                                            {
                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                soul::parser::Match* parentMatch55 = &match;
                                                                                                                                                                lexer.SetPos(save);
                                                                                                                                                                {
                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                    soul::parser::Match* parentMatch56 = &match;
                                                                                                                                                                    {
                                                                                                                                                                        std::int64_t pos = lexer.GetPos();
                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                        if (*lexer == MINUS_MINUS)
                                                                                                                                                                        {
                                                                                                                                                                            auto a = ++lexer;
                                                                                                                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                            match.hit = true;
                                                                                                                                                                        }
                                                                                                                                                                        if (match.hit)
                                                                                                                                                                        {
                                                                                                                                                                            {
                                                                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                #endif
                                                                                                                                                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("--"));
                                                                                                                                                                            }
                                                                                                                                                                        }
                                                                                                                                                                        *parentMatch56 = match;
                                                                                                                                                                    }
                                                                                                                                                                    *parentMatch55 = match;
                                                                                                                                                                }
                                                                                                                                                                *parentMatch37 = match;
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                        *parentMatch36 = match;
                                                                                                                                                        if (!match.hit)
                                                                                                                                                        {
                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                            soul::parser::Match* parentMatch57 = &match;
                                                                                                                                                            lexer.SetPos(save);
                                                                                                                                                            {
                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                soul::parser::Match* parentMatch58 = &match;
                                                                                                                                                                {
                                                                                                                                                                    std::int64_t pos = lexer.GetPos();
                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                    if (*lexer == PLUS_PLUS)
                                                                                                                                                                    {
                                                                                                                                                                        auto a = ++lexer;
                                                                                                                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                        match.hit = true;
                                                                                                                                                                    }
                                                                                                                                                                    if (match.hit)
                                                                                                                                                                    {
                                                                                                                                                                        {
                                                                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                            #endif
                                                                                                                                                                            return soul::parser::Match(true, new soul::parser::Value<std::string>("++"));
                                                                                                                                                                        }
                                                                                                                                                                    }
                                                                                                                                                                    *parentMatch58 = match;
                                                                                                                                                                }
                                                                                                                                                                *parentMatch57 = match;
                                                                                                                                                            }
                                                                                                                                                            *parentMatch36 = match;
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                    *parentMatch35 = match;
                                                                                                                                                    if (!match.hit)
                                                                                                                                                    {
                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                        soul::parser::Match* parentMatch59 = &match;
                                                                                                                                                        lexer.SetPos(save);
                                                                                                                                                        {
                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                            soul::parser::Match* parentMatch60 = &match;
                                                                                                                                                            {
                                                                                                                                                                std::int64_t pos = lexer.GetPos();
                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                if (*lexer == DISJUNCTION)
                                                                                                                                                                {
                                                                                                                                                                    auto a = ++lexer;
                                                                                                                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                    match.hit = true;
                                                                                                                                                                }
                                                                                                                                                                if (match.hit)
                                                                                                                                                                {
                                                                                                                                                                    {
                                                                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                        #endif
                                                                                                                                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("||"));
                                                                                                                                                                    }
                                                                                                                                                                }
                                                                                                                                                                *parentMatch60 = match;
                                                                                                                                                            }
                                                                                                                                                            *parentMatch59 = match;
                                                                                                                                                        }
                                                                                                                                                        *parentMatch35 = match;
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                *parentMatch34 = match;
                                                                                                                                                if (!match.hit)
                                                                                                                                                {
                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                    soul::parser::Match* parentMatch61 = &match;
                                                                                                                                                    lexer.SetPos(save);
                                                                                                                                                    {
                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                        soul::parser::Match* parentMatch62 = &match;
                                                                                                                                                        {
                                                                                                                                                            std::int64_t pos = lexer.GetPos();
                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                            if (*lexer == AMP_AMP)
                                                                                                                                                            {
                                                                                                                                                                auto a = ++lexer;
                                                                                                                                                                if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                                match.hit = true;
                                                                                                                                                            }
                                                                                                                                                            if (match.hit)
                                                                                                                                                            {
                                                                                                                                                                {
                                                                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                    #endif
                                                                                                                                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("&&"));
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                            *parentMatch62 = match;
                                                                                                                                                        }
                                                                                                                                                        *parentMatch61 = match;
                                                                                                                                                    }
                                                                                                                                                    *parentMatch34 = match;
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                            *parentMatch33 = match;
                                                                                                                                            if (!match.hit)
                                                                                                                                            {
                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                soul::parser::Match* parentMatch63 = &match;
                                                                                                                                                lexer.SetPos(save);
                                                                                                                                                {
                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                    soul::parser::Match* parentMatch64 = &match;
                                                                                                                                                    {
                                                                                                                                                        std::int64_t pos = lexer.GetPos();
                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                        if (*lexer == LEQ)
                                                                                                                                                        {
                                                                                                                                                            auto a = ++lexer;
                                                                                                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                            match.hit = true;
                                                                                                                                                        }
                                                                                                                                                        if (match.hit)
                                                                                                                                                        {
                                                                                                                                                            {
                                                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                #endif
                                                                                                                                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("<="));
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                        *parentMatch64 = match;
                                                                                                                                                    }
                                                                                                                                                    *parentMatch63 = match;
                                                                                                                                                }
                                                                                                                                                *parentMatch33 = match;
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                        *parentMatch32 = match;
                                                                                                                                        if (!match.hit)
                                                                                                                                        {
                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                            soul::parser::Match* parentMatch65 = &match;
                                                                                                                                            lexer.SetPos(save);
                                                                                                                                            {
                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                soul::parser::Match* parentMatch66 = &match;
                                                                                                                                                {
                                                                                                                                                    std::int64_t pos = lexer.GetPos();
                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                    if (*lexer == GEQ)
                                                                                                                                                    {
                                                                                                                                                        auto a = ++lexer;
                                                                                                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                        match.hit = true;
                                                                                                                                                    }
                                                                                                                                                    if (match.hit)
                                                                                                                                                    {
                                                                                                                                                        {
                                                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                            #endif
                                                                                                                                                            return soul::parser::Match(true, new soul::parser::Value<std::string>(">="));
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                    *parentMatch66 = match;
                                                                                                                                                }
                                                                                                                                                *parentMatch65 = match;
                                                                                                                                            }
                                                                                                                                            *parentMatch32 = match;
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                    *parentMatch31 = match;
                                                                                                                                    if (!match.hit)
                                                                                                                                    {
                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                        soul::parser::Match* parentMatch67 = &match;
                                                                                                                                        lexer.SetPos(save);
                                                                                                                                        {
                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                            soul::parser::Match* parentMatch68 = &match;
                                                                                                                                            {
                                                                                                                                                std::int64_t pos = lexer.GetPos();
                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                if (*lexer == NEQ)
                                                                                                                                                {
                                                                                                                                                    auto a = ++lexer;
                                                                                                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                    match.hit = true;
                                                                                                                                                }
                                                                                                                                                if (match.hit)
                                                                                                                                                {
                                                                                                                                                    {
                                                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                        #endif
                                                                                                                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("!="));
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                *parentMatch68 = match;
                                                                                                                                            }
                                                                                                                                            *parentMatch67 = match;
                                                                                                                                        }
                                                                                                                                        *parentMatch31 = match;
                                                                                                                                    }
                                                                                                                                }
                                                                                                                                *parentMatch30 = match;
                                                                                                                                if (!match.hit)
                                                                                                                                {
                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                    soul::parser::Match* parentMatch69 = &match;
                                                                                                                                    lexer.SetPos(save);
                                                                                                                                    {
                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                        soul::parser::Match* parentMatch70 = &match;
                                                                                                                                        {
                                                                                                                                            std::int64_t pos = lexer.GetPos();
                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                            if (*lexer == EQ)
                                                                                                                                            {
                                                                                                                                                auto a = ++lexer;
                                                                                                                                                if (!a) return std::unexpected<int>(a.error());
                                                                                                                                                match.hit = true;
                                                                                                                                            }
                                                                                                                                            if (match.hit)
                                                                                                                                            {
                                                                                                                                                {
                                                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                    #endif
                                                                                                                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("=="));
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                            *parentMatch70 = match;
                                                                                                                                        }
                                                                                                                                        *parentMatch69 = match;
                                                                                                                                    }
                                                                                                                                    *parentMatch30 = match;
                                                                                                                                }
                                                                                                                            }
                                                                                                                            *parentMatch29 = match;
                                                                                                                            if (!match.hit)
                                                                                                                            {
                                                                                                                                soul::parser::Match match(false);
                                                                                                                                soul::parser::Match* parentMatch71 = &match;
                                                                                                                                lexer.SetPos(save);
                                                                                                                                {
                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                    soul::parser::Match* parentMatch72 = &match;
                                                                                                                                    {
                                                                                                                                        std::int64_t pos = lexer.GetPos();
                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                        if (*lexer == SHIFT_LEFT_ASSIGN)
                                                                                                                                        {
                                                                                                                                            auto a = ++lexer;
                                                                                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                                                                                            match.hit = true;
                                                                                                                                        }
                                                                                                                                        if (match.hit)
                                                                                                                                        {
                                                                                                                                            {
                                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                #endif
                                                                                                                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("<<="));
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                        *parentMatch72 = match;
                                                                                                                                    }
                                                                                                                                    *parentMatch71 = match;
                                                                                                                                }
                                                                                                                                *parentMatch29 = match;
                                                                                                                            }
                                                                                                                        }
                                                                                                                        *parentMatch28 = match;
                                                                                                                        if (!match.hit)
                                                                                                                        {
                                                                                                                            soul::parser::Match match(false);
                                                                                                                            soul::parser::Match* parentMatch73 = &match;
                                                                                                                            lexer.SetPos(save);
                                                                                                                            {
                                                                                                                                soul::parser::Match match(false);
                                                                                                                                soul::parser::Match* parentMatch74 = &match;
                                                                                                                                {
                                                                                                                                    std::int64_t pos = lexer.GetPos();
                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                    if (*lexer == SHIFT_RIGHT_ASSIGN)
                                                                                                                                    {
                                                                                                                                        auto a = ++lexer;
                                                                                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                                                                                        match.hit = true;
                                                                                                                                    }
                                                                                                                                    if (match.hit)
                                                                                                                                    {
                                                                                                                                        {
                                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                            #endif
                                                                                                                                            return soul::parser::Match(true, new soul::parser::Value<std::string>(">>="));
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                    *parentMatch74 = match;
                                                                                                                                }
                                                                                                                                *parentMatch73 = match;
                                                                                                                            }
                                                                                                                            *parentMatch28 = match;
                                                                                                                        }
                                                                                                                    }
                                                                                                                    *parentMatch27 = match;
                                                                                                                    if (!match.hit)
                                                                                                                    {
                                                                                                                        soul::parser::Match match(false);
                                                                                                                        soul::parser::Match* parentMatch75 = &match;
                                                                                                                        lexer.SetPos(save);
                                                                                                                        {
                                                                                                                            soul::parser::Match match(false);
                                                                                                                            soul::parser::Match* parentMatch76 = &match;
                                                                                                                            {
                                                                                                                                std::int64_t pos = lexer.GetPos();
                                                                                                                                soul::parser::Match match(false);
                                                                                                                                if (*lexer == SHIFT_LEFT)
                                                                                                                                {
                                                                                                                                    auto a = ++lexer;
                                                                                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                                                                                    match.hit = true;
                                                                                                                                }
                                                                                                                                if (match.hit)
                                                                                                                                {
                                                                                                                                    {
                                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                        #endif
                                                                                                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("<<"));
                                                                                                                                    }
                                                                                                                                }
                                                                                                                                *parentMatch76 = match;
                                                                                                                            }
                                                                                                                            *parentMatch75 = match;
                                                                                                                        }
                                                                                                                        *parentMatch27 = match;
                                                                                                                    }
                                                                                                                }
                                                                                                                *parentMatch26 = match;
                                                                                                                if (!match.hit)
                                                                                                                {
                                                                                                                    soul::parser::Match match(false);
                                                                                                                    soul::parser::Match* parentMatch77 = &match;
                                                                                                                    lexer.SetPos(save);
                                                                                                                    {
                                                                                                                        soul::parser::Match match(false);
                                                                                                                        soul::parser::Match* parentMatch78 = &match;
                                                                                                                        {
                                                                                                                            std::int64_t pos = lexer.GetPos();
                                                                                                                            soul::parser::Match match(false);
                                                                                                                            if (*lexer == SHIFT_RIGHT)
                                                                                                                            {
                                                                                                                                auto a = ++lexer;
                                                                                                                                if (!a) return std::unexpected<int>(a.error());
                                                                                                                                match.hit = true;
                                                                                                                            }
                                                                                                                            if (match.hit)
                                                                                                                            {
                                                                                                                                {
                                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                    #endif
                                                                                                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(">>"));
                                                                                                                                }
                                                                                                                            }
                                                                                                                            *parentMatch78 = match;
                                                                                                                        }
                                                                                                                        *parentMatch77 = match;
                                                                                                                    }
                                                                                                                    *parentMatch26 = match;
                                                                                                                }
                                                                                                            }
                                                                                                            *parentMatch25 = match;
                                                                                                            if (!match.hit)
                                                                                                            {
                                                                                                                soul::parser::Match match(false);
                                                                                                                soul::parser::Match* parentMatch79 = &match;
                                                                                                                lexer.SetPos(save);
                                                                                                                {
                                                                                                                    soul::parser::Match match(false);
                                                                                                                    soul::parser::Match* parentMatch80 = &match;
                                                                                                                    {
                                                                                                                        std::int64_t pos = lexer.GetPos();
                                                                                                                        soul::parser::Match match(false);
                                                                                                                        if (*lexer == OR_ASSIGN)
                                                                                                                        {
                                                                                                                            auto a = ++lexer;
                                                                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                                                                            match.hit = true;
                                                                                                                        }
                                                                                                                        if (match.hit)
                                                                                                                        {
                                                                                                                            {
                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                #endif
                                                                                                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("|="));
                                                                                                                            }
                                                                                                                        }
                                                                                                                        *parentMatch80 = match;
                                                                                                                    }
                                                                                                                    *parentMatch79 = match;
                                                                                                                }
                                                                                                                *parentMatch25 = match;
                                                                                                            }
                                                                                                        }
                                                                                                        *parentMatch24 = match;
                                                                                                        if (!match.hit)
                                                                                                        {
                                                                                                            soul::parser::Match match(false);
                                                                                                            soul::parser::Match* parentMatch81 = &match;
                                                                                                            lexer.SetPos(save);
                                                                                                            {
                                                                                                                soul::parser::Match match(false);
                                                                                                                soul::parser::Match* parentMatch82 = &match;
                                                                                                                {
                                                                                                                    std::int64_t pos = lexer.GetPos();
                                                                                                                    soul::parser::Match match(false);
                                                                                                                    if (*lexer == AND_ASSIGN)
                                                                                                                    {
                                                                                                                        auto a = ++lexer;
                                                                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                                                                        match.hit = true;
                                                                                                                    }
                                                                                                                    if (match.hit)
                                                                                                                    {
                                                                                                                        {
                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                            #endif
                                                                                                                            return soul::parser::Match(true, new soul::parser::Value<std::string>("&="));
                                                                                                                        }
                                                                                                                    }
                                                                                                                    *parentMatch82 = match;
                                                                                                                }
                                                                                                                *parentMatch81 = match;
                                                                                                            }
                                                                                                            *parentMatch24 = match;
                                                                                                        }
                                                                                                    }
                                                                                                    *parentMatch23 = match;
                                                                                                    if (!match.hit)
                                                                                                    {
                                                                                                        soul::parser::Match match(false);
                                                                                                        soul::parser::Match* parentMatch83 = &match;
                                                                                                        lexer.SetPos(save);
                                                                                                        {
                                                                                                            soul::parser::Match match(false);
                                                                                                            soul::parser::Match* parentMatch84 = &match;
                                                                                                            {
                                                                                                                std::int64_t pos = lexer.GetPos();
                                                                                                                soul::parser::Match match(false);
                                                                                                                if (*lexer == XOR_ASSIGN)
                                                                                                                {
                                                                                                                    auto a = ++lexer;
                                                                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                                                                    match.hit = true;
                                                                                                                }
                                                                                                                if (match.hit)
                                                                                                                {
                                                                                                                    {
                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                        #endif
                                                                                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("^="));
                                                                                                                    }
                                                                                                                }
                                                                                                                *parentMatch84 = match;
                                                                                                            }
                                                                                                            *parentMatch83 = match;
                                                                                                        }
                                                                                                        *parentMatch23 = match;
                                                                                                    }
                                                                                                }
                                                                                                *parentMatch22 = match;
                                                                                                if (!match.hit)
                                                                                                {
                                                                                                    soul::parser::Match match(false);
                                                                                                    soul::parser::Match* parentMatch85 = &match;
                                                                                                    lexer.SetPos(save);
                                                                                                    {
                                                                                                        soul::parser::Match match(false);
                                                                                                        soul::parser::Match* parentMatch86 = &match;
                                                                                                        {
                                                                                                            std::int64_t pos = lexer.GetPos();
                                                                                                            soul::parser::Match match(false);
                                                                                                            if (*lexer == REM_ASSIGN)
                                                                                                            {
                                                                                                                auto a = ++lexer;
                                                                                                                if (!a) return std::unexpected<int>(a.error());
                                                                                                                match.hit = true;
                                                                                                            }
                                                                                                            if (match.hit)
                                                                                                            {
                                                                                                                {
                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                    #endif
                                                                                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("%="));
                                                                                                                }
                                                                                                            }
                                                                                                            *parentMatch86 = match;
                                                                                                        }
                                                                                                        *parentMatch85 = match;
                                                                                                    }
                                                                                                    *parentMatch22 = match;
                                                                                                }
                                                                                            }
                                                                                            *parentMatch21 = match;
                                                                                            if (!match.hit)
                                                                                            {
                                                                                                soul::parser::Match match(false);
                                                                                                soul::parser::Match* parentMatch87 = &match;
                                                                                                lexer.SetPos(save);
                                                                                                {
                                                                                                    soul::parser::Match match(false);
                                                                                                    soul::parser::Match* parentMatch88 = &match;
                                                                                                    {
                                                                                                        std::int64_t pos = lexer.GetPos();
                                                                                                        soul::parser::Match match(false);
                                                                                                        if (*lexer == DIV_ASSIGN)
                                                                                                        {
                                                                                                            auto a = ++lexer;
                                                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                                                            match.hit = true;
                                                                                                        }
                                                                                                        if (match.hit)
                                                                                                        {
                                                                                                            {
                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                #endif
                                                                                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("/="));
                                                                                                            }
                                                                                                        }
                                                                                                        *parentMatch88 = match;
                                                                                                    }
                                                                                                    *parentMatch87 = match;
                                                                                                }
                                                                                                *parentMatch21 = match;
                                                                                            }
                                                                                        }
                                                                                        *parentMatch20 = match;
                                                                                        if (!match.hit)
                                                                                        {
                                                                                            soul::parser::Match match(false);
                                                                                            soul::parser::Match* parentMatch89 = &match;
                                                                                            lexer.SetPos(save);
                                                                                            {
                                                                                                soul::parser::Match match(false);
                                                                                                soul::parser::Match* parentMatch90 = &match;
                                                                                                {
                                                                                                    std::int64_t pos = lexer.GetPos();
                                                                                                    soul::parser::Match match(false);
                                                                                                    if (*lexer == MUL_ASSIGN)
                                                                                                    {
                                                                                                        auto a = ++lexer;
                                                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                                                        match.hit = true;
                                                                                                    }
                                                                                                    if (match.hit)
                                                                                                    {
                                                                                                        {
                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                            #endif
                                                                                                            return soul::parser::Match(true, new soul::parser::Value<std::string>("*="));
                                                                                                        }
                                                                                                    }
                                                                                                    *parentMatch90 = match;
                                                                                                }
                                                                                                *parentMatch89 = match;
                                                                                            }
                                                                                            *parentMatch20 = match;
                                                                                        }
                                                                                    }
                                                                                    *parentMatch19 = match;
                                                                                    if (!match.hit)
                                                                                    {
                                                                                        soul::parser::Match match(false);
                                                                                        soul::parser::Match* parentMatch91 = &match;
                                                                                        lexer.SetPos(save);
                                                                                        {
                                                                                            soul::parser::Match match(false);
                                                                                            soul::parser::Match* parentMatch92 = &match;
                                                                                            {
                                                                                                std::int64_t pos = lexer.GetPos();
                                                                                                soul::parser::Match match(false);
                                                                                                if (*lexer == MINUS_ASSIGN)
                                                                                                {
                                                                                                    auto a = ++lexer;
                                                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                                                    match.hit = true;
                                                                                                }
                                                                                                if (match.hit)
                                                                                                {
                                                                                                    {
                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                        #endif
                                                                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("-="));
                                                                                                    }
                                                                                                }
                                                                                                *parentMatch92 = match;
                                                                                            }
                                                                                            *parentMatch91 = match;
                                                                                        }
                                                                                        *parentMatch19 = match;
                                                                                    }
                                                                                }
                                                                                *parentMatch18 = match;
                                                                                if (!match.hit)
                                                                                {
                                                                                    soul::parser::Match match(false);
                                                                                    soul::parser::Match* parentMatch93 = &match;
                                                                                    lexer.SetPos(save);
                                                                                    {
                                                                                        soul::parser::Match match(false);
                                                                                        soul::parser::Match* parentMatch94 = &match;
                                                                                        {
                                                                                            std::int64_t pos = lexer.GetPos();
                                                                                            soul::parser::Match match(false);
                                                                                            if (*lexer == PLUS_ASSIGN)
                                                                                            {
                                                                                                auto a = ++lexer;
                                                                                                if (!a) return std::unexpected<int>(a.error());
                                                                                                match.hit = true;
                                                                                            }
                                                                                            if (match.hit)
                                                                                            {
                                                                                                {
                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                    #endif
                                                                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("+="));
                                                                                                }
                                                                                            }
                                                                                            *parentMatch94 = match;
                                                                                        }
                                                                                        *parentMatch93 = match;
                                                                                    }
                                                                                    *parentMatch18 = match;
                                                                                }
                                                                            }
                                                                            *parentMatch17 = match;
                                                                            if (!match.hit)
                                                                            {
                                                                                soul::parser::Match match(false);
                                                                                soul::parser::Match* parentMatch95 = &match;
                                                                                lexer.SetPos(save);
                                                                                {
                                                                                    soul::parser::Match match(false);
                                                                                    soul::parser::Match* parentMatch96 = &match;
                                                                                    {
                                                                                        std::int64_t pos = lexer.GetPos();
                                                                                        soul::parser::Match match(false);
                                                                                        if (*lexer == LANGLE)
                                                                                        {
                                                                                            auto a = ++lexer;
                                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                                            match.hit = true;
                                                                                        }
                                                                                        if (match.hit)
                                                                                        {
                                                                                            {
                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                #endif
                                                                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("<"));
                                                                                            }
                                                                                        }
                                                                                        *parentMatch96 = match;
                                                                                    }
                                                                                    *parentMatch95 = match;
                                                                                }
                                                                                *parentMatch17 = match;
                                                                            }
                                                                        }
                                                                        *parentMatch16 = match;
                                                                        if (!match.hit)
                                                                        {
                                                                            soul::parser::Match match(false);
                                                                            soul::parser::Match* parentMatch97 = &match;
                                                                            lexer.SetPos(save);
                                                                            {
                                                                                soul::parser::Match match(false);
                                                                                soul::parser::Match* parentMatch98 = &match;
                                                                                {
                                                                                    std::int64_t pos = lexer.GetPos();
                                                                                    soul::parser::Match match(false);
                                                                                    if (*lexer == RANGLE)
                                                                                    {
                                                                                        auto a = ++lexer;
                                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                                        match.hit = true;
                                                                                    }
                                                                                    if (match.hit)
                                                                                    {
                                                                                        {
                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                            #endif
                                                                                            return soul::parser::Match(true, new soul::parser::Value<std::string>(">"));
                                                                                        }
                                                                                    }
                                                                                    *parentMatch98 = match;
                                                                                }
                                                                                *parentMatch97 = match;
                                                                            }
                                                                            *parentMatch16 = match;
                                                                        }
                                                                    }
                                                                    *parentMatch15 = match;
                                                                    if (!match.hit)
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch99 = &match;
                                                                        lexer.SetPos(save);
                                                                        {
                                                                            soul::parser::Match match(false);
                                                                            soul::parser::Match* parentMatch100 = &match;
                                                                            {
                                                                                std::int64_t pos = lexer.GetPos();
                                                                                soul::parser::Match match(false);
                                                                                if (*lexer == ASSIGN)
                                                                                {
                                                                                    auto a = ++lexer;
                                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                                    match.hit = true;
                                                                                }
                                                                                if (match.hit)
                                                                                {
                                                                                    {
                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                        #endif
                                                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("="));
                                                                                    }
                                                                                }
                                                                                *parentMatch100 = match;
                                                                            }
                                                                            *parentMatch99 = match;
                                                                        }
                                                                        *parentMatch15 = match;
                                                                    }
                                                                }
                                                                *parentMatch14 = match;
                                                                if (!match.hit)
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch101 = &match;
                                                                    lexer.SetPos(save);
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch102 = &match;
                                                                        {
                                                                            std::int64_t pos = lexer.GetPos();
                                                                            soul::parser::Match match(false);
                                                                            if (*lexer == EXCLAMATION)
                                                                            {
                                                                                auto a = ++lexer;
                                                                                if (!a) return std::unexpected<int>(a.error());
                                                                                match.hit = true;
                                                                            }
                                                                            if (match.hit)
                                                                            {
                                                                                {
                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                    #endif
                                                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("!"));
                                                                                }
                                                                            }
                                                                            *parentMatch102 = match;
                                                                        }
                                                                        *parentMatch101 = match;
                                                                    }
                                                                    *parentMatch14 = match;
                                                                }
                                                            }
                                                            *parentMatch13 = match;
                                                            if (!match.hit)
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch103 = &match;
                                                                lexer.SetPos(save);
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch104 = &match;
                                                                    {
                                                                        std::int64_t pos = lexer.GetPos();
                                                                        soul::parser::Match match(false);
                                                                        if (*lexer == TILDE)
                                                                        {
                                                                            auto a = ++lexer;
                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                            match.hit = true;
                                                                        }
                                                                        if (match.hit)
                                                                        {
                                                                            {
                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                #endif
                                                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("~"));
                                                                            }
                                                                        }
                                                                        *parentMatch104 = match;
                                                                    }
                                                                    *parentMatch103 = match;
                                                                }
                                                                *parentMatch13 = match;
                                                            }
                                                        }
                                                        *parentMatch12 = match;
                                                        if (!match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch105 = &match;
                                                            lexer.SetPos(save);
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch106 = &match;
                                                                {
                                                                    std::int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match(false);
                                                                    if (*lexer == AMP)
                                                                    {
                                                                        auto a = ++lexer;
                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                        match.hit = true;
                                                                    }
                                                                    if (match.hit)
                                                                    {
                                                                        {
                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                            #endif
                                                                            return soul::parser::Match(true, new soul::parser::Value<std::string>("&"));
                                                                        }
                                                                    }
                                                                    *parentMatch106 = match;
                                                                }
                                                                *parentMatch105 = match;
                                                            }
                                                            *parentMatch12 = match;
                                                        }
                                                    }
                                                    *parentMatch11 = match;
                                                    if (!match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch107 = &match;
                                                        lexer.SetPos(save);
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch108 = &match;
                                                            {
                                                                std::int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match(false);
                                                                if (*lexer == CARET)
                                                                {
                                                                    auto a = ++lexer;
                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                    match.hit = true;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    {
                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                        #endif
                                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("^"));
                                                                    }
                                                                }
                                                                *parentMatch108 = match;
                                                            }
                                                            *parentMatch107 = match;
                                                        }
                                                        *parentMatch11 = match;
                                                    }
                                                }
                                                *parentMatch10 = match;
                                                if (!match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch109 = &match;
                                                    lexer.SetPos(save);
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch110 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match(false);
                                                            if (*lexer == PIPE)
                                                            {
                                                                auto a = ++lexer;
                                                                if (!a) return std::unexpected<int>(a.error());
                                                                match.hit = true;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                {
                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                    #endif
                                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("|"));
                                                                }
                                                            }
                                                            *parentMatch110 = match;
                                                        }
                                                        *parentMatch109 = match;
                                                    }
                                                    *parentMatch10 = match;
                                                }
                                            }
                                            *parentMatch9 = match;
                                            if (!match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch111 = &match;
                                                lexer.SetPos(save);
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch112 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == REM)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            {
                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                #endif
                                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("%"));
                                                            }
                                                        }
                                                        *parentMatch112 = match;
                                                    }
                                                    *parentMatch111 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                        }
                                        *parentMatch8 = match;
                                        if (!match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch113 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch114 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == DIV)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        {
                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                            #endif
                                                            return soul::parser::Match(true, new soul::parser::Value<std::string>("/"));
                                                        }
                                                    }
                                                    *parentMatch114 = match;
                                                }
                                                *parentMatch113 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                    }
                                    *parentMatch7 = match;
                                    if (!match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch115 = &match;
                                        lexer.SetPos(save);
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch116 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
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
                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                        #endif
                                                        return soul::parser::Match(true, new soul::parser::Value<std::string>("*"));
                                                    }
                                                }
                                                *parentMatch116 = match;
                                            }
                                            *parentMatch115 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                }
                                *parentMatch6 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch117 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch118 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
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
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                    #endif
                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("-"));
                                                }
                                            }
                                            *parentMatch118 = match;
                                        }
                                        *parentMatch117 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch119 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch120 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
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
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                #endif
                                                return soul::parser::Match(true, new soul::parser::Value<std::string>("+"));
                                            }
                                        }
                                        *parentMatch120 = match;
                                    }
                                    *parentMatch119 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
                        if (!match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch121 = &match;
                            lexer.SetPos(save);
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch122 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch123 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == NEW)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch123 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch124 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            if (*lexer == LBRACKET)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            *parentMatch124 = match;
                                        }
                                        *parentMatch123 = match;
                                    }
                                    *parentMatch122 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch125 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch126 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == RBRACKET)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                    #endif
                                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(" new[]"));
                                                }
                                            }
                                            *parentMatch126 = match;
                                        }
                                        *parentMatch125 = match;
                                    }
                                    *parentMatch122 = match;
                                }
                                *parentMatch121 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch127 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch128 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch129 = &match;
                                {
                                    soul::parser::Match match(false);
                                    if (*lexer == DELETE)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    *parentMatch129 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch130 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        if (*lexer == LBRACKET)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch130 = match;
                                    }
                                    *parentMatch129 = match;
                                }
                                *parentMatch128 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch131 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch132 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == RBRACKET)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                #endif
                                                return soul::parser::Match(true, new soul::parser::Value<std::string>(" delete[]"));
                                            }
                                        }
                                        *parentMatch132 = match;
                                    }
                                    *parentMatch131 = match;
                                }
                                *parentMatch128 = match;
                            }
                            *parentMatch127 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch133 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch134 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == NEW)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(" new"));
                                }
                            }
                            *parentMatch134 = match;
                        }
                        *parentMatch133 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch135 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch136 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == DELETE)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                #endif
                                return soul::parser::Match(true, new soul::parser::Value<std::string>(" delete"));
                            }
                        }
                        *parentMatch136 = match;
                    }
                    *parentMatch135 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
        else soul::lexer::WriteFailureToLog(lexer, "Operator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct ExpressionParser<soul::lexer::Lexer<soul::lex::slg::SlgLexer<char32_t>, char32_t>>;
template struct ExpressionParser<soul::lexer::Lexer<soul::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul::cpp::expression::parser
