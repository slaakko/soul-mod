// this file has been automatically generated from 'D:/work/soul-mod/test_expected/id/id.lexer' using soul lexer generator eslg version 5.0.0

export module id;

import std;
import soul_expected.lexer;
import soul_expected.ast.slg;
import util_expected;
import id.token;

using namespace soul_expected;
using namespace soul_expected::lexer;
using namespace id::token;

export namespace id {

std::mutex& MakeLexerMtx();

template<typename CharT>
struct IdLexer;

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<IdLexer<CharT>, CharT>, int> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName);

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<IdLexer<CharT>, CharT>, int> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName);

soul_expected::ast::slg::TokenCollection* GetTokens();

struct IdLexer_Variables : public soul_expected::lexer::Variables
{
    IdLexer_Variables();
};

template<typename CharT>
struct IdLexer
{
    using Variables = IdLexer_Variables;

    static std::int32_t NextState(std::int32_t state, CharT chr, soul_expected::lexer::LexerBase<CharT>& lexer)
    {
        soul_expected::lexer::ClassMap<CharT>* classmap = lexer.GetClassMap();
        std::int32_t cls = classmap->GetClass(chr);
        switch (state)
        {
            case 0:
            {
                switch (cls)
                {
                    case 2:
                    case 3:
                    {
                        return 1;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 1:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 3:
                    {
                        return 2;
                    }
                    case 4:
                    {
                        return 3;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 3:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 3:
                    {
                        return 2;
                    }
                    case 4:
                    {
                        return 3;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 2:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 3:
                    {
                        return 2;
                    }
                    case 4:
                    {
                        return 3;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
        }
        return -1;
    }

    static std::int64_t GetTokenId(std::int32_t ruleIndex, soul_expected::lexer::LexerBase<CharT>& lexer)
    {
        switch (ruleIndex)
        {
            case 0:
            {
                lexer.Retract();
                return ID;
                break;
            }
        }
        return soul_expected::lexer::CONTINUE_TOKEN;
    }
};

template<typename CharT>
std::expected<soul_expected::lexer::ClassMap<CharT>*, int> GetClassMap()
{
    static soul_expected::lexer::ClassMap<CharT>* classmap;
    if (!classmap)
    {
        std::expected<ClassMap<CharT>*, int> rv = soul_expected::lexer::MakeClassMap<CharT>("id.classmap");
        if (!rv) return std::unexpected<int>(rv.error());
        classmap = *rv;
    }
    return classmap;
}

template<typename CharT>
std::expected<soul_expected::lexer::ClassMap<CharT>*, int> GetClassMap(const std::string & moduleFileName, util::ResourceFlags resourceFlags)
{
    static soul_expected::lexer::ClassMap<CharT>* classmap;
    if (!classmap)
    {
        std::expected<ClassMap<CharT>*, int> rv = soul_expected::lexer::MakeClassMap<CharT>(moduleFileName, "id.classmap", resourceFlags);
        if (!rv) return std::unexpected<int>(rv.error());
        classmap = *rv;
    }
    return classmap;
}

template<typename CharT>
soul_expected::lexer::KeywordMap<CharT>* GetKeywords();

template<>
soul_expected::lexer::KeywordMap<char>* GetKeywords<char>();

template<>
soul_expected::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>();

template<>
soul_expected::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>();

template<>
soul_expected::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>();

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<IdLexer<CharT>, CharT>, int> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul_expected::lexer::Lexer<IdLexer<CharT>, CharT>(start, end, fileName);
    std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>();
    if (!rv) return std::unexpected<int>(rv.error());
    lexer.SetClassMap(*rv);
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<CharT>());
    return lexer;
}

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<IdLexer<CharT>, CharT>, int> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul_expected::lexer::Lexer<IdLexer<CharT>, CharT>(start, end, fileName);
    std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>(moduleFileName, resourceFlags);
    if (!rv) return std::unexpected<int>(rv.error());
    lexer.SetClassMap(*rv);
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<CharT>());
    return lexer;
}

} // namespace id
