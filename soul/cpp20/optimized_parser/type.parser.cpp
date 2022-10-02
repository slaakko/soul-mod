
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_parser/type.parser' using soul parser generator spg version 4.1.0

module soul.cpp20.parser.type;

import util;
import soul.ast.spg;
import soul.cpp20.ast;
import soul.cpp20.symbols;
import soul.cpp20.token;
import soul.cpp20.lexer;
import soul.cpp20.parser.attribute;
import soul.cpp20.parser.classes;
import soul.cpp20.parser.concepts;
import soul.cpp20.parser.declaration;
import soul.cpp20.parser.enums;
import soul.cpp20.parser.expression;
import soul.cpp20.parser.function;
import soul.cpp20.parser.guard;
import soul.cpp20.parser.identifier;
import soul.cpp20.parser.simple.type;
import soul.cpp20.parser.templates;

using namespace soul::cpp20::ast;
using namespace soul::cpp20::symbols;
using namespace soul::cpp20::token;
using namespace soul::cpp20::lexer;
using namespace soul::cpp20::parser::attribute;
using namespace soul::cpp20::parser::classes;
using namespace soul::cpp20::parser::concepts;
using namespace soul::cpp20::parser::declaration;
using namespace soul::cpp20::parser::enums;
using namespace soul::cpp20::parser::expression;
using namespace soul::cpp20::parser::function;
using namespace soul::cpp20::parser::guard;
using namespace soul::cpp20::parser::identifier;
using namespace soul::cpp20::parser::simple::type;
using namespace soul::cpp20::parser::templates;

