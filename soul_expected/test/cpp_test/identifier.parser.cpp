
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/test/cpp_test/identifier.parser' using soul parser generator espg version 5.0.0

module soul_expected.cpp.identifier.parser;

import util_expected;
import soul_expected.ast.spg;
import soul_expected.cpp.token;
import soul_expected.cpp.op.token;
import soul_expected.tool.token;
import soul_expected.punctuation.token;
import soul_expected.lex.slg;
import soul_expected.lex.spg;

using namespace soul_expected::cpp::token;
using namespace soul_expected::cpp::op::token;
using namespace soul_expected::tool::token;
using namespace soul_expected::punctuation::token;
using namespace soul_expected::lex::slg;
using namespace soul_expected::lex::spg;

namespace soul_expected::cpp::identifier::parser {

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> CppIdentifierParser<LexerT>::CppIdentifier(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "CppIdentifier");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 267984059232157697);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        if (*lexer == ID)
        {
            auto a = ++lexer;
            if (!a) return std::unexpected<int>(a.error());
            match.hit = true;
        }
        if (match.hit)
        {
            auto u = lexer.TokenToUtf8(pos);
            if (!u) return std::unexpected<int>(u.error());
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CppIdentifier");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(*u));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CppIdentifier");
        else soul_expected::lexer::WriteFailureToLog(lexer, "CppIdentifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> CppIdentifierParser<LexerT>::QualifiedCppId(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "QualifiedCppId");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 267984059232157698);
    std::string str = std::string();
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul_expected::parser::Match match(false);
                                if (*lexer == COLON_COLON)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    str.append("::");
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
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch7 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch8 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            if (*lexer == ID)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                auto u = lexer.TokenToUtf8(pos);
                                if (!u) return std::unexpected<int>(u.error());
                                str.append(*u);
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch9 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch10 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch11 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch12 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == COLON_COLON)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch12 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch13 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch14 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul_expected::parser::Match match(false);
                                                if (*lexer == ID)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    auto u = lexer.TokenToUtf8(pos);
                                                    if (!u) return std::unexpected<int>(u.error());
                                                    str.append("::").append(*u);
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "QualifiedCppId");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "QualifiedCppId");
        else soul_expected::lexer::WriteFailureToLog(lexer, "QualifiedCppId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct CppIdentifierParser<soul_expected::lexer::Lexer<soul_expected::lex::slg::SlgLexer<char32_t>, char32_t>>;
template struct CppIdentifierParser<soul_expected::lexer::Lexer<soul_expected::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul_expected::cpp::identifier::parser
