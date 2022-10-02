
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/expression.parser' using soul parser generator spg version 4.1.0

module otava.parser.expression;

import util;
import soul.ast.spg;
import otava.token;
import otava.lexer;
import otava.parser.attribute;
import otava.parser.initialization;
import otava.parser.type;
import otava.parser.function;
import otava.parser.literal;
import otava.parser.lambda;
import otava.parser.guard;
import otava.parser.concepts;
import otava.parser.identifier;
import otava.parser.declaration;
import otava.parser.punctuation;
import otava.parser.token;

using namespace otava::token;
using namespace otava::lexer;
using namespace otava::parser::attribute;
using namespace otava::parser::initialization;
using namespace otava::parser::type;
using namespace otava::parser::function;
using namespace otava::parser::literal;
using namespace otava::parser::lambda;
using namespace otava::parser::guard;
using namespace otava::parser::concepts;
using namespace otava::parser::identifier;
using namespace otava::parser::declaration;
using namespace otava::parser::punctuation;
using namespace otava::parser::token;

namespace otava::parser::expression {

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::Expression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Expression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475201);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos commaPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match* parentMatch8 = &match;
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
                                                commaPos = lexer.GetSourcePos(pos);
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
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, new otava::ast::CommaNode(commaPos), expr.release(), right.release()));
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ConstantExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConstantExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475202);
    std::unique_ptr<otava::ast::Node> conditionalExpr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = ExpressionParser<Lexer>::ConditionalExpression(lexer, context);
        conditionalExpr.reset(static_cast<otava::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstantExpression");
                #endif
                return soul::parser::Match(true, conditionalExpr.release());
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AssignmentExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AssignmentExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475203);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> leftExpr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> yieldExpr;
    std::unique_ptr<otava::ast::Node> throwExpr;
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> op;
    std::unique_ptr<otava::ast::Node> right;
    std::unique_ptr<otava::ast::Node> conditionalExpr;
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
                    switch (*lexer)
                    {
                        case CO_YIELD:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch5 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::YieldExpression(lexer, context);
                                yieldExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(yieldExpr.release());
                                }
                                *parentMatch5 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case THROW:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::ThrowExpression(lexer, context);
                                throwExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(throwExpr.release());
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch7 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch8 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch9 = &match;
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
                                                bool pass = true;
                                                soul::parser::Match match = ExpressionParser<Lexer>::LogicalOrExpression(lexer, context);
                                                left.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    sourcePos = lexer.GetSourcePos(pos);
                                                    leftExpr.reset(left.release());
                                                    if (leftExpr->IsBinaryExprNode())
                                                    {
                                                        pass = false;
                                                    }
                                                }
                                                if (match.hit && !pass)
                                                {
                                                    match = soul::parser::Match(false);
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::AssignmentOp(lexer);
                                                op.reset(static_cast<otava::ast::Node*>(match.value));
                                                *parentMatch13 = match;
                                            }
                                            *parentMatch11 = match;
                                        }
                                        *parentMatch10 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch14 = &match;
                                        {
                                            soul::parser::Match match = InitializationParser<Lexer>::InitializerClause(lexer, context);
                                            right.reset(static_cast<otava::ast::Node*>(match.value));
                                            *parentMatch14 = match;
                                        }
                                        *parentMatch10 = match;
                                    }
                                    *parentMatch9 = match;
                                }
                                if (match.hit)
                                {
                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, op.release(), leftExpr.release(), right.release()));
                                }
                                *parentMatch8 = match;
                            }
                            *parentMatch7 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
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
                            soul::parser::Match match = ExpressionParser<Lexer>::ConditionalExpression(lexer, context);
                            conditionalExpr.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                expr.reset(conditionalExpr.release());
                            }
                            *parentMatch16 = match;
                        }
                        *parentMatch15 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
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
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475204);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::AssignNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::MulAssignNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DivAssignNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ModAssignNode(lexer.GetSourcePos(pos)));
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
        case ADD_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == ADD_ASSIGN)
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
                        return soul::parser::Match(true, new otava::ast::PlusAssignNode(lexer.GetSourcePos(pos)));
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
        case SUB_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == SUB_ASSIGN)
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
                        return soul::parser::Match(true, new otava::ast::MinusAssignNode(lexer.GetSourcePos(pos)));
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
        case SHIFT_RIGHT_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ShiftRightAssignNode(lexer.GetSourcePos(pos)));
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
        case SHIFT_LEFT_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ShiftLeftAssignNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::AndAssignNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::XorAssignNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AssignmentOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::OrAssignNode(lexer.GetSourcePos(pos)));
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ConditionalExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConditionalExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475205);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> cond;
    std::unique_ptr<otava::ast::Node> quest;
    std::unique_ptr<otava::ast::Node> thenExpr;
    std::unique_ptr<otava::ast::Node> colon;
    std::unique_ptr<otava::ast::Node> elseExpr;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::LogicalOrExpression(lexer, context);
                    cond.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        sourcePos = lexer.GetSourcePos(pos);
                        expr.reset(cond.release());
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
                                        soul::parser::Match match = PunctuationParser<Lexer>::Quest(lexer);
                                        quest.reset(static_cast<otava::ast::Node*>(match.value));
                                        *parentMatch9 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer, context);
                                            thenExpr.reset(static_cast<otava::ast::Node*>(match.value));
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
                                        soul::parser::Match match = PunctuationParser<Lexer>::Colon(lexer);
                                        colon.reset(static_cast<otava::ast::Node*>(match.value));
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
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer, context);
                                        elseExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            expr.reset(new otava::ast::ConditionalExprNode(sourcePos, expr.release(), quest.release(), thenExpr.release(), colon.release(), elseExpr.release()));
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::YieldExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "YieldExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475206);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> assignmentExpr;
    std::unique_ptr<otava::ast::Node> bracedInitList;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == CO_YIELD)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                sourcePos = lexer.GetSourcePos(pos);
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer, context);
                        assignmentExpr.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "YieldExpression");
                                #endif
                                return soul::parser::Match(true, new otava::ast::YieldExprNode(sourcePos, assignmentExpr.release()));
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
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = InitializationParser<Lexer>::BracedInitList(lexer, context);
                                bracedInitList.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "YieldExpression");
                                        #endif
                                        return soul::parser::Match(true, new otava::ast::YieldExprNode(sourcePos, bracedInitList.release()));
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
            }
            *parentMatch2 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "YieldExpression");
        else soul::lexer::WriteFailureToLog(lexer, "YieldExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ThrowExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ThrowExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475207);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> exception;
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
                    if (*lexer == THROW)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sourcePos = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = ExpressionParser<Lexer>::AssignmentExpression(lexer, context);
                        exception.reset(static_cast<otava::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ThrowExpression");
                #endif
                return soul::parser::Match(true, new otava::ast::ThrowExprNode(sourcePos, exception.release()));
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
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::LogicalOrExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LogicalOrExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475208);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos opPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::LogicalAndExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == OR_OR)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                opPos = lexer.GetSourcePos(pos);
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
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::LogicalAndExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, new otava::ast::DisjunctionNode(opPos), expr.release(), right.release()));
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::LogicalAndExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LogicalAndExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475209);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos opPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::InclusiveOrExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match* parentMatch8 = &match;
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
                                                opPos = lexer.GetSourcePos(pos);
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
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::InclusiveOrExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, new otava::ast::ConjunctionNode(opPos), expr.release(), right.release()));
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::InclusiveOrExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "InclusiveOrExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475210);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos opPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::ExclusiveOrExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == OR)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                opPos = lexer.GetSourcePos(pos);
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
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::ExclusiveOrExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, new otava::ast::InclusiveOrNode(opPos), expr.release(), right.release()));
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ExclusiveOrExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ExclusiveOrExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475211);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos opPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::AndExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == XOR)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                opPos = lexer.GetSourcePos(pos);
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
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::AndExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, new otava::ast::ExclusiveOrNode(opPos), expr.release(), right.release()));
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AndExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AndExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475212);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos opPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::EqualityExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match* parentMatch8 = &match;
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
                                                opPos = lexer.GetSourcePos(pos);
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
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::EqualityExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, new otava::ast::AndNode(opPos), expr.release(), right.release()));
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::EqualityExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "EqualityExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475213);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> op;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::RelationalExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match match = ExpressionParser<Lexer>::EqualityOp(lexer);
                                        op.reset(static_cast<otava::ast::Node*>(match.value));
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::RelationalExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, op.release(), expr.release(), right.release()));
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::EqualityOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "EqualityOp");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475214);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case EQ:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::EqualNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::NotEqualNode(lexer.GetSourcePos(pos)));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "EqualityOp");
        else soul::lexer::WriteFailureToLog(lexer, "EqualityOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::RelationalExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RelationalExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475215);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> op;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::CompareExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match match = ExpressionParser<Lexer>::RelationalOp(lexer, context->GetFlag(otava::symbols::ContextFlags::parsingTemplateId));
                                        op.reset(static_cast<otava::ast::Node*>(match.value));
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::CompareExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, op.release(), expr.release(), right.release()));
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::RelationalOp(Lexer& lexer, bool rejectRAngle)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RelationalOp");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475216);
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
                            #endif
                            return soul::parser::Match(true, new otava::ast::LessNode(lexer.GetSourcePos(pos)));
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
                                int64_t pos = lexer.GetPos();
                                bool pass = true;
                                soul::parser::Match match(true);
                                if (match.hit)
                                {
                                    pass = !rejectRAngle;
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
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
                                            #endif
                                            return soul::parser::Match(true, new otava::ast::GreaterNode(lexer.GetSourcePos(pos)));
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
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
                                #endif
                                return soul::parser::Match(true, new otava::ast::LessOrEqualNode(lexer.GetSourcePos(pos)));
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
                            #endif
                            return soul::parser::Match(true, new otava::ast::GreaterOrEqualNode(lexer.GetSourcePos(pos)));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RelationalOp");
        else soul::lexer::WriteFailureToLog(lexer, "RelationalOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::CompareExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CompareExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475217);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos opPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::ShiftExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == SPACE_SHIP)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                opPos = lexer.GetSourcePos(pos);
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
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::ShiftExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, new otava::ast::CompareNode(opPos), expr.release(), right.release()));
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompareExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompareExpression");
        else soul::lexer::WriteFailureToLog(lexer, "CompareExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ShiftExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ShiftExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475218);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> op;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::AdditiveExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        op.reset(static_cast<otava::ast::Node*>(match.value));
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::AdditiveExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, op.release(), expr.release(), right.release()));
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
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475219);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case SHIFT_LEFT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ShiftLeftNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShiftOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ShiftRightNode(lexer.GetSourcePos(pos)));
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AdditiveExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AdditiveExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475220);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> op;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::MultiplicativeExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match match = ExpressionParser<Lexer>::AdditiveOp(lexer);
                                        op.reset(static_cast<otava::ast::Node*>(match.value));
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::MultiplicativeExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, op.release(), expr.release(), right.release()));
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AdditiveOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AdditiveOp");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475221);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case PLUS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::PlusNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::MinusNode(lexer.GetSourcePos(pos)));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AdditiveOp");
        else soul::lexer::WriteFailureToLog(lexer, "AdditiveOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::MultiplicativeExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MultiplicativeExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475222);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> op;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::PmExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match match = ExpressionParser<Lexer>::MultiplicativeOp(lexer);
                                        op.reset(static_cast<otava::ast::Node*>(match.value));
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::PmExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, op.release(), expr.release(), right.release()));
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::MultiplicativeOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MultiplicativeOp");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475223);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case STAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::MulNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DivNode(lexer.GetSourcePos(pos)));
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
        case MOD:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == MOD)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ModNode(lexer.GetSourcePos(pos)));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MultiplicativeOp");
        else soul::lexer::WriteFailureToLog(lexer, "MultiplicativeOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::PmExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PmExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475224);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> left;
    std::unique_ptr<otava::ast::Node> op;
    std::unique_ptr<otava::ast::Node> right;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                    left.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        expr.reset(left.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                                        op.reset(static_cast<otava::ast::Node*>(match.value));
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                                                right.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    expr.reset(new otava::ast::BinaryExprNode(sourcePos, op.release(), expr.release(), right.release()));
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
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475225);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case DOT_STAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
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
                        return soul::parser::Match(true, new otava::ast::DotStarNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PmOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ArrowStarNode(lexer.GetSourcePos(pos)));
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::CastExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CastExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475226);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> typeId;
    std::unique_ptr<otava::ast::Node> child;
    std::unique_ptr<otava::ast::Node> ue;
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == LPAREN)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                sourcePos = lexer.GetSourcePos(pos);
                                                lpPos = sourcePos;
                                            }
                                            *parentMatch9 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            soul::parser::Match match = TypeParser<Lexer>::TypeId(lexer, context);
                                            typeId.reset(static_cast<otava::ast::Node*>(match.value));
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch12 = &match;
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
                                                rpPos = lexer.GetSourcePos(pos);
                                            }
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch13 = &match;
                                {
                                    soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                                    child.reset(static_cast<otava::ast::Node*>(match.value));
                                    *parentMatch13 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            expr.reset(new otava::ast::CastExprNode(sourcePos, typeId.release(), child.release(), lpPos, rpPos));
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch14 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch15 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::UnaryExpression(lexer, context);
                            ue.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                expr.reset(ue.release());
                            }
                            *parentMatch15 = match;
                        }
                        *parentMatch14 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::UnaryExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UnaryExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475227);
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> op;
    std::unique_ptr<otava::ast::Node> child;
    std::unique_ptr<otava::ast::Node> awaitExpr;
    std::unique_ptr<otava::ast::Node> sizeOfExpr;
    std::unique_ptr<otava::ast::Node> alignOfExpr;
    std::unique_ptr<otava::ast::Node> noexceptExpr;
    std::unique_ptr<otava::ast::Node> newExpr;
    std::unique_ptr<otava::ast::Node> deleteExpr;
    std::unique_ptr<otava::ast::Node> postfixExpr;
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
                    switch (*lexer)
                    {
                        case AMP:
                        case EXCLAMATION:
                        case MINUS:
                        case MINUS_MINUS:
                        case PLUS:
                        case PLUS_PLUS:
                        case STAR:
                        case TILDE:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch5 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ExpressionParser<Lexer>::UnaryOp(lexer);
                                    op.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        sourcePos = lexer.GetSourcePos(pos);
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
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                                        child.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            expr.reset(new otava::ast::UnaryExprNode(sourcePos, op.release(), child.release()));
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch5 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case CO_AWAIT:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::AwaitExpression(lexer, context);
                                awaitExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(awaitExpr.release());
                                }
                                *parentMatch9 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case SIZEOF:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch10 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::SizeOfExpression(lexer, context);
                                sizeOfExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(sizeOfExpr.release());
                                }
                                *parentMatch10 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case ALIGNOF:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch11 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::AlignOfExpression(lexer, context);
                                alignOfExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(alignOfExpr.release());
                                }
                                *parentMatch11 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case NOEXCEPT:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch12 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::NoexceptEpression(lexer, context);
                                noexceptExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(noexceptExpr.release());
                                }
                                *parentMatch12 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case COLON_COLON:
                        case NEW:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch13 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::NewExpression(lexer, context);
                                newExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(newExpr.release());
                                }
                                *parentMatch13 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch15 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::DeleteExpression(lexer, context);
                                deleteExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    expr.reset(deleteExpr.release());
                                }
                                *parentMatch15 = match;
                            }
                            *parentMatch14 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch16 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch17 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::PostfixExpression(lexer, context);
                            postfixExpr.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                expr.reset(postfixExpr.release());
                            }
                            *parentMatch17 = match;
                        }
                        *parentMatch16 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::UnaryOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UnaryOp");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475228);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case STAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DerefNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::AddrOfNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::PlusNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::MinusNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::NotNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ComplementNode(lexer.GetSourcePos(pos)));
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
        case PLUS_PLUS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::PrefixIncNode(lexer.GetSourcePos(pos)));
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
        case MINUS_MINUS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::PrefixDecNode(lexer.GetSourcePos(pos)));
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryOp");
        else soul::lexer::WriteFailureToLog(lexer, "UnaryOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AwaitExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AwaitExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475229);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> child;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == CO_AWAIT)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                sourcePos = lexer.GetSourcePos(pos);
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
                soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                child.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AwaitExpression");
                        #endif
                        return soul::parser::Match(true, new otava::ast::AwaitExprNode(sourcePos, child.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AwaitExpression");
        else soul::lexer::WriteFailureToLog(lexer, "AwaitExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::SizeOfExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SizeOfExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475230);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    soul::ast::SourcePos ellipsisPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> childNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> typeId;
    std::unique_ptr<otava::ast::Node> child;
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == SIZEOF)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                sourcePos = lexer.GetSourcePos(pos);
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
                                soul::parser::Match match(false);
                                if (*lexer == LPAREN)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    lpPos = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = TypeParser<Lexer>::TypeId(lexer, context);
                        typeId.reset(static_cast<otava::ast::Node*>(match.value));
                        *parentMatch8 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch9 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
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
                            rpPos = lexer.GetSourcePos(pos);
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SizeOfExpression");
                                #endif
                                return soul::parser::Match(true, new otava::ast::SizeOfTypeExprNode(sourcePos, typeId.release(), lpPos, rpPos));
                            }
                        }
                        *parentMatch10 = match;
                    }
                    *parentMatch9 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch11 = &match;
                lexer.SetPos(save);
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
                                soul::parser::Match* parentMatch15 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch16 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == SIZEOF)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            sourcePos = lexer.GetSourcePos(pos);
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
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch18 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == ELLIPSIS)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                ellipsisPos = lexer.GetSourcePos(pos);
                                            }
                                            *parentMatch18 = match;
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
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch20 = &match;
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
                                            lpPos = lexer.GetSourcePos(pos);
                                        }
                                        *parentMatch20 = match;
                                    }
                                    *parentMatch19 = match;
                                }
                                *parentMatch14 = match;
                            }
                            *parentMatch13 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch21 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch22 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == ID)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        childNode.reset(otava::parser::token::ParseIdentifier(lexer.GetSourcePos(pos), lexer.FileName(), lexer.GetToken(pos)));
                                    }
                                    *parentMatch22 = match;
                                }
                                *parentMatch21 = match;
                            }
                            *parentMatch13 = match;
                        }
                        *parentMatch12 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch23 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch24 = &match;
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
                                    rpPos = lexer.GetSourcePos(pos);
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SizeOfExpression");
                                        #endif
                                        return soul::parser::Match(true, new otava::ast::SizeOfPackExprNode(sourcePos, childNode.release(), ellipsisPos, lpPos, rpPos));
                                    }
                                }
                                *parentMatch24 = match;
                            }
                            *parentMatch23 = match;
                        }
                        *parentMatch12 = match;
                    }
                    *parentMatch11 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == SIZEOF)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            sourcePos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch27 = match;
                    }
                    *parentMatch26 = match;
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
                            soul::parser::Match match = ExpressionParser<Lexer>::UnaryExpression(lexer, context);
                            child.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SizeOfExpression");
                                    #endif
                                    return soul::parser::Match(true, new otava::ast::SizeOfUnaryExprNode(sourcePos, child.release()));
                                }
                            }
                            *parentMatch29 = match;
                        }
                        *parentMatch28 = match;
                    }
                    *parentMatch26 = match;
                }
                *parentMatch25 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SizeOfExpression");
        else soul::lexer::WriteFailureToLog(lexer, "SizeOfExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::AlignOfExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AlignOfExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475231);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> typeId;
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
                            if (*lexer == ALIGNOF)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                sourcePos = lexer.GetSourcePos(pos);
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
                                soul::parser::Match match(false);
                                if (*lexer == LPAREN)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    lpPos = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = TypeParser<Lexer>::TypeId(lexer, context);
                        typeId.reset(static_cast<otava::ast::Node*>(match.value));
                        *parentMatch8 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch9 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
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
                            rpPos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch10 = match;
                    }
                    *parentMatch9 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AlignOfExpression");
                #endif
                return soul::parser::Match(true, new otava::ast::AlignOfExprNode(sourcePos, typeId.release(), lpPos, rpPos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AlignOfExpression");
        else soul::lexer::WriteFailureToLog(lexer, "AlignOfExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NoexceptEpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NoexceptEpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475232);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> expr;
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
                            if (*lexer == NOEXCEPT)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                sourcePos = lexer.GetSourcePos(pos);
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
                                soul::parser::Match match(false);
                                if (*lexer == LPAREN)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    lpPos = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer, context);
                        expr.reset(static_cast<otava::ast::Node*>(match.value));
                        *parentMatch8 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch9 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
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
                            rpPos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch10 = match;
                    }
                    *parentMatch9 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoexceptEpression");
                #endif
                return soul::parser::Match(true, new otava::ast::NoexceptExprNode(sourcePos, expr.release(), lpPos, rpPos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoexceptEpression");
        else soul::lexer::WriteFailureToLog(lexer, "NoexceptEpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475233);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> colonColonNode = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos newPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> placement;
    std::unique_ptr<otava::ast::Node> newTypeId;
    std::unique_ptr<otava::ast::Node> newInitializer;
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
                            switch (*lexer)
                            {
                                case COLON_COLON:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch8 = &match;
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
                                                sourcePos = lexer.GetSourcePos(pos);
                                                colonColonNode.reset(new otava::ast::ColonColonNode(sourcePos));
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
                                            soul::parser::Match* parentMatch10 = &match;
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
                                                    newPos = lexer.GetSourcePos(pos);
                                                }
                                                *parentMatch10 = match;
                                            }
                                            *parentMatch9 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch6 = match;
                                    }
                                    break;
                                }
                                case NEW:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
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
                                            sourcePos = lexer.GetSourcePos(pos);
                                            newPos = sourcePos;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch6 = match;
                                    }
                                    break;
                                }
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
                            soul::parser::Match match(true);
                            int64_t save = lexer.GetPos();
                            soul::parser::Match* parentMatch13 = &match;
                            {
                                soul::parser::Match match = ExpressionParser<Lexer>::NewPlacement(lexer, context);
                                placement.reset(static_cast<otava::ast::Node*>(match.value));
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
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch14 = &match;
                    {
                        soul::parser::Match match = ExpressionParser<Lexer>::NewTypeId(lexer, context);
                        newTypeId.reset(static_cast<otava::ast::Node*>(match.value));
                        *parentMatch14 = match;
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
                    int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch16 = &match;
                    {
                        soul::parser::Match match = ExpressionParser<Lexer>::NewInitializer(lexer, context);
                        newInitializer.reset(static_cast<otava::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewExpression");
                #endif
                return soul::parser::Match(true, new otava::ast::NewExprNode(sourcePos, placement.release(), newTypeId.release(), newInitializer.release(), colonColonNode.release(), newPos));
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewPlacement(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewPlacement");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475234);
    std::unique_ptr<otava::ast::NewPlacementNode> placement = std::unique_ptr<otava::ast::NewPlacementNode>();
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == LPAREN)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            soul::ast::SourcePos sourcePos = lexer.GetSourcePos(pos);
                            placement.reset(new otava::ast::NewPlacementNode(sourcePos));
                            placement->SetLParenPos(sourcePos);
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
                        soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, context, placement.get());
                        *parentMatch5 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                        soul::parser::Match match(false);
                        if (*lexer == RPAREN)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            placement->SetRParenPos(lexer.GetSourcePos(pos));
                        }
                        *parentMatch7 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewPlacement");
                #endif
                return soul::parser::Match(true, placement.release());
            }
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewInitializer(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewInitializer");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475235);
    std::unique_ptr<otava::ast::NewInitializerNode> node = std::unique_ptr<otava::ast::NewInitializerNode>();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> bracedInitList;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case LPAREN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch2 = &match;
                {
                    int64_t pos = lexer.GetPos();
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == LPAREN)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        lpPos = lexer.GetSourcePos(pos);
                                        node.reset(new otava::ast::NewInitializerNode(lpPos));
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
                                    int64_t save = lexer.GetPos();
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, context, node.get());
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
                                *parentMatch5 = match;
                            }
                            *parentMatch4 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch10 = &match;
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
                                        rpPos = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch4 = match;
                        }
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        node->SetLParenPos(lpPos);
                        node->SetRParenPos(rpPos);
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewInitializer");
                            #endif
                            return soul::parser::Match(true, node.release());
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
            case LBRACE:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch11 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = InitializationParser<Lexer>::BracedInitList(lexer, context);
                    bracedInitList.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewInitializer");
                            #endif
                            return soul::parser::Match(true, bracedInitList.release());
                        }
                    }
                    *parentMatch11 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewTypeId(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewTypeId");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475236);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> typeId;
    std::unique_ptr<otava::ast::Node> typeSpecifierSeq;
    std::unique_ptr<otava::ast::Node> newDeclarator;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
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
                            if (*lexer == LPAREN)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                sourcePos = lexer.GetSourcePos(pos);
                                lpPos = sourcePos;
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
                            soul::parser::Match match = TypeParser<Lexer>::TypeId(lexer, context);
                            typeId.reset(static_cast<otava::ast::Node*>(match.value));
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
                            soul::parser::Match match(false);
                            if (*lexer == RPAREN)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                rpPos = lexer.GetSourcePos(pos);
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewTypeId");
                    #endif
                    return soul::parser::Match(true, new otava::ast::ParenNewTypeIdNode(sourcePos, typeId.release(), lpPos, rpPos));
                }
            }
            *parentMatch1 = match;
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
                                context->PushResetFlag(otava::symbols::ContextFlags::hasDefiningTypeSpecifier);
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch14 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = TypeParser<Lexer>::TypeSpecifierSeq(lexer, context);
                                typeSpecifierSeq.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    sourcePos = lexer.GetSourcePos(pos);
                                    context->PopFlags();
                                }
                                else
                                {
                                    context->PopFlags();
                                }
                                *parentMatch14 = match;
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
                    soul::parser::Match* parentMatch15 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch16 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch17 = &match;
                            {
                                int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch18 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ExpressionParser<Lexer>::NewDeclarator(lexer, context);
                                    newDeclarator.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewTypeId");
                                            #endif
                                            return soul::parser::Match(true, new otava::ast::NewTypeIdNode(sourcePos, typeSpecifierSeq.release(), newDeclarator.release()));
                                        }
                                    }
                                    *parentMatch18 = match;
                                }
                                *parentMatch17 = match;
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
                                            soul::parser::Match match(true);
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NewTypeId");
                                                    #endif
                                                    return soul::parser::Match(true, new otava::ast::NewTypeIdNode(sourcePos, typeSpecifierSeq.release(), nullptr));
                                                }
                                            }
                                            *parentMatch20 = match;
                                        }
                                        *parentMatch19 = match;
                                    }
                                    *parentMatch17 = match;
                                }
                            }
                            *parentMatch16 = match;
                        }
                        *parentMatch15 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NewDeclarator(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NewDeclarator");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475237);
    std::unique_ptr<otava::ast::Node> node = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> first;
    std::unique_ptr<otava::ast::Node> next;
    std::unique_ptr<otava::ast::Node> noPtrNewDeclarator;
    std::unique_ptr<otava::ast::Node> noPtrNewDecl;
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = DeclarationParser<Lexer>::PtrOperator(lexer, context);
                            first.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                node.reset(new otava::ast::NewDeclaratorNode(lexer.GetSourcePos(pos)));
                                node->AddNode(first.release());
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
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                while (true)
                                {
                                    int64_t save = lexer.GetPos();
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = DeclarationParser<Lexer>::PtrOperator(lexer, context);
                                                next.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    node->AddNode(next.release());
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
                                            break;
                                        }
                                    }
                                }
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
                    soul::parser::Match* parentMatch10 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch11 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch12 = &match;
                            {
                                int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch13 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ExpressionParser<Lexer>::NoPtrNewDeclarator(lexer, context);
                                    noPtrNewDeclarator.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        node->AddNode(noPtrNewDeclarator.release());
                                    }
                                    *parentMatch13 = match;
                                }
                                *parentMatch12 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch14 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(true);
                                        *parentMatch14 = match;
                                    }
                                    *parentMatch12 = match;
                                }
                            }
                            *parentMatch11 = match;
                        }
                        *parentMatch10 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                            soul::parser::Match match = ExpressionParser<Lexer>::NoPtrNewDeclarator(lexer, context);
                            noPtrNewDecl.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                node.reset(noPtrNewDecl.release());
                            }
                            *parentMatch16 = match;
                        }
                        *parentMatch15 = match;
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
                return soul::parser::Match(true, node.release());
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::NoPtrNewDeclarator(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NoPtrNewDeclarator");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475238);
    std::unique_ptr<otava::ast::Node> node = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> lb;
    std::unique_ptr<otava::ast::Node> size;
    std::unique_ptr<otava::ast::Node> rb;
    std::unique_ptr<otava::ast::Node> lb2;
    std::unique_ptr<otava::ast::Node> size2;
    std::unique_ptr<otava::ast::Node> rb2;
    std::unique_ptr<otava::ast::Node> attributes;
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = PunctuationParser<Lexer>::LBracket(lexer);
                                    lb.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        node.reset(new otava::ast::ArrayNewDeclaratorNode(lexer.GetSourcePos(pos)));
                                        node->AddNode(lb.release());
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
                                    int64_t save = lexer.GetPos();
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch11 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer, context);
                                                size.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    node->AddNode(size.release());
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
                            soul::parser::Match* parentMatch12 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch13 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = PunctuationParser<Lexer>::RBracket(lexer);
                                    rb.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        node->AddNode(rb.release());
                                    }
                                    *parentMatch13 = match;
                                }
                                *parentMatch12 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch14 = &match;
                    {
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch15 = &match;
                        {
                            while (true)
                            {
                                int64_t save = lexer.GetPos();
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch16 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch17 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch18 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch19 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = PunctuationParser<Lexer>::LBracket(lexer);
                                                    lb2.reset(static_cast<otava::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        node->AddNode(lb2.release());
                                                    }
                                                    *parentMatch19 = match;
                                                }
                                                *parentMatch18 = match;
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
                                                        soul::parser::Match match = ExpressionParser<Lexer>::ConstantExpression(lexer, context);
                                                        size2.reset(static_cast<otava::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            node->AddNode(size2.release());
                                                        }
                                                        *parentMatch21 = match;
                                                    }
                                                    *parentMatch20 = match;
                                                }
                                                *parentMatch18 = match;
                                            }
                                            *parentMatch17 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch22 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch23 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = PunctuationParser<Lexer>::RBracket(lexer);
                                                    rb2.reset(static_cast<otava::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        node->AddNode(rb2.release());
                                                    }
                                                    *parentMatch23 = match;
                                                }
                                                *parentMatch22 = match;
                                            }
                                            *parentMatch17 = match;
                                        }
                                        *parentMatch16 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch15 = match;
                                    }
                                    else
                                    {
                                        lexer.SetPos(save);
                                        break;
                                    }
                                }
                            }
                        }
                        *parentMatch14 = match;
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
                    soul::parser::Match match(true);
                    int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch25 = &match;
                    {
                        soul::parser::Match match = AttributeParser<Lexer>::AttributeSpecifierSeq(lexer, context);
                        attributes.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            *parentMatch25 = match;
                        }
                        else
                        {
                            lexer.SetPos(save);
                        }
                    }
                    *parentMatch24 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoPtrNewDeclarator");
                #endif
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoPtrNewDeclarator");
        else soul::lexer::WriteFailureToLog(lexer, "NoPtrNewDeclarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::DeleteExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DeleteExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475239);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> colonColonNode = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos deletePos = soul::ast::SourcePos();
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> ptr1;
    std::unique_ptr<otava::ast::Node> ptr2;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            switch (*lexer)
            {
                case COLON_COLON:
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch3 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch4 = &match;
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
                                sourcePos = lexer.GetSourcePos(pos);
                                colonColonNode.reset(new otava::ast::ColonColonNode(sourcePos));
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
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
                                    deletePos = lexer.GetSourcePos(pos);
                                }
                                *parentMatch6 = match;
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
                case DELETE:
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch7 = &match;
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
                            sourcePos = lexer.GetSourcePos(pos);
                            deletePos = sourcePos;
                        }
                        *parentMatch7 = match;
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
        *parentMatch0 = match;
    }
    if (match.hit)
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
                    int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch11 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch13 = &match;
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
                                    lbPos = lexer.GetSourcePos(pos);
                                }
                                *parentMatch13 = match;
                            }
                            *parentMatch12 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch14 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch15 = &match;
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
                                        rbPos = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch15 = match;
                                }
                                *parentMatch14 = match;
                            }
                            *parentMatch12 = match;
                        }
                        *parentMatch11 = match;
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
                                soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                                ptr1.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeleteExpression");
                                        #endif
                                        return soul::parser::Match(true, new otava::ast::ArrayDeletePtrNode(sourcePos, ptr1.release(), colonColonNode.release(), deletePos, lbPos, rbPos));
                                    }
                                }
                                *parentMatch17 = match;
                            }
                            *parentMatch16 = match;
                        }
                        *parentMatch11 = match;
                    }
                    *parentMatch10 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch18 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch19 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                                ptr2.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeleteExpression");
                                        #endif
                                        return soul::parser::Match(true, new otava::ast::DeletePtrNode(sourcePos, ptr2.release(), colonColonNode.release(), deletePos));
                                    }
                                }
                                *parentMatch19 = match;
                            }
                            *parentMatch18 = match;
                        }
                        *parentMatch10 = match;
                    }
                }
                *parentMatch9 = match;
            }
            *parentMatch8 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::PostfixExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PostfixExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475240);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::InvokeExprNode> invokeNode = std::unique_ptr<otava::ast::InvokeExprNode>();
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> cppCastExpr;
    std::unique_ptr<otava::ast::Node> typeIdExpr;
    std::unique_ptr<otava::ast::Node> simpleTypeSpecifier1;
    std::unique_ptr<otava::ast::Node> simpleTypeSpecifier2;
    std::unique_ptr<otava::ast::Node> args3;
    std::unique_ptr<otava::ast::Node> typenameSpecifier1;
    std::unique_ptr<otava::ast::Node> typenameSpecifier2;
    std::unique_ptr<otava::ast::Node> args5;
    std::unique_ptr<otava::ast::Node> invokeExpr;
    std::unique_ptr<otava::ast::Node> primaryExpr;
    std::unique_ptr<otava::ast::Node> index;
    std::unique_ptr<otava::ast::Node> dotOp;
    std::unique_ptr<otava::ast::Node> idExpr1;
    std::unique_ptr<otava::ast::Node> arrowOp;
    std::unique_ptr<otava::ast::Node> idExpr2;
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
                                            switch (*lexer)
                                            {
                                                case CONST_CAST:
                                                case DYNAMIC_CAST:
                                                case REINTERPRET_CAST:
                                                case STATIC_CAST:
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch11 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = ExpressionParser<Lexer>::CppCastExpression(lexer, context);
                                                        cppCastExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            sourcePos = lexer.GetSourcePos(pos);
                                                            expr.reset(cppCastExpr.release());
                                                        }
                                                        *parentMatch11 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    break;
                                                }
                                                case TYPEID:
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = ExpressionParser<Lexer>::TypeIdExpression(lexer, context);
                                                        typeIdExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            sourcePos = lexer.GetSourcePos(pos);
                                                            expr.reset(typeIdExpr.release());
                                                        }
                                                        *parentMatch12 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        *parentMatch10 = match;
                                                    }
                                                    break;
                                                }
                                            }
                                            *parentMatch9 = match;
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
                                                        soul::parser::Match* parentMatch15 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch16 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch17 = &match;
                                                                {
                                                                    int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match = TypeParser<Lexer>::SimpleTypeSpecifierReset(lexer, context);
                                                                    simpleTypeSpecifier1.reset(static_cast<otava::ast::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        sourcePos = lexer.GetSourcePos(pos);
                                                                    }
                                                                    *parentMatch17 = match;
                                                                }
                                                                *parentMatch16 = match;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch18 = &match;
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch19 = &match;
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
                                                                            lpPos = lexer.GetSourcePos(pos);
                                                                            invokeNode.reset(new otava::ast::InvokeExprNode(sourcePos, simpleTypeSpecifier1.release()));
                                                                        }
                                                                        *parentMatch19 = match;
                                                                    }
                                                                    *parentMatch18 = match;
                                                                }
                                                                *parentMatch16 = match;
                                                            }
                                                            *parentMatch15 = match;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch20 = &match;
                                                            {
                                                                soul::parser::Match match(true);
                                                                int64_t save = lexer.GetPos();
                                                                soul::parser::Match* parentMatch21 = &match;
                                                                {
                                                                    soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, context, invokeNode.get());
                                                                    if (match.hit)
                                                                    {
                                                                        *parentMatch21 = match;
                                                                    }
                                                                    else
                                                                    {
                                                                        lexer.SetPos(save);
                                                                    }
                                                                }
                                                                *parentMatch20 = match;
                                                            }
                                                            *parentMatch15 = match;
                                                        }
                                                        *parentMatch14 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch22 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch23 = &match;
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
                                                                    rpPos = lexer.GetSourcePos(pos);
                                                                    invokeNode->SetLParenPos(lpPos);
                                                                    invokeNode->SetRParenPos(rpPos);
                                                                    expr.reset(invokeNode.release());
                                                                }
                                                                *parentMatch23 = match;
                                                            }
                                                            *parentMatch22 = match;
                                                        }
                                                        *parentMatch14 = match;
                                                    }
                                                    *parentMatch13 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                        }
                                        *parentMatch8 = match;
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
                                                    soul::parser::Match* parentMatch26 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = TypeParser<Lexer>::SimpleTypeSpecifierReset(lexer, context);
                                                        simpleTypeSpecifier2.reset(static_cast<otava::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            sourcePos = lexer.GetSourcePos(pos);
                                                            expr.reset(new otava::ast::InvokeExprNode(sourcePos, simpleTypeSpecifier1.release()));
                                                        }
                                                        *parentMatch26 = match;
                                                    }
                                                    *parentMatch25 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch27 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch28 = &match;
                                                        {
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = InitializationParser<Lexer>::BracedInitList(lexer, context);
                                                            args3.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                expr->AddNode(args3.release());
                                                            }
                                                            *parentMatch28 = match;
                                                        }
                                                        *parentMatch27 = match;
                                                    }
                                                    *parentMatch25 = match;
                                                }
                                                *parentMatch24 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                    }
                                    *parentMatch7 = match;
                                    if (!match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch29 = &match;
                                        lexer.SetPos(save);
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch30 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch31 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch32 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch33 = &match;
                                                        {
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = TypeParser<Lexer>::TypenameSpecifier(lexer, context);
                                                            typenameSpecifier1.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                sourcePos = lexer.GetSourcePos(pos);
                                                            }
                                                            *parentMatch33 = match;
                                                        }
                                                        *parentMatch32 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch34 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch35 = &match;
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
                                                                    lpPos = lexer.GetSourcePos(pos);
                                                                    invokeNode.reset(new otava::ast::InvokeExprNode(sourcePos, typenameSpecifier1.release()));
                                                                }
                                                                *parentMatch35 = match;
                                                            }
                                                            *parentMatch34 = match;
                                                        }
                                                        *parentMatch32 = match;
                                                    }
                                                    *parentMatch31 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch36 = &match;
                                                    {
                                                        soul::parser::Match match(true);
                                                        int64_t save = lexer.GetPos();
                                                        soul::parser::Match* parentMatch37 = &match;
                                                        {
                                                            soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, context, invokeNode.get());
                                                            if (match.hit)
                                                            {
                                                                *parentMatch37 = match;
                                                            }
                                                            else
                                                            {
                                                                lexer.SetPos(save);
                                                            }
                                                        }
                                                        *parentMatch36 = match;
                                                    }
                                                    *parentMatch31 = match;
                                                }
                                                *parentMatch30 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch38 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch39 = &match;
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
                                                            rpPos = lexer.GetSourcePos(pos);
                                                            invokeNode->SetLParenPos(lpPos);
                                                            invokeNode->SetRParenPos(rpPos);
                                                            expr.reset(invokeNode.release());
                                                        }
                                                        *parentMatch39 = match;
                                                    }
                                                    *parentMatch38 = match;
                                                }
                                                *parentMatch30 = match;
                                            }
                                            *parentMatch29 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                }
                                *parentMatch6 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch40 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch41 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch42 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = TypeParser<Lexer>::TypenameSpecifier(lexer, context);
                                                typenameSpecifier2.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    sourcePos = lexer.GetSourcePos(pos);
                                                    expr.reset(new otava::ast::InvokeExprNode(sourcePos, simpleTypeSpecifier2.release()));
                                                }
                                                *parentMatch42 = match;
                                            }
                                            *parentMatch41 = match;
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
                                                    soul::parser::Match match = InitializationParser<Lexer>::BracedInitList(lexer, context);
                                                    args5.reset(static_cast<otava::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        expr->AddNode(args5.release());
                                                    }
                                                    *parentMatch44 = match;
                                                }
                                                *parentMatch43 = match;
                                            }
                                            *parentMatch41 = match;
                                        }
                                        *parentMatch40 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch45 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch46 = &match;
                                    {
                                        soul::parser::Match match = GuardParser<Lexer>::ConceptGuard(lexer, context);
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::IntrinsicInvokeExpr(lexer, context);
                                                invokeExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    sourcePos = lexer.GetSourcePos(pos);
                                                    expr.reset(invokeExpr.release());
                                                }
                                                *parentMatch48 = match;
                                            }
                                            *parentMatch47 = match;
                                        }
                                        *parentMatch46 = match;
                                    }
                                    *parentMatch45 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
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
                                    soul::parser::Match match = ExpressionParser<Lexer>::PrimaryExpression(lexer, context);
                                    primaryExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        expr.reset(primaryExpr.release());
                                        sourcePos = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch50 = match;
                                }
                                *parentMatch49 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch51 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch52 = &match;
                    {
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch53 = &match;
                        {
                            while (true)
                            {
                                int64_t save = lexer.GetPos();
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch54 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch55 = &match;
                                        switch (*lexer)
                                        {
                                            case LBRACKET:
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch56 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch57 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch58 = &match;
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
                                                                lbPos = lexer.GetSourcePos(pos);
                                                            }
                                                            *parentMatch58 = match;
                                                        }
                                                        *parentMatch57 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch59 = &match;
                                                        {
                                                            soul::parser::Match match = InitializationParser<Lexer>::ExprOrBracedInitList(lexer, context);
                                                            index.reset(static_cast<otava::ast::Node*>(match.value));
                                                            *parentMatch59 = match;
                                                        }
                                                        *parentMatch57 = match;
                                                    }
                                                    *parentMatch56 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch60 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch61 = &match;
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
                                                                rbPos = lexer.GetSourcePos(pos);
                                                                expr.reset(new otava::ast::SubscriptExprNode(sourcePos, expr.release(), index.release(), lbPos, rbPos));
                                                            }
                                                            *parentMatch61 = match;
                                                        }
                                                        *parentMatch60 = match;
                                                    }
                                                    *parentMatch56 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch55 = match;
                                                }
                                                break;
                                            }
                                            case LPAREN:
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch62 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch63 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch64 = &match;
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
                                                                lpPos = lexer.GetSourcePos(pos);
                                                                invokeNode.reset(new otava::ast::InvokeExprNode(sourcePos, expr.release()));
                                                            }
                                                            *parentMatch64 = match;
                                                        }
                                                        *parentMatch63 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch65 = &match;
                                                        {
                                                            soul::parser::Match match(true);
                                                            int64_t save = lexer.GetPos();
                                                            soul::parser::Match* parentMatch66 = &match;
                                                            {
                                                                soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, context, invokeNode.get());
                                                                if (match.hit)
                                                                {
                                                                    *parentMatch66 = match;
                                                                }
                                                                else
                                                                {
                                                                    lexer.SetPos(save);
                                                                }
                                                            }
                                                            *parentMatch65 = match;
                                                        }
                                                        *parentMatch63 = match;
                                                    }
                                                    *parentMatch62 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch67 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch68 = &match;
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
                                                                rpPos = lexer.GetSourcePos(pos);
                                                                invokeNode->SetLParenPos(lpPos);
                                                                invokeNode->SetRParenPos(rpPos);
                                                                expr.reset(invokeNode.release());
                                                            }
                                                            *parentMatch68 = match;
                                                        }
                                                        *parentMatch67 = match;
                                                    }
                                                    *parentMatch62 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch55 = match;
                                                }
                                                break;
                                            }
                                            case DOT:
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch69 = &match;
                                                {
                                                    soul::parser::Match match = ExpressionParser<Lexer>::DotOp(lexer);
                                                    dotOp.reset(static_cast<otava::ast::Node*>(match.value));
                                                    *parentMatch69 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch70 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch71 = &match;
                                                        {
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = ExpressionParser<Lexer>::IdExpression(lexer, context);
                                                            idExpr1.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                expr.reset(new otava::ast::MemberExprNode(sourcePos, expr.release(), dotOp.release(), idExpr1.release()));
                                                            }
                                                            *parentMatch71 = match;
                                                        }
                                                        *parentMatch70 = match;
                                                    }
                                                    *parentMatch69 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch55 = match;
                                                }
                                                break;
                                            }
                                            case ARROW:
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch72 = &match;
                                                {
                                                    soul::parser::Match match = ExpressionParser<Lexer>::ArrowOp(lexer);
                                                    arrowOp.reset(static_cast<otava::ast::Node*>(match.value));
                                                    *parentMatch72 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch73 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch74 = &match;
                                                        {
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = ExpressionParser<Lexer>::IdExpression(lexer, context);
                                                            idExpr2.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                expr.reset(new otava::ast::MemberExprNode(sourcePos, expr.release(), arrowOp.release(), idExpr2.release()));
                                                            }
                                                            *parentMatch74 = match;
                                                        }
                                                        *parentMatch73 = match;
                                                    }
                                                    *parentMatch72 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch55 = match;
                                                }
                                                break;
                                            }
                                            case PLUS_PLUS:
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch75 = &match;
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
                                                        expr.reset(new otava::ast::PostfixIncExprNode(sourcePos, expr.release(), lexer.GetSourcePos(pos)));
                                                    }
                                                    *parentMatch75 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch55 = match;
                                                }
                                                break;
                                            }
                                            case MINUS_MINUS:
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch76 = &match;
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
                                                        expr.reset(new otava::ast::PostfixDecExprNode(sourcePos, expr.release(), lexer.GetSourcePos(pos)));
                                                    }
                                                    *parentMatch76 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch55 = match;
                                                }
                                                break;
                                            }
                                        }
                                        *parentMatch54 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch53 = match;
                                    }
                                    else
                                    {
                                        lexer.SetPos(save);
                                        break;
                                    }
                                }
                            }
                        }
                        *parentMatch52 = match;
                    }
                    *parentMatch51 = match;
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::CppCastExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CppCastExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475241);
    std::unique_ptr<otava::ast::Node> op = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos laPos = soul::ast::SourcePos();
    soul::ast::SourcePos raPos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> typeId;
    std::unique_ptr<otava::ast::Node> child;
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
                                        switch (*lexer)
                                        {
                                            case DYNAMIC_CAST:
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch10 = &match;
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
                                                        op.reset(new otava::ast::DynamicCastNode(lexer.GetSourcePos(pos)));
                                                    }
                                                    *parentMatch10 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch9 = match;
                                                }
                                                break;
                                            }
                                            case STATIC_CAST:
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
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
                                                        op.reset(new otava::ast::StaticCastNode(lexer.GetSourcePos(pos)));
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
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == REINTERPRET_CAST)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        op.reset(new otava::ast::ReinterpretCastNode(lexer.GetSourcePos(pos)));
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
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == CONST_CAST)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        op.reset(new otava::ast::ConstCastNode(lexer.GetSourcePos(pos)));
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
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch15 = &match;
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
                                                laPos = lexer.GetSourcePos(pos);
                                            }
                                            *parentMatch15 = match;
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
                                    soul::parser::Match match = TypeParser<Lexer>::TypeId(lexer, context);
                                    typeId.reset(static_cast<otava::ast::Node*>(match.value));
                                    *parentMatch16 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
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
                                    soul::parser::Match match(false);
                                    if (*lexer == RANGLE)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        raPos = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch18 = match;
                                }
                                *parentMatch17 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
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
                                soul::parser::Match match(false);
                                if (*lexer == LPAREN)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    lpPos = lexer.GetSourcePos(pos);
                                }
                                *parentMatch20 = match;
                            }
                            *parentMatch19 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch21 = &match;
                    {
                        soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer, context);
                        child.reset(static_cast<otava::ast::Node*>(match.value));
                        *parentMatch21 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch22 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch23 = &match;
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
                            rpPos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch23 = match;
                    }
                    *parentMatch22 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CppCastExpression");
                #endif
                return soul::parser::Match(true, new otava::ast::CppCastExprNode(lexer.GetSourcePos(pos), typeId.release(), child.release(), op.release(), laPos, raPos, lpPos, rpPos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CppCastExpression");
        else soul::lexer::WriteFailureToLog(lexer, "CppCastExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::TypeIdExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeIdExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475242);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> child = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> typeId;
    std::unique_ptr<otava::ast::Node> expr;
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
                            if (*lexer == TYPEID)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                sourcePos = lexer.GetSourcePos(pos);
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
                                soul::parser::Match match(false);
                                if (*lexer == LPAREN)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    lpPos = lexer.GetSourcePos(pos);
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch10 = &match;
                            {
                                int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch11 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = TypeParser<Lexer>::TypeId(lexer, context);
                                    typeId.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        child.reset(typeId.release());
                                    }
                                    *parentMatch11 = match;
                                }
                                *parentMatch10 = match;
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
                                            soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer, context);
                                            expr.reset(static_cast<otava::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                child.reset(expr.release());
                                            }
                                            *parentMatch13 = match;
                                        }
                                        *parentMatch12 = match;
                                    }
                                    *parentMatch10 = match;
                                }
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
                soul::parser::Match* parentMatch14 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch15 = &match;
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
                            rpPos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch15 = match;
                    }
                    *parentMatch14 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeIdExpression");
                #endif
                return soul::parser::Match(true, new otava::ast::TypeIdExprNode(sourcePos, child.release(), lpPos, rpPos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeIdExpression");
        else soul::lexer::WriteFailureToLog(lexer, "TypeIdExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::IntrinsicInvokeExpr(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IntrinsicInvokeExpr");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475243);
    std::unique_ptr<otava::ast::Node> exprNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::InvokeExprNode> invokeNode = std::unique_ptr<otava::ast::InvokeExprNode>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> primaryExpr;
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
                    soul::parser::Match match = ExpressionParser<Lexer>::PrimaryExpression(lexer, context);
                    primaryExpr.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        exprNode.reset(primaryExpr.release());
                        sourcePos = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
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
                                            lpPos = lexer.GetSourcePos(pos);
                                            invokeNode.reset(new otava::ast::InvokeExprNode(lexer.GetSourcePos(pos), exprNode.release()));
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch10 = &match;
                                    {
                                        soul::parser::Match match = FunctionParser<Lexer>::ParameterDeclarationClause(lexer, context, invokeNode.get());
                                        *parentMatch10 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch11 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch12 = &match;
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
                                            rpPos = lexer.GetSourcePos(pos);
                                            invokeNode->SetLParenPos(lpPos);
                                            invokeNode->SetRParenPos(rpPos);
                                            exprNode.reset(invokeNode.release());
                                        }
                                        *parentMatch12 = match;
                                    }
                                    *parentMatch11 = match;
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch6 = match;
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
                                        soul::parser::Match* parentMatch15 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch16 = &match;
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
                                                    lpPos = lexer.GetSourcePos(pos);
                                                    invokeNode.reset(new otava::ast::InvokeExprNode(lexer.GetSourcePos(pos), exprNode.release()));
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
                                                int64_t save = lexer.GetPos();
                                                soul::parser::Match* parentMatch18 = &match;
                                                {
                                                    soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, context, invokeNode.get());
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
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch20 = &match;
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
                                                    rpPos = lexer.GetSourcePos(pos);
                                                    invokeNode->SetLParenPos(lpPos);
                                                    invokeNode->SetRParenPos(rpPos);
                                                    exprNode.reset(invokeNode.release());
                                                }
                                                *parentMatch20 = match;
                                            }
                                            *parentMatch19 = match;
                                        }
                                        *parentMatch14 = match;
                                    }
                                    *parentMatch13 = match;
                                }
                                *parentMatch6 = match;
                            }
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IntrinsicInvokeExpr");
                #endif
                return soul::parser::Match(true, exprNode.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IntrinsicInvokeExpr");
        else soul::lexer::WriteFailureToLog(lexer, "IntrinsicInvokeExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::PrimaryExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PrimaryExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475244);
    std::unique_ptr<otava::ast::Node> literal;
    std::unique_ptr<otava::ast::Node> foldExpr;
    std::unique_ptr<otava::ast::Node> parenExpr;
    std::unique_ptr<otava::ast::Node> idExpr;
    std::unique_ptr<otava::ast::Node> lambdaExpr;
    std::unique_ptr<otava::ast::Node> requiresExpr;
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
                    int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    switch (*lexer)
                    {
                        case BEGIN_RAW_STRING_LITERAL:
                        case CHARACTER_LITERAL:
                        case FALSE:
                        case FLOATING_LITERAL:
                        case INTEGER_LITERAL:
                        case NULLPTR:
                        case STRING_LITERAL:
                        case TRUE:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch5 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = LiteralParser<Lexer>::Literal(lexer, context);
                                literal.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                                        #endif
                                        return soul::parser::Match(true, literal.release());
                                    }
                                }
                                *parentMatch5 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case THIS:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
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
                                        #endif
                                        return soul::parser::Match(true, new otava::ast::ThisNode(lexer.GetSourcePos(pos)));
                                    }
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case LPAREN:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::FoldExpression(lexer, context);
                                foldExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                                        #endif
                                        return soul::parser::Match(true, foldExpr.release());
                                    }
                                }
                                *parentMatch7 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
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
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ExpressionParser<Lexer>::ParenthesizedExpression(lexer, context);
                                parenExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                                        #endif
                                        return soul::parser::Match(true, parenExpr.release());
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ExpressionParser<Lexer>::IdExpression(lexer, context);
                            idExpr.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                                    #endif
                                    return soul::parser::Match(true, idExpr.release());
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = LambdaParser<Lexer>::LambdaExpression(lexer, context);
                        lambdaExpr.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                                #endif
                                return soul::parser::Match(true, lambdaExpr.release());
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ConceptParser<Lexer>::RequiresExpression(lexer, context);
                    requiresExpr.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PrimaryExpression");
                            #endif
                            return soul::parser::Match(true, requiresExpr.release());
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::FoldExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FoldExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475245);
    std::unique_ptr<otava::ast::FoldExprNode> expr = std::unique_ptr<otava::ast::FoldExprNode>();
    std::unique_ptr<otava::ast::Node> op2Node = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> castExpr1;
    std::unique_ptr<otava::ast::Node> op1;
    std::unique_ptr<otava::ast::Node> ellipsis1;
    std::unique_ptr<otava::ast::Node> op2;
    std::unique_ptr<otava::ast::Node> castExpr2;
    std::unique_ptr<otava::ast::Node> ellipsis3;
    std::unique_ptr<otava::ast::Node> op3;
    std::unique_ptr<otava::ast::Node> castExpr3;
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == LPAREN)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            lpPos = lexer.GetSourcePos(pos);
                            expr.reset(new otava::ast::FoldExprNode(lpPos));
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
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
                                                    soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                                                    castExpr1.reset(static_cast<otava::ast::Node*>(match.value));
                                                    *parentMatch12 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch13 = &match;
                                                    {
                                                        soul::parser::Match match = ExpressionParser<Lexer>::FoldOp(lexer);
                                                        op1.reset(static_cast<otava::ast::Node*>(match.value));
                                                        *parentMatch13 = match;
                                                    }
                                                    *parentMatch12 = match;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch14 = &match;
                                                {
                                                    soul::parser::Match match = PunctuationParser<Lexer>::Ellipsis(lexer);
                                                    ellipsis1.reset(static_cast<otava::ast::Node*>(match.value));
                                                    *parentMatch14 = match;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            *parentMatch10 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch15 = &match;
                                            {
                                                soul::parser::Match match(true);
                                                int64_t save = lexer.GetPos();
                                                soul::parser::Match* parentMatch16 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch17 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch18 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch19 = &match;
                                                            {
                                                                int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = ExpressionParser<Lexer>::FoldOp(lexer);
                                                                op2.reset(static_cast<otava::ast::Node*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    op2Node.reset(op2.release());
                                                                }
                                                                *parentMatch19 = match;
                                                            }
                                                            *parentMatch18 = match;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch20 = &match;
                                                            {
                                                                soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                                                                castExpr2.reset(static_cast<otava::ast::Node*>(match.value));
                                                                *parentMatch20 = match;
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
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    if (match.hit)
                                    {
                                        expr->AddNode(castExpr1.release());
                                        expr->AddNode(op1.release());
                                        expr->AddNode(ellipsis1.release());
                                        if (op2Node)
                                        {
                                            expr->AddNode(op2Node.release());
                                            expr->AddNode(castExpr2.release());
                                        }
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch21 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch22 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch23 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch24 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch25 = &match;
                                                    {
                                                        soul::parser::Match match = PunctuationParser<Lexer>::Ellipsis(lexer);
                                                        ellipsis3.reset(static_cast<otava::ast::Node*>(match.value));
                                                        *parentMatch25 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch26 = &match;
                                                        {
                                                            soul::parser::Match match = ExpressionParser<Lexer>::FoldOp(lexer);
                                                            op3.reset(static_cast<otava::ast::Node*>(match.value));
                                                            *parentMatch26 = match;
                                                        }
                                                        *parentMatch25 = match;
                                                    }
                                                    *parentMatch24 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch27 = &match;
                                                    {
                                                        soul::parser::Match match = ExpressionParser<Lexer>::CastExpression(lexer, context);
                                                        castExpr3.reset(static_cast<otava::ast::Node*>(match.value));
                                                        *parentMatch27 = match;
                                                    }
                                                    *parentMatch24 = match;
                                                }
                                                *parentMatch23 = match;
                                            }
                                            if (match.hit)
                                            {
                                                expr->AddNode(ellipsis3.release());
                                                expr->AddNode(op3.release());
                                                expr->AddNode(castExpr3.release());
                                            }
                                            *parentMatch22 = match;
                                        }
                                        *parentMatch21 = match;
                                    }
                                    *parentMatch7 = match;
                                }
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch28 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch29 = &match;
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
                            rpPos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch29 = match;
                    }
                    *parentMatch28 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            expr->SetLParenPos(lpPos);
            expr->SetRParenPos(rpPos);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldExpression");
                #endif
                return soul::parser::Match(true, expr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldExpression");
        else soul::lexer::WriteFailureToLog(lexer, "FoldExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::FoldOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FoldOp");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475246);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case PLUS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::PlusNode(lexer.GetSourcePos(pos)));
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::MinusNode(lexer.GetSourcePos(pos)));
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
        case STAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::MulNode(lexer.GetSourcePos(pos)));
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
        case DIV:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DivNode(lexer.GetSourcePos(pos)));
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
        case MOD:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == MOD)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ModNode(lexer.GetSourcePos(pos)));
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
        case XOR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == XOR)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ExclusiveOrNode(lexer.GetSourcePos(pos)));
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
        case AMP:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::AndNode(lexer.GetSourcePos(pos)));
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
        case OR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == OR)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::InclusiveOrNode(lexer.GetSourcePos(pos)));
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
        case SHIFT_LEFT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch9 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ShiftLeftNode(lexer.GetSourcePos(pos)));
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
        case SHIFT_RIGHT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch10 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ShiftRightNode(lexer.GetSourcePos(pos)));
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
        case ADD_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == ADD_ASSIGN)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::PlusAssignNode(lexer.GetSourcePos(pos)));
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
        case SUB_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch12 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == SUB_ASSIGN)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::MinusAssignNode(lexer.GetSourcePos(pos)));
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
        case MUL_ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch13 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::MulAssignNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch13 = match;
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
            soul::parser::Match* parentMatch14 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DivAssignNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch14 = match;
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
            soul::parser::Match* parentMatch15 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ModAssignNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch15 = match;
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
            soul::parser::Match* parentMatch16 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::XorAssignNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch16 = match;
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
            soul::parser::Match* parentMatch17 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::AndAssignNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch17 = match;
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
            soul::parser::Match* parentMatch18 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::OrAssignNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch18 = match;
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
            soul::parser::Match* parentMatch19 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ShiftLeftAssignNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch19 = match;
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
            soul::parser::Match* parentMatch20 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ShiftRightAssignNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch20 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case ASSIGN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch21 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::AssignNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch21 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case EQ:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch22 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::EqualNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch22 = match;
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
            soul::parser::Match* parentMatch23 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::NotEqualNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch23 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case LANGLE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch24 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::LessNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch24 = match;
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
            soul::parser::Match* parentMatch25 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::GreaterNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch25 = match;
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
            soul::parser::Match* parentMatch26 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::LessOrEqualNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch26 = match;
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
            soul::parser::Match* parentMatch27 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::GreaterOrEqualNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch27 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case AMP_AMP:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch28 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ConjunctionNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch28 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case OR_OR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch29 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == OR_OR)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DisjunctionNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch29 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case COMMA:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch30 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::CommaNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch30 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case DOT_STAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch31 = &match;
            {
                int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DotStarNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch31 = match;
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
            soul::parser::Match* parentMatch32 = &match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ArrowStarNode(lexer.GetSourcePos(pos)));
                    }
                }
                *parentMatch32 = match;
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FoldOp");
        else soul::lexer::WriteFailureToLog(lexer, "FoldOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ParenthesizedExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParenthesizedExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475247);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> expr;
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == LPAREN)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            sourcePos = lexer.GetSourcePos(pos);
                            lpPos = sourcePos;
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
                        soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer, context);
                        expr.reset(static_cast<otava::ast::Node*>(match.value));
                        *parentMatch5 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                        soul::parser::Match match(false);
                        if (*lexer == RPAREN)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            rpPos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch7 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParenthesizedExpression");
                #endif
                return soul::parser::Match(true, new otava::ast::ParenthesizedExprNode(sourcePos, expr.release(), lpPos, rpPos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParenthesizedExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ParenthesizedExpression");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::DotOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DotOp");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475248);
    std::unique_ptr<otava::ast::Node> dotNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> templateNode = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == DOT)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sourcePos = lexer.GetSourcePos(pos);
                        dotNode.reset(new otava::ast::DotNode(sourcePos));
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
                        soul::parser::Match match(false);
                        if (*lexer == TEMPLATE)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            templateNode.reset(new otava::ast::TemplateNode(lexer.GetSourcePos(pos)));
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DotOp");
                                #endif
                                return soul::parser::Match(true, new otava::ast::PairNode(sourcePos, dotNode.release(), templateNode.release()));
                            }
                        }
                        *parentMatch5 = match;
                    }
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == DOT)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DotOp");
                                #endif
                                return soul::parser::Match(true, new otava::ast::DotNode(lexer.GetSourcePos(pos)));
                            }
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DotOp");
        else soul::lexer::WriteFailureToLog(lexer, "DotOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ArrowOp(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ArrowOp");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475249);
    std::unique_ptr<otava::ast::Node> arrowNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> templateNode = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
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
                    sourcePos = lexer.GetSourcePos(pos);
                    arrowNode.reset(new otava::ast::ArrowNode(sourcePos));
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == TEMPLATE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        templateNode.reset(new otava::ast::TemplateNode(lexer.GetSourcePos(pos)));
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ArrowOp");
                            #endif
                            return soul::parser::Match(true, new otava::ast::PairNode(sourcePos, arrowNode.release(), templateNode.release()));
                        }
                    }
                    *parentMatch4 = match;
                }
                *parentMatch3 = match;
            }
            *parentMatch1 = match;
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ArrowOp");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ArrowNode(lexer.GetSourcePos(pos)));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ArrowOp");
        else soul::lexer::WriteFailureToLog(lexer, "ArrowOp");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::IdExpression(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IdExpression");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475250);
    std::unique_ptr<otava::ast::Node> idExpr;
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
                context->PushResetFlag(otava::symbols::ContextFlags::hasDefiningTypeSpecifier);
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
                soul::parser::Match match = ExpressionParser<Lexer>::IdExpr(lexer, context);
                idExpr.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    context->PopFlags();
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpression");
                        #endif
                        return soul::parser::Match(true, idExpr.release());
                    }
                }
                else
                {
                    context->PopFlags();
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

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::IdExpr(Lexer& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IdExpr");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475251);
    std::unique_ptr<otava::ast::Node> qualifiedId;
    std::unique_ptr<otava::ast::Node> unqualifiedId;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = IdentifierParser<Lexer>::QualifiedId(lexer, context);
            qualifiedId.reset(static_cast<otava::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpr");
                    #endif
                    return soul::parser::Match(true, qualifiedId.release());
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
                    soul::parser::Match match = IdentifierParser<Lexer>::UnqualifiedId(lexer, context);
                    unqualifiedId.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpr");
                            #endif
                            return soul::parser::Match(true, unqualifiedId.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IdExpr");
        else soul::lexer::WriteFailureToLog(lexer, "IdExpr");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ExpressionParser<Lexer>::ExpressionList(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ExpressionList");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 7352148961735475252);
    soul::parser::Match match = InitializationParser<Lexer>::InitializerList(lexer, context, container);
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

template struct ExpressionParser<soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>>;

} // namespace otava::parser::expression
