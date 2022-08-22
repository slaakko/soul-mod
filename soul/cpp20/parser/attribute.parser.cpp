
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/attribute.parser' using soul parser generator spg version 4.1.0

module soul.cpp20.parser.attribute;

import util;
import soul.ast.spg;
import soul.cpp20.token;
import soul.cpp20.lexer;
import soul.cpp20.parser.expression;
import soul.cpp20.parser.punctuation;

using namespace soul::cpp20::token;
using namespace soul::cpp20::lexer;
using namespace soul::cpp20::parser::expression;
using namespace soul::cpp20::parser::punctuation;

namespace soul::cpp20::parser::attribute {

template<typename Lexer>
soul::parser::Match AttributeParser<Lexer>::AttributeSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "AttributeSpecifierSeq");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 5156478082776825857);
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        int64_t pos = lexer.GetPos();
        bool pass = true;
        soul::parser::Match match(true);
        if (match.hit)
        {
            pass = false;
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AttributeSpecifierSeq");
        else soul::lexer::WriteFailureToLog(lexer, "AttributeSpecifierSeq");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct AttributeParser<soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>>;

} // namespace soul::cpp20::parser::attribute
