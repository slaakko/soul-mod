
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/function_parser.parser' using soul parser generator spg version 4.0.0

module minilang.parser.function;

import util;
import soul.ast.spg;
import minilang.lexer;
import minilang.token;
import minilang.parser.type;
import minilang.parser.identifier;
import minilang.parser.statement;

using namespace minilang::lexer;
using namespace minilang::token;
using namespace minilang::parser::type;
using namespace minilang::parser::identifier;
using namespace minilang::parser::statement;

namespace minilang::parser::function {

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::Function(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Function");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 1162212618379722753);
    std::unique_ptr<minilang::ast::FunctionNode> function = std::unique_ptr<minilang::ast::FunctionNode>();
    std::unique_ptr<minilang::ast::Node> returnType;
    std::unique_ptr<minilang::ast::IdentifierNode> functionName;
    std::unique_ptr<minilang::ast::CompoundStatementNode> functionBody;
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
                                soul::parser::Match match = TypeParser<Lexer>::Type(lexer);
                                returnType.reset(static_cast<minilang::ast::Node*>(match.value));
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer);
                                        functionName.reset(static_cast<minilang::ast::IdentifierNode*>(match.value));
                                        if (match.hit)
                                        {
                                            *parentMatch8 = match;
                                        }
                                        else
                                        {
                                            lexer.ThrowExpectationFailure(pos, "Identifier");
                                        }
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
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
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch11 = &match;
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
                                            *parentMatch11 = match;
                                        }
                                        else
                                        {
                                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LPAREN));
                                        }
                                    }
                                    if (match.hit)
                                    {
                                        function.reset(new minilang::ast::FunctionNode(returnType.release(), functionName.release()));
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch9 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
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
                                soul::parser::Match match = FunctionParser<Lexer>::ParameterList(lexer, function.get());
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
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch14 = &match;
                    {
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch15 = &match;
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
                                *parentMatch15 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RPAREN));
                            }
                        }
                        *parentMatch14 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
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
                        soul::parser::Match match(true);
                        soul::parser::Match* parentMatch18 = &match;
                        {
                            int64_t pos = lexer.GetPos();
                            soul::parser::Match match = StatementParser<Lexer>::CompoundStatement(lexer);
                            functionBody.reset(static_cast<minilang::ast::CompoundStatementNode*>(match.value));
                            if (match.hit)
                            {
                                *parentMatch18 = match;
                            }
                            else
                            {
                                lexer.ThrowExpectationFailure(pos, "CompoundStatement");
                            }
                        }
                        if (match.hit)
                        {
                            function->SetBody(functionBody.release());
                        }
                        *parentMatch17 = match;
                    }
                    *parentMatch16 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Function");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, function.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Function");
        else soul::lexer::WriteFailureToLog(lexer, "Function");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::ParameterList(Lexer& lexer, minilang::ast::FunctionNode* function)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "ParameterList");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 1162212618379722754);
    std::unique_ptr<minilang::ast::ParameterNode> left;
    std::unique_ptr<minilang::ast::ParameterNode> right;
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
                soul::parser::Match match = FunctionParser<Lexer>::Parameter(lexer);
                left.reset(static_cast<minilang::ast::ParameterNode*>(match.value));
                if (match.hit)
                {
                    function->AddParam(left.release());
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
                soul::parser::Match* parentMatch4 = &match;
                {
                    while (true)
                    {
                        int64_t save = lexer.GetPos();
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch5 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch6 = &match;
                                {
                                    soul::parser::Match match(false);
                                    if (*lexer == COMMA)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    *parentMatch6 = match;
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
                                            soul::parser::Match match(true);
                                            soul::parser::Match* parentMatch9 = &match;
                                            {
                                                int64_t pos = lexer.GetPos();
                                                soul::parser::Match match = FunctionParser<Lexer>::Parameter(lexer);
                                                right.reset(static_cast<minilang::ast::ParameterNode*>(match.value));
                                                if (match.hit)
                                                {
                                                    *parentMatch9 = match;
                                                }
                                                else
                                                {
                                                    lexer.ThrowExpectationFailure(pos, "Parameter");
                                                }
                                            }
                                            if (match.hit)
                                            {
                                                function->AddParam(right.release());
                                            }
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch7 = match;
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
                                break;
                            }
                        }
                    }
                }
                *parentMatch3 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "ParameterList");
        else soul::lexer::WriteFailureToLog(lexer, "ParameterList");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename Lexer>
soul::parser::Match FunctionParser<Lexer>::Parameter(Lexer& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::WriteBeginRuleToLog(lexer, "Parameter");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    soul::lexer::RuleGuard ruleGuard(lexer, 1162212618379722755);
    std::unique_ptr<minilang::ast::Node> type;
    std::unique_ptr<minilang::ast::IdentifierNode> name;
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
                soul::parser::Match match = TypeParser<Lexer>::Type(lexer);
                type.reset(static_cast<minilang::ast::Node*>(match.value));
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch3 = &match;
                {
                    soul::parser::Match match = IdentifierParser<Lexer>::Identifier(lexer);
                    name.reset(static_cast<minilang::ast::IdentifierNode*>(match.value));
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Parameter");
                #endif SOUL_PARSER_DEBUG_SUPPORT
                return soul::parser::Match(true, new minilang::ast::ParameterNode(type.release(), name.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Parameter");
        else soul::lexer::WriteFailureToLog(lexer, "Parameter");
    }
    #endif // SOUL_PARSER_DEBUG_SUPPORT
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct FunctionParser<soul::lexer::Lexer<minilang::lexer::MinilangLexer<char32_t>, char32_t>>;

} // namespace minilang::parser::function
