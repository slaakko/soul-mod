
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/class.parser' using soul parser generator spg version 4.0.0

module soul.cpp20.parser.classes;

import util;
import soul.ast.spg;
import soul.cpp20.token;
import soul.cpp20.lexer;
import soul.cpp20.symbols;
import soul.cpp20.parser.attribute;
import soul.cpp20.parser.concepts;
import soul.cpp20.parser.declaration;
import soul.cpp20.parser.enums;
import soul.cpp20.parser.expression;
import soul.cpp20.parser.function;
import soul.cpp20.parser.identifier;
import soul.cpp20.parser.initialization;
import soul.cpp20.parser.punctuation;
import soul.cpp20.parser.templates;
import soul.cpp20.parser.type;

using namespace soul::cpp20::token;
using namespace soul::cpp20::lexer;
using namespace soul::cpp20::symbols;
using namespace soul::cpp20::parser::attribute;
using namespace soul::cpp20::parser::concepts;
using namespace soul::cpp20::parser::declaration;
using namespace soul::cpp20::parser::enums;
using namespace soul::cpp20::parser::expression;
using namespace soul::cpp20::parser::function;
using namespace soul::cpp20::parser::identifier;
using namespace soul::cpp20::parser::initialization;
using namespace soul::cpp20::parser::punctuation;
using namespace soul::cpp20::parser::templates;
using namespace soul::cpp20::parser::type;

