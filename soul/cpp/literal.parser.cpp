
// this file has been automatically generated from 'D:/work/soul-mod/soul/cpp/literal.parser' using soul parser generator spg version 5.0.0

module soul.cpp.literal.parser;

import util;
import soul.ast.spg;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.tool.token;
import soul.punctuation.token;
import soul.lex.slg;
import soul.lex.spg;

using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::tool::token;
using namespace soul::punctuation::token;
using namespace soul::lex::slg;
using namespace soul::lex::spg;

namespace soul::cpp::literal::parser {

template<typename LexerT>
soul::parser::Match LiteralParser<LexerT>::Literal(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "Literal");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 5808325801866690561);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    switch (*lexer)
    {
        case INTEGER_LITERAL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch1 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == INTEGER_LITERAL)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                        #endif
                        return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        case FLOATING_LITERAL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == FLOATING_LITERAL)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                        #endif
                        return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        case CHAR_LITERAL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == CHAR_LITERAL)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                        #endif
                        return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        case STRING_LITERAL:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch4 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == STRING_LITERAL)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                        #endif
                        return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        case TRUE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch5 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                        #endif
                        return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        case FALSE:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch6 = &match;
            {
                std::int64_t pos = lexer.GetPos();
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
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                        #endif
                        return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
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
        case NULLPTR:
        {
            soul::parser::Match match(false);
            soul::parser::Match* parentMatch7 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul::parser::Match match(false);
                if (*lexer == NULLPTR)
                {
                    ++lexer;
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                        #endif
                        return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
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
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
        else soul::lexer::WriteFailureToLog(lexer, "Literal");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct LiteralParser<soul::lexer::Lexer<soul::lex::slg::SlgLexer<char32_t>, char32_t>>;
template struct LiteralParser<soul::lexer::Lexer<soul::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul::cpp::literal::parser
