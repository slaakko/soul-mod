
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/identifier_parser.parser' using soul parser generator spg version 4.0.0

module minilang.parser.identifier;

import util;
import soul.ast.spg;
import minilang.ast;
import minilang.lexer;
import minilang.token;

using namespace minilang::ast;
using namespace minilang::lexer;
using namespace minilang::token;

namespace minilang::parser::identifier {

template<typename Lexer>
soul::parser::Match IdentifierParser<Lexer>::Identifier(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Identifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 2933912217394872321);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
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
            auto token = lexer.GetToken(pos);
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Identifier");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new minilang::ast::IdentifierNode(token.ToString()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Identifier");
        else soul::lexer::WriteFailureToLog(lexer, "Identifier");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct IdentifierParser<soul::lexer::Lexer<minilang::lexer::MinilangLexer<char32_t>, char32_t>>;

} // namespace minilang::parser::identifier