namespace soul::cpp20::parser::type {

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::TypeSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeSpecifierSeq");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340353);
    std::unique_ptr<soul::cpp20::ast::Node> sequence = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> first;
    std::unique_ptr<soul::cpp20::ast::Node> next;
    std::unique_ptr<soul::cpp20::ast::Node> attributes;
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
                        soul::parser::Match match = TypeParser<Lexer>::TypeSpecifier(lexer, context);
                        first.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            sequence.reset(new soul::cpp20::ast::TypeSpecifierSequenceNode(lexer.GetSourcePos(pos)));
                            sequence->AddNode(first.release());
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = TypeParser<Lexer>::TypeSpecifier(lexer, context);
                                            next.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                sequence->AddNode(next.release());
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
                                soul::parser::Match match = AttributeParser<Lexer>::AttributeSpecifierSeq(lexer, context);
                                attributes.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    sequence->AddNode(attributes.release());
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierSeq");
                #endif
                return soul::parser::Match(true, sequence.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierSeq");
        else soul::lexer::WriteFailureToLog(lexer, "TypeSpecifierSeq");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::TypeSpecifierSeqReset(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeSpecifierSeqReset");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340354);
    std::unique_ptr<soul::cpp20::ast::Node> typeSpecifierSeq;
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
                context->PushResetFlag(soul::cpp20::symbols::ContextFlags::hasDefiningTypeSpecifier);
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
                soul::parser::Match match = TypeParser<Lexer>::TypeSpecifierSeq(lexer, context);
                typeSpecifierSeq.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    context->PopFlags();
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierSeqReset");
                        #endif
                        return soul::parser::Match(true, typeSpecifierSeq.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierSeqReset");
        else soul::lexer::WriteFailureToLog(lexer, "TypeSpecifierSeqReset");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::DefiningTypeId(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DefiningTypeId");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340355);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> definingTypeSpecifierSeq;
    std::unique_ptr<soul::cpp20::ast::Node> abstractDeclararator;
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
                    soul::parser::Match match = TypeParser<Lexer>::DefiningTypeSpecifierSeq(lexer, context);
                    definingTypeSpecifierSeq.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                        soul::parser::Match match = DeclarationParser<Lexer>::AbstractDeclarator(lexer, context);
                        abstractDeclararator.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeId");
                #endif
                return soul::parser::Match(true, new DefiningTypeIdNode(sourcePos, definingTypeSpecifierSeq.release(), abstractDeclararator.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeId");
        else soul::lexer::WriteFailureToLog(lexer, "DefiningTypeId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::DefiningTypeSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DefiningTypeSpecifierSeq");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340356);
    std::unique_ptr<soul::cpp20::ast::Node> node = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<Node> first;
    std::unique_ptr<Node> next;
    std::unique_ptr<soul::cpp20::ast::Node> attributes;
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
                        soul::parser::Match match = TypeParser<Lexer>::DefiningTypeSpecifierReset(lexer, context);
                        first.reset(static_cast<Node*>(match.value));
                        if (match.hit)
                        {
                            node.reset(new soul::cpp20::ast::DefiningTypeSpecifierSequenceNode(lexer.GetSourcePos(pos)));
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = TypeParser<Lexer>::DefiningTypeSpecifierReset(lexer, context);
                                            next.reset(static_cast<Node*>(match.value));
                                            if (match.hit)
                                            {
                                                node->AddNode(next.release());
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
                                soul::parser::Match match = AttributeParser<Lexer>::AttributeSpecifierSeq(lexer, context);
                                attributes.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                if (match.hit)
                                {
                                    node->AddNode(attributes.release());
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeSpecifierSeq");
                #endif
                return soul::parser::Match(true, node.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeSpecifierSeq");
        else soul::lexer::WriteFailureToLog(lexer, "DefiningTypeSpecifierSeq");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::DefiningTypeSpecifierReset(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DefiningTypeSpecifierReset");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340357);
    std::unique_ptr<soul::cpp20::ast::Node> definingTypeSpecifier;
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
                context->PushResetFlag(soul::cpp20::symbols::ContextFlags::hasDefiningTypeSpecifier);
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
                soul::parser::Match match = TypeParser<Lexer>::DefiningTypeSpecifier(lexer, context);
                definingTypeSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    context->PopFlags();
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeSpecifierReset");
                        #endif
                        return soul::parser::Match(true, definingTypeSpecifier.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeSpecifierReset");
        else soul::lexer::WriteFailureToLog(lexer, "DefiningTypeSpecifierReset");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::DefiningTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DefiningTypeSpecifier");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340358);
    std::unique_ptr<soul::cpp20::ast::Node> classSpecifier;
    std::unique_ptr<soul::cpp20::ast::Node> enumSpecifier;
    std::unique_ptr<soul::cpp20::ast::Node> typeSpecifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t save = lexer.GetPos();
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            switch (*lexer)
            {
                case CLASS:
                case STRUCT:
                case UNION:
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch3 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = ClassParser<Lexer>::ClassSpecifier(lexer, context);
                        classSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            context->SetFlag(soul::cpp20::symbols::ContextFlags::hasDefiningTypeSpecifier);
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeSpecifier");
                                #endif
                                return soul::parser::Match(true, classSpecifier.release());
                            }
                        }
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case ENUM:
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = EnumParser<Lexer>::EnumSpecifier(lexer, context);
                        enumSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            context->SetFlag(soul::cpp20::symbols::ContextFlags::hasDefiningTypeSpecifier);
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeSpecifier");
                                #endif
                                return soul::parser::Match(true, enumSpecifier.release());
                            }
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
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
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = TypeParser<Lexer>::TypeSpecifier(lexer, context);
                        typeSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeSpecifier");
                                #endif
                                return soul::parser::Match(true, typeSpecifier.release());
                            }
                        }
                        *parentMatch6 = match;
                    }
                    *parentMatch5 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DefiningTypeSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "DefiningTypeSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::TypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeSpecifier");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340359);
    std::unique_ptr<soul::cpp20::ast::Node> simpleTypeSpecifier;
    std::unique_ptr<soul::cpp20::ast::Node> elaboratedTypeSpecifier;
    std::unique_ptr<soul::cpp20::ast::Node> typenameSpecifier;
    std::unique_ptr<soul::cpp20::ast::Node> cvQualifier;
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
                    soul::parser::Match match = TypeParser<Lexer>::SimpleTypeSpecifier(lexer, context);
                    simpleTypeSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        context->SetFlag(soul::cpp20::symbols::ContextFlags::hasDefiningTypeSpecifier);
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifier");
                            #endif
                            return soul::parser::Match(true, simpleTypeSpecifier.release());
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
                            soul::parser::Match match = TypeParser<Lexer>::ElaboratedTypeSpecifier(lexer, context);
                            elaboratedTypeSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                context->SetFlag(soul::cpp20::symbols::ContextFlags::hasDefiningTypeSpecifier);
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifier");
                                    #endif
                                    return soul::parser::Match(true, elaboratedTypeSpecifier.release());
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
                        soul::parser::Match match = TypeParser<Lexer>::TypenameSpecifier(lexer, context);
                        typenameSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                        if (match.hit)
                        {
                            context->SetFlag(soul::cpp20::symbols::ContextFlags::hasDefiningTypeSpecifier);
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifier");
                                #endif
                                return soul::parser::Match(true, typenameSpecifier.release());
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
                    soul::parser::Match match = DeclarationParser<Lexer>::CVQualifier(lexer);
                    cvQualifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifier");
                            #endif
                            return soul::parser::Match(true, cvQualifier.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "TypeSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::ElaboratedTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ElaboratedTypeSpecifier");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340360);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos nnsPos = soul::ast::SourcePos();
    soul::ast::SourcePos tmpPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> classKey;
    std::unique_ptr<soul::cpp20::ast::Node> attributes;
    std::unique_ptr<soul::cpp20::ast::Node> nns;
    std::unique_ptr<soul::cpp20::ast::Node> tmp;
    std::unique_ptr<soul::cpp20::ast::Node> simpleTemplateId;
    std::unique_ptr<soul::cpp20::ast::Node> simpleTemplateId2;
    std::unique_ptr<soul::cpp20::ast::Node> identifier;
    std::unique_ptr<soul::cpp20::ast::Node> simpleTemplateId3;
    std::unique_ptr<soul::cpp20::ast::Node> identifier2;
    std::unique_ptr<soul::cpp20::ast::Node> elaboratedEnumSpecifier;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case CLASS:
        case STRUCT:
        case UNION:
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
                                int64_t save = lexer.GetPos();
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IdentifierParser<Lexer>::NestedNameSpecifier(lexer, context);
                                        nns.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            nnsPos = lexer.GetSourcePos(pos);
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
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch14 = &match;
                                            {
                                                int64_t save = lexer.GetPos();
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch15 = &match;
                                                switch (*lexer)
                                                {
                                                    case TEMPLATE:
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch16 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch17 = &match;
                                                            {
                                                                int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = IdentifierParser<Lexer>::Template(lexer);
                                                                tmp.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    tmpPos = lexer.GetSourcePos(pos);
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
                                                                    soul::parser::Match match = TemplateParser<Lexer>::SimpleTemplateId(lexer, context);
                                                                    simpleTemplateId.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        soul::cpp20::ast::Node *node = new soul::cpp20::ast::ElaboratedTypeSpecifierNode(sourcePos, classKey.release(), new soul::cpp20::ast::QualifiedIdNode(nnsPos, nns.release(), new soul::cpp20::ast::PrefixNode(tmpPos, tmp.release(), simpleTemplateId.release())), attributes.release());
                                                                        soul::cpp20::symbols::AddForwardClassDeclaration(node, context);
                                                                        {
                                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElaboratedTypeSpecifier");
                                                                            #endif
                                                                            return soul::parser::Match(true, node);
                                                                        }
                                                                    }
                                                                    *parentMatch19 = match;
                                                                }
                                                                *parentMatch18 = match;
                                                            }
                                                            *parentMatch16 = match;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            *parentMatch15 = match;
                                                        }
                                                        break;
                                                    }
                                                    case ID:
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch20 = &match;
                                                        {
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = TemplateParser<Lexer>::SimpleTemplateId(lexer, context);
                                                            simpleTemplateId2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                soul::cpp20::ast::Node *node = new soul::cpp20::ast::ElaboratedTypeSpecifierNode(sourcePos, classKey.release(), new soul::cpp20::ast::QualifiedIdNode(nnsPos, nns.release(), simpleTemplateId2.release()), attributes.release());
                                                                soul::cpp20::symbols::AddForwardClassDeclaration(node, context);
                                                                {
                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElaboratedTypeSpecifier");
                                                                    #endif
                                                                    return soul::parser::Match(true, node);
                                                                }
                                                            }
                                                            *parentMatch20 = match;
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
                                                    soul::parser::Match* parentMatch21 = &match;
                                                    lexer.SetPos(save);
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch22 = &match;
                                                        {
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer, context);
                                                            identifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                soul::cpp20::ast::Node *node = new soul::cpp20::ast::ElaboratedTypeSpecifierNode(sourcePos, classKey.release(), new soul::cpp20::ast::QualifiedIdNode(nnsPos, nns.release(), identifier.release()), attributes.release());
                                                                soul::cpp20::symbols::AddForwardClassDeclaration(node, context);
                                                                {
                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElaboratedTypeSpecifier");
                                                                    #endif
                                                                    return soul::parser::Match(true, node);
                                                                }
                                                            }
                                                            *parentMatch22 = match;
                                                        }
                                                        *parentMatch21 = match;
                                                    }
                                                    *parentMatch14 = match;
                                                }
                                            }
                                            *parentMatch13 = match;
                                        }
                                        *parentMatch12 = match;
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                                if (!match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch23 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch24 = &match;
                                        {
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match = TemplateParser<Lexer>::SimpleTemplateId(lexer, context);
                                            simpleTemplateId3.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                            if (match.hit)
                                            {
                                                soul::cpp20::ast::Node *node = new soul::cpp20::ast::ElaboratedTypeSpecifierNode(sourcePos, classKey.release(), simpleTemplateId3.release(), attributes.release());
                                                soul::cpp20::symbols::AddForwardClassDeclaration(node, context);
                                                {
                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElaboratedTypeSpecifier");
                                                    #endif
                                                    return soul::parser::Match(true, node);
                                                }
                                            }
                                            *parentMatch24 = match;
                                        }
                                        *parentMatch23 = match;
                                    }
                                    *parentMatch9 = match;
                                }
                            }
                            *parentMatch8 = match;
                            if (!match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch25 = &match;
                                lexer.SetPos(save);
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch26 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer, context);
                                        identifier2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            soul::cpp20::ast::Node *node = new soul::cpp20::ast::ElaboratedTypeSpecifierNode(sourcePos, classKey.release(), identifier2.release(), attributes.release());
                                            soul::cpp20::symbols::AddForwardClassDeclaration(node, context);
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElaboratedTypeSpecifier");
                                                #endif
                                                return soul::parser::Match(true, node);
                                            }
                                        }
                                        *parentMatch26 = match;
                                    }
                                    *parentMatch25 = match;
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
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case ENUM:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch27 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = EnumParser<Lexer>::ElaboratedEnumSpecifier(lexer, context);
                elaboratedEnumSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElaboratedTypeSpecifier");
                        #endif
                        return soul::parser::Match(true, elaboratedEnumSpecifier.release());
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElaboratedTypeSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "ElaboratedTypeSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::SimpleTypeSpecifierReset(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SimpleTypeSpecifierReset");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340361);
    std::unique_ptr<soul::cpp20::ast::Node> simpleTypeSpecifier;
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
                context->PushResetFlag(soul::cpp20::symbols::ContextFlags::hasDefiningTypeSpecifier);
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
                soul::parser::Match match = TypeParser<Lexer>::SimpleTypeSpecifier(lexer, context);
                simpleTypeSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    context->PopFlags();
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifierReset");
                        #endif
                        return soul::parser::Match(true, simpleTypeSpecifier.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifierReset");
        else soul::lexer::WriteFailureToLog(lexer, "SimpleTypeSpecifierReset");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::SimpleTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SimpleTypeSpecifier");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340362);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos tmpPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> nns = std::unique_ptr<soul::cpp20::ast::Node>();
    bool isConstructorNameNode = bool();
    std::unique_ptr<soul::cpp20::ast::Node> simpleType;
    std::unique_ptr<soul::cpp20::ast::Node> nns1;
    std::unique_ptr<soul::cpp20::ast::Node> tmp;
    std::unique_ptr<soul::cpp20::ast::Node> simpleTemplateId;
    std::unique_ptr<soul::cpp20::ast::Node> nns2;
    std::unique_ptr<soul::cpp20::ast::Node> typeName;
    std::unique_ptr<soul::cpp20::ast::Node> typeName2;
    std::unique_ptr<soul::cpp20::ast::Node> declTypeSpecifier;
    std::unique_ptr<soul::cpp20::ast::Node> placeholderTypeSpecifier;
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
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = SimpleTypeParser<Lexer>::SimpleType(lexer);
                simpleType.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                        #endif
                        return soul::parser::Match(true, simpleType.release());
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
                        soul::parser::Match match = GuardParser<Lexer>::NotDefiningTypeSpecifierGuard(lexer, context);
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
                                                            soul::parser::Match* parentMatch14 = &match;
                                                            {
                                                                int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = IdentifierParser<Lexer>::NestedNameSpecifier(lexer, context);
                                                                nns1.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    nns.reset(nns1.release());
                                                                    sourcePos = lexer.GetSourcePos(pos);
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
                                                                    int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match = IdentifierParser<Lexer>::Template(lexer);
                                                                    tmp.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        tmpPos = lexer.GetSourcePos(pos);
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
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch18 = &match;
                                                            {
                                                                int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = TemplateParser<Lexer>::SimpleTemplateId(lexer, context);
                                                                simpleTemplateId.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    {
                                                                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                                        #endif
                                                                        return soul::parser::Match(true, new soul::cpp20::ast::QualifiedIdNode(sourcePos, nns.release(), new soul::cpp20::ast::PrefixNode(tmpPos, tmp.release(), simpleTemplateId.release())));
                                                                    }
                                                                }
                                                                *parentMatch18 = match;
                                                            }
                                                            *parentMatch17 = match;
                                                        }
                                                        *parentMatch12 = match;
                                                    }
                                                    *parentMatch11 = match;
                                                    if (!match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch19 = &match;
                                                        lexer.SetPos(save);
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch20 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch21 = &match;
                                                                {
                                                                    int64_t pos = lexer.GetPos();
                                                                    soul::parser::Match match = IdentifierParser<Lexer>::NestedNameSpecifier(lexer, context);
                                                                    nns2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        nns.reset(nns2.release());
                                                                        soul::cpp20::symbols::BeginScope(nns.get(), context);
                                                                        sourcePos = lexer.GetSourcePos(pos);
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
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch23 = &match;
                                                                    {
                                                                        int64_t pos = lexer.GetPos();
                                                                        bool pass = true;
                                                                        soul::parser::Match match = TypeParser<Lexer>::TypeName(lexer, context);
                                                                        typeName.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                        if (match.hit)
                                                                        {
                                                                            std::unique_ptr<soul::cpp20::ast::Node> typeNameNode;
                                                                            typeNameNode.reset(typeName.release());
                                                                            isConstructorNameNode = context->IsConstructorNameNode(typeNameNode.get());
                                                                            soul::cpp20::symbols::EndScope(context);
                                                                            if (isConstructorNameNode)
                                                                            {
                                                                                pass = false;
                                                                            }
                                                                            else
                                                                            {
                                                                                {
                                                                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                                                    #endif
                                                                                    return soul::parser::Match(true, new soul::cpp20::ast::QualifiedIdNode(sourcePos, nns.release(), typeNameNode.release()));
                                                                                }
                                                                            }
                                                                        }
                                                                        else
                                                                        {
                                                                            soul::cpp20::symbols::EndScope(context);
                                                                        }
                                                                        if (match.hit && !pass)
                                                                        {
                                                                            match = soul::parser::Match(false);
                                                                        }
                                                                        *parentMatch23 = match;
                                                                    }
                                                                    *parentMatch22 = match;
                                                                }
                                                                *parentMatch20 = match;
                                                            }
                                                            *parentMatch19 = match;
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
                                                            soul::parser::Match* parentMatch26 = &match;
                                                            {
                                                                int64_t pos = lexer.GetPos();
                                                                bool pass = true;
                                                                soul::parser::Match match(true);
                                                                if (match.hit)
                                                                {
                                                                    if (isConstructorNameNode) pass = false;
                                                                }
                                                                if (match.hit && !pass)
                                                                {
                                                                    match = soul::parser::Match(false);
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
                                                                    bool pass = true;
                                                                    soul::parser::Match match = TypeParser<Lexer>::TypeName(lexer, context);
                                                                    typeName2.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                                    if (match.hit)
                                                                    {
                                                                        std::unique_ptr<soul::cpp20::ast::Node> typeNameNode;
                                                                        typeNameNode.reset(typeName2.release());
                                                                        if (context->IsConstructorNameNode(typeNameNode.get()))
                                                                        {
                                                                            pass = false;
                                                                        }
                                                                        else
                                                                        {
                                                                            {
                                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                                                #endif
                                                                                return soul::parser::Match(true, typeNameNode.release());
                                                                            }
                                                                        }
                                                                    }
                                                                    if (match.hit && !pass)
                                                                    {
                                                                        match = soul::parser::Match(false);
                                                                    }
                                                                    *parentMatch28 = match;
                                                                }
                                                                *parentMatch27 = match;
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
                                                soul::parser::Match* parentMatch29 = &match;
                                                lexer.SetPos(save);
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch30 = &match;
                                                    {
                                                        int64_t pos = lexer.GetPos();
                                                        soul::parser::Match match = TypeParser<Lexer>::DeclTypeSpecifier(lexer, context);
                                                        declTypeSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            {
                                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                                #endif
                                                                return soul::parser::Match(true, declTypeSpecifier.release());
                                                            }
                                                        }
                                                        *parentMatch30 = match;
                                                    }
                                                    *parentMatch29 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                        }
                                        *parentMatch8 = match;
                                        if (!match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch31 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch32 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = TypeParser<Lexer>::PlaceholderTypeSpecifier(lexer, context);
                                                    placeholderTypeSpecifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        {
                                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                            #endif
                                                            return soul::parser::Match(true, placeholderTypeSpecifier.release());
                                                        }
                                                    }
                                                    *parentMatch32 = match;
                                                }
                                                *parentMatch31 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "SimpleTypeSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::TypeName(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeName");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340363);
    std::unique_ptr<soul::cpp20::ast::Node> templateId;
    std::unique_ptr<soul::cpp20::ast::Node> typeIdentifier;
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
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeName");
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
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = IdentifierParser<Lexer>::TypeIdentifier(lexer, context);
                    typeIdentifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeName");
                            #endif
                            return soul::parser::Match(true, typeIdentifier.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeName");
        else soul::lexer::WriteFailureToLog(lexer, "TypeName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::TypeId(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeId");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340364);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> typeSpecifiers;
    std::unique_ptr<soul::cpp20::ast::Node> abstractDeclarator;
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
                        soul::parser::Match match(true);
                        if (match.hit)
                        {
                            context->PushResetFlag(soul::cpp20::symbols::ContextFlags::hasDefiningTypeSpecifier);
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
                            soul::parser::Match match = TypeParser<Lexer>::TypeSpecifierSeq(lexer, context);
                            typeSpecifiers.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                            if (match.hit)
                            {
                                sourcePos = lexer.GetSourcePos(pos);
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
                soul::parser::Match* parentMatch7 = &match;
                {
                    soul::parser::Match match(true);
                    int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch8 = &match;
                    {
                        soul::parser::Match match = DeclarationParser<Lexer>::AbstractDeclarator(lexer, context);
                        abstractDeclarator.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            context->PopFlags();
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeId");
                #endif
                return soul::parser::Match(true, new soul::cpp20::ast::TypeIdNode(sourcePos, typeSpecifiers.release(), abstractDeclarator.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeId");
        else soul::lexer::WriteFailureToLog(lexer, "TypeId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::TypenameSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypenameSpecifier");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340365);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> templateNode = std::unique_ptr<soul::cpp20::ast::Node>();
    bool typenameSeen = bool();
    std::unique_ptr<soul::cpp20::ast::Node> leaf = std::unique_ptr<soul::cpp20::ast::Node>();
    std::unique_ptr<soul::cpp20::ast::Node> nns;
    std::unique_ptr<soul::cpp20::ast::Node> t;
    std::unique_ptr<soul::cpp20::ast::Node> simpleTemplateId;
    std::unique_ptr<soul::cpp20::ast::Node> identifier;
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
                            context->PushSetFlag(soul::cpp20::symbols::ContextFlags::assumeType);
                            typenameSeen = true;
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
                            soul::parser::Match match(true);
                            if (match.hit)
                            {
                                context->PushResetFlag(soul::cpp20::symbols::ContextFlags::assumeType);
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
                            context->PopFlags();
                        }
                        else
                        {
                            context->PopFlags();
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch11 = &match;
                    {
                        int64_t save = lexer.GetPos();
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
                                        soul::parser::Match match = IdentifierParser<Lexer>::Template(lexer);
                                        t.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                        if (match.hit)
                                        {
                                            templateNode.reset(t.release());
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch17 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = TemplateParser<Lexer>::SimpleTemplateId(lexer, context);
                                    simpleTemplateId.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        context->PopFlags();
                                        leaf.reset(simpleTemplateId.release());
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypenameSpecifier");
                                            #endif
                                            return soul::parser::Match(true, new soul::cpp20::ast::TypenameSpecifierNode(sourcePos, nns.release(), leaf.release(), templateNode.release()));
                                        }
                                    }
                                    *parentMatch17 = match;
                                }
                                *parentMatch16 = match;
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer, context);
                                    identifier.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        context->PopFlags();
                                        leaf.reset(identifier.release());
                                        {
                                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypenameSpecifier");
                                            #endif
                                            return soul::parser::Match(true, new soul::cpp20::ast::TypenameSpecifierNode(sourcePos, nns.release(), leaf.release(), nullptr));
                                        }
                                    }
                                    *parentMatch19 = match;
                                }
                                *parentMatch18 = match;
                            }
                            *parentMatch11 = match;
                        }
                    }
                    *parentMatch10 = match;
                }
                *parentMatch9 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                    bool pass = true;
                    soul::parser::Match match(true);
                    if (match.hit)
                    {
                        if (typenameSeen)
                        {
                            context->PopFlags();
                        }
                        pass = false;
                    }
                    if (match.hit && !pass)
                    {
                        match = soul::parser::Match(false);
                    }
                    *parentMatch21 = match;
                }
                *parentMatch20 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypenameSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "TypenameSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::DeclTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DeclTypeSpecifier");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340366);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> expr;
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
                            if (*lexer == DECLTYPE)
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
                        expr.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclTypeSpecifier");
                #endif
                return soul::parser::Match(true, new soul::cpp20::ast::DeclTypeSpecifierNode(sourcePos, expr.release(), lpPos, rpPos));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclTypeSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "DeclTypeSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match TypeParser<Lexer>::PlaceholderTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PlaceholderTypeSpecifier");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5708918577642340367);
    soul::ast::SourcePos sourcePos = soul::ast::SourcePos();
    soul::ast::SourcePos dtPos = soul::ast::SourcePos();
    soul::ast::SourcePos autoPos = soul::ast::SourcePos();
    soul::ast::SourcePos lpPos = soul::ast::SourcePos();
    soul::ast::SourcePos rpPos = soul::ast::SourcePos();
    std::unique_ptr<soul::cpp20::ast::Node> typeConstraint;
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
                            soul::parser::Match match = ConceptParser<Lexer>::TypeConstraint(lexer, context);
                            typeConstraint.reset(static_cast<soul::cpp20::ast::Node*>(match.value));
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch8 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == AUTO)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
                                autoPos = lexer.GetSourcePos(pos);
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PlaceholderTypeSpecifier");
                                    #endif
                                    return soul::parser::Match(true, new soul::cpp20::ast::PlaceholderTypeSpecifierNode(sourcePos, typeConstraint.release(), dtPos, autoPos, lpPos, rpPos));
                                }
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                *parentMatch2 = match;
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch11 = &match;
                        {
                            int64_t pos = lexer.GetPos();
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
                                                if (*lexer == DECLTYPE)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    dtPos = lexer.GetSourcePos(pos);
                                                    if (!sourcePos.IsValid()) sourcePos = lexer.GetSourcePos(pos);
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
                                                    if (*lexer == LPAREN)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        lpPos = lexer.GetSourcePos(pos);
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
                                                if (*lexer == AUTO)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    autoPos = lexer.GetSourcePos(pos);
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
                                            if (*lexer == RPAREN)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                rpPos = lexer.GetSourcePos(pos);
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
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PlaceholderTypeSpecifier");
                                    #endif
                                    return soul::parser::Match(true, new soul::cpp20::ast::PlaceholderTypeSpecifierNode(sourcePos, typeConstraint.release(), dtPos, autoPos, lpPos, rpPos));
                                }
                            }
                            *parentMatch11 = match;
                        }
                        *parentMatch10 = match;
                    }
                    *parentMatch9 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PlaceholderTypeSpecifier");
        else soul::lexer::WriteFailureToLog(lexer, "PlaceholderTypeSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct TypeParser<soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>>;

} // namespace soul::cpp20::parser::type
