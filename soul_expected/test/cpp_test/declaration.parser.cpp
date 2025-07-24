
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/test/cpp_test/declaration.parser' using soul parser generator espg version 5.0.0

module soul_expected.cpp.declaration.parser;

import util_expected;
import soul_expected.ast.spg;
import soul_expected.cpp.token;
import soul_expected.cpp.op.token;
import soul_expected.punctuation.token;
import soul_expected.tool.token;
import soul_expected.cpp.expression.parser;
import soul_expected.cpp.identifier.parser;
import soul_expected.cpp.declarator.parser;
import soul_expected.lex.slg;
import soul_expected.lex.spg;

using namespace soul_expected::cpp::token;
using namespace soul_expected::cpp::op::token;
using namespace soul_expected::punctuation::token;
using namespace soul_expected::tool::token;
using namespace soul_expected::cpp::expression::parser;
using namespace soul_expected::cpp::identifier::parser;
using namespace soul_expected::cpp::declarator::parser;
using namespace soul_expected::lex::slg;
using namespace soul_expected::lex::spg;

namespace soul_expected::cpp::declaration::parser {

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::BlockDeclaration(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "BlockDeclaration");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379969);
    std::unique_ptr<soul_expected::ast::cpp::UsingObjectNode> nsAlias;
    std::unique_ptr<soul_expected::ast::cpp::UsingObjectNode> usingDirective;
    std::unique_ptr<soul_expected::ast::cpp::UsingObjectNode> usingDeclaration;
    std::unique_ptr<soul_expected::ast::cpp::SimpleDeclarationNode> simpleDeclaration;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t save = lexer.GetPos();
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::NamespaceAliasDefinition(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    nsAlias.reset(static_cast<soul_expected::ast::cpp::UsingObjectNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BlockDeclaration");
                            #endif
                            return soul_expected::parser::Match(true, nsAlias.release());
                        }
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
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::UsingDirective(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            usingDirective.reset(static_cast<soul_expected::ast::cpp::UsingObjectNode*>(match.value));
                            if (match.hit)
                            {
                                {
                                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BlockDeclaration");
                                    #endif
                                    return soul_expected::parser::Match(true, usingDirective.release());
                                }
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch6 = &match;
                lexer.SetPos(save);
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch7 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::UsingDeclaration(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        usingDeclaration.reset(static_cast<soul_expected::ast::cpp::UsingObjectNode*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BlockDeclaration");
                                #endif
                                return soul_expected::parser::Match(true, usingDeclaration.release());
                            }
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch6 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
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
                    std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::SimpleDeclaration(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    simpleDeclaration.reset(static_cast<soul_expected::ast::cpp::SimpleDeclarationNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BlockDeclaration");
                            #endif
                            return soul_expected::parser::Match(true, simpleDeclaration.release());
                        }
                    }
                    *parentMatch9 = match;
                }
                *parentMatch8 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "BlockDeclaration");
        else soul_expected::lexer::WriteFailureToLog(lexer, "BlockDeclaration");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::SimpleDeclaration(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "SimpleDeclaration");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379970);
    std::unique_ptr<soul_expected::ast::cpp::SimpleDeclarationNode> simpleDeclaration = std::unique_ptr<soul_expected::ast::cpp::SimpleDeclarationNode>();
    std::unique_ptr<soul_expected::ast::cpp::InitDeclaratorListNode> initDeclaratorList;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
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
                        simpleDeclaration.reset(new soul_expected::ast::cpp::SimpleDeclarationNode(*sp));
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
                    std::int64_t save = lexer.GetPos();
                    soul_expected::parser::Match* parentMatch5 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch6 = &match;
                        {
                            std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::DeclSpecifierSeq(lexer, context, simpleDeclaration.get());
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            *parentMatch6 = match;
                        }
                        if (match.hit)
                        {
                            *parentMatch5 = match;
                        }
                        else
                        {
                            lexer.SetPos(save);
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
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch7 = &match;
            {
                soul_expected::parser::Match match(true);
                std::int64_t save = lexer.GetPos();
                soul_expected::parser::Match* parentMatch8 = &match;
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch9 = &match;
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch10 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            std::expected<soul_expected::parser::Match, int> m = DeclaratorParser<LexerT>::InitDeclaratorList(lexer, context);
                            if (!m) return std::unexpected<int>(m.error());
                            soul_expected::parser::Match match = *m;
                            initDeclaratorList.reset(static_cast<soul_expected::ast::cpp::InitDeclaratorListNode*>(match.value));
                            if (match.hit)
                            {
                                simpleDeclaration->SetInitDeclaratorList(initDeclaratorList.release());
                            }
                            *parentMatch10 = match;
                        }
                        *parentMatch9 = match;
                    }
                    if (match.hit)
                    {
                        *parentMatch8 = match;
                    }
                    else
                    {
                        lexer.SetPos(save);
                    }
                }
                *parentMatch7 = match;
            }
            *parentMatch1 = match;
        }
        *parentMatch0 = match;
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
                soul_expected::parser::Match match(false);
                if (*lexer == SEMICOLON)
                {
                    auto a = ++lexer;
                    if (!a) return std::unexpected<int>(a.error());
                    match.hit = true;
                }
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleDeclaration");
                        #endif
                        return soul_expected::parser::Match(true, simpleDeclaration.release());
                    }
                }
                *parentMatch12 = match;
            }
            *parentMatch11 = match;
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleDeclaration");
        else soul_expected::lexer::WriteFailureToLog(lexer, "SimpleDeclaration");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::DeclSpecifierSeq(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::SimpleDeclarationNode* declaration)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "DeclSpecifierSeq");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379971);
    std::unique_ptr<soul_expected::ast::cpp::DeclSpecifierNode> declSpecifier;
    std::unique_ptr<soul_expected::ast::cpp::TypeNameNode> typeName;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
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
                        std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::DeclSpecifier(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        declSpecifier.reset(static_cast<soul_expected::ast::cpp::DeclSpecifierNode*>(match.value));
                        if (match.hit)
                        {
                            declaration->Add(declSpecifier.release());
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
                                std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::DeclSpecifier(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                declSpecifier.reset(static_cast<soul_expected::ast::cpp::DeclSpecifierNode*>(match.value));
                                if (match.hit)
                                {
                                    declaration->Add(declSpecifier.release());
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
                        std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::TypeName(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        typeName.reset(static_cast<soul_expected::ast::cpp::TypeNameNode*>(match.value));
                        if (match.hit)
                        {
                            declaration->Add(typeName.release());
                        }
                        *parentMatch9 = match;
                    }
                    *parentMatch8 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclSpecifierSeq");
        else soul_expected::lexer::WriteFailureToLog(lexer, "DeclSpecifierSeq");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::DeclSpecifier(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "DeclSpecifier");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379972);
    std::unique_ptr<soul_expected::ast::cpp::StorageClassSpecifierNode> storateClassSpecifier;
    std::unique_ptr<soul_expected::ast::cpp::TypeSpecifierNode> typeSpecifier;
    std::unique_ptr<soul_expected::ast::cpp::DeclSpecifierNode> tdef;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch2 = &match;
            {
                std::int64_t pos = lexer.GetPos();
                std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::StorageClassSpecifier(lexer, context);
                if (!m) return std::unexpected<int>(m.error());
                soul_expected::parser::Match match = *m;
                storateClassSpecifier.reset(static_cast<soul_expected::ast::cpp::StorageClassSpecifierNode*>(match.value));
                if (match.hit)
                {
                    {
                        #ifdef SOUL_PARSER_DEBUG_SUPPORT
                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclSpecifier");
                        #endif
                        return soul_expected::parser::Match(true, storateClassSpecifier.release());
                    }
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch3 = &match;
                lexer.SetPos(save);
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch4 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::TypeSpecifier(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        typeSpecifier.reset(static_cast<soul_expected::ast::cpp::TypeSpecifierNode*>(match.value));
                        if (match.hit)
                        {
                            {
                                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclSpecifier");
                                #endif
                                return soul_expected::parser::Match(true, typeSpecifier.release());
                            }
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch5 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch6 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::Typedef(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    tdef.reset(static_cast<soul_expected::ast::cpp::DeclSpecifierNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclSpecifier");
                            #endif
                            return soul_expected::parser::Match(true, tdef.release());
                        }
                    }
                    *parentMatch6 = match;
                }
                *parentMatch5 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "DeclSpecifier");
        else soul_expected::lexer::WriteFailureToLog(lexer, "DeclSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::StorageClassSpecifier(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "StorageClassSpecifier");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379973);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
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
                        soul_expected::parser::Match match(false);
                        if (*lexer == AUTO)
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
                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StorageClassSpecifier");
                                #endif
                                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::StorageClassSpecifierNode(*sp, "auto"));
                            }
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
                                std::int64_t pos = lexer.GetPos();
                                soul_expected::parser::Match match(false);
                                if (*lexer == REGISTER)
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
                                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StorageClassSpecifier");
                                        #endif
                                        return soul_expected::parser::Match(true, new soul_expected::ast::cpp::StorageClassSpecifierNode(*sp, "register"));
                                    }
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
                    soul_expected::parser::Match* parentMatch7 = &match;
                    lexer.SetPos(save);
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch8 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            if (*lexer == STATIC)
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
                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StorageClassSpecifier");
                                    #endif
                                    return soul_expected::parser::Match(true, new soul_expected::ast::cpp::StorageClassSpecifierNode(*sp, "static"));
                                }
                            }
                            *parentMatch8 = match;
                        }
                        *parentMatch7 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch9 = &match;
                lexer.SetPos(save);
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch10 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == EXTERN)
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
                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StorageClassSpecifier");
                                #endif
                                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::StorageClassSpecifierNode(*sp, "extern"));
                            }
                        }
                        *parentMatch10 = match;
                    }
                    *parentMatch9 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch11 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch12 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == MUTABLE)
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
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StorageClassSpecifier");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::cpp::StorageClassSpecifierNode(*sp, "mutable"));
                        }
                    }
                    *parentMatch12 = match;
                }
                *parentMatch11 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "StorageClassSpecifier");
        else soul_expected::lexer::WriteFailureToLog(lexer, "StorageClassSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::TypeSpecifier(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "TypeSpecifier");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379974);
    std::unique_ptr<soul_expected::ast::cpp::TypeSpecifierNode> simpleTypeSpecifier;
    std::unique_ptr<soul_expected::ast::cpp::TypeSpecifierNode> cvQualifier;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::SimpleTypeSpecifier(lexer, context);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            simpleTypeSpecifier.reset(static_cast<soul_expected::ast::cpp::TypeSpecifierNode*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifier");
                    #endif
                    return soul_expected::parser::Match(true, simpleTypeSpecifier.release());
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
                    std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::CVQualifier(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    cvQualifier.reset(static_cast<soul_expected::ast::cpp::TypeSpecifierNode*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifier");
                            #endif
                            return soul_expected::parser::Match(true, cvQualifier.release());
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeSpecifier");
        else soul_expected::lexer::WriteFailureToLog(lexer, "TypeSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::SimpleTypeSpecifier(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "SimpleTypeSpecifier");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379975);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t save = lexer.GetPos();
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
                        std::int64_t save = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            std::int64_t save = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                std::int64_t save = lexer.GetPos();
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch7 = &match;
                                {
                                    std::int64_t save = lexer.GetPos();
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t save = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch9 = &match;
                                        {
                                            std::int64_t save = lexer.GetPos();
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch10 = &match;
                                            {
                                                std::int64_t save = lexer.GetPos();
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch11 = &match;
                                                {
                                                    std::int64_t save = lexer.GetPos();
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch12 = &match;
                                                    {
                                                        std::int64_t save = lexer.GetPos();
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch13 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul_expected::parser::Match match(false);
                                                            if (*lexer == CHAR)
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
                                                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                                    #endif
                                                                    return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "char"));
                                                                }
                                                            }
                                                            *parentMatch13 = match;
                                                        }
                                                        *parentMatch12 = match;
                                                        if (!match.hit)
                                                        {
                                                            soul_expected::parser::Match match(false);
                                                            soul_expected::parser::Match* parentMatch14 = &match;
                                                            lexer.SetPos(save);
                                                            {
                                                                soul_expected::parser::Match match(false);
                                                                soul_expected::parser::Match* parentMatch15 = &match;
                                                                {
                                                                    std::int64_t pos = lexer.GetPos();
                                                                    soul_expected::parser::Match match(false);
                                                                    if (*lexer == CHAR8T)
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
                                                                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                                            #endif
                                                                            return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "char8_t"));
                                                                        }
                                                                    }
                                                                    *parentMatch15 = match;
                                                                }
                                                                *parentMatch14 = match;
                                                            }
                                                            *parentMatch12 = match;
                                                        }
                                                    }
                                                    *parentMatch11 = match;
                                                    if (!match.hit)
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch16 = &match;
                                                        lexer.SetPos(save);
                                                        {
                                                            soul_expected::parser::Match match(false);
                                                            soul_expected::parser::Match* parentMatch17 = &match;
                                                            {
                                                                std::int64_t pos = lexer.GetPos();
                                                                soul_expected::parser::Match match(false);
                                                                if (*lexer == CHAR16T)
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
                                                                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                                        #endif
                                                                        return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "char16_t"));
                                                                    }
                                                                }
                                                                *parentMatch17 = match;
                                                            }
                                                            *parentMatch16 = match;
                                                        }
                                                        *parentMatch11 = match;
                                                    }
                                                }
                                                *parentMatch10 = match;
                                                if (!match.hit)
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch18 = &match;
                                                    lexer.SetPos(save);
                                                    {
                                                        soul_expected::parser::Match match(false);
                                                        soul_expected::parser::Match* parentMatch19 = &match;
                                                        {
                                                            std::int64_t pos = lexer.GetPos();
                                                            soul_expected::parser::Match match(false);
                                                            if (*lexer == CHAR32T)
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
                                                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                                    #endif
                                                                    return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "char32_t"));
                                                                }
                                                            }
                                                            *parentMatch19 = match;
                                                        }
                                                        *parentMatch18 = match;
                                                    }
                                                    *parentMatch10 = match;
                                                }
                                            }
                                            *parentMatch9 = match;
                                            if (!match.hit)
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch20 = &match;
                                                lexer.SetPos(save);
                                                {
                                                    soul_expected::parser::Match match(false);
                                                    soul_expected::parser::Match* parentMatch21 = &match;
                                                    {
                                                        std::int64_t pos = lexer.GetPos();
                                                        soul_expected::parser::Match match(false);
                                                        if (*lexer == WCHART)
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
                                                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                                #endif
                                                                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "wchar_t"));
                                                            }
                                                        }
                                                        *parentMatch21 = match;
                                                    }
                                                    *parentMatch20 = match;
                                                }
                                                *parentMatch9 = match;
                                            }
                                        }
                                        *parentMatch8 = match;
                                        if (!match.hit)
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch22 = &match;
                                            lexer.SetPos(save);
                                            {
                                                soul_expected::parser::Match match(false);
                                                soul_expected::parser::Match* parentMatch23 = &match;
                                                {
                                                    std::int64_t pos = lexer.GetPos();
                                                    soul_expected::parser::Match match(false);
                                                    if (*lexer == BOOL)
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
                                                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                            #endif
                                                            return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "bool"));
                                                        }
                                                    }
                                                    *parentMatch23 = match;
                                                }
                                                *parentMatch22 = match;
                                            }
                                            *parentMatch8 = match;
                                        }
                                    }
                                    *parentMatch7 = match;
                                    if (!match.hit)
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch24 = &match;
                                        lexer.SetPos(save);
                                        {
                                            soul_expected::parser::Match match(false);
                                            soul_expected::parser::Match* parentMatch25 = &match;
                                            {
                                                std::int64_t pos = lexer.GetPos();
                                                soul_expected::parser::Match match(false);
                                                if (*lexer == SHORT)
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
                                                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                        #endif
                                                        return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "short"));
                                                    }
                                                }
                                                *parentMatch25 = match;
                                            }
                                            *parentMatch24 = match;
                                        }
                                        *parentMatch7 = match;
                                    }
                                }
                                *parentMatch6 = match;
                                if (!match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch26 = &match;
                                    lexer.SetPos(save);
                                    {
                                        soul_expected::parser::Match match(false);
                                        soul_expected::parser::Match* parentMatch27 = &match;
                                        {
                                            std::int64_t pos = lexer.GetPos();
                                            soul_expected::parser::Match match(false);
                                            if (*lexer == INT)
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
                                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                    #endif
                                                    return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "int"));
                                                }
                                            }
                                            *parentMatch27 = match;
                                        }
                                        *parentMatch26 = match;
                                    }
                                    *parentMatch6 = match;
                                }
                            }
                            *parentMatch5 = match;
                            if (!match.hit)
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch28 = &match;
                                lexer.SetPos(save);
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch29 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == LONG)
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
                                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                                #endif
                                                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "long"));
                                            }
                                        }
                                        *parentMatch29 = match;
                                    }
                                    *parentMatch28 = match;
                                }
                                *parentMatch5 = match;
                            }
                        }
                        *parentMatch4 = match;
                        if (!match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch30 = &match;
                            lexer.SetPos(save);
                            {
                                soul_expected::parser::Match match(false);
                                soul_expected::parser::Match* parentMatch31 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul_expected::parser::Match match(false);
                                    if (*lexer == SIGNED)
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
                                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                            #endif
                                            return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "signed"));
                                        }
                                    }
                                    *parentMatch31 = match;
                                }
                                *parentMatch30 = match;
                            }
                            *parentMatch4 = match;
                        }
                    }
                    *parentMatch3 = match;
                    if (!match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch32 = &match;
                        lexer.SetPos(save);
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch33 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul_expected::parser::Match match(false);
                                if (*lexer == UNSIGNED)
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
                                        if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                        #endif
                                        return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "unsigned"));
                                    }
                                }
                                *parentMatch33 = match;
                            }
                            *parentMatch32 = match;
                        }
                        *parentMatch3 = match;
                    }
                }
                *parentMatch2 = match;
                if (!match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch34 = &match;
                    lexer.SetPos(save);
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch35 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul_expected::parser::Match match(false);
                            if (*lexer == FLOAT)
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
                                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                    #endif
                                    return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "float"));
                                }
                            }
                            *parentMatch35 = match;
                        }
                        *parentMatch34 = match;
                    }
                    *parentMatch2 = match;
                }
            }
            *parentMatch1 = match;
            if (!match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch36 = &match;
                lexer.SetPos(save);
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch37 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul_expected::parser::Match match(false);
                        if (*lexer == DOUBLE)
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
                                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                                #endif
                                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "double"));
                            }
                        }
                        *parentMatch37 = match;
                    }
                    *parentMatch36 = match;
                }
                *parentMatch1 = match;
            }
        }
        *parentMatch0 = match;
        if (!match.hit)
        {
            soul_expected::parser::Match match(false);
            soul_expected::parser::Match* parentMatch38 = &match;
            lexer.SetPos(save);
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch39 = &match;
                {
                    std::int64_t pos = lexer.GetPos();
                    soul_expected::parser::Match match(false);
                    if (*lexer == VOID)
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
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypeSpecifierNode(*sp, "void"));
                        }
                    }
                    *parentMatch39 = match;
                }
                *parentMatch38 = match;
            }
            *parentMatch0 = match;
        }
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "SimpleTypeSpecifier");
        else soul_expected::lexer::WriteFailureToLog(lexer, "SimpleTypeSpecifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::TypeName(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "TypeName");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379976);
    std::unique_ptr<soul_expected::ast::cpp::TypeNameNode> typeName = std::unique_ptr<soul_expected::ast::cpp::TypeNameNode>();
    std::unique_ptr<soul_expected::parser::Value<std::string>> qid;
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
                    std::expected<soul_expected::parser::Match, int> m = CppIdentifierParser<LexerT>::QualifiedCppId(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    qid.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                    if (match.hit)
                    {
                        auto sp = lexer.GetSourcePos(pos);
                        if (!sp) return std::unexpected<int>(sp.error());
                        typeName.reset(new soul_expected::ast::cpp::TypeNameNode(*sp, qid->value));
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
                    std::int64_t save = lexer.GetPos();
                    soul_expected::parser::Match* parentMatch5 = &match;
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
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch9 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        auto vars = static_cast<typename LexerT::VariableClassType*>(lexer.GetVariables());
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == LANGLE)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            ++vars->leftAngleCount;
                                            typeName->SetTemplate();
                                            context->BeginParsingTemplateId();
                                        }
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                if (match.hit)
                                {
                                    soul_expected::parser::Match match(false);
                                    soul_expected::parser::Match* parentMatch10 = &match;
                                    {
                                        std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::TemplateArgumentList(lexer, context, typeName.get());
                                        if (!m) return std::unexpected<int>(m.error());
                                        soul_expected::parser::Match match = *m;
                                        *parentMatch10 = match;
                                    }
                                    *parentMatch8 = match;
                                }
                                *parentMatch7 = match;
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
                                        auto vars = static_cast<typename LexerT::VariableClassType*>(lexer.GetVariables());
                                        soul_expected::parser::Match match(false);
                                        if (*lexer == RANGLE)
                                        {
                                            auto a = ++lexer;
                                            if (!a) return std::unexpected<int>(a.error());
                                            match.hit = true;
                                        }
                                        if (match.hit)
                                        {
                                            --vars->leftAngleCount;
                                            context->EndParsingTemplateId();
                                        }
                                        *parentMatch12 = match;
                                    }
                                    *parentMatch11 = match;
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeName");
                #endif
                return soul_expected::parser::Match(true, typeName.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TypeName");
        else soul_expected::lexer::WriteFailureToLog(lexer, "TypeName");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::TemplateArgumentList(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::TypeNameNode* typeName)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "TemplateArgumentList");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379977);
    std::unique_ptr<soul_expected::ast::cpp::Node> arg;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::TemplateArgument(lexer, context);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            arg.reset(static_cast<soul_expected::ast::cpp::Node*>(match.value));
            if (match.hit)
            {
                typeName->AddTemplateArgument(arg.release());
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
                            if (*lexer == COMMA)
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
                                    std::expected<soul_expected::parser::Match, int> m = DeclarationParser<LexerT>::TemplateArgument(lexer, context);
                                    if (!m) return std::unexpected<int>(m.error());
                                    soul_expected::parser::Match match = *m;
                                    arg.reset(static_cast<soul_expected::ast::cpp::Node*>(match.value));
                                    if (match.hit)
                                    {
                                        typeName->AddTemplateArgument(arg.release());
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TemplateArgumentList");
        else soul_expected::lexer::WriteFailureToLog(lexer, "TemplateArgumentList");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::TemplateArgument(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "TemplateArgument");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379978);
    std::unique_ptr<soul_expected::ast::cpp::TypeIdNode> typeId;
    std::unique_ptr<soul_expected::ast::cpp::Node> assignmentExpr;
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            std::expected<soul_expected::parser::Match, int> m = DeclaratorParser<LexerT>::TypeId(lexer, context);
            if (!m) return std::unexpected<int>(m.error());
            soul_expected::parser::Match match = *m;
            typeId.reset(static_cast<soul_expected::ast::cpp::TypeIdNode*>(match.value));
            if (match.hit)
            {
                {
                    #ifdef SOUL_PARSER_DEBUG_SUPPORT
                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TemplateArgument");
                    #endif
                    return soul_expected::parser::Match(true, typeId.release());
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
                    std::expected<soul_expected::parser::Match, int> m = ExpressionParser<LexerT>::AssignmentExpression(lexer, context);
                    if (!m) return std::unexpected<int>(m.error());
                    soul_expected::parser::Match match = *m;
                    assignmentExpr.reset(static_cast<soul_expected::ast::cpp::Node*>(match.value));
                    if (match.hit)
                    {
                        {
                            #ifdef SOUL_PARSER_DEBUG_SUPPORT
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TemplateArgument");
                            #endif
                            return soul_expected::parser::Match(true, assignmentExpr.release());
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "TemplateArgument");
        else soul_expected::lexer::WriteFailureToLog(lexer, "TemplateArgument");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::Typedef(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "Typedef");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379979);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
        soul_expected::parser::Match match(false);
        if (*lexer == TYPEDEF)
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Typedef");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::TypedefNode(*sp));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Typedef");
        else soul_expected::lexer::WriteFailureToLog(lexer, "Typedef");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::CVQualifier(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "CVQualifier");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379980);
    soul_expected::parser::Match match(false);
    soul_expected::parser::Match* parentMatch0 = &match;
    {
        std::int64_t save = lexer.GetPos();
        soul_expected::parser::Match match(false);
        soul_expected::parser::Match* parentMatch1 = &match;
        {
            std::int64_t pos = lexer.GetPos();
            soul_expected::parser::Match match(false);
            if (*lexer == CONST)
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
                    if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CVQualifier");
                    #endif
                    return soul_expected::parser::Match(true, new soul_expected::ast::cpp::ConstNode(*sp));
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
                    soul_expected::parser::Match match(false);
                    if (*lexer == VOLATILE)
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
                            if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CVQualifier");
                            #endif
                            return soul_expected::parser::Match(true, new soul_expected::ast::cpp::VolatileNode(*sp));
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
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "CVQualifier");
        else soul_expected::lexer::WriteFailureToLog(lexer, "CVQualifier");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::NamespaceAliasDefinition(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "NamespaceAliasDefinition");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379981);
    std::unique_ptr<soul_expected::parser::Value<std::string>> id;
    std::unique_ptr<soul_expected::parser::Value<std::string>> qid;
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
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch5 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == NAMESPACE)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul_expected::parser::Match match(false);
                            soul_expected::parser::Match* parentMatch6 = &match;
                            {
                                std::expected<soul_expected::parser::Match, int> m = CppIdentifierParser<LexerT>::CppIdentifier(lexer, context);
                                if (!m) return std::unexpected<int>(m.error());
                                soul_expected::parser::Match match = *m;
                                id.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul_expected::parser::Match match(false);
                        soul_expected::parser::Match* parentMatch7 = &match;
                        {
                            soul_expected::parser::Match match(false);
                            if (*lexer == ASSIGN)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch7 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch8 = &match;
                    {
                        std::expected<soul_expected::parser::Match, int> m = CppIdentifierParser<LexerT>::QualifiedCppId(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        qid.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                        *parentMatch8 = match;
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
                    soul_expected::parser::Match match(false);
                    if (*lexer == SEMICOLON)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch9 = match;
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NamespaceAliasDefinition");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::NamespaceAliasNode(*sp, id->value, qid->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "NamespaceAliasDefinition");
        else soul_expected::lexer::WriteFailureToLog(lexer, "NamespaceAliasDefinition");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::UsingDeclaration(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "UsingDeclaration");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379982);
    std::unique_ptr<soul_expected::parser::Value<std::string>> qid;
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
                    if (*lexer == USING)
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
                        std::expected<soul_expected::parser::Match, int> m = CppIdentifierParser<LexerT>::QualifiedCppId(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        qid.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch5 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == SEMICOLON)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch5 = match;
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UsingDeclaration");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::UsingDeclarationNode(*sp, qid->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UsingDeclaration");
        else soul_expected::lexer::WriteFailureToLog(lexer, "UsingDeclaration");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
std::expected<soul_expected::parser::Match, int> DeclarationParser<LexerT>::UsingDirective(LexerT& lexer, soul_expected::ast::cpp::Context* context)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul_expected::lexer::WriteBeginRuleToLog(lexer, "UsingDirective");
    }
    #endif
    soul_expected::lexer::RuleGuard<LexerT> ruleGuard(lexer, 309842625815379983);
    std::unique_ptr<soul_expected::parser::Value<std::string>> ns;
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
                        soul_expected::parser::Match match(false);
                        if (*lexer == USING)
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
                            if (*lexer == NAMESPACE)
                            {
                                auto a = ++lexer;
                                if (!a) return std::unexpected<int>(a.error());
                                match.hit = true;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul_expected::parser::Match match(false);
                    soul_expected::parser::Match* parentMatch6 = &match;
                    {
                        std::expected<soul_expected::parser::Match, int> m = CppIdentifierParser<LexerT>::QualifiedCppId(lexer, context);
                        if (!m) return std::unexpected<int>(m.error());
                        soul_expected::parser::Match match = *m;
                        ns.reset(static_cast<soul_expected::parser::Value<std::string>*>(match.value));
                        *parentMatch6 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul_expected::parser::Match match(false);
                soul_expected::parser::Match* parentMatch7 = &match;
                {
                    soul_expected::parser::Match match(false);
                    if (*lexer == SEMICOLON)
                    {
                        auto a = ++lexer;
                        if (!a) return std::unexpected<int>(a.error());
                        match.hit = true;
                    }
                    *parentMatch7 = match;
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
                if (parser_debug_write_to_log) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UsingDirective");
                #endif
                return soul_expected::parser::Match(true, new soul_expected::ast::cpp::UsingDirectiveNode(*sp, ns->value));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul_expected::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "UsingDirective");
        else soul_expected::lexer::WriteFailureToLog(lexer, "UsingDirective");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct DeclarationParser<soul_expected::lexer::Lexer<soul_expected::lex::slg::SlgLexer<char32_t>, char32_t>>;
template struct DeclarationParser<soul_expected::lexer::Lexer<soul_expected::lex::spg::SpgLexer<char32_t>, char32_t>>;

} // namespace soul_expected::cpp::declaration::parser
