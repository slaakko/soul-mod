
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp/literal.parser' using soul parser generator spg version 4.1.0

module soul.cpp.literal.parser;

import util;
import soul.ast.spg;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.lex.slg;
import soul.lex.spg;

using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::lex::slg;
using namespace soul::lex::spg;

namespace soul::cpp::literal::parser {

template<typename Lexer>
soul::parser::Match LiteralParser<Lexer>::Literal(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Literal");
    }
    #endif
    soul::lexer::RuleGuard ruleGuard(lexer, 5808325801866690561);
    soul::parser::Match match(false);
    int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case INTEGER_LITERAL:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                    #endif
                    return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
                }
            }
            break;
        }
        case FLOATING_LITERAL:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                    #endif
                    return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
                }
            }
            break;
        }
        case CHAR_LITERAL:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                    #endif
                    return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
                }
            }
            break;
        }
        case STRING_LITERAL:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                    #endif
                    return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
                }
            }
            break;
        }
        case TRUE:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                    #endif
                    return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
                }
            }
            break;
        }
        case FALSE:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                    #endif
                    return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
                }
            }
            break;
        }
        case NULLPTR:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                    #endif
                    return soul::parser::Match(true, new soul::ast::cpp::LiteralNode(lexer.GetSourcePos(pos), util::ToUtf8(lexer.GetToken(pos).ToString())));
                }
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
