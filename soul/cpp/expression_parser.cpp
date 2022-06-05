
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp/expression_parser.parser' using soul parser generator spg version 4.0.0

module soul.cpp.expression.parser;

import util;
import soul.ast.spg;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.punctuation.token;
import soul.cpp.declarator.parser;
import soul.cpp.declaration.parser;
import soul.cpp.literal.parser;
import soul.cpp.identifier.parser;
import soul.lex.slg;
import soul.lex.spg;

using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::punctuation::token;
using namespace soul::cpp::declarator::parser;
using namespace soul::cpp::declaration::parser;
using namespace soul::cpp::literal::parser;
using namespace soul::cpp::identifier::parser;
using namespace soul::lex::slg;
using namespace soul::lex::spg;

namespace soul::cpp::expression::parser {

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::Expression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Expression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688193);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer);
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
                            int64_t save = lexer.GetPos();
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
                                            ++lexer;
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer);
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), soul::ast::cpp::Operator::comma, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ConstantExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConstantExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688194);
    std::unique_ptr<soul::ast::cpp::Node> expr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer);
        expr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstantExpression");
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AssignmentExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AssignmentExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688195);
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
    std::unique_ptr<soul::ast::cpp::Node> conditionalExpr;
    std::unique_ptr<soul::ast::cpp::Node> throwExpr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match = ExpressionParser<Lexer>::LogicalOrExpression(lexer);
                    left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match = ExpressionParser<Lexer>::AssignmentOp(lexer);
                        op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
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
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch7 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer);
                            right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                            if (match.hit)
                            {
                                *parentMatch7 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, "AssignmentExpression");
                            }
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentExpression");
                                #endif SOUL_PARSER_DEBUG_SUPPORT
                                return soul::parser::Match(true, new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), op->value, left.release(), right.release()));
                            }
                        }
                        *parentMatch6 = match;
                    }
                    *parentMatch5 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
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
                        soul::parser::Match match = ExpressionParser<Lexer>::ConditionalExpression(lexer);
                        conditionalExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentExpression");
                                #endif SOUL_PARSER_DEBUG_SUPPORT
                                return soul::parser::Match(true, conditionalExpr.release());
                            }
                        }
                        *parentMatch9 = match;
                    }
                    *parentMatch8 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch10 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch11 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::ThrowExpression(lexer);
                    throwExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentExpression");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
                            return soul::parser::Match(true, throwExpr.release());
                        }
                    }
                    *parentMatch11 = match;
                }
                *parentMatch10 = match;
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AssignmentOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AssignmentOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688196);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::assign));
                }
            }
            break;
        }
        case MUL_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::mulAssign));
                }
            }
            break;
        }
        case DIV_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::divAssign));
                }
            }
            break;
        }
        case REM_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::remAssign));
                }
            }
            break;
        }
        case PLUS_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::plusAssign));
                }
            }
            break;
        }
        case MINUS_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::minusAssign));
                }
            }
            break;
        }
        case SHIFT_LEFT_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftLeftAssign));
                }
            }
            break;
        }
        case SHIFT_RIGHT_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftRightAssign));
                }
            }
            break;
        }
        case AND_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::andAssign));
                }
            }
            break;
        }
        case XOR_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::xorAssign));
                }
            }
            break;
        }
        case OR_ASSIGN:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::orAssign));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
        else soul::lexer::WriteFailureToLog(lexer, "AssignmentOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ConditionalExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConditionalExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688197);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> thenExpr;
    std::unique_ptr<soul::ast::cpp::Node> elseExpr;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::LogicalOrExpression(lexer);
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
                    int64_t save = lexer.GetPos();
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
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        *parentMatch9 = match;
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer);
                                                thenExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    *parentMatch11 = match;
                                                }
                                                else
                                                {
                                                    lexer.ThrowExpectationFailure(pos, "Expression");
                                                }
                                            }
                                            *parentMatch10 = match;
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
                                        if (*lexer == COLON)
                                        {
                                            ++lexer;
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch13 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch14 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(true);
                                        soul::parser::Match* parentMatch15 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer);
                                            elseExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                *parentMatch15 = match;
                                            }
                                            else
                                            {
                                                lexer.ThrowExpectationFailure(pos, "AssignmentExpression");
                                            }
                                        }
                                        if (match.hit)
                                        {
                                            expr.reset(new soul::ast::cpp::ConditionalNode(lexer.GetSourcePos(pos), expr.release(), thenExpr.release(), elseExpr.release()));
                                        }
                                        *parentMatch14 = match;
                                    }
                                    *parentMatch13 = match;
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ThrowExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ThrowExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688198);
    std::unique_ptr<soul::ast::cpp::Node> exception;
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
                if (*lexer == THROW)
                {
                    ++lexer;
                    match.hit = true;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match(true);
                    int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer);
                        exception.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                        if (match.hit)
                        {
                            *parentMatch4 = match;
                        }
                        else
                        {
                            lexer.SetPos(save);
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
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ThrowExpression");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::ast::cpp::ThrowExprNode(lexer.GetSourcePos(pos), exception.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ThrowExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ThrowExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::LogicalOrExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LogicalOrExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688199);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::LogicalAndExpression(lexer);
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
                            int64_t save = lexer.GetPos();
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
                                            ++lexer;
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<Lexer>::LogicalAndExpression(lexer);
                                                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "LogicalAndExpression");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), soul::ast::cpp::Operator::or_, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::LogicalAndExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LogicalAndExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688200);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::InclusiveOrExpression(lexer);
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
                            int64_t save = lexer.GetPos();
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
                                            ++lexer;
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<Lexer>::InclusiveOrExpression(lexer);
                                                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "InclusiveOrExpression");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), soul::ast::cpp::Operator::and_, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::InclusiveOrExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "InclusiveOrExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688201);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::ExclusiveOrExpression(lexer);
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
                            int64_t save = lexer.GetPos();
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
                                            ++lexer;
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::ExclusiveOrExpression(lexer);
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), soul::ast::cpp::Operator::bitor_, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ExclusiveOrExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ExclusiveOrExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688202);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::AndExpression(lexer);
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
                            int64_t save = lexer.GetPos();
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
                                            ++lexer;
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<Lexer>::AndExpression(lexer);
                                                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "AndExpression");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), soul::ast::cpp::Operator::bitxor, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AndExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AndExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688203);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::EqualityExpression(lexer);
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
                            int64_t save = lexer.GetPos();
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
                                            ++lexer;
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<Lexer>::EqualityExpression(lexer);
                                                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "EqualityExpression");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), soul::ast::cpp::Operator::bitand_, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::EqualityExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "EqualityExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688204);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::RelationalExpression(lexer);
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
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match = ExpressionParser<Lexer>::EqOp(lexer);
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<Lexer>::RelationalExpression(lexer);
                                                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "RelationalExpression");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), op->value, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::EqOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "EqOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688205);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case EQ:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::eq));
                }
            }
            break;
        }
        case NEQ:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::notEq));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqOp");
        else soul::lexer::WriteFailureToLog(lexer, "EqOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::RelationalExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RelationalExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688206);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::ShiftExpression(lexer);
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
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match = ExpressionParser<Lexer>::RelOp(lexer);
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<Lexer>::ShiftExpression(lexer);
                                                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "ShiftExpression");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), op->value, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::RelOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RelOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688207);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case LANGLE:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::less));
                }
            }
            break;
        }
        case RANGLE:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::greater));
                }
            }
            break;
        }
        case LEQ:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::lessOrEq));
                }
            }
            break;
        }
        case GEQ:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::greaterOrEq));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
        else soul::lexer::WriteFailureToLog(lexer, "RelOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ShiftExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ShiftExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688208);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::AdditiveExpression(lexer);
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
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match = ExpressionParser<Lexer>::ShiftOp(lexer);
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<Lexer>::AdditiveExpression(lexer);
                                                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "AdditiveExpression");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), op->value, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ShiftOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ShiftOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688209);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case SHIFT_LEFT:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftLeft));
                }
            }
            break;
        }
        case SHIFT_RIGHT:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftRight));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
        else soul::lexer::WriteFailureToLog(lexer, "ShiftOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AdditiveExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AdditiveExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688210);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::MultiplicativeExpression(lexer);
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
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match = ExpressionParser<Lexer>::AddOp(lexer);
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<Lexer>::MultiplicativeExpression(lexer);
                                                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "MultiplicativeExpression");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), op->value, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AddOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AddOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688211);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case PLUS:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::plus));
                }
            }
            break;
        }
        case MINUS:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::minus));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddOp");
        else soul::lexer::WriteFailureToLog(lexer, "AddOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::MultiplicativeExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MultiplicativeExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688212);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::PmExpression(lexer);
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
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match = ExpressionParser<Lexer>::MulOp(lexer);
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<Lexer>::PmExpression(lexer);
                                                    right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "PmExpression");
                                                    }
                                                }
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), op->value, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::MulOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MulOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688213);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case STAR:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::mul));
                }
            }
            break;
        }
        case DIV:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::div));
                }
            }
            break;
        }
        case REM:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::rem));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
        else soul::lexer::WriteFailureToLog(lexer, "MulOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::PmExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PmExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688214);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> left;
    std::unique_ptr<soul::parser::Value<soul::ast::cpp::Operator>> op;
    std::unique_ptr<soul::ast::cpp::Node> right;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer);
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
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match = ExpressionParser<Lexer>::PmOp(lexer);
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer);
                                                right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), op->value, expr.release(), right.release()));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::PmOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PmOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688215);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case DOT_STAR:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::dotStar));
                }
            }
            break;
        }
        case ARROW_STAR:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmOp");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::arrowStar));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmOp");
        else soul::lexer::WriteFailureToLog(lexer, "PmOp");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::CastExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CastExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688216);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::TypeIdNode> typeId;
    std::unique_ptr<soul::ast::cpp::Node> castExpr;
    std::unique_ptr<soul::ast::cpp::Node> unaryExpr;
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
                int64_t save = lexer.GetPos();
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
                                ++lexer;
                                match.hit = true;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                soul::parser::Match match = DeclaratorParser<Lexer>::TypeId(lexer);
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
                                ++lexer;
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer);
                            castExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                            if (match.hit)
                            {
                                expr.reset(new soul::ast::cpp::CastNode(lexer.GetSourcePos(pos), typeId.release(), castExpr.release()));
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::UnaryExpression(lexer);
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::UnaryExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UnaryExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688217);
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
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    int64_t save = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch9 = &match;
                                        {
                                            int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::PostfixExpression(lexer);
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
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = ExpressionParser<Lexer>::PostCastExpression(lexer);
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
                                                        ++lexer;
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
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match(true);
                                                            soul::parser::Match* parentMatch17 = &match;
                                                            {
                                                                int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = ExpressionParser<Lexer>::UnaryExpression(lexer);
                                                                u1.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    *parentMatch17 = match;
                                                                }
                                                                else
                                                                {
                                                                    lexer.ThrowExpectationFailure(pos, "UnaryExpression");
                                                                }
                                                            }
                                                            if (match.hit)
                                                            {
                                                                expr.reset(new soul::ast::cpp::PreIncrementNode(lexer.GetSourcePos(pos), u1.release()));
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
                                        soul::parser::Match* parentMatch18 = &match;
                                        lexer.SetPos(save);
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch19 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == MINUS_MINUS)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch19 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch20 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch21 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(true);
                                                        soul::parser::Match* parentMatch22 = &match;
                                                        {
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = ExpressionParser<Lexer>::UnaryExpression(lexer);
                                                            u2.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                *parentMatch22 = match;
                                                            }
                                                            else
                                                            {
                                                                lexer.ThrowExpectationFailure(pos, "UnaryExpression");
                                                            }
                                                        }
                                                        if (match.hit)
                                                        {
                                                            expr.reset(new soul::ast::cpp::PreDecrementNode(lexer.GetSourcePos(pos), u2.release()));
                                                        }
                                                        *parentMatch21 = match;
                                                    }
                                                    *parentMatch20 = match;
                                                }
                                                *parentMatch19 = match;
                                            }
                                            *parentMatch18 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                }
                                *parentMatch6 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch23 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch24 = &match;
                                        {
                                            soul::parser::Match match = ExpressionParser<Lexer>::UnaryOperator(lexer);
                                            op.reset(static_cast<soul::parser::Value<soul::ast::cpp::Operator>*>(match.value));
                                            *parentMatch24 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch25 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch26 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(true);
                                                    soul::parser::Match* parentMatch27 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer);
                                                        castExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            *parentMatch27 = match;
                                                        }
                                                        else
                                                        {
                                                            lexer.ThrowExpectationFailure(pos, "CastExpression");
                                                        }
                                                    }
                                                    if (match.hit)
                                                    {
                                                        expr.reset(new soul::ast::cpp::UnaryOpExprNode(lexer.GetSourcePos(pos), op->value, castExpr.release()));
                                                    }
                                                    *parentMatch26 = match;
                                                }
                                                *parentMatch25 = match;
                                            }
                                            *parentMatch24 = match;
                                        }
                                        *parentMatch23 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
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
                                        soul::parser::Match* parentMatch30 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch31 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == SIZEOF)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch31 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch32 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == LPAREN)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    *parentMatch32 = match;
                                                }
                                                *parentMatch31 = match;
                                            }
                                            *parentMatch30 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch33 = &match;
                                            {
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch34 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = DeclaratorParser<Lexer>::TypeId(lexer);
                                                    typeId.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        *parentMatch34 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.ThrowExpectationFailure(pos, "TypeId");
                                                    }
                                                }
                                                *parentMatch33 = match;
                                            }
                                            *parentMatch30 = match;
                                        }
                                        *parentMatch29 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch35 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch36 = &match;
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
                                                    expr.reset(new soul::ast::cpp::SizeOfNode(lexer.GetSourcePos(pos), typeId.release(), true));
                                                }
                                                *parentMatch36 = match;
                                            }
                                            *parentMatch35 = match;
                                        }
                                        *parentMatch29 = match;
                                    }
                                    *parentMatch28 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
                        if (!match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch37 = &match;
                            lexer.SetPos(save);
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch38 = &match;
                                {
                                    soul::parser::Match match(false);
                                    if (*lexer == SIZEOF)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    *parentMatch38 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch39 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch40 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(true);
                                            soul::parser::Match* parentMatch41 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::UnaryExpression(lexer);
                                                u3.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    *parentMatch41 = match;
                                                }
                                                else
                                                {
                                                    lexer.ThrowExpectationFailure(pos, "UnaryExpression");
                                                }
                                            }
                                            if (match.hit)
                                            {
                                                expr.reset(new soul::ast::cpp::SizeOfNode(lexer.GetSourcePos(pos), u3.release(), false));
                                            }
                                            *parentMatch40 = match;
                                        }
                                        *parentMatch39 = match;
                                    }
                                    *parentMatch38 = match;
                                }
                                *parentMatch37 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch42 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch43 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::NewExpression(lexer);
                                newExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(newExpr.release());
                                }
                                *parentMatch43 = match;
                            }
                            *parentMatch42 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch44 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch45 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::DeleteExpression(lexer);
                            deleteExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                            if (match.hit)
                            {
                                expr.reset(deleteExpr.release());
                            }
                            *parentMatch45 = match;
                        }
                        *parentMatch44 = match;
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::UnaryOperator(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UnaryOperator");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688218);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case STAR:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::deref));
                }
            }
            break;
        }
        case AMP:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::addrOf));
                }
            }
            break;
        }
        case PLUS:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::plus));
                }
            }
            break;
        }
        case MINUS:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::minus));
                }
            }
            break;
        }
        case EXCLAMATION:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::not_));
                }
            }
            break;
        }
        case TILDE:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::cpl));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
        else soul::lexer::WriteFailureToLog(lexer, "UnaryOperator");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::PostfixExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PostfixExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688219);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> primaryExpr;
    std::unique_ptr<soul::ast::cpp::Node> index;
    std::unique_ptr<soul::ast::cpp::IdExprNode> dotMember;
    std::unique_ptr<soul::ast::cpp::IdExprNode> arrowMember;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::PrimaryExpression(lexer);
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
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                int64_t save = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    int64_t save = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch11 = &match;
                                                    {
                                                        int64_t save = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch12 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch13 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                if (*lexer == LBRACKET)
                                                                {
                                                                    ++lexer;
                                                                    match.hit = true;
                                                                }
                                                                *parentMatch13 = match;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch14 = &match;
                                                                {
                                                                    soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer);
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
                                                                    int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match(true);
                                                                    soul::parser::Match* parentMatch17 = &match;
                                                                    {
                                                                        int64_t pos = lexer.GetPos();
                                                                        soul::parser::Match match(false);
                                                                        if (*lexer == RBRACKET)
                                                                        {
                                                                            ++lexer;
                                                                            match.hit = true;
                                                                        }
                                                                        if (match.hit)
                                                                        {
                                                                            *parentMatch17 = match;
                                                                        }
                                                                        else
                                                                        {
                                                                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RBRACKET));
                                                                        }
                                                                    }
                                                                    if (match.hit)
                                                                    {
                                                                        expr.reset(new soul::ast::cpp::IndexExprNode(lexer.GetSourcePos(pos), expr.release(), index.release()));
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
                                                            soul::parser::Match* parentMatch18 = &match;
                                                            lexer.SetPos(save);
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch19 = &match;
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch20 = &match;
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch21 = &match;
                                                                        {
                                                                            int64_t pos = lexer.GetPos();
                                                                            soul::parser::Match match(false);
                                                                            if (*lexer == LPAREN)
                                                                            {
                                                                                ++lexer;
                                                                                match.hit = true;
                                                                            }
                                                                            if (match.hit)
                                                                            {
                                                                                expr.reset(new soul::ast::cpp::InvokeNode(lexer.GetSourcePos(pos), expr.release()));
                                                                            }
                                                                            *parentMatch21 = match;
                                                                        }
                                                                        *parentMatch20 = match;
                                                                    }
                                                                    if (match.hit)
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch22 = &match;
                                                                        {
                                                                            soul::parser::Match match(true);
                                                                            int64_t save = lexer.GetPos();
                                                                            soul::parser::Match* parentMatch23 = &match;
                                                                            {
                                                                                soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, expr.get());
                                                                                if (match.hit)
                                                                                {
                                                                                    *parentMatch23 = match;
                                                                                }
                                                                                else
                                                                                {
                                                                                    lexer.SetPos(save);
                                                                                }
                                                                            }
                                                                            *parentMatch22 = match;
                                                                        }
                                                                        *parentMatch20 = match;
                                                                    }
                                                                    *parentMatch19 = match;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch24 = &match;
                                                                    {
                                                                        soul::parser::Match match(true);
                                                                        soul::parser::Match* parentMatch25 = &match;
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
                                                                                *parentMatch25 = match;
                                                                            }
                                                                            else
                                                                            {
                                                                                lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RPAREN));
                                                                            }
                                                                        }
                                                                        *parentMatch24 = match;
                                                                    }
                                                                    *parentMatch19 = match;
                                                                }
                                                                *parentMatch18 = match;
                                                            }
                                                            *parentMatch11 = match;
                                                        }
                                                    }
                                                    *parentMatch10 = match;
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
                                                                if (*lexer == DOT)
                                                                {
                                                                    ++lexer;
                                                                    match.hit = true;
                                                                }
                                                                *parentMatch27 = match;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch28 = &match;
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch29 = &match;
                                                                    {
                                                                        int64_t pos = lexer.GetPos();
                                                                        soul::parser::Match match(true);
                                                                        soul::parser::Match* parentMatch30 = &match;
                                                                        {
                                                                            int64_t pos = lexer.GetPos();
                                                                            soul::parser::Match match = ExpressionParser<Lexer>::IdExpression(lexer);
                                                                            dotMember.reset(static_cast<soul::ast::cpp::IdExprNode*>(match.value));
                                                                            if (match.hit)
                                                                            {
                                                                                *parentMatch30 = match;
                                                                            }
                                                                            else
                                                                            {
                                                                                lexer.ThrowExpectationFailure(pos, "IdExpression");
                                                                            }
                                                                        }
                                                                        if (match.hit)
                                                                        {
                                                                            expr.reset(new soul::ast::cpp::MemberAccessNode(lexer.GetSourcePos(pos), expr.release(), dotMember.release()));
                                                                        }
                                                                        *parentMatch29 = match;
                                                                    }
                                                                    *parentMatch28 = match;
                                                                }
                                                                *parentMatch27 = match;
                                                            }
                                                            *parentMatch26 = match;
                                                        }
                                                        *parentMatch10 = match;
                                                    }
                                                }
                                                *parentMatch9 = match;
                                                if (!match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch31 = &match;
                                                    lexer.SetPos(save);
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch32 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            if (*lexer == ARROW)
                                                            {
                                                                ++lexer;
                                                                match.hit = true;
                                                            }
                                                            *parentMatch32 = match;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch33 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch34 = &match;
                                                                {
                                                                    int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match(true);
                                                                    soul::parser::Match* parentMatch35 = &match;
                                                                    {
                                                                        int64_t pos = lexer.GetPos();
                                                                        soul::parser::Match match = ExpressionParser<Lexer>::IdExpression(lexer);
                                                                        arrowMember.reset(static_cast<soul::ast::cpp::IdExprNode*>(match.value));
                                                                        if (match.hit)
                                                                        {
                                                                            *parentMatch35 = match;
                                                                        }
                                                                        else
                                                                        {
                                                                            lexer.ThrowExpectationFailure(pos, "IdExpression");
                                                                        }
                                                                    }
                                                                    if (match.hit)
                                                                    {
                                                                        expr.reset(new soul::ast::cpp::PtrMemberAccessNode(lexer.GetSourcePos(pos), expr.release(), arrowMember.release()));
                                                                    }
                                                                    *parentMatch34 = match;
                                                                }
                                                                *parentMatch33 = match;
                                                            }
                                                            *parentMatch32 = match;
                                                        }
                                                        *parentMatch31 = match;
                                                    }
                                                    *parentMatch9 = match;
                                                }
                                            }
                                            *parentMatch8 = match;
                                            if (!match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch36 = &match;
                                                lexer.SetPos(save);
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch37 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == PLUS_PLUS)
                                                        {
                                                            ++lexer;
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            expr.reset(new soul::ast::cpp::PostIncrementNode(lexer.GetSourcePos(pos), expr.release()));
                                                        }
                                                        *parentMatch37 = match;
                                                    }
                                                    *parentMatch36 = match;
                                                }
                                                *parentMatch8 = match;
                                            }
                                        }
                                        *parentMatch7 = match;
                                        if (!match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch38 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch39 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == MINUS_MINUS)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        expr.reset(new soul::ast::cpp::PostDecrementNode(lexer.GetSourcePos(pos), expr.release()));
                                                    }
                                                    *parentMatch39 = match;
                                                }
                                                *parentMatch38 = match;
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::PostCastExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PostCastExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688220);
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
            int64_t save = lexer.GetPos();
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
                                            int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t save = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    int64_t save = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == STATIC_CAST)
                                                        {
                                                            ++lexer;
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            cppCastNode.reset(new soul::ast::cpp::StaticCastNode(lexer.GetSourcePos(pos)));
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
                                                                int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match(false);
                                                                if (*lexer == DYNAMIC_CAST)
                                                                {
                                                                    ++lexer;
                                                                    match.hit = true;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    cppCastNode.reset(new soul::ast::cpp::DynamicCastNode(lexer.GetSourcePos(pos)));
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
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match(false);
                                                            if (*lexer == REINTERPRET_CAST)
                                                            {
                                                                ++lexer;
                                                                match.hit = true;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                cppCastNode.reset(new soul::ast::cpp::ReinterpretCastNode(lexer.GetSourcePos(pos)));
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
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == CONST_CAST)
                                                        {
                                                            ++lexer;
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            cppCastNode.reset(new soul::ast::cpp::ConstCastNode(lexer.GetSourcePos(pos)));
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
                                        soul::parser::Match match(true);
                                        soul::parser::Match* parentMatch20 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == LANGLE)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch20 = match;
                                            }
                                            else
                                            {
                                                lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LANGLE));
                                            }
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
                                soul::parser::Match* parentMatch21 = &match;
                                {
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch22 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = DeclaratorParser<Lexer>::TypeId(lexer);
                                        typeId.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                                        if (match.hit)
                                        {
                                            *parentMatch22 = match;
                                        }
                                        else
                                        {
                                            lexer.ThrowExpectationFailure(pos, "TypeId");
                                        }
                                    }
                                    *parentMatch21 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch23 = &match;
                            {
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch24 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == RANGLE)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch24 = match;
                                    }
                                    else
                                    {
                                        lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RANGLE));
                                    }
                                }
                                *parentMatch23 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch25 = &match;
                        {
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch26 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == LPAREN)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    *parentMatch26 = match;
                                }
                                else
                                {
                                    lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LPAREN));
                                }
                            }
                            *parentMatch25 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch27 = &match;
                    {
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch28 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer);
                            expr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                            if (match.hit)
                            {
                                *parentMatch28 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, "Expression");
                            }
                        }
                        *parentMatch27 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch29 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch30 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch31 = &match;
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
                                *parentMatch31 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RPAREN));
                            }
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PostCastExpression");
                                #endif SOUL_PARSER_DEBUG_SUPPORT
                                return soul::parser::Match(true, new soul::ast::cpp::PostCastNode(lexer.GetSourcePos(pos), cppCastNode.release(), typeId.release(), expr.release()));
                            }
                        }
                        *parentMatch30 = match;
                    }
                    *parentMatch29 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch32 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch33 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch34 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch35 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == TYPEID)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch35 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch36 = &match;
                                {
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch37 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == LPAREN)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            *parentMatch37 = match;
                                        }
                                        else
                                        {
                                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LPAREN));
                                        }
                                    }
                                    *parentMatch36 = match;
                                }
                                *parentMatch35 = match;
                            }
                            *parentMatch34 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch38 = &match;
                            {
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch39 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer);
                                    typeIdExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        *parentMatch39 = match;
                                    }
                                    else
                                    {
                                        lexer.ThrowExpectationFailure(pos, "Expression");
                                    }
                                }
                                *parentMatch38 = match;
                            }
                            *parentMatch34 = match;
                        }
                        *parentMatch33 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch40 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch41 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch42 = &match;
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
                                        *parentMatch42 = match;
                                    }
                                    else
                                    {
                                        lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RPAREN));
                                    }
                                }
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PostCastExpression");
                                        #endif SOUL_PARSER_DEBUG_SUPPORT
                                        return soul::parser::Match(true, new soul::ast::cpp::TypeIdExprNode(lexer.GetSourcePos(pos), typeIdExpr.release()));
                                    }
                                }
                                *parentMatch41 = match;
                            }
                            *parentMatch40 = match;
                        }
                        *parentMatch33 = match;
                    }
                    *parentMatch32 = match;
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ExpressionList(Lexer& lexer, soul::ast::cpp::Node* owner)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ExpressionList");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688221);
    std::unique_ptr<soul::ast::cpp::Node> expr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer);
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
                    int64_t save = lexer.GetPos();
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch4 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == COMMA)
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
                                    soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer);
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::PrimaryExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PrimaryExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688222);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::LiteralNode> literal;
    std::unique_ptr<soul::ast::cpp::Node> parenExpr;
    std::unique_ptr<soul::ast::cpp::IdExprNode> idExpr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = LiteralParser<Lexer>::Literal(lexer);
                    literal.reset(static_cast<soul::ast::cpp::LiteralNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == THIS)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                    return soul::parser::Match(true, new soul::ast::cpp::ThisNode(lexer.GetSourcePos(pos)));
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
                                ++lexer;
                                match.hit = true;
                            }
                            *parentMatch8 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer);
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
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                                        #endif SOUL_PARSER_DEBUG_SUPPORT
                                        return soul::parser::Match(true, new soul::ast::cpp::ParenExprNode(lexer.GetSourcePos(pos), parenExpr.release()));
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<Lexer>::IdExpression(lexer);
                    idExpr.reset(static_cast<soul::ast::cpp::IdExprNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::IdExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IdExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688223);
    std::string str = std::string();
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
            int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = CppIdentifierParser<Lexer>::QualifiedCppId(lexer);
                            id1.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                str = id1->value;
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
                            if (*lexer == COLON_COLON)
                            {
                                ++lexer;
                                match.hit = true;
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
                    soul::parser::Match* parentMatch7 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch8 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::OperatorFunctionId(lexer);
                            ofId1.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                str.append("::").append(ofId1->value);
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                    return soul::parser::Match(true, new soul::ast::cpp::IdExprNode(lexer.GetSourcePos(pos), str));
                                }
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch11 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch12 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(true);
                                    if (match.hit)
                                    {
                                        str.clear();
                                    }
                                    *parentMatch12 = match;
                                }
                                *parentMatch11 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch13 = &match;
                                {
                                    soul::parser::Match match(true);
                                    int64_t save = lexer.GetPos();
                                    soul::parser::Match* parentMatch14 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch15 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch16 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == COLON_COLON)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    str.append("::");
                                                }
                                                *parentMatch16 = match;
                                            }
                                            *parentMatch15 = match;
                                        }
                                        if (match.hit)
                                        {
                                            *parentMatch14 = match;
                                        }
                                        else
                                        {
                                            lexer.SetPos(save);
                                        }
                                    }
                                    *parentMatch13 = match;
                                }
                                *parentMatch11 = match;
                            }
                            *parentMatch10 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch17 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch18 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ExpressionParser<Lexer>::OperatorFunctionId(lexer);
                                    ofId2.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                                    if (match.hit)
                                    {
                                        str.append(ofId2->value);
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                            #endif SOUL_PARSER_DEBUG_SUPPORT
                                            return soul::parser::Match(true, new soul::ast::cpp::IdExprNode(lexer.GetSourcePos(pos), str));
                                        }
                                    }
                                    *parentMatch18 = match;
                                }
                                *parentMatch17 = match;
                            }
                            *parentMatch10 = match;
                        }
                        *parentMatch9 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch19 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch20 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = CppIdentifierParser<Lexer>::QualifiedCppId(lexer);
                        id2.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                #endif SOUL_PARSER_DEBUG_SUPPORT
                                return soul::parser::Match(true, new soul::ast::cpp::IdExprNode(lexer.GetSourcePos(pos), id2->value));
                            }
                        }
                        *parentMatch20 = match;
                    }
                    *parentMatch19 = match;
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::TypeSpecifierOrTypeName(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeSpecifierOrTypeName");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688224);
    std::unique_ptr<soul::ast::cpp::TypeSpecifierNode> simpleTypeSpecifier;
    std::unique_ptr<soul::ast::cpp::TypeNameNode> typeName;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = DeclarationParser<Lexer>::SimpleTypeSpecifier(lexer);
            simpleTypeSpecifier.reset(static_cast<soul::ast::cpp::TypeSpecifierNode*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierOrTypeName");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = DeclarationParser<Lexer>::TypeName(lexer);
                    typeName.reset(static_cast<soul::ast::cpp::TypeNameNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierOrTypeName");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688225);
    bool global = bool();
    std::unique_ptr<soul::ast::cpp::NewNode> newExprNode = std::unique_ptr<soul::ast::cpp::NewNode>();
    std::unique_ptr<soul::ast::cpp::TypeIdNode> newTypeId;
    std::unique_ptr<soul::ast::cpp::TypeIdNode> ti;
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
                                            soul::parser::Match match(true);
                                            int64_t save = lexer.GetPos();
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == COLON_COLON)
                                                        {
                                                            ++lexer;
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
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == NEW)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        newExprNode.reset(new soul::ast::cpp::NewNode(lexer.GetSourcePos(pos), global));
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
                                                int64_t pos = lexer.GetPos();
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
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match* parentMatch18 = &match;
                                        {
                                            soul::parser::Match match = ExpressionParser<Lexer>::NewPlacement(lexer, newExprNode.get());
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
                                        int64_t pos = lexer.GetPos();
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
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch24 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = ExpressionParser<Lexer>::NewTypeId(lexer);
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
                                                            ++lexer;
                                                            match.hit = true;
                                                        }
                                                        *parentMatch27 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch28 = &match;
                                                        {
                                                            soul::parser::Match match = DeclaratorParser<Lexer>::TypeId(lexer);
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
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match(false);
                                                            if (*lexer == RPAREN)
                                                            {
                                                                ++lexer;
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
                                int64_t pos = lexer.GetPos();
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
                        int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch34 = &match;
                        {
                            soul::parser::Match match = ExpressionParser<Lexer>::NewInitializer(lexer, newExprNode.get());
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
                        int64_t pos = lexer.GetPos();
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewPlacement(Lexer& lexer, soul::ast::cpp::Node* owner)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewPlacement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688226);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == LPAREN)
            {
                ++lexer;
                match.hit = true;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, owner);
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
                ++lexer;
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewTypeId(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewTypeId");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688227);
    std::unique_ptr<soul::ast::cpp::TypeIdNode> ti = std::unique_ptr<soul::ast::cpp::TypeIdNode>();
    std::unique_ptr<soul::ast::cpp::TypeNameNode> typeName;
    std::unique_ptr<soul::parser::Value<std::string>> newDeclarator;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(true);
            if (match.hit)
            {
                ti.reset(new soul::ast::cpp::TypeIdNode(lexer.GetSourcePos(pos)));
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
                int64_t pos = lexer.GetPos();
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
                                int64_t save = lexer.GetPos();
                                soul::parser::Match match = DeclaratorParser<Lexer>::TypeSpecifierSeq(lexer, ti.get());
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = DeclarationParser<Lexer>::TypeName(lexer);
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
                            int64_t save = lexer.GetPos();
                            soul::parser::Match* parentMatch11 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch12 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch13 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = ExpressionParser<Lexer>::NewDeclarator(lexer);
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
                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewDeclarator(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewDeclarator");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688228);
    std::string str = std::string();
    std::unique_ptr<soul::parser::Value<std::string>> ptrOperator;
    std::unique_ptr<soul::parser::Value<std::string>> newDeclarator;
    std::unique_ptr<soul::parser::Value<std::string>> directNewDeclarator;
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
                int64_t save = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = DeclaratorParser<Lexer>::PtrOperator(lexer);
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
                        int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ExpressionParser<Lexer>::NewDeclarator(lexer);
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::DirectNewDeclarator(lexer);
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewInitializer(Lexer& lexer, soul::ast::cpp::Node* owner)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewInitializer");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688229);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == LPAREN)
            {
                ++lexer;
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
                int64_t save = lexer.GetPos();
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, owner);
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
                ++lexer;
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::DirectNewDeclarator(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DirectNewDeclarator");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688230);
    std::string str = std::string();
    std::unique_ptr<soul::ast::cpp::Node> expr;
    std::unique_ptr<soul::ast::cpp::Node> constantExpr;
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == LBRACKET)
                            {
                                ++lexer;
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
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer);
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == RBRACKET)
                            {
                                ++lexer;
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
                            int64_t save = lexer.GetPos();
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
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            *parentMatch14 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch15 = &match;
                                            {
                                                soul::parser::Match match = ExpressionParser<Lexer>::ConstantExpression(lexer);
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == RBRACKET)
                                                {
                                                    ++lexer;
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::DeleteExpression(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DeleteExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688231);
    bool global = bool();
    bool isArray = bool();
    std::unique_ptr<soul::ast::cpp::Node> ptr;
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
                        soul::parser::Match match(true);
                        int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == COLON_COLON)
                                    {
                                        ++lexer;
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
                                ++lexer;
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
                        int64_t save = lexer.GetPos();
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
                                        ++lexer;
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == RBRACKET)
                                            {
                                                ++lexer;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer);
                    ptr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeleteExpression");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::ast::cpp::DeleteNode(lexer.GetSourcePos(pos), global, isArray, ptr.release()));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::OperatorFunctionId(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "OperatorFunctionId");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688232);
    std::string str = std::string();
    std::unique_ptr<soul::parser::Value<std::string>> op;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == OPERATOR)
                    {
                        ++lexer;
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ExpressionParser<Lexer>::Operator(lexer);
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::Operator(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Operator");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2139687109831688233);
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    int64_t save = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch9 = &match;
                                        {
                                            int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t save = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    int64_t save = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        int64_t save = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch13 = &match;
                                                        {
                                                            int64_t save = lexer.GetPos();
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch14 = &match;
                                                            {
                                                                int64_t save = lexer.GetPos();
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch15 = &match;
                                                                {
                                                                    int64_t save = lexer.GetPos();
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch16 = &match;
                                                                    {
                                                                        int64_t save = lexer.GetPos();
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch17 = &match;
                                                                        {
                                                                            int64_t save = lexer.GetPos();
                                                                            soul::parser::Match match(false);
                                                                            soul::parser::Match* parentMatch18 = &match;
                                                                            {
                                                                                int64_t save = lexer.GetPos();
                                                                                soul::parser::Match match(false);
                                                                                soul::parser::Match* parentMatch19 = &match;
                                                                                {
                                                                                    int64_t save = lexer.GetPos();
                                                                                    soul::parser::Match match(false);
                                                                                    soul::parser::Match* parentMatch20 = &match;
                                                                                    {
                                                                                        int64_t save = lexer.GetPos();
                                                                                        soul::parser::Match match(false);
                                                                                        soul::parser::Match* parentMatch21 = &match;
                                                                                        {
                                                                                            int64_t save = lexer.GetPos();
                                                                                            soul::parser::Match match(false);
                                                                                            soul::parser::Match* parentMatch22 = &match;
                                                                                            {
                                                                                                int64_t save = lexer.GetPos();
                                                                                                soul::parser::Match match(false);
                                                                                                soul::parser::Match* parentMatch23 = &match;
                                                                                                {
                                                                                                    int64_t save = lexer.GetPos();
                                                                                                    soul::parser::Match match(false);
                                                                                                    soul::parser::Match* parentMatch24 = &match;
                                                                                                    {
                                                                                                        int64_t save = lexer.GetPos();
                                                                                                        soul::parser::Match match(false);
                                                                                                        soul::parser::Match* parentMatch25 = &match;
                                                                                                        {
                                                                                                            int64_t save = lexer.GetPos();
                                                                                                            soul::parser::Match match(false);
                                                                                                            soul::parser::Match* parentMatch26 = &match;
                                                                                                            {
                                                                                                                int64_t save = lexer.GetPos();
                                                                                                                soul::parser::Match match(false);
                                                                                                                soul::parser::Match* parentMatch27 = &match;
                                                                                                                {
                                                                                                                    int64_t save = lexer.GetPos();
                                                                                                                    soul::parser::Match match(false);
                                                                                                                    soul::parser::Match* parentMatch28 = &match;
                                                                                                                    {
                                                                                                                        int64_t save = lexer.GetPos();
                                                                                                                        soul::parser::Match match(false);
                                                                                                                        soul::parser::Match* parentMatch29 = &match;
                                                                                                                        {
                                                                                                                            int64_t save = lexer.GetPos();
                                                                                                                            soul::parser::Match match(false);
                                                                                                                            soul::parser::Match* parentMatch30 = &match;
                                                                                                                            {
                                                                                                                                int64_t save = lexer.GetPos();
                                                                                                                                soul::parser::Match match(false);
                                                                                                                                soul::parser::Match* parentMatch31 = &match;
                                                                                                                                {
                                                                                                                                    int64_t save = lexer.GetPos();
                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                    soul::parser::Match* parentMatch32 = &match;
                                                                                                                                    {
                                                                                                                                        int64_t save = lexer.GetPos();
                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                        soul::parser::Match* parentMatch33 = &match;
                                                                                                                                        {
                                                                                                                                            int64_t save = lexer.GetPos();
                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                            soul::parser::Match* parentMatch34 = &match;
                                                                                                                                            {
                                                                                                                                                int64_t save = lexer.GetPos();
                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                soul::parser::Match* parentMatch35 = &match;
                                                                                                                                                {
                                                                                                                                                    int64_t save = lexer.GetPos();
                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                    soul::parser::Match* parentMatch36 = &match;
                                                                                                                                                    {
                                                                                                                                                        int64_t save = lexer.GetPos();
                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                        soul::parser::Match* parentMatch37 = &match;
                                                                                                                                                        {
                                                                                                                                                            int64_t save = lexer.GetPos();
                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                            soul::parser::Match* parentMatch38 = &match;
                                                                                                                                                            {
                                                                                                                                                                int64_t save = lexer.GetPos();
                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                soul::parser::Match* parentMatch39 = &match;
                                                                                                                                                                {
                                                                                                                                                                    int64_t save = lexer.GetPos();
                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                    soul::parser::Match* parentMatch40 = &match;
                                                                                                                                                                    {
                                                                                                                                                                        int64_t save = lexer.GetPos();
                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                        soul::parser::Match* parentMatch41 = &match;
                                                                                                                                                                        {
                                                                                                                                                                            int64_t save = lexer.GetPos();
                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                            soul::parser::Match* parentMatch42 = &match;
                                                                                                                                                                            {
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                if (*lexer == LBRACKET)
                                                                                                                                                                                {
                                                                                                                                                                                    ++lexer;
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
                                                                                                                                                                                        int64_t pos = lexer.GetPos();
                                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                                        if (*lexer == RBRACKET)
                                                                                                                                                                                        {
                                                                                                                                                                                            ++lexer;
                                                                                                                                                                                            match.hit = true;
                                                                                                                                                                                        }
                                                                                                                                                                                        if (match.hit)
                                                                                                                                                                                        {
                                                                                                                                                                                            {
                                                                                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                                                            ++lexer;
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
                                                                                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                                                    int64_t pos = lexer.GetPos();
                                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                                    if (*lexer == ARROW_STAR)
                                                                                                                                                                                    {
                                                                                                                                                                                        ++lexer;
                                                                                                                                                                                        match.hit = true;
                                                                                                                                                                                    }
                                                                                                                                                                                    if (match.hit)
                                                                                                                                                                                    {
                                                                                                                                                                                        {
                                                                                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                                                int64_t pos = lexer.GetPos();
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                if (*lexer == ARROW)
                                                                                                                                                                                {
                                                                                                                                                                                    ++lexer;
                                                                                                                                                                                    match.hit = true;
                                                                                                                                                                                }
                                                                                                                                                                                if (match.hit)
                                                                                                                                                                                {
                                                                                                                                                                                    {
                                                                                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                                            int64_t pos = lexer.GetPos();
                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                            if (*lexer == COMMA)
                                                                                                                                                                            {
                                                                                                                                                                                ++lexer;
                                                                                                                                                                                match.hit = true;
                                                                                                                                                                            }
                                                                                                                                                                            if (match.hit)
                                                                                                                                                                            {
                                                                                                                                                                                {
                                                                                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                                        int64_t pos = lexer.GetPos();
                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                        if (*lexer == MINUS_MINUS)
                                                                                                                                                                        {
                                                                                                                                                                            ++lexer;
                                                                                                                                                                            match.hit = true;
                                                                                                                                                                        }
                                                                                                                                                                        if (match.hit)
                                                                                                                                                                        {
                                                                                                                                                                            {
                                                                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                                    int64_t pos = lexer.GetPos();
                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                    if (*lexer == PLUS_PLUS)
                                                                                                                                                                    {
                                                                                                                                                                        ++lexer;
                                                                                                                                                                        match.hit = true;
                                                                                                                                                                    }
                                                                                                                                                                    if (match.hit)
                                                                                                                                                                    {
                                                                                                                                                                        {
                                                                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                                int64_t pos = lexer.GetPos();
                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                if (*lexer == DISJUNCTION)
                                                                                                                                                                {
                                                                                                                                                                    ++lexer;
                                                                                                                                                                    match.hit = true;
                                                                                                                                                                }
                                                                                                                                                                if (match.hit)
                                                                                                                                                                {
                                                                                                                                                                    {
                                                                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                            int64_t pos = lexer.GetPos();
                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                            if (*lexer == AMP_AMP)
                                                                                                                                                            {
                                                                                                                                                                ++lexer;
                                                                                                                                                                match.hit = true;
                                                                                                                                                            }
                                                                                                                                                            if (match.hit)
                                                                                                                                                            {
                                                                                                                                                                {
                                                                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                        int64_t pos = lexer.GetPos();
                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                        if (*lexer == LEQ)
                                                                                                                                                        {
                                                                                                                                                            ++lexer;
                                                                                                                                                            match.hit = true;
                                                                                                                                                        }
                                                                                                                                                        if (match.hit)
                                                                                                                                                        {
                                                                                                                                                            {
                                                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                    int64_t pos = lexer.GetPos();
                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                    if (*lexer == GEQ)
                                                                                                                                                    {
                                                                                                                                                        ++lexer;
                                                                                                                                                        match.hit = true;
                                                                                                                                                    }
                                                                                                                                                    if (match.hit)
                                                                                                                                                    {
                                                                                                                                                        {
                                                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                                int64_t pos = lexer.GetPos();
                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                if (*lexer == NEQ)
                                                                                                                                                {
                                                                                                                                                    ++lexer;
                                                                                                                                                    match.hit = true;
                                                                                                                                                }
                                                                                                                                                if (match.hit)
                                                                                                                                                {
                                                                                                                                                    {
                                                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                            int64_t pos = lexer.GetPos();
                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                            if (*lexer == EQ)
                                                                                                                                            {
                                                                                                                                                ++lexer;
                                                                                                                                                match.hit = true;
                                                                                                                                            }
                                                                                                                                            if (match.hit)
                                                                                                                                            {
                                                                                                                                                {
                                                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                        int64_t pos = lexer.GetPos();
                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                        if (*lexer == SHIFT_LEFT_ASSIGN)
                                                                                                                                        {
                                                                                                                                            ++lexer;
                                                                                                                                            match.hit = true;
                                                                                                                                        }
                                                                                                                                        if (match.hit)
                                                                                                                                        {
                                                                                                                                            {
                                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                    int64_t pos = lexer.GetPos();
                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                    if (*lexer == SHIFT_RIGHT_ASSIGN)
                                                                                                                                    {
                                                                                                                                        ++lexer;
                                                                                                                                        match.hit = true;
                                                                                                                                    }
                                                                                                                                    if (match.hit)
                                                                                                                                    {
                                                                                                                                        {
                                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                                int64_t pos = lexer.GetPos();
                                                                                                                                soul::parser::Match match(false);
                                                                                                                                if (*lexer == SHIFT_LEFT)
                                                                                                                                {
                                                                                                                                    ++lexer;
                                                                                                                                    match.hit = true;
                                                                                                                                }
                                                                                                                                if (match.hit)
                                                                                                                                {
                                                                                                                                    {
                                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                            int64_t pos = lexer.GetPos();
                                                                                                                            soul::parser::Match match(false);
                                                                                                                            if (*lexer == SHIFT_RIGHT)
                                                                                                                            {
                                                                                                                                ++lexer;
                                                                                                                                match.hit = true;
                                                                                                                            }
                                                                                                                            if (match.hit)
                                                                                                                            {
                                                                                                                                {
                                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                        int64_t pos = lexer.GetPos();
                                                                                                                        soul::parser::Match match(false);
                                                                                                                        if (*lexer == OR_ASSIGN)
                                                                                                                        {
                                                                                                                            ++lexer;
                                                                                                                            match.hit = true;
                                                                                                                        }
                                                                                                                        if (match.hit)
                                                                                                                        {
                                                                                                                            {
                                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                    int64_t pos = lexer.GetPos();
                                                                                                                    soul::parser::Match match(false);
                                                                                                                    if (*lexer == AND_ASSIGN)
                                                                                                                    {
                                                                                                                        ++lexer;
                                                                                                                        match.hit = true;
                                                                                                                    }
                                                                                                                    if (match.hit)
                                                                                                                    {
                                                                                                                        {
                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                                int64_t pos = lexer.GetPos();
                                                                                                                soul::parser::Match match(false);
                                                                                                                if (*lexer == XOR_ASSIGN)
                                                                                                                {
                                                                                                                    ++lexer;
                                                                                                                    match.hit = true;
                                                                                                                }
                                                                                                                if (match.hit)
                                                                                                                {
                                                                                                                    {
                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                            int64_t pos = lexer.GetPos();
                                                                                                            soul::parser::Match match(false);
                                                                                                            if (*lexer == REM_ASSIGN)
                                                                                                            {
                                                                                                                ++lexer;
                                                                                                                match.hit = true;
                                                                                                            }
                                                                                                            if (match.hit)
                                                                                                            {
                                                                                                                {
                                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                        int64_t pos = lexer.GetPos();
                                                                                                        soul::parser::Match match(false);
                                                                                                        if (*lexer == DIV_ASSIGN)
                                                                                                        {
                                                                                                            ++lexer;
                                                                                                            match.hit = true;
                                                                                                        }
                                                                                                        if (match.hit)
                                                                                                        {
                                                                                                            {
                                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                    int64_t pos = lexer.GetPos();
                                                                                                    soul::parser::Match match(false);
                                                                                                    if (*lexer == MUL_ASSIGN)
                                                                                                    {
                                                                                                        ++lexer;
                                                                                                        match.hit = true;
                                                                                                    }
                                                                                                    if (match.hit)
                                                                                                    {
                                                                                                        {
                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                                int64_t pos = lexer.GetPos();
                                                                                                soul::parser::Match match(false);
                                                                                                if (*lexer == MINUS_ASSIGN)
                                                                                                {
                                                                                                    ++lexer;
                                                                                                    match.hit = true;
                                                                                                }
                                                                                                if (match.hit)
                                                                                                {
                                                                                                    {
                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                            int64_t pos = lexer.GetPos();
                                                                                            soul::parser::Match match(false);
                                                                                            if (*lexer == PLUS_ASSIGN)
                                                                                            {
                                                                                                ++lexer;
                                                                                                match.hit = true;
                                                                                            }
                                                                                            if (match.hit)
                                                                                            {
                                                                                                {
                                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                        int64_t pos = lexer.GetPos();
                                                                                        soul::parser::Match match(false);
                                                                                        if (*lexer == LANGLE)
                                                                                        {
                                                                                            ++lexer;
                                                                                            match.hit = true;
                                                                                        }
                                                                                        if (match.hit)
                                                                                        {
                                                                                            {
                                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                    int64_t pos = lexer.GetPos();
                                                                                    soul::parser::Match match(false);
                                                                                    if (*lexer == RANGLE)
                                                                                    {
                                                                                        ++lexer;
                                                                                        match.hit = true;
                                                                                    }
                                                                                    if (match.hit)
                                                                                    {
                                                                                        {
                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                                int64_t pos = lexer.GetPos();
                                                                                soul::parser::Match match(false);
                                                                                if (*lexer == ASSIGN)
                                                                                {
                                                                                    ++lexer;
                                                                                    match.hit = true;
                                                                                }
                                                                                if (match.hit)
                                                                                {
                                                                                    {
                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                            int64_t pos = lexer.GetPos();
                                                                            soul::parser::Match match(false);
                                                                            if (*lexer == EXCLAMATION)
                                                                            {
                                                                                ++lexer;
                                                                                match.hit = true;
                                                                            }
                                                                            if (match.hit)
                                                                            {
                                                                                {
                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                        int64_t pos = lexer.GetPos();
                                                                        soul::parser::Match match(false);
                                                                        if (*lexer == TILDE)
                                                                        {
                                                                            ++lexer;
                                                                            match.hit = true;
                                                                        }
                                                                        if (match.hit)
                                                                        {
                                                                            {
                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                    int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match(false);
                                                                    if (*lexer == AMP)
                                                                    {
                                                                        ++lexer;
                                                                        match.hit = true;
                                                                    }
                                                                    if (match.hit)
                                                                    {
                                                                        {
                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                                int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match(false);
                                                                if (*lexer == CARET)
                                                                {
                                                                    ++lexer;
                                                                    match.hit = true;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    {
                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match(false);
                                                            if (*lexer == PIPE)
                                                            {
                                                                ++lexer;
                                                                match.hit = true;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                {
                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == REM)
                                                        {
                                                            ++lexer;
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            {
                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == DIV)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        {
                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == STAR)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    {
                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == MINUS)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == PLUS)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                            ++lexer;
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
                                                ++lexer;
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == RBRACKET)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                                        ++lexer;
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
                                            ++lexer;
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
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == RBRACKET)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == NEW)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == DELETE)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct ExpressionParser<soul::lexer::Lexer<soul::lex::slg::SlgLexer<char32_t>, char32_t>>;
template struct ExpressionParser<soul::lexer::Lexer<soul::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul::cpp::expression::parser
