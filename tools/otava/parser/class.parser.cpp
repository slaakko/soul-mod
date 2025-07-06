
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/parser/class.parser' using soul parser generator spg version 5.0.0

module otava.parser.classes;

import util;
import soul.ast.spg;
import soul.ast.source.pos;
import soul.ast.lexer.pos.pair;
import otava.token;
import otava.lexer;
import otava.symbols;
import otava.parser.attribute;
import otava.parser.concepts;
import otava.parser.declaration;
import otava.parser.enums;
import otava.parser.expression;
import otava.parser.function;
import otava.parser.guard;
import otava.parser.identifier;
import otava.parser.initialization;
import otava.parser.punctuation;
import otava.parser.recorded.parse;
import otava.parser.templates;
import otava.parser.type;

using namespace soul::ast::source::pos;
using namespace soul::ast::lexer::pos::pair;
using namespace otava::token;
using namespace otava::lexer;
using namespace otava::symbols;
using namespace otava::parser::attribute;
using namespace otava::parser::concepts;
using namespace otava::parser::declaration;
using namespace otava::parser::enums;
using namespace otava::parser::expression;
using namespace otava::parser::function;
using namespace otava::parser::guard;
using namespace otava::parser::identifier;
using namespace otava::parser::initialization;
using namespace otava::parser::punctuation;
using namespace otava::parser::recorded::parse;
using namespace otava::parser::templates;
using namespace otava::parser::type;