namespace soul::cpp20::parser::classes {

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::ClassSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ClassSpecifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542209);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::ClassSpecifierNode> node = std::unique_ptr<soul::cpp20::ast::ClassSpecifierNode>();
    soul::ast::SourcePos lbPos = soul::ast::SourcePos();
    soul::ast::SourcePos rbPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> classHead;
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
                            soul::parser::Match match = ClassParser<Lexer>::ClassHead(lexer, context);
                            classHead.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                if (*lexer == LBRACE)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    lbPos = lexer.GetSourcePos(pos);
                                    node.reset(new soul::cpp20::ast::ClassSpecifierNode(sourcePos, classHead.release()));
                                    soul::cpp20::symbols::BeginClass(node.get(), context);
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
                        int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch9 = &match;
                        {
                            soul::parser::Match match = ClassParser<Lexer>::MemberSpecification(lexer, context, node.get());
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
            soul::cpp20::symbols::EndClass(context);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassSpecifier");
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::ClassHead(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ClassHead");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542210);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> classKey;
    std::unique_ptr<soul::cpp20::ast::Node> attributes;
    std::unique_ptr<soul::cpp20::ast::Node> classHeadName;
    std::unique_ptr<soul::cpp20::ast::Node> classVirtSpecifier;
    std::unique_ptr<soul::cpp20::ast::Node> baseClause;
    std::unique_ptr<soul::cpp20::ast::Node> unnamed;
    std::unique_ptr<soul::cpp20::ast::Node> baseClause2;
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ClassParser<Lexer>::ClassKey(lexer);
                    classKey.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                        soul::parser::Match match = AttributeParser<Lexer>::AttributeSpecifierSeq(lexer, context);
                        attributes.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                        int64_t save = lexer.GetPos();
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
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch12 = &match;
                                    {
                                        soul::parser::Match match = ClassParser<Lexer>::ClassHeadName(lexer, context);
                                        classHeadName.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                        *parentMatch12 = match;
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
                                                soul::parser::Match match = ClassParser<Lexer>::ClassVirtSpecifier(lexer, context);
                                                classVirtSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match* parentMatch16 = &match;
                                        {
                                            soul::parser::Match match = ClassParser<Lexer>::BaseClause(lexer, context);
                                            baseClause.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                    return soul::parser::Match(true, new soul::cpp20::ast::ClassHeadNode(sourcePos, classKey.release(), classHeadName.release(), classVirtSpecifier.release(), baseClause.release(), attributes.release()));
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch19 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch20 = &match;
                                        {
                                            soul::parser::Match match = IdentifierParser<Lexer>::Unnamed(lexer);
                                            unnamed.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            *parentMatch20 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch21 = &match;
                                            {
                                                soul::parser::Match match(true);
                                                int64_t save = lexer.GetPos();
                                                soul::parser::Match* parentMatch22 = &match;
                                                {
                                                    soul::parser::Match match = ClassParser<Lexer>::BaseClause(lexer, context);
                                                    baseClause2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                            #endif SOUL_PARSER_DEBUG_SUPPORT
                                            return soul::parser::Match(true, new soul::cpp20::ast::ClassHeadNode(sourcePos, classKey.release(), unnamed.release(), nullptr, baseClause2.release(), attributes.release()));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::ClassKey(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ClassKey");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542211);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case CLASS:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::cpp20::ast::ClassNode(lexer.GetSourcePos(pos)));
                }
            }
            break;
        }
        case STRUCT:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::cpp20::ast::StructNode(lexer.GetSourcePos(pos)));
                }
            }
            break;
        }
        case UNION:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassKey");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, new soul::cpp20::ast::UnionNode(lexer.GetSourcePos(pos)));
                }
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::ClassHeadName(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ClassHeadName");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542212);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> nns;
    std::unique_ptr<soul::cpp20::ast::Node> className;
    std::unique_ptr<soul::cpp20::ast::Node> className2;
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
                soul::parser::Match match = IdentifierParser<Lexer>::NestedNameSpecifier(lexer, context);
                nns.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ClassParser<Lexer>::ClassName(lexer, context);
                    className.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassHeadName");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
                            return soul::parser::Match(true, new soul::cpp20::ast::QualifiedIdNode(sourcePos, nns.release(), className.release()));
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
                    soul::parser::Match match = ClassParser<Lexer>::ClassName(lexer, context);
                    className2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassHeadName");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::ClassName(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ClassName");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542213);
    std::unique_ptr<soul::cpp20::ast::Node> templateId;
    std::unique_ptr<soul::cpp20::ast::Node> identifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = TemplateParser<Lexer>::SimpleTemplateId(lexer, context);
            templateId.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassName");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer, context);
                    identifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassName");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::ClassVirtSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ClassVirtSpecifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542214);
    std::unique_ptr<soul::cpp20::ast::Node> finalKw;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = ClassParser<Lexer>::FinalKeyword(lexer, context);
        finalKw.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassVirtSpecifier");
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::VirtSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "VirtSpecifierSeq");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542215);
    std::unique_ptr<soul::cpp20::ast::Node> node = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> first;
    std::unique_ptr<soul::cpp20::ast::Node> next;
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
                    soul::parser::Match match = ClassParser<Lexer>::VirtSpecifier(lexer, context);
                    first.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        node.reset(new soul::cpp20::ast::VirtSpecifierSequenceNode(lexer.GetSourcePos(pos)));
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
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = ClassParser<Lexer>::VirtSpecifier(lexer, context);
                                        next.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::VirtSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "VirtSpecifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542216);
    std::unique_ptr<soul::cpp20::ast::Node> overrideKw;
    std::unique_ptr<soul::cpp20::ast::Node> finalKw;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = ClassParser<Lexer>::OverrideKeyword(lexer, context);
            overrideKw.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VirtSpecifier");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ClassParser<Lexer>::FinalKeyword(lexer, context);
                    finalKw.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "VirtSpecifier");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::OverrideKeyword(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "OverrideKeyword");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542217);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
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
                int64_t pos = lexer.GetPos();
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::OverrideNode(sourcePos));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::FinalKeyword(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FinalKeyword");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542218);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
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
                int64_t pos = lexer.GetPos();
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::FinalNode(sourcePos));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::BaseClause(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BaseClause");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542219);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> baseSpecifierList;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
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
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = ClassParser<Lexer>::BaseSpecifierList(lexer, context);
                baseSpecifierList.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BaseClause");
                        #endif SOUL_PARSER_DEBUG_SUPPORT
                        return soul::parser::Match(true, new soul::cpp20::ast::BaseClauseNode(sourcePos, baseSpecifierList.release()));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::BaseSpecifierList(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BaseSpecifierList");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542220);
    std::unique_ptr<soul::cpp20::ast::Node> node = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> first;
    std::unique_ptr<soul::cpp20::ast::Node> comma;
    std::unique_ptr<soul::cpp20::ast::Node> next;
    std::unique_ptr<soul::cpp20::ast::Node> ellipsis;
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
                        soul::parser::Match match = ClassParser<Lexer>::BaseSpecifier(lexer, context);
                        first.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            node.reset(new soul::cpp20::ast::BaseSpecifierListNode(lexer.GetSourcePos(pos)));
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
                                int64_t save = lexer.GetPos();
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
                                                soul::parser::Match match = PunctuationParser<Lexer>::Comma(lexer);
                                                comma.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ClassParser<Lexer>::BaseSpecifier(lexer, context);
                                                    next.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                    int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch13 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch15 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = PunctuationParser<Lexer>::Ellipsis(lexer);
                                ellipsis.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::BaseSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BaseSpecifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542221);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> accessSpecifierNode = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> virtualSpecifier = std::unique_ptr<soul::cpp20::ast::Node>();
    bool virtualFirst = bool();
    std::unique_ptr<soul::cpp20::ast::Node> attributes;
    std::unique_ptr<soul::cpp20::ast::Node> virt;
    std::unique_ptr<soul::cpp20::ast::Node> access;
    std::unique_ptr<soul::cpp20::ast::Node> access2;
    std::unique_ptr<soul::cpp20::ast::Node> virt2;
    std::unique_ptr<soul::cpp20::ast::Node> classOrDeclType;
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
                                int64_t save = lexer.GetPos();
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = ClassParser<Lexer>::VirtualSpecifier(lexer);
                                            virt.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                                        soul::parser::Match match = ClassParser<Lexer>::AccessSpecifier(lexer);
                                                        access.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                    *parentMatch10 = match;
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
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ClassParser<Lexer>::AccessSpecifier(lexer);
                                                    access2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                        accessSpecifierNode.reset(access2.release());
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
                                                                int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = ClassParser<Lexer>::VirtualSpecifier(lexer);
                                                                virt2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                    virtualSpecifier.reset(virt2.release());
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
                                                *parentMatch18 = match;
                                            }
                                            *parentMatch17 = match;
                                        }
                                        *parentMatch10 = match;
                                    }
                                }
                                *parentMatch9 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch24 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(true);
                                        *parentMatch24 = match;
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
                soul::parser::Match* parentMatch25 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch26 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ClassParser<Lexer>::ClassOrDeclType(lexer, context);
                        classOrDeclType.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                        }
                        *parentMatch26 = match;
                    }
                    *parentMatch25 = match;
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::BaseSpecifierNode(sourcePos, classOrDeclType.release(), accessSpecifierNode.release(), virtualSpecifier.release(), attributes.release(), virtualFirst));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::ClassOrDeclType(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ClassOrDeclType");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542222);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos tmpPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> nns;
    std::unique_ptr<soul::cpp20::ast::Node> tmp;
    std::unique_ptr<soul::cpp20::ast::Node> simpleTemplateId;
    std::unique_ptr<soul::cpp20::ast::Node> nns2;
    std::unique_ptr<soul::cpp20::ast::Node> id;
    std::unique_ptr<soul::cpp20::ast::Node> typeName2;
    std::unique_ptr<soul::cpp20::ast::Node> declTypeSpecifier;
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = IdentifierParser<Lexer>::NestedNameSpecifier(lexer, context);
                            nns.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                soul::parser::Match match = TemplateParser<Lexer>::Template(lexer);
                                tmp.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = TemplateParser<Lexer>::SimpleTemplateId(lexer, context);
                            simpleTemplateId.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassOrDeclType");
                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                    return soul::parser::Match(true, new soul::cpp20::ast::QualifiedIdNode(sourcePos, nns.release(), new soul::cpp20::ast::PrefixNode(tmpPos, tmp.release(), simpleTemplateId.release())));
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
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = IdentifierParser<Lexer>::NestedNameSpecifier(lexer, context);
                                nns2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer, context);
                                    id.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassOrDeclType");
                                            #endif SOUL_PARSER_DEBUG_SUPPORT
                                            return soul::parser::Match(true, new soul::cpp20::ast::QualifiedIdNode(sourcePos, nns2.release(), id.release()));
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = TypeParser<Lexer>::TypeName(lexer, context);
                        typeName2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassOrDeclType");
                                #endif SOUL_PARSER_DEBUG_SUPPORT
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = TypeParser<Lexer>::DeclTypeSpecifier(lexer, context);
                    declTypeSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClassOrDeclType");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberSpecification(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberSpecification");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542223);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos colonPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> accessSpecifier;
    std::unique_ptr<soul::cpp20::ast::Node> memberDeclaration1;
    std::unique_ptr<soul::cpp20::ast::Node> memberDeclaration2;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = ClassParser<Lexer>::AccessSpecifier(lexer);
                            accessSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                if (*lexer == COLON)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    colonPos = lexer.GetSourcePos(pos);
                                    container->AddNode(new soul::cpp20::ast::BeginAccessGroupNode(sourcePos, accessSpecifier.release(), colonPos));
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch6 = match;
                        }
                        *parentMatch4 = match;
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
                                soul::parser::Match match = ClassParser<Lexer>::MemberDeclaration(lexer, context);
                                memberDeclaration1.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    container->AddNode(memberDeclaration1.release());
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
                            soul::parser::Match match = ClassParser<Lexer>::MemberDeclaration(lexer, context);
                            memberDeclaration2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                container->AddNode(memberDeclaration2.release());
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
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(true);
        soul::parser::Match* parentMatch12 = &match;
        while (true)
        {
            int64_t save = lexer.GetPos();
            {
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch17 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ClassParser<Lexer>::AccessSpecifier(lexer);
                                    accessSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                        if (*lexer == COLON)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            colonPos = lexer.GetSourcePos(pos);
                                            container->AddNode(new soul::cpp20::ast::BeginAccessGroupNode(sourcePos, accessSpecifier.release(), colonPos));
                                        }
                                        *parentMatch19 = match;
                                    }
                                    *parentMatch18 = match;
                                }
                                *parentMatch16 = match;
                            }
                            *parentMatch15 = match;
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
                                        soul::parser::Match match = ClassParser<Lexer>::MemberDeclaration(lexer, context);
                                        memberDeclaration1.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            container->AddNode(memberDeclaration1.release());
                                        }
                                        *parentMatch21 = match;
                                    }
                                    *parentMatch20 = match;
                                }
                                *parentMatch15 = match;
                            }
                        }
                        *parentMatch14 = match;
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
                                    soul::parser::Match match = ClassParser<Lexer>::MemberDeclaration(lexer, context);
                                    memberDeclaration2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        container->AddNode(memberDeclaration2.release());
                                    }
                                    *parentMatch23 = match;
                                }
                                *parentMatch22 = match;
                            }
                            *parentMatch14 = match;
                        }
                    }
                    *parentMatch13 = match;
                }
                if (match.hit)
                {
                    *parentMatch12 = match;
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberDeclaration");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542224);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> declSpecifiersNode = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> declaratorsNode = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> attributes;
    std::unique_ptr<soul::cpp20::ast::Node> declSpecifiers;
    std::unique_ptr<soul::cpp20::ast::Node> declarators;
    std::unique_ptr<soul::cpp20::ast::Node> semicolon;
    std::unique_ptr<soul::cpp20::ast::Node> memberFunctionDefinition;
    std::unique_ptr<soul::cpp20::ast::Node> usingDeclaration;
    std::unique_ptr<soul::cpp20::ast::Node> usingEnumDeclaration;
    std::unique_ptr<soul::cpp20::ast::Node> staticAssertDeclaration;
    std::unique_ptr<soul::cpp20::ast::Node> templateDeclaration;
    std::unique_ptr<soul::cpp20::ast::Node> explicitSpecialization;
    std::unique_ptr<soul::cpp20::ast::Node> deductionGuide;
    std::unique_ptr<soul::cpp20::ast::Node> aliasDeclaration;
    std::unique_ptr<soul::cpp20::ast::Node> opaqueEnumDeclaration;
    std::unique_ptr<soul::cpp20::ast::Node> emptyDeclaration;
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
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        soul::parser::Match match(true);
                                                        int64_t save = lexer.GetPos();
                                                        soul::parser::Match* parentMatch13 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch14 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch15 = &match;
                                                                {
                                                                    int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match = AttributeParser<Lexer>::AttributeSpecifierSeq(lexer, context);
                                                                    attributes.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        sourcePos = lexer.GetSourcePos(pos);
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
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch16 = &match;
                                                        {
                                                            soul::parser::Match match(true);
                                                            int64_t save = lexer.GetPos();
                                                            soul::parser::Match* parentMatch17 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch18 = &match;
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch19 = &match;
                                                                    {
                                                                        int64_t pos = lexer.GetPos();
                                                                        soul::parser::Match match = ClassParser<Lexer>::MemberDeclSpecifiers(lexer, context);
                                                                        declSpecifiers.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                        if (match.hit)
                                                                        {
                                                                            if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                            declSpecifiersNode.reset(declSpecifiers.release());
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
                                                        *parentMatch12 = match;
                                                    }
                                                    *parentMatch11 = match;
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
                                                                    int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match = ClassParser<Lexer>::MemberDeclaratorList(lexer, context);
                                                                    declarators.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                        declaratorsNode.reset(declarators.release());
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
                                                    *parentMatch11 = match;
                                                }
                                                *parentMatch10 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch24 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch25 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        bool pass = true;
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch26 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch27 = &match;
                                                            {
                                                                int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = PunctuationParser<Lexer>::Semicolon(lexer);
                                                                semicolon.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                                                }
                                                                *parentMatch27 = match;
                                                            }
                                                            *parentMatch26 = match;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            if (!declSpecifiersNode && !declaratorsNode) pass = false;
                                                            else
                                                            {
                                                                soul::cpp20::ast::MemberDeclarationNode *memberDeclarationNode = new soul::cpp20::ast::MemberDeclarationNode(sourcePos, attributes.release(), declSpecifiersNode.release(), declaratorsNode.release(), semicolon.release());
                                                                soul::cpp20::symbols::ProcessMemberDeclaration(memberDeclarationNode, context);
                                                                {
                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                                                    return soul::parser::Match(true, memberDeclarationNode);
                                                                }
                                                            }
                                                        }
                                                        if (match.hit && !pass)
                                                        {
                                                            match = soul::parser::Match(false);
                                                        }
                                                        *parentMatch25 = match;
                                                    }
                                                    *parentMatch24 = match;
                                                }
                                                *parentMatch10 = match;
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
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = ClassParser<Lexer>::MemberFunctionDefinition(lexer, context);
                                                        memberFunctionDefinition.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            {
                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                                #endif SOUL_PARSER_DEBUG_SUPPORT
                                                                return soul::parser::Match(true, memberFunctionDefinition.release());
                                                            }
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
                                            soul::parser::Match* parentMatch30 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch31 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = DeclarationParser<Lexer>::UsingDeclaration(lexer, context);
                                                    usingDeclaration.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        {
                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
                                                            return soul::parser::Match(true, usingDeclaration.release());
                                                        }
                                                    }
                                                    *parentMatch31 = match;
                                                }
                                                *parentMatch30 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                    }
                                    *parentMatch7 = match;
                                    if (!match.hit)
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch32 = &match;
                                        lexer.SetPos(save);
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch33 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = DeclarationParser<Lexer>::UsingEnumDeclaration(lexer, context);
                                                usingEnumDeclaration.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                if (match.hit)
                                                {
                                                    {
                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                        #endif SOUL_PARSER_DEBUG_SUPPORT
                                                        return soul::parser::Match(true, usingEnumDeclaration.release());
                                                    }
                                                }
                                                *parentMatch33 = match;
                                            }
                                            *parentMatch32 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                }
                                *parentMatch6 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch34 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch35 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = DeclarationParser<Lexer>::StaticAssertDeclaration(lexer, context);
                                            staticAssertDeclaration.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                                    return soul::parser::Match(true, staticAssertDeclaration.release());
                                                }
                                            }
                                            *parentMatch35 = match;
                                        }
                                        *parentMatch34 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
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
                                        soul::parser::Match match = ClassParser<Lexer>::MemberTemplateDeclaration(lexer, context);
                                        templateDeclaration.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                                #endif SOUL_PARSER_DEBUG_SUPPORT
                                                return soul::parser::Match(true, templateDeclaration.release());
                                            }
                                        }
                                        *parentMatch37 = match;
                                    }
                                    *parentMatch36 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
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
                                    soul::parser::Match match = TemplateParser<Lexer>::ExplicitSpecialization(lexer, context);
                                    explicitSpecialization.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                            #endif SOUL_PARSER_DEBUG_SUPPORT
                                            return soul::parser::Match(true, explicitSpecialization.release());
                                        }
                                    }
                                    *parentMatch39 = match;
                                }
                                *parentMatch38 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch40 = &match;
                        lexer.SetPos(save);
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch41 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = TemplateParser<Lexer>::DeductionGuide(lexer, context);
                                deductionGuide.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    {
                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                        #endif SOUL_PARSER_DEBUG_SUPPORT
                                        return soul::parser::Match(true, deductionGuide.release());
                                    }
                                }
                                *parentMatch41 = match;
                            }
                            *parentMatch40 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
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
                            soul::parser::Match match = DeclarationParser<Lexer>::AliasDeclaration(lexer, context);
                            aliasDeclaration.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                    return soul::parser::Match(true, aliasDeclaration.release());
                                }
                            }
                            *parentMatch43 = match;
                        }
                        *parentMatch42 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
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
                        soul::parser::Match match = EnumParser<Lexer>::OpaqueEnumDeclaration(lexer, context);
                        opaqueEnumDeclaration.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                                #endif SOUL_PARSER_DEBUG_SUPPORT
                                return soul::parser::Match(true, opaqueEnumDeclaration.release());
                            }
                        }
                        *parentMatch45 = match;
                    }
                    *parentMatch44 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch46 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch47 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = DeclarationParser<Lexer>::EmptyDeclaration(lexer);
                    emptyDeclaration.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclaration");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
                            return soul::parser::Match(true, emptyDeclaration.release());
                        }
                    }
                    *parentMatch47 = match;
                }
                *parentMatch46 = match;
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberDeclSpecifiers(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberDeclSpecifiers");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542225);
    std::unique_ptr<soul::cpp20::ast::Node> declSpecifiers;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = DeclarationParser<Lexer>::DeclSpecifierSeq(lexer, context);
        declSpecifiers.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclSpecifiers");
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberFunctionDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberFunctionDefinition");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542226);
    std::unique_ptr<soul::cpp20::ast::Node> functionDefinition;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = FunctionParser<Lexer>::FunctionDefinition(lexer, context);
        functionDefinition.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberFunctionDefinition");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, functionDefinition.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberFunctionDefinition");
        else soul::lexer::WriteFailureToLog(lexer, "MemberFunctionDefinition");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberTemplateDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberTemplateDeclaration");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542227);
    std::unique_ptr<soul::cpp20::ast::Node> templateDeclaration;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match = TemplateParser<Lexer>::TemplateDeclaration(lexer, context);
        templateDeclaration.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberTemplateDeclaration");
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberDeclaratorList(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberDeclaratorList");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542228);
    std::unique_ptr<soul::cpp20::ast::Node> node = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> first;
    std::unique_ptr<soul::cpp20::ast::Node> comma;
    std::unique_ptr<soul::cpp20::ast::Node> next;
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
                    soul::parser::Match match = ClassParser<Lexer>::MemberDeclarator(lexer, context);
                    first.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        node.reset(new soul::cpp20::ast::MemberDeclaratorListNode(lexer.GetSourcePos(pos)));
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
                                            soul::parser::Match match = PunctuationParser<Lexer>::Comma(lexer);
                                            comma.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = ClassParser<Lexer>::MemberDeclarator(lexer, context);
                                                next.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberDeclarator");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542229);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::TrailingQualifiersNode> trailingQualifiersNode = std::unique_ptr<soul::cpp20::ast::TrailingQualifiersNode>();
    std::unique_ptr<soul::cpp20::ast::Node> declarator;
    std::unique_ptr<soul::cpp20::ast::Node> requiresClause;
    std::unique_ptr<soul::cpp20::ast::Node> initializer;
    std::unique_ptr<soul::cpp20::ast::Node> virtSpecifierSeq;
    std::unique_ptr<soul::cpp20::ast::Node> pureSpecifier;
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
                            soul::parser::Match match = DeclarationParser<Lexer>::Declarator(lexer, context);
                            declarator.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                    int64_t save = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = ConceptParser<Lexer>::RequiresClause(lexer, context);
                                            requiresClause.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarator");
                                                    #endif SOUL_PARSER_DEBUG_SUPPORT
                                                    return soul::parser::Match(true, new soul::cpp20::ast::InitDeclaratorNode(sourcePos, declarator.release(), requiresClause.release()));
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
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = InitializationParser<Lexer>::BraceOrEqualInitializer(lexer, context);
                                                    initializer.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        {
                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarator");
                                                            #endif SOUL_PARSER_DEBUG_SUPPORT
                                                            return soul::parser::Match(true, new soul::cpp20::ast::InitDeclaratorNode(sourcePos, declarator.release(), initializer.release()));
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
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match(true);
                                                if (match.hit)
                                                {
                                                    trailingQualifiersNode.reset(new soul::cpp20::ast::TrailingQualifiersNode(sourcePos, declarator.release()));
                                                }
                                                *parentMatch14 = match;
                                            }
                                            *parentMatch13 = match;
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = ClassParser<Lexer>::VirtSpecifierSeq(lexer, context);
                                    virtSpecifierSeq.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        trailingQualifiersNode->AddNode(virtSpecifierSeq.release());
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
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch21 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch22 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = ClassParser<Lexer>::PureSpecifier(lexer);
                                pureSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    trailingQualifiersNode->AddNode(pureSpecifier.release());
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
                    #endif SOUL_PARSER_DEBUG_SUPPORT
                    return soul::parser::Match(true, trailingQualifiersNode->ReleaseSubject());
                }
            }
            else
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberDeclarator");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::CtorInitializer(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CtorInitializer");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542230);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> memberInitializerList;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
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
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = ClassParser<Lexer>::MemberInitializerList(lexer, context);
                memberInitializerList.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializer");
                        #endif SOUL_PARSER_DEBUG_SUPPORT
                        return soul::parser::Match(true, new soul::cpp20::ast::ConstructorInitializerNode(sourcePos, memberInitializerList.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CtorInitializer");
        else soul::lexer::WriteFailureToLog(lexer, "CtorInitializer");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberInitializerList(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberInitializerList");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542231);
    std::unique_ptr<soul::cpp20::ast::Node> node = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> first;
    std::unique_ptr<soul::cpp20::ast::Node> comma;
    std::unique_ptr<soul::cpp20::ast::Node> next;
    std::unique_ptr<soul::cpp20::ast::Node> ellipsis;
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
                        soul::parser::Match match = ClassParser<Lexer>::MemberInitializer(lexer, context);
                        first.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            node.reset(new soul::cpp20::ast::MemberInitializerListNode(lexer.GetSourcePos(pos)));
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
                                int64_t save = lexer.GetPos();
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
                                                soul::parser::Match match = PunctuationParser<Lexer>::Comma(lexer);
                                                comma.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = ClassParser<Lexer>::MemberInitializer(lexer, context);
                                                    next.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                    int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch13 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch15 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = PunctuationParser<Lexer>::Ellipsis(lexer);
                                ellipsis.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberInitializer(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberInitializer");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542232);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::ExpressionListNode> exprListNode = std::unique_ptr<soul::cpp20::ast::ExpressionListNode>();
    std::unique_ptr<soul::cpp20::ast::Node> node = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> id;
    std::unique_ptr<soul::cpp20::ast::Node> bracedInitList;
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
                    soul::parser::Match match = ClassParser<Lexer>::MemberInitializerId(lexer, context);
                    id.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                                            exprListNode.reset(new soul::cpp20::ast::ExpressionListNode(sourcePos));
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
                                        int64_t save = lexer.GetPos();
                                        soul::parser::Match* parentMatch11 = &match;
                                        {
                                            soul::parser::Match match = ExpressionParser<Lexer>::ExpressionList(lexer, context, exprListNode.get());
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
                                        int64_t pos = lexer.GetPos();
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
                            *parentMatch6 = match;
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
                                        soul::parser::Match match = InitializationParser<Lexer>::BracedInitList(lexer, context);
                                        bracedInitList.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            node.reset(bracedInitList.release());
                                        }
                                        *parentMatch15 = match;
                                    }
                                    *parentMatch14 = match;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializer");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::MemberInitializerNode(sourcePos, id.release(), node.release()));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::MemberInitializerId(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MemberInitializerId");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542233);
    std::unique_ptr<soul::cpp20::ast::Node> classOrDeclType;
    std::unique_ptr<soul::cpp20::ast::Node> identifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = ClassParser<Lexer>::ClassOrDeclType(lexer, context);
            classOrDeclType.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializerId");
                    #endif SOUL_PARSER_DEBUG_SUPPORT
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer, context);
                    identifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MemberInitializerId");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::PureSpecifier(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PureSpecifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542234);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos zeroPos = soul::ast::SourcePos();
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
                        int64_t pos = lexer.GetPos();
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::PureSpecifierNode(sourcePos, zeroPos));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::AccessSpecifier(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AccessSpecifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542235);
    std::unique_ptr<soul::cpp20::ast::Node> privat;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t save = lexer.GetPos();
        int64_t pos = lexer.GetPos();
        switch (*lexer)
        {
            case PUBLIC:
            {
                ++lexer;
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AccessSpecifier");
                        #endif SOUL_PARSER_DEBUG_SUPPORT
                        return soul::parser::Match(true, new soul::cpp20::ast::PublicNode(lexer.GetSourcePos(pos)));
                    }
                }
                break;
            }
            case PROTECTED:
            {
                ++lexer;
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AccessSpecifier");
                        #endif SOUL_PARSER_DEBUG_SUPPORT
                        return soul::parser::Match(true, new soul::cpp20::ast::ProtectedNode(lexer.GetSourcePos(pos)));
                    }
                }
                break;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch2 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = ClassParser<Lexer>::Private(lexer);
                    privat.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AccessSpecifier");
                            #endif SOUL_PARSER_DEBUG_SUPPORT
                            return soul::parser::Match(true, privat.release());
                        }
                    }
                    *parentMatch2 = match;
                }
                *parentMatch1 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AccessSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "AccessSpecifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::Private(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Private");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542236);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::PrivateNode(lexer.GetSourcePos(pos)));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match ClassParser<Lexer>::VirtualSpecifier(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "VirtualSpecifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 8201428699560542237);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
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
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new soul::cpp20::ast::VirtualNode(lexer.GetSourcePos(pos)));
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
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct ClassParser<soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>>;

} // namespace soul::cpp20::parser::classes
