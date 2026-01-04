
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/statement.parser' using soul parser generator ospg version 5.0.0

module otava.parser.statement;

import util;
import soul.ast.spg;
import soul.ast.common;
import soul.ast.source.pos;
import soul.ast.lexer.pos.pair;
import otava.ast;
import otava.token;
import otava.lexer;
import otava.symbols;
import otava.parser.attribute;
import otava.parser.declaration;
import otava.parser.expression;
import otava.parser.identifier;
import otava.parser.initialization;
import otava.parser.recorded.parse;
import otava.parser.guard;
import otava.parser.punctuation;
import otava.parser.type;
import otava.token.parser;
import soul.ast.lexer.pos.pair;

namespace otava::parser::statement {

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::Statement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Statement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585281);
    std::unique_ptr<otava::ast::Node> labeledStatement;
    std::unique_ptr<otava::ast::Node> compoundStatement;
    std::unique_ptr<otava::ast::Node> selectionStatement;
    std::unique_ptr<otava::ast::Node> iterationStatement;
    std::unique_ptr<otava::ast::Node> jumpStatement;
    std::unique_ptr<otava::ast::Node> expressionStatement;
    std::unique_ptr<otava::ast::Node> declarationStatement;
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
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::LabeledStatement(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                labeledStatement.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Statement");
                                        #endif
                                        return soul::parser::Match(true, labeledStatement.release());
                                    }
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
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
                                        std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::CompoundStatement(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        compoundStatement.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Statement");
                                                #endif
                                                return soul::parser::Match(true, compoundStatement.release());
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch9 = &match;
                            lexer.SetPos(save);
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::SelectionStatement(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    selectionStatement.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Statement");
                                            #endif
                                            return soul::parser::Match(true, selectionStatement.release());
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch11 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch12 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::IterationStatement(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                iterationStatement.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Statement");
                                        #endif
                                        return soul::parser::Match(true, iterationStatement.release());
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch13 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::JumpStatement(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            jumpStatement.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Statement");
                                    #endif
                                    return soul::parser::Match(true, jumpStatement.release());
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch15 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch16 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::ExpressionStatement(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        expressionStatement.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Statement");
                                #endif
                                return soul::parser::Match(true, expressionStatement.release());
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch17 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch18 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::DeclarationStatement(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    declarationStatement.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Statement");
                            #endif
                            return soul::parser::Match(true, declarationStatement.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Statement");
        else soul::lexer::WriteFailureToLog(lexer, "Statement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::LabeledStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LabeledStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585282);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos labelPos = soul::ast::SourcePos();
    std::int64_t labelP = std::int64_t();
    soul::ast::SourcePos colonPos = soul::ast::SourcePos();
    soul::ast::SourcePos casePos = soul::ast::SourcePos();
    soul::ast::SourcePos defaultPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> stmt;
    std::unique_ptr<otava::ast::Node> caseExpr;
    std::unique_ptr<otava::ast::Node> stmt2;
    std::unique_ptr<otava::ast::Node> stmt3;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                switch (*lexer)
                {
                    case otava::token::ID:
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
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == otava::token::ID)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        sourcePos = *sp;
                                        labelPos = sourcePos;
                                        labelP = pos;
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
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == otava::token::COLON)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            colonPos = *sp;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch10 = match;
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
                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    stmt.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        auto t = lexer.GetToken(labelP);
                                        if (!t) return std::unexpected<int>(t.error());
                                        const auto *token = *t;
                                        auto i = otava::token::parser::ParseIdentifier(labelPos, lexer.FileName(), *token);
                                        if (!i) return std::unexpected<int>(i.error());
                                        otava::ast::IdentifierNode *identifierNode = *i;
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LabeledStatement");
                                            #endif
                                            return soul::parser::Match(true, new otava::ast::LabeledStatementNode(sourcePos, identifierNode, stmt.release(), attributes.release(), colonPos));
                                        }
                                    }
                                    *parentMatch13 = match;
                                }
                                *parentMatch12 = match;
                            }
                            *parentMatch7 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch6 = match;
                        }
                        break;
                    }
                    case otava::token::CASE:
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
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == otava::token::CASE)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            casePos = *sp;
                                            if (!sourcePos.IsValid())
                                            {
                                                sourcePos = casePos;
                                            }
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
                                        std::expected<soul::parser::Match, int> m = otava::parser::expression::ExpressionParser<LexerT>::ConstantExpression(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        caseExpr.reset(static_cast<otava::ast::Node*>(match.value));
                                        *parentMatch18 = match;
                                    }
                                    *parentMatch16 = match;
                                }
                                *parentMatch15 = match;
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
                                        soul::parser::Match match(false);
                                        if (*lexer == otava::token::COLON)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            colonPos = *sp;
                                        }
                                        *parentMatch20 = match;
                                    }
                                    *parentMatch19 = match;
                                }
                                *parentMatch15 = match;
                            }
                            *parentMatch14 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch21 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch22 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    stmt2.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LabeledStatement");
                                            #endif
                                            return soul::parser::Match(true, new otava::ast::CaseStatementNode(sourcePos, caseExpr.release(), stmt2.release(), attributes.release(), casePos, colonPos));
                                        }
                                    }
                                    *parentMatch22 = match;
                                }
                                *parentMatch21 = match;
                            }
                            *parentMatch14 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch6 = match;
                        }
                        break;
                    }
                    case otava::token::DEFAULT:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch23 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch24 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch25 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == otava::token::DEFAULT)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        defaultPos = *sp;
                                        if (!sourcePos.IsValid())
                                        {
                                            sourcePos = defaultPos;
                                        }
                                    }
                                    *parentMatch25 = match;
                                }
                                *parentMatch24 = match;
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
                                        soul::parser::Match match(false);
                                        if (*lexer == otava::token::COLON)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            colonPos = *sp;
                                        }
                                        *parentMatch27 = match;
                                    }
                                    *parentMatch26 = match;
                                }
                                *parentMatch24 = match;
                            }
                            *parentMatch23 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch28 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch29 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    stmt3.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LabeledStatement");
                                            #endif
                                            return soul::parser::Match(true, new otava::ast::DefaultStatementNode(sourcePos, stmt3.release(), attributes.release(), defaultPos, colonPos));
                                        }
                                    }
                                    *parentMatch29 = match;
                                }
                                *parentMatch28 = match;
                            }
                            *parentMatch23 = match;
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
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LabeledStatement");
        else soul::lexer::WriteFailureToLog(lexer, "LabeledStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::CompoundStatementUnguarded(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CompoundStatementUnguarded");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585283);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::CompoundStatementNode> compoundStatementNode = std::unique_ptr<otava::ast::CompoundStatementNode>();
    std::unique_ptr<otava::ast::Node> statementNode = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
    bool nextIsRBrace = bool();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> stmt;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == otava::token::LBRACE)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    lbPos = *sp;
                                    if (!sourcePos.IsValid())
                                    {
                                        sourcePos = lbPos;
                                    }
                                    compoundStatementNode.reset(new otava::ast::CompoundStatementNode(sourcePos));
                                    compoundStatementNode->SetAttributes(attributes.release());
                                    auto rv = otava::symbols::BeginBlock(sourcePos, context);
                                    if (!rv) return std::unexpected<int>(rv.error());
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
                                                    std::int64_t save = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch14 = &match;
                                                    {
                                                        std::int64_t save = lexer.GetPos();
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch15 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                                                            if (!m) return std::unexpected<int>(m.error());
                                                            soul::parser::Match match = *m;
                                                            stmt.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                statementNode.reset(stmt.release());
                                                                auto rv = compoundStatementNode->AddNode(statementNode.release());
                                                                if (!rv) return std::unexpected<int>(rv.error());
                                                            }
                                                            *parentMatch15 = match;
                                                        }
                                                        *parentMatch14 = match;
                                                        if (!match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch16 = &match;
                                                            lexer.SetPos(save);
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch17 = &match;
                                                                {
                                                                    std::int64_t pos = lexer.GetPos();
                                                                    bool pass = true;
                                                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::RBraceNext(lexer);
                                                                    if (!m) return std::unexpected<int>(m.error());
                                                                    soul::parser::Match match = *m;
                                                                    if (match.hit)
                                                                    {
                                                                        nextIsRBrace = true;
                                                                        pass = false;
                                                                    }
                                                                    if (match.hit && !pass)
                                                                    {
                                                                        match = soul::parser::Match(false);
                                                                    }
                                                                    *parentMatch17 = match;
                                                                }
                                                                *parentMatch16 = match;
                                                            }
                                                            *parentMatch14 = match;
                                                        }
                                                    }
                                                    *parentMatch13 = match;
                                                    if (!match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch18 = &match;
                                                        lexer.SetPos(save);
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch19 = &match;
                                                            {
                                                                std::int64_t pos = lexer.GetPos();
                                                                bool pass = true;
                                                                soul::parser::Match match(true);
                                                                if (match.hit)
                                                                {
                                                                    if (!nextIsRBrace)
                                                                    {
                                                                        auto sp = lexer.GetSourcePos(pos);
                                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                                        std::unexpected<int> rv = otava::symbols::ReturnStatementParsingError(*sp, context);
                                                                        return std::unexpected<int>(rv.error());
                                                                    }
                                                                    else
                                                                    {
                                                                        pass = false;
                                                                    }
                                                                }
                                                                if (match.hit && !pass)
                                                                {
                                                                    match = soul::parser::Match(false);
                                                                }
                                                                *parentMatch19 = match;
                                                            }
                                                            *parentMatch18 = match;
                                                        }
                                                        *parentMatch13 = match;
                                                    }
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
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
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
                                soul::parser::Match match(false);
                                if (*lexer == otava::token::RBRACE)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    rbPos = *sp;
                                }
                                *parentMatch21 = match;
                            }
                            *parentMatch20 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    compoundStatementNode->SetLBracePos(lbPos);
                    compoundStatementNode->SetRBracePos(rbPos);
                    otava::symbols::MapNode(compoundStatementNode.get(), context);
                    auto rv = otava::symbols::EndBlock(context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatementUnguarded");
                        #endif
                        return soul::parser::Match(true, compoundStatementNode.release());
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatementUnguarded");
        else soul::lexer::WriteFailureToLog(lexer, "CompoundStatementUnguarded");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::RBraceNext(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RBraceNext");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585284);
    soul::parser::Match match(true);
    std::int64_t save = lexer.GetPos();
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == otava::token::RBRACE)
            {
                auto a = ++lexer;
                if (!a) return std::unexpected<int>(a.error());
                match.hit = true;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            *parentMatch0 = match;
            lexer.SetPos(save);
        }
        else
        {
            *parentMatch0 = soul::parser::Match(false);
            lexer.SetPos(save);
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RBraceNext");
        else soul::lexer::WriteFailureToLog(lexer, "RBraceNext");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::CompoundStatementGuarded(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CompoundStatementGuarded");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585285);
    std::unique_ptr<otava::ast::CompoundStatementNode> compoundStatementNode = std::unique_ptr<otava::ast::CompoundStatementNode>();
    std::unique_ptr<otava::ast::Node> attributes;
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
                    std::int64_t pos = lexer.GetPos();
                    bool pass = true;
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        soul::ast::SourcePos sourcePos = *sp;
                        std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int> rv = otava::parser::recorded::parse::RecordCompoundStatement(lexer);
                        if (!rv) return std::unexpected<int>(rv.error());
                        soul::ast::lexer::pos::pair::LexerPosPair lexerPosPair = std::move(*rv);
                        if (lexerPosPair.IsValid())
                        {
                            compoundStatementNode.reset(new otava::ast::CompoundStatementNode(sourcePos));
                            compoundStatementNode->SetLexerPosPair(lexerPosPair);
                            compoundStatementNode->SetAttributes(attributes.release());
                            compoundStatementNode->SetFunctionScope(context->GetSymbolTable()->CurrentScope());
                        }
                        else
                        {
                            pass = false;
                        }
                    }
                    if (match.hit && !pass)
                    {
                        match = soul::parser::Match(false);
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
                            bool pass = true;
                            soul::parser::Match match(true);
                            if (match.hit)
                            {
                                auto sp = lexer.GetSourcePos(pos);
                                if (!sp) return std::unexpected<int>(sp.error());
                                soul::ast::SourcePos sourcePos = *sp;
                                std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int> rv = otava::parser::recorded::parse::RecordCompoundStatement(lexer);
                                if (!rv) return std::unexpected<int>(rv.error());
                                soul::ast::lexer::pos::pair::LexerPosPair lexerPosPair = std::move(*rv);
                                if (lexerPosPair.IsValid())
                                {
                                    compoundStatementNode.reset(new otava::ast::CompoundStatementNode(sourcePos));
                                    compoundStatementNode->SetLexerPosPair(lexerPosPair);
                                    compoundStatementNode->SetFunctionScope(context->GetSymbolTable()->CurrentScope());
                                }
                                else
                                {
                                    pass = false;
                                }
                            }
                            if (match.hit && !pass)
                            {
                                match = soul::parser::Match(false);
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatementGuarded");
                #endif
                return soul::parser::Match(true, compoundStatementNode.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatementGuarded");
        else soul::lexer::WriteFailureToLog(lexer, "CompoundStatementGuarded");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::CompoundStatementSaved(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CompoundStatementSaved");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585286);
    otava::ast::CompoundStatementNode* compoundStatementNode = nullptr;
    std::unique_ptr<otava::ast::Node> statementNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> stmt;
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
                std::int64_t pos = lexer.GetPos();
                bool pass = true;
                soul::parser::Match match(true);
                if (match.hit)
                {
                    std::expected<otava::ast::CompoundStatementNode*, int> rv = otava::parser::recorded::parse::GetSavedCompoundStatementNode(context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    compoundStatementNode = *rv;
                    if (!compoundStatementNode)
                    {
                        pass = false;
                    }
                    lexer.BeginRecordedParse(compoundStatementNode->GetLexerPosPair());
                    otava::symbols::Scope *functionScope = static_cast<otava::symbols::Scope*>(compoundStatementNode->FunctionScope());
                    context->GetSymbolTable()->BeginScope(functionScope);
                }
                if (match.hit && !pass)
                {
                    match = soul::parser::Match(false);
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
                                if (*lexer == otava::token::LBRACE)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    soul::ast::SourcePos sourcePos = *sp;
                                    compoundStatementNode->SetLBracePos(sourcePos);
                                    auto rv = otava::symbols::BeginBlock(sourcePos, context);
                                    if (!rv) return std::unexpected<int>(rv.error());
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
                                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul::parser::Match match = *m;
                                                    stmt.reset(static_cast<otava::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        statementNode.reset(stmt.release());
                                                        auto rv = compoundStatementNode->AddNode(statementNode.release());
                                                        if (!rv) return std::unexpected<int>(rv.error());
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == otava::token::RBRACE)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    compoundStatementNode->SetRBracePos(*sp);
                                    lexer.EndRecordedParse();
                                    otava::symbols::MapNode(compoundStatementNode, context);
                                    auto rv = otava::symbols::EndBlock(context);
                                    if (!rv) return std::unexpected<int>(rv.error());
                                    rv = context->GetSymbolTable()->EndScope();
                                    if (!rv) return std::unexpected<int>(rv.error());
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatementSaved");
                                        #endif
                                        return soul::parser::Match(true, compoundStatementNode);
                                    }
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
            *parentMatch1 = match;
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
                    bool pass = true;
                    soul::parser::Match match(true);
                    if (match.hit)
                    {
                        lexer.EndRecordedParse();
                        auto rv = context->GetSymbolTable()->EndScope();
                        if (!rv) return std::unexpected<int>(rv.error());
                        pass = false;
                    }
                    if (match.hit && !pass)
                    {
                        match = soul::parser::Match(false);
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatementSaved");
        else soul::lexer::WriteFailureToLog(lexer, "CompoundStatementSaved");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::CompoundStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CompoundStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585287);
    std::unique_ptr<otava::ast::Node> guardedCompoundStatement;
    std::unique_ptr<otava::ast::Node> savedCompoundStatement;
    std::unique_ptr<otava::ast::Node> unguardedCompoundStatement;
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
                    std::expected<soul::parser::Match, int> m = otava::parser::guard::GuardParser<LexerT>::MemberFunctionGuard(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    *parentMatch3 = match;
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
                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::CompoundStatementGuarded(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            guardedCompoundStatement.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatement");
                                    #endif
                                    return soul::parser::Match(true, guardedCompoundStatement.release());
                                }
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = otava::parser::guard::GuardParser<LexerT>::SavedMemberFunctionBodyGuard(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                if (match.hit)
                                {
                                    context->ResetFlag(otava::symbols::ContextFlags::parseSavedMemberFunctionBody);
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
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::CompoundStatementSaved(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    savedCompoundStatement.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatement");
                                            #endif
                                            return soul::parser::Match(true, savedCompoundStatement.release());
                                        }
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch7 = match;
                        }
                        *parentMatch6 = match;
                    }
                    *parentMatch2 = match;
                }
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
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::CompoundStatementUnguarded(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        unguardedCompoundStatement.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatement");
                                #endif
                                return soul::parser::Match(true, unguardedCompoundStatement.release());
                            }
                        }
                        *parentMatch12 = match;
                    }
                    *parentMatch11 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompoundStatement");
        else soul::lexer::WriteFailureToLog(lexer, "CompoundStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::SelectionStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SelectionStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585288);
    std::unique_ptr<otava::ast::Node> ifStmt;
    std::unique_ptr<otava::ast::Node> switchStmt;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::IfStatement(lexer, context);
            if (!m) return std::unexpected<int>(m.error());
            soul::parser::Match match = *m;
            ifStmt.reset(static_cast<otava::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SelectionStatement");
                    #endif
                    return soul::parser::Match(true, ifStmt.release());
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
                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::SwitchStatement(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    switchStmt.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SelectionStatement");
                            #endif
                            return soul::parser::Match(true, switchStmt.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SelectionStatement");
        else soul::lexer::WriteFailureToLog(lexer, "SelectionStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::IfStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IfStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585289);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos ifPos = soul::ast::SourcePos();
    soul::ast::SourcePos constExprPos = soul::ast::SourcePos();
    soul::ast::SourcePos elsePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> initStmt;
    std::unique_ptr<otava::ast::Node> cond;
    std::unique_ptr<otava::ast::Node> thenStmt;
    std::unique_ptr<otava::ast::Node> elseStmt;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
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
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == otava::token::IF)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        auto sp = lexer.GetSourcePos(pos);
                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                        ifPos = *sp;
                                                        if (!sourcePos.IsValid())
                                                        {
                                                            sourcePos = ifPos;
                                                        }
                                                        auto rv = otava::symbols::BeginBlock(sourcePos, context);
                                                        if (!rv) return std::unexpected<int>(rv.error());
                                                    }
                                                    *parentMatch14 = match;
                                                }
                                                *parentMatch13 = match;
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
                                                                if (*lexer == otava::token::CONSTEXPR)
                                                                {
                                                                    auto a = ++lexer;
                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                    match.hit = true;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    auto sp = lexer.GetSourcePos(pos);
                                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                                    constExprPos = *sp;
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
                                                *parentMatch13 = match;
                                            }
                                            *parentMatch12 = match;
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
                                                    soul::parser::Match match(false);
                                                    if (*lexer == otava::token::LPAREN)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        auto sp = lexer.GetSourcePos(pos);
                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                        lpPos = *sp;
                                                    }
                                                    *parentMatch20 = match;
                                                }
                                                *parentMatch19 = match;
                                            }
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch11 = match;
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
                                                std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::InitStatement(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                initStmt.reset(static_cast<otava::ast::Node*>(match.value));
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
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch10 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch23 = &match;
                                    {
                                        std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Condition(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        cond.reset(static_cast<otava::ast::Node*>(match.value));
                                        *parentMatch23 = match;
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
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
                                        if (*lexer == otava::token::RPAREN)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            rpPos = *sp;
                                        }
                                        *parentMatch25 = match;
                                    }
                                    *parentMatch24 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch8 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch26 = &match;
                            {
                                std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                thenStmt.reset(static_cast<otava::ast::Node*>(match.value));
                                *parentMatch26 = match;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch27 = &match;
                        {
                            soul::parser::Match match(true);
                            std::int64_t save = lexer.GetPos();
                            soul::parser::Match* parentMatch28 = &match;
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
                                            std::int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == otava::token::ELSE)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                auto sp = lexer.GetSourcePos(pos);
                                                if (!sp) return std::unexpected<int>(sp.error());
                                                elsePos = *sp;
                                            }
                                            *parentMatch31 = match;
                                        }
                                        *parentMatch30 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch32 = &match;
                                        {
                                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            elseStmt.reset(static_cast<otava::ast::Node*>(match.value));
                                            *parentMatch32 = match;
                                        }
                                        *parentMatch30 = match;
                                    }
                                    *parentMatch29 = match;
                                }
                                if (match.hit)
                                {
                                    *parentMatch28 = match;
                                }
                                else
                                {
                                    lexer.SetPos(save);
                                }
                            }
                            *parentMatch27 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    otava::ast::IfStatementNode *node = new otava::ast::IfStatementNode(sourcePos, initStmt.release(), cond.release(), thenStmt.release(), elseStmt.release(), attributes.release(), ifPos, lpPos, rpPos, constExprPos, elsePos);
                    otava::symbols::MapNode(node, context);
                    auto rv = otava::symbols::EndBlock(context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IfStatement");
                        #endif
                        return soul::parser::Match(true, node);
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IfStatement");
        else soul::lexer::WriteFailureToLog(lexer, "IfStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::SwitchStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SwitchStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585290);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos switchPos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> initStmt;
    std::unique_ptr<otava::ast::Node> cond;
    std::unique_ptr<otava::ast::Node> stmt;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                            if (*lexer == otava::token::SWITCH)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                auto sp = lexer.GetSourcePos(pos);
                                                if (!sp) return std::unexpected<int>(sp.error());
                                                switchPos = *sp;
                                                if (!sourcePos.IsValid())
                                                {
                                                    sourcePos = switchPos;
                                                }
                                                auto rv = otava::symbols::BeginBlock(sourcePos, context);
                                                if (!rv) return std::unexpected<int>(rv.error());
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
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == otava::token::LPAREN)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    lpPos = *sp;
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
                                        soul::parser::Match match(true);
                                        std::int64_t save = lexer.GetPos();
                                        soul::parser::Match* parentMatch16 = &match;
                                        {
                                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::InitStatement(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            initStmt.reset(static_cast<otava::ast::Node*>(match.value));
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch17 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Condition(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    cond.reset(static_cast<otava::ast::Node*>(match.value));
                                    *parentMatch17 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch8 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch18 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch19 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == otava::token::RPAREN)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        rpPos = *sp;
                                    }
                                    *parentMatch19 = match;
                                }
                                *parentMatch18 = match;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch20 = &match;
                        {
                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            stmt.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch20 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    otava::ast::SwitchStatementNode *node = new otava::ast::SwitchStatementNode(sourcePos, initStmt.release(), cond.release(), stmt.release(), attributes.release(), switchPos, lpPos, rpPos);
                    otava::symbols::MapNode(node, context);
                    auto rv = otava::symbols::EndBlock(context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SwitchStatement");
                        #endif
                        return soul::parser::Match(true, node);
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SwitchStatement");
        else soul::lexer::WriteFailureToLog(lexer, "SwitchStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::IterationStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IterationStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585291);
    std::unique_ptr<otava::ast::Node> whileStmt;
    std::unique_ptr<otava::ast::Node> doStmt;
    std::unique_ptr<otava::ast::Node> rangeForStmt;
    std::unique_ptr<otava::ast::Node> forStmt;
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
                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::WhileStatement(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    whileStmt.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IterationStatement");
                            #endif
                            return soul::parser::Match(true, whileStmt.release());
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
                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::DoStatement(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            doStmt.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IterationStatement");
                                    #endif
                                    return soul::parser::Match(true, doStmt.release());
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
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::RangeForStatement(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        rangeForStmt.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IterationStatement");
                                #endif
                                return soul::parser::Match(true, rangeForStmt.release());
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
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::ForStatement(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    forStmt.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IterationStatement");
                            #endif
                            return soul::parser::Match(true, forStmt.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IterationStatement");
        else soul::lexer::WriteFailureToLog(lexer, "IterationStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::WhileStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "WhileStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585292);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos whilePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> cond;
    std::unique_ptr<otava::ast::Node> stmt;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == otava::token::WHILE)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            whilePos = *sp;
                                            if (!sourcePos.IsValid())
                                            {
                                                sourcePos = whilePos;
                                            }
                                            auto rv = otava::symbols::BeginBlock(sourcePos, context);
                                            if (!rv) return std::unexpected<int>(rv.error());
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch10 = match;
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
                                            soul::parser::Match match(false);
                                            if (*lexer == otava::token::LPAREN)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                auto sp = lexer.GetSourcePos(pos);
                                                if (!sp) return std::unexpected<int>(sp.error());
                                                lpPos = *sp;
                                            }
                                            *parentMatch13 = match;
                                        }
                                        *parentMatch12 = match;
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch14 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Condition(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    cond.reset(static_cast<otava::ast::Node*>(match.value));
                                    *parentMatch14 = match;
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
                                    soul::parser::Match match(false);
                                    if (*lexer == otava::token::RPAREN)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        rpPos = *sp;
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
                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            stmt.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch17 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    otava::ast::WhileStatementNode *node = new otava::ast::WhileStatementNode(sourcePos, cond.release(), stmt.release(), attributes.release(), whilePos, lpPos, rpPos);
                    otava::symbols::MapNode(node, context);
                    auto rv = otava::symbols::EndBlock(context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "WhileStatement");
                        #endif
                        return soul::parser::Match(true, node);
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "WhileStatement");
        else soul::lexer::WriteFailureToLog(lexer, "WhileStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::DoStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DoStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585293);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos doPos = soul::ast::SourcePos();
    soul::ast::SourcePos whilePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> stmt;
    std::unique_ptr<otava::ast::Node> expr;
    std::unique_ptr<otava::ast::Node> semicolon;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch12 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch13 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                if (*lexer == otava::token::DO)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    doPos = *sp;
                                                    if (!sourcePos.IsValid())
                                                    {
                                                        sourcePos = doPos;
                                                    }
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
                                                std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                stmt.reset(static_cast<otava::ast::Node*>(match.value));
                                                *parentMatch14 = match;
                                            }
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch11 = match;
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
                                                if (*lexer == otava::token::WHILE)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    auto sp = lexer.GetSourcePos(pos);
                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                    whilePos = *sp;
                                                }
                                                *parentMatch16 = match;
                                            }
                                            *parentMatch15 = match;
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
                                            soul::parser::Match match(false);
                                            if (*lexer == otava::token::LPAREN)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                auto sp = lexer.GetSourcePos(pos);
                                                if (!sp) return std::unexpected<int>(sp.error());
                                                lpPos = *sp;
                                            }
                                            *parentMatch18 = match;
                                        }
                                        *parentMatch17 = match;
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch19 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::expression::ExpressionParser<LexerT>::Expression(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    expr.reset(static_cast<otava::ast::Node*>(match.value));
                                    *parentMatch19 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch8 = match;
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
                                    soul::parser::Match match(false);
                                    if (*lexer == otava::token::RPAREN)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        rpPos = *sp;
                                    }
                                    *parentMatch21 = match;
                                }
                                *parentMatch20 = match;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch22 = &match;
                        {
                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch22 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DoStatement");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DoStatementNode(sourcePos, stmt.release(), expr.release(), attributes.release(), semicolon.release(), doPos, whilePos, lpPos, rpPos));
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DoStatement");
        else soul::lexer::WriteFailureToLog(lexer, "DoStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::RangeForStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RangeForStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585294);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos forPos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    soul::ast::SourcePos colonPos = soul::ast::SourcePos();
    bool blockOpen = bool();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> initStmt;
    std::unique_ptr<otava::ast::Node> declaration;
    std::unique_ptr<otava::ast::Node> initializer;
    std::unique_ptr<otava::ast::Node> stmt;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
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
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == otava::token::FOR)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        auto sp = lexer.GetSourcePos(pos);
                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                        forPos = *sp;
                                                        if (!sourcePos.IsValid())
                                                        {
                                                            sourcePos = forPos;
                                                        }
                                                        auto rv = otava::symbols::BeginBlock(sourcePos, context);
                                                        if (!rv) return std::unexpected<int>(rv.error());
                                                        blockOpen = true;
                                                    }
                                                    *parentMatch14 = match;
                                                }
                                                *parentMatch13 = match;
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
                                                        if (*lexer == otava::token::LPAREN)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            auto sp = lexer.GetSourcePos(pos);
                                                            if (!sp) return std::unexpected<int>(sp.error());
                                                            lpPos = *sp;
                                                        }
                                                        *parentMatch16 = match;
                                                    }
                                                    *parentMatch15 = match;
                                                }
                                                *parentMatch13 = match;
                                            }
                                            *parentMatch12 = match;
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
                                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::InitStatement(lexer, context);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul::parser::Match match = *m;
                                                    initStmt.reset(static_cast<otava::ast::Node*>(match.value));
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
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch19 = &match;
                                        {
                                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::ForRangeDeclaration(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            declaration.reset(static_cast<otava::ast::Node*>(match.value));
                                            *parentMatch19 = match;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch10 = match;
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
                                            soul::parser::Match match(false);
                                            if (*lexer == otava::token::COLON)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                auto sp = lexer.GetSourcePos(pos);
                                                if (!sp) return std::unexpected<int>(sp.error());
                                                colonPos = *sp;
                                            }
                                            *parentMatch21 = match;
                                        }
                                        *parentMatch20 = match;
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch22 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::ForRangeInitializer(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    initializer.reset(static_cast<otava::ast::Node*>(match.value));
                                    *parentMatch22 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch8 = match;
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
                                    soul::parser::Match match(false);
                                    if (*lexer == otava::token::RPAREN)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        rpPos = *sp;
                                    }
                                    *parentMatch24 = match;
                                }
                                *parentMatch23 = match;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch25 = &match;
                        {
                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            stmt.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch25 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    otava::ast::RangeForStatementNode *node = new otava::ast::RangeForStatementNode(sourcePos, initStmt.release(), declaration.release(), initializer.release(), stmt.release(), attributes.release(), forPos, lpPos, rpPos, colonPos);
                    otava::symbols::MapNode(node, context);
                    auto rv = otava::symbols::EndBlock(context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RangeForStatement");
                        #endif
                        return soul::parser::Match(true, node);
                    }
                }
                else
                {
                    if (blockOpen)
                    {
                        auto rv = otava::symbols::RemoveBlock(context);
                        if (!rv) return std::unexpected<int>(rv.error());
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RangeForStatement");
        else soul::lexer::WriteFailureToLog(lexer, "RangeForStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::ForRangeDeclaration(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ForRangeDeclaration");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585295);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> node = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> declSpecifierSeq = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> declSpecifierSeq1;
    std::unique_ptr<otava::ast::Node> declarator;
    std::unique_ptr<otava::ast::Node> refQualifier;
    std::unique_ptr<otava::ast::Node> identifiers;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                            std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::DeclSpecifierSeq(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            declSpecifierSeq1.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                if (!sourcePos.IsValid())
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    sourcePos = *sp;
                                }
                                declSpecifierSeq.reset(declSpecifierSeq1.release());
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch11 = &match;
                                {
                                    std::int64_t save = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch12 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::Declarator(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        declarator.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            node.reset(new otava::ast::ForRangeDeclarationNode(sourcePos, declSpecifierSeq.release(), declarator.release(), attributes.release()));
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
                                                                soul::parser::Match match(true);
                                                                std::int64_t save = lexer.GetPos();
                                                                soul::parser::Match* parentMatch19 = &match;
                                                                {
                                                                    std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::RefQualifier(lexer);
                                                                    if (!m) return std::unexpected<int>(m.error());
                                                                    soul::parser::Match match = *m;
                                                                    refQualifier.reset(static_cast<otava::ast::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        *parentMatch19 = match;
                                                                    }
                                                                    else
                                                                    {
                                                                        lexer.SetPos(save);
                                                                    }
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
                                                                        std::int64_t pos = lexer.GetPos();
                                                                        soul::parser::Match match(false);
                                                                        if (*lexer == otava::token::LBRACKET)
                                                                        {
                                                                            auto a = ++lexer;
                                                                            if (!a) return std::unexpected<int>(a.error());
                                                                            match.hit = true;
                                                                        }
                                                                        if (match.hit)
                                                                        {
                                                                            auto sp = lexer.GetSourcePos(pos);
                                                                            if (!sp) return std::unexpected<int>(sp.error());
                                                                            lbPos = *sp;
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
                                                                std::expected<soul::parser::Match, int> m = otava::parser::identifier::IdentifierParser<LexerT>::IdentifierList(lexer, context);
                                                                if (!m) return std::unexpected<int>(m.error());
                                                                soul::parser::Match match = *m;
                                                                identifiers.reset(static_cast<otava::ast::Node*>(match.value));
                                                                *parentMatch22 = match;
                                                            }
                                                            *parentMatch17 = match;
                                                        }
                                                        *parentMatch16 = match;
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
                                                                soul::parser::Match match(false);
                                                                if (*lexer == otava::token::RBRACKET)
                                                                {
                                                                    auto a = ++lexer;
                                                                    if (!a) return std::unexpected<int>(a.error());
                                                                    match.hit = true;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    auto sp = lexer.GetSourcePos(pos);
                                                                    if (!sp) return std::unexpected<int>(sp.error());
                                                                    rbPos = *sp;
                                                                }
                                                                *parentMatch24 = match;
                                                            }
                                                            *parentMatch23 = match;
                                                        }
                                                        *parentMatch16 = match;
                                                    }
                                                    *parentMatch15 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    node.reset(new otava::ast::StructuredBindingNode(sourcePos, declSpecifierSeq.release(), refQualifier.release(), identifiers.release(), nullptr, attributes.release(), nullptr, lbPos, rbPos));
                                                }
                                                *parentMatch14 = match;
                                            }
                                            *parentMatch13 = match;
                                        }
                                        *parentMatch11 = match;
                                    }
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
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ForRangeDeclaration");
                        #endif
                        return soul::parser::Match(true, node.release());
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ForRangeDeclaration");
        else soul::lexer::WriteFailureToLog(lexer, "ForRangeDeclaration");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::ForRangeInitializer(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ForRangeInitializer");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585296);
    std::unique_ptr<otava::ast::Node> initializer;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        std::expected<soul::parser::Match, int> m = otava::parser::initialization::InitializationParser<LexerT>::ExprOrBracedInitList(lexer, context);
        if (!m) return std::unexpected<int>(m.error());
        soul::parser::Match match = *m;
        initializer.reset(static_cast<otava::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ForRangeInitializer");
                #endif
                return soul::parser::Match(true, initializer.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ForRangeInitializer");
        else soul::lexer::WriteFailureToLog(lexer, "ForRangeInitializer");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::ForStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ForStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585297);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos forPos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> initStmt;
    std::unique_ptr<otava::ast::Node> cond;
    std::unique_ptr<otava::ast::Node> semicolon;
    std::unique_ptr<otava::ast::Node> loopExpr;
    std::unique_ptr<otava::ast::Node> stmt;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
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
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match(false);
                                                    if (*lexer == otava::token::FOR)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        auto sp = lexer.GetSourcePos(pos);
                                                        if (!sp) return std::unexpected<int>(sp.error());
                                                        forPos = *sp;
                                                        if (!sourcePos.IsValid())
                                                        {
                                                            sourcePos = forPos;
                                                        }
                                                        auto rv = otava::symbols::BeginBlock(sourcePos, context);
                                                        if (!rv) return std::unexpected<int>(rv.error());
                                                    }
                                                    *parentMatch14 = match;
                                                }
                                                *parentMatch13 = match;
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
                                                        if (*lexer == otava::token::LPAREN)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            auto sp = lexer.GetSourcePos(pos);
                                                            if (!sp) return std::unexpected<int>(sp.error());
                                                            lpPos = *sp;
                                                        }
                                                        *parentMatch16 = match;
                                                    }
                                                    *parentMatch15 = match;
                                                }
                                                *parentMatch13 = match;
                                            }
                                            *parentMatch12 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch17 = &match;
                                            {
                                                std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::InitStatement(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                initStmt.reset(static_cast<otava::ast::Node*>(match.value));
                                                *parentMatch17 = match;
                                            }
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch18 = &match;
                                        {
                                            soul::parser::Match match(true);
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match* parentMatch19 = &match;
                                            {
                                                std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Condition(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                cond.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    *parentMatch19 = match;
                                                }
                                                else
                                                {
                                                    lexer.SetPos(save);
                                                }
                                            }
                                            *parentMatch18 = match;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch10 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch20 = &match;
                                    {
                                        std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                                        *parentMatch20 = match;
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
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
                                        std::expected<soul::parser::Match, int> m = otava::parser::expression::ExpressionParser<LexerT>::Expression(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        loopExpr.reset(static_cast<otava::ast::Node*>(match.value));
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
                                *parentMatch9 = match;
                            }
                            *parentMatch8 = match;
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
                                    soul::parser::Match match(false);
                                    if (*lexer == otava::token::RPAREN)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        rpPos = *sp;
                                    }
                                    *parentMatch24 = match;
                                }
                                *parentMatch23 = match;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch25 = &match;
                        {
                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::Statement(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            stmt.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch25 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    otava::ast::ForStatementNode *node = new otava::ast::ForStatementNode(sourcePos, initStmt.release(), cond.release(), loopExpr.release(), stmt.release(), attributes.release(), semicolon.release(), forPos, lpPos, rpPos);
                    otava::symbols::MapNode(node, context);
                    auto rv = otava::symbols::EndBlock(context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ForStatement");
                        #endif
                        return soul::parser::Match(true, node);
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ForStatement");
        else soul::lexer::WriteFailureToLog(lexer, "ForStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::JumpStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "JumpStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585298);
    std::unique_ptr<otava::ast::Node> breakStatement;
    std::unique_ptr<otava::ast::Node> continueStatement;
    std::unique_ptr<otava::ast::Node> returnStatement;
    std::unique_ptr<otava::ast::Node> coRoutineReturnStatement;
    std::unique_ptr<otava::ast::Node> gotoStatement;
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
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::BreakStatement(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        breakStatement.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "JumpStatement");
                                #endif
                                return soul::parser::Match(true, breakStatement.release());
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
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::ContinueStatement(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                continueStatement.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "JumpStatement");
                                        #endif
                                        return soul::parser::Match(true, continueStatement.release());
                                    }
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
                    soul::parser::Match* parentMatch7 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch8 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::ReturnStatement(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            returnStatement.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "JumpStatement");
                                    #endif
                                    return soul::parser::Match(true, returnStatement.release());
                                }
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
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
                        std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::CoroutineReturnStatement(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        coRoutineReturnStatement.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "JumpStatement");
                                #endif
                                return soul::parser::Match(true, coRoutineReturnStatement.release());
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
                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::GotoStatement(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    gotoStatement.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "JumpStatement");
                            #endif
                            return soul::parser::Match(true, gotoStatement.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "JumpStatement");
        else soul::lexer::WriteFailureToLog(lexer, "JumpStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::BreakStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BreakStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585299);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos breakPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> semicolon;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                            soul::parser::Match match(false);
                            if (*lexer == otava::token::BREAK)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                auto sp = lexer.GetSourcePos(pos);
                                if (!sp) return std::unexpected<int>(sp.error());
                                breakPos = *sp;
                                if (!sourcePos.IsValid())
                                {
                                    sourcePos = breakPos;
                                }
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
                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch9 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BreakStatement");
                        #endif
                        return soul::parser::Match(true, new otava::ast::BreakStatementNode(sourcePos, attributes.release(), semicolon.release(), breakPos));
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BreakStatement");
        else soul::lexer::WriteFailureToLog(lexer, "BreakStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::ContinueStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ContinueStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585300);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos continuePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> semicolon;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                            soul::parser::Match match(false);
                            if (*lexer == otava::token::CONTINUE)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                auto sp = lexer.GetSourcePos(pos);
                                if (!sp) return std::unexpected<int>(sp.error());
                                continuePos = *sp;
                                if (!sourcePos.IsValid())
                                {
                                    sourcePos = continuePos;
                                }
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
                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch9 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ContinueStatement");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ContinueStatementNode(sourcePos, attributes.release(), semicolon.release(), continuePos));
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ContinueStatement");
        else soul::lexer::WriteFailureToLog(lexer, "ContinueStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::ReturnStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ReturnStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585301);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos returnPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> returnValue;
    std::unique_ptr<otava::ast::Node> semicolon;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == otava::token::RETURN)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    returnPos = *sp;
                                    if (!sourcePos.IsValid())
                                    {
                                        sourcePos = returnPos;
                                    }
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
                                soul::parser::Match match(true);
                                std::int64_t save = lexer.GetPos();
                                soul::parser::Match* parentMatch11 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::initialization::InitializationParser<LexerT>::ExprOrBracedInitList(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    returnValue.reset(static_cast<otava::ast::Node*>(match.value));
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
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch12 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ReturnStatement");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ReturnStatementNode(sourcePos, returnValue.release(), attributes.release(), semicolon.release(), returnPos));
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ReturnStatement");
        else soul::lexer::WriteFailureToLog(lexer, "ReturnStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::CoroutineReturnStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CoroutineReturnStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585302);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos coReturnPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> returnValue;
    std::unique_ptr<otava::ast::Node> semicolon;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == otava::token::CO_RETURN)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    coReturnPos = *sp;
                                    if (!sourcePos.IsValid())
                                    {
                                        sourcePos = coReturnPos;
                                    }
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
                                soul::parser::Match match(true);
                                std::int64_t save = lexer.GetPos();
                                soul::parser::Match* parentMatch11 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::initialization::InitializationParser<LexerT>::ExprOrBracedInitList(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    returnValue.reset(static_cast<otava::ast::Node*>(match.value));
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
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch12 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CoroutineReturnStatement");
                        #endif
                        return soul::parser::Match(true, new otava::ast::CoReturnStatementNode(sourcePos, returnValue.release(), attributes.release(), semicolon.release(), coReturnPos));
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CoroutineReturnStatement");
        else soul::lexer::WriteFailureToLog(lexer, "CoroutineReturnStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::GotoStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "GotoStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585303);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos gotoPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> target;
    std::unique_ptr<otava::ast::Node> semicolon;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == otava::token::GOTO)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    gotoPos = *sp;
                                    if (!sourcePos.IsValid())
                                    {
                                        sourcePos = gotoPos;
                                    }
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
                                std::expected<soul::parser::Match, int> m = otava::parser::identifier::IdentifierParser<LexerT>::Identifier(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                target.reset(static_cast<otava::ast::Node*>(match.value));
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
                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                            *parentMatch11 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "GotoStatement");
                        #endif
                        return soul::parser::Match(true, new otava::ast::GotoStatementNode(sourcePos, target.release(), attributes.release(), semicolon.release(), gotoPos));
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "GotoStatement");
        else soul::lexer::WriteFailureToLog(lexer, "GotoStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::ExpressionStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ExpressionStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585304);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> expr = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> expr1;
    std::unique_ptr<otava::ast::Node> semicolon;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(true);
        std::int64_t save = lexer.GetPos();
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        sourcePos = *sp;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                *parentMatch1 = match;
            }
            else
            {
                lexer.SetPos(save);
            }
        }
        *parentMatch0 = match;
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
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul::parser::Match, int> m = otava::parser::expression::ExpressionParser<LexerT>::Expression(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    expr1.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        expr.reset(expr1.release());
                                        if (!sourcePos.IsValid())
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            sourcePos = *sp;
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
                                        soul::parser::Match match(true);
                                        *parentMatch11 = match;
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
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch13 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    if (!sourcePos.IsValid())
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        sourcePos = *sp;
                                    }
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
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExpressionStatement");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ExpressionStatementNode(sourcePos, expr.release(), attributes.release(), semicolon.release()));
                    }
                }
                *parentMatch5 = match;
            }
            *parentMatch4 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ExpressionStatement");
        else soul::lexer::WriteFailureToLog(lexer, "ExpressionStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::DeclarationStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DeclarationStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585305);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> declaration;
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
                    soul::parser::Match match(true);
                    if (match.hit)
                    {
                        context->PushSetFlag(otava::symbols::ContextFlags::saveDeclarations);
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
                        std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::BlockDeclaration(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        declaration.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            auto sp = lexer.GetSourcePos(pos);
                            if (!sp) return std::unexpected<int>(sp.error());
                            sourcePos = *sp;
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
            context->PopFlags();
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclarationStatement");
                #endif
                return soul::parser::Match(true, new otava::ast::DeclarationStatementNode(sourcePos, declaration.release()));
            }
        }
        else
        {
            context->PopFlags();
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclarationStatement");
        else soul::lexer::WriteFailureToLog(lexer, "DeclarationStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::InitStatement(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "InitStatement");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585306);
    std::unique_ptr<otava::ast::Node> simpleDeclaration;
    std::unique_ptr<otava::ast::Node> expressionStatement;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(true);
                if (match.hit)
                {
                    context->PushSetFlag(otava::symbols::ContextFlags::saveDeclarations);
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
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            std::int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::SimpleDeclaration(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                simpleDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitStatement");
                                        #endif
                                        return soul::parser::Match(true, simpleDeclaration.release());
                                    }
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
                                        std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::ExpressionStatement(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        expressionStatement.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitStatement");
                                                #endif
                                                return soul::parser::Match(true, expressionStatement.release());
                                            }
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch6 = match;
                            }
                        }
                        *parentMatch5 = match;
                    }
                    if (match.hit)
                    {
                        context->PopFlags();
                    }
                    else
                    {
                        context->PopFlags();
                    }
                    *parentMatch4 = match;
                }
                *parentMatch3 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitStatement");
        else soul::lexer::WriteFailureToLog(lexer, "InitStatement");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> StatementParser<LexerT>::Condition(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Condition");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 4569043890895585307);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> declSpecifiers = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> declSpecifierSeq;
    std::unique_ptr<otava::ast::Node> declarator;
    std::unique_ptr<otava::ast::Node> initializer;
    std::unique_ptr<otava::ast::Node> expr;
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
                                    std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        sourcePos = *sp;
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
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::DeclSpecifierSeq(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                declSpecifierSeq.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    if (!sourcePos.IsValid())
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        sourcePos = *sp;
                                    }
                                    declSpecifiers.reset(declSpecifierSeq.release());
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
                        std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::Declarator(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        declarator.reset(static_cast<otava::ast::Node*>(match.value));
                        *parentMatch10 = match;
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
                    soul::parser::Match* parentMatch12 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = otava::parser::initialization::InitializationParser<LexerT>::BraceOrEqualInitializer(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        initializer.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Condition");
                                #endif
                                return soul::parser::Match(true, new otava::ast::InitConditionNode(sourcePos, declSpecifiers.release(), declarator.release(), initializer.release(), attributes.release()));
                            }
                        }
                        *parentMatch12 = match;
                    }
                    *parentMatch11 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
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
                        std::expected<soul::parser::Match, int> m = otava::parser::expression::ExpressionParser<LexerT>::Expression(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        expr.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Condition");
                                #endif
                                return soul::parser::Match(true, expr.release());
                            }
                        }
                        *parentMatch14 = match;
                    }
                    *parentMatch13 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Condition");
        else soul::lexer::WriteFailureToLog(lexer, "Condition");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct StatementParser<soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>>;

} // namespace otava::parser::statement