namespace otava::parser::classes {

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::ClassSpecifier(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ClassSpecifier");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158017);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::ClassSpecifierNode> node = std::unique_ptr<otava::ast::ClassSpecifierNode>();
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> classHead;
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
                            soul::parser::Match match = ClassParser<LexerT>::ClassHead(lexer, context);
                            classHead.reset(static_cast<otava::ast::Node*>(match.value));
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == LBRACE)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    lbPos = lexer.GetSourcePos(pos);
                                    node.reset(new otava::ast::ClassSpecifierNode(sourcePos, classHead.release()));
                                    otava::symbols::BeginClass(node.get(), context);
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
                        soul::parser::Match match(true);
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch9 = &match;
                        {
                            soul::parser::Match match = ClassParser<LexerT>::MemberSpecification(lexer, context, node.get());
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
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                        if (*lexer == RBRACE)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            rbPos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch11 = match;
                    }
                    *parentMatch10 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            node->SetLBracePos(lbPos);
            node->SetRBracePos(rbPos);
            otava::symbols::EndClass(node.get(), context);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassSpecifier");
                #endif
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "ClassSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::ClassHead(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ClassHead");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158018);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> classKey;
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> classHeadName;
    std::unique_ptr<otava::ast::Node> classVirtSpecifier;
    std::unique_ptr<otava::ast::Node> baseClause;
    std::unique_ptr<otava::ast::Node> unnamed;
    std::unique_ptr<otava::ast::Node> baseClause2;
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
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ClassParser<LexerT>::ClassKey(lexer);
                    classKey.reset(static_cast<otava::ast::Node*>(match.value));
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
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        soul::parser::Match match = AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                        attributes.reset(static_cast<otava::ast::Node*>(match.value));
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch7 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch8 = &match;
                    {
                        std::int64_t save = lexer.GetPos();
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
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch12 = &match;
                                    {
                                        soul::parser::Match match = ClassParser<LexerT>::ClassHeadName(lexer, context);
                                        classHeadName.reset(static_cast<otava::ast::Node*>(match.value));
                                        *parentMatch12 = match;
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
                                                soul::parser::Match match = ClassParser<LexerT>::ClassVirtSpecifier(lexer, context);
                                                classVirtSpecifier.reset(static_cast<otava::ast::Node*>(match.value));
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
                                        *parentMatch12 = match;
                                    }
                                    *parentMatch11 = match;
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
                                            soul::parser::Match match = ClassParser<LexerT>::BaseClause(lexer, context);
                                            baseClause.reset(static_cast<otava::ast::Node*>(match.value));
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
                                    *parentMatch11 = match;
                                }
                                *parentMatch10 = match;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassHead");
                                    #endif
                                    return soul::parser::Match(true, new otava::ast::ClassHeadNode(sourcePos, classKey.release(), classHeadName.release(), classVirtSpecifier.release(), baseClause.release(), attributes.release()));
                                }
                            }
                            *parentMatch9 = match;
                        }
                        *parentMatch8 = match;
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
                                    soul::parser::Match* parentMatch19 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch20 = &match;
                                        {
                                            soul::parser::Match match = IdentifierParser<LexerT>::Unnamed(lexer);
                                            unnamed.reset(static_cast<otava::ast::Node*>(match.value));
                                            *parentMatch20 = match;
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
                                                    soul::parser::Match match = ClassParser<LexerT>::BaseClause(lexer, context);
                                                    baseClause2.reset(static_cast<otava::ast::Node*>(match.value));
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
                                            *parentMatch20 = match;
                                        }
                                        *parentMatch19 = match;
                                    }
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassHead");
                                            #endif
                                            return soul::parser::Match(true, new otava::ast::ClassHeadNode(sourcePos, classKey.release(), unnamed.release(), nullptr, baseClause2.release(), attributes.release()));
                                        }
                                    }
                                    *parentMatch18 = match;
                                }
                                *parentMatch17 = match;
                            }
                            *parentMatch8 = match;
                        }
                    }
                    *parentMatch7 = match;
                }
                *parentMatch6 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassHead");
        else soul::lexer::WriteFailureToLog(lexer, "ClassHead");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::ClassKey(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ClassKey");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158019);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case CLASS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == CLASS)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ClassNode(lexer.GetSourcePos(pos)));
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
        case STRUCT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == STRUCT)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
                        #endif
                        return soul::parser::Match(true, new otava::ast::StructNode(lexer.GetSourcePos(pos)));
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
        case UNION:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == UNION)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
                        #endif
                        return soul::parser::Match(true, new otava::ast::UnionNode(lexer.GetSourcePos(pos)));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
        else soul::lexer::WriteFailureToLog(lexer, "ClassKey");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::ClassHeadName(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ClassHeadName");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158020);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> nns;
    std::unique_ptr<otava::ast::Node> className;
    std::unique_ptr<otava::ast::Node> className2;
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
                soul::parser::Match match = IdentifierParser<LexerT>::NestedNameSpecifier(lexer, context);
                nns.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    sourcePos = lexer.GetSourcePos(pos);
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
                    soul::parser::Match match = ClassParser<LexerT>::ClassName(lexer, context);
                    className.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassHeadName");
                            #endif
                            return soul::parser::Match(true, new otava::ast::QualifiedIdNode(sourcePos, nns.release(), className.release()));
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
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ClassParser<LexerT>::ClassName(lexer, context);
                    className2.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassHeadName");
                            #endif
                            return soul::parser::Match(true, className2.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassHeadName");
        else soul::lexer::WriteFailureToLog(lexer, "ClassHeadName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::ClassName(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ClassName");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158021);
    std::unique_ptr<otava::ast::Node> templateId;
    std::unique_ptr<otava::ast::Node> identifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match = TemplateParser<LexerT>::SimpleTemplateId(lexer, context);
            templateId.reset(static_cast<otava::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassName");
                    #endif
                    return soul::parser::Match(true, templateId.release());
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
                    soul::parser::Match match = IdentifierParser<LexerT>::Identifier(lexer, context);
                    identifier.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassName");
                            #endif
                            return soul::parser::Match(true, identifier.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassName");
        else soul::lexer::WriteFailureToLog(lexer, "ClassName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::ClassVirtSpecifier(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ClassVirtSpecifier");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158022);
    std::unique_ptr<otava::ast::Node> finalKw;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match = ClassParser<LexerT>::FinalKeyword(lexer, context);
        finalKw.reset(static_cast<otava::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassVirtSpecifier");
                #endif
                return soul::parser::Match(true, finalKw.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassVirtSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "ClassVirtSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::VirtSpecifierSeq(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "VirtSpecifierSeq");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158023);
    std::unique_ptr<otava::ast::Node> node = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> first;
    std::unique_ptr<otava::ast::Node> next;
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
                    soul::parser::Match match = ClassParser<LexerT>::VirtSpecifier(lexer, context);
                    first.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        node.reset(new otava::ast::VirtSpecifierSequenceNode(lexer.GetSourcePos(pos)));
                        node->AddNode(first.release());
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
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = ClassParser<LexerT>::VirtSpecifier(lexer, context);
                                        next.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            node->AddNode(next.release());
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VirtSpecifierSeq");
                #endif
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VirtSpecifierSeq");
        else soul::lexer::WriteFailureToLog(lexer, "VirtSpecifierSeq");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::VirtSpecifier(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "VirtSpecifier");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158024);
    std::unique_ptr<otava::ast::Node> overrideKw;
    std::unique_ptr<otava::ast::Node> finalKw;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match = ClassParser<LexerT>::OverrideKeyword(lexer, context);
            overrideKw.reset(static_cast<otava::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VirtSpecifier");
                    #endif
                    return soul::parser::Match(true, overrideKw.release());
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
                    soul::parser::Match match = ClassParser<LexerT>::FinalKeyword(lexer, context);
                    finalKw.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VirtSpecifier");
                            #endif
                            return soul::parser::Match(true, finalKw.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VirtSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "VirtSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::OverrideKeyword(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "OverrideKeyword");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158025);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
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
                std::int64_t pos = lexer.GetPos();
                bool pass = true;
                soul::parser::Match match(false);
                if (*lexer == ID)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    sourcePos = lexer.GetSourcePos(pos);
                    std::u32string id = lexer.GetToken(pos).ToString();
                    pass = id == U"override";
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
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OverrideKeyword");
                #endif
                return soul::parser::Match(true, new otava::ast::OverrideNode(sourcePos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "OverrideKeyword");
        else soul::lexer::WriteFailureToLog(lexer, "OverrideKeyword");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::FinalKeyword(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "FinalKeyword");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158026);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
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
                std::int64_t pos = lexer.GetPos();
                bool pass = true;
                soul::parser::Match match(false);
                if (*lexer == ID)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    sourcePos = lexer.GetSourcePos(pos);
                    std::u32string id = lexer.GetToken(pos).ToString();
                    pass = id == U"final";
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
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FinalKeyword");
                #endif
                return soul::parser::Match(true, new otava::ast::FinalNode(sourcePos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FinalKeyword");
        else soul::lexer::WriteFailureToLog(lexer, "FinalKeyword");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::BaseClause(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "BaseClause");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158027);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> baseSpecifierList;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == COLON)
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
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match = ClassParser<LexerT>::BaseSpecifierList(lexer, context);
                baseSpecifierList.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BaseClause");
                        #endif
                        return soul::parser::Match(true, new otava::ast::BaseClauseNode(sourcePos, baseSpecifierList.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BaseClause");
        else soul::lexer::WriteFailureToLog(lexer, "BaseClause");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::BaseSpecifierList(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "BaseSpecifierList");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158028);
    std::unique_ptr<otava::ast::Node> node = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> first;
    std::unique_ptr<otava::ast::Node> comma;
    std::unique_ptr<otava::ast::Node> next;
    std::unique_ptr<otava::ast::Node> ellipsis;
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
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ClassParser<LexerT>::BaseSpecifier(lexer, context);
                        first.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            node.reset(new otava::ast::BaseSpecifierListNode(lexer.GetSourcePos(pos)));
                            node->AddNode(first.release());
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
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            while (true)
                            {
                                std::int64_t save = lexer.GetPos();
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
                                                soul::parser::Match match = PunctuationParser<LexerT>::Comma(lexer);
                                                comma.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    node->AddNode(comma.release());
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
                                                    soul::parser::Match match = ClassParser<LexerT>::BaseSpecifier(lexer, context);
                                                    next.reset(static_cast<otava::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        node->AddNode(next.release());
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
                                        *parentMatch6 = match;
                                    }
                                    else
                                    {
                                        lexer.SetPos(save);
                                        break;
                                    }
                                }
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
                soul::parser::Match* parentMatch12 = &match;
                {
                    soul::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch13 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch15 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = PunctuationParser<LexerT>::Ellipsis(lexer);
                                ellipsis.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    node->AddNode(ellipsis.release());
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BaseSpecifierList");
                #endif
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BaseSpecifierList");
        else soul::lexer::WriteFailureToLog(lexer, "BaseSpecifierList");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::BaseSpecifier(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "BaseSpecifier");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158029);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> accessSpecifierNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> virtualSpecifier = std::unique_ptr<otava::ast::Node>();
    bool virtualFirst = bool();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> virt;
    std::unique_ptr<otava::ast::Node> access;
    std::unique_ptr<otava::ast::Node> access2;
    std::unique_ptr<otava::ast::Node> virt2;
    std::unique_ptr<otava::ast::Node> classOrDeclType;
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
                                soul::parser::Match match = AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                                attributes.reset(static_cast<otava::ast::Node*>(match.value));
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                std::int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch10 = &match;
                                switch (*lexer)
                                {
                                    case VIRTUAL:
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch11 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch12 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ClassParser<LexerT>::VirtualSpecifier(lexer);
                                                virt.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                    virtualSpecifier.reset(virt.release());
                                                    virtualFirst = true;
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
                                                            soul::parser::Match match = ClassParser<LexerT>::AccessSpecifier(lexer);
                                                            access.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                accessSpecifierNode.reset(access.release());
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
                                        if (match.hit)
                                        {
                                            *parentMatch10 = match;
                                        }
                                        break;
                                    }
                                    case PRIVATE:
                                    case PROTECTED:
                                    case PUBLIC:
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch17 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch18 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ClassParser<LexerT>::AccessSpecifier(lexer);
                                                access2.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                    accessSpecifierNode.reset(access2.release());
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
                                                std::int64_t save = lexer.GetPos();
                                                soul::parser::Match* parentMatch20 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch21 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch22 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = ClassParser<LexerT>::VirtualSpecifier(lexer);
                                                            virt2.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                virtualSpecifier.reset(virt2.release());
                                                            }
                                                            *parentMatch22 = match;
                                                        }
                                                        *parentMatch21 = match;
                                                    }
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
                                    soul::parser::Match* parentMatch23 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(true);
                                        *parentMatch23 = match;
                                    }
                                    *parentMatch9 = match;
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
                soul::parser::Match* parentMatch24 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch25 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ClassParser<LexerT>::ClassOrDeclType(lexer, context);
                        classOrDeclType.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch25 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BaseSpecifier");
                #endif
                return soul::parser::Match(true, new otava::ast::BaseSpecifierNode(sourcePos, classOrDeclType.release(), accessSpecifierNode.release(), virtualSpecifier.release(), attributes.release(), virtualFirst));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BaseSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "BaseSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::ClassOrDeclType(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "ClassOrDeclType");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158030);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos tmpPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> nns;
    std::unique_ptr<otava::ast::Node> tmp;
    std::unique_ptr<otava::ast::Node> simpleTemplateId;
    std::unique_ptr<otava::ast::Node> nns2;
    std::unique_ptr<otava::ast::Node> id;
    std::unique_ptr<otava::ast::Node> typeName2;
    std::unique_ptr<otava::ast::Node> declTypeSpecifier;
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match = IdentifierParser<LexerT>::NestedNameSpecifier(lexer, context);
                            nns.reset(static_cast<otava::ast::Node*>(match.value));
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = TemplateParser<LexerT>::Template(lexer);
                                tmp.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    tmpPos = sourcePos;
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
                            soul::parser::Match match = TemplateParser<LexerT>::SimpleTemplateId(lexer, context);
                            simpleTemplateId.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassOrDeclType");
                                    #endif
                                    return soul::parser::Match(true, new otava::ast::QualifiedIdNode(sourcePos, nns.release(), new otava::ast::PrefixNode(tmpPos, tmp.release(), simpleTemplateId.release())));
                                }
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch12 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = IdentifierParser<LexerT>::NestedNameSpecifier(lexer, context);
                                nns2.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    sourcePos = lexer.GetSourcePos(pos);
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
                                    soul::parser::Match match = IdentifierParser<LexerT>::Identifier(lexer, context);
                                    id.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassOrDeclType");
                                            #endif
                                            return soul::parser::Match(true, new otava::ast::QualifiedIdNode(sourcePos, nns2.release(), id.release()));
                                        }
                                    }
                                    *parentMatch14 = match;
                                }
                                *parentMatch13 = match;
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
                soul::parser::Match* parentMatch15 = &match;
                lexer.SetPos(save);
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch16 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match = TypeParser<LexerT>::TypeName(lexer, context);
                        typeName2.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassOrDeclType");
                                #endif
                                return soul::parser::Match(true, typeName2.release());
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
                    soul::parser::Match match = TypeParser<LexerT>::DeclTypeSpecifier(lexer, context);
                    declTypeSpecifier.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassOrDeclType");
                            #endif
                            return soul::parser::Match(true, declTypeSpecifier.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassOrDeclType");
        else soul::lexer::WriteFailureToLog(lexer, "ClassOrDeclType");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberSpecification(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberSpecification");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158031);
    std::unique_ptr<otava::ast::Node> accessSpecifierNode = std::unique_ptr<otava::ast::Node>();
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos colonPos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> accessSpecifier;
    std::unique_ptr<otava::ast::Node> memberDeclaration;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
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
                        soul::parser::Match match = ClassParser<LexerT>::AccessSpecifier(lexer);
                        accessSpecifier.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            sourcePos = lexer.GetSourcePos(pos);
                            accessSpecifierNode.reset(accessSpecifier.release());
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
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == COLON)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                colonPos = lexer.GetSourcePos(pos);
                                otava::symbols::SetCurrentAccess(accessSpecifierNode.get(), context);
                                container->AddNode(new otava::ast::BeginAccessGroupNode(sourcePos, accessSpecifierNode.release(), colonPos));
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
                    soul::parser::Match* parentMatch7 = &match;
                    lexer.SetPos(save);
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch8 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ClassParser<LexerT>::MemberDeclarationReset(lexer, context);
                            memberDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                container->AddNode(memberDeclaration.release());
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(true);
        soul::parser::Match* parentMatch9 = &match;
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
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch13 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ClassParser<LexerT>::AccessSpecifier(lexer);
                                accessSpecifier.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    sourcePos = lexer.GetSourcePos(pos);
                                    accessSpecifierNode.reset(accessSpecifier.release());
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
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == COLON)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        colonPos = lexer.GetSourcePos(pos);
                                        otava::symbols::SetCurrentAccess(accessSpecifierNode.get(), context);
                                        container->AddNode(new otava::ast::BeginAccessGroupNode(sourcePos, accessSpecifierNode.release(), colonPos));
                                    }
                                    *parentMatch15 = match;
                                }
                                *parentMatch14 = match;
                            }
                            *parentMatch12 = match;
                        }
                        *parentMatch11 = match;
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
                                    soul::parser::Match match = ClassParser<LexerT>::MemberDeclarationReset(lexer, context);
                                    memberDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        container->AddNode(memberDeclaration.release());
                                    }
                                    *parentMatch17 = match;
                                }
                                *parentMatch16 = match;
                            }
                            *parentMatch11 = match;
                        }
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
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberSpecification");
        else soul::lexer::WriteFailureToLog(lexer, "MemberSpecification");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberDeclarationReset(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberDeclarationReset");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158032);
    std::unique_ptr<otava::ast::Node> memberDeclaration;
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
                context->PushResetFlag(otava::symbols::ContextFlags::virtualSeen);
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
                soul::parser::Match match = ClassParser<LexerT>::MemberDeclaration(lexer, context);
                memberDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    context->PopFlags();
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarationReset");
                        #endif
                        return soul::parser::Match(true, memberDeclaration.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarationReset");
        else soul::lexer::WriteFailureToLog(lexer, "MemberDeclarationReset");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberDeclaration(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberDeclaration");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158033);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> declSpecifiersNode = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> declaratorsNode = std::unique_ptr<otava::ast::Node>();
    bool nextIsRBrace = bool();
    std::unique_ptr<otava::ast::Node> attributes;
    std::unique_ptr<otava::ast::Node> declSpecifiers;
    std::unique_ptr<otava::ast::Node> declarators;
    std::unique_ptr<otava::ast::Node> semicolon;
    std::unique_ptr<otava::ast::Node> attributes2;
    std::unique_ptr<otava::ast::Node> declSpecifiers2;
    std::unique_ptr<otava::ast::Node> declarators2;
    std::unique_ptr<otava::ast::Node> semicolon2;
    std::unique_ptr<otava::ast::Node> memberFunctionDefinition;
    std::unique_ptr<otava::ast::Node> retMemberFunctionDefinition;
    std::unique_ptr<otava::ast::Node> usingDeclaration;
    std::unique_ptr<otava::ast::Node> usingEnumDeclaration;
    std::unique_ptr<otava::ast::Node> staticAssertDeclaration;
    std::unique_ptr<otava::ast::Node> templateDeclaration;
    std::unique_ptr<otava::ast::Node> explicitSpecialization;
    std::unique_ptr<otava::ast::Node> deductionGuide;
    std::unique_ptr<otava::ast::Node> aliasDeclaration;
    std::unique_ptr<otava::ast::Node> opaqueEnumDeclaration;
    std::unique_ptr<otava::ast::Node> emptyDeclaration;
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
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch15 = &match;
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
                                                                                    soul::parser::Match match = AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                                                                                    attributes.reset(static_cast<otava::ast::Node*>(match.value));
                                                                                    if (match.hit)
                                                                                    {
                                                                                        sourcePos = lexer.GetSourcePos(pos);
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
                                                                                        std::int64_t pos = lexer.GetPos();
                                                                                        soul::parser::Match match = ClassParser<LexerT>::MemberDeclSpecifiers(lexer, context);
                                                                                        declSpecifiers.reset(static_cast<otava::ast::Node*>(match.value));
                                                                                        if (match.hit)
                                                                                        {
                                                                                            if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                                            declSpecifiersNode.reset(declSpecifiers.release());
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
                                                                        *parentMatch16 = match;
                                                                    }
                                                                    *parentMatch15 = match;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch24 = &match;
                                                                    {
                                                                        soul::parser::Match match(true);
                                                                        std::int64_t save = lexer.GetPos();
                                                                        soul::parser::Match* parentMatch25 = &match;
                                                                        {
                                                                            soul::parser::Match match(false);
                                                                            soul::parser::Match* parentMatch26 = &match;
                                                                            {
                                                                                soul::parser::Match match(false);
                                                                                soul::parser::Match* parentMatch27 = &match;
                                                                                {
                                                                                    std::int64_t pos = lexer.GetPos();
                                                                                    soul::parser::Match match = ClassParser<LexerT>::MemberDeclaratorList(lexer, context);
                                                                                    declarators.reset(static_cast<otava::ast::Node*>(match.value));
                                                                                    if (match.hit)
                                                                                    {
                                                                                        if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                                        declaratorsNode.reset(declarators.release());
                                                                                    }
                                                                                    *parentMatch27 = match;
                                                                                }
                                                                                *parentMatch26 = match;
                                                                            }
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
                                                                    *parentMatch15 = match;
                                                                }
                                                                *parentMatch14 = match;
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
                                                                        bool pass = true;
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch30 = &match;
                                                                        {
                                                                            soul::parser::Match match(false);
                                                                            soul::parser::Match* parentMatch31 = &match;
                                                                            {
                                                                                std::int64_t pos = lexer.GetPos();
                                                                                soul::parser::Match match = PunctuationParser<LexerT>::Semicolon(lexer);
                                                                                semicolon.reset(static_cast<otava::ast::Node*>(match.value));
                                                                                if (match.hit)
                                                                                {
                                                                                    if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                                }
                                                                                *parentMatch31 = match;
                                                                            }
                                                                            *parentMatch30 = match;
                                                                        }
                                                                        if (match.hit)
                                                                        {
                                                                            if (!declSpecifiersNode && !declaratorsNode) pass = false;
                                                                            else
                                                                            {
                                                                                otava::ast::MemberDeclarationNode *memberDeclarationNode = new otava::ast::MemberDeclarationNode(sourcePos, attributes.release(), declSpecifiersNode.release(), declaratorsNode.release(), semicolon.release());
                                                                                otava::symbols::ProcessMemberDeclaration(memberDeclarationNode, nullptr, context);
                                                                                {
                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                                                    #endif
                                                                                    return soul::parser::Match(true, memberDeclarationNode);
                                                                                }
                                                                            }
                                                                        }
                                                                        if (match.hit && !pass)
                                                                        {
                                                                            match = soul::parser::Match(false);
                                                                        }
                                                                        *parentMatch29 = match;
                                                                    }
                                                                    *parentMatch28 = match;
                                                                }
                                                                *parentMatch14 = match;
                                                            }
                                                            *parentMatch13 = match;
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
                                                                                soul::parser::Match match(true);
                                                                                std::int64_t save = lexer.GetPos();
                                                                                soul::parser::Match* parentMatch36 = &match;
                                                                                {
                                                                                    soul::parser::Match match(false);
                                                                                    soul::parser::Match* parentMatch37 = &match;
                                                                                    {
                                                                                        soul::parser::Match match(false);
                                                                                        soul::parser::Match* parentMatch38 = &match;
                                                                                        {
                                                                                            std::int64_t pos = lexer.GetPos();
                                                                                            soul::parser::Match match = AttributeParser<LexerT>::AttributeSpecifierSeq(lexer, context);
                                                                                            attributes2.reset(static_cast<otava::ast::Node*>(match.value));
                                                                                            if (match.hit)
                                                                                            {
                                                                                                sourcePos = lexer.GetSourcePos(pos);
                                                                                            }
                                                                                            *parentMatch38 = match;
                                                                                        }
                                                                                        *parentMatch37 = match;
                                                                                    }
                                                                                    if (match.hit)
                                                                                    {
                                                                                        *parentMatch36 = match;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        lexer.SetPos(save);
                                                                                    }
                                                                                }
                                                                                *parentMatch35 = match;
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
                                                                                        soul::parser::Match match = ClassParser<LexerT>::RetMemberDeclSpecifiers(lexer, context);
                                                                                        declSpecifiers2.reset(static_cast<otava::ast::Node*>(match.value));
                                                                                        if (match.hit)
                                                                                        {
                                                                                            if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                                            declSpecifiersNode.reset(declSpecifiers2.release());
                                                                                        }
                                                                                        *parentMatch40 = match;
                                                                                    }
                                                                                    *parentMatch39 = match;
                                                                                }
                                                                                *parentMatch35 = match;
                                                                            }
                                                                            *parentMatch34 = match;
                                                                        }
                                                                        if (match.hit)
                                                                        {
                                                                            soul::parser::Match match(false);
                                                                            soul::parser::Match* parentMatch41 = &match;
                                                                            {
                                                                                soul::parser::Match match(false);
                                                                                soul::parser::Match* parentMatch42 = &match;
                                                                                {
                                                                                    std::int64_t pos = lexer.GetPos();
                                                                                    soul::parser::Match match = ClassParser<LexerT>::MemberDeclaratorList(lexer, context);
                                                                                    declarators2.reset(static_cast<otava::ast::Node*>(match.value));
                                                                                    if (match.hit)
                                                                                    {
                                                                                        declaratorsNode.reset(declarators2.release());
                                                                                    }
                                                                                    *parentMatch42 = match;
                                                                                }
                                                                                *parentMatch41 = match;
                                                                            }
                                                                            *parentMatch34 = match;
                                                                        }
                                                                        *parentMatch33 = match;
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
                                                                                soul::parser::Match match = PunctuationParser<LexerT>::Semicolon(lexer);
                                                                                semicolon2.reset(static_cast<otava::ast::Node*>(match.value));
                                                                                if (match.hit)
                                                                                {
                                                                                    otava::ast::MemberDeclarationNode *memberDeclarationNode = new otava::ast::MemberDeclarationNode(sourcePos, attributes2.release(), declSpecifiersNode.release(), declaratorsNode.release(), semicolon2.release());
                                                                                    otava::symbols::ProcessMemberDeclaration(memberDeclarationNode, nullptr, context);
                                                                                    {
                                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                                                        #endif
                                                                                        return soul::parser::Match(true, memberDeclarationNode);
                                                                                    }
                                                                                }
                                                                                *parentMatch44 = match;
                                                                            }
                                                                            *parentMatch43 = match;
                                                                        }
                                                                        *parentMatch33 = match;
                                                                    }
                                                                    *parentMatch32 = match;
                                                                }
                                                                *parentMatch13 = match;
                                                            }
                                                        }
                                                        *parentMatch12 = match;
                                                        if (!match.hit)
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch45 = &match;
                                                            lexer.SetPos(save);
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch46 = &match;
                                                                {
                                                                    std::int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match = ClassParser<LexerT>::MemberFunctionDefinition(lexer, context);
                                                                    memberFunctionDefinition.reset(static_cast<otava::ast::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        std::unique_ptr<otava::ast::Node> memFunDefNode;
                                                                        memFunDefNode.reset(memberFunctionDefinition.release());
                                                                        otava::symbols::ProcessMemberFunctionDefinition(memFunDefNode.get(), context);
                                                                        {
                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                                            #endif
                                                                            return soul::parser::Match(true, memFunDefNode.release());
                                                                        }
                                                                    }
                                                                    *parentMatch46 = match;
                                                                }
                                                                *parentMatch45 = match;
                                                            }
                                                            *parentMatch12 = match;
                                                        }
                                                    }
                                                    *parentMatch11 = match;
                                                    if (!match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch47 = &match;
                                                        lexer.SetPos(save);
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch48 = &match;
                                                            {
                                                                std::int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = ClassParser<LexerT>::RetMemberFunctionDefinition(lexer, context);
                                                                retMemberFunctionDefinition.reset(static_cast<otava::ast::Node*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    std::unique_ptr<otava::ast::Node> memFunDefNode;
                                                                    memFunDefNode.reset(retMemberFunctionDefinition.release());
                                                                    otava::symbols::ProcessMemberFunctionDefinition(memFunDefNode.get(), context);
                                                                    {
                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                                        #endif
                                                                        return soul::parser::Match(true, memFunDefNode.release());
                                                                    }
                                                                }
                                                                *parentMatch48 = match;
                                                            }
                                                            *parentMatch47 = match;
                                                        }
                                                        *parentMatch11 = match;
                                                    }
                                                }
                                                *parentMatch10 = match;
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
                                                            soul::parser::Match match = DeclarationParser<LexerT>::UsingDeclaration(lexer, context);
                                                            usingDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                {
                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                                    #endif
                                                                    return soul::parser::Match(true, usingDeclaration.release());
                                                                }
                                                            }
                                                            *parentMatch50 = match;
                                                        }
                                                        *parentMatch49 = match;
                                                    }
                                                    *parentMatch10 = match;
                                                }
                                            }
                                            *parentMatch9 = match;
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
                                                        soul::parser::Match match = DeclarationParser<LexerT>::UsingEnumDeclaration(lexer, context);
                                                        usingEnumDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            {
                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                                #endif
                                                                return soul::parser::Match(true, usingEnumDeclaration.release());
                                                            }
                                                        }
                                                        *parentMatch52 = match;
                                                    }
                                                    *parentMatch51 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                        }
                                        *parentMatch8 = match;
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
                                                    soul::parser::Match match = DeclarationParser<LexerT>::StaticAssertDeclaration(lexer, context);
                                                    staticAssertDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        {
                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                            #endif
                                                            return soul::parser::Match(true, staticAssertDeclaration.release());
                                                        }
                                                    }
                                                    *parentMatch54 = match;
                                                }
                                                *parentMatch53 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                    }
                                    *parentMatch7 = match;
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
                                                soul::parser::Match match = ClassParser<LexerT>::MemberTemplateDeclaration(lexer, context);
                                                templateDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    {
                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                        #endif
                                                        return soul::parser::Match(true, templateDeclaration.release());
                                                    }
                                                }
                                                *parentMatch56 = match;
                                            }
                                            *parentMatch55 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                }
                                *parentMatch6 = match;
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
                                            soul::parser::Match match = TemplateParser<LexerT>::ExplicitSpecialization(lexer, context);
                                            explicitSpecialization.reset(static_cast<otava::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                    #endif
                                                    return soul::parser::Match(true, explicitSpecialization.release());
                                                }
                                            }
                                            *parentMatch58 = match;
                                        }
                                        *parentMatch57 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
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
                                        soul::parser::Match match = TemplateParser<LexerT>::DeductionGuide(lexer, context);
                                        deductionGuide.reset(static_cast<otava::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                #endif
                                                return soul::parser::Match(true, deductionGuide.release());
                                            }
                                        }
                                        *parentMatch60 = match;
                                    }
                                    *parentMatch59 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
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
                                    soul::parser::Match match = DeclarationParser<LexerT>::AliasDeclaration(lexer, context);
                                    aliasDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                            #endif
                                            return soul::parser::Match(true, aliasDeclaration.release());
                                        }
                                    }
                                    *parentMatch62 = match;
                                }
                                *parentMatch61 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
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
                                soul::parser::Match match = EnumParser<LexerT>::OpaqueEnumDeclaration(lexer, context);
                                opaqueEnumDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                        #endif
                                        return soul::parser::Match(true, opaqueEnumDeclaration.release());
                                    }
                                }
                                *parentMatch64 = match;
                            }
                            *parentMatch63 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
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
                            soul::parser::Match match = DeclarationParser<LexerT>::EmptyDeclaration(lexer);
                            emptyDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                    #endif
                                    return soul::parser::Match(true, emptyDeclaration.release());
                                }
                            }
                            *parentMatch66 = match;
                        }
                        *parentMatch65 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
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
                        bool pass = true;
                        soul::parser::Match match = ClassParser<LexerT>::RBraceNext(lexer);
                        if (match.hit)
                        {
                            nextIsRBrace = true;
                            pass = false;
                        }
                        if (match.hit && !pass)
                        {
                            match = soul::parser::Match(false);
                        }
                        *parentMatch68 = match;
                    }
                    *parentMatch67 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
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
                    bool pass = true;
                    soul::parser::Match match(true);
                    if (match.hit)
                    {
                        if (!nextIsRBrace)
                        {
                            ThrowMemberDeclarationParsingError(lexer.GetSourcePos(pos), context);
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
                    *parentMatch70 = match;
                }
                *parentMatch69 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
        else soul::lexer::WriteFailureToLog(lexer, "MemberDeclaration");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::RBraceNext(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "RBraceNext");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158034);
    soul::parser::Match match(true);
    std::int64_t save = lexer.GetPos();
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == RBRACE)
            {
                ++lexer;
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
soul::parser::Match ClassParser<LexerT>::MemberDeclSpecifiers(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberDeclSpecifiers");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158035);
    std::unique_ptr<otava::ast::Node> declSpecifiers;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match = DeclarationParser<LexerT>::DeclSpecifierSeq(lexer, context);
        declSpecifiers.reset(static_cast<otava::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclSpecifiers");
                #endif
                return soul::parser::Match(true, declSpecifiers.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclSpecifiers");
        else soul::lexer::WriteFailureToLog(lexer, "MemberDeclSpecifiers");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::RetMemberDeclSpecifiers(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "RetMemberDeclSpecifiers");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158036);
    std::unique_ptr<otava::ast::Node> declSpecifiers;
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
                context->PushSetFlag(ContextFlags::retMemberDeclSpecifiers);
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
                soul::parser::Match match = DeclarationParser<LexerT>::DeclSpecifierSeq(lexer, context);
                declSpecifiers.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    context->PopFlags();
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RetMemberDeclSpecifiers");
                        #endif
                        return soul::parser::Match(true, declSpecifiers.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RetMemberDeclSpecifiers");
        else soul::lexer::WriteFailureToLog(lexer, "RetMemberDeclSpecifiers");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberFunctionDefinition(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberFunctionDefinition");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158037);
    std::unique_ptr<otava::ast::Node> noDeclSpecFunctionDefinition;
    std::unique_ptr<otava::ast::Node> functionDefinition;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match = FunctionParser<LexerT>::NoDeclSpecFunctionDefinition(lexer, context);
            noDeclSpecFunctionDefinition.reset(static_cast<otava::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberFunctionDefinition");
                    #endif
                    return soul::parser::Match(true, noDeclSpecFunctionDefinition.release());
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
                    soul::parser::Match match = FunctionParser<LexerT>::FunctionDefinition(lexer, context);
                    functionDefinition.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberFunctionDefinition");
                            #endif
                            return soul::parser::Match(true, functionDefinition.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberFunctionDefinition");
        else soul::lexer::WriteFailureToLog(lexer, "MemberFunctionDefinition");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::RetMemberFunctionDefinition(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "RetMemberFunctionDefinition");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158038);
    std::unique_ptr<otava::ast::Node> functionDefinition;
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
                context->PushSetFlag(ContextFlags::retMemberDeclSpecifiers);
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
                soul::parser::Match match = FunctionParser<LexerT>::FunctionDefinition(lexer, context);
                functionDefinition.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    context->PopFlags();
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RetMemberFunctionDefinition");
                        #endif
                        return soul::parser::Match(true, functionDefinition.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RetMemberFunctionDefinition");
        else soul::lexer::WriteFailureToLog(lexer, "RetMemberFunctionDefinition");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberTemplateDeclaration(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberTemplateDeclaration");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158039);
    std::unique_ptr<otava::ast::Node> templateDeclaration;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match = TemplateParser<LexerT>::TemplateDeclaration(lexer, context);
        templateDeclaration.reset(static_cast<otava::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberTemplateDeclaration");
                #endif
                return soul::parser::Match(true, templateDeclaration.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberTemplateDeclaration");
        else soul::lexer::WriteFailureToLog(lexer, "MemberTemplateDeclaration");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberDeclaratorList(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberDeclaratorList");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158040);
    std::unique_ptr<otava::ast::Node> node = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> first;
    std::unique_ptr<otava::ast::Node> comma;
    std::unique_ptr<otava::ast::Node> next;
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
                    soul::parser::Match match = ClassParser<LexerT>::MemberDeclarator(lexer, context);
                    first.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        node.reset(new otava::ast::MemberDeclaratorListNode(lexer.GetSourcePos(pos)));
                        node->AddNode(first.release());
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
                                        soul::parser::Match* parentMatch8 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = PunctuationParser<LexerT>::Comma(lexer);
                                            comma.reset(static_cast<otava::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                node->AddNode(comma.release());
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
                                                soul::parser::Match match = ClassParser<LexerT>::MemberDeclarator(lexer, context);
                                                next.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    node->AddNode(next.release());
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaratorList");
                #endif
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaratorList");
        else soul::lexer::WriteFailureToLog(lexer, "MemberDeclaratorList");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberDeclarator(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberDeclarator");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158041);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::TrailingQualifiersNode> trailingQualifiersNode = std::unique_ptr<otava::ast::TrailingQualifiersNode>();
    std::unique_ptr<otava::ast::Node> declarator;
    std::unique_ptr<otava::ast::Node> requiresClause;
    std::unique_ptr<otava::ast::Node> initializer;
    std::unique_ptr<otava::ast::Node> virtSpecifierSeq;
    std::unique_ptr<otava::ast::Node> pureSpecifier;
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
                            soul::parser::Match match = DeclarationParser<LexerT>::Declarator(lexer, context);
                            declarator.reset(static_cast<otava::ast::Node*>(match.value));
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
                                            soul::parser::Match match = ConceptParser<LexerT>::RequiresClause(lexer, context);
                                            requiresClause.reset(static_cast<otava::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarator");
                                                    #endif
                                                    return soul::parser::Match(true, new otava::ast::InitDeclaratorNode(sourcePos, declarator.release(), requiresClause.release()));
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
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch13 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        bool pass = true;
                                                        soul::parser::Match match(true);
                                                        if (match.hit)
                                                        {
                                                            pass = !context->GetFlag(otava::symbols::ContextFlags::virtualSeen);
                                                        }
                                                        if (match.hit && !pass)
                                                        {
                                                            match = soul::parser::Match(false);
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
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = InitializationParser<LexerT>::BraceOrEqualInitializer(lexer, context);
                                                            initializer.reset(static_cast<otava::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                {
                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarator");
                                                                    #endif
                                                                    return soul::parser::Match(true, new otava::ast::InitDeclaratorNode(sourcePos, declarator.release(), initializer.release()));
                                                                }
                                                            }
                                                            *parentMatch15 = match;
                                                        }
                                                        *parentMatch14 = match;
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
                                        soul::parser::Match* parentMatch16 = &match;
                                        lexer.SetPos(save);
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch17 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                if (match.hit)
                                                {
                                                    trailingQualifiersNode.reset(new otava::ast::TrailingQualifiersNode(sourcePos, declarator.release()));
                                                }
                                                *parentMatch17 = match;
                                            }
                                            *parentMatch16 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
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
                                    soul::parser::Match match = ClassParser<LexerT>::VirtSpecifierSeq(lexer, context);
                                    virtSpecifierSeq.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        trailingQualifiersNode->AddNode(virtSpecifierSeq.release());
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
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ClassParser<LexerT>::PureSpecifier(lexer);
                                pureSpecifier.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    trailingQualifiersNode->AddNode(pureSpecifier.release());
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            if (trailingQualifiersNode->Nodes().IsEmpty())
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarator");
                    #endif
                    return soul::parser::Match(true, trailingQualifiersNode->ReleaseSubject());
                }
            }
            else
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarator");
                    #endif
                    return soul::parser::Match(true, trailingQualifiersNode.release());
                }
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarator");
        else soul::lexer::WriteFailureToLog(lexer, "MemberDeclarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::CtorInitializer(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "CtorInitializer");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158042);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> ctorInitializerGuarded;
    std::unique_ptr<otava::ast::Node> ctorInitializerSaved;
    std::unique_ptr<otava::ast::Node> ctorInitializerUnguarded;
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
                soul::parser::Match match = GuardParser<LexerT>::MemberFunctionGuard(lexer, context);
                *parentMatch2 = match;
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
                        soul::parser::Match match = ClassParser<LexerT>::CtorInitializerGuarded(lexer, context);
                        ctorInitializerGuarded.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializer");
                                #endif
                                return soul::parser::Match(true, ctorInitializerGuarded.release());
                            }
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
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
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match = GuardParser<LexerT>::SavedCtorInitializerGuard(lexer, context);
                            if (match.hit)
                            {
                                context->ResetFlag(ContextFlags::parseSavedCtorInitializer);
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
                                soul::parser::Match match = ClassParser<LexerT>::CtorInitializerSaved(lexer, context);
                                ctorInitializerSaved.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializer");
                                        #endif
                                        return soul::parser::Match(true, ctorInitializerSaved.release());
                                    }
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch6 = match;
                    }
                    *parentMatch5 = match;
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
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ClassParser<LexerT>::CtorInitializerUnguarded(lexer, context);
                    ctorInitializerUnguarded.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializer");
                            #endif
                            return soul::parser::Match(true, ctorInitializerUnguarded.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializer");
        else soul::lexer::WriteFailureToLog(lexer, "CtorInitializer");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::CtorInitializerGuarded(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "CtorInitializerGuarded");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158043);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        bool pass = true;
        soul::parser::Match match(false);
        if (*lexer == COLON)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            sourcePos = lexer.GetSourcePos(pos);
            soul::ast::lexer::pos::pair::LexerPosPair lexerPosPair = otava::parser::recorded::parse::RecordCtorInitializer(lexer);
            if (lexerPosPair.IsValid())
            {
                otava::ast::ConstructorInitializerNode *ctorInitializerNode = new otava::ast::ConstructorInitializerNode(sourcePos);
                ctorInitializerNode->SetLexerPosPair(lexerPosPair);
                ctorInitializerNode->SetFunctionScope(context->GetSymbolTable()->CurrentScope());
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializerGuarded");
                    #endif
                    return soul::parser::Match(true, ctorInitializerNode);
                }
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
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializerGuarded");
        else soul::lexer::WriteFailureToLog(lexer, "CtorInitializerGuarded");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::CtorInitializerUnguarded(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "CtorInitializerUnguarded");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158044);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::Node> memberInitializerList;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == COLON)
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
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match = ClassParser<LexerT>::MemberInitializerList(lexer, context);
                memberInitializerList.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializerUnguarded");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ConstructorInitializerNode(sourcePos, memberInitializerList.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializerUnguarded");
        else soul::lexer::WriteFailureToLog(lexer, "CtorInitializerUnguarded");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::CtorInitializerSaved(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "CtorInitializerSaved");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158045);
    otava::ast::ConstructorInitializerNode* ctorInitializerNode = nullptr;
    std::unique_ptr<otava::ast::Node> memberInitializerList;
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
                    ctorInitializerNode = otava::parser::recorded::parse::GetSavedCtorInitializerNode(context);
                    if (!ctorInitializerNode)
                    {
                        pass = false;
                    }
                    else
                    {
                        lexer.BeginRecordedParse(ctorInitializerNode->GetLexerPosPair());
                        Scope *functionScope = static_cast<Scope*>(ctorInitializerNode->FunctionScope());
                        context->GetSymbolTable()->BeginScope(functionScope);
                    }
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
                    std::int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ClassParser<LexerT>::MemberInitializerList(lexer, context);
                    memberInitializerList.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        ctorInitializerNode->SetMemberInitializerListNode(memberInitializerList.release());
                        lexer.EndRecordedParse();
                        context->GetSymbolTable()->EndScope();
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializerSaved");
                            #endif
                            return soul::parser::Match(true, ctorInitializerNode);
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
                    std::int64_t pos = lexer.GetPos();
                    bool pass = true;
                    soul::parser::Match match(true);
                    if (match.hit)
                    {
                        lexer.EndRecordedParse();
                        pass = false;
                    }
                    if (match.hit && !pass)
                    {
                        match = soul::parser::Match(false);
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializerSaved");
        else soul::lexer::WriteFailureToLog(lexer, "CtorInitializerSaved");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberInitializerList(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberInitializerList");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158046);
    std::unique_ptr<otava::ast::Node> node = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> first;
    std::unique_ptr<otava::ast::Node> comma;
    std::unique_ptr<otava::ast::Node> next;
    std::unique_ptr<otava::ast::Node> ellipsis;
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
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ClassParser<LexerT>::MemberInitializer(lexer, context);
                        first.reset(static_cast<otava::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            node.reset(new otava::ast::MemberInitializerListNode(lexer.GetSourcePos(pos)));
                            node->AddNode(first.release());
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
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            while (true)
                            {
                                std::int64_t save = lexer.GetPos();
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
                                                soul::parser::Match match = PunctuationParser<LexerT>::Comma(lexer);
                                                comma.reset(static_cast<otava::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    node->AddNode(comma.release());
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
                                                    soul::parser::Match match = ClassParser<LexerT>::MemberInitializer(lexer, context);
                                                    next.reset(static_cast<otava::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        node->AddNode(next.release());
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
                                        *parentMatch6 = match;
                                    }
                                    else
                                    {
                                        lexer.SetPos(save);
                                        break;
                                    }
                                }
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
                soul::parser::Match* parentMatch12 = &match;
                {
                    soul::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch13 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch15 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match = PunctuationParser<LexerT>::Ellipsis(lexer);
                                ellipsis.reset(static_cast<otava::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    node->AddNode(ellipsis.release());
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializerList");
                #endif
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializerList");
        else soul::lexer::WriteFailureToLog(lexer, "MemberInitializerList");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberInitializer(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberInitializer");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158047);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<otava::ast::ExpressionListNode> exprListNode = std::unique_ptr<otava::ast::ExpressionListNode>();
    std::unique_ptr<otava::ast::Node> node = std::unique_ptr<otava::ast::Node>();
    std::unique_ptr<otava::ast::Node> id;
    std::unique_ptr<otava::ast::Node> bracedInitList;
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
                    soul::parser::Match match = ClassParser<LexerT>::MemberInitializerId(lexer, context);
                    id.reset(static_cast<otava::ast::Node*>(match.value));
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        switch (*lexer)
                        {
                            case LPAREN:
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
                                            if (*lexer == LPAREN)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                exprListNode.reset(new otava::ast::ExpressionListNode(sourcePos));
                                                exprListNode->SetLParenPos(sourcePos);
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
                                                soul::parser::Match match = ExpressionParser<LexerT>::ExpressionList(lexer, context, exprListNode.get());
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
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch13 = &match;
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
                                                exprListNode->SetRParenPos(sourcePos);
                                                node.reset(exprListNode.release());
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
                            case LBRACE:
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch14 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = InitializationParser<LexerT>::BracedInitList(lexer, context);
                                    bracedInitList.reset(static_cast<otava::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        node.reset(bracedInitList.release());
                                    }
                                    *parentMatch14 = match;
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
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializer");
                #endif
                return soul::parser::Match(true, new otava::ast::MemberInitializerNode(sourcePos, id.release(), node.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializer");
        else soul::lexer::WriteFailureToLog(lexer, "MemberInitializer");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::MemberInitializerId(LexerT& lexer, otava::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "MemberInitializerId");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158048);
    std::unique_ptr<otava::ast::Node> classOrDeclType;
    std::unique_ptr<otava::ast::Node> identifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match = ClassParser<LexerT>::ClassOrDeclType(lexer, context);
            classOrDeclType.reset(static_cast<otava::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializerId");
                    #endif
                    return soul::parser::Match(true, classOrDeclType.release());
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
                    soul::parser::Match match = IdentifierParser<LexerT>::Identifier(lexer, context);
                    identifier.reset(static_cast<otava::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializerId");
                            #endif
                            return soul::parser::Match(true, identifier.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializerId");
        else soul::lexer::WriteFailureToLog(lexer, "MemberInitializerId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::PureSpecifier(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "PureSpecifier");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158049);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos zeroPos = soul::ast::SourcePos();
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
                    if (*lexer == ASSIGN)
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch5 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        bool pass = true;
                        soul::parser::Match match(false);
                        if (*lexer == INTEGER_LITERAL)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            zeroPos = lexer.GetSourcePos(pos);
                            std::u32string value = lexer.GetToken(pos).ToString();
                            pass = value == U"0";
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
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PureSpecifier");
                #endif
                return soul::parser::Match(true, new otava::ast::PureSpecifierNode(sourcePos, zeroPos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PureSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "PureSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::AccessSpecifier(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "AccessSpecifier");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158050);
    std::unique_ptr<otava::ast::Node> privat;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case PUBLIC:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == PUBLIC)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AccessSpecifier");
                        #endif
                        return soul::parser::Match(true, new otava::ast::PublicNode(lexer.GetSourcePos(pos)));
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
        case PROTECTED:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == PROTECTED)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AccessSpecifier");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ProtectedNode(lexer.GetSourcePos(pos)));
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
        case PRIVATE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match = ClassParser<LexerT>::Private(lexer);
                privat.reset(static_cast<otava::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AccessSpecifier");
                        #endif
                        return soul::parser::Match(true, privat.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AccessSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "AccessSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::Private(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "Private");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158051);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == PRIVATE)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Private");
                #endif
                return soul::parser::Match(true, new otava::ast::PrivateNode(lexer.GetSourcePos(pos)));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Private");
        else soul::lexer::WriteFailureToLog(lexer, "Private");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match ClassParser<LexerT>::VirtualSpecifier(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "VirtualSpecifier");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 1303477245251158052);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == VIRTUAL)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VirtualSpecifier");
                #endif
                return soul::parser::Match(true, new otava::ast::VirtualNode(lexer.GetSourcePos(pos)));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VirtualSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "VirtualSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct ClassParser<soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>>;

} // namespace otava::parser::classes
