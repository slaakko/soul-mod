
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/literal.parser' using soul parser generator spg version 5.0.0

module minilang.parser.literal;

import util;
import soul.ast.spg;
import minilang.ast;
import minilang.lexer;
import minilang.token;

using namespace minilang::ast;
using namespace minilang::lexer;
using namespace minilang::token;

namespace minilang::parser::literal {

template<typename LexerT>
soul::parser::Match LiteralParser<LexerT>::Literal(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Literal");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2710058753855586305);
    std::unique_ptr<minilang::ast::Node> booleanLiteral;
    std::unique_ptr<minilang::ast::Node> integerLiteral;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul::parser::Match match(false);
        soul::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul::parser::Match match = LiteralParser<LexerT>::BooleanLiteral(lexer);
            booleanLiteral.reset(static_cast<minilang::ast::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                    #endif
                    return soul::parser::Match(true, booleanLiteral.release());
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
                    soul::parser::Match match = LiteralParser<LexerT>::IntegerLiteral(lexer);
                    integerLiteral.reset(static_cast<minilang::ast::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Literal");
                            #endif
                            return soul::parser::Match(true, integerLiteral.release());
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

template<typename LexerT>
soul::parser::Match LiteralParser<LexerT>::BooleanLiteral(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "BooleanLiteral");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2710058753855586306);
    soul::parser::Match match(false);
    std::int64_t pos = lexer.GetPos();
    switch (*lexer)
    {
        case TRUE:
        {
            ++lexer;
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BooleanLiteral");
                    #endif
                    return soul::parser::Match(true, new minilang::ast::BooleanLiteralNode(true));
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
                    if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BooleanLiteral");
                    #endif
                    return soul::parser::Match(true, new minilang::ast::BooleanLiteralNode(false));
                }
            }
            break;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BooleanLiteral");
        else soul::lexer::WriteFailureToLog(lexer, "BooleanLiteral");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match LiteralParser<LexerT>::IntegerLiteral(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "IntegerLiteral");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 2710058753855586307);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
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
            auto token = lexer.GetToken(pos);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IntegerLiteral");
                #endif
                return soul::parser::Match(true, new minilang::ast::IntegerLiteralNode(token.ToLong()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "IntegerLiteral");
        else soul::lexer::WriteFailureToLog(lexer, "IntegerLiteral");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct LiteralParser<soul::lexer::Lexer<minilang::lexer::MinilangLexer<char32_t>, char32_t>>;

} // namespace minilang::parser::literal
