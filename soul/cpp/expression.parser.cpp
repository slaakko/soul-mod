
// this file has been automatically generated from 'D:/work/soul-mod/soul/cpp/expression.parser' using soul parser generator spg version 5.0.0

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
import soul.lex.slg;
import soul.lex.spg;

using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::tool::token;
using namespace soul::punctuation::token;
using namespace soul::cpp::declarator::parser;
using namespace soul::cpp::declaration::parser;
using namespace soul::cpp::literal::parser;
using namespace soul::cpp::identifier::parser;
using namespace soul::lex::slg;
using namespace soul::lex::spg;

namespace soul::cpp::expression::parser {

template<typename LexerT>
soul::parser::Match ExpressionParser<LexerT>::Expression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "Expression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::AssignmentExpression(lexer);
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
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<LexerT>::AssignmentExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::ConstantExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ConstantExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688194);
    std::unique_ptr<soul::ast::cpp::Node> expr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match = ExpressionParser<LexerT>::Expression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::AssignmentExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "AssignmentExpression");
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
                soul::parser::Match match = ExpressionParser<LexerT>::LogicalOrExpression(lexer);
                left.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match = ExpressionParser<LexerT>::AssignmentOp(lexer);
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
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch6 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ExpressionParser<LexerT>::AssignmentExpression(lexer);
                        right.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                        if (match.hit)
                        {
                            *parentMatch6 = match;
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
                            #endif
                            return soul::parser::Match(true, new soul::ast::cpp::BinaryOpExprNode(lexer.GetSourcePos(pos), op->value, left.release(), right.release()));
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
            soul::parser::Match* parentMatch7 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch8 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<LexerT>::ConditionalExpression(lexer);
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
                    *parentMatch8 = match;
                }
                *parentMatch7 = match;
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
soul::parser::Match ExpressionParser<LexerT>::AssignmentOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "AssignmentOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688196);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::assign));
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
        case MUL_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::mulAssign));
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
        case DIV_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::divAssign));
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
        case REM_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::remAssign));
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
        case PLUS_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::plusAssign));
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
        case MINUS_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::minusAssign));
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
        case SHIFT_LEFT_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftLeftAssign));
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
        case SHIFT_RIGHT_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftRightAssign));
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
        case AND_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch9 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::andAssign));
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
        case XOR_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch10 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::xorAssign));
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
        case OR_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::orAssign));
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
soul::parser::Match ExpressionParser<LexerT>::ConditionalExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ConditionalExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::LogicalOrExpression(lexer);
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
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<LexerT>::Expression(lexer);
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
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(true);
                                        soul::parser::Match* parentMatch15 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = ExpressionParser<LexerT>::AssignmentExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::LogicalOrExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "LogicalOrExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::LogicalAndExpression(lexer);
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
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<LexerT>::LogicalAndExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::LogicalAndExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "LogicalAndExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::InclusiveOrExpression(lexer);
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
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<LexerT>::InclusiveOrExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::InclusiveOrExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "InclusiveOrExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::ExclusiveOrExpression(lexer);
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
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<LexerT>::ExclusiveOrExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::ExclusiveOrExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ExclusiveOrExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::AndExpression(lexer);
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
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<LexerT>::AndExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::AndExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "AndExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::EqualityExpression(lexer);
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
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<LexerT>::EqualityExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::EqualityExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "EqualityExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::RelationalExpression(lexer);
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
                                        soul::parser::Match match = ExpressionParser<LexerT>::EqOp(lexer);
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
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<LexerT>::RelationalExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::EqOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "EqOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688204);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case EQ:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::eq));
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
        case NEQ:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::notEq));
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
soul::parser::Match ExpressionParser<LexerT>::RelationalExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "RelationalExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::ShiftExpression(lexer);
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
                                        soul::parser::Match match = ExpressionParser<LexerT>::RelOp(lexer);
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
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<LexerT>::ShiftExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::RelOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "RelOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688206);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case LANGLE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::less));
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
        case RANGLE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::greater));
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
        case LEQ:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::lessOrEq));
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
        case GEQ:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::greaterOrEq));
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
soul::parser::Match ExpressionParser<LexerT>::ShiftExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ShiftExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::AdditiveExpression(lexer);
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
                                        soul::parser::Match match = ExpressionParser<LexerT>::ShiftOp(lexer);
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
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<LexerT>::AdditiveExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::ShiftOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ShiftOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688208);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case SHIFT_LEFT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftLeft));
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
        case SHIFT_RIGHT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::shiftRight));
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
soul::parser::Match ExpressionParser<LexerT>::AdditiveExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "AdditiveExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::MultiplicativeExpression(lexer);
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
                                        soul::parser::Match match = ExpressionParser<LexerT>::AddOp(lexer);
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
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<LexerT>::MultiplicativeExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::AddOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "AddOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688210);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case PLUS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::plus));
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
        case MINUS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::minus));
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
soul::parser::Match ExpressionParser<LexerT>::MultiplicativeExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MultiplicativeExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::PmExpression(lexer);
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
                                        soul::parser::Match match = ExpressionParser<LexerT>::MulOp(lexer);
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
                                                soul::parser::Match match(true);
                                                soul::parser::Match* parentMatch10 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ExpressionParser<LexerT>::PmExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::MulOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MulOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688212);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case STAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::mul));
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
        case DIV:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::div));
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
        case REM:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MulOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::rem));
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
soul::parser::Match ExpressionParser<LexerT>::PmExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "PmExpression");
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
                    soul::parser::Match match = ExpressionParser<LexerT>::CastExpression(lexer);
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
                                        soul::parser::Match match = ExpressionParser<LexerT>::PmOp(lexer);
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
                                                soul::parser::Match match = ExpressionParser<LexerT>::CastExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::PmOp(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "PmOp");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688214);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case DOT_STAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == DOT_STAR)
                {
                    ++lexer;
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
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case ARROW_STAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmOp");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::arrowStar));
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
soul::parser::Match ExpressionParser<LexerT>::CastExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "CastExpression");
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
                                soul::parser::Match match = DeclaratorParser<LexerT>::TypeId(lexer);
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
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<LexerT>::CastExpression(lexer);
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
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<LexerT>::UnaryExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::UnaryExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "UnaryExpression");
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
                                                soul::parser::Match match = ExpressionParser<LexerT>::PostfixExpression(lexer);
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
                                                        soul::parser::Match match = ExpressionParser<LexerT>::PostCastExpression(lexer);
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
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match(true);
                                                            soul::parser::Match* parentMatch17 = &match;
                                                            {
                                                                std::int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = ExpressionParser<LexerT>::UnaryExpression(lexer);
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
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(true);
                                                        soul::parser::Match* parentMatch22 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = ExpressionParser<LexerT>::UnaryExpression(lexer);
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
                                            soul::parser::Match match = ExpressionParser<LexerT>::UnaryOperator(lexer);
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
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(true);
                                                    soul::parser::Match* parentMatch27 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = ExpressionParser<LexerT>::CastExpression(lexer);
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
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = DeclaratorParser<LexerT>::TypeId(lexer);
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
                                                std::int64_t pos = lexer.GetPos();
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
                                            std::int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(true);
                                            soul::parser::Match* parentMatch41 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<LexerT>::UnaryExpression(lexer);
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<LexerT>::NewExpression(lexer);
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
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<LexerT>::DeleteExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::UnaryOperator(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "UnaryOperator");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688217);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case STAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::deref));
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
        case AMP:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::addrOf));
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
        case PLUS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::plus));
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
        case MINUS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::minus));
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
        case EXCLAMATION:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::not_));
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
        case TILDE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOperator");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<soul::ast::cpp::Operator>(soul::ast::cpp::Operator::cpl));
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
soul::parser::Match ExpressionParser<LexerT>::PostfixExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "PostfixExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688218);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::Node> primaryExpr;
    std::unique_ptr<soul::ast::cpp::Node> index;
    std::unique_ptr<soul::ast::cpp::IdExprNode> dotMember;
    std::unique_ptr<soul::ast::cpp::IdExprNode> arrowMember;
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
                    soul::parser::Match match = ExpressionParser<LexerT>::PrimaryExpression(lexer);
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
                                    switch (*lexer)
                                    {
                                        case LBRACKET:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch8 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch9 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == LBRACKET)
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
                                                        soul::parser::Match match = ExpressionParser<LexerT>::Expression(lexer);
                                                        index.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(true);
                                                        soul::parser::Match* parentMatch13 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match(false);
                                                            if (*lexer == RBRACKET)
                                                            {
                                                                ++lexer;
                                                                match.hit = true;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                *parentMatch13 = match;
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
                                                        *parentMatch12 = match;
                                                    }
                                                    *parentMatch11 = match;
                                                }
                                                *parentMatch8 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case LPAREN:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch14 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch15 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch16 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
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
                                                        *parentMatch16 = match;
                                                    }
                                                    *parentMatch15 = match;
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
                                                            soul::parser::Match match = ExpressionParser<LexerT>::ExpressionList(lexer, expr.get());
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
                                                    *parentMatch15 = match;
                                                }
                                                *parentMatch14 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch19 = &match;
                                                {
                                                    soul::parser::Match match(true);
                                                    soul::parser::Match* parentMatch20 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        if (*lexer == RPAREN)
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
                                                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RPAREN));
                                                        }
                                                    }
                                                    *parentMatch19 = match;
                                                }
                                                *parentMatch14 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case DOT:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch21 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == DOT)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch21 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch22 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch23 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match(true);
                                                        soul::parser::Match* parentMatch24 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = ExpressionParser<LexerT>::IdExpression(lexer);
                                                            dotMember.reset(static_cast<soul::ast::cpp::IdExprNode*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                *parentMatch24 = match;
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
                                                        *parentMatch23 = match;
                                                    }
                                                    *parentMatch22 = match;
                                                }
                                                *parentMatch21 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case ARROW:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch25 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == ARROW)
                                                {
                                                    ++lexer;
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
                                                        soul::parser::Match match(true);
                                                        soul::parser::Match* parentMatch28 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = ExpressionParser<LexerT>::IdExpression(lexer);
                                                            arrowMember.reset(static_cast<soul::ast::cpp::IdExprNode*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                *parentMatch28 = match;
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
                                                        *parentMatch27 = match;
                                                    }
                                                    *parentMatch26 = match;
                                                }
                                                *parentMatch25 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case PLUS_PLUS:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch29 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
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
                                                *parentMatch29 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case MINUS_MINUS:
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch30 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
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
                                                *parentMatch30 = match;
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
soul::parser::Match ExpressionParser<LexerT>::PostCastExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "PostCastExpression");
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
        switch (*lexer)
        {
            case CONST_CAST:
            case DYNAMIC_CAST:
            case REINTERPRET_CAST:
            case STATIC_CAST:
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
                                            switch (*lexer)
                                            {
                                                case STATIC_CAST:
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch10 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
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
                                                        *parentMatch10 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        *parentMatch9 = match;
                                                    }
                                                    break;
                                                }
                                                case DYNAMIC_CAST:
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch11 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
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
                                                        *parentMatch11 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        *parentMatch9 = match;
                                                    }
                                                    break;
                                                }
                                                case REINTERPRET_CAST:
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
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
                                                        *parentMatch12 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        *parentMatch9 = match;
                                                    }
                                                    break;
                                                }
                                                case CONST_CAST:
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch13 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
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
                                                        *parentMatch13 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        *parentMatch9 = match;
                                                    }
                                                    break;
                                                }
                                            }
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch14 = &match;
                                        {
                                            soul::parser::Match match(true);
                                            soul::parser::Match* parentMatch15 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == LANGLE)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch15 = match;
                                                }
                                                else
                                                {
                                                    lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LANGLE));
                                                }
                                            }
                                            *parentMatch14 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch16 = &match;
                                    {
                                        soul::parser::Match match(true);
                                        soul::parser::Match* parentMatch17 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = DeclaratorParser<LexerT>::TypeId(lexer);
                                            typeId.reset(static_cast<soul::ast::cpp::TypeIdNode*>(match.value));
                                            if (match.hit)
                                            {
                                                *parentMatch17 = match;
                                            }
                                            else
                                            {
                                                lexer.ThrowExpectationFailure(pos, "TypeId");
                                            }
                                        }
                                        *parentMatch16 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                *parentMatch5 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch18 = &match;
                                {
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch19 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == RANGLE)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            *parentMatch19 = match;
                                        }
                                        else
                                        {
                                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RANGLE));
                                        }
                                    }
                                    *parentMatch18 = match;
                                }
                                *parentMatch5 = match;
                            }
                            *parentMatch4 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch20 = &match;
                            {
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch21 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == LPAREN)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch21 = match;
                                    }
                                    else
                                    {
                                        lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LPAREN));
                                    }
                                }
                                *parentMatch20 = match;
                            }
                            *parentMatch4 = match;
                        }
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch22 = &match;
                        {
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch23 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<LexerT>::Expression(lexer);
                                expr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                if (match.hit)
                                {
                                    *parentMatch23 = match;
                                }
                                else
                                {
                                    lexer.ThrowExpectationFailure(pos, "Expression");
                                }
                            }
                            *parentMatch22 = match;
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
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch26 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == RPAREN)
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
                                    lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RPAREN));
                                }
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PostCastExpression");
                                    #endif
                                    return soul::parser::Match(true, new soul::ast::cpp::PostCastNode(lexer.GetSourcePos(pos), cppCastNode.release(), typeId.release(), expr.release()));
                                }
                            }
                            *parentMatch25 = match;
                        }
                        *parentMatch24 = match;
                    }
                    *parentMatch2 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case TYPEID:
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
                                ++lexer;
                                match.hit = true;
                            }
                            *parentMatch29 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch30 = &match;
                            {
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch31 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == LPAREN)
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
                                        lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LPAREN));
                                    }
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
                        soul::parser::Match* parentMatch32 = &match;
                        {
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch33 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<LexerT>::Expression(lexer);
                                typeIdExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
                                if (match.hit)
                                {
                                    *parentMatch33 = match;
                                }
                                else
                                {
                                    lexer.ThrowExpectationFailure(pos, "Expression");
                                }
                            }
                            *parentMatch32 = match;
                        }
                        *parentMatch28 = match;
                    }
                    *parentMatch27 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch34 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch35 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch36 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == RPAREN)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    *parentMatch36 = match;
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
                                    #endif
                                    return soul::parser::Match(true, new soul::ast::cpp::TypeIdExprNode(lexer.GetSourcePos(pos), typeIdExpr.release()));
                                }
                            }
                            *parentMatch35 = match;
                        }
                        *parentMatch34 = match;
                    }
                    *parentMatch27 = match;
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
soul::parser::Match ExpressionParser<LexerT>::ExpressionList(LexerT& lexer, soul::ast::cpp::Node* owner)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ExpressionList");
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
            soul::parser::Match match = ExpressionParser<LexerT>::AssignmentExpression(lexer);
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
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ExpressionParser<LexerT>::AssignmentExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::PrimaryExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "PrimaryExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688221);
    std::unique_ptr<soul::ast::cpp::Node> expr = std::unique_ptr<soul::ast::cpp::Node>();
    std::unique_ptr<soul::ast::cpp::LiteralNode> literal;
    std::unique_ptr<soul::ast::cpp::Node> parenExpr;
    std::unique_ptr<soul::ast::cpp::IdExprNode> idExpr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case CHAR_LITERAL:
            case FALSE:
            case FLOATING_LITERAL:
            case INTEGER_LITERAL:
            case NULLPTR:
            case STRING_LITERAL:
            case TRUE:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch2 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match = LiteralParser<LexerT>::Literal(lexer);
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
                    *parentMatch2 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case THIS:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
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
                            #endif
                            return soul::parser::Match(true, new soul::ast::cpp::ThisNode(lexer.GetSourcePos(pos)));
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
            case LPAREN:
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
                            soul::parser::Match match = ExpressionParser<LexerT>::Expression(lexer);
                            parenExpr.reset(static_cast<soul::ast::cpp::Node*>(match.value));
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
                        soul::parser::Match* parentMatch8 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::ast::cpp::ParenExprNode(lexer.GetSourcePos(pos), parenExpr.release()));
                                }
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch4 = match;
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch9 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch10 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ExpressionParser<LexerT>::IdExpression(lexer);
                    idExpr.reset(static_cast<soul::ast::cpp::IdExprNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                            #endif
                            return soul::parser::Match(true, idExpr.release());
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
soul::parser::Match ExpressionParser<LexerT>::IdExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "IdExpression");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2139687109831688222);
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
            std::int64_t save = lexer.GetPos();
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
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match = CppIdentifierParser<LexerT>::QualifiedCppId(lexer);
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
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<LexerT>::OperatorFunctionId(lexer);
                            ofId1.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                str.append("::").append(ofId1->value);
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                    #endif
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
                                    std::int64_t pos = lexer.GetPos();
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
                                    std::int64_t save = lexer.GetPos();
                                    soul::parser::Match* parentMatch14 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch15 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch16 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
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
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ExpressionParser<LexerT>::OperatorFunctionId(lexer);
                                    ofId2.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                                    if (match.hit)
                                    {
                                        str.append(ofId2->value);
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                            #endif
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
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match = CppIdentifierParser<LexerT>::QualifiedCppId(lexer);
                        id2.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                                #endif
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
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ExpressionParser<LexerT>::TypeSpecifierOrTypeName(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "TypeSpecifierOrTypeName");
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
            soul::parser::Match match = DeclarationParser<LexerT>::SimpleTypeSpecifier(lexer);
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
                    soul::parser::Match match = DeclarationParser<LexerT>::TypeName(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::NewExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "NewExpression");
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
                                                    std::int64_t pos = lexer.GetPos();
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
                                            soul::parser::Match match = ExpressionParser<LexerT>::NewPlacement(lexer, newExprNode.get());
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
                                            soul::parser::Match match = ExpressionParser<LexerT>::NewTypeId(lexer);
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
                                                            soul::parser::Match match = DeclaratorParser<LexerT>::TypeId(lexer);
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
                            soul::parser::Match match = ExpressionParser<LexerT>::NewInitializer(lexer, newExprNode.get());
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
soul::parser::Match ExpressionParser<LexerT>::NewPlacement(LexerT& lexer, soul::ast::cpp::Node* owner)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "NewPlacement");
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
                soul::parser::Match match = ExpressionParser<LexerT>::ExpressionList(lexer, owner);
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
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ExpressionParser<LexerT>::NewTypeId(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "NewTypeId");
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
                                soul::parser::Match match = DeclaratorParser<LexerT>::TypeSpecifierSeq(lexer, ti.get());
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
                                            soul::parser::Match match = DeclarationParser<LexerT>::TypeName(lexer);
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
                                        soul::parser::Match match = ExpressionParser<LexerT>::NewDeclarator(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::NewDeclarator(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "NewDeclarator");
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
            switch (*lexer)
            {
                case AMP:
                case STAR:
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch3 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch4 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match = DeclaratorParser<LexerT>::PtrOperator(lexer);
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
                                        soul::parser::Match match = ExpressionParser<LexerT>::NewDeclarator(lexer);
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
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case LBRACKET:
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch9 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ExpressionParser<LexerT>::DirectNewDeclarator(lexer);
                        directNewDeclarator.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            str.append(directNewDeclarator->value);
                        }
                        *parentMatch9 = match;
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
soul::parser::Match ExpressionParser<LexerT>::NewInitializer(LexerT& lexer, soul::ast::cpp::Node* owner)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "NewInitializer");
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
                std::int64_t save = lexer.GetPos();
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match = ExpressionParser<LexerT>::ExpressionList(lexer, owner);
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
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ExpressionParser<LexerT>::DirectNewDeclarator(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "DirectNewDeclarator");
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<LexerT>::Expression(lexer);
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
                                                soul::parser::Match match = ExpressionParser<LexerT>::ConstantExpression(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::DeleteExpression(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "DeleteExpression");
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
                                            std::int64_t pos = lexer.GetPos();
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
                    soul::parser::Match match = ExpressionParser<LexerT>::CastExpression(lexer);
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
                #endif
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
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ExpressionParser<LexerT>::OperatorFunctionId(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "OperatorFunctionId");
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
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ExpressionParser<LexerT>::Operator(lexer);
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
soul::parser::Match ExpressionParser<LexerT>::Operator(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "Operator");
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
                switch (*lexer)
                {
                    case LBRACKET:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch4 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == LBRACKET)
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
                                    std::int64_t pos = lexer.GetPos();
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
                                            #endif
                                            return soul::parser::Match(true, new soul::parser::Value<std::string>("[]"));
                                        }
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
                        break;
                    }
                    case LPAREN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch7 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == LPAREN)
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
                                    std::int64_t pos = lexer.GetPos();
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
                                            #endif
                                            return soul::parser::Match(true, new soul::parser::Value<std::string>("()"));
                                        }
                                    }
                                    *parentMatch9 = match;
                                }
                                *parentMatch8 = match;
                            }
                            *parentMatch7 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case ARROW_STAR:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch10 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("->*"));
                                }
                            }
                            *parentMatch10 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case ARROW:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch11 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("->"));
                                }
                            }
                            *parentMatch11 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case COMMA:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(","));
                                }
                            }
                            *parentMatch12 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case MINUS_MINUS:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch13 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("--"));
                                }
                            }
                            *parentMatch13 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case PLUS_PLUS:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("++"));
                                }
                            }
                            *parentMatch14 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case DISJUNCTION:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch15 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("||"));
                                }
                            }
                            *parentMatch15 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case AMP_AMP:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch16 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("&&"));
                                }
                            }
                            *parentMatch16 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case LEQ:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch17 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("<="));
                                }
                            }
                            *parentMatch17 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case GEQ:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch18 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(">="));
                                }
                            }
                            *parentMatch18 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case NEQ:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch19 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("!="));
                                }
                            }
                            *parentMatch19 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case EQ:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch20 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("=="));
                                }
                            }
                            *parentMatch20 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case SHIFT_LEFT_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch21 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("<<="));
                                }
                            }
                            *parentMatch21 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case SHIFT_RIGHT_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch22 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(">>="));
                                }
                            }
                            *parentMatch22 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case SHIFT_LEFT:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch23 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("<<"));
                                }
                            }
                            *parentMatch23 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case SHIFT_RIGHT:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch24 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(">>"));
                                }
                            }
                            *parentMatch24 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case OR_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch25 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("|="));
                                }
                            }
                            *parentMatch25 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case AND_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch26 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("&="));
                                }
                            }
                            *parentMatch26 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case XOR_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch27 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("^="));
                                }
                            }
                            *parentMatch27 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case REM_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch28 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("%="));
                                }
                            }
                            *parentMatch28 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case DIV_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch29 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("/="));
                                }
                            }
                            *parentMatch29 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case MUL_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch30 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("*="));
                                }
                            }
                            *parentMatch30 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case MINUS_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch31 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("-="));
                                }
                            }
                            *parentMatch31 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case PLUS_ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch32 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("+="));
                                }
                            }
                            *parentMatch32 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case LANGLE:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch33 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("<"));
                                }
                            }
                            *parentMatch33 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case RANGLE:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch34 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(">"));
                                }
                            }
                            *parentMatch34 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch35 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("="));
                                }
                            }
                            *parentMatch35 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case EXCLAMATION:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch36 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("!"));
                                }
                            }
                            *parentMatch36 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case TILDE:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch37 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("~"));
                                }
                            }
                            *parentMatch37 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case AMP:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch38 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("&"));
                                }
                            }
                            *parentMatch38 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case CARET:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch39 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("^"));
                                }
                            }
                            *parentMatch39 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case PIPE:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch40 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("|"));
                                }
                            }
                            *parentMatch40 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case REM:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch41 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("%"));
                                }
                            }
                            *parentMatch41 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case DIV:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch42 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("/"));
                                }
                            }
                            *parentMatch42 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case STAR:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch43 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("*"));
                                }
                            }
                            *parentMatch43 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case MINUS:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch44 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("-"));
                                }
                            }
                            *parentMatch44 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case PLUS:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch45 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>("+"));
                                }
                            }
                            *parentMatch45 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case NEW:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch46 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch47 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == NEW)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch47 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch48 = &match;
                                {
                                    soul::parser::Match match(false);
                                    if (*lexer == LBRACKET)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    *parentMatch48 = match;
                                }
                                *parentMatch47 = match;
                            }
                            *parentMatch46 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch49 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch50 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
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
                                            #endif
                                            return soul::parser::Match(true, new soul::parser::Value<std::string>(" new[]"));
                                        }
                                    }
                                    *parentMatch50 = match;
                                }
                                *parentMatch49 = match;
                            }
                            *parentMatch46 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case DELETE:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch51 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch52 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == DELETE)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch52 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch53 = &match;
                                {
                                    soul::parser::Match match(false);
                                    if (*lexer == LBRACKET)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    *parentMatch53 = match;
                                }
                                *parentMatch52 = match;
                            }
                            *parentMatch51 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch54 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch55 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
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
                                            #endif
                                            return soul::parser::Match(true, new soul::parser::Value<std::string>(" delete[]"));
                                        }
                                    }
                                    *parentMatch55 = match;
                                }
                                *parentMatch54 = match;
                            }
                            *parentMatch51 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch56 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch57 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
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
                                    #endif
                                    return soul::parser::Match(true, new soul::parser::Value<std::string>(" new"));
                                }
                            }
                            *parentMatch57 = match;
                        }
                        *parentMatch56 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch58 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch59 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
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
                                #endif
                                return soul::parser::Match(true, new soul::parser::Value<std::string>(" delete"));
                            }
                        }
                        *parentMatch59 = match;
                    }
                    *parentMatch58 = match;
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
