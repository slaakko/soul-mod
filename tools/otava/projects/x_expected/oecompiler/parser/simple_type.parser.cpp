
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/simple_type.parser' using soul parser generator ospg version 5.0.0

module otava.parser.simple.type;

import util;
import soul.ast.spg;
import soul.ast.common;
import otava.ast;
import otava.token;
import otava.lexer;

namespace otava::parser::simple::type {

template<typename LexerT>
std::expected<soul::parser::Match, int> SimpleTypeParser<LexerT>::SimpleType(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SimpleType");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 695727793635328001);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case otava::token::CHAR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::CHAR)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::CharNode(*sp));
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
        case otava::token::CHAR8_T:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::CHAR8_T)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::Char8Node(*sp));
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
        case otava::token::CHAR16_T:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::CHAR16_T)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::Char16Node(*sp));
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
        case otava::token::CHAR32_T:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::CHAR32_T)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::Char32Node(*sp));
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
        case otava::token::WCHAR_T:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::WCHAR_T)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::WCharNode(*sp));
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
        case otava::token::BOOL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::BOOL)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::BoolNode(*sp));
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
        case otava::token::SHORT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::SHORT)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::ShortNode(*sp));
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
        case otava::token::INT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch8 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::INT)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::IntNode(*sp));
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
        case otava::token::LONG:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch9 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::LONG)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::LongNode(*sp));
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
        case otava::token::SIGNED:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch10 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::SIGNED)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::SignedNode(*sp));
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
        case otava::token::UNSIGNED:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch11 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::UNSIGNED)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::UnsignedNode(*sp));
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
        case otava::token::FLOAT:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch12 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::FLOAT)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::FloatNode(*sp));
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
        case otava::token::DOUBLE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch13 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::DOUBLE)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::DoubleNode(*sp));
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
        case otava::token::VOID:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch14 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == otava::token::VOID)
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
                        #endif
                        return soul::parser::Match(true, new otava::ast::VoidNode(*sp));
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleType");
        else soul::lexer::WriteFailureToLog(lexer, "SimpleType");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct SimpleTypeParser<soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>>;

} // namespace otava::parser::simple::type
