
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/source_file.parser' using soul parser generator spg version 4.0.0

module minilang.parser.source.file;

import util;
import soul.ast.spg;
import minilang.lexer;
import minilang.token;
import minilang.parser.function;

using namespace minilang::lexer;
using namespace minilang::token;
using namespace minilang::parser::function;

namespace minilang::parser::source::file {

template<typename Lexer>
std::unique_ptr<minilang::ast::SourceFileNode> SourceFileParser<Lexer>::Parse(Lexer& lexer)
{
    std::unique_ptr<minilang::ast::SourceFileNode> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    ++lexer;
    soul::parser::Match match = SourceFileParser<Lexer>::SourceFile(lexer);
    value.reset(static_cast<minilang::ast::SourceFileNode*>(match.value));
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->DecIndent();
        lexer.Log()->WriteEndRule("parse");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (match.hit)
    {
        if (*lexer == soul::lexer::END_TOKEN)
        {
            return value;
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
    return value;
}

template<typename Lexer>
soul::parser::Match SourceFileParser<Lexer>::SourceFile(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "SourceFile");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 604673310139088897);
    std::unique_ptr<minilang::ast::SourceFileNode> sourceFile = std::unique_ptr<minilang::ast::SourceFileNode>();
    std::unique_ptr<minilang::ast::FunctionNode> function;
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
                    soul::parser::Match match(true);
                    if (match.hit)
                    {
                        sourceFile.reset(new minilang::ast::SourceFileNode);
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
                                        soul::parser::Match match = FunctionParser<Lexer>::Function(lexer);
                                        function.reset(static_cast<minilang::ast::FunctionNode*>(match.value));
                                        if (match.hit)
                                        {
                                            sourceFile->AddFunction(function.release());
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
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SourceFile");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, sourceFile.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SourceFile");
        else soul::lexer::WriteFailureToLog(lexer, "SourceFile");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct SourceFileParser<soul::lexer::Lexer<minilang::lexer::MinilangLexer<char32_t>, char32_t>>;

} // namespace minilang::parser::source::file
