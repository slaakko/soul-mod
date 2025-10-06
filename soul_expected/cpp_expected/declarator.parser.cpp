
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/cpp_expected/declarator.parser' using soul parser generator espg version 5.0.0

module soul_expected.cpp.declarator.parser;

import util_expected;
import soul_expected.ast.spg;
import soul_expected.cpp.token;
import soul_expected.cpp.op.token;
import soul_expected.tool.token;
import soul_expected.punctuation.token;
import soul_expected.cpp.declaration.parser;
import soul_expected.cpp.expression.parser;
import soul_expected.lex.slg;
import soul_expected.lex.spg;

namespace soul_expected::cpp::declarator::parser {

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::InitDeclaratorList(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "InitDeclaratorList");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344001);
    std::unique_ptr<soul_expected::ast::cpp::InitDeclaratorListNode> initDeclaratorList = std::unique_ptr<soul_expected::ast::cpp::InitDeclaratorListNode>();
    std::unique_ptr<soul_expected::ast::cpp::InitDeclaratorNode> initDeclarator;
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
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(true);
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        initDeclaratorList.reset(new soul_expected::ast::cpp::InitDeclaratorListNode(*sp));
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch6 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch7 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::InitDeclarator(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                initDeclarator.reset(static_cast<soul_expected::ast::cpp::InitDeclaratorNode*>(match.value));
                                if (match.hit)
                                {
                                    initDeclaratorList->Add(initDeclarator.release());
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch6 = match;
                        }
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch8 = &match;
                            {
                                soul_expected::parser::Match match(true);
                                soul_expected::parser::Match* parentMatch9 = &match;
                                {
                                    while (true)
                                    {
                                        std::int64_t save = lexer.GetPos();
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch10 = &match;
                                            {
                                                soul_expected::parser::Match match(false);
                                                if (*lexer == soul_expected::punctuation::token::COMMA)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                *parentMatch10 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch11 = &match;
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch12 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::InitDeclarator(lexer, context);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul_expected::parser::Match match = *m;
                                                        initDeclarator.reset(static_cast<soul_expected::ast::cpp::InitDeclaratorNode*>(match.value));
                                                        if (match.hit)
                                                        {
                                                            initDeclaratorList->Add(initDeclarator.release());
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitDeclaratorList");
                #endif
                return soul_expected::parser::Match(true, initDeclaratorList.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitDeclaratorList");
        else soul_expected::lexer::WriteFailureToLog(lexer, "InitDeclaratorList");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::InitDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "InitDeclarator");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344002);
    std::unique_ptr<soul_expected::parser::Value<std::string>> declarator;
    std::unique_ptr<soul_expected::ast::cpp::InitializerNode> initializer;
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
                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::Declarator(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                declarator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    soul_expected::parser::Match match(true);
                    std::int64_t save = lexer.GetPos();
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::Initializer(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        initializer.reset(static_cast<soul_expected::ast::cpp::InitializerNode*>(match.value));
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            auto sp = lexer.GetSourcePos(pos);
            if (!sp) return std::unexpected<int>(sp.error());
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitDeclarator");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::InitDeclaratorNode(*sp, declarator->value, initializer.release()));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitDeclarator");
        else soul_expected::lexer::WriteFailureToLog(lexer, "InitDeclarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::Declarator(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Declarator");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344003);
    std::string str = std::string();
    std::unique_ptr<soul_expected::parser::Value<std::string>> directDeclarator;
    std::unique_ptr<soul_expected::parser::Value<std::string>> ptrOperator;
    std::unique_ptr<soul_expected::parser::Value<std::string>> declarator;
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
                std::int64_t save = lexer.GetPos();
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::DirectDeclarator(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    directDeclarator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                    if (match.hit)
                    {
                        str.append(directDeclarator->value);
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    lexer.SetPos(save);
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::PtrOperator(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                ptrOperator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                if (match.hit)
                                {
                                    str.append(ptrOperator->value);
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
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
                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::Declarator(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    declarator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                    if (match.hit)
                                    {
                                        str.append(declarator->value);
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Declarator");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Declarator");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Declarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::DirectDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "DirectDeclarator");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344004);
    std::string str = std::string();
    std::unique_ptr<soul_expected::parser::Value<std::string>> declaratorId;
    std::unique_ptr<soul_expected::ast::cpp::Node> expr;
    std::unique_ptr<soul_expected::parser::Value<std::string>> declarator;
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
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::DeclaratorId(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    declaratorId.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                    if (match.hit)
                    {
                        str.append(declaratorId->value);
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(true);
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        while (true)
                        {
                            std::int64_t save = lexer.GetPos();
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch6 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch7 = &match;
                                    switch (*lexer)
                                    {
                                        case soul_expected::punctuation::token::LBRACKET:
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch8 = &match;
                                            {
                                                std::int64_t save = lexer.GetPos();
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch9 = &match;
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch10 = &match;
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        if (*lexer == soul_expected::punctuation::token::LBRACKET)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        *parentMatch10 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch11 = &match;
                                                        {
                                                            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::expression::parser::ExpressionParser<LexerT>::ConstantExpression(lexer, context);
                                                            if (!m) return std::unexpected<int>(m.error());
                                                            soul_expected::parser::Match match = *m;
                                                            expr.reset(static_cast<soul_expected::ast::cpp::Node*>(match.value));
                                                            *parentMatch11 = match;
                                                        }
                                                        *parentMatch10 = match;
                                                    }
                                                    *parentMatch9 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch12 = &match;
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch13 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul_expected::parser::Match match(false);
                                                            if (*lexer == soul_expected::punctuation::token::RBRACKET)
                                                            {
                                                                auto a = ++lexer;
                                                                if (!a) return std::unexpected<int>(a.error());
                                                                match.hit = true;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                str.append("[").append(expr.release()->ToString()).append("]");
                                                            }
                                                            *parentMatch13 = match;
                                                        }
                                                        *parentMatch12 = match;
                                                    }
                                                    *parentMatch9 = match;
                                                }
                                                *parentMatch8 = match;
                                                if (!match.hit)
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch14 = &match;
                                                    lexer.SetPos(save);
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch15 = &match;
                                                        {
                                                            soul_expected::parser::Match match(false);
                                                            if (*lexer == soul_expected::punctuation::token::LBRACKET)
                                                            {
                                                                auto a = ++lexer;
                                                                if (!a) return std::unexpected<int>(a.error());
                                                                match.hit = true;
                                                            }
                                                            *parentMatch15 = match;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            soul_expected::parser::Match match(false);
                                                            soul_expected::parser::Match* parentMatch16 = &match;
                                                            {
                                                                soul_expected::parser::Match match(false);
                                                                soul_expected::parser::Match* parentMatch17 = &match;
                                                                {
                                                                    std::int64_t pos = lexer.GetPos();
                                                                    soul_expected::parser::Match match(false);
                                                                    if (*lexer == soul_expected::punctuation::token::RBRACKET)
                                                                    {
                                                                        auto a = ++lexer;
                                                                        if (!a) return std::unexpected<int>(a.error());
                                                                        match.hit = true;
                                                                    }
                                                                    if (match.hit)
                                                                    {
                                                                        str.append("[]");
                                                                    }
                                                                    *parentMatch17 = match;
                                                                }
                                                                *parentMatch16 = match;
                                                            }
                                                            *parentMatch15 = match;
                                                        }
                                                        *parentMatch14 = match;
                                                    }
                                                    *parentMatch8 = match;
                                                }
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
                                        case soul_expected::punctuation::token::LPAREN:
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch18 = &match;
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch19 = &match;
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    if (*lexer == soul_expected::punctuation::token::LPAREN)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    *parentMatch19 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch20 = &match;
                                                    {
                                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::Declarator(lexer, context);
                                                        if (!m) return std::unexpected<int>(m.error());
                                                        soul_expected::parser::Match match = *m;
                                                        declarator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                                        *parentMatch20 = match;
                                                    }
                                                    *parentMatch19 = match;
                                                }
                                                *parentMatch18 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch21 = &match;
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch22 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul_expected::parser::Match match(false);
                                                        if (*lexer == soul_expected::punctuation::token::RPAREN)
                                                        {
                                                            auto a = ++lexer;
                                                            if (!a) return std::unexpected<int>(a.error());
                                                            match.hit = true;
                                                        }
                                                        if (match.hit)
                                                        {
                                                            str.append("(").append(declarator->value).append(")");
                                                        }
                                                        *parentMatch22 = match;
                                                    }
                                                    *parentMatch21 = match;
                                                }
                                                *parentMatch18 = match;
                                            }
                                            if (match.hit)
                                            {
                                                *parentMatch7 = match;
                                            }
                                            break;
                                        }
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DirectDeclarator");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DirectDeclarator");
        else soul_expected::lexer::WriteFailureToLog(lexer, "DirectDeclarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::DeclaratorId(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "DeclaratorId");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344005);
    std::unique_ptr<soul_expected::ast::cpp::Node> idExpr;
    std::unique_ptr<soul_expected::ast::cpp::TypeNameNode> typeName;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::expression::parser::ExpressionParser<LexerT>::IdExpression(lexer, context);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            idExpr.reset(static_cast<soul_expected::ast::cpp::Node*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclaratorId");
                    #endif
                    return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(idExpr.release()->ToString()));
                }
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declaration::parser::DeclarationParser<LexerT>::TypeName(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    typeName.reset(static_cast<soul_expected::ast::cpp::TypeNameNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclaratorId");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(typeName.release()->ToString()));
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclaratorId");
        else soul_expected::lexer::WriteFailureToLog(lexer, "DeclaratorId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::TypeId(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "TypeId");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344006);
    std::unique_ptr<soul_expected::ast::cpp::TypeIdNode> typeId = std::unique_ptr<soul_expected::ast::cpp::TypeIdNode>();
    std::unique_ptr<soul_expected::ast::cpp::TypeNameNode> typeName;
    std::unique_ptr<soul_expected::parser::Value<std::string>> abstractDeclarator;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul_expected::parser::Match match(true);
            if (match.hit)
            {
                typeId.reset(new soul_expected::ast::cpp::TypeIdNode(*lexer.GetSourcePos(pos)));
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch2 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch6 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch7 = &match;
                            {
                                std::int64_t save = lexer.GetPos();
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::TypeSpecifierSeq(lexer, context, typeId.get());
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                *parentMatch7 = match;
                                if (!match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch9 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declaration::parser::DeclarationParser<LexerT>::TypeName(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul_expected::parser::Match match = *m;
                                            typeName.reset(static_cast<soul_expected::ast::cpp::TypeNameNode*>(match.value));
                                            if (match.hit)
                                            {
                                                typeId->Add(typeName.release());
                                            }
                                            *parentMatch9 = match;
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                            }
                            *parentMatch6 = match;
                        }
                        *parentMatch5 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch10 = &match;
                        {
                            soul_expected::parser::Match match(true);
                            std::int64_t save = lexer.GetPos();
                            soul_expected::parser::Match* parentMatch11 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch12 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch13 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::AbstractDeclarator(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        abstractDeclarator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                        if (match.hit)
                                        {
                                            typeId->SetDeclarator(abstractDeclarator->value);
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
                                }
                            }
                            *parentMatch10 = match;
                        }
                        *parentMatch5 = match;
                    }
                    *parentMatch4 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeId");
                        #endif
                        return soul_expected::parser::Match(true, typeId.release());
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeId");
        else soul_expected::lexer::WriteFailureToLog(lexer, "TypeId");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::Type(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Type");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344007);
    std::unique_ptr<soul_expected::ast::cpp::TypeNode> type = std::unique_ptr<soul_expected::ast::cpp::TypeNode>();
    std::unique_ptr<soul_expected::ast::cpp::TypeSpecifierNode> typeSpecifier;
    std::unique_ptr<soul_expected::ast::cpp::TypeNameNode> typeName;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul_expected::parser::Match match(true);
            if (match.hit)
            {
                auto sp = lexer.GetSourcePos(pos);
                if (!sp) return std::unexpected<int>(sp.error());
                type.reset(new soul_expected::ast::cpp::TypeNode(*sp));
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch2 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch3 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        std::int64_t save = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch6 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch7 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch8 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declaration::parser::DeclarationParser<LexerT>::TypeSpecifier(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    typeSpecifier.reset(static_cast<soul_expected::ast::cpp::TypeSpecifierNode*>(match.value));
                                    if (match.hit)
                                    {
                                        type->Add(typeSpecifier.release());
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
                            }
                            *parentMatch6 = match;
                        }
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(true);
                            soul_expected::parser::Match* parentMatch9 = &match;
                            while (true)
                            {
                                std::int64_t save = lexer.GetPos();
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch10 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch11 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declaration::parser::DeclarationParser<LexerT>::TypeSpecifier(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul_expected::parser::Match match = *m;
                                            typeSpecifier.reset(static_cast<soul_expected::ast::cpp::TypeSpecifierNode*>(match.value));
                                            if (match.hit)
                                            {
                                                type->Add(typeSpecifier.release());
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
                        *parentMatch5 = match;
                        if (!match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch12 = &match;
                            lexer.SetPos(save);
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch13 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declaration::parser::DeclarationParser<LexerT>::TypeName(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    typeName.reset(static_cast<soul_expected::ast::cpp::TypeNameNode*>(match.value));
                                    if (match.hit)
                                    {
                                        type->Add(typeName.release());
                                    }
                                    *parentMatch13 = match;
                                }
                                *parentMatch12 = match;
                            }
                            *parentMatch5 = match;
                        }
                    }
                    *parentMatch4 = match;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Type");
                        #endif
                        return soul_expected::parser::Match(true, type.release());
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Type");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Type");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::TypeSpecifierSeq(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::TypeIdNode* typeId)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "TypeSpecifierSeq");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344008);
    std::unique_ptr<soul_expected::ast::cpp::TypeSpecifierNode> typeSpecifier;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declaration::parser::DeclarationParser<LexerT>::TypeSpecifier(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                typeSpecifier.reset(static_cast<soul_expected::ast::cpp::TypeSpecifierNode*>(match.value));
                if (match.hit)
                {
                    typeId->Add(typeSpecifier.release());
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul_expected::parser::Match match(true);
        soul_expected::parser::Match* parentMatch3 = &match;
        while (true)
        {
            std::int64_t save = lexer.GetPos();
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch4 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declaration::parser::DeclarationParser<LexerT>::TypeSpecifier(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        typeSpecifier.reset(static_cast<soul_expected::ast::cpp::TypeSpecifierNode*>(match.value));
                        if (match.hit)
                        {
                            typeId->Add(typeSpecifier.release());
                        }
                        *parentMatch5 = match;
                    }
                    *parentMatch4 = match;
                }
                if (match.hit)
                {
                    *parentMatch3 = match;
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifierSeq");
        else soul_expected::lexer::WriteFailureToLog(lexer, "TypeSpecifierSeq");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::AbstractDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "AbstractDeclarator");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344009);
    std::string str = std::string();
    std::unique_ptr<soul_expected::parser::Value<std::string>> ptrOperator;
    std::unique_ptr<soul_expected::parser::Value<std::string>> abstractDeclarator;
    std::unique_ptr<soul_expected::parser::Value<std::string>> directAbstractDeclarator;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            switch (*lexer)
            {
                case soul_expected::cpp::op::token::STAR:
                case soul_expected::punctuation::token::AMP:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch3 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch4 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::PtrOperator(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            ptrOperator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                            if (match.hit)
                            {
                                str.append(ptrOperator->value);
                            }
                            *parentMatch4 = match;
                        }
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            soul_expected::parser::Match match(true);
                            std::int64_t save = lexer.GetPos();
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::AbstractDeclarator(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        abstractDeclarator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                        if (match.hit)
                                        {
                                            str.append(abstractDeclarator->value);
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
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case soul_expected::punctuation::token::LPAREN:
                case soul_expected::punctuation::token::LBRACKET:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch9 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::DirectAbstractDeclarator(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        directAbstractDeclarator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                        if (match.hit)
                        {
                            str.append(directAbstractDeclarator->value);
                        }
                        *parentMatch9 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbstractDeclarator");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "AbstractDeclarator");
        else soul_expected::lexer::WriteFailureToLog(lexer, "AbstractDeclarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::DirectAbstractDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "DirectAbstractDeclarator");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344010);
    std::string str = std::string();
    std::unique_ptr<soul_expected::ast::cpp::Node> expr;
    std::unique_ptr<soul_expected::parser::Value<std::string>> abstractDeclarator;
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
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    switch (*lexer)
                    {
                        case soul_expected::punctuation::token::LBRACKET:
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch5 = &match;
                            {
                                std::int64_t save = lexer.GetPos();
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch6 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch7 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::punctuation::token::LBRACKET)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch8 = &match;
                                        {
                                            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::expression::parser::ExpressionParser<LexerT>::ConstantExpression(lexer, context);
                                            if (!m) return std::unexpected<int>(m.error());
                                            soul_expected::parser::Match match = *m;
                                            expr.reset(static_cast<soul_expected::ast::cpp::Node*>(match.value));
                                            *parentMatch8 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                if (match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch9 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch10 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul_expected::parser::Match match(false);
                                            if (*lexer == soul_expected::punctuation::token::RBRACKET)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            if (match.hit)
                                            {
                                                str.append("[").append(expr.release()->ToString()).append("]");
                                            }
                                            *parentMatch10 = match;
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                                *parentMatch5 = match;
                                if (!match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch11 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch12 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            if (*lexer == soul_expected::punctuation::token::LBRACKET)
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
                                                    if (*lexer == soul_expected::punctuation::token::RBRACKET)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        str.append("[]");
                                                    }
                                                    *parentMatch14 = match;
                                                }
                                                *parentMatch13 = match;
                                            }
                                            *parentMatch12 = match;
                                        }
                                        *parentMatch11 = match;
                                    }
                                    *parentMatch5 = match;
                                }
                            }
                            if (match.hit)
                            {
                                *parentMatch4 = match;
                            }
                            break;
                        }
                        case soul_expected::punctuation::token::LPAREN:
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch15 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch16 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    if (*lexer == soul_expected::punctuation::token::LPAREN)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    *parentMatch16 = match;
                                }
                                if (match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch17 = &match;
                                    {
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::AbstractDeclarator(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        abstractDeclarator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                        *parentMatch17 = match;
                                    }
                                    *parentMatch16 = match;
                                }
                                *parentMatch15 = match;
                            }
                            if (match.hit)
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch18 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch19 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::punctuation::token::RPAREN)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            str.append("(").append(abstractDeclarator->value).append(")");
                                        }
                                        *parentMatch19 = match;
                                    }
                                    *parentMatch18 = match;
                                }
                                *parentMatch15 = match;
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
                soul_expected::parser::Match match(true);
                soul_expected::parser::Match* parentMatch20 = &match;
                while (true)
                {
                    std::int64_t save = lexer.GetPos();
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch21 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch22 = &match;
                            switch (*lexer)
                            {
                                case soul_expected::punctuation::token::LBRACKET:
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch23 = &match;
                                    {
                                        std::int64_t save = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch24 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch25 = &match;
                                            {
                                                soul_expected::parser::Match match(false);
                                                if (*lexer == soul_expected::punctuation::token::LBRACKET)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                *parentMatch25 = match;
                                            }
                                            if (match.hit)
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch26 = &match;
                                                {
                                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::expression::parser::ExpressionParser<LexerT>::ConstantExpression(lexer, context);
                                                    if (!m) return std::unexpected<int>(m.error());
                                                    soul_expected::parser::Match match = *m;
                                                    expr.reset(static_cast<soul_expected::ast::cpp::Node*>(match.value));
                                                    *parentMatch26 = match;
                                                }
                                                *parentMatch25 = match;
                                            }
                                            *parentMatch24 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch27 = &match;
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch28 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul_expected::parser::Match match(false);
                                                    if (*lexer == soul_expected::punctuation::token::RBRACKET)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        str.append("[").append(expr.release()->ToString()).append("]");
                                                    }
                                                    *parentMatch28 = match;
                                                }
                                                *parentMatch27 = match;
                                            }
                                            *parentMatch24 = match;
                                        }
                                        *parentMatch23 = match;
                                        if (!match.hit)
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch29 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch30 = &match;
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    if (*lexer == soul_expected::punctuation::token::LBRACKET)
                                                    {
                                                        auto a = ++lexer;
                                                        if (!a) return std::unexpected<int>(a.error());
                                                        match.hit = true;
                                                    }
                                                    *parentMatch30 = match;
                                                }
                                                if (match.hit)
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch31 = &match;
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch32 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul_expected::parser::Match match(false);
                                                            if (*lexer == soul_expected::punctuation::token::RBRACKET)
                                                            {
                                                                auto a = ++lexer;
                                                                if (!a) return std::unexpected<int>(a.error());
                                                                match.hit = true;
                                                            }
                                                            if (match.hit)
                                                            {
                                                                str.append("[]");
                                                            }
                                                            *parentMatch32 = match;
                                                        }
                                                        *parentMatch31 = match;
                                                    }
                                                    *parentMatch30 = match;
                                                }
                                                *parentMatch29 = match;
                                            }
                                            *parentMatch23 = match;
                                        }
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch22 = match;
                                    }
                                    break;
                                }
                                case soul_expected::punctuation::token::LPAREN:
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch33 = &match;
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch34 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            if (*lexer == soul_expected::punctuation::token::LPAREN)
                                            {
                                                auto a = ++lexer;
                                                if (!a) return std::unexpected<int>(a.error());
                                                match.hit = true;
                                            }
                                            *parentMatch34 = match;
                                        }
                                        if (match.hit)
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch35 = &match;
                                            {
                                                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::AbstractDeclarator(lexer, context);
                                                if (!m) return std::unexpected<int>(m.error());
                                                soul_expected::parser::Match match = *m;
                                                abstractDeclarator.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                                *parentMatch35 = match;
                                            }
                                            *parentMatch34 = match;
                                        }
                                        *parentMatch33 = match;
                                    }
                                    if (match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch36 = &match;
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch37 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul_expected::parser::Match match(false);
                                                if (*lexer == soul_expected::punctuation::token::RPAREN)
                                                {
                                                    auto a = ++lexer;
                                                    if (!a) return std::unexpected<int>(a.error());
                                                    match.hit = true;
                                                }
                                                if (match.hit)
                                                {
                                                    str.append("(").append(abstractDeclarator->value).append(")");
                                                }
                                                *parentMatch37 = match;
                                            }
                                            *parentMatch36 = match;
                                        }
                                        *parentMatch33 = match;
                                    }
                                    if (match.hit)
                                    {
                                        *parentMatch22 = match;
                                    }
                                    break;
                                }
                            }
                            *parentMatch21 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch20 = match;
                        }
                        else
                        {
                            lexer.SetPos(save);
                            break;
                        }
                    }
                }
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DirectAbstractDeclarator");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DirectAbstractDeclarator");
        else soul_expected::lexer::WriteFailureToLog(lexer, "DirectAbstractDeclarator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::PtrOperator(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "PtrOperator");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344011);
    std::string str = std::string();
    std::unique_ptr<soul_expected::parser::Value<std::string>> cvQualifiedSeq;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            switch (*lexer)
            {
                case soul_expected::cpp::op::token::STAR:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch3 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch4 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::cpp::op::token::STAR)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            if (match.hit)
                            {
                                str.append("*");
                            }
                            *parentMatch4 = match;
                        }
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            soul_expected::parser::Match match(true);
                            std::int64_t save = lexer.GetPos();
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::CVQualifierSeq(lexer, context);
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        cvQualifiedSeq.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                        if (match.hit)
                                        {
                                            str.append(1, ' ').append(cvQualifiedSeq->value);
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
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case soul_expected::punctuation::token::AMP:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch9 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == soul_expected::punctuation::token::AMP)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            str.append("&");
                        }
                        *parentMatch9 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PtrOperator");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "PtrOperator");
        else soul_expected::lexer::WriteFailureToLog(lexer, "PtrOperator");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::CVQualifierSeq(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "CVQualifierSeq");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344012);
    std::string str = std::string();
    std::unique_ptr<soul_expected::ast::cpp::TypeSpecifierNode> cvQualifier;
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
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declaration::parser::DeclarationParser<LexerT>::CVQualifier(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        cvQualifier.reset(static_cast<soul_expected::ast::cpp::TypeSpecifierNode*>(match.value));
                        if (match.hit)
                        {
                            if (str != std::string()) str.append(1, ' ');
                            str.append(cvQualifier.release()->ToString());
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(true);
                soul_expected::parser::Match* parentMatch5 = &match;
                while (true)
                {
                    std::int64_t save = lexer.GetPos();
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch6 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch7 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declaration::parser::DeclarationParser<LexerT>::CVQualifier(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                cvQualifier.reset(static_cast<soul_expected::ast::cpp::TypeSpecifierNode*>(match.value));
                                if (match.hit)
                                {
                                    if (str != std::string()) str.append(1, ' ');
                                    str.append(cvQualifier.release()->ToString());
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
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CVQualifierSeq");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::parser::Value<std::string>(str));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CVQualifierSeq");
        else soul_expected::lexer::WriteFailureToLog(lexer, "CVQualifierSeq");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::Initializer(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Initializer");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344013);
    std::unique_ptr<soul_expected::ast::cpp::InitializerNode> initializer = std::unique_ptr<soul_expected::ast::cpp::InitializerNode>();
    std::unique_ptr<soul_expected::ast::cpp::AssignInitNode> initializerClause;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            switch (*lexer)
            {
                case soul_expected::cpp::op::token::ASSIGN:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch3 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        if (*lexer == soul_expected::cpp::op::token::ASSIGN)
                        {
                            auto a = ++lexer;
                            if (!a) return std::unexpected<int>(a.error());
                            match.hit = true;
                        }
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch4 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch5 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::InitializerClause(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                initializerClause.reset(static_cast<soul_expected::ast::cpp::AssignInitNode*>(match.value));
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    initializer.reset(new soul_expected::ast::cpp::InitializerNode(*sp, initializerClause.release()));
                                }
                                *parentMatch5 = match;
                            }
                            *parentMatch4 = match;
                        }
                        *parentMatch3 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
                case soul_expected::punctuation::token::LPAREN:
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch6 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch7 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch8 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul_expected::parser::Match match(false);
                                if (*lexer == soul_expected::punctuation::token::LPAREN)
                                {
                                    auto a = ++lexer;
                                    if (!a) return std::unexpected<int>(a.error());
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    auto sp = lexer.GetSourcePos(pos);
                                    if (!sp) return std::unexpected<int>(sp.error());
                                    initializer.reset(new soul_expected::ast::cpp::InitializerNode(*sp, nullptr));
                                }
                                *parentMatch8 = match;
                            }
                            *parentMatch7 = match;
                        }
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch9 = &match;
                            {
                                std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::expression::parser::ExpressionParser<LexerT>::ExpressionList(lexer, context, initializer.get());
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                *parentMatch9 = match;
                            }
                            *parentMatch7 = match;
                        }
                        *parentMatch6 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch10 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::punctuation::token::RPAREN)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch10 = match;
                        }
                        *parentMatch6 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch2 = match;
                    }
                    break;
                }
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Initializer");
                #endif
                return soul_expected::parser::Match(true, initializer.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Initializer");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Initializer");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::InitializerClause(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "InitializerClause");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344014);
    std::unique_ptr<soul_expected::ast::cpp::AssignInitNode> assignInit = std::unique_ptr<soul_expected::ast::cpp::AssignInitNode>();
    std::unique_ptr<soul_expected::ast::cpp::Node> expr;
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
                std::int64_t save = lexer.GetPos();
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t save = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::expression::parser::ExpressionParser<LexerT>::AssignmentExpression(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        expr.reset(static_cast<soul_expected::ast::cpp::Node*>(match.value));
                        if (match.hit)
                        {
                            auto sp = lexer.GetSourcePos(pos);
                            if (!sp) return std::unexpected<int>(sp.error());
                            assignInit.reset(new soul_expected::ast::cpp::AssignInitNode(*sp, expr.release()));
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        lexer.SetPos(save);
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == soul_expected::punctuation::token::LBRACE)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            auto sp = lexer.GetSourcePos(pos);
                                            if (!sp) return std::unexpected<int>(sp.error());
                                            assignInit.reset(new soul_expected::ast::cpp::AssignInitNode(*sp, nullptr));
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch9 = &match;
                                    {
                                        std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::InitializerList(lexer, context, assignInit.get());
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch10 = &match;
                                {
                                    soul_expected::parser::Match match(false);
                                    if (*lexer == soul_expected::punctuation::token::RBRACE)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch11 = &match;
                    lexer.SetPos(save);
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch12 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::punctuation::token::LBRACE)
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
                                    if (*lexer == soul_expected::punctuation::token::RBRACE)
                                    {
                                        auto a = ++lexer;
                                        if (!a) return std::unexpected<int>(a.error());
                                        match.hit = true;
                                    }
                                    if (match.hit)
                                    {
                                        auto sp = lexer.GetSourcePos(pos);
                                        if (!sp) return std::unexpected<int>(sp.error());
                                        assignInit.reset(new soul_expected::ast::cpp::AssignInitNode(*sp, nullptr));
                                    }
                                    *parentMatch14 = match;
                                }
                                *parentMatch13 = match;
                            }
                            *parentMatch12 = match;
                        }
                        *parentMatch11 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitializerClause");
                #endif
                return soul_expected::parser::Match(true, assignInit.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitializerClause");
        else soul_expected::lexer::WriteFailureToLog(lexer, "InitializerClause");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclaratorParser<LexerT>::InitializerList(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::AssignInitNode* init)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "InitializerList");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8071162672185344015);
    std::unique_ptr<soul_expected::ast::cpp::AssignInitNode> initializerClause;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::InitializerClause(lexer, context);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            initializerClause.reset(static_cast<soul_expected::ast::cpp::AssignInitNode*>(match.value));
            if (match.hit)
            {
                init->Add(initializerClause.release());
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
    }
    if (match.hit)
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch2 = &match;
        {
            soul_expected::parser::Match match(true);
            soul_expected::parser::Match* parentMatch3 = &match;
            {
                while (true)
                {
                    std::int64_t save = lexer.GetPos();
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch4 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == soul_expected::punctuation::token::COMMA)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch4 = match;
                        }
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch5 = &match;
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch6 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    std::expected<soul_expected::parser::Match, int> m = soul_expected::cpp::declarator::parser::DeclaratorParser<LexerT>::InitializerClause(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    initializerClause.reset(static_cast<soul_expected::ast::cpp::AssignInitNode*>(match.value));
                                    if (match.hit)
                                    {
                                        init->Add(initializerClause.release());
                                    }
                                    *parentMatch6 = match;
                                }
                                *parentMatch5 = match;
                            }
                            *parentMatch4 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch3 = match;
                        }
                        else
                        {
                            lexer.SetPos(save);
                            break;
                        }
                    }
                }
            }
            *parentMatch2 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "InitializerList");
        else soul_expected::lexer::WriteFailureToLog(lexer, "InitializerList");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct DeclaratorParser<soul_expected::lexer::Lexer<soul_expected::lex::slg::SlgLexer<char32_t>, char32_t>>;
template struct DeclaratorParser<soul_expected::lexer::Lexer<soul_expected::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul_expected::cpp::declarator::parser
