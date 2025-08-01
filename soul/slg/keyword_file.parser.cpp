
// this file has been automatically generated from 'D:/work/soul-mod/soul/slg/keyword_file.parser' using soul parser generator spg version 5.0.0

module soul.slg.keyword.file.parser;

import util;
import soul.ast.spg;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.punctuation.token;
import soul.tool.token;
import soul.common.common.parser;
import soul.common.token.parser;
import soul.lex.slg;

using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::punctuation::token;
using namespace soul::tool::token;
using namespace soul::common::common::parser;
using namespace soul::common::token::parser;
using namespace soul::lex::slg;

namespace soul::slg::keyword::file::parser {

template<typename LexerT>
std::unique_ptr<soul::ast::slg::KeywordFile> KeywordFileParser<LexerT>::Parse(LexerT& lexer)
{
    std::unique_ptr<soul::ast::slg::KeywordFile> value;
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->WriteBeginRule("parse");
        lexer.Log()->IncIndent();
    }
    #endif
    ++lexer;
    soul::parser::Match match = KeywordFileParser<LexerT>::KeywordFile(lexer);
    value.reset(static_cast<soul::ast::slg::KeywordFile*>(match.value));
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (lexer.Log())
    {
        lexer.Log()->DecIndent();
        lexer.Log()->WriteEndRule("parse");
    }
    #endif
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

template<typename LexerT>
soul::parser::Match KeywordFileParser<LexerT>::KeywordFile(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "KeywordFile");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8613845327771860993);
    std::unique_ptr<soul::ast::slg::KeywordFile> keywordFile = std::unique_ptr<soul::ast::slg::KeywordFile>();
    std::unique_ptr<soul::ast::slg::KeywordCollection> keywordCollection = std::unique_ptr<soul::ast::slg::KeywordCollection>();
    std::unique_ptr<soul::parser::Value<std::string>> keywordCollectionName;
    std::unique_ptr<soul::ast::slg::Keyword> keyword;
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
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
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch8 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match(true);
                                        if (match.hit)
                                        {
                                            keywordFile.reset(new soul::ast::slg::KeywordFile(lexer.FileName()));
                                        }
                                        *parentMatch8 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch9 = &match;
                                    {
                                        soul::parser::Match match = KeywordFileParser<LexerT>::Imports(lexer, keywordFile.get());
                                        *parentMatch9 = match;
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            if (match.hit)
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch10 = &match;
                                {
                                    soul::parser::Match match(false);
                                    if (*lexer == KEYWORDS)
                                    {
                                        ++lexer;
                                        match.hit = true;
                                    }
                                    *parentMatch10 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch11 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch12 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch13 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = CommonParser<LexerT>::QualifiedId(lexer);
                                        keywordCollectionName.reset(static_cast<soul::parser::Value<std::string>*>(match.value));
                                        if (match.hit)
                                        {
                                            *parentMatch13 = match;
                                        }
                                        else
                                        {
                                            lexer.ThrowExpectationFailure(pos, "QualifiedId");
                                        }
                                    }
                                    if (match.hit)
                                    {
                                        keywordCollection.reset(new soul::ast::slg::KeywordCollection(keywordCollectionName->value));
                                    }
                                    *parentMatch12 = match;
                                }
                                *parentMatch11 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch14 = &match;
                        {
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch15 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == LBRACE)
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
                                    lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(LBRACE));
                                }
                            }
                            *parentMatch14 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch16 = &match;
                    {
                        soul::parser::Match match(true);
                        std::int64_t save = lexer.GetPos();
                        soul::parser::Match* parentMatch17 = &match;
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch18 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch19 = &match;
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch20 = &match;
                                    {
                                        std::int64_t pos = lexer.GetPos();
                                        soul::parser::Match match = KeywordFileParser<LexerT>::Keyword(lexer);
                                        keyword.reset(static_cast<soul::ast::slg::Keyword*>(match.value));
                                        if (match.hit)
                                        {
                                            keywordCollection->AddKeyword(keyword.release());
                                        }
                                        *parentMatch20 = match;
                                    }
                                    *parentMatch19 = match;
                                }
                                if (match.hit)
                                {
                                    soul::parser::Match match(false);
                                    soul::parser::Match* parentMatch21 = &match;
                                    {
                                        soul::parser::Match match(true);
                                        soul::parser::Match* parentMatch22 = &match;
                                        {
                                            while (true)
                                            {
                                                std::int64_t save = lexer.GetPos();
                                                {
                                                    soul::parser::Match match(false);
                                                    soul::parser::Match* parentMatch23 = &match;
                                                    {
                                                        soul::parser::Match match(false);
                                                        if (*lexer == COMMA)
                                                        {
                                                            ++lexer;
                                                            match.hit = true;
                                                        }
                                                        *parentMatch23 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        soul::parser::Match match(false);
                                                        soul::parser::Match* parentMatch24 = &match;
                                                        {
                                                            soul::parser::Match match(false);
                                                            soul::parser::Match* parentMatch25 = &match;
                                                            {
                                                                std::int64_t pos = lexer.GetPos();
                                                                soul::parser::Match match = KeywordFileParser<LexerT>::Keyword(lexer);
                                                                keyword.reset(static_cast<soul::ast::slg::Keyword*>(match.value));
                                                                if (match.hit)
                                                                {
                                                                    keywordCollection->AddKeyword(keyword.release());
                                                                }
                                                                *parentMatch25 = match;
                                                            }
                                                            *parentMatch24 = match;
                                                        }
                                                        *parentMatch23 = match;
                                                    }
                                                    if (match.hit)
                                                    {
                                                        *parentMatch22 = match;
                                                    }
                                                    else
                                                    {
                                                        lexer.SetPos(save);
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        *parentMatch21 = match;
                                    }
                                    *parentMatch19 = match;
                                }
                                *parentMatch18 = match;
                            }
                            if (match.hit)
                            {
                                *parentMatch17 = match;
                            }
                            else
                            {
                                lexer.SetPos(save);
                            }
                        }
                        *parentMatch16 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch26 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch27 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match(false);
                        if (*lexer == RBRACE)
                        {
                            ++lexer;
                            match.hit = true;
                        }
                        if (match.hit)
                        {
                            *parentMatch27 = match;
                        }
                        else
                        {
                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(RBRACE));
                        }
                    }
                    *parentMatch26 = match;
                }
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            keywordFile->SetKeywordCollection(keywordCollection.release());
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "KeywordFile");
                #endif
                return soul::parser::Match(true, keywordFile.release());
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "KeywordFile");
        else soul::lexer::WriteFailureToLog(lexer, "KeywordFile");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match KeywordFileParser<LexerT>::Imports(LexerT& lexer, soul::ast::slg::KeywordFile* keywordFile)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "Imports");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8613845327771860994);
    std::unique_ptr<soul::ast::common::Import> imp;
    soul::parser::Match match(true);
    soul::parser::Match* parentMatch0 = &match;
    {
        while (true)
        {
            std::int64_t save = lexer.GetPos();
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch1 = &match;
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch2 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
                        soul::parser::Match match = CommonParser<LexerT>::Import(lexer);
                        imp.reset(static_cast<soul::ast::common::Import*>(match.value));
                        if (match.hit)
                        {
                            keywordFile->AddImport(imp.release());
                        }
                        *parentMatch2 = match;
                    }
                    *parentMatch1 = match;
                }
                if (match.hit)
                {
                    *parentMatch0 = match;
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
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Imports");
        else soul::lexer::WriteFailureToLog(lexer, "Imports");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template<typename LexerT>
soul::parser::Match KeywordFileParser<LexerT>::Keyword(LexerT& lexer)
{
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    std::int64_t parser_debug_match_pos = 0;
    bool parser_debug_write_to_log = lexer.Log() != nullptr;
    if (parser_debug_write_to_log)
    {
        parser_debug_match_pos = lexer.GetPos();
        soul::lexer::soul::lexer::WriteBeginRuleToLog(lexer, "Keyword");
    }
    #endif
    soul::lexer::RuleGuard<LexerT> ruleGuard(lexer, 8613845327771860995);
    std::string str = std::string();
    std::string tokenName = std::string();
    soul::parser::Match match(false);
    soul::parser::Match* parentMatch0 = &match;
    {
        std::int64_t pos = lexer.GetPos();
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
                            if (*lexer == LPAREN)
                            {
                                ++lexer;
                                match.hit = true;
                            }
                            *parentMatch5 = match;
                        }
                        if (match.hit)
                        {
                            soul::parser::Match match(false);
                            soul::parser::Match* parentMatch6 = &match;
                            {
                                soul::parser::Match match(false);
                                soul::parser::Match* parentMatch7 = &match;
                                {
                                    std::int64_t pos = lexer.GetPos();
                                    soul::parser::Match match(true);
                                    soul::parser::Match* parentMatch8 = &match;
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
                                            *parentMatch8 = match;
                                        }
                                        else
                                        {
                                            lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(STRING_LITERAL));
                                        }
                                    }
                                    if (match.hit)
                                    {
                                        str = util::ToUtf8(ParseStringLiteral(lexer.FileName(), lexer.GetToken(pos)));
                                    }
                                    *parentMatch7 = match;
                                }
                                *parentMatch6 = match;
                            }
                            *parentMatch5 = match;
                        }
                        *parentMatch4 = match;
                    }
                    if (match.hit)
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch9 = &match;
                        {
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch10 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == COMMA)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    *parentMatch10 = match;
                                }
                                else
                                {
                                    lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(COMMA));
                                }
                            }
                            *parentMatch9 = match;
                        }
                        *parentMatch4 = match;
                    }
                    *parentMatch3 = match;
                }
                if (match.hit)
                {
                    soul::parser::Match match(false);
                    soul::parser::Match* parentMatch11 = &match;
                    {
                        soul::parser::Match match(false);
                        soul::parser::Match* parentMatch12 = &match;
                        {
                            std::int64_t pos = lexer.GetPos();
                            soul::parser::Match match(true);
                            soul::parser::Match* parentMatch13 = &match;
                            {
                                std::int64_t pos = lexer.GetPos();
                                soul::parser::Match match(false);
                                if (*lexer == ID)
                                {
                                    ++lexer;
                                    match.hit = true;
                                }
                                if (match.hit)
                                {
                                    *parentMatch13 = match;
                                }
                                else
                                {
                                    lexer.ThrowExpectationFailure(pos, lexer.GetTokenInfo(ID));
                                }
                            }
                            if (match.hit)
                            {
                                tokenName = util::ToUtf8(lexer.GetToken(pos).ToString());
                            }
                            *parentMatch12 = match;
                        }
                        *parentMatch11 = match;
                    }
                    *parentMatch3 = match;
                }
                *parentMatch2 = match;
            }
            if (match.hit)
            {
                soul::parser::Match match(false);
                soul::parser::Match* parentMatch14 = &match;
                {
                    soul::parser::Match match(true);
                    soul::parser::Match* parentMatch15 = &match;
                    {
                        std::int64_t pos = lexer.GetPos();
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
                *parentMatch2 = match;
            }
            *parentMatch1 = match;
        }
        if (match.hit)
        {
            {
                #ifdef SOUL_PARSER_DEBUG_SUPPORT
                if (parser_debug_write_to_log) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Keyword");
                #endif
                return soul::parser::Match(true, new soul::ast::slg::Keyword(str, tokenName));
            }
        }
        *parentMatch0 = match;
    }
    #ifdef SOUL_PARSER_DEBUG_SUPPORT
    if (parser_debug_write_to_log)
    {
        if (match.hit) soul::lexer::WriteSuccessToLog(lexer, parser_debug_match_pos, "Keyword");
        else soul::lexer::WriteFailureToLog(lexer, "Keyword");
    }
    #endif
    if (!match.hit)
    {
        match.value = nullptr;
    }
    return match;
}

template struct KeywordFileParser<soul::lexer::Lexer<soul::lex::slg::SlgLexer<char32_t>, char32_t>>;

} // namespace soul::slg::keyword::file::parser
