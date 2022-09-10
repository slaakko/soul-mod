
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/concept.parser' using soul parser generator spg version 4.1.0

module soul.cpp20.parser.concepts;

import util;
import soul.ast.spg;
import soul.ast.source.pos;
import soul.cpp20.ast;
import soul.cpp20.token;
import soul.cpp20.lexer;
import soul.cpp20.symbols;
import soul.cpp20.parser.type;
import soul.cpp20.parser.expression;
import soul.cpp20.parser.function;
import soul.cpp20.parser.identifier;
import soul.cpp20.parser.punctuation;
import soul.cpp20.parser.templates;

using namespace soul::ast::source::pos;
using namespace soul::cpp20::ast;
using namespace soul::cpp20::token;
using namespace soul::cpp20::lexer;
using namespace soul::cpp20::symbols;
using namespace soul::cpp20::parser::type;
using namespace soul::cpp20::parser::expression;
using namespace soul::cpp20::parser::function;
using namespace soul::cpp20::parser::identifier;
using namespace soul::cpp20::parser::punctuation;
using namespace soul::cpp20::parser::templates;

namespace soul::cpp20::parser::concepts {

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::ConceptDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConceptDefinition");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171457);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> conceptName;
    std::unique_ptr<soul::cpp20::ast::Node> assign;
    std::unique_ptr<soul::cpp20::ast::Node> constraintExpr;
    std::unique_ptr<soul::cpp20::ast::Node> semicolon;
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
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == CONCEPT)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
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
                                soul::parser::Match match = ConceptParser<Lexer>::ConceptName(lexer, context);
                                conceptName.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                *parentMatch7 = match;
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
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = PunctuationParser<Lexer>::Assign(lexer);
                                assign.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    context->PushSetFlag(soul::cpp20::symbols::ContextFlags::parsingConceptDefinition);
                                }
                                *parentMatch9 = match;
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
                    soul::parser::Match* parentMatch10 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch11 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ConceptParser<Lexer>::ConstraintExpression(lexer, context);
                            constraintExpr.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                context->PopFlags();
                            }
                            else
                            {
                                context->PopFlags();
                            }
                            *parentMatch11 = match;
                        }
                        *parentMatch10 = match;
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
                    soul::parser::Match match = PunctuationParser<Lexer>::Semicolon(lexer);
                    semicolon.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    *parentMatch12 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::cpp20::ast::ConceptDefinitionNode *conceptDefinitionNode = new soul::cpp20::ast::ConceptDefinitionNode(sourcePos, conceptName.release(), assign.release(), constraintExpr.release(), semicolon.release());
            soul::cpp20::symbols::ProcessConcept(conceptDefinitionNode, context);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConceptDefinition");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, conceptDefinitionNode);
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConceptDefinition");
        else soul::lexer::WriteFailureToLog(lexer, "ConceptDefinition");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::ConceptName(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConceptName");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171458);
    std::unique_ptr<soul::cpp20::ast::Node> identifierNode = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> identifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer, context);
        identifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConceptName");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, identifier.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConceptName");
        else soul::lexer::WriteFailureToLog(lexer, "ConceptName");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::ConceptNameChecked(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConceptNameChecked");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171459);
    std::unique_ptr<soul::cpp20::ast::Node> identifierNode = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> identifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        bool pass = true;
        soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer, context);
        identifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
        if (match.hit)
        {
            identifierNode.reset(identifier.release());
            pass = soul::cpp20::symbols::IsConceptName(identifierNode.get(), context);
            if (pass)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConceptNameChecked");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, identifierNode.release());
                }
            }
        }
        if (match.hit && !pass)
        {
            match = soul::parser::Match(false);
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConceptNameChecked");
        else soul::lexer::WriteFailureToLog(lexer, "ConceptNameChecked");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::ConstraintExpression(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConstraintExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171460);
    std::unique_ptr<soul::cpp20::ast::Node> logicalOrExpr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = ExpressionParser<Lexer>::LogicalOrExpression(lexer, context);
        logicalOrExpr.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstraintExpression");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, logicalOrExpr.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstraintExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ConstraintExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::RequiresClause(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RequiresClause");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171461);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> orExpr;
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
                    if (*lexer == REQUIRES)
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
                    soul::parser::Match match = ConceptParser<Lexer>::ConstraintLogicalOrExpression(lexer, context);
                    orExpr.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RequiresClause");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::RequiresClauseNode(sourcePos, orExpr.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RequiresClause");
        else soul::lexer::WriteFailureToLog(lexer, "RequiresClause");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::ConstraintLogicalOrExpression(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConstraintLogicalOrExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171462);
    std::unique_ptr<soul::cpp20::ast::Node> node = std::unique_ptr<soul::cpp20::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos opPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> left;
    std::unique_ptr<soul::cpp20::ast::Node> right;
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
                    soul::parser::Match match = ConceptParser<Lexer>::ConstraintLogicalAndExpression(lexer, context);
                    left.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        node.reset(left.release());
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
                                                soul::parser::Match match = ConceptParser<Lexer>::ConstraintLogicalAndExpression(lexer, context);
                                                right.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    node.reset(new soul::cpp20::ast::BinaryExprNode(sourcePos, new soul::cpp20::ast::DisjunctionNode(opPos), node.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstraintLogicalOrExpression");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstraintLogicalOrExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ConstraintLogicalOrExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::ConstraintLogicalAndExpression(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConstraintLogicalAndExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171463);
    std::unique_ptr<soul::cpp20::ast::Node> node = std::unique_ptr<soul::cpp20::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos opPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> left;
    std::unique_ptr<soul::cpp20::ast::Node> right;
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
                    left.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        node.reset(left.release());
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
                                                soul::parser::Match match = ExpressionParser<Lexer>::PrimaryExpression(lexer, context);
                                                right.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    node.reset(new soul::cpp20::ast::BinaryExprNode(sourcePos, new soul::cpp20::ast::ConjunctionNode(opPos), node.release(), right.release()));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstraintLogicalAndExpression");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConstraintLogicalAndExpression");
        else soul::lexer::WriteFailureToLog(lexer, "ConstraintLogicalAndExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::RequiresExpression(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RequiresExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171464);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> params;
    std::unique_ptr<soul::cpp20::ast::Node> body;
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
                        if (*lexer == REQUIRES)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            sourcePos = lexer.GetSourcePos(pos);
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
                            soul::parser::Match match = ConceptParser<Lexer>::RequirementParameterList(lexer, context);
                            params.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                soul::parser::Match* parentMatch7 = &match;
                {
                    soul::parser::Match match = ConceptParser<Lexer>::RequirementBody(lexer, context);
                    body.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    *parentMatch7 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RequiresExpression");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::RequiresExprNode(sourcePos, params.release(), body.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RequiresExpression");
        else soul::lexer::WriteFailureToLog(lexer, "RequiresExpression");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::RequirementParameterList(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RequirementParameterList");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171465);
    std::unique_ptr<soul::cpp20::ast::ParameterListNode> node = std::unique_ptr<soul::cpp20::ast::ParameterListNode>();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
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
                            node.reset(new soul::cpp20::ast::ParameterListNode(lpPos));
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
                        soul::parser::Match match = FunctionParser<Lexer>::ParameterDeclarationClause(lexer, context, node.get());
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
            node->SetLParenPos(lpPos);
            node->SetRParenPos(rpPos);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RequirementParameterList");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RequirementParameterList");
        else soul::lexer::WriteFailureToLog(lexer, "RequirementParameterList");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::RequirementBody(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RequirementBody");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171466);
    std::unique_ptr<soul::cpp20::ast::RequirementBodyNode> node = std::unique_ptr<soul::cpp20::ast::RequirementBodyNode>();
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
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
                        if (*lexer == LBRACE)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            lbPos = lexer.GetSourcePos(pos);
                            node.reset(new soul::cpp20::ast::RequirementBodyNode(lbPos));
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
                        soul::parser::Match match = ConceptParser<Lexer>::RequirementSeq(lexer, context, node.get());
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
                        if (*lexer == RBRACE)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            rbPos = lexer.GetSourcePos(pos);
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
            node->SetLBracePos(lbPos);
            node->SetRBracePos(rbPos);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RequirementBody");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RequirementBody");
        else soul::lexer::WriteFailureToLog(lexer, "RequirementBody");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::RequirementSeq(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* requirementBody)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RequirementSeq");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171467);
    std::unique_ptr<soul::cpp20::ast::Node> requirement;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = ConceptParser<Lexer>::Requirement(lexer, context);
                requirement.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    requirementBody->AddNode(requirement.release());
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(true);
        soul::parser::Match* parentMatch3 = &match;
        while (true)
        {
            int64_t save = lexer.GetPos();
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ConceptParser<Lexer>::Requirement(lexer, context);
                        requirement.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            requirementBody->AddNode(requirement.release());
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
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RequirementSeq");
        else soul::lexer::WriteFailureToLog(lexer, "RequirementSeq");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::Requirement(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Requirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171468);
    std::unique_ptr<soul::cpp20::ast::Node> nestedRequirement;
    std::unique_ptr<soul::cpp20::ast::Node> typeRequirement;
    std::unique_ptr<soul::cpp20::ast::Node> compoundRequirement;
    std::unique_ptr<soul::cpp20::ast::Node> simpleRequirement;
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
                    soul::parser::Match match = ConceptParser<Lexer>::NestedRequirement(lexer, context);
                    nestedRequirement.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Requirement");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
                            return soul::parser::Match(true, nestedRequirement.release());
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
                            soul::parser::Match match = ConceptParser<Lexer>::TypeRequirement(lexer, context);
                            typeRequirement.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Requirement");
                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                    return soul::parser::Match(true, typeRequirement.release());
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ConceptParser<Lexer>::CompoundRequirement(lexer, context);
                        compoundRequirement.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Requirement");
                                #endif SOUL_PARSER_DEBUG_SUPPORT
                                return soul::parser::Match(true, compoundRequirement.release());
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
                    soul::parser::Match match = ConceptParser<Lexer>::SimpleRequirement(lexer, context);
                    simpleRequirement.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Requirement");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
                            return soul::parser::Match(true, simpleRequirement.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Requirement");
        else soul::lexer::WriteFailureToLog(lexer, "Requirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::SimpleRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SimpleRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171469);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> expr;
    std::unique_ptr<soul::cpp20::ast::Node> semicolon;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer, context);
            expr.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                soul::parser::Match match = PunctuationParser<Lexer>::Semicolon(lexer);
                semicolon.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleRequirement");
                        #endif SOUL_PARSER_DEBUG_SUPPORT
                        return soul::parser::Match(true, new soul::cpp20::ast::SimpleRequirementNode(sourcePos, expr.release(), semicolon.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleRequirement");
        else soul::lexer::WriteFailureToLog(lexer, "SimpleRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::TypeRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171470);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> nns;
    std::unique_ptr<soul::cpp20::ast::Node> typeName;
    std::unique_ptr<soul::cpp20::ast::Node> semicolon;
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == TYPENAME)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            sourcePos = lexer.GetSourcePos(pos);
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
                            soul::parser::Match match = IdentifierParser<Lexer>::NestedNameSpecifier(lexer, context);
                            nns.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                soul::parser::Match* parentMatch7 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch8 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match(true);
                        if (match.hit)
                        {
                            context->PushSetFlag(soul::cpp20::symbols::ContextFlags::assumeType);
                        }
                        *parentMatch8 = match;
                    }
                    *parentMatch7 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
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
                    soul::parser::Match match = TypeParser<Lexer>::TypeName(lexer, context);
                    typeName.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        context->PopFlags();
                    }
                    else
                    {
                        context->PopFlags();
                    }
                    *parentMatch10 = match;
                }
                *parentMatch9 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = PunctuationParser<Lexer>::Semicolon(lexer);
                semicolon.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeRequirement");
                        #endif SOUL_PARSER_DEBUG_SUPPORT
                        return soul::parser::Match(true, new soul::cpp20::ast::TypeRequirementNode(sourcePos, nns.release(), typeName.release(), semicolon.release()));
                    }
                }
                *parentMatch12 = match;
            }
            *parentMatch11 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeRequirement");
        else soul::lexer::WriteFailureToLog(lexer, "TypeRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::CompoundRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CompoundRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171471);
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> expr;
    std::unique_ptr<soul::cpp20::ast::Node> noexcept_;
    std::unique_ptr<soul::cpp20::ast::Node> returnTypeRequirement;
    std::unique_ptr<soul::cpp20::ast::Node> semicolon;
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
                                    soul::parser::Match match(false);
                                    if (*lexer == LBRACE)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        lbPos = lexer.GetSourcePos(pos);
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
                                    soul::parser::Match match = ExpressionParser<Lexer>::Expression(lexer, context);
                                    expr.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    *parentMatch8 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
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
                                    if (*lexer == RBRACE)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        rbPos = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch11 = &match;
                        {
                            soul::parser::Match match(true);
                            int64_t save = lexer.GetPos();
                            soul::parser::Match* parentMatch12 = &match;
                            {
                                soul::parser::Match match = FunctionParser<Lexer>::Noexcept(lexer);
                                noexcept_.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
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
                            soul::parser::Match match = ConceptParser<Lexer>::ReturnTypeRequirement(lexer, context);
                            returnTypeRequirement.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch15 = &match;
                {
                    soul::parser::Match match = PunctuationParser<Lexer>::Semicolon(lexer);
                    semicolon.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundRequirement");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::CompoundRequirementNode(lbPos, expr.release(), noexcept_.release(), returnTypeRequirement.release(), semicolon.release(), lbPos, rbPos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundRequirement");
        else soul::lexer::WriteFailureToLog(lexer, "CompoundRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::ReturnTypeRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ReturnTypeRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171472);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> typeConstraint;
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
                    if (*lexer == ARROW)
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
                    soul::parser::Match match = ConceptParser<Lexer>::TypeConstraint(lexer, context);
                    typeConstraint.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ReturnTypeRequirement");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::ReturnTypeRequirementNode(sourcePos, typeConstraint.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ReturnTypeRequirement");
        else soul::lexer::WriteFailureToLog(lexer, "ReturnTypeRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::NestedRequirement(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NestedRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171473);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> constraintExpr;
    std::unique_ptr<soul::cpp20::ast::Node> semicolon;
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
                        if (*lexer == REQUIRES)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            sourcePos = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = ConceptParser<Lexer>::ConstraintExpression(lexer, context);
                        constraintExpr.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                    soul::parser::Match match = PunctuationParser<Lexer>::Semicolon(lexer);
                    semicolon.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NestedRequirement");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::NestedRequirementNode(sourcePos, constraintExpr.release(), semicolon.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NestedRequirement");
        else soul::lexer::WriteFailureToLog(lexer, "NestedRequirement");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ConceptParser<Lexer>::TypeConstraint(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeConstraint");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 7901898380417171474);
    std::unique_ptr<soul::cpp20::ast::TypeConstraintNode> node = std::unique_ptr<soul::cpp20::ast::TypeConstraintNode>();
    std::unique_ptr<soul::cpp20::ast::Node> conceptName = std::unique_ptr<soul::cpp20::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos laPos = soul::ast::SourcePos();
    soul::ast::SourcePos raPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> nns;
    std::unique_ptr<soul::cpp20::ast::Node> conceptName1;
    std::unique_ptr<soul::cpp20::ast::Node> conceptName2;
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
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IdentifierParser<Lexer>::NestedNameSpecifier(lexer, context);
                                        nns.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            sourcePos = lexer.GetSourcePos(pos);
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
                                            soul::parser::Match match = ConceptParser<Lexer>::ConceptNameChecked(lexer, context);
                                            conceptName1.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                conceptName.reset(new soul::cpp20::ast::QualifiedIdNode(sourcePos, nns.release(), conceptName1.release()));
                                            }
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
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
                                            soul::parser::Match match = ConceptParser<Lexer>::ConceptNameChecked(lexer, context);
                                            conceptName2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                sourcePos = lexer.GetSourcePos(pos);
                                                conceptName.reset(conceptName2.release());
                                            }
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            node.reset(new soul::cpp20::ast::TypeConstraintNode(sourcePos, conceptName.release()));
                        }
                        *parentMatch4 = match;
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch17 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch18 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        auto vars = static_cast<Lexer::VariableClassType*>(lexer.GetVariables());
                                        soul::parser::Match match(false);
                                        if (*lexer == LANGLE)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            laPos = lexer.GetSourcePos(pos);
                                            ++vars->langleCount;
                                            context->PushSetFlag(soul::cpp20::symbols::ContextFlags::parsingTemplateId);
                                            node->SetHasTemplateArgumentList();
                                        }
                                        *parentMatch18 = match;
                                    }
                                    *parentMatch17 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch19 = &match;
                                    {
                                        soul::parser::Match match(true);
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match* parentMatch20 = &match;
                                        {
                                            soul::parser::Match match = TemplateParser<Lexer>::TemplateArgumentList(lexer, context, node.get());
                                            if (match.hit)
                                            {
                                                *parentMatch20 = match;
                                            }
                                            else
                                            {
                                                lexer.SetPos(save);
                                            }
                                        }
                                        *parentMatch19 = match;
                                    }
                                    *parentMatch17 = match;
                                }
                                *parentMatch16 = match;
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
                                        auto vars = static_cast<Lexer::VariableClassType*>(lexer.GetVariables());
                                        soul::parser::Match match(false);
                                        if (*lexer == RANGLE)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            raPos = lexer.GetSourcePos(pos);
                                            --vars->langleCount;
                                            context->PopFlags();
                                        }
                                        else
                                        {
                                            --vars->langleCount;
                                            context->PopFlags();
                                        }
                                        *parentMatch22 = match;
                                    }
                                    *parentMatch21 = match;
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            node->SetLAnglePos(laPos);
            node->SetRAnglePos(raPos);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeConstraint");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeConstraint");
        else soul::lexer::WriteFailureToLog(lexer, "TypeConstraint");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct ConceptParser<soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>>;

} // namespace soul::cpp20::parser::concepts
