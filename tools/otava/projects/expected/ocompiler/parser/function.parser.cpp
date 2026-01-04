
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/function.parser' using soul parser generator ospg version 5.0.0

module otava.parser.function;

import util;
import soul.ast.spg;
import soul.ast.common;
import soul.ast.source.pos;
import soul.ast.lexer.pos.pair;
import otava.token;
import otava.lexer;
import otava.parser.attribute;
import otava.parser.classes;
import otava.parser.concepts;
import otava.parser.declaration;
import otava.parser.initialization;
import otava.parser.punctuation;
import otava.parser.statement;
import otava.parser.type;
import otava.symbols;

namespace otava::parser::function {

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::FunctionDefinition(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionDefinition");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041793);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> declSpecifierSeqNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> declaratorNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> specifierNode = std::unique_ptr<otava::ast::Node>();
    int scopes = int();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> declSpecifiers;
    std::unique_ptr<otava::ast::Node> declarator;
    std::unique_ptr<otava::ast::Node> virtSpecifiers;
    std::unique_ptr<otava::ast::Node> requiresClause;
    std::unique_ptr<otava::ast::Node> functionBody;
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
                    soul::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
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
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
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
                if (match.hit)
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
                            declSpecifiers.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                declSpecifierSeqNode.reset(declSpecifiers.release());
                                if (!sourcePos.IsValid())
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    sourcePos = *sp;
                                }
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch9 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::DeclaratorPushClassScope(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        declarator.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            if (!sourcePos.IsValid())
                            {
                                auto sp = lexer.GetSourcePos(pos);
                                if (!sp) return std::unexpected<int>(sp.error());
                                sourcePos = *sp;
                            }
                            declaratorNode.reset(declarator.release());
                        }
                        else
                        {
                            auto rv = context->GetSymbolTable()->CurrentScope()->PopParentScope();
                            if (!rv) return std::unexpected<int>(rv.error());
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch12 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch13 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        {
                            std::int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch15 = &match;
                            switch (*lexer)
                            {
                                case otava::token::ID:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch16 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = otava::parser::classes::ClassParser<LexerT>::VirtSpecifierSeq(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        virtSpecifiers.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            specifierNode.reset(virtSpecifiers.release());
                                        }
                                        *parentMatch16 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch15 = match;
                                    }
                                    break;
                                }
                                case otava::token::REQUIRES:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch17 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = otava::parser::concepts::ConceptParser<LexerT>::RequiresClause(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        requiresClause.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            specifierNode.reset(requiresClause.release());
                                        }
                                        *parentMatch17 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch15 = match;
                                    }
                                    break;
                                }
                            }
                            *parentMatch14 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch18 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(true);
                                    *parentMatch18 = match;
                                }
                                *parentMatch14 = match;
                            }
                        }
                        *parentMatch13 = match;
                    }
                    if (match.hit)
                    {
                        bool get = false;
                        std::expected<int, int> rv = otava::symbols::BeginFunctionDefinition(declSpecifierSeqNode.get(), declaratorNode.get(), nullptr, specifierNode.get(), get, context);
                        if (!rv) return std::unexpected<int>(rv.error());
                        scopes = *rv;
                    }
                    *parentMatch12 = match;
                }
                *parentMatch11 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::FunctionBody(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                functionBody.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    otava::ast::Node *node = new otava::ast::FunctionDefinitionNode(sourcePos, attributes.release(), declSpecifierSeqNode.release(), declaratorNode.release(), specifierNode.release(), functionBody.release());
                    auto rv = otava::symbols::EndFunctionDefinition(node, scopes, context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionDefinition");
                        #endif
                        return soul::parser::Match(true, node);
                    }
                }
                *parentMatch20 = match;
            }
            *parentMatch19 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionDefinition");
        else soul::lexer::WriteFailureToLog(lexer, "FunctionDefinition");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::NoDeclSpecFunctionDefinition(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NoDeclSpecFunctionDefinition");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041794);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> declSpecifierSeqNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> declaratorNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> specifierNode = std::unique_ptr<otava::ast::Node>();
    int scopes = int();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> declarator;
    std::unique_ptr<otava::ast::Node> virtSpecifiers;
    std::unique_ptr<otava::ast::Node> requiresClause;
    std::unique_ptr<otava::ast::Node> functionBody;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(true);
                std::int64_t save = lexer.GetPos();
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
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
                    }
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
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::DeclaratorPushClassScope(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        declarator.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            if (!sourcePos.IsValid())
                            {
                                auto sp = lexer.GetSourcePos(pos);
                                if (!sp) return std::unexpected<int>(sp.error());
                                sourcePos = *sp;
                            }
                            declaratorNode.reset(declarator.release());
                        }
                        else
                        {
                            auto rv = context->GetSymbolTable()->CurrentScope()->PopParentScope();
                            if (!rv) return std::unexpected<int>(rv.error());
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch9 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch11 = &match;
                        {
                            std::int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch12 = &match;
                            switch (*lexer)
                            {
                                case otava::token::ID:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch13 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = otava::parser::classes::ClassParser<LexerT>::VirtSpecifierSeq(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        virtSpecifiers.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            specifierNode.reset(virtSpecifiers.release());
                                        }
                                        *parentMatch13 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch12 = match;
                                    }
                                    break;
                                }
                                case otava::token::REQUIRES:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch14 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = otava::parser::concepts::ConceptParser<LexerT>::RequiresClause(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        requiresClause.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            specifierNode.reset(requiresClause.release());
                                        }
                                        *parentMatch14 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch12 = match;
                                    }
                                    break;
                                }
                            }
                            *parentMatch11 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch15 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(true);
                                    *parentMatch15 = match;
                                }
                                *parentMatch11 = match;
                            }
                        }
                        *parentMatch10 = match;
                    }
                    if (match.hit)
                    {
                        bool get = false;
                        std::expected<int, int> rv = otava::symbols::BeginFunctionDefinition(declSpecifierSeqNode.get(), declaratorNode.get(), nullptr, specifierNode.get(), get, context);
                        if (!rv) return std::unexpected<int>(rv.error());
                        scopes = *rv;
                    }
                    *parentMatch9 = match;
                }
                *parentMatch8 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::FunctionBody(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                functionBody.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    otava::ast::Node *node = new otava::ast::FunctionDefinitionNode(sourcePos, attributes.release(), declSpecifierSeqNode.release(), declaratorNode.release(), specifierNode.release(), functionBody.release());
                    auto rv = otava::symbols::EndFunctionDefinition(node, scopes, context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoDeclSpecFunctionDefinition");
                        #endif
                        return soul::parser::Match(true, node);
                    }
                }
                *parentMatch17 = match;
            }
            *parentMatch16 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoDeclSpecFunctionDefinition");
        else soul::lexer::WriteFailureToLog(lexer, "NoDeclSpecFunctionDefinition");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::FunctionBody(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionBody");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041795);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> assign;
    std::unique_ptr<otava::ast::Node> def;
    std::unique_ptr<otava::ast::Node> semicolon;
    std::unique_ptr<otava::ast::Node> del;
    std::unique_ptr<otava::ast::Node> semicolon2;
    std::unique_ptr<otava::ast::Node> ctorInitializer;
    std::unique_ptr<otava::ast::Node> compoundStatement;
    std::unique_ptr<otava::ast::Node> compoundStatement2;
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Assign(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    assign.reset(static_cast<otava::ast::Node*>(match.value));
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
                            case otava::token::DEFAULT:
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::Default(lexer);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    def.reset(static_cast<otava::ast::Node*>(match.value));
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
                                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
                                                    #endif
                                                    return soul::parser::Match(true, new otava::ast::DefaultedOrDeletedFunctionNode(sourcePos, assign.release(), def.release(), semicolon.release()));
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
                                    *parentMatch6 = match;
                                }
                                break;
                            }
                            case otava::token::DELETE:
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::Delete(lexer);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    del.reset(static_cast<otava::ast::Node*>(match.value));
                                    *parentMatch10 = match;
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
                                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Semicolon(lexer);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            semicolon2.reset(static_cast<otava::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
                                                    #endif
                                                    return soul::parser::Match(true, new otava::ast::DefaultedOrDeletedFunctionNode(sourcePos, assign.release(), del.release(), semicolon2.release()));
                                                }
                                            }
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch10 = match;
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch15 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul::parser::Match, int> m = otava::parser::classes::ClassParser<LexerT>::CtorInitializer(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            ctorInitializer.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                auto sp = lexer.GetSourcePos(pos);
                                if (!sp) return std::unexpected<int>(sp.error());
                                sourcePos = *sp;
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch17 = &match;
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
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
                                        #endif
                                        return soul::parser::Match(true, new otava::ast::ConstructorNode(sourcePos, ctorInitializer.release(), compoundStatement.release()));
                                    }
                                }
                                *parentMatch17 = match;
                            }
                            *parentMatch16 = match;
                        }
                        *parentMatch14 = match;
                    }
                    *parentMatch13 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
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
                    std::expected<soul::parser::Match, int> m = otava::parser::statement::StatementParser<LexerT>::CompoundStatement(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    compoundStatement2.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
                            #endif
                            return soul::parser::Match(true, new otava::ast::FunctionBodyNode(*sp, compoundStatement2.release()));
                        }
                    }
                    *parentMatch19 = match;
                }
                *parentMatch18 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
        else soul::lexer::WriteFailureToLog(lexer, "FunctionBody");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::Default(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Default");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041796);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
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
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Default");
                #endif
                return soul::parser::Match(true, new otava::ast::DefaultNode(*sp));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Default");
        else soul::lexer::WriteFailureToLog(lexer, "Default");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::Delete(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Delete");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041797);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == otava::token::DELETE)
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Delete");
                #endif
                return soul::parser::Match(true, new otava::ast::DeleteNode(*sp));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Delete");
        else soul::lexer::WriteFailureToLog(lexer, "Delete");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::ParameterDeclarationClause(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParameterDeclarationClause");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041798);
    std::unique_ptr<otava::ast::Node> comma;
    std::unique_ptr<otava::ast::Node> ellipsis;
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
                context->PushSetFlag(otava::symbols::ContextFlags::parsingParameters);
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
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::ParameterDeclarationList(lexer, context, container);
                                if (!m) return std::unexpected<int>(m.error());
                                soul::parser::Match match = *m;
                                *parentMatch7 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Comma(lexer);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    comma.reset(static_cast<otava::ast::Node*>(match.value));
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch6 = match;
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
                                    std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Ellipsis(lexer);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    ellipsis.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        auto rv = container->AddNode(comma.release());
                                        if (!rv) return std::unexpected<int>(rv.error());
                                        rv = container->AddNode(ellipsis.release());
                                        if (!rv) return std::unexpected<int>(rv.error());
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch6 = match;
                        }
                        *parentMatch5 = match;
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
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                if (match.hit)
                                                {
                                                    auto rv = container->Clear();
                                                    if (!rv) return std::unexpected<int>(rv.error());
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
                                                    std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::ParameterDeclarationList(lexer, context, container);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul::parser::Match match = *m;
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
                                        soul::parser::Match* parentMatch18 = &match;
                                        {
                                            soul::parser::Match match(true);
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match* parentMatch19 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch20 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch21 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Ellipsis(lexer);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul::parser::Match match = *m;
                                                        ellipsis.reset(static_cast<otava::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            auto rv = container->AddNode(ellipsis.release());
                                                            if (!rv) return std::unexpected<int>(rv.error());
                                                        }
                                                        *parentMatch21 = match;
                                                    }
                                                    *parentMatch20 = match;
                                                }
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
                                        *parentMatch13 = match;
                                    }
                                    *parentMatch12 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch22 = &match;
                                    {
                                        soul::parser::Match match(true);
                                        std::int64_t save = lexer.GetPos();
                                        soul::parser::Match* parentMatch23 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch24 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch25 = &match;
                                                {
                                                    std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Comma(lexer);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul::parser::Match match = *m;
                                                    comma.reset(static_cast<otava::ast::Node*>(match.value));
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
                                                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Ellipsis(lexer);
                                                            if (!m) return std::unexpected<int>(m.error());
                                                            soul::parser::Match match = *m;
                                                            ellipsis.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                auto rv = container->AddNode(comma.release());
                                                                if (!rv) return std::unexpected<int>(rv.error());
                                                                rv = container->AddNode(ellipsis.release());
                                                                if (!rv) return std::unexpected<int>(rv.error());
                                                            }
                                                            *parentMatch27 = match;
                                                        }
                                                        *parentMatch26 = match;
                                                    }
                                                    *parentMatch25 = match;
                                                }
                                                *parentMatch24 = match;
                                            }
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
                                    *parentMatch12 = match;
                                }
                                *parentMatch11 = match;
                            }
                            *parentMatch5 = match;
                        }
                    }
                    *parentMatch4 = match;
                }
                if (match.hit)
                {
                    context->PopFlags();
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParameterDeclarationClause");
        else soul::lexer::WriteFailureToLog(lexer, "ParameterDeclarationClause");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::ParameterDeclarationList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParameterDeclarationList");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041799);
    std::unique_ptr<otava::ast::Node> first;
    std::unique_ptr<otava::ast::Node> comma;
    std::unique_ptr<otava::ast::Node> next;
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
                std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::ParameterDeclaration(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul::parser::Match match = *m;
                first.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    auto rv = container->AddNode(first.release());
                    if (!rv) return std::unexpected<int>(rv.error());
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
                soul::parser::Match match(true);
                soul::parser::Match* parentMatch4 = &match;
                {
                    while (true)
                    {
                        std::int64_t save = lexer.GetPos();
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch5 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Comma(lexer);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    comma.reset(static_cast<otava::ast::Node*>(match.value));
                                    *parentMatch6 = match;
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
                                            std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::ParameterDeclaration(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            next.reset(static_cast<otava::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                auto rv = container->AddNode(comma.release());
                                                if (!rv) return std::unexpected<int>(rv.error());
                                                rv = container->AddNode(next.release());
                                                if (!rv) return std::unexpected<int>(rv.error());
                                            }
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                *parentMatch5 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            else
                            {
                                lexer.SetPos(save);
                                break;
                            }
                        }
                    }
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParameterDeclarationList");
        else soul::lexer::WriteFailureToLog(lexer, "ParameterDeclarationList");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::ParameterDeclaration(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParameterDeclaration");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041800);
    std::unique_ptr<otava::ast::ParameterNode> parameterNode = std::unique_ptr<otava::ast::ParameterNode>();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> declSpecifierSeq;
    std::unique_ptr<otava::ast::Node> declarator;
    std::unique_ptr<otava::ast::Node> abstractDeclarator;
    std::unique_ptr<otava::ast::Node> assign;
    std::unique_ptr<otava::ast::Node> initializer;
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
                auto sp = lexer.GetSourcePos(pos);
                if (!sp) return std::unexpected<int>(sp.error());
                parameterNode.reset(new otava::ast::ParameterNode(*sp));
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
                                soul::parser::Match match(true);
                                std::int64_t save = lexer.GetPos();
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            std::expected<soul::parser::Match, int> m = otava::parser::attribute::AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            attributes.reset(static_cast<otava::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                parameterNode->SetAttributes(attributes.release());
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch11 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch12 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::DeclSpecifierSeq(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul::parser::Match match = *m;
                                        declSpecifierSeq.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            parameterNode->SetDeclSpecifiers(declSpecifierSeq.release());
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
                                            std::int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch17 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::Declarator(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                declarator.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    parameterNode->SetDeclarator(declarator.release());
                                                }
                                                *parentMatch17 = match;
                                            }
                                            *parentMatch16 = match;
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
                                                        std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::AbstractDeclarator(lexer, context);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul::parser::Match match = *m;
                                                        abstractDeclarator.reset(static_cast<otava::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            parameterNode->SetDeclarator(abstractDeclarator.release());
                                                        }
                                                        *parentMatch19 = match;
                                                    }
                                                    *parentMatch18 = match;
                                                }
                                                *parentMatch16 = match;
                                            }
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
                            *parentMatch6 = match;
                        }
                        *parentMatch5 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch20 = &match;
                        {
                            soul::parser::Match match(true);
                            std::int64_t save = lexer.GetPos();
                            soul::parser::Match* parentMatch21 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch22 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch23 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch24 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            std::expected<soul::parser::Match, int> m = otava::parser::punctuation::PunctuationParser<LexerT>::Assign(lexer);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul::parser::Match match = *m;
                                            assign.reset(static_cast<otava::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                parameterNode->SetAssign(assign.release());
                                            }
                                            *parentMatch24 = match;
                                        }
                                        *parentMatch23 = match;
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
                                                std::expected<soul::parser::Match, int> m = otava::parser::initialization::InitializationParser<LexerT>::InitializerClause(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul::parser::Match match = *m;
                                                initializer.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    parameterNode->SetInitializer(initializer.release());
                                                }
                                                *parentMatch26 = match;
                                            }
                                            *parentMatch25 = match;
                                        }
                                        *parentMatch23 = match;
                                    }
                                    *parentMatch22 = match;
                                }
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
                        *parentMatch5 = match;
                    }
                    *parentMatch4 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParameterDeclaration");
                        #endif
                        return soul::parser::Match(true, parameterNode.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParameterDeclaration");
        else soul::lexer::WriteFailureToLog(lexer, "ParameterDeclaration");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::OperatorFunctionId(LexerT& lexer, otava::symbols::Context* context)
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
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041801);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> operatorKw;
    std::unique_ptr<otava::ast::Node> op;
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
                    std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::OperatorKw(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    operatorKw.reset(static_cast<otava::ast::Node*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::Operator(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    op.reset(static_cast<otava::ast::Node*>(match.value));
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
                return soul::parser::Match(true, new otava::ast::OperatorFunctionIdNode(sourcePos, operatorKw.release(), op.release()));
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
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::ConversionFunctionId(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConversionFunctionId");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041802);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> operatorKw;
    std::unique_ptr<otava::ast::Node> conversionTypeId;
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
                    std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::OperatorKw(lexer);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    operatorKw.reset(static_cast<otava::ast::Node*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::ConversionTypeId(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    conversionTypeId.reset(static_cast<otava::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConversionFunctionId");
                #endif
                return soul::parser::Match(true, new otava::ast::ConversionFunctionIdNode(sourcePos, operatorKw.release(), conversionTypeId.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConversionFunctionId");
        else soul::lexer::WriteFailureToLog(lexer, "ConversionFunctionId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::DestructorId(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DestructorId");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041803);
    std::unique_ptr<otava::ast::Node> node = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> typeName;
    std::unique_ptr<otava::ast::Node> declTypeSpecifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == otava::token::TILDE)
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
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul::parser::Match, int> m = otava::parser::type::TypeParser<LexerT>::TypeName(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul::parser::Match match = *m;
                            typeName.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                node.reset(typeName.release());
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
                                    std::expected<soul::parser::Match, int> m = otava::parser::type::TypeParser<LexerT>::DeclTypeSpecifier(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul::parser::Match match = *m;
                                    declTypeSpecifier.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        node.reset(declTypeSpecifier.release());
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch5 = match;
                        }
                    }
                    *parentMatch4 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DestructorId");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DestructorIdNode(sourcePos, node.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DestructorId");
        else soul::lexer::WriteFailureToLog(lexer, "DestructorId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::ConversionTypeId(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConversionTypeId");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041804);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> typeSpecifierSeq;
    std::unique_ptr<otava::ast::Node> declarator;
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
                    std::expected<soul::parser::Match, int> m = otava::parser::type::TypeParser<LexerT>::TypeSpecifierSeq(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    typeSpecifierSeq.reset(static_cast<otava::ast::Node*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::ConversionDeclarator(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        declarator.reset(static_cast<otava::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConversionTypeId");
                #endif
                return soul::parser::Match(true, new otava::ast::ConversionTypeIdNode(sourcePos, typeSpecifierSeq.release(), declarator.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConversionTypeId");
        else soul::lexer::WriteFailureToLog(lexer, "ConversionTypeId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::ConversionDeclarator(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConversionDeclarator");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041805);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> op;
    std::unique_ptr<otava::ast::Node> declarator;
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
                    std::expected<soul::parser::Match, int> m = otava::parser::declaration::DeclarationParser<LexerT>::PtrOperator(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul::parser::Match match = *m;
                    op.reset(static_cast<otava::ast::Node*>(match.value));
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        std::expected<soul::parser::Match, int> m = otava::parser::function::FunctionParser<LexerT>::ConversionDeclarator(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul::parser::Match match = *m;
                        declarator.reset(static_cast<otava::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConversionDeclarator");
                #endif
                return soul::parser::Match(true, new otava::ast::ConversionDeclaratorNode(sourcePos, op.release(), declarator.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConversionDeclarator");
        else soul::lexer::WriteFailureToLog(lexer, "ConversionDeclarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::OperatorKw(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "OperatorKw");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041806);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == otava::token::OPERATOR)
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OperatorKw");
                #endif
                return soul::parser::Match(true, new otava::ast::OperatorNode(*sp));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OperatorKw");
        else soul::lexer::WriteFailureToLog(lexer, "OperatorKw");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::Operator(LexerT& lexer, otava::symbols::Context* context)
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
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041807);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        switch (*lexer)
        {
            case otava::token::DELETE:
            case otava::token::NEW:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch2 = &match;
                {
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch3 = &match;
                    switch (*lexer)
                    {
                        case otava::token::NEW:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch4 = &match;
                            {
                                std::int64_t save = lexer.GetPos();
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
                                            if (*lexer == otava::token::NEW)
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
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch9 = &match;
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
                                                *parentMatch9 = match;
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
                                    soul::parser::Match* parentMatch10 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch11 = &match;
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
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                    #endif
                                                    return soul::parser::Match(true, new otava::ast::NewArrayOpNode(sourcePos, lbPos, rbPos));
                                                }
                                            }
                                            *parentMatch11 = match;
                                        }
                                        *parentMatch10 = match;
                                    }
                                    *parentMatch5 = match;
                                }
                                *parentMatch4 = match;
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
                                            if (*lexer == otava::token::NEW)
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
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                    #endif
                                                    return soul::parser::Match(true, new otava::ast::NewOpNode(*sp));
                                                }
                                            }
                                            *parentMatch13 = match;
                                        }
                                        *parentMatch12 = match;
                                    }
                                    *parentMatch4 = match;
                                }
                            }
                            if (match.hit)
                            {
                                *parentMatch3 = match;
                            }
                            break;
                        }
                        case otava::token::DELETE:
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
                                        if (*lexer == otava::token::DELETE)
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
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                #endif
                                                return soul::parser::Match(true, new otava::ast::DeleteArrayOpNode(sourcePos, lbPos, rbPos));
                                            }
                                        }
                                        *parentMatch20 = match;
                                    }
                                    *parentMatch19 = match;
                                }
                                *parentMatch14 = match;
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
                        soul::parser::Match* parentMatch21 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch22 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == otava::token::DELETE)
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
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                        #endif
                                        return soul::parser::Match(true, new otava::ast::DeleteOpNode(*sp));
                                    }
                                }
                                *parentMatch22 = match;
                            }
                            *parentMatch21 = match;
                        }
                        *parentMatch2 = match;
                    }
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::CO_AWAIT:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch23 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::CO_AWAIT)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::CoAwaitOpNode(*sp));
                        }
                    }
                    *parentMatch23 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::LPAREN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch24 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch25 = &match;
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
                            sourcePos = *sp;
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
                            if (*lexer == otava::token::RPAREN)
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
                                    return soul::parser::Match(true, new otava::ast::InvokeOpNode(sourcePos));
                                }
                            }
                            *parentMatch27 = match;
                        }
                        *parentMatch26 = match;
                    }
                    *parentMatch24 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::LBRACKET:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch28 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch29 = &match;
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
                            sourcePos = *sp;
                        }
                        *parentMatch29 = match;
                    }
                    *parentMatch28 = match;
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
                            soul::parser::Match match(false);
                            if (*lexer == otava::token::RBRACKET)
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
                                    return soul::parser::Match(true, new otava::ast::SubscriptOpNode(sourcePos));
                                }
                            }
                            *parentMatch31 = match;
                        }
                        *parentMatch30 = match;
                    }
                    *parentMatch28 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::ARROW:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch32 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::ARROW)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ArrowNode(*sp));
                        }
                    }
                    *parentMatch32 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::ARROW_STAR:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch33 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::ARROW_STAR)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ArrowStarNode(*sp));
                        }
                    }
                    *parentMatch33 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::TILDE:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch34 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::TILDE)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ComplementNode(*sp));
                        }
                    }
                    *parentMatch34 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::EXCLAMATION:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch35 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::EXCLAMATION)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::NotNode(*sp));
                        }
                    }
                    *parentMatch35 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::PLUS:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch36 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::PLUS)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::PlusNode(*sp));
                        }
                    }
                    *parentMatch36 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::MINUS:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch37 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::MINUS)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::MinusNode(*sp));
                        }
                    }
                    *parentMatch37 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::STAR:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch38 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::STAR)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::MulNode(*sp));
                        }
                    }
                    *parentMatch38 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::DIV:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch39 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::DIV)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::DivNode(*sp));
                        }
                    }
                    *parentMatch39 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::MOD:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch40 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::MOD)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ModNode(*sp));
                        }
                    }
                    *parentMatch40 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::XOR:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch41 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::XOR)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ExclusiveOrNode(*sp));
                        }
                    }
                    *parentMatch41 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::AMP:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch42 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::AMP)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::AndNode(*sp));
                        }
                    }
                    *parentMatch42 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::OR:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch43 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::OR)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::InclusiveOrNode(*sp));
                        }
                    }
                    *parentMatch43 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch44 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::AssignNode(*sp));
                        }
                    }
                    *parentMatch44 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::ADD_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch45 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::ADD_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::PlusAssignNode(*sp));
                        }
                    }
                    *parentMatch45 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::SUB_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch46 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::SUB_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::MinusAssignNode(*sp));
                        }
                    }
                    *parentMatch46 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::MUL_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch47 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::MUL_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::MulAssignNode(*sp));
                        }
                    }
                    *parentMatch47 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::DIV_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch48 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::DIV_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::DivAssignNode(*sp));
                        }
                    }
                    *parentMatch48 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::REM_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch49 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::REM_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ModAssignNode(*sp));
                        }
                    }
                    *parentMatch49 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::XOR_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch50 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::XOR_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::XorAssignNode(*sp));
                        }
                    }
                    *parentMatch50 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::AND_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch51 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::AND_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::AndAssignNode(*sp));
                        }
                    }
                    *parentMatch51 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::OR_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch52 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::OR_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::OrAssignNode(*sp));
                        }
                    }
                    *parentMatch52 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::SHIFT_LEFT_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch53 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::SHIFT_LEFT_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ShiftLeftAssignNode(*sp));
                        }
                    }
                    *parentMatch53 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::SHIFT_RIGHT_ASSIGN:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch54 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::SHIFT_RIGHT_ASSIGN)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ShiftRightAssignNode(*sp));
                        }
                    }
                    *parentMatch54 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::EQ:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch55 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::EQ)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::EqualNode(*sp));
                        }
                    }
                    *parentMatch55 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::NEQ:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch56 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::NEQ)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::NotEqualNode(*sp));
                        }
                    }
                    *parentMatch56 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::LEQ:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch57 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::LEQ)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::LessOrEqualNode(*sp));
                        }
                    }
                    *parentMatch57 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::GEQ:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch58 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::GEQ)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::GreaterOrEqualNode(*sp));
                        }
                    }
                    *parentMatch58 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::SPACE_SHIP:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch59 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::SPACE_SHIP)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::CompareNode(*sp));
                        }
                    }
                    *parentMatch59 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::LANGLE:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch60 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::LANGLE)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::LessNode(*sp));
                        }
                    }
                    *parentMatch60 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::RANGLE:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch61 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::RANGLE)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::GreaterNode(*sp));
                        }
                    }
                    *parentMatch61 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::AMP_AMP:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch62 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::AMP_AMP)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ConjunctionNode(*sp));
                        }
                    }
                    *parentMatch62 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::OR_OR:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch63 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::OR_OR)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::DisjunctionNode(*sp));
                        }
                    }
                    *parentMatch63 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::SHIFT_LEFT:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch64 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::SHIFT_LEFT)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ShiftLeftNode(*sp));
                        }
                    }
                    *parentMatch64 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::SHIFT_RIGHT:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch65 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::SHIFT_RIGHT)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::ShiftRightNode(*sp));
                        }
                    }
                    *parentMatch65 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::PLUS_PLUS:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch66 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::PLUS_PLUS)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::PrefixIncNode(*sp));
                        }
                    }
                    *parentMatch66 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::MINUS_MINUS:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch67 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::MINUS_MINUS)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::PrefixDecNode(*sp));
                        }
                    }
                    *parentMatch67 = match;
                }
                if (match.hit)
                {
                    *parentMatch1 = match;
                }
                break;
            }
            case otava::token::COMMA:
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch68 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == otava::token::COMMA)
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
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                            #endif
                            return soul::parser::Match(true, new otava::ast::CommaNode(*sp));
                        }
                    }
                    *parentMatch68 = match;
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

template<typename LexerT>
std::expected<soul::parser::Match, int> FunctionParser<LexerT>::Noexcept(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Noexcept");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 3334239814043041808);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == otava::token::NOEXCEPT)
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Noexcept");
                #endif
                return soul::parser::Match(true, new otava::ast::NoexceptNode(*sp));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Noexcept");
        else soul::lexer::WriteFailureToLog(lexer, "Noexcept");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct FunctionParser<soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>>;

} // namespace otava::parser::function
