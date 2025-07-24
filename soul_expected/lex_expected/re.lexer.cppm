// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/lex_expected/re.lexer' using soul lexer generator eslg version 5.0.0

export module soul_expected.lex.re;

import std;
import soul_expected.lexer;
import soul_expected.ast.slg;
import util_expected;
import soul_expected.cpp.token;
import soul_expected.cpp.op.token;
import soul_expected.punctuation.token;
import soul_expected.tool.token;

using namespace soul_expected;
using namespace soul_expected::lexer;
using namespace soul_expected::cpp::token;
using namespace soul_expected::cpp::op::token;
using namespace soul_expected::punctuation::token;
using namespace soul_expected::tool::token;

export namespace soul_expected::lex::re {

std::mutex& MakeLexerMtx();

template<typename CharT>
struct RegExLexer;

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<RegExLexer<CharT>, CharT>, int> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName);

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<RegExLexer<CharT>, CharT>, int> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName);

soul_expected::ast::slg::TokenCollection* GetTokens();

struct RegExLexer_Variables : public soul_expected::lexer::Variables
{
    RegExLexer_Variables();
};

template<typename CharT>
struct RegExLexer
{
    using Variables = RegExLexer_Variables;

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
                    case 0:
                    {
                        return 1;
                    }
                    case 1:
                    {
                        return 2;
                    }
                    case 2:
                    {
                        return 3;
                    }
                    case 3:
                    {
                        return 4;
                    }
                    case 4:
                    {
                        return 5;
                    }
                    case 5:
                    {
                        return 6;
                    }
                    case 6:
                    {
                        return 7;
                    }
                    case 7:
                    {
                        return 8;
                    }
                    case 8:
                    {
                        return 9;
                    }
                    case 9:
                    {
                        return 10;
                    }
                    case 10:
                    {
                        return 11;
                    }
                    case 11:
                    {
                        return 12;
                    }
                    case 12:
                    {
                        return 13;
                    }
                    case 13:
                    {
                        return 14;
                    }
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    {
                        return 15;
                    }
                    case 35:
                    {
                        return 16;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 16:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 1;
                    }
                    case 1:
                    {
                        return 2;
                    }
                    case 2:
                    {
                        return 3;
                    }
                    case 3:
                    {
                        return 4;
                    }
                    case 4:
                    {
                        return 5;
                    }
                    case 5:
                    {
                        return 6;
                    }
                    case 6:
                    {
                        return 7;
                    }
                    case 7:
                    {
                        return 8;
                    }
                    case 8:
                    {
                        return 9;
                    }
                    case 9:
                    {
                        return 10;
                    }
                    case 10:
                    {
                        return 11;
                    }
                    case 11:
                    {
                        return 12;
                    }
                    case 12:
                    {
                        return 13;
                    }
                    case 13:
                    {
                        return 14;
                    }
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    {
                        return 15;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 15:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(14, lexer);
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
                return -1;
            }
            case 14:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 22:
                    case 25:
                    case 34:
                    case 36:
                    case 37:
                    {
                        return 17;
                    }
                    case 18:
                    {
                        return 18;
                    }
                    case 19:
                    {
                        return 19;
                    }
                    case 20:
                    {
                        return 20;
                    }
                    case 21:
                    {
                        return 21;
                    }
                    case 23:
                    {
                        return 22;
                    }
                    case 24:
                    {
                        return 23;
                    }
                    case 26:
                    {
                        return 24;
                    }
                    case 27:
                    {
                        return 25;
                    }
                    case 28:
                    {
                        return 26;
                    }
                    case 29:
                    {
                        return 27;
                    }
                    case 30:
                    {
                        return 28;
                    }
                    case 31:
                    {
                        return 29;
                    }
                    case 32:
                    {
                        return 30;
                    }
                    case 33:
                    {
                        return 31;
                    }
                    case 35:
                    {
                        return 32;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 32:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 22:
                    case 25:
                    case 34:
                    case 36:
                    case 37:
                    {
                        return 17;
                    }
                    case 18:
                    {
                        return 18;
                    }
                    case 19:
                    {
                        return 19;
                    }
                    case 20:
                    {
                        return 20;
                    }
                    case 21:
                    {
                        return 21;
                    }
                    case 23:
                    {
                        return 22;
                    }
                    case 24:
                    {
                        return 23;
                    }
                    case 26:
                    {
                        return 24;
                    }
                    case 27:
                    {
                        return 25;
                    }
                    case 28:
                    {
                        return 26;
                    }
                    case 29:
                    {
                        return 27;
                    }
                    case 30:
                    {
                        return 28;
                    }
                    case 31:
                    {
                        return 29;
                    }
                    case 32:
                    {
                        return 30;
                    }
                    case 33:
                    {
                        return 31;
                    }
                    case 35:
                    {
                        return 33;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 33:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 22:
                    case 25:
                    case 34:
                    case 36:
                    case 37:
                    {
                        return 17;
                    }
                    case 18:
                    {
                        return 18;
                    }
                    case 19:
                    {
                        return 19;
                    }
                    case 20:
                    {
                        return 20;
                    }
                    case 21:
                    {
                        return 21;
                    }
                    case 23:
                    {
                        return 22;
                    }
                    case 24:
                    {
                        return 23;
                    }
                    case 26:
                    {
                        return 24;
                    }
                    case 27:
                    {
                        return 25;
                    }
                    case 28:
                    {
                        return 26;
                    }
                    case 29:
                    {
                        return 27;
                    }
                    case 30:
                    {
                        return 28;
                    }
                    case 31:
                    {
                        return 29;
                    }
                    case 32:
                    {
                        return 30;
                    }
                    case 33:
                    {
                        return 31;
                    }
                    case 35:
                    {
                        return 34;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 34:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 18:
                    {
                        return 35;
                    }
                    case 19:
                    {
                        return 36;
                    }
                    case 20:
                    {
                        return 37;
                    }
                    case 23:
                    {
                        return 38;
                    }
                    case 24:
                    {
                        return 39;
                    }
                    case 26:
                    {
                        return 40;
                    }
                    case 27:
                    {
                        return 41;
                    }
                    case 28:
                    {
                        return 42;
                    }
                    case 29:
                    {
                        return 43;
                    }
                    case 30:
                    {
                        return 44;
                    }
                    case 31:
                    {
                        return 45;
                    }
                    case 32:
                    {
                        return 46;
                    }
                    case 33:
                    {
                        return 47;
                    }
                    case 35:
                    {
                        return 48;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 48:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 18:
                    {
                        return 35;
                    }
                    case 19:
                    {
                        return 36;
                    }
                    case 23:
                    {
                        return 38;
                    }
                    case 24:
                    {
                        return 39;
                    }
                    case 26:
                    {
                        return 40;
                    }
                    case 27:
                    {
                        return 41;
                    }
                    case 28:
                    {
                        return 42;
                    }
                    case 29:
                    {
                        return 43;
                    }
                    case 30:
                    {
                        return 44;
                    }
                    case 31:
                    {
                        return 45;
                    }
                    case 32:
                    {
                        return 46;
                    }
                    case 35:
                    {
                        return 49;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 49:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 18:
                    {
                        return 35;
                    }
                    case 19:
                    {
                        return 36;
                    }
                    case 23:
                    {
                        return 38;
                    }
                    case 24:
                    {
                        return 39;
                    }
                    case 26:
                    {
                        return 40;
                    }
                    case 27:
                    {
                        return 41;
                    }
                    case 28:
                    {
                        return 42;
                    }
                    case 29:
                    {
                        return 43;
                    }
                    case 30:
                    {
                        return 44;
                    }
                    case 31:
                    {
                        return 45;
                    }
                    case 35:
                    {
                        return 50;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 50:
            {
                switch (cls)
                {
                    case 18:
                    {
                        return 35;
                    }
                    case 19:
                    {
                        return 36;
                    }
                    case 23:
                    {
                        return 38;
                    }
                    case 24:
                    {
                        return 39;
                    }
                    case 27:
                    {
                        return 41;
                    }
                    case 28:
                    {
                        return 42;
                    }
                    case 29:
                    {
                        return 43;
                    }
                    case 30:
                    {
                        return 44;
                    }
                    case 35:
                    {
                        return 51;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 51:
            {
                switch (cls)
                {
                    case 27:
                    {
                        return 41;
                    }
                    case 28:
                    {
                        return 42;
                    }
                    case 29:
                    {
                        return 43;
                    }
                    case 35:
                    {
                        return 52;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 52:
            {
                switch (cls)
                {
                    case 27:
                    {
                        return 41;
                    }
                    case 28:
                    {
                        return 42;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 47:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 53;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 53:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 54;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 54:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 55;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 55:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                return -1;
            }
            case 46:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 56;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 56:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 53;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 45:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 57;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 57:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 56;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 44:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 58;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 58:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 57;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 43:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 59;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 59:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 58;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 42:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 60;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 60:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 59;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 41:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 60;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 40:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 26:
                    {
                        return 40;
                    }
                    case 35:
                    {
                        return 61;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 61:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 26:
                    {
                        return 40;
                    }
                    case 35:
                    {
                        return 62;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 62:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 63;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 63:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 64;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 64:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 55;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 39:
            {
                switch (cls)
                {
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    case 35:
                    {
                        return 66;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 66:
            {
                switch (cls)
                {
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    case 35:
                    {
                        return 67;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 67:
            {
                switch (cls)
                {
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 65:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    case 35:
                    {
                        return 68;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 68:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    case 35:
                    {
                        return 69;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 69:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 62;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 38:
            {
                switch (cls)
                {
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    case 35:
                    {
                        return 66;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 37:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 70;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 70:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 71;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 71:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 72;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 72:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 73;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 73:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 63;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 36:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    case 35:
                    {
                        return 75;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 75:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    case 35:
                    {
                        return 76;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 76:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 74:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    case 35:
                    {
                        return 77;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 77:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 69;
                    }
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 35:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    case 35:
                    {
                        return 75;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 31:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 53;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 30:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 56;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 29:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 57;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 28:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 58;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 27:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 59;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 26:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 60;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 25:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 60;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 24:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 26:
                    {
                        return 40;
                    }
                    case 35:
                    {
                        return 78;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 78:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 26:
                    {
                        return 40;
                    }
                    case 35:
                    {
                        return 62;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 23:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    case 35:
                    {
                        return 79;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 79:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    case 35:
                    {
                        return 80;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 80:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 22:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 25:
                    case 26:
                    {
                        return 65;
                    }
                    case 35:
                    {
                        return 79;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 21:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 54;
                    }
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 81;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 81:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 82;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 82:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 83;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 83:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 84;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 84:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 85;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 85:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 86;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 86:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 87;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 87:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 88;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 88:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 64;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 20:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 54;
                    }
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 70;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 19:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    case 35:
                    {
                        return 89;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 89:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    case 35:
                    {
                        return 90;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 90:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 18:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    {
                        return 74;
                    }
                    case 35:
                    {
                        return 89;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 17:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
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
                    case 35:
                    {
                        return 54;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 13:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(12, lexer);
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
                return -1;
            }
            case 12:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(11, lexer);
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
                return -1;
            }
            case 11:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(10, lexer);
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
                return -1;
            }
            case 10:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(9, lexer);
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
                return -1;
            }
            case 9:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(8, lexer);
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
                return -1;
            }
            case 8:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(7, lexer);
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
                return -1;
            }
            case 7:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(6, lexer);
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
                return -1;
            }
            case 6:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(5, lexer);
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
                return -1;
            }
            case 5:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(4, lexer);
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
                return -1;
            }
            case 4:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(3, lexer);
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
                return -1;
            }
            case 3:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
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
                return -1;
            }
            case 2:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(1, lexer);
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
                return -1;
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
                return -1;
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
                return LPAREN;
                break;
            }
            case 1:
            {
                lexer.Retract();
                return RPAREN;
                break;
            }
            case 2:
            {
                lexer.Retract();
                return LBRACKET;
                break;
            }
            case 3:
            {
                lexer.Retract();
                return RBRACKET;
                break;
            }
            case 4:
            {
                lexer.Retract();
                return LBRACE;
                break;
            }
            case 5:
            {
                lexer.Retract();
                return RBRACE;
                break;
            }
            case 6:
            {
                lexer.Retract();
                return PIPE;
                break;
            }
            case 7:
            {
                lexer.Retract();
                return STAR;
                break;
            }
            case 8:
            {
                lexer.Retract();
                return PLUS;
                break;
            }
            case 9:
            {
                lexer.Retract();
                return QUEST;
                break;
            }
            case 10:
            {
                lexer.Retract();
                return DOT;
                break;
            }
            case 11:
            {
                lexer.Retract();
                return CARET;
                break;
            }
            case 12:
            {
                lexer.Retract();
                return MINUS;
                break;
            }
            case 13:
            {
                lexer.Retract();
                return ESCAPE;
                break;
            }
            case 14:
            {
                lexer.Retract();
                return CHARACTER;
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
        std::expected<ClassMap<CharT>*, int> rv = soul_expected::lexer::MakeClassMap<CharT>("soul_expected.lex.re.classmap");
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
        std::expected<ClassMap<CharT>*, int> rv = soul_expected::lexer::MakeClassMap<CharT>(moduleFileName, "soul_expected.lex.re.classmap", resourceFlags);
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
std::expected<soul_expected::lexer::Lexer<RegExLexer<CharT>, CharT>, int> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul_expected::lexer::Lexer<RegExLexer<CharT>, CharT>(start, end, fileName);
    std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>();
    if (!rv) return std::unexpected<int>(rv.error());
    lexer.SetClassMap(*rv);
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<CharT>());
    return lexer;
}

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<RegExLexer<CharT>, CharT>, int> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul_expected::lexer::Lexer<RegExLexer<CharT>, CharT>(start, end, fileName);
    std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>(moduleFileName, resourceFlags);
    if (!rv) return std::unexpected<int>(rv.error());
    lexer.SetClassMap(*rv);
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<CharT>());
    return lexer;
}

} // namespace soul_expected::lex::re
