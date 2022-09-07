
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/function.parser' using soul parser generator spg version 4.1.0

module soul.cpp20.parser.function;

import util;
import soul.ast.spg;
import soul.cpp20.token;
import soul.cpp20.lexer;
import soul.cpp20.parser.attribute;
import soul.cpp20.parser.classes;
import soul.cpp20.parser.concepts;
import soul.cpp20.parser.declaration;
import soul.cpp20.parser.initialization;
import soul.cpp20.parser.punctuation;
import soul.cpp20.parser.statement;
import soul.cpp20.parser.type;
import soul.cpp20.symbols;

using namespace soul::cpp20::token;
using namespace soul::cpp20::lexer;
using namespace soul::cpp20::parser::attribute;
using namespace soul::cpp20::parser::classes;
using namespace soul::cpp20::parser::concepts;
using namespace soul::cpp20::parser::declaration;
using namespace soul::cpp20::parser::initialization;
using namespace soul::cpp20::parser::punctuation;
using namespace soul::cpp20::parser::statement;
using namespace soul::cpp20::parser::type;
using namespace soul::cpp20::symbols;

namespace soul::cpp20::parser::function {

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::FunctionDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionDefinition");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018497);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> declSpecifierSeqNode = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> declaratorNode = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> specifierNode = std::unique_ptr<soul::cpp20::ast::Node>();
    int scopes = int();
    std::unique_ptr<soul::cpp20::ast::Node> attributes;
    std::unique_ptr<soul::cpp20::ast::Node> declSpecifiers;
    std::unique_ptr<soul::cpp20::ast::Node> declarator;
    std::unique_ptr<soul::cpp20::ast::Node> virtSpecifiers;
    std::unique_ptr<soul::cpp20::ast::Node> requiresClause;
    std::unique_ptr<soul::cpp20::ast::Node> functionBody;
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
                    int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = AttributeParser<Lexer>::AttributeSpecifierSeq(lexer, context);
                                attributes.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    lexer.GetSourcePos(pos);
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = DeclarationParser<Lexer>::DeclSpecifierSeq(lexer, context);
                            declSpecifiers.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                declSpecifierSeqNode.reset(declSpecifiers.release());
                                if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = DeclarationParser<Lexer>::Declarator(lexer, context);
                        declarator.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                            declaratorNode.reset(declarator.release());
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch13 = &match;
                    {
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ClassParser<Lexer>::VirtSpecifierSeq(lexer, context);
                                    virtSpecifiers.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        specifierNode.reset(virtSpecifiers.release());
                                    }
                                    *parentMatch16 = match;
                                }
                                *parentMatch15 = match;
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
                                            soul::parser::Match match = ConceptParser<Lexer>::RequiresClause(lexer, context);
                                            requiresClause.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                specifierNode.reset(requiresClause.release());
                                            }
                                            *parentMatch18 = match;
                                        }
                                        *parentMatch17 = match;
                                    }
                                    *parentMatch15 = match;
                                }
                            }
                            *parentMatch14 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch19 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(true);
                                    *parentMatch19 = match;
                                }
                                *parentMatch14 = match;
                            }
                        }
                        *parentMatch13 = match;
                    }
                    if (match.hit)
                    {
                        scopes = soul::cpp20::symbols::BeginFunctionDefinition(declSpecifierSeqNode.get(), declaratorNode.get(), context);
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
        soul::parser::Match* parentMatch20 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch21 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = FunctionParser<Lexer>::FunctionBody(lexer, context);
                functionBody.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    soul::cpp20::ast::Node *node = new soul::cpp20::ast::FunctionDefinitionNode(sourcePos, attributes.release(), declSpecifierSeqNode.release(), declaratorNode.release(), specifierNode.release(), functionBody.release());
                    soul::cpp20::symbols::EndFunctionDefinition(node, scopes, context);
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionDefinition");
                        #endif SOUL_PARSER_DEBUG_SUPPORT
                        return soul::parser::Match(true, node);
                    }
                }
                *parentMatch21 = match;
            }
            *parentMatch20 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionDefinition");
        else soul::lexer::WriteFailureToLog(lexer, "FunctionDefinition");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::NoDeclSpecFunctionDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NoDeclSpecFunctionDefinition");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018498);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> declSpecifierSeqNode = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> declaratorNode = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> specifierNode = std::unique_ptr<soul::cpp20::ast::Node>();
    int scopes = int();
    std::unique_ptr<soul::cpp20::ast::Node> attributes;
    std::unique_ptr<soul::cpp20::ast::Node> declarator;
    std::unique_ptr<soul::cpp20::ast::Node> virtSpecifiers;
    std::unique_ptr<soul::cpp20::ast::Node> requiresClause;
    std::unique_ptr<soul::cpp20::ast::Node> functionBody;
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
                int64_t save = lexer.GetPos();
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = AttributeParser<Lexer>::AttributeSpecifierSeq(lexer, context);
                            attributes.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                lexer.GetSourcePos(pos);
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = DeclarationParser<Lexer>::Declarator(lexer, context);
                        declarator.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                            declaratorNode.reset(declarator.release());
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch10 = &match;
                    {
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ClassParser<Lexer>::VirtSpecifierSeq(lexer, context);
                                    virtSpecifiers.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        specifierNode.reset(virtSpecifiers.release());
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
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch15 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = ConceptParser<Lexer>::RequiresClause(lexer, context);
                                            requiresClause.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                specifierNode.reset(requiresClause.release());
                                            }
                                            *parentMatch15 = match;
                                        }
                                        *parentMatch14 = match;
                                    }
                                    *parentMatch12 = match;
                                }
                            }
                            *parentMatch11 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch16 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(true);
                                    *parentMatch16 = match;
                                }
                                *parentMatch11 = match;
                            }
                        }
                        *parentMatch10 = match;
                    }
                    if (match.hit)
                    {
                        scopes = soul::cpp20::symbols::BeginFunctionDefinition(declSpecifierSeqNode.get(), declaratorNode.get(), context);
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
        soul::parser::Match* parentMatch17 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch18 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = FunctionParser<Lexer>::FunctionBody(lexer, context);
                functionBody.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    soul::cpp20::ast::Node *node = new soul::cpp20::ast::FunctionDefinitionNode(sourcePos, attributes.release(), declSpecifierSeqNode.release(), declaratorNode.release(), specifierNode.release(), functionBody.release());
                    soul::cpp20::symbols::EndFunctionDefinition(node, scopes, context);
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoDeclSpecFunctionDefinition");
                        #endif SOUL_PARSER_DEBUG_SUPPORT
                        return soul::parser::Match(true, node);
                    }
                }
                *parentMatch18 = match;
            }
            *parentMatch17 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoDeclSpecFunctionDefinition");
        else soul::lexer::WriteFailureToLog(lexer, "NoDeclSpecFunctionDefinition");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::FunctionBody(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionBody");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018499);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> assign;
    std::unique_ptr<soul::cpp20::ast::Node> def;
    std::unique_ptr<soul::cpp20::ast::Node> semicolon;
    std::unique_ptr<soul::cpp20::ast::Node> del;
    std::unique_ptr<soul::cpp20::ast::Node> semicolon2;
    std::unique_ptr<soul::cpp20::ast::Node> ctorInitializer;
    std::unique_ptr<soul::cpp20::ast::Node> compoundStatement;
    std::unique_ptr<soul::cpp20::ast::Node> compoundStatement2;
    std::unique_ptr<soul::cpp20::ast::Node> functionTryBlock;
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = PunctuationParser<Lexer>::Assign(lexer);
                        assign.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                    soul::parser::Match match = FunctionParser<Lexer>::Default(lexer);
                                    def.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    *parentMatch8 = match;
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
                                            soul::parser::Match match = PunctuationParser<Lexer>::Semicolon(lexer);
                                            semicolon.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                                    return soul::parser::Match(true, new soul::cpp20::ast::DefaultedOrDeletedFunctionNode(sourcePos, assign.release(), def.release(), semicolon.release()));
                                                }
                                            }
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch12 = &match;
                                        {
                                            soul::parser::Match match = FunctionParser<Lexer>::Delete(lexer);
                                            del.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                                    soul::parser::Match match = PunctuationParser<Lexer>::Semicolon(lexer);
                                                    semicolon2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        {
                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
                                                            return soul::parser::Match(true, new soul::cpp20::ast::DefaultedOrDeletedFunctionNode(sourcePos, assign.release(), del.release(), semicolon2.release()));
                                                        }
                                                    }
                                                    *parentMatch14 = match;
                                                }
                                                *parentMatch13 = match;
                                            }
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch11 = match;
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
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch15 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch16 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch17 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ClassParser<Lexer>::CtorInitializer(lexer, context);
                                ctorInitializer.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                    soul::parser::Match match = StatementParser<Lexer>::CompoundStatement(lexer, context);
                                    compoundStatement.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
                                            #endif SOUL_PARSER_DEBUG_SUPPORT
                                            return soul::parser::Match(true, new soul::cpp20::ast::ConstructorNode(sourcePos, ctorInitializer.release(), compoundStatement.release()));
                                        }
                                    }
                                    *parentMatch19 = match;
                                }
                                *parentMatch18 = match;
                            }
                            *parentMatch16 = match;
                        }
                        *parentMatch15 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch20 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch21 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = StatementParser<Lexer>::CompoundStatement(lexer, context);
                        compoundStatement2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
                                #endif SOUL_PARSER_DEBUG_SUPPORT
                                return soul::parser::Match(true, new soul::cpp20::ast::FunctionBodyNode(lexer.GetSourcePos(pos), compoundStatement2.release()));
                            }
                        }
                        *parentMatch21 = match;
                    }
                    *parentMatch20 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch22 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch23 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = FunctionParser<Lexer>::FunctionTryBlock(lexer, context);
                    functionTryBlock.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionBody");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
                            return soul::parser::Match(true, functionTryBlock.release());
                        }
                    }
                    *parentMatch23 = match;
                }
                *parentMatch22 = match;
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::Default(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Default");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018500);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == DEFAULT)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Default");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::DefaultNode(lexer.GetSourcePos(pos)));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::Delete(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Delete");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018501);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Delete");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::DeleteNode(lexer.GetSourcePos(pos)));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::ParameterDeclarationClause(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParameterDeclarationClause");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018502);
    std::unique_ptr<soul::cpp20::ast::Node> comma;
    std::unique_ptr<soul::cpp20::ast::Node> ellipsis;
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
                context->PushSetFlag(soul::cpp20::symbols::ContextFlags::parsingParameters);
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
                        int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                soul::parser::Match match = FunctionParser<Lexer>::ParameterDeclarationList(lexer, context, container);
                                *parentMatch7 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    soul::parser::Match match = PunctuationParser<Lexer>::Comma(lexer);
                                    comma.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = PunctuationParser<Lexer>::Ellipsis(lexer);
                                    ellipsis.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        container->AddNode(comma.release());
                                        container->AddNode(ellipsis.release());
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                if (match.hit)
                                                {
                                                    container->Clear();
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
                                                int64_t save = lexer.GetPos();
                                                soul::parser::Match* parentMatch17 = &match;
                                                {
                                                    soul::parser::Match match = FunctionParser<Lexer>::ParameterDeclarationList(lexer, context, container);
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
                                            int64_t save = lexer.GetPos();
                                            soul::parser::Match* parentMatch19 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch20 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch21 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = PunctuationParser<Lexer>::Ellipsis(lexer);
                                                        ellipsis.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            container->AddNode(ellipsis.release());
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
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match* parentMatch23 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch24 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch25 = &match;
                                                {
                                                    soul::parser::Match match = PunctuationParser<Lexer>::Comma(lexer);
                                                    comma.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = PunctuationParser<Lexer>::Ellipsis(lexer);
                                                            ellipsis.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                container->AddNode(comma.release());
                                                                container->AddNode(ellipsis.release());
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::ParameterDeclarationList(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParameterDeclarationList");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018503);
    std::unique_ptr<soul::cpp20::ast::Node> first;
    std::unique_ptr<soul::cpp20::ast::Node> comma;
    std::unique_ptr<soul::cpp20::ast::Node> next;
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
                soul::parser::Match match = FunctionParser<Lexer>::ParameterDeclaration(lexer, context);
                first.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    container->AddNode(first.release());
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
                        int64_t save = lexer.GetPos();
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch5 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match = PunctuationParser<Lexer>::Comma(lexer);
                                    comma.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = FunctionParser<Lexer>::ParameterDeclaration(lexer, context);
                                            next.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                container->AddNode(comma.release());
                                                container->AddNode(next.release());
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::ParameterDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParameterDeclaration");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018504);
    std::unique_ptr<soul::cpp20::ast::ParameterNode> parameterNode = std::unique_ptr<soul::cpp20::ast::ParameterNode>();
    std::unique_ptr<soul::cpp20::ast::Node> attributes;
    std::unique_ptr<soul::cpp20::ast::Node> declSpecifierSeq;
    std::unique_ptr<soul::cpp20::ast::Node> declarator;
    std::unique_ptr<soul::cpp20::ast::Node> abstractDeclarator;
    std::unique_ptr<soul::cpp20::ast::Node> assign;
    std::unique_ptr<soul::cpp20::ast::Node> initializer;
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
                parameterNode.reset(new soul::cpp20::ast::ParameterNode(lexer.GetSourcePos(pos)));
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
                                soul::parser::Match match(true);
                                int64_t save = lexer.GetPos();
                                soul::parser::Match* parentMatch8 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = AttributeParser<Lexer>::AttributeSpecifierSeq(lexer, context);
                                            attributes.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = DeclarationParser<Lexer>::DeclSpecifierSeq(lexer, context);
                                        declSpecifierSeq.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                int64_t save = lexer.GetPos();
                                soul::parser::Match* parentMatch14 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch15 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch16 = &match;
                                        {
                                            int64_t save = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch17 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = DeclarationParser<Lexer>::Declarator(lexer, context);
                                                declarator.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = DeclarationParser<Lexer>::AbstractDeclarator(lexer, context);
                                                        abstractDeclarator.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                            int64_t save = lexer.GetPos();
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = PunctuationParser<Lexer>::Assign(lexer);
                                            assign.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = InitializationParser<Lexer>::InitializerClause(lexer, context);
                                                initializer.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                        #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::OperatorFunctionId(Lexer& lexer, soul::cpp20::symbols::Context* context)
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
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018505);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> operatorKw;
    std::unique_ptr<soul::cpp20::ast::Node> op;
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
                    soul::parser::Match match = FunctionParser<Lexer>::OperatorKw(lexer);
                    operatorKw.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                    soul::parser::Match match = FunctionParser<Lexer>::Operator(lexer, context);
                    op.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                return soul::parser::Match(true, new soul::cpp20::ast::OperatorFunctionIdNode(sourcePos, operatorKw.release(), op.release()));
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
soul::parser::Match FunctionParser<Lexer>::ConversionFunctionId(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConversionFunctionId");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018506);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> operatorKw;
    std::unique_ptr<soul::cpp20::ast::Node> conversionTypeId;
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
                    soul::parser::Match match = FunctionParser<Lexer>::OperatorKw(lexer);
                    operatorKw.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                    soul::parser::Match match = FunctionParser<Lexer>::ConversionTypeId(lexer, context);
                    conversionTypeId.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::ConversionFunctionIdNode(sourcePos, operatorKw.release(), conversionTypeId.release()));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::DestructorId(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DestructorId");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018507);
    std::unique_ptr<soul::cpp20::ast::Node> node = std::unique_ptr<soul::cpp20::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> typeName;
    std::unique_ptr<soul::cpp20::ast::Node> declTypeSpecifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch4 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = TypeParser<Lexer>::TypeName(lexer, context);
                            typeName.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = TypeParser<Lexer>::DeclTypeSpecifier(lexer, context);
                                    declTypeSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                        #endif SOUL_PARSER_DEBUG_SUPPORT
                        return soul::parser::Match(true, new soul::cpp20::ast::DestructorIdNode(sourcePos, node.release()));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::ConversionTypeId(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConversionTypeId");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018508);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> typeSpecifierSeq;
    std::unique_ptr<soul::cpp20::ast::Node> declarator;
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
                    soul::parser::Match match = TypeParser<Lexer>::TypeSpecifierSeq(lexer, context);
                    typeSpecifierSeq.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                        soul::parser::Match match = FunctionParser<Lexer>::ConversionDeclarator(lexer, context);
                        declarator.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::ConversionTypeIdNode(sourcePos, typeSpecifierSeq.release(), declarator.release()));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::ConversionDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConversionDeclarator");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018509);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> op;
    std::unique_ptr<soul::cpp20::ast::Node> declarator;
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
                    soul::parser::Match match = DeclarationParser<Lexer>::PtrOperator(lexer, context);
                    op.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                        soul::parser::Match match = FunctionParser<Lexer>::ConversionDeclarator(lexer, context);
                        declarator.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::ConversionDeclaratorNode(sourcePos, op.release(), declarator.release()));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::OperatorKw(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "OperatorKw");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018510);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
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
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OperatorKw");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::OperatorNode(lexer.GetSourcePos(pos)));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::Operator(Lexer& lexer, soul::cpp20::symbols::Context* context)
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
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018511);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
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
                                                                                                                                                                                int64_t save = lexer.GetPos();
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                soul::parser::Match* parentMatch43 = &match;
                                                                                                                                                                                {
                                                                                                                                                                                    int64_t save = lexer.GetPos();
                                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                                    soul::parser::Match* parentMatch44 = &match;
                                                                                                                                                                                    {
                                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                                        soul::parser::Match* parentMatch45 = &match;
                                                                                                                                                                                        {
                                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                                            soul::parser::Match* parentMatch46 = &match;
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
                                                                                                                                                                                                }
                                                                                                                                                                                                *parentMatch46 = match;
                                                                                                                                                                                            }
                                                                                                                                                                                            *parentMatch45 = match;
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
                                                                                                                                                                                                    if (*lexer == LBRACKET)
                                                                                                                                                                                                    {
                                                                                                                                                                                                        ++lexer;
                                                                                                                                                                                                        match.hit = true;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    if (match.hit)
                                                                                                                                                                                                    {
                                                                                                                                                                                                        lbPos = lexer.GetSourcePos(pos);
                                                                                                                                                                                                    }
                                                                                                                                                                                                    *parentMatch48 = match;
                                                                                                                                                                                                }
                                                                                                                                                                                                *parentMatch47 = match;
                                                                                                                                                                                            }
                                                                                                                                                                                            *parentMatch45 = match;
                                                                                                                                                                                        }
                                                                                                                                                                                        *parentMatch44 = match;
                                                                                                                                                                                    }
                                                                                                                                                                                    if (match.hit)
                                                                                                                                                                                    {
                                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                                        soul::parser::Match* parentMatch49 = &match;
                                                                                                                                                                                        {
                                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                                            soul::parser::Match* parentMatch50 = &match;
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
                                                                                                                                                                                                    {
                                                                                                                                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                                        return soul::parser::Match(true, new soul::cpp20::ast::NewArrayOpNode(sourcePos, lbPos, rbPos));
                                                                                                                                                                                                    }
                                                                                                                                                                                                }
                                                                                                                                                                                                *parentMatch50 = match;
                                                                                                                                                                                            }
                                                                                                                                                                                            *parentMatch49 = match;
                                                                                                                                                                                        }
                                                                                                                                                                                        *parentMatch44 = match;
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch43 = match;
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
                                                                                                                                                                                                        return soul::parser::Match(true, new soul::cpp20::ast::NewOpNode(lexer.GetSourcePos(pos)));
                                                                                                                                                                                                    }
                                                                                                                                                                                                }
                                                                                                                                                                                                *parentMatch52 = match;
                                                                                                                                                                                            }
                                                                                                                                                                                            *parentMatch51 = match;
                                                                                                                                                                                        }
                                                                                                                                                                                        *parentMatch43 = match;
                                                                                                                                                                                    }
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch42 = match;
                                                                                                                                                                                if (!match.hit)
                                                                                                                                                                                {
                                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                                    soul::parser::Match* parentMatch53 = &match;
                                                                                                                                                                                    lexer.SetPos(save);
                                                                                                                                                                                    {
                                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                                        soul::parser::Match* parentMatch54 = &match;
                                                                                                                                                                                        {
                                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                                            soul::parser::Match* parentMatch55 = &match;
                                                                                                                                                                                            {
                                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                                soul::parser::Match* parentMatch56 = &match;
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
                                                                                                                                                                                                    }
                                                                                                                                                                                                    *parentMatch56 = match;
                                                                                                                                                                                                }
                                                                                                                                                                                                *parentMatch55 = match;
                                                                                                                                                                                            }
                                                                                                                                                                                            if (match.hit)
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
                                                                                                                                                                                                            lbPos = sourcePos;
                                                                                                                                                                                                        }
                                                                                                                                                                                                        *parentMatch58 = match;
                                                                                                                                                                                                    }
                                                                                                                                                                                                    *parentMatch57 = match;
                                                                                                                                                                                                }
                                                                                                                                                                                                *parentMatch55 = match;
                                                                                                                                                                                            }
                                                                                                                                                                                            *parentMatch54 = match;
                                                                                                                                                                                        }
                                                                                                                                                                                        if (match.hit)
                                                                                                                                                                                        {
                                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                                            soul::parser::Match* parentMatch59 = &match;
                                                                                                                                                                                            {
                                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                                soul::parser::Match* parentMatch60 = &match;
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
                                                                                                                                                                                                        rbPos = sourcePos;
                                                                                                                                                                                                        {
                                                                                                                                                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                                                                                                                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
                                                                                                                                                                                                            return soul::parser::Match(true, new soul::cpp20::ast::DeleteArrayOpNode(sourcePos, lbPos, rbPos));
                                                                                                                                                                                                        }
                                                                                                                                                                                                    }
                                                                                                                                                                                                    *parentMatch60 = match;
                                                                                                                                                                                                }
                                                                                                                                                                                                *parentMatch59 = match;
                                                                                                                                                                                            }
                                                                                                                                                                                            *parentMatch54 = match;
                                                                                                                                                                                        }
                                                                                                                                                                                        *parentMatch53 = match;
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch42 = match;
                                                                                                                                                                                }
                                                                                                                                                                            }
                                                                                                                                                                            *parentMatch41 = match;
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
                                                                                                                                                                                                return soul::parser::Match(true, new soul::cpp20::ast::DeleteOpNode(lexer.GetSourcePos(pos)));
                                                                                                                                                                                            }
                                                                                                                                                                                        }
                                                                                                                                                                                        *parentMatch62 = match;
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch61 = match;
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch41 = match;
                                                                                                                                                                            }
                                                                                                                                                                        }
                                                                                                                                                                        *parentMatch40 = match;
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
                                                                                                                                                                                    if (*lexer == CO_AWAIT)
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
                                                                                                                                                                                            return soul::parser::Match(true, new soul::cpp20::ast::CoAwaitOpNode(lexer.GetSourcePos(pos)));
                                                                                                                                                                                        }
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch64 = match;
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch63 = match;
                                                                                                                                                                            }
                                                                                                                                                                            *parentMatch40 = match;
                                                                                                                                                                        }
                                                                                                                                                                    }
                                                                                                                                                                    *parentMatch39 = match;
                                                                                                                                                                    if (!match.hit)
                                                                                                                                                                    {
                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                        soul::parser::Match* parentMatch65 = &match;
                                                                                                                                                                        lexer.SetPos(save);
                                                                                                                                                                        {
                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                            soul::parser::Match* parentMatch66 = &match;
                                                                                                                                                                            {
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                soul::parser::Match* parentMatch67 = &match;
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
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch67 = match;
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch66 = match;
                                                                                                                                                                            }
                                                                                                                                                                            if (match.hit)
                                                                                                                                                                            {
                                                                                                                                                                                soul::parser::Match match(false);
                                                                                                                                                                                soul::parser::Match* parentMatch68 = &match;
                                                                                                                                                                                {
                                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                                    soul::parser::Match* parentMatch69 = &match;
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
                                                                                                                                                                                                return soul::parser::Match(true, new soul::cpp20::ast::InvokeOpNode(sourcePos));
                                                                                                                                                                                            }
                                                                                                                                                                                        }
                                                                                                                                                                                        *parentMatch69 = match;
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch68 = match;
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch66 = match;
                                                                                                                                                                            }
                                                                                                                                                                            *parentMatch65 = match;
                                                                                                                                                                        }
                                                                                                                                                                        *parentMatch39 = match;
                                                                                                                                                                    }
                                                                                                                                                                }
                                                                                                                                                                *parentMatch38 = match;
                                                                                                                                                                if (!match.hit)
                                                                                                                                                                {
                                                                                                                                                                    soul::parser::Match match(false);
                                                                                                                                                                    soul::parser::Match* parentMatch70 = &match;
                                                                                                                                                                    lexer.SetPos(save);
                                                                                                                                                                    {
                                                                                                                                                                        soul::parser::Match match(false);
                                                                                                                                                                        soul::parser::Match* parentMatch71 = &match;
                                                                                                                                                                        {
                                                                                                                                                                            soul::parser::Match match(false);
                                                                                                                                                                            soul::parser::Match* parentMatch72 = &match;
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
                                                                                                                                                                                    sourcePos = lexer.GetSourcePos(pos);
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch72 = match;
                                                                                                                                                                            }
                                                                                                                                                                            *parentMatch71 = match;
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
                                                                                                                                                                                            return soul::parser::Match(true, new soul::cpp20::ast::SubscriptOpNode(sourcePos));
                                                                                                                                                                                        }
                                                                                                                                                                                    }
                                                                                                                                                                                    *parentMatch74 = match;
                                                                                                                                                                                }
                                                                                                                                                                                *parentMatch73 = match;
                                                                                                                                                                            }
                                                                                                                                                                            *parentMatch71 = match;
                                                                                                                                                                        }
                                                                                                                                                                        *parentMatch70 = match;
                                                                                                                                                                    }
                                                                                                                                                                    *parentMatch38 = match;
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                            *parentMatch37 = match;
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
                                                                                                                                                                                return soul::parser::Match(true, new soul::cpp20::ast::ArrowNode(lexer.GetSourcePos(pos)));
                                                                                                                                                                            }
                                                                                                                                                                        }
                                                                                                                                                                        *parentMatch76 = match;
                                                                                                                                                                    }
                                                                                                                                                                    *parentMatch75 = match;
                                                                                                                                                                }
                                                                                                                                                                *parentMatch37 = match;
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                        *parentMatch36 = match;
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
                                                                                                                                                                            return soul::parser::Match(true, new soul::cpp20::ast::ArrowStarNode(lexer.GetSourcePos(pos)));
                                                                                                                                                                        }
                                                                                                                                                                    }
                                                                                                                                                                    *parentMatch78 = match;
                                                                                                                                                                }
                                                                                                                                                                *parentMatch77 = match;
                                                                                                                                                            }
                                                                                                                                                            *parentMatch36 = match;
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                    *parentMatch35 = match;
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
                                                                                                                                                                        return soul::parser::Match(true, new soul::cpp20::ast::ComplementNode(lexer.GetSourcePos(pos)));
                                                                                                                                                                    }
                                                                                                                                                                }
                                                                                                                                                                *parentMatch80 = match;
                                                                                                                                                            }
                                                                                                                                                            *parentMatch79 = match;
                                                                                                                                                        }
                                                                                                                                                        *parentMatch35 = match;
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                *parentMatch34 = match;
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
                                                                                                                                                                    return soul::parser::Match(true, new soul::cpp20::ast::NotNode(lexer.GetSourcePos(pos)));
                                                                                                                                                                }
                                                                                                                                                            }
                                                                                                                                                            *parentMatch82 = match;
                                                                                                                                                        }
                                                                                                                                                        *parentMatch81 = match;
                                                                                                                                                    }
                                                                                                                                                    *parentMatch34 = match;
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                            *parentMatch33 = match;
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
                                                                                                                                                                return soul::parser::Match(true, new soul::cpp20::ast::PlusNode(lexer.GetSourcePos(pos)));
                                                                                                                                                            }
                                                                                                                                                        }
                                                                                                                                                        *parentMatch84 = match;
                                                                                                                                                    }
                                                                                                                                                    *parentMatch83 = match;
                                                                                                                                                }
                                                                                                                                                *parentMatch33 = match;
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                        *parentMatch32 = match;
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
                                                                                                                                                            return soul::parser::Match(true, new soul::cpp20::ast::MinusNode(lexer.GetSourcePos(pos)));
                                                                                                                                                        }
                                                                                                                                                    }
                                                                                                                                                    *parentMatch86 = match;
                                                                                                                                                }
                                                                                                                                                *parentMatch85 = match;
                                                                                                                                            }
                                                                                                                                            *parentMatch32 = match;
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                    *parentMatch31 = match;
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
                                                                                                                                                        return soul::parser::Match(true, new soul::cpp20::ast::MulNode(lexer.GetSourcePos(pos)));
                                                                                                                                                    }
                                                                                                                                                }
                                                                                                                                                *parentMatch88 = match;
                                                                                                                                            }
                                                                                                                                            *parentMatch87 = match;
                                                                                                                                        }
                                                                                                                                        *parentMatch31 = match;
                                                                                                                                    }
                                                                                                                                }
                                                                                                                                *parentMatch30 = match;
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
                                                                                                                                                    return soul::parser::Match(true, new soul::cpp20::ast::DivNode(lexer.GetSourcePos(pos)));
                                                                                                                                                }
                                                                                                                                            }
                                                                                                                                            *parentMatch90 = match;
                                                                                                                                        }
                                                                                                                                        *parentMatch89 = match;
                                                                                                                                    }
                                                                                                                                    *parentMatch30 = match;
                                                                                                                                }
                                                                                                                            }
                                                                                                                            *parentMatch29 = match;
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
                                                                                                                                        if (*lexer == MOD)
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
                                                                                                                                                return soul::parser::Match(true, new soul::cpp20::ast::ModNode(lexer.GetSourcePos(pos)));
                                                                                                                                            }
                                                                                                                                        }
                                                                                                                                        *parentMatch92 = match;
                                                                                                                                    }
                                                                                                                                    *parentMatch91 = match;
                                                                                                                                }
                                                                                                                                *parentMatch29 = match;
                                                                                                                            }
                                                                                                                        }
                                                                                                                        *parentMatch28 = match;
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
                                                                                                                                    if (*lexer == XOR)
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
                                                                                                                                            return soul::parser::Match(true, new soul::cpp20::ast::ExclusiveOrNode(lexer.GetSourcePos(pos)));
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                    *parentMatch94 = match;
                                                                                                                                }
                                                                                                                                *parentMatch93 = match;
                                                                                                                            }
                                                                                                                            *parentMatch28 = match;
                                                                                                                        }
                                                                                                                    }
                                                                                                                    *parentMatch27 = match;
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
                                                                                                                                        return soul::parser::Match(true, new soul::cpp20::ast::AndNode(lexer.GetSourcePos(pos)));
                                                                                                                                    }
                                                                                                                                }
                                                                                                                                *parentMatch96 = match;
                                                                                                                            }
                                                                                                                            *parentMatch95 = match;
                                                                                                                        }
                                                                                                                        *parentMatch27 = match;
                                                                                                                    }
                                                                                                                }
                                                                                                                *parentMatch26 = match;
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
                                                                                                                            if (*lexer == OR)
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
                                                                                                                                    return soul::parser::Match(true, new soul::cpp20::ast::InclusiveOrNode(lexer.GetSourcePos(pos)));
                                                                                                                                }
                                                                                                                            }
                                                                                                                            *parentMatch98 = match;
                                                                                                                        }
                                                                                                                        *parentMatch97 = match;
                                                                                                                    }
                                                                                                                    *parentMatch26 = match;
                                                                                                                }
                                                                                                            }
                                                                                                            *parentMatch25 = match;
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
                                                                                                                                return soul::parser::Match(true, new soul::cpp20::ast::AssignNode(lexer.GetSourcePos(pos)));
                                                                                                                            }
                                                                                                                        }
                                                                                                                        *parentMatch100 = match;
                                                                                                                    }
                                                                                                                    *parentMatch99 = match;
                                                                                                                }
                                                                                                                *parentMatch25 = match;
                                                                                                            }
                                                                                                        }
                                                                                                        *parentMatch24 = match;
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
                                                                                                                    if (*lexer == ADD_ASSIGN)
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
                                                                                                                            return soul::parser::Match(true, new soul::cpp20::ast::PlusAssignNode(lexer.GetSourcePos(pos)));
                                                                                                                        }
                                                                                                                    }
                                                                                                                    *parentMatch102 = match;
                                                                                                                }
                                                                                                                *parentMatch101 = match;
                                                                                                            }
                                                                                                            *parentMatch24 = match;
                                                                                                        }
                                                                                                    }
                                                                                                    *parentMatch23 = match;
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
                                                                                                                if (*lexer == SUB_ASSIGN)
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
                                                                                                                        return soul::parser::Match(true, new soul::cpp20::ast::MinusAssignNode(lexer.GetSourcePos(pos)));
                                                                                                                    }
                                                                                                                }
                                                                                                                *parentMatch104 = match;
                                                                                                            }
                                                                                                            *parentMatch103 = match;
                                                                                                        }
                                                                                                        *parentMatch23 = match;
                                                                                                    }
                                                                                                }
                                                                                                *parentMatch22 = match;
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
                                                                                                                    return soul::parser::Match(true, new soul::cpp20::ast::MulAssignNode(lexer.GetSourcePos(pos)));
                                                                                                                }
                                                                                                            }
                                                                                                            *parentMatch106 = match;
                                                                                                        }
                                                                                                        *parentMatch105 = match;
                                                                                                    }
                                                                                                    *parentMatch22 = match;
                                                                                                }
                                                                                            }
                                                                                            *parentMatch21 = match;
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
                                                                                                                return soul::parser::Match(true, new soul::cpp20::ast::DivAssignNode(lexer.GetSourcePos(pos)));
                                                                                                            }
                                                                                                        }
                                                                                                        *parentMatch108 = match;
                                                                                                    }
                                                                                                    *parentMatch107 = match;
                                                                                                }
                                                                                                *parentMatch21 = match;
                                                                                            }
                                                                                        }
                                                                                        *parentMatch20 = match;
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
                                                                                                            return soul::parser::Match(true, new soul::cpp20::ast::ModAssignNode(lexer.GetSourcePos(pos)));
                                                                                                        }
                                                                                                    }
                                                                                                    *parentMatch110 = match;
                                                                                                }
                                                                                                *parentMatch109 = match;
                                                                                            }
                                                                                            *parentMatch20 = match;
                                                                                        }
                                                                                    }
                                                                                    *parentMatch19 = match;
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
                                                                                                        return soul::parser::Match(true, new soul::cpp20::ast::XorAssignNode(lexer.GetSourcePos(pos)));
                                                                                                    }
                                                                                                }
                                                                                                *parentMatch112 = match;
                                                                                            }
                                                                                            *parentMatch111 = match;
                                                                                        }
                                                                                        *parentMatch19 = match;
                                                                                    }
                                                                                }
                                                                                *parentMatch18 = match;
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
                                                                                                    return soul::parser::Match(true, new soul::cpp20::ast::AndAssignNode(lexer.GetSourcePos(pos)));
                                                                                                }
                                                                                            }
                                                                                            *parentMatch114 = match;
                                                                                        }
                                                                                        *parentMatch113 = match;
                                                                                    }
                                                                                    *parentMatch18 = match;
                                                                                }
                                                                            }
                                                                            *parentMatch17 = match;
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
                                                                                                return soul::parser::Match(true, new soul::cpp20::ast::OrAssignNode(lexer.GetSourcePos(pos)));
                                                                                            }
                                                                                        }
                                                                                        *parentMatch116 = match;
                                                                                    }
                                                                                    *parentMatch115 = match;
                                                                                }
                                                                                *parentMatch17 = match;
                                                                            }
                                                                        }
                                                                        *parentMatch16 = match;
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
                                                                                            return soul::parser::Match(true, new soul::cpp20::ast::ShiftLeftAssignNode(lexer.GetSourcePos(pos)));
                                                                                        }
                                                                                    }
                                                                                    *parentMatch118 = match;
                                                                                }
                                                                                *parentMatch117 = match;
                                                                            }
                                                                            *parentMatch16 = match;
                                                                        }
                                                                    }
                                                                    *parentMatch15 = match;
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
                                                                                        return soul::parser::Match(true, new soul::cpp20::ast::ShiftRightAssignNode(lexer.GetSourcePos(pos)));
                                                                                    }
                                                                                }
                                                                                *parentMatch120 = match;
                                                                            }
                                                                            *parentMatch119 = match;
                                                                        }
                                                                        *parentMatch15 = match;
                                                                    }
                                                                }
                                                                *parentMatch14 = match;
                                                                if (!match.hit)
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch121 = &match;
                                                                    lexer.SetPos(save);
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch122 = &match;
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
                                                                                    return soul::parser::Match(true, new soul::cpp20::ast::EqualNode(lexer.GetSourcePos(pos)));
                                                                                }
                                                                            }
                                                                            *parentMatch122 = match;
                                                                        }
                                                                        *parentMatch121 = match;
                                                                    }
                                                                    *parentMatch14 = match;
                                                                }
                                                            }
                                                            *parentMatch13 = match;
                                                            if (!match.hit)
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch123 = &match;
                                                                lexer.SetPos(save);
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch124 = &match;
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
                                                                                return soul::parser::Match(true, new soul::cpp20::ast::NotEqualNode(lexer.GetSourcePos(pos)));
                                                                            }
                                                                        }
                                                                        *parentMatch124 = match;
                                                                    }
                                                                    *parentMatch123 = match;
                                                                }
                                                                *parentMatch13 = match;
                                                            }
                                                        }
                                                        *parentMatch12 = match;
                                                        if (!match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch125 = &match;
                                                            lexer.SetPos(save);
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch126 = &match;
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
                                                                            return soul::parser::Match(true, new soul::cpp20::ast::LessOrEqualNode(lexer.GetSourcePos(pos)));
                                                                        }
                                                                    }
                                                                    *parentMatch126 = match;
                                                                }
                                                                *parentMatch125 = match;
                                                            }
                                                            *parentMatch12 = match;
                                                        }
                                                    }
                                                    *parentMatch11 = match;
                                                    if (!match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch127 = &match;
                                                        lexer.SetPos(save);
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch128 = &match;
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
                                                                        return soul::parser::Match(true, new soul::cpp20::ast::GreaterOrEqualNode(lexer.GetSourcePos(pos)));
                                                                    }
                                                                }
                                                                *parentMatch128 = match;
                                                            }
                                                            *parentMatch127 = match;
                                                        }
                                                        *parentMatch11 = match;
                                                    }
                                                }
                                                *parentMatch10 = match;
                                                if (!match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch129 = &match;
                                                    lexer.SetPos(save);
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch130 = &match;
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
                                                                {
                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                                                    return soul::parser::Match(true, new soul::cpp20::ast::CompareNode(lexer.GetSourcePos(pos)));
                                                                }
                                                            }
                                                            *parentMatch130 = match;
                                                        }
                                                        *parentMatch129 = match;
                                                    }
                                                    *parentMatch10 = match;
                                                }
                                            }
                                            *parentMatch9 = match;
                                            if (!match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch131 = &match;
                                                lexer.SetPos(save);
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch132 = &match;
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
                                                                return soul::parser::Match(true, new soul::cpp20::ast::LessNode(lexer.GetSourcePos(pos)));
                                                            }
                                                        }
                                                        *parentMatch132 = match;
                                                    }
                                                    *parentMatch131 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                        }
                                        *parentMatch8 = match;
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
                                                            return soul::parser::Match(true, new soul::cpp20::ast::GreaterNode(lexer.GetSourcePos(pos)));
                                                        }
                                                    }
                                                    *parentMatch134 = match;
                                                }
                                                *parentMatch133 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                    }
                                    *parentMatch7 = match;
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
                                                        return soul::parser::Match(true, new soul::cpp20::ast::ConjunctionNode(lexer.GetSourcePos(pos)));
                                                    }
                                                }
                                                *parentMatch136 = match;
                                            }
                                            *parentMatch135 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                }
                                *parentMatch6 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch137 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch138 = &match;
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
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operator");
                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                                    return soul::parser::Match(true, new soul::cpp20::ast::DisjunctionNode(lexer.GetSourcePos(pos)));
                                                }
                                            }
                                            *parentMatch138 = match;
                                        }
                                        *parentMatch137 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch139 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch140 = &match;
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
                                                return soul::parser::Match(true, new soul::cpp20::ast::ShiftLeftNode(lexer.GetSourcePos(pos)));
                                            }
                                        }
                                        *parentMatch140 = match;
                                    }
                                    *parentMatch139 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
                        if (!match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch141 = &match;
                            lexer.SetPos(save);
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch142 = &match;
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
                                            return soul::parser::Match(true, new soul::cpp20::ast::ShiftRightNode(lexer.GetSourcePos(pos)));
                                        }
                                    }
                                    *parentMatch142 = match;
                                }
                                *parentMatch141 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch143 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch144 = &match;
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
                                        return soul::parser::Match(true, new soul::cpp20::ast::PrefixIncNode(lexer.GetSourcePos(pos)));
                                    }
                                }
                                *parentMatch144 = match;
                            }
                            *parentMatch143 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch145 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch146 = &match;
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
                                    return soul::parser::Match(true, new soul::cpp20::ast::PrefixDecNode(lexer.GetSourcePos(pos)));
                                }
                            }
                            *parentMatch146 = match;
                        }
                        *parentMatch145 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch147 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch148 = &match;
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
                                return soul::parser::Match(true, new soul::cpp20::ast::CommaNode(lexer.GetSourcePos(pos)));
                            }
                        }
                        *parentMatch148 = match;
                    }
                    *parentMatch147 = match;
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

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::Noexcept(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Noexcept");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018512);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
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
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Noexcept");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::NoexceptNode(lexer.GetSourcePos(pos)));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::FunctionTryBlock(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionTryBlock");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 4456440676007018513);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> ctorInitializer;
    std::unique_ptr<soul::cpp20::ast::Node> tryBlock;
    std::unique_ptr<soul::cpp20::ast::Node> handlers;
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
                            if (*lexer == TRY)
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
                            soul::parser::Match match(true);
                            int64_t save = lexer.GetPos();
                            soul::parser::Match* parentMatch7 = &match;
                            {
                                soul::parser::Match match = ClassParser<Lexer>::CtorInitializer(lexer, context);
                                ctorInitializer.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch8 = &match;
                    {
                        soul::parser::Match match = StatementParser<Lexer>::CompoundStatement(lexer, context);
                        tryBlock.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                    soul::parser::Match match = StatementParser<Lexer>::HandlerSeq(lexer, context);
                    handlers.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionTryBlock");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::FunctionTryBlockNode(sourcePos, ctorInitializer.release(), tryBlock.release(), handlers.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionTryBlock");
        else soul::lexer::WriteFailureToLog(lexer, "FunctionTryBlock");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct FunctionParser<soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>>;

} // namespace soul::cpp20::parser::function
