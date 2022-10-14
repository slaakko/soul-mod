
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/intermediate/intermediate.parser' using soul parser generator spg version 4.1.0

module otava.intermediate.code.parser;

import util;
import soul.ast.spg;
import otava.intermediate.lexer;
import otava.intermediate.token;
import otava.intermediate.type;
import otava.intermediate.function;
import otava.intermediate.basic.block;
import otava.intermediate.metadata;
import otava.intermediate.data;
import otava.intermediate.instruction;

using namespace otava::intermediate::lexer;
using namespace otava::intermediate::token;
using namespace otava::intermediate::type;
using namespace otava::intermediate::function;
using namespace otava::intermediate::basic::block;
using namespace otava::intermediate::metadata;
using namespace otava::intermediate::data;
using namespace otava::intermediate::instruction;

namespace otava::intermediate::code::parser {

template<typename Lexer>
void IntermediateCodeParser<Lexer>::Parse(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    ++lexer;
    soul::parser::Match match = IntermediateCodeParser<Lexer>::IntermediateCodeFile(lexer, context);
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->DecIndent();
        lexer.Log()->WriteEndRule("parse");
    }
    #endif
    if (match.hit)
    {
        if (*lexer == soul::lexer::END_TOKEN)
        {
            return;
        }
        else
        {
            lexer.ThrowFarthestError();
        }
    }
    else
    {
        lexer.ThrowFarthestError();
    }
    return;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::IntermediateCodeFile(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IntermediateCodeFile");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589441);
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(true);
                            if (match.hit)
                            {
                                context->SetFilePath(lexer.FileName());
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
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::CompileUnitHeader(lexer, context);
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
                        soul::parser::Match match(true);
                        int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch8 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeDeclarations(lexer, context);
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::DataDefinitions(lexer, context);
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            {
                soul::parser::Match match(true);
                int64_t save = lexer.GetPos();
                soul::parser::Match* parentMatch12 = &match;
                {
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::FunctionDefinitions(lexer, context);
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
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Metadata(lexer, context);
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
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IntermediateCodeFile");
        else soul::lexer::WriteFailureToLog(lexer, "IntermediateCodeFile");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::CompileUnitHeader(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CompileUnitHeader");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589442);
    std::unique_ptr<soul::parser::Value<std::string>> cuid;
    std::unique_ptr<otava::intermediate::MetadataRef> mdref;
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
                        soul::parser::Match match(false);
                        if (*lexer == CU)
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
                            if (*lexer == LPAREN)
                            {
                                ++lexer;
                                match.hit = true;
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
                    soul::parser::Match* parentMatch6 = &match;
                    {
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::CompileUnitId(lexer);
                        cuid.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                        *parentMatch6 = match;
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
                    if (*lexer == COMMA)
                    {
                        ++lexer;
                        match.hit = true;
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
            soul::parser::Match* parentMatch8 = &match;
            {
                soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataRef(lexer, context);
                mdref.reset(static_cast<otava::intermediate::MetadataRef*>(match.value));
                *parentMatch8 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                    context->SetCompileUnitInfo(cuid->value, mdref.release());
                }
                *parentMatch10 = match;
            }
            *parentMatch9 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompileUnitHeader");
        else soul::lexer::WriteFailureToLog(lexer, "CompileUnitHeader");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::CompileUnitId(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "CompileUnitId");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589443);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case HEXNUM:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == HEXNUM)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompileUnitId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<std::string>(util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        case NUMBER:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompileUnitId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<std::string>(util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        case ID:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
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
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompileUnitId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<std::string>(util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CompileUnitId");
        else soul::lexer::WriteFailureToLog(lexer, "CompileUnitId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::TypeDeclarations(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeDeclarations");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589444);
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
                if (*lexer == TYPES)
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
                    soul::parser::Match match(false);
                    if (*lexer == LBRACE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
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
                soul::parser::Match match(true);
                soul::parser::Match* parentMatch5 = &match;
                {
                    while (true)
                    {
                        int64_t save = lexer.GetPos();
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeDeclaration(lexer, context);
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
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                    context->ResolveTypes();
                }
                *parentMatch7 = match;
            }
            *parentMatch6 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeDeclarations");
        else soul::lexer::WriteFailureToLog(lexer, "TypeDeclarations");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::TypeDeclaration(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeDeclaration");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589445);
    int32_t tid = int32_t();
    std::unique_ptr<soul::parser::Value<int32_t>> typeId;
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeId(lexer);
                    typeId.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
                    if (match.hit)
                    {
                        tid = typeId->value;
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
                    if (*lexer == ASSIGN)
                    {
                        ++lexer;
                        match.hit = true;
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
            soul::parser::Match* parentMatch5 = &match;
            {
                soul::parser::Match match(false);
                if (*lexer == TYPE)
                {
                    ++lexer;
                    match.hit = true;
                }
                *parentMatch5 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                switch (*lexer)
                {
                    case LBRACE:
                    {
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::StructureType(lexer, context, tid);
                        if (match.hit)
                        {
                            *parentMatch8 = match;
                        }
                        break;
                    }
                    case LBRACKET:
                    {
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::ArrayType(lexer, context, tid);
                        if (match.hit)
                        {
                            *parentMatch8 = match;
                        }
                        break;
                    }
                    case FUNCTION:
                    {
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::FunctionType(lexer, context, tid);
                        if (match.hit)
                        {
                            *parentMatch8 = match;
                        }
                        break;
                    }
                }
                *parentMatch7 = match;
            }
            *parentMatch6 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeDeclaration");
        else soul::lexer::WriteFailureToLog(lexer, "TypeDeclaration");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::TypeId(Lexer& lexer)
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
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589446);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
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
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeId");
                    #endif
                    return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::MakeUserTypeId(util::ToUtf8(lexer.GetToken(pos).ToString()))));
                }
            }
            *parentMatch1 = match;
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
soul::parser::Match IntermediateCodeParser<Lexer>::FundamentalTypeId(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FundamentalTypeId");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589447);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case VOID:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == VOID)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::voidTypeId));
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
        case BOOL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == BOOL)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::boolTypeId));
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
        case SBYTE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == SBYTE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::sbyteTypeId));
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
        case BYTE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == BYTE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::byteTypeId));
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
        case SHORT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == SHORT)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::shortTypeId));
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
        case USHORT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == USHORT)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::ushortTypeId));
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
        case INT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == INT)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::intTypeId));
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
        case UINT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == UINT)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::uintTypeId));
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
        case LONG:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch9 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == LONG)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::longTypeId));
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
        case ULONG:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch10 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == ULONG)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::ulongTypeId));
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
        case FLOAT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == FLOAT)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::floatTypeId));
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
        case DOUBLE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch12 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == DOUBLE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(otava::intermediate::doubleTypeId));
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FundamentalTypeId");
        else soul::lexer::WriteFailureToLog(lexer, "FundamentalTypeId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::TypeRef(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TypeRef");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589448);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    int32_t baseTypeId = int32_t();
    int8_t pointerCount = int8_t();
    std::unique_ptr<soul::parser::Value<int32_t>> typeId;
    std::unique_ptr<soul::parser::Value<int32_t>> fundamentalTypeId;
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
                    switch (*lexer)
                    {
                        case TYPEID:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch5 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeId(lexer);
                                typeId.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
                                if (match.hit)
                                {
                                    sp = lexer.GetSourcePos(pos);
                                    baseTypeId = typeId->value;
                                }
                                *parentMatch5 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case BOOL:
                        case BYTE:
                        case DOUBLE:
                        case FLOAT:
                        case INT:
                        case LONG:
                        case SBYTE:
                        case SHORT:
                        case UINT:
                        case ULONG:
                        case USHORT:
                        case VOID:
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::FundamentalTypeId(lexer);
                                fundamentalTypeId.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
                                if (match.hit)
                                {
                                    sp = lexer.GetSourcePos(pos);
                                    baseTypeId = fundamentalTypeId->value;
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
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch7 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch8 = &match;
                    {
                        while (true)
                        {
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch9 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch10 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(false);
                                        if (*lexer == AST)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            ++pointerCount;
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
                                    break;
                                }
                            }
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
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeRef");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<otava::intermediate::TypeRef>(otava::intermediate::MakeTypeRef(sp, baseTypeId, pointerCount)));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeRef");
        else soul::lexer::WriteFailureToLog(lexer, "TypeRef");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::StructureType(Lexer& lexer, otava::intermediate::Context* context, int32_t typeId)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "StructureType");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589449);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::vector<otava::intermediate::TypeRef> fieldTypeRefs = std::vector<otava::intermediate::TypeRef>();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> first;
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> next;
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
                soul::parser::Match match(false);
                if (*lexer == LBRACE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    sp = lexer.GetSourcePos(pos);
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
                int64_t save = lexer.GetPos();
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
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                first.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                if (match.hit)
                                {
                                    fieldTypeRefs.push_back(first->value);
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
                                        int64_t save = lexer.GetPos();
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == COMMA)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    *parentMatch11 = match;
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
                                                            soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                                            next.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                fieldTypeRefs.push_back(next->value);
                                                            }
                                                            *parentMatch13 = match;
                                                        }
                                                        *parentMatch12 = match;
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
                        *parentMatch4 = match;
                    }
                    else
                    {
                        lexer.SetPos(save);
                    }
                }
                *parentMatch3 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                if (*lexer == RBRACE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    context->GetStructureType(sp, typeId, fieldTypeRefs);
                }
                *parentMatch15 = match;
            }
            *parentMatch14 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StructureType");
        else soul::lexer::WriteFailureToLog(lexer, "StructureType");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ArrayType(Lexer& lexer, otava::intermediate::Context* context, int32_t typeId)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ArrayType");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589450);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    int64_t size = int64_t();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> elementTypeRef;
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
                        if (*lexer == LBRACKET)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            sp = lexer.GetSourcePos(pos);
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
                            if (*lexer == NUMBER)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                size = lexer.GetToken(pos).ToLong();
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
                        bool pass = true;
                        soul::parser::Match match(false);
                        if (*lexer == ID)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            pass = util::ToUtf8(lexer.GetToken(pos).ToString()) == "x";
                        }
                        if (match.hit && !pass)
                        {
                            match = soul::parser::Match(false);
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                elementTypeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                *parentMatch9 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                if (*lexer == RBRACKET)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    context->GetArrayType(sp, typeId, size, elementTypeRef->value);
                }
                *parentMatch11 = match;
            }
            *parentMatch10 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ArrayType");
        else soul::lexer::WriteFailureToLog(lexer, "ArrayType");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::FunctionType(Lexer& lexer, otava::intermediate::Context* context, int32_t typeId)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionType");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589451);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::vector<otava::intermediate::TypeRef> paramTypeRefs = std::vector<otava::intermediate::TypeRef>();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> returnTypeRef;
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> first;
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> next;
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
                        if (*lexer == FUNCTION)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            sp = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                        returnTypeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
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
                    if (*lexer == LPAREN)
                    {
                        ++lexer;
                        match.hit = true;
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch11 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                first.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                if (match.hit)
                                {
                                    paramTypeRefs.push_back(first->value);
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
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch13 = &match;
                                {
                                    while (true)
                                    {
                                        int64_t save = lexer.GetPos();
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch14 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch15 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == COMMA)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    *parentMatch15 = match;
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
                                                            soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                                            next.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                paramTypeRefs.push_back(next->value);
                                                            }
                                                            *parentMatch17 = match;
                                                        }
                                                        *parentMatch16 = match;
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
                                                break;
                                            }
                                        }
                                    }
                                }
                                *parentMatch12 = match;
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
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                if (*lexer == RPAREN)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    context->GetFunctionType(sp, typeId, returnTypeRef->value, paramTypeRefs);
                }
                *parentMatch19 = match;
            }
            *parentMatch18 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionType");
        else soul::lexer::WriteFailureToLog(lexer, "FunctionType");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::DataDefinitions(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DataDefinitions");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589452);
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
                if (*lexer == DATA)
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
                    soul::parser::Match match(false);
                    if (*lexer == LBRACE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
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
                soul::parser::Match match(true);
                soul::parser::Match* parentMatch5 = &match;
                {
                    while (true)
                    {
                        int64_t save = lexer.GetPos();
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::DataDefinition(lexer, context);
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
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                    context->ValidateData();
                }
                *parentMatch7 = match;
            }
            *parentMatch6 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DataDefinitions");
        else soul::lexer::WriteFailureToLog(lexer, "DataDefinitions");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::DataDefinition(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DataDefinition");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589453);
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    bool once = bool();
    std::string variableName = std::string();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::ConstantValue> initializer;
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                    typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                    if (match.hit)
                    {
                        tref = typeRef->value;
                        context->ResolveType(tref);
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
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == ONCE)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    once = true;
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch9 = &match;
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
                        sp = lexer.GetSourcePos(pos);
                        variableName = util::ToUtf8(lexer.GetToken(pos).ToString());
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
        soul::parser::Match* parentMatch10 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch12 = &match;
                switch (*lexer)
                {
                    case SEMICOLON:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch13 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == SEMICOLON)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                context->AddGlobalVariable(sp, tref.GetType(), variableName, nullptr, once);
                            }
                            *parentMatch13 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch12 = match;
                        }
                        break;
                    }
                    case ASSIGN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == ASSIGN)
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
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Constant(lexer, context);
                                    initializer.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                    if (match.hit)
                                    {
                                        context->AddGlobalVariable(sp, tref.GetType(), variableName, initializer.release(), once);
                                    }
                                    *parentMatch16 = match;
                                }
                                *parentMatch15 = match;
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
            }
            *parentMatch10 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DataDefinition");
        else soul::lexer::WriteFailureToLog(lexer, "DataDefinition");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::Constant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Constant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589454);
    std::unique_ptr<otava::intermediate::ConstantValue> boolConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> sbyteConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> byteConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> shortConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> ushortConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> intConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> uintConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> longConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> ulongConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> floatConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> doubleConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> addressConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> arrayConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> structureConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> stringConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> stringArrayConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> conversionConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> clsidConstant;
    std::unique_ptr<otava::intermediate::ConstantValue> symbolConstant;
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
                switch (*lexer)
                {
                    case BOOL:
                    case BYTE:
                    case DOUBLE:
                    case FLOAT:
                    case INT:
                    case LONG:
                    case SBYTE:
                    case SHORT:
                    case TYPEID:
                    case UINT:
                    case ULONG:
                    case USHORT:
                    case VOID:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch4 = &match;
                        {
                            int64_t save = lexer.GetPos();
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch5 = &match;
                            switch (*lexer)
                            {
                                case BOOL:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch6 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::BoolConstant(lexer, context);
                                        boolConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, boolConstant.release());
                                            }
                                        }
                                        *parentMatch6 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case SBYTE:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch7 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::SByteConstant(lexer, context);
                                        sbyteConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, sbyteConstant.release());
                                            }
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case BYTE:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::ByteConstant(lexer, context);
                                        byteConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, byteConstant.release());
                                            }
                                        }
                                        *parentMatch8 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case SHORT:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::ShortConstant(lexer, context);
                                        shortConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, shortConstant.release());
                                            }
                                        }
                                        *parentMatch9 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case USHORT:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch10 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::UShortConstant(lexer, context);
                                        ushortConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, ushortConstant.release());
                                            }
                                        }
                                        *parentMatch10 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case INT:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch11 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::IntConstant(lexer, context);
                                        intConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, intConstant.release());
                                            }
                                        }
                                        *parentMatch11 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case UINT:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch12 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::UIntConstant(lexer, context);
                                        uintConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, uintConstant.release());
                                            }
                                        }
                                        *parentMatch12 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case LONG:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch13 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::LongConstant(lexer, context);
                                        longConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, longConstant.release());
                                            }
                                        }
                                        *parentMatch13 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case ULONG:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch14 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::ULongConstant(lexer, context);
                                        ulongConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, ulongConstant.release());
                                            }
                                        }
                                        *parentMatch14 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case FLOAT:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch15 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::FloatConstant(lexer, context);
                                        floatConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, floatConstant.release());
                                            }
                                        }
                                        *parentMatch15 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                                case DOUBLE:
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch16 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::DoubleConstant(lexer, context);
                                        doubleConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, doubleConstant.release());
                                            }
                                        }
                                        *parentMatch16 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch5 = match;
                                    }
                                    break;
                                }
                            }
                            *parentMatch4 = match;
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
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::AddressConstant(lexer, context);
                                        addressConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                                #endif
                                                return soul::parser::Match(true, addressConstant.release());
                                            }
                                        }
                                        *parentMatch18 = match;
                                    }
                                    *parentMatch17 = match;
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
                    case LBRACKET:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch19 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::ArrayConstant(lexer, context);
                            arrayConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                    #endif
                                    return soul::parser::Match(true, arrayConstant.release());
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
                    case LBRACE:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch20 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::StructureConstant(lexer, context);
                            structureConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                    #endif
                                    return soul::parser::Match(true, structureConstant.release());
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
                    case STRING:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch21 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::StringConstant(lexer, context);
                            stringConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                    #endif
                                    return soul::parser::Match(true, stringConstant.release());
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
                    case ID:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch22 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::StringArrayConstant(lexer, context);
                            stringArrayConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                    #endif
                                    return soul::parser::Match(true, stringArrayConstant.release());
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
                }
                *parentMatch2 = match;
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
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::ConversionConstant(lexer, context);
                            conversionConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                    #endif
                                    return soul::parser::Match(true, conversionConstant.release());
                                }
                            }
                            *parentMatch24 = match;
                        }
                        *parentMatch23 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::ClsIdConstant(lexer, context);
                        clsidConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                                #endif
                                return soul::parser::Match(true, clsidConstant.release());
                            }
                        }
                        *parentMatch26 = match;
                    }
                    *parentMatch25 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch27 = &match;
            lexer.SetPos(save);
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch28 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::SymbolConstant(lexer, context);
                    symbolConstant.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
                            #endif
                            return soul::parser::Match(true, symbolConstant.release());
                        }
                    }
                    *parentMatch28 = match;
                }
                *parentMatch27 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Constant");
        else soul::lexer::WriteFailureToLog(lexer, "Constant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::BoolConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BoolConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589455);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == BOOL)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                switch (*lexer)
                {
                    case TRUE:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch4 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == TRUE)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BoolConstant");
                                    #endif
                                    return soul::parser::Match(true, context->GetTrueValue());
                                }
                            }
                            *parentMatch4 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                    case FALSE:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == FALSE)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BoolConstant");
                                    #endif
                                    return soul::parser::Match(true, context->GetFalseValue());
                                }
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        break;
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BoolConstant");
        else soul::lexer::WriteFailureToLog(lexer, "BoolConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::SByteConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SByteConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589456);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == SBYTE)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SByteConstant");
                        #endif
                        return soul::parser::Match(true, context->GetSByteValue(lexer.GetToken(pos).ToSByte()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SByteConstant");
        else soul::lexer::WriteFailureToLog(lexer, "SByteConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ByteConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ByteConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589457);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == BYTE)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ByteConstant");
                        #endif
                        return soul::parser::Match(true, context->GetByteValue(lexer.GetToken(pos).ToByte()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ByteConstant");
        else soul::lexer::WriteFailureToLog(lexer, "ByteConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ShortConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ShortConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589458);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == SHORT)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShortConstant");
                        #endif
                        return soul::parser::Match(true, context->GetShortValue(lexer.GetToken(pos).ToShort()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ShortConstant");
        else soul::lexer::WriteFailureToLog(lexer, "ShortConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::UShortConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UShortConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589459);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == USHORT)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UShortConstant");
                        #endif
                        return soul::parser::Match(true, context->GetUShortValue(lexer.GetToken(pos).ToUShort()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UShortConstant");
        else soul::lexer::WriteFailureToLog(lexer, "UShortConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::IntConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IntConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589460);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == INT)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IntConstant");
                        #endif
                        return soul::parser::Match(true, context->GetIntValue(lexer.GetToken(pos).ToInt()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IntConstant");
        else soul::lexer::WriteFailureToLog(lexer, "IntConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::UIntConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UIntConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589461);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == UINT)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UIntConstant");
                        #endif
                        return soul::parser::Match(true, context->GetUIntValue(lexer.GetToken(pos).ToUInt()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UIntConstant");
        else soul::lexer::WriteFailureToLog(lexer, "UIntConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::LongConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LongConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589462);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == LONG)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LongConstant");
                        #endif
                        return soul::parser::Match(true, context->GetLongValue(lexer.GetToken(pos).ToLong()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LongConstant");
        else soul::lexer::WriteFailureToLog(lexer, "LongConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ULongConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ULongConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589463);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == ULONG)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ULongConstant");
                        #endif
                        return soul::parser::Match(true, context->GetULongValue(lexer.GetToken(pos).ToULong()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ULongConstant");
        else soul::lexer::WriteFailureToLog(lexer, "ULongConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::FloatConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FloatConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589464);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == FLOAT)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FloatConstant");
                        #endif
                        return soul::parser::Match(true, context->GetFloatValue(lexer.GetToken(pos).ToFloat()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FloatConstant");
        else soul::lexer::WriteFailureToLog(lexer, "FloatConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::DoubleConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "DoubleConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589465);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == DOUBLE)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DoubleConstant");
                        #endif
                        return soul::parser::Match(true, context->GetDoubleValue(lexer.GetToken(pos).ToDouble()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DoubleConstant");
        else soul::lexer::WriteFailureToLog(lexer, "DoubleConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::AddressConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AddressConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589466);
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
            typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
            if (match.hit)
            {
                tref = typeRef->value;
                context->ResolveType(tref);
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
                switch (*lexer)
                {
                    case NULL_TOKEN:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == NULL_TOKEN)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddressConstant");
                                    #endif
                                    return soul::parser::Match(true, context->GetNullValue(lexer.GetSourcePos(pos), tref.GetType()));
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
                    case ID:
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
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
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddressConstant");
                                    #endif
                                    return soul::parser::Match(true, context->MakeAddressLiteral(lexer.GetSourcePos(pos), tref.GetType(), util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AddressConstant");
        else soul::lexer::WriteFailureToLog(lexer, "AddressConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ArrayConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ArrayConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589467);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::vector<otava::intermediate::ConstantValue*> elements = std::vector<otava::intermediate::ConstantValue*>();
    std::unique_ptr<otava::intermediate::ConstantValue> first;
    std::unique_ptr<otava::intermediate::ConstantValue> next;
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
                soul::parser::Match match(false);
                if (*lexer == LBRACKET)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    sp = lexer.GetSourcePos(pos);
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
                int64_t save = lexer.GetPos();
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
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::Constant(lexer, context);
                                first.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                if (match.hit)
                                {
                                    elements.push_back(first.release());
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
                                        int64_t save = lexer.GetPos();
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == COMMA)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    *parentMatch11 = match;
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
                                                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Constant(lexer, context);
                                                            next.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                elements.push_back(next.release());
                                                            }
                                                            *parentMatch13 = match;
                                                        }
                                                        *parentMatch12 = match;
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
                        *parentMatch4 = match;
                    }
                    else
                    {
                        lexer.SetPos(save);
                    }
                }
                *parentMatch3 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ArrayConstant");
                        #endif
                        return soul::parser::Match(true, context->MakeArrayValue(sp, elements));
                    }
                }
                *parentMatch15 = match;
            }
            *parentMatch14 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ArrayConstant");
        else soul::lexer::WriteFailureToLog(lexer, "ArrayConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::StructureConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "StructureConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589468);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::vector<otava::intermediate::ConstantValue*> fieldValues = std::vector<otava::intermediate::ConstantValue*>();
    std::unique_ptr<otava::intermediate::ConstantValue> first;
    std::unique_ptr<otava::intermediate::ConstantValue> next;
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
                soul::parser::Match match(false);
                if (*lexer == LBRACE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    sp = lexer.GetSourcePos(pos);
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
                int64_t save = lexer.GetPos();
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
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::Constant(lexer, context);
                                first.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                if (match.hit)
                                {
                                    fieldValues.push_back(first.release());
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
                                        int64_t save = lexer.GetPos();
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch10 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == COMMA)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    *parentMatch11 = match;
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
                                                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Constant(lexer, context);
                                                            next.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                fieldValues.push_back(next.release());
                                                            }
                                                            *parentMatch13 = match;
                                                        }
                                                        *parentMatch12 = match;
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
                        *parentMatch4 = match;
                    }
                    else
                    {
                        lexer.SetPos(save);
                    }
                }
                *parentMatch3 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                if (*lexer == RBRACE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StructureConstant");
                        #endif
                        return soul::parser::Match(true, context->MakeStructureValue(sp, fieldValues));
                    }
                }
                *parentMatch15 = match;
            }
            *parentMatch14 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StructureConstant");
        else soul::lexer::WriteFailureToLog(lexer, "StructureConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::StringConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "StringConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589469);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == STRING)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StringConstant");
                #endif
                return soul::parser::Match(true, context->MakeStringValue(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StringConstant");
        else soul::lexer::WriteFailureToLog(lexer, "StringConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::StringArrayConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "StringArrayConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589470);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::vector<otava::intermediate::ConstantValue*> strings = std::vector<otava::intermediate::ConstantValue*>();
    std::unique_ptr<soul::parser::Value<char>> prefix;
    std::unique_ptr<otava::intermediate::ConstantValue> first;
    std::unique_ptr<otava::intermediate::ConstantValue> next;
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::StringArrayPrefix(lexer);
                    prefix.reset(static_cast<soul::parser::Value<char>*>(match.value));
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
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
                    if (*lexer == LBRACKET)
                    {
                        ++lexer;
                        match.hit = true;
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
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch9 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::Constant(lexer, context);
                                first.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                if (match.hit)
                                {
                                    strings.push_back(first.release());
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
                                        int64_t save = lexer.GetPos();
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch12 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch13 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == COMMA)
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
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch15 = &match;
                                                        {
                                                            int64_t pos = lexer.GetPos();
                                                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Constant(lexer, context);
                                                            next.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                                                            if (match.hit)
                                                            {
                                                                strings.push_back(next.release());
                                                            }
                                                            *parentMatch15 = match;
                                                        }
                                                        *parentMatch14 = match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StringArrayConstant");
                        #endif
                        return soul::parser::Match(true, context->MakeStringArrayValue(sp, prefix->value, strings));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StringArrayConstant");
        else soul::lexer::WriteFailureToLog(lexer, "StringArrayConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::StringArrayPrefix(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "StringArrayPrefix");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589471);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
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
            std::string p = util::ToUtf8(lexer.GetToken(pos).ToString());
            pass = p == "u" || p == "w" || p == "b";
            if (pass)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StringArrayPrefix");
                    #endif
                    return soul::parser::Match(true, new soul::parser::Value<char>(p[0]));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StringArrayPrefix");
        else soul::lexer::WriteFailureToLog(lexer, "StringArrayPrefix");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ConversionConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ConversionConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589472);
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::ConstantValue> from;
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                        typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                        if (match.hit)
                        {
                            tref = typeRef->value;
                            context->ResolveType(tref);
                            sp = lexer.GetSourcePos(pos);
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
                        if (*lexer == CONV)
                        {
                            ++lexer;
                            match.hit = true;
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
                soul::parser::Match* parentMatch6 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == LPAREN)
                    {
                        ++lexer;
                        match.hit = true;
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
            soul::parser::Match* parentMatch7 = &match;
            {
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Constant(lexer, context);
                from.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                *parentMatch7 = match;
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConversionConstant");
                        #endif
                        return soul::parser::Match(true, context->MakeConversionValue(sp, tref.GetType(), from.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ConversionConstant");
        else soul::lexer::WriteFailureToLog(lexer, "ConversionConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ClsIdConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ClsIdConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589473);
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
            typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
            if (match.hit)
            {
                tref = typeRef->value;
                context->ResolveType(tref);
                sp = lexer.GetSourcePos(pos);
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
                if (*lexer == CLSID)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClsIdConstant");
                        #endif
                        return soul::parser::Match(true, context->MakeClsIdValue(sp, tref.GetType(), util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ClsIdConstant");
        else soul::lexer::WriteFailureToLog(lexer, "ClsIdConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::SymbolConstant(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SymbolConstant");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589474);
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::ConstantValue> symbolValue;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
            typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
            if (match.hit)
            {
                tref = typeRef->value;
                context->ResolveType(tref);
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::SymbolValue(lexer, context, tref.GetType());
                symbolValue.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SymbolConstant");
                        #endif
                        return soul::parser::Match(true, symbolValue.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SymbolConstant");
        else soul::lexer::WriteFailureToLog(lexer, "SymbolConstant");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::Value(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Value");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589475);
    std::unique_ptr<otava::intermediate::Value> regValue;
    std::unique_ptr<otava::intermediate::ConstantValue> symbolValue;
    std::unique_ptr<otava::intermediate::ConstantValue> literalValue;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case DOLLAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::RegValue(lexer, context, type);
                regValue.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Value");
                        #endif
                        return soul::parser::Match(true, regValue.release());
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
        case AT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::SymbolValue(lexer, context, type);
                symbolValue.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Value");
                        #endif
                        return soul::parser::Match(true, symbolValue.release());
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
        case FALSE:
        case ID:
        case NULL_TOKEN:
        case NUMBER:
        case TRUE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::LiteralValue(lexer, context, type);
                literalValue.reset(static_cast<otava::intermediate::ConstantValue*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Value");
                        #endif
                        return soul::parser::Match(true, literalValue.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Value");
        else soul::lexer::WriteFailureToLog(lexer, "Value");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::RegValue(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RegValue");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589476);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == DOLLAR)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                sp = lexer.GetSourcePos(pos);
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
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    int32_t reg = lexer.GetToken(pos).ToInt();
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RegValue");
                        #endif
                        return soul::parser::Match(true, context->CurrentFunction()->GetRegRef(sp, type, reg, context));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RegValue");
        else soul::lexer::WriteFailureToLog(lexer, "RegValue");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ResultRegValue(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ResultRegValue");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589477);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == DOLLAR)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                sp = lexer.GetSourcePos(pos);
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
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    int32_t reg = lexer.GetToken(pos).ToInt();
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ResultRegValue");
                        #endif
                        return soul::parser::Match(true, context->CurrentFunction()->MakeRegValue(sp, type, reg, context));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ResultRegValue");
        else soul::lexer::WriteFailureToLog(lexer, "ResultRegValue");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::SymbolValue(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SymbolValue");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589478);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == AT)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
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
                    sp = lexer.GetSourcePos(pos);
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SymbolValue");
                        #endif
                        return soul::parser::Match(true, context->MakeSymbolValue(sp, type, util::ToUtf8(lexer.GetToken(pos).ToString())));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SymbolValue");
        else soul::lexer::WriteFailureToLog(lexer, "SymbolValue");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::LiteralValue(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LiteralValue");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589479);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case TRUE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == TRUE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LiteralValue");
                        #endif
                        return soul::parser::Match(true, context->GetBooleanLiteral(lexer.GetSourcePos(pos), type, true));
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
        case FALSE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == FALSE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LiteralValue");
                        #endif
                        return soul::parser::Match(true, context->GetBooleanLiteral(lexer.GetSourcePos(pos), type, false));
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
        case NULL_TOKEN:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NULL_TOKEN)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LiteralValue");
                        #endif
                        return soul::parser::Match(true, context->GetNullValue(lexer.GetSourcePos(pos), type));
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
        case NUMBER:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LiteralValue");
                        #endif
                        return soul::parser::Match(true, context->MakeNumericLiteral(lexer.GetSourcePos(pos), type, util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        case ID:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
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
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LiteralValue");
                        #endif
                        return soul::parser::Match(true, context->MakeAddressLiteral(lexer.GetSourcePos(pos), type, util::ToUtf8(lexer.GetToken(pos).ToString())));
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LiteralValue");
        else soul::lexer::WriteFailureToLog(lexer, "LiteralValue");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::FunctionDefinitions(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionDefinitions");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589480);
    soul::parser::Match match(true);
    soul::parser::Match* parentMatch0 = &match;
    {
        while (true)
        {
            int64_t save = lexer.GetPos();
            {
                soul::parser::Match match = IntermediateCodeParser<Lexer>::FunctionDefinition(lexer, context);
                if (match.hit)
                {
                    *parentMatch0 = match;
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionDefinitions");
        else soul::lexer::WriteFailureToLog(lexer, "FunctionDefinitions");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::FunctionDefinition(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionDefinition");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589481);
    otava::intermediate::Function* function = nullptr;
    std::unique_ptr<otava::intermediate::Function> header;
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::FunctionHeader(lexer, context);
                    header.reset(static_cast<otava::intermediate::Function*>(match.value));
                    if (match.hit)
                    {
                        function = header.release();
                        context->SetCurrentFunction(function);
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
                    if (*lexer == LBRACE)
                    {
                        ++lexer;
                        match.hit = true;
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
            soul::parser::Match* parentMatch5 = &match;
            {
                soul::parser::Match match(true);
                soul::parser::Match* parentMatch6 = &match;
                {
                    while (true)
                    {
                        int64_t save = lexer.GetPos();
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::BasicBlock(lexer, context, function);
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
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch7 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == RBRACE)
            {
                ++lexer;
                match.hit = true;
            }
            *parentMatch7 = match;
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

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::FunctionHeader(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionHeader");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589482);
    otava::intermediate::TypeRef functionTypeRef = otava::intermediate::TypeRef();
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    bool once = bool();
    std::string functionId = std::string();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::MetadataRef> mdRef;
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
                                if (*lexer == FUNCTION)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    sp = lexer.GetSourcePos(pos);
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
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                    typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                    if (match.hit)
                                    {
                                        functionTypeRef = typeRef->value;
                                        context->ResolveType(functionTypeRef);
                                    }
                                    *parentMatch8 = match;
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
                                        if (*lexer == ONCE)
                                        {
                                            ++lexer;
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            once = true;
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
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
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
                            if (*lexer == ID)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                functionId = util::ToUtf8(lexer.GetToken(pos).ToString());
                            }
                            *parentMatch14 = match;
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
                    soul::parser::Match match(true);
                    int64_t save = lexer.GetPos();
                    soul::parser::Match* parentMatch16 = &match;
                    {
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataRef(lexer, context);
                        mdRef.reset(static_cast<otava::intermediate::MetadataRef*>(match.value));
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionHeader");
                #endif
                return soul::parser::Match(true, context->AddFunctionDefinition(sp, functionTypeRef.GetType(), functionId, once, mdRef.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionHeader");
        else soul::lexer::WriteFailureToLog(lexer, "FunctionHeader");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::BasicBlock(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Function* function)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BasicBlock");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589483);
    otava::intermediate::BasicBlock* basicBlock = nullptr;
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<soul::parser::Value<int32_t>> id;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = IntermediateCodeParser<Lexer>::Label(lexer);
            id.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
            if (match.hit)
            {
                sp = lexer.GetSourcePos(pos);
                basicBlock = function->AddBasicBlock(sp, id->value, context);
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
            soul::parser::Match match = IntermediateCodeParser<Lexer>::Instructions(lexer, context, basicBlock);
            *parentMatch2 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BasicBlock");
        else soul::lexer::WriteFailureToLog(lexer, "BasicBlock");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::Label(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Label");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589484);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == AT)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Label");
                        #endif
                        return soul::parser::Match(true, new soul::parser::Value<int32_t>(lexer.GetToken(pos).ToInt()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Label");
        else soul::lexer::WriteFailureToLog(lexer, "Label");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::Operand(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Operand");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589485);
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::Value> value;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
            typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
            if (match.hit)
            {
                tref = typeRef->value;
                context->ResolveType(tref);
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, tref.GetType());
                value.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operand");
                        #endif
                        return soul::parser::Match(true, value.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operand");
        else soul::lexer::WriteFailureToLog(lexer, "Operand");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::Instructions(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::BasicBlock* basicBlock)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Instructions");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589486);
    std::unique_ptr<otava::intermediate::Instruction> instruction;
    std::unique_ptr<otava::intermediate::MetadataRef> mdRef;
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
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch4 = &match;
                    {
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Instruction(lexer, context);
                        instruction.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                        *parentMatch4 = match;
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
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataRef(lexer, context);
                                mdRef.reset(static_cast<otava::intermediate::MetadataRef*>(match.value));
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
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    basicBlock->AddInstruction(instruction.release(), mdRef.release());
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
        soul::parser::Match* parentMatch7 = &match;
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch10 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch11 = &match;
                            {
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::Instruction(lexer, context);
                                instruction.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                                *parentMatch11 = match;
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
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataRef(lexer, context);
                                        mdRef.reset(static_cast<otava::intermediate::MetadataRef*>(match.value));
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
                                *parentMatch11 = match;
                            }
                            *parentMatch10 = match;
                        }
                        if (match.hit)
                        {
                            basicBlock->AddInstruction(instruction.release(), mdRef.release());
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
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instructions");
        else soul::lexer::WriteFailureToLog(lexer, "Instructions");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::Instruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Instruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589487);
    std::unique_ptr<otava::intermediate::Instruction> store;
    std::unique_ptr<otava::intermediate::Instruction> arg;
    std::unique_ptr<otava::intermediate::Instruction> jmp;
    std::unique_ptr<otava::intermediate::Instruction> branch;
    std::unique_ptr<otava::intermediate::Instruction> procedureCall;
    std::unique_ptr<otava::intermediate::Instruction> ret;
    std::unique_ptr<otava::intermediate::Instruction> switch_;
    std::unique_ptr<otava::intermediate::Instruction> valueInst;
    std::unique_ptr<otava::intermediate::Instruction> nopInst;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case STORE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::StoreInstruction(lexer, context);
                store.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
                        #endif
                        return soul::parser::Match(true, store.release());
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
        case ARG:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::ArgInstruction(lexer, context);
                arg.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
                        #endif
                        return soul::parser::Match(true, arg.release());
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
        case JMP:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::JmpInstruction(lexer, context);
                jmp.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
                        #endif
                        return soul::parser::Match(true, jmp.release());
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
        case BRANCH:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::BranchInstruction(lexer, context);
                branch.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
                        #endif
                        return soul::parser::Match(true, branch.release());
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
        case CALL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::ProcedureCallInstruction(lexer, context);
                procedureCall.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
                        #endif
                        return soul::parser::Match(true, procedureCall.release());
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
        case RET:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::RetInstruction(lexer, context);
                ret.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
                        #endif
                        return soul::parser::Match(true, ret.release());
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
        case SWITCH:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::SwitchInstruction(lexer, context);
                switch_.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
                        #endif
                        return soul::parser::Match(true, switch_.release());
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
        case BOOL:
        case BYTE:
        case DOUBLE:
        case FLOAT:
        case INT:
        case LONG:
        case SBYTE:
        case SHORT:
        case TYPEID:
        case UINT:
        case ULONG:
        case USHORT:
        case VOID:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::ValueInstruction(lexer, context);
                valueInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
                        #endif
                        return soul::parser::Match(true, valueInst.release());
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
        case NOP:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch9 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::NoOperationInstruction(lexer, context);
                nopInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
                        #endif
                        return soul::parser::Match(true, nopInst.release());
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Instruction");
        else soul::lexer::WriteFailureToLog(lexer, "Instruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::StoreInstruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "StoreInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589488);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    otava::intermediate::TypeRef ptref = otava::intermediate::TypeRef();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::Value> value;
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> ptrTypeRef;
    std::unique_ptr<otava::intermediate::Value> ptr;
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == STORE)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                sp = lexer.GetSourcePos(pos);
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
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                if (match.hit)
                                {
                                    tref = typeRef->value;
                                    context->ResolveType(tref);
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, tref.GetType());
                        value.reset(static_cast<otava::intermediate::Value*>(match.value));
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
                    if (*lexer == COMMA)
                    {
                        ++lexer;
                        match.hit = true;
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
            soul::parser::Match* parentMatch10 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch11 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                    ptrTypeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                    if (match.hit)
                    {
                        ptref = ptrTypeRef->value;
                        context->ResolveType(ptref);
                    }
                    *parentMatch11 = match;
                }
                *parentMatch10 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, ptref.GetType());
                ptr.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StoreInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::StoreInstruction(sp, value.release(), ptr.release()));
                    }
                }
                *parentMatch13 = match;
            }
            *parentMatch12 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StoreInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "StoreInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ArgInstruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ArgInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589489);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::Value> arg;
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
                soul::parser::Match match(false);
                if (*lexer == ARG)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    sp = lexer.GetSourcePos(pos);
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                    typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                    if (match.hit)
                    {
                        tref = typeRef->value;
                        context->ResolveType(tref);
                    }
                    *parentMatch4 = match;
                }
                *parentMatch3 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, tref.GetType());
                arg.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ArgInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::ArgInstruction(sp, arg.release()));
                    }
                }
                *parentMatch6 = match;
            }
            *parentMatch5 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ArgInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "ArgInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::JmpInstruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "JmpInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589490);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<soul::parser::Value<int32_t>> target;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == JMP)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                sp = lexer.GetSourcePos(pos);
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Label(lexer);
                target.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "JmpInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::JmpInstruction(sp, target->value));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "JmpInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "JmpInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::BranchInstruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BranchInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589491);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::Value> cond;
    std::unique_ptr<soul::parser::Value<int32_t>> trueTarget;
    std::unique_ptr<soul::parser::Value<int32_t>> falseTarget;
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == BRANCH)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    sp = lexer.GetSourcePos(pos);
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
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                    typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                    if (match.hit)
                                    {
                                        tref = typeRef->value;
                                        context->ResolveType(tref);
                                    }
                                    *parentMatch8 = match;
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
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, tref.GetType());
                            cond.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch9 = match;
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
                        if (*lexer == COMMA)
                        {
                            ++lexer;
                            match.hit = true;
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
                soul::parser::Match* parentMatch11 = &match;
                {
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Label(lexer);
                    trueTarget.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
                    *parentMatch11 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch12 = &match;
            {
                soul::parser::Match match(false);
                if (*lexer == COMMA)
                {
                    ++lexer;
                    match.hit = true;
                }
                *parentMatch12 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Label(lexer);
                falseTarget.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BranchInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::BranchInstruction(sp, cond.release(), trueTarget->value, falseTarget->value));
                    }
                }
                *parentMatch14 = match;
            }
            *parentMatch13 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BranchInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "BranchInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ProcedureCallInstruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ProcedureCallInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589492);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::Value> callee;
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
                soul::parser::Match match(false);
                if (*lexer == CALL)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    sp = lexer.GetSourcePos(pos);
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                    typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                    if (match.hit)
                    {
                        tref = typeRef->value;
                        context->ResolveType(tref);
                    }
                    *parentMatch4 = match;
                }
                *parentMatch3 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, tref.GetType());
                callee.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ProcedureCallInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::ProcedureCallInstruction(sp, callee.release()));
                    }
                }
                *parentMatch6 = match;
            }
            *parentMatch5 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ProcedureCallInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "ProcedureCallInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::RetInstruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "RetInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589493);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::Value> returnValue;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == RET)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                sp = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch6 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch7 = &match;
                            int64_t save = lexer.GetPos();
                            {
                                soul::parser::Match match(false);
                                if (*lexer == VOID)
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
                                    int64_t tmp = lexer.GetPos();
                                    lexer.SetPos(save);
                                    save = tmp;
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        soul::parser::Match match(false);
                                        soul::parser::Match* parentMatch10 = &match;
                                        {
                                            soul::parser::Match match(false);
                                            if (*lexer == VOID)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            *parentMatch10 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch11 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == AST)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch11 = match;
                                            }
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                if (!match.hit)
                                {
                                    lexer.SetPos(save);
                                }
                                *parentMatch7 = soul::parser::Match(!match.hit, match.value);
                            }
                            *parentMatch6 = match;
                        }
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RetInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::RetInstruction(sp, nullptr));
                            }
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch14 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                    typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                    if (match.hit)
                                    {
                                        tref = typeRef->value;
                                        context->ResolveType(tref);
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
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, tref.GetType());
                                        returnValue.reset(static_cast<otava::intermediate::Value*>(match.value));
                                        if (match.hit)
                                        {
                                            {
                                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RetInstruction");
                                                #endif
                                                return soul::parser::Match(true, new otava::intermediate::RetInstruction(sp, returnValue.release()));
                                            }
                                        }
                                        *parentMatch16 = match;
                                    }
                                    *parentMatch15 = match;
                                }
                                *parentMatch13 = match;
                            }
                            *parentMatch12 = match;
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "RetInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "RetInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::SwitchInstruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SwitchInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589494);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    otava::intermediate::TypeRef caseTref = otava::intermediate::TypeRef();
    otava::intermediate::SwitchInstruction* inst = nullptr;
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::Value> cond;
    std::unique_ptr<soul::parser::Value<int32_t>> defaultTarget;
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> caseTypeRef;
    std::unique_ptr<otava::intermediate::Value> caseValue;
    std::unique_ptr<soul::parser::Value<int32_t>> caseTarget;
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
                                            int64_t pos = lexer.GetPos();
                                            soul::parser::Match match(false);
                                            if (*lexer == SWITCH)
                                            {
                                                ++lexer;
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                sp = lexer.GetSourcePos(pos);
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
                                                soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                                typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                                if (match.hit)
                                                {
                                                    tref = typeRef->value;
                                                    context->ResolveType(tref);
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
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, tref.GetType());
                                        cond.reset(static_cast<otava::intermediate::Value*>(match.value));
                                        *parentMatch12 = match;
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
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch14 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Label(lexer);
                                        defaultTarget.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
                                        if (match.hit)
                                        {
                                            inst = new otava::intermediate::SwitchInstruction(sp, cond.release(), defaultTarget->value);
                                        }
                                        *parentMatch14 = match;
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
                            soul::parser::Match* parentMatch15 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch15 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch16 = &match;
                        {
                            soul::parser::Match match(false);
                            if (*lexer == LBRACKET)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            *parentMatch16 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch20 = &match;
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
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch24 = &match;
                                                {
                                                    int64_t pos = lexer.GetPos();
                                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                                    caseTypeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                                    if (match.hit)
                                                    {
                                                        caseTref = caseTypeRef->value;
                                                        context->ResolveType(caseTref);
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
                                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, caseTref.GetType());
                                                    caseValue.reset(static_cast<otava::intermediate::Value*>(match.value));
                                                    *parentMatch25 = match;
                                                }
                                                *parentMatch23 = match;
                                            }
                                            *parentMatch22 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch26 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                if (*lexer == COMMA)
                                                {
                                                    ++lexer;
                                                    match.hit = true;
                                                }
                                                *parentMatch26 = match;
                                            }
                                            *parentMatch22 = match;
                                        }
                                        *parentMatch21 = match;
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
                                                soul::parser::Match match = IntermediateCodeParser<Lexer>::Label(lexer);
                                                caseTarget.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
                                                if (match.hit)
                                                {
                                                    inst->AddCaseTarget(otava::intermediate::CaseTarget(caseValue.release(), caseTarget->value));
                                                }
                                                *parentMatch28 = match;
                                            }
                                            *parentMatch27 = match;
                                        }
                                        *parentMatch21 = match;
                                    }
                                    *parentMatch20 = match;
                                }
                                *parentMatch19 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch29 = &match;
                                {
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch30 = &match;
                                    {
                                        while (true)
                                        {
                                            int64_t save = lexer.GetPos();
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch31 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == COLON)
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
                                                        soul::parser::Match* parentMatch33 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch34 = &match;
                                                            {
                                                                soul::parser::Match match(false);
                                                                soul::parser::Match* parentMatch35 = &match;
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch36 = &match;
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch37 = &match;
                                                                        {
                                                                            int64_t pos = lexer.GetPos();
                                                                            soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                                                                            caseTypeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                                                                            if (match.hit)
                                                                            {
                                                                                caseTref = caseTypeRef->value;
                                                                                context->ResolveType(caseTref);
                                                                            }
                                                                            *parentMatch37 = match;
                                                                        }
                                                                        *parentMatch36 = match;
                                                                    }
                                                                    if (match.hit)
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        soul::parser::Match* parentMatch38 = &match;
                                                                        {
                                                                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, caseTref.GetType());
                                                                            caseValue.reset(static_cast<otava::intermediate::Value*>(match.value));
                                                                            *parentMatch38 = match;
                                                                        }
                                                                        *parentMatch36 = match;
                                                                    }
                                                                    *parentMatch35 = match;
                                                                }
                                                                if (match.hit)
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch39 = &match;
                                                                    {
                                                                        soul::parser::Match match(false);
                                                                        if (*lexer == COMMA)
                                                                        {
                                                                            ++lexer;
                                                                            match.hit = true;
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
                                                                soul::parser::Match* parentMatch40 = &match;
                                                                {
                                                                    soul::parser::Match match(false);
                                                                    soul::parser::Match* parentMatch41 = &match;
                                                                    {
                                                                        int64_t pos = lexer.GetPos();
                                                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Label(lexer);
                                                                        caseTarget.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
                                                                        if (match.hit)
                                                                        {
                                                                            inst->AddCaseTarget(otava::intermediate::CaseTarget(caseValue.release(), caseTarget->value));
                                                                        }
                                                                        *parentMatch41 = match;
                                                                    }
                                                                    *parentMatch40 = match;
                                                                }
                                                                *parentMatch34 = match;
                                                            }
                                                            *parentMatch33 = match;
                                                        }
                                                        *parentMatch32 = match;
                                                    }
                                                    *parentMatch31 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    *parentMatch30 = match;
                                                }
                                                else
                                                {
                                                    lexer.SetPos(save);
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    *parentMatch29 = match;
                                }
                                *parentMatch19 = match;
                            }
                            *parentMatch18 = match;
                        }
                        *parentMatch17 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch42 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == RBRACKET)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    *parentMatch42 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SwitchInstruction");
                #endif
                return soul::parser::Match(true, inst);
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SwitchInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "SwitchInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ValueInstruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ValueInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589495);
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    otava::intermediate::RegValue* rslt = nullptr;
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::RegValue> result;
    std::unique_ptr<otava::intermediate::Instruction> inst;
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                    typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                    if (match.hit)
                    {
                        tref = typeRef->value;
                        context->ResolveType(tref);
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::ResultRegValue(lexer, context, tref.GetType());
                        result.reset(static_cast<otava::intermediate::RegValue*>(match.value));
                        if (match.hit)
                        {
                            rslt = result.release();
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
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                soul::parser::Match match(false);
                if (*lexer == ASSIGN)
                {
                    ++lexer;
                    match.hit = true;
                }
                *parentMatch6 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Operation(lexer, context, rslt);
                inst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ValueInstruction");
                        #endif
                        return soul::parser::Match(true, inst.release());
                    }
                }
                *parentMatch8 = match;
            }
            *parentMatch7 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ValueInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "ValueInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::Operation(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Operation");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589496);
    std::unique_ptr<otava::intermediate::Instruction> unaryInst;
    std::unique_ptr<otava::intermediate::Instruction> binaryInst;
    std::unique_ptr<otava::intermediate::Instruction> paramInst;
    std::unique_ptr<otava::intermediate::Instruction> localInst;
    std::unique_ptr<otava::intermediate::Instruction> loadInst;
    std::unique_ptr<otava::intermediate::Instruction> elemAddrInst;
    std::unique_ptr<otava::intermediate::Instruction> ptrOffsetInst;
    std::unique_ptr<otava::intermediate::Instruction> ptrDiffInst;
    std::unique_ptr<otava::intermediate::Instruction> functionCallInst;
    std::unique_ptr<otava::intermediate::Instruction> trapInst;
    std::unique_ptr<otava::intermediate::Instruction> phiInst;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case BITCAST:
        case FLOATTOINT:
        case INTTOFLOAT:
        case INTTOPTR:
        case NEG:
        case NOT:
        case PTRTOINT:
        case SIGNEXTEND:
        case TRUNCATE:
        case ZEROEXTEND:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::UnaryInstruction(lexer, context, result);
                unaryInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, unaryInst.release());
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
        case ADD:
        case AND:
        case DIV:
        case EQUAL:
        case LESS:
        case MOD:
        case MUL:
        case OR:
        case SHL:
        case SHR:
        case SUB:
        case XOR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::BinaryInstruction(lexer, context, result);
                binaryInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, binaryInst.release());
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
        case PARAM:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::ParamInstruction(lexer, context, result);
                paramInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, paramInst.release());
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
        case LOCAL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::LocalInstruction(lexer, context, result);
                localInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, localInst.release());
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
        case LOAD:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::LoadInstruction(lexer, context, result);
                loadInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, loadInst.release());
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
        case ELEMADDR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::ElemAddrInstruction(lexer, context, result);
                elemAddrInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, elemAddrInst.release());
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
        case PTROFFSET:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::PtrOffsetInstruction(lexer, context, result);
                ptrOffsetInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, ptrOffsetInst.release());
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
        case PTRDIFF:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::PtrDiffInstruction(lexer, context, result);
                ptrDiffInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, ptrDiffInst.release());
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
        case CALL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch9 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::FunctionCallInstruction(lexer, context, result);
                functionCallInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, functionCallInst.release());
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
        case TRAP:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch10 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::TrapInstruction(lexer, context, result);
                trapInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, trapInst.release());
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
        case PHI:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::PhiInstruction(lexer, context, result);
                phiInst.reset(static_cast<otava::intermediate::Instruction*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
                        #endif
                        return soul::parser::Match(true, phiInst.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Operation");
        else soul::lexer::WriteFailureToLog(lexer, "Operation");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::UnaryInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "UnaryInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589497);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<otava::intermediate::Value> notOp;
    std::unique_ptr<otava::intermediate::Value> negOp;
    std::unique_ptr<otava::intermediate::Value> sextOp;
    std::unique_ptr<otava::intermediate::Value> zextOp;
    std::unique_ptr<otava::intermediate::Value> truncOp;
    std::unique_ptr<otava::intermediate::Value> bcOp;
    std::unique_ptr<otava::intermediate::Value> ifOp;
    std::unique_ptr<otava::intermediate::Value> fiOp;
    std::unique_ptr<otava::intermediate::Value> ipOp;
    std::unique_ptr<otava::intermediate::Value> piOp;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case NOT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch2 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == NOT)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        notOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::NotInstruction(sp, result, notOp.release()));
                            }
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch1 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case NEG:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch6 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == NEG)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        negOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::NegInstruction(sp, result, negOp.release()));
                            }
                        }
                        *parentMatch8 = match;
                    }
                    *parentMatch7 = match;
                }
                *parentMatch5 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case SIGNEXTEND:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch9 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch10 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == SIGNEXTEND)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
                    }
                    *parentMatch10 = match;
                }
                *parentMatch9 = match;
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        sextOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::SignExtendInstruction(sp, result, sextOp.release()));
                            }
                        }
                        *parentMatch12 = match;
                    }
                    *parentMatch11 = match;
                }
                *parentMatch9 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case ZEROEXTEND:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch13 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch14 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == ZEROEXTEND)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        zextOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::ZeroExtendInstruction(sp, result, zextOp.release()));
                            }
                        }
                        *parentMatch16 = match;
                    }
                    *parentMatch15 = match;
                }
                *parentMatch13 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case TRUNCATE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch17 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch18 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == TRUNCATE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
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
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch20 = &match;
                    {
                        int64_t pos = lexer.GetPos();
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        truncOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::TruncateInstruction(sp, result, truncOp.release()));
                            }
                        }
                        *parentMatch20 = match;
                    }
                    *parentMatch19 = match;
                }
                *parentMatch17 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case BITCAST:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch21 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch22 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == BITCAST)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
                    }
                    *parentMatch22 = match;
                }
                *parentMatch21 = match;
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        bcOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::BitcastInstruction(sp, result, bcOp.release()));
                            }
                        }
                        *parentMatch24 = match;
                    }
                    *parentMatch23 = match;
                }
                *parentMatch21 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case INTTOFLOAT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch25 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch26 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == INTTOFLOAT)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        ifOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::IntToFloatInstruction(sp, result, ifOp.release()));
                            }
                        }
                        *parentMatch28 = match;
                    }
                    *parentMatch27 = match;
                }
                *parentMatch25 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case FLOATTOINT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch29 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch30 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == FLOATTOINT)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
                    }
                    *parentMatch30 = match;
                }
                *parentMatch29 = match;
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        fiOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::FloatToIntInstruction(sp, result, fiOp.release()));
                            }
                        }
                        *parentMatch32 = match;
                    }
                    *parentMatch31 = match;
                }
                *parentMatch29 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case INTTOPTR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch33 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch34 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == INTTOPTR)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
                    }
                    *parentMatch34 = match;
                }
                *parentMatch33 = match;
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        ipOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::IntToPtrInstruction(sp, result, ipOp.release()));
                            }
                        }
                        *parentMatch36 = match;
                    }
                    *parentMatch35 = match;
                }
                *parentMatch33 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case PTRTOINT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch37 = &match;
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch38 = &match;
                {
                    int64_t pos = lexer.GetPos();
                    soul::parser::Match match(false);
                    if (*lexer == PTRTOINT)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
                    }
                    *parentMatch38 = match;
                }
                *parentMatch37 = match;
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                        piOp.reset(static_cast<otava::intermediate::Value*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
                                #endif
                                return soul::parser::Match(true, new otava::intermediate::PtrToIntInstruction(sp, result, piOp.release()));
                            }
                        }
                        *parentMatch40 = match;
                    }
                    *parentMatch39 = match;
                }
                *parentMatch37 = match;
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UnaryInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "UnaryInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::BinaryInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BinaryInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589498);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<otava::intermediate::Value> leftAdd;
    std::unique_ptr<otava::intermediate::Value> rightAdd;
    std::unique_ptr<otava::intermediate::Value> leftSub;
    std::unique_ptr<otava::intermediate::Value> rightSub;
    std::unique_ptr<otava::intermediate::Value> leftMul;
    std::unique_ptr<otava::intermediate::Value> rightMul;
    std::unique_ptr<otava::intermediate::Value> leftDiv;
    std::unique_ptr<otava::intermediate::Value> rightDiv;
    std::unique_ptr<otava::intermediate::Value> leftMod;
    std::unique_ptr<otava::intermediate::Value> rightMod;
    std::unique_ptr<otava::intermediate::Value> leftAnd;
    std::unique_ptr<otava::intermediate::Value> rightAnd;
    std::unique_ptr<otava::intermediate::Value> leftOr;
    std::unique_ptr<otava::intermediate::Value> rightOr;
    std::unique_ptr<otava::intermediate::Value> leftXor;
    std::unique_ptr<otava::intermediate::Value> rightXor;
    std::unique_ptr<otava::intermediate::Value> leftShl;
    std::unique_ptr<otava::intermediate::Value> rightShl;
    std::unique_ptr<otava::intermediate::Value> leftShr;
    std::unique_ptr<otava::intermediate::Value> rightShr;
    std::unique_ptr<otava::intermediate::Value> leftEqual;
    std::unique_ptr<otava::intermediate::Value> rightEqual;
    std::unique_ptr<otava::intermediate::Value> leftLess;
    std::unique_ptr<otava::intermediate::Value> rightLess;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case ADD:
        {
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == ADD)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        sp = lexer.GetSourcePos(pos);
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
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftAdd.reset(static_cast<otava::intermediate::Value*>(match.value));
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
                                if (*lexer == COMMA)
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
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightAdd.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch9 = match;
                        }
                        *parentMatch3 = match;
                    }
                    *parentMatch2 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::AddInstruction(sp, result, leftAdd.release(), rightAdd.release()));
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
        case SUB:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch10 = &match;
            {
                int64_t pos = lexer.GetPos();
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch15 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == SUB)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        sp = lexer.GetSourcePos(pos);
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
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftSub.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch16 = match;
                                }
                                *parentMatch14 = match;
                            }
                            *parentMatch13 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch17 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch17 = match;
                            }
                            *parentMatch13 = match;
                        }
                        *parentMatch12 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch18 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightSub.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch18 = match;
                        }
                        *parentMatch12 = match;
                    }
                    *parentMatch11 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::SubInstruction(sp, result, leftSub.release(), rightSub.release()));
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
        case MUL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch19 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch20 = &match;
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch24 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == MUL)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        sp = lexer.GetSourcePos(pos);
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
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftMul.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch25 = match;
                                }
                                *parentMatch23 = match;
                            }
                            *parentMatch22 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch26 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch26 = match;
                            }
                            *parentMatch22 = match;
                        }
                        *parentMatch21 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch27 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightMul.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch27 = match;
                        }
                        *parentMatch21 = match;
                    }
                    *parentMatch20 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::MulInstruction(sp, result, leftMul.release(), rightMul.release()));
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
        case DIV:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch28 = &match;
            {
                int64_t pos = lexer.GetPos();
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
                            soul::parser::Match* parentMatch32 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch33 = &match;
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
                                        sp = lexer.GetSourcePos(pos);
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
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftDiv.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch34 = match;
                                }
                                *parentMatch32 = match;
                            }
                            *parentMatch31 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch35 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch35 = match;
                            }
                            *parentMatch31 = match;
                        }
                        *parentMatch30 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch36 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightDiv.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch36 = match;
                        }
                        *parentMatch30 = match;
                    }
                    *parentMatch29 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::DivInstruction(sp, result, leftDiv.release(), rightDiv.release()));
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
        case MOD:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch37 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch38 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch39 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch40 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch41 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch42 = &match;
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
                                        sp = lexer.GetSourcePos(pos);
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
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftMod.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch43 = match;
                                }
                                *parentMatch41 = match;
                            }
                            *parentMatch40 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch44 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch44 = match;
                            }
                            *parentMatch40 = match;
                        }
                        *parentMatch39 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch45 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightMod.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch45 = match;
                        }
                        *parentMatch39 = match;
                    }
                    *parentMatch38 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::ModInstruction(sp, result, leftMod.release(), rightMod.release()));
                    }
                }
                *parentMatch37 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case AND:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch46 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch47 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch48 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch49 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch50 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch51 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == AND)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        sp = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch51 = match;
                                }
                                *parentMatch50 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch52 = &match;
                                {
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftAnd.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch52 = match;
                                }
                                *parentMatch50 = match;
                            }
                            *parentMatch49 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch53 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch53 = match;
                            }
                            *parentMatch49 = match;
                        }
                        *parentMatch48 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch54 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightAnd.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch54 = match;
                        }
                        *parentMatch48 = match;
                    }
                    *parentMatch47 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::AndInstruction(sp, result, leftAnd.release(), rightAnd.release()));
                    }
                }
                *parentMatch46 = match;
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
            soul::parser::Match* parentMatch55 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch56 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch57 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch58 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch59 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch60 = &match;
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
                                        sp = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch60 = match;
                                }
                                *parentMatch59 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch61 = &match;
                                {
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftOr.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch61 = match;
                                }
                                *parentMatch59 = match;
                            }
                            *parentMatch58 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch62 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch62 = match;
                            }
                            *parentMatch58 = match;
                        }
                        *parentMatch57 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch63 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightOr.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch63 = match;
                        }
                        *parentMatch57 = match;
                    }
                    *parentMatch56 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::OrInstruction(sp, result, leftOr.release(), rightOr.release()));
                    }
                }
                *parentMatch55 = match;
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
            soul::parser::Match* parentMatch64 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch65 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch66 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch67 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch68 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch69 = &match;
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
                                        sp = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch69 = match;
                                }
                                *parentMatch68 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch70 = &match;
                                {
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftXor.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch70 = match;
                                }
                                *parentMatch68 = match;
                            }
                            *parentMatch67 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch71 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch71 = match;
                            }
                            *parentMatch67 = match;
                        }
                        *parentMatch66 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch72 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightXor.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch72 = match;
                        }
                        *parentMatch66 = match;
                    }
                    *parentMatch65 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::XorInstruction(sp, result, leftXor.release(), rightXor.release()));
                    }
                }
                *parentMatch64 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case SHL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch73 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch74 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch75 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch76 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch77 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch78 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == SHL)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        sp = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch78 = match;
                                }
                                *parentMatch77 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch79 = &match;
                                {
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftShl.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch79 = match;
                                }
                                *parentMatch77 = match;
                            }
                            *parentMatch76 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch80 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch80 = match;
                            }
                            *parentMatch76 = match;
                        }
                        *parentMatch75 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch81 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightShl.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch81 = match;
                        }
                        *parentMatch75 = match;
                    }
                    *parentMatch74 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::ShlInstruction(sp, result, leftShl.release(), rightShl.release()));
                    }
                }
                *parentMatch73 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case SHR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch82 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch83 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch84 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch85 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch86 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch87 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == SHR)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        sp = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch87 = match;
                                }
                                *parentMatch86 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch88 = &match;
                                {
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftShr.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch88 = match;
                                }
                                *parentMatch86 = match;
                            }
                            *parentMatch85 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch89 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch89 = match;
                            }
                            *parentMatch85 = match;
                        }
                        *parentMatch84 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch90 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightShr.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch90 = match;
                        }
                        *parentMatch84 = match;
                    }
                    *parentMatch83 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::ShrInstruction(sp, result, leftShr.release(), rightShr.release()));
                    }
                }
                *parentMatch82 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case EQUAL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch91 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch92 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch93 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch94 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch95 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch96 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == EQUAL)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        sp = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch96 = match;
                                }
                                *parentMatch95 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch97 = &match;
                                {
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftEqual.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch97 = match;
                                }
                                *parentMatch95 = match;
                            }
                            *parentMatch94 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch98 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch98 = match;
                            }
                            *parentMatch94 = match;
                        }
                        *parentMatch93 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch99 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightEqual.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch99 = match;
                        }
                        *parentMatch93 = match;
                    }
                    *parentMatch92 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::EqualInstruction(sp, result, leftEqual.release(), rightEqual.release()));
                    }
                }
                *parentMatch91 = match;
            }
            if (match.hit)
            {
                *parentMatch0 = match;
            }
            break;
        }
        case LESS:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch100 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch101 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch102 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch103 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch104 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch105 = &match;
                                {
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(false);
                                    if (*lexer == LESS)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        sp = lexer.GetSourcePos(pos);
                                    }
                                    *parentMatch105 = match;
                                }
                                *parentMatch104 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch106 = &match;
                                {
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                    leftLess.reset(static_cast<otava::intermediate::Value*>(match.value));
                                    *parentMatch106 = match;
                                }
                                *parentMatch104 = match;
                            }
                            *parentMatch103 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch107 = &match;
                            {
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                *parentMatch107 = match;
                            }
                            *parentMatch103 = match;
                        }
                        *parentMatch102 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch108 = &match;
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            rightLess.reset(static_cast<otava::intermediate::Value*>(match.value));
                            *parentMatch108 = match;
                        }
                        *parentMatch102 = match;
                    }
                    *parentMatch101 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::LessInstruction(sp, result, leftLess.release(), rightLess.release()));
                    }
                }
                *parentMatch100 = match;
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BinaryInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "BinaryInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ParamInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParamInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589499);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == PARAM)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            sp = lexer.GetSourcePos(pos);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParamInstruction");
                #endif
                return soul::parser::Match(true, new otava::intermediate::ParamInstruction(sp, result));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParamInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "ParamInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::LocalInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LocalInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589500);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == LOCAL)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                sp = lexer.GetSourcePos(pos);
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                if (match.hit)
                {
                    tref = typeRef->value;
                    context->ResolveType(tref);
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LocalInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::LocalInstruction(sp, result, tref.GetType()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LocalInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "LocalInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::LoadInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "LoadInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589501);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<otava::intermediate::Value> ptr;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            int64_t pos = lexer.GetPos();
            soul::parser::Match match(false);
            if (*lexer == LOAD)
            {
                ++lexer;
                match.hit = true;
            }
            if (match.hit)
            {
                sp = lexer.GetSourcePos(pos);
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                ptr.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LoadInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::LoadInstruction(sp, result, ptr.release()));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "LoadInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "LoadInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::ElemAddrInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ElemAddrInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589502);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<otava::intermediate::Value> ptr;
    std::unique_ptr<otava::intermediate::Value> index;
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
                    soul::parser::Match match(false);
                    if (*lexer == ELEMADDR)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                    ptr.reset(static_cast<otava::intermediate::Value*>(match.value));
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                soul::parser::Match match(false);
                if (*lexer == COMMA)
                {
                    ++lexer;
                    match.hit = true;
                }
                *parentMatch5 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                index.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElemAddrInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::ElemAddrInstruction(sp, result, ptr.release(), index.release()));
                    }
                }
                *parentMatch7 = match;
            }
            *parentMatch6 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ElemAddrInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "ElemAddrInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::PtrOffsetInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PtrOffsetInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589503);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<otava::intermediate::Value> ptr;
    std::unique_ptr<otava::intermediate::Value> offset;
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
                    soul::parser::Match match(false);
                    if (*lexer == PTROFFSET)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                    ptr.reset(static_cast<otava::intermediate::Value*>(match.value));
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                soul::parser::Match match(false);
                if (*lexer == COMMA)
                {
                    ++lexer;
                    match.hit = true;
                }
                *parentMatch5 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                offset.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PtrOffsetInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::PtrOffsetInstruction(sp, result, ptr.release(), offset.release()));
                    }
                }
                *parentMatch7 = match;
            }
            *parentMatch6 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PtrOffsetInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "PtrOffsetInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::PtrDiffInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PtrDiffInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589504);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<otava::intermediate::Value> leftPtr;
    std::unique_ptr<otava::intermediate::Value> rightPtr;
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
                    soul::parser::Match match(false);
                    if (*lexer == PTRDIFF)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                    leftPtr.reset(static_cast<otava::intermediate::Value*>(match.value));
                    *parentMatch4 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                soul::parser::Match match(false);
                if (*lexer == COMMA)
                {
                    ++lexer;
                    match.hit = true;
                }
                *parentMatch5 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                rightPtr.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PtrDiffInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::PtrDiffInstruction(sp, result, leftPtr.release(), rightPtr.release()));
                    }
                }
                *parentMatch7 = match;
            }
            *parentMatch6 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PtrDiffInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "PtrDiffInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::FunctionCallInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "FunctionCallInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589505);
    otava::intermediate::TypeRef tref = otava::intermediate::TypeRef();
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<soul::parser::Value<otava::intermediate::TypeRef>> typeRef;
    std::unique_ptr<otava::intermediate::Value> callee;
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
                soul::parser::Match match(false);
                if (*lexer == CALL)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    sp = lexer.GetSourcePos(pos);
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
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::TypeRef(lexer);
                    typeRef.reset(static_cast<soul::parser::Value<otava::intermediate::TypeRef>*>(match.value));
                    if (match.hit)
                    {
                        tref = typeRef->value;
                        context->ResolveType(tref);
                    }
                    *parentMatch4 = match;
                }
                *parentMatch3 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Value(lexer, context, tref.GetType());
                callee.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionCallInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::FunctionCallInstruction(sp, result, callee.release()));
                    }
                }
                *parentMatch6 = match;
            }
            *parentMatch5 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "FunctionCallInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "FunctionCallInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::TrapInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "TrapInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589506);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    std::unique_ptr<otava::intermediate::Value> op1;
    std::unique_ptr<otava::intermediate::Value> op2;
    std::unique_ptr<otava::intermediate::Value> op3;
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
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch5 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match(false);
                            if (*lexer == TRAP)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                sp = lexer.GetSourcePos(pos);
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
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                            op1.reset(static_cast<otava::intermediate::Value*>(match.value));
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
                        if (*lexer == COMMA)
                        {
                            ++lexer;
                            match.hit = true;
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
                soul::parser::Match* parentMatch8 = &match;
                {
                    soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                    op2.reset(static_cast<otava::intermediate::Value*>(match.value));
                    *parentMatch8 = match;
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
                if (*lexer == COMMA)
                {
                    ++lexer;
                    match.hit = true;
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
        soul::parser::Match* parentMatch10 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                op3.reset(static_cast<otava::intermediate::Value*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TrapInstruction");
                        #endif
                        return soul::parser::Match(true, new otava::intermediate::TrapInstruction(sp, result, op1.release(), op2.release(), op3.release()));
                    }
                }
                *parentMatch11 = match;
            }
            *parentMatch10 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TrapInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "TrapInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::PhiInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "PhiInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589507);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    otava::intermediate::PhiInstruction* inst = nullptr;
    std::unique_ptr<soul::parser::Value<otava::intermediate::BlockValue>> first;
    std::unique_ptr<soul::parser::Value<otava::intermediate::BlockValue>> next;
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
                    if (*lexer == PHI)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    if (match.hit)
                    {
                        sp = lexer.GetSourcePos(pos);
                        inst = new otava::intermediate::PhiInstruction(sp, result);
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
                                    int64_t pos = lexer.GetPos();
                                    soul::parser::Match match = IntermediateCodeParser<Lexer>::BlockValue(lexer, context);
                                    first.reset(static_cast<soul::parser::Value<otava::intermediate::BlockValue>*>(match.value));
                                    if (match.hit)
                                    {
                                        inst->AddBlockValue(first->value);
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
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch10 = &match;
                                    {
                                        while (true)
                                        {
                                            int64_t save = lexer.GetPos();
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch11 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch12 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        if (*lexer == COMMA)
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
                                                                soul::parser::Match match = IntermediateCodeParser<Lexer>::BlockValue(lexer, context);
                                                                next.reset(static_cast<soul::parser::Value<otava::intermediate::BlockValue>*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    inst->AddBlockValue(next->value);
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
                                                    break;
                                                }
                                            }
                                        }
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PhiInstruction");
                #endif
                return soul::parser::Match(true, inst);
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PhiInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "PhiInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::BlockValue(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BlockValue");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589508);
    std::unique_ptr<otava::intermediate::Value> operand;
    std::unique_ptr<soul::parser::Value<int32_t>> blockId;
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
                            if (*lexer == LBRACKET)
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
                                soul::parser::Match match = IntermediateCodeParser<Lexer>::Operand(lexer, context);
                                operand.reset(static_cast<otava::intermediate::Value*>(match.value));
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
                            if (*lexer == COMMA)
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
                        soul::parser::Match match = IntermediateCodeParser<Lexer>::Label(lexer);
                        blockId.reset(static_cast<soul::parser::Value<int32_t>*>(match.value));
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
                    if (*lexer == RBRACKET)
                    {
                        ++lexer;
                        match.hit = true;
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BlockValue");
                #endif
                return soul::parser::Match(true, new soul::parser::Value<otava::intermediate::BlockValue>(otava::intermediate::BlockValue(operand.release(), blockId->value)));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BlockValue");
        else soul::lexer::WriteFailureToLog(lexer, "BlockValue");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::NoOperationInstruction(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "NoOperationInstruction");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589509);
    soul::ast::SourcePos sp = soul::ast::SourcePos();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == NOP)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            sp = lexer.GetSourcePos(pos);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoOperationInstruction");
                #endif
                return soul::parser::Match(true, new otava::intermediate::NoOperationInstruction(sp));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NoOperationInstruction");
        else soul::lexer::WriteFailureToLog(lexer, "NoOperationInstruction");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::Metadata(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Metadata");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589510);
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
                if (*lexer == METADATA)
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
                    soul::parser::Match match(false);
                    if (*lexer == LBRACE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
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
                soul::parser::Match match(true);
                soul::parser::Match* parentMatch5 = &match;
                {
                    while (true)
                    {
                        int64_t save = lexer.GetPos();
                        {
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataStruct(lexer, context);
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
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                    context->ResolveMetadataReferences();
                }
                *parentMatch7 = match;
            }
            *parentMatch6 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Metadata");
        else soul::lexer::WriteFailureToLog(lexer, "Metadata");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::MetadataStruct(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MetadataStruct");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589511);
    otava::intermediate::MetadataStruct* value = nullptr;
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
                        soul::parser::Match match(false);
                        if (*lexer == EXCLAMATION)
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
                                soul::parser::Match match(false);
                                if (*lexer == NUMBER)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    value = context->AddMetadataStruct(lexer.GetSourcePos(pos), lexer.GetToken(pos).ToInt(), context);
                                }
                                *parentMatch6 = match;
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
                    soul::parser::Match* parentMatch7 = &match;
                    {
                        soul::parser::Match match(false);
                        if (*lexer == ASSIGN)
                        {
                            ++lexer;
                            match.hit = true;
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
                soul::parser::Match* parentMatch8 = &match;
                {
                    soul::parser::Match match(false);
                    if (*lexer == LBRACE)
                    {
                        ++lexer;
                        match.hit = true;
                    }
                    *parentMatch8 = match;
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
                            soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataField(lexer, context, value);
                            *parentMatch12 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch13 = &match;
                            {
                                soul::parser::Match match(true);
                                soul::parser::Match* parentMatch14 = &match;
                                {
                                    while (true)
                                    {
                                        int64_t save = lexer.GetPos();
                                        {
                                            soul::parser::Match match(false);
                                            soul::parser::Match* parentMatch15 = &match;
                                            {
                                                soul::parser::Match match(false);
                                                soul::parser::Match* parentMatch16 = &match;
                                                {
                                                    soul::parser::Match match(false);
                                                    if (*lexer == COMMA)
                                                    {
                                                        ++lexer;
                                                        match.hit = true;
                                                    }
                                                    *parentMatch16 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch17 = &match;
                                                    {
                                                        soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataField(lexer, context, value);
                                                        *parentMatch17 = match;
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
                                                break;
                                            }
                                        }
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
                        *parentMatch10 = match;
                    }
                    else
                    {
                        lexer.SetPos(save);
                    }
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
        soul::parser::Match* parentMatch18 = &match;
        {
            soul::parser::Match match(false);
            if (*lexer == RBRACE)
            {
                ++lexer;
                match.hit = true;
            }
            *parentMatch18 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataStruct");
        else soul::lexer::WriteFailureToLog(lexer, "MetadataStruct");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::MetadataField(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::MetadataStruct* parent)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MetadataField");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589512);
    std::string fieldName = std::string();
    std::unique_ptr<otava::intermediate::MetadataItem> item;
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
                soul::parser::Match match(false);
                if (*lexer == ID)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    fieldName = util::ToUtf8(lexer.GetToken(pos).ToString());
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
                if (*lexer == COLON)
                {
                    ++lexer;
                    match.hit = true;
                }
                *parentMatch3 = match;
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
            soul::parser::Match* parentMatch5 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataItem(lexer, context);
                item.reset(static_cast<otava::intermediate::MetadataItem*>(match.value));
                if (match.hit)
                {
                    parent->AddItem(fieldName, item.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataField");
        else soul::lexer::WriteFailureToLog(lexer, "MetadataField");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::MetadataItem(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MetadataItem");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589513);
    std::unique_ptr<otava::intermediate::MetadataItem> mdBool;
    std::unique_ptr<otava::intermediate::MetadataItem> mdLong;
    std::unique_ptr<otava::intermediate::MetadataItem> mdString;
    std::unique_ptr<otava::intermediate::MetadataRef> mdRef;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case FALSE:
        case TRUE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataBool(lexer, context);
                mdBool.reset(static_cast<otava::intermediate::MetadataItem*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataItem");
                        #endif
                        return soul::parser::Match(true, mdBool.release());
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
        case NUMBER:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataLong(lexer, context);
                mdLong.reset(static_cast<otava::intermediate::MetadataItem*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataItem");
                        #endif
                        return soul::parser::Match(true, mdLong.release());
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
        case STRING:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataString(lexer, context);
                mdString.reset(static_cast<otava::intermediate::MetadataItem*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataItem");
                        #endif
                        return soul::parser::Match(true, mdString.release());
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
        case EXCLAMATION:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match = IntermediateCodeParser<Lexer>::MetadataRef(lexer, context);
                mdRef.reset(static_cast<otava::intermediate::MetadataRef*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataItem");
                        #endif
                        return soul::parser::Match(true, mdRef.release());
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataItem");
        else soul::lexer::WriteFailureToLog(lexer, "MetadataItem");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::MetadataBool(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MetadataBool");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589514);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case TRUE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == TRUE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataBool");
                        #endif
                        return soul::parser::Match(true, context->CreateMetadataBool(true));
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
        case FALSE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == FALSE)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataBool");
                        #endif
                        return soul::parser::Match(true, context->CreateMetadataBool(false));
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataBool");
        else soul::lexer::WriteFailureToLog(lexer, "MetadataBool");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::MetadataLong(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MetadataLong");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589515);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == NUMBER)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataLong");
                #endif
                return soul::parser::Match(true, context->CreateMetadataLong(lexer.GetToken(pos).ToLong()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataLong");
        else soul::lexer::WriteFailureToLog(lexer, "MetadataLong");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::MetadataString(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MetadataString");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589516);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        soul::parser::Match match(false);
        if (*lexer == STRING)
        {
            ++lexer;
            match.hit = true;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataString");
                #endif
                return soul::parser::Match(true, context->CreateMetadataString(util::ToUtf8(lexer.GetToken(pos).ToString())));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataString");
        else soul::lexer::WriteFailureToLog(lexer, "MetadataString");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match IntermediateCodeParser<Lexer>::MetadataRef(Lexer& lexer, otava::intermediate::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "MetadataRef");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 9185574142806589517);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        soul::parser::Match match(false);
        if (*lexer == EXCLAMATION)
        {
            ++lexer;
            match.hit = true;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NUMBER)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataRef");
                        #endif
                        return soul::parser::Match(true, context->CreateMetadataRef(lexer.GetSourcePos(pos), lexer.GetToken(pos).ToInt()));
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "MetadataRef");
        else soul::lexer::WriteFailureToLog(lexer, "MetadataRef");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct IntermediateCodeParser<soul::lexer::Lexer<otava::intermediate::lexer::IntermediateCodeLexer<char32_t>, char32_t>>;

} // namespace otava::intermediate::code::parser
