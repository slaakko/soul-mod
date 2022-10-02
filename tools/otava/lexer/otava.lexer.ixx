// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/lexer/otava.lexer' using soul lexer generator slg version 4.1.0

export module otava.lexer;

import std.core;
import soul.lexer;
import soul.ast.slg;
import otava.token;

using namespace soul;
using namespace soul::lexer;
using namespace otava::token;

export namespace otava::lexer {

std::mutex& MakeLexerMtx();

template<typename Char>
struct OtavaLexer;

template<typename Char>
soul::lexer::Lexer<OtavaLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName);

soul::ast::slg::TokenCollection* GetTokens();

struct OtavaLexer_Variables : public soul::lexer::Variables
{
    OtavaLexer_Variables();
    int langleCount;
};

template<typename Char>
struct OtavaLexer
{
    using Variables = OtavaLexer_Variables;

    static int32_t NextState(int32_t state, Char chr, soul::lexer::LexerBase<Char>& lexer)
    {
        ClassMap<Char>* classmap = lexer.GetClassMap();
        int32_t cls = classmap->GetClass(chr);
        switch (state)
        {
            case 0:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 2;
                    }
                    case 3:
                    {
                        return 3;
                    }
                    case 4:
                    case 5:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 18:
                    case 19:
                    case 20:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 4;
                    }
                    case 13:
                    {
                        return 5;
                    }
                    case 14:
                    {
                        return 6;
                    }
                    case 15:
                    {
                        return 7;
                    }
                    case 16:
                    {
                        return 8;
                    }
                    case 17:
                    {
                        return 9;
                    }
                    case 21:
                    {
                        return 10;
                    }
                    case 22:
                    {
                        return 11;
                    }
                    case 23:
                    {
                        return 12;
                    }
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 14;
                    }
                    case 26:
                    {
                        return 15;
                    }
                    case 35:
                    case 37:
                    case 42:
                    case 43:
                    {
                        return 16;
                    }
                    case 41:
                    {
                        return 17;
                    }
                    case 44:
                    case 45:
                    {
                        return 18;
                    }
                    case 46:
                    {
                        return 19;
                    }
                    case 47:
                    {
                        return 20;
                    }
                    case 48:
                    {
                        return 21;
                    }
                    case 49:
                    {
                        return 22;
                    }
                    case 50:
                    {
                        return 23;
                    }
                    case 51:
                    {
                        return 24;
                    }
                    case 52:
                    {
                        return 25;
                    }
                    case 53:
                    {
                        return 26;
                    }
                    case 54:
                    {
                        return 27;
                    }
                    case 55:
                    {
                        return 28;
                    }
                    case 56:
                    {
                        return 29;
                    }
                    case 57:
                    {
                        return 30;
                    }
                    case 58:
                    {
                        return 31;
                    }
                    case 59:
                    {
                        return 32;
                    }
                    case 60:
                    {
                        return 33;
                    }
                    case 61:
                    {
                        return 34;
                    }
                    case 62:
                    {
                        return 35;
                    }
                    case 63:
                    {
                        return 36;
                    }
                    case 64:
                    {
                        return 37;
                    }
                    case 65:
                    {
                        return 38;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 38:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(57, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 37:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(56, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 36:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(54, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 35:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(51, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 34:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(50, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 33:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(49, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 32:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(45, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 31:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(44, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 30:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(48, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 39;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 39:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(29, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 29:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(25, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 40;
                    }
                    case 56:
                    {
                        return 41;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(23, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 40:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(20, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 28:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(26, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 42;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(19, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 27:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(27, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 43;
                    }
                    case 54:
                    {
                        return 44;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(24, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 43:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(18, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 26:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(33, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 45;
                    }
                    case 53:
                    {
                        return 46;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 46:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(35, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 47;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(17, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 45:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(30, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 52:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(32, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 25:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(34, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 49;
                    }
                    case 52:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(36, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(16, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 49:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(31, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 24:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(41, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 23:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(10, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(28, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 22:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(9, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 21:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(22, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 48:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 20:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 2;
                    }
                    case 3:
                    {
                        return 3;
                    }
                    case 4:
                    case 5:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 18:
                    case 19:
                    case 20:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 4;
                    }
                    case 13:
                    {
                        return 5;
                    }
                    case 14:
                    {
                        return 6;
                    }
                    case 15:
                    {
                        return 7;
                    }
                    case 16:
                    {
                        return 8;
                    }
                    case 17:
                    {
                        return 9;
                    }
                    case 21:
                    {
                        return 10;
                    }
                    case 22:
                    {
                        return 11;
                    }
                    case 23:
                    {
                        return 12;
                    }
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 14;
                    }
                    case 26:
                    {
                        return 15;
                    }
                    case 35:
                    case 37:
                    case 42:
                    case 43:
                    {
                        return 16;
                    }
                    case 41:
                    {
                        return 17;
                    }
                    case 44:
                    case 45:
                    {
                        return 18;
                    }
                    case 46:
                    {
                        return 19;
                    }
                    case 48:
                    {
                        return 21;
                    }
                    case 49:
                    {
                        return 22;
                    }
                    case 50:
                    {
                        return 23;
                    }
                    case 51:
                    {
                        return 24;
                    }
                    case 52:
                    {
                        return 25;
                    }
                    case 53:
                    {
                        return 26;
                    }
                    case 54:
                    {
                        return 27;
                    }
                    case 55:
                    {
                        return 28;
                    }
                    case 56:
                    {
                        return 29;
                    }
                    case 57:
                    {
                        return 30;
                    }
                    case 58:
                    {
                        return 31;
                    }
                    case 59:
                    {
                        return 32;
                    }
                    case 60:
                    {
                        return 33;
                    }
                    case 61:
                    {
                        return 34;
                    }
                    case 62:
                    {
                        return 35;
                    }
                    case 63:
                    {
                        return 36;
                    }
                    case 64:
                    {
                        return 37;
                    }
                    case 65:
                    {
                        return 38;
                    }
                    case 47:
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
                switch (cls)
                {
                    case 0:
                    case 1:
                    {
                        return 1;
                    }
                    case 4:
                    case 5:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 18:
                    case 19:
                    case 20:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 4;
                    }
                    case 13:
                    {
                        return 5;
                    }
                    case 14:
                    {
                        return 6;
                    }
                    case 21:
                    {
                        return 10;
                    }
                    case 22:
                    {
                        return 11;
                    }
                    case 23:
                    {
                        return 12;
                    }
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 14;
                    }
                    case 35:
                    case 37:
                    case 42:
                    case 43:
                    {
                        return 16;
                    }
                    case 41:
                    {
                        return 17;
                    }
                    case 44:
                    case 45:
                    {
                        return 18;
                    }
                    case 46:
                    {
                        return 19;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 15:
                    {
                        return 57;
                    }
                    case 47:
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
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 23:
                    {
                        return 12;
                    }
                    case 41:
                    {
                        return 17;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 15:
                    {
                        return 57;
                    }
                    case 13:
                    {
                        return 59;
                    }
                    case 14:
                    {
                        return 60;
                    }
                    case 25:
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 47:
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
                switch (cls)
                {
                    case 2:
                    {
                        return 56;
                    }
                    case 15:
                    {
                        return 57;
                    }
                    case 13:
                    {
                        return 59;
                    }
                    case 25:
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 41:
                    {
                        return 64;
                    }
                    case 47:
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
                switch (cls)
                {
                    case 15:
                    {
                        return 57;
                    }
                    case 25:
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 41:
                    {
                        return 66;
                    }
                    case 47:
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
                    {
                        return 68;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
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
                switch (cls)
                {
                    case 25:
                    {
                        return 68;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 69;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 47:
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
                    case 25:
                    {
                        return 68;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 69;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 47:
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
                    case 47:
                    {
                        return 67;
                    }
                    case 25:
                    {
                        return 68;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 69;
                    }
                    case 15:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 25:
                    {
                        return 74;
                    }
                    case 33:
                    case 34:
                    {
                        return 75;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 25:
                    {
                        return 74;
                    }
                    case 33:
                    case 34:
                    {
                        return 75;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 25:
                    {
                        return 74;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 77:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 82;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 76:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 25:
                    {
                        return 74;
                    }
                    case 33:
                    case 34:
                    {
                        return 75;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 25:
                    {
                        return 74;
                    }
                    case 33:
                    case 34:
                    {
                        return 75;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 25:
                    {
                        return 74;
                    }
                    case 33:
                    case 34:
                    {
                        return 75;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 25:
                    {
                        return 74;
                    }
                    case 33:
                    case 34:
                    {
                        return 75;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
                    {
                        return 80;
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
                    case 16:
                    {
                        return 88;
                    }
                    case 17:
                    {
                        return 89;
                    }
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 92:
            {
                switch (cls)
                {
                    case 16:
                    {
                        return 88;
                    }
                    case 17:
                    {
                        return 89;
                    }
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 93;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 93:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 94;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 94:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 91:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 95;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 95:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 96;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 96:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 97;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 97:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
                    {
                        return 81;
                    }
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 95;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 89:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 98;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 98:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 93;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 88:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 98;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 25:
                    {
                        return 74;
                    }
                    case 33:
                    case 34:
                    {
                        return 75;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
                    {
                        return 84;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 83;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 68:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 68;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 69;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 47:
                    {
                        return 71;
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
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 9:
                    {
                        return 99;
                    }
                    case 10:
                    {
                        return 100;
                    }
                    case 32:
                    {
                        return 101;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 38:
                    {
                        return 103;
                    }
                    case 47:
                    {
                        return 104;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 104:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 47:
                    {
                        return 105;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 105:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 47:
                    {
                        return 106;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 106:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 103:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 47:
                    {
                        return 110;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 110:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 47:
                    {
                        return 111;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 111:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 47:
                    {
                        return 112;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 112:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 47:
                    {
                        return 113;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 113:
            {
                switch (cls)
                {
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 109:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 11:
                    case 12:
                    {
                        return 114;
                    }
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 116;
                    }
                    case 21:
                    {
                        return 117;
                    }
                    case 47:
                    {
                        return 118;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 118:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 11:
                    case 12:
                    {
                        return 114;
                    }
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 116;
                    }
                    case 21:
                    {
                        return 117;
                    }
                    case 47:
                    {
                        return 119;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 119:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 11:
                    case 12:
                    {
                        return 114;
                    }
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 116;
                    }
                    case 21:
                    {
                        return 117;
                    }
                    case 47:
                    {
                        return 120;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 120:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 11:
                    case 12:
                    {
                        return 114;
                    }
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 116;
                    }
                    case 21:
                    {
                        return 117;
                    }
                    case 47:
                    {
                        return 121;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 121:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 11:
                    case 12:
                    {
                        return 114;
                    }
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 116;
                    }
                    case 21:
                    {
                        return 117;
                    }
                    case 47:
                    {
                        return 122;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 122:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 116;
                    }
                    case 21:
                    {
                        return 117;
                    }
                    case 47:
                    {
                        return 123;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 123:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 124;
                    }
                    case 21:
                    {
                        return 125;
                    }
                    case 47:
                    {
                        return 126;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 126:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 124;
                    }
                    case 21:
                    {
                        return 125;
                    }
                    case 47:
                    {
                        return 127;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 127:
            {
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 128;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 128:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 129;
                    }
                    case 21:
                    {
                        return 130;
                    }
                    case 47:
                    {
                        return 131;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 131:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 132;
                    }
                    case 21:
                    {
                        return 133;
                    }
                    case 47:
                    {
                        return 134;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 134:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 135;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 135:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 136;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 136:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 137;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 137:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 138;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 138:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 139;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 139:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 140;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 140:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 141;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 141:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 133:
            {
                switch (cls)
                {
                    case 21:
                    {
                        return 142;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 142:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 143;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 143:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 134;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 132:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 144;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 144:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 143;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 130:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 134;
                    }
                    case 21:
                    {
                        return 142;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 129:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 134;
                    }
                    case 20:
                    {
                        return 144;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 125:
            {
                switch (cls)
                {
                    case 21:
                    {
                        return 145;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 145:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 146;
                    }
                    case 47:
                    {
                        return 147;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 147:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 146;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 146:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 136;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 124:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 148;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 148:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 146;
                    }
                    case 47:
                    {
                        return 147;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 117:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 21:
                    {
                        return 145;
                    }
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 149;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 149:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 137;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 116:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 148;
                    }
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 149;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 115:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 129;
                    }
                    case 21:
                    {
                        return 130;
                    }
                    case 47:
                    {
                        return 131;
                    }
                    case 11:
                    case 12:
                    {
                        return 150;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 150:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 135;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 114:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 151;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 151:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 138;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 108:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 11:
                    case 12:
                    {
                        return 114;
                    }
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 116;
                    }
                    case 21:
                    {
                        return 117;
                    }
                    case 47:
                    {
                        return 118;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 107:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 11:
                    case 12:
                    {
                        return 114;
                    }
                    case 13:
                    case 14:
                    {
                        return 115;
                    }
                    case 20:
                    {
                        return 116;
                    }
                    case 21:
                    {
                        return 117;
                    }
                    case 47:
                    {
                        return 119;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 102:
            {
                switch (cls)
                {
                    case 16:
                    {
                        return 152;
                    }
                    case 17:
                    {
                        return 153;
                    }
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 156;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 156:
            {
                switch (cls)
                {
                    case 16:
                    {
                        return 152;
                    }
                    case 17:
                    {
                        return 153;
                    }
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 157;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 157:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 158;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 158:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 155:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 159;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 159:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 160;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 160:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 161;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 161:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
                    {
                        return 81;
                    }
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 154:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 159;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 153:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 162;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 162:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 157;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 152:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 162;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 101:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 107;
                    }
                    case 41:
                    {
                        return 108;
                    }
                    case 43:
                    {
                        return 109;
                    }
                    case 47:
                    {
                        return 110;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 100:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    case 47:
                    {
                        return 165;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 165:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    case 47:
                    {
                        return 166;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 166:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    case 47:
                    {
                        return 167;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 167:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 164:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 47:
                    {
                        return 172;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 172:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 47:
                    {
                        return 173;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 173:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 47:
                    {
                        return 174;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 174:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 47:
                    {
                        return 175;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 175:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 47:
                    {
                        return 176;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 176:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 177;
                    }
                    case 21:
                    {
                        return 178;
                    }
                    case 47:
                    {
                        return 179;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 179:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 177;
                    }
                    case 21:
                    {
                        return 178;
                    }
                    case 47:
                    {
                        return 180;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 180:
            {
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 181;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 181:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 182;
                    }
                    case 21:
                    {
                        return 183;
                    }
                    case 47:
                    {
                        return 184;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 184:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 185;
                    }
                    case 21:
                    {
                        return 186;
                    }
                    case 47:
                    {
                        return 187;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 187:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 188;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 188:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 189;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 189:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 190;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 190:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 191;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 191:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 139;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 186:
            {
                switch (cls)
                {
                    case 21:
                    {
                        return 192;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 192:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 193:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 187;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 185:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 194;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 194:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 183:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 187;
                    }
                    case 21:
                    {
                        return 192;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 182:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 187;
                    }
                    case 20:
                    {
                        return 194;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 178:
            {
                switch (cls)
                {
                    case 21:
                    {
                        return 195;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 195:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 196;
                    }
                    case 47:
                    {
                        return 197;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 197:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 196;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 196:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 189;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 177:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 198;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 198:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 196;
                    }
                    case 47:
                    {
                        return 197;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 171:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 21:
                    {
                        return 195;
                    }
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 199;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 199:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 190;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 170:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 198;
                    }
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 199;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 169:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 182;
                    }
                    case 21:
                    {
                        return 183;
                    }
                    case 47:
                    {
                        return 184;
                    }
                    case 11:
                    case 12:
                    {
                        return 200;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 200:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 188;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 168:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 201;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 201:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 191;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 163:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 47:
                    {
                        return 172;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 99:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 163;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 164;
                    }
                    case 47:
                    {
                        return 165;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 64:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 32:
                    {
                        return 101;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 38:
                    {
                        return 103;
                    }
                    case 47:
                    {
                        return 104;
                    }
                    case 9:
                    {
                        return 202;
                    }
                    case 10:
                    {
                        return 203;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 203:
            {
                switch (cls)
                {
                    case 15:
                    {
                        return 204;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    case 47:
                    {
                        return 207;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 207:
            {
                switch (cls)
                {
                    case 15:
                    {
                        return 204;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    case 47:
                    {
                        return 208;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 208:
            {
                switch (cls)
                {
                    case 15:
                    {
                        return 204;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    case 47:
                    {
                        return 209;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 209:
            {
                switch (cls)
                {
                    case 15:
                    {
                        return 204;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    case 47:
                    {
                        return 210;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 210:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 211;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 212;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 212:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 211;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 212;
                    }
                    case 15:
                    {
                        return 213;
                    }
                    case 47:
                    {
                        return 214;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 214:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 211;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 212;
                    }
                    case 15:
                    {
                        return 213;
                    }
                    case 47:
                    {
                        return 215;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 215:
            {
                switch (cls)
                {
                    case 47:
                    {
                        return 210;
                    }
                    case 25:
                    {
                        return 211;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 212;
                    }
                    case 15:
                    {
                        return 213;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 213:
            {
                switch (cls)
                {
                    case 18:
                    case 19:
                    {
                        return 216;
                    }
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    case 47:
                    {
                        return 219;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 219:
            {
                switch (cls)
                {
                    case 18:
                    case 19:
                    {
                        return 216;
                    }
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    case 47:
                    {
                        return 220;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 220:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 218:
            {
                switch (cls)
                {
                    case 18:
                    case 19:
                    {
                        return 216;
                    }
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    case 47:
                    {
                        return 221;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 221:
            {
                switch (cls)
                {
                    case 18:
                    case 19:
                    {
                        return 216;
                    }
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    case 47:
                    {
                        return 222;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 222:
            {
                switch (cls)
                {
                    case 18:
                    case 19:
                    {
                        return 216;
                    }
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    case 47:
                    {
                        return 223;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 223:
            {
                switch (cls)
                {
                    case 18:
                    case 19:
                    {
                        return 216;
                    }
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 217:
            {
                switch (cls)
                {
                    case 18:
                    case 19:
                    {
                        return 216;
                    }
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    case 47:
                    {
                        return 221;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 216:
            {
                switch (cls)
                {
                    case 16:
                    {
                        return 224;
                    }
                    case 17:
                    {
                        return 225;
                    }
                    case 25:
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 47:
                    {
                        return 228;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 228:
            {
                switch (cls)
                {
                    case 16:
                    {
                        return 224;
                    }
                    case 17:
                    {
                        return 225;
                    }
                    case 25:
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 47:
                    {
                        return 229;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 229:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 47:
                    {
                        return 230;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 230:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 227:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 20:
                    case 21:
                    {
                        return 231;
                    }
                    case 36:
                    case 39:
                    {
                        return 232;
                    }
                    case 47:
                    {
                        return 233;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 233:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 20:
                    case 21:
                    {
                        return 231;
                    }
                    case 36:
                    case 39:
                    {
                        return 232;
                    }
                    case 47:
                    {
                        return 234;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 234:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 20:
                    case 21:
                    {
                        return 231;
                    }
                    case 36:
                    case 39:
                    {
                        return 232;
                    }
                    case 47:
                    {
                        return 235;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 235:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 20:
                    case 21:
                    {
                        return 231;
                    }
                    case 36:
                    case 39:
                    {
                        return 232;
                    }
                    case 47:
                    {
                        return 236;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 236:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 82;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 232:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 237;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 237:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 236;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 231:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 237;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 226:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 20:
                    case 21:
                    {
                        return 231;
                    }
                    case 36:
                    case 39:
                    {
                        return 232;
                    }
                    case 47:
                    {
                        return 233;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 225:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 47:
                    {
                        return 238;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 238:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 47:
                    {
                        return 229;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 224:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 226;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 227;
                    }
                    case 47:
                    {
                        return 238;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 211:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 211;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 212;
                    }
                    case 15:
                    {
                        return 213;
                    }
                    case 47:
                    {
                        return 214;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 206:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    case 15:
                    {
                        return 213;
                    }
                    case 18:
                    case 19:
                    {
                        return 239;
                    }
                    case 47:
                    {
                        return 240;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 240:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    case 15:
                    {
                        return 213;
                    }
                    case 18:
                    case 19:
                    {
                        return 239;
                    }
                    case 47:
                    {
                        return 241;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 241:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    case 15:
                    {
                        return 213;
                    }
                    case 18:
                    case 19:
                    {
                        return 239;
                    }
                    case 47:
                    {
                        return 242;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 242:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 47:
                    {
                        return 175;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 239:
            {
                switch (cls)
                {
                    case 16:
                    {
                        return 243;
                    }
                    case 17:
                    {
                        return 244;
                    }
                    case 25:
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 47:
                    {
                        return 247;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 247:
            {
                switch (cls)
                {
                    case 16:
                    {
                        return 243;
                    }
                    case 17:
                    {
                        return 244;
                    }
                    case 25:
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 47:
                    {
                        return 248;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 248:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 47:
                    {
                        return 249;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 249:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 246:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 20:
                    case 21:
                    {
                        return 250;
                    }
                    case 36:
                    case 39:
                    {
                        return 251;
                    }
                    case 47:
                    {
                        return 252;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 252:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 20:
                    case 21:
                    {
                        return 250;
                    }
                    case 36:
                    case 39:
                    {
                        return 251;
                    }
                    case 47:
                    {
                        return 253;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 253:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 20:
                    case 21:
                    {
                        return 250;
                    }
                    case 36:
                    case 39:
                    {
                        return 251;
                    }
                    case 47:
                    {
                        return 254;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 254:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 236;
                    }
                    case 25:
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 20:
                    case 21:
                    {
                        return 250;
                    }
                    case 36:
                    case 39:
                    {
                        return 251;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 251:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 255;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 255:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 236;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 250:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 255;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 245:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 20:
                    case 21:
                    {
                        return 250;
                    }
                    case 36:
                    case 39:
                    {
                        return 251;
                    }
                    case 47:
                    {
                        return 252;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 244:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 47:
                    {
                        return 256;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 256:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 47:
                    {
                        return 248;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 243:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 245;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 246;
                    }
                    case 47:
                    {
                        return 256;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 205:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 11:
                    case 12:
                    {
                        return 168;
                    }
                    case 13:
                    case 14:
                    {
                        return 169;
                    }
                    case 20:
                    {
                        return 170;
                    }
                    case 21:
                    {
                        return 171;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    case 15:
                    {
                        return 213;
                    }
                    case 18:
                    case 19:
                    {
                        return 239;
                    }
                    case 47:
                    {
                        return 240;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 204:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    case 47:
                    {
                        return 257;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 257:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 217;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 218;
                    }
                    case 47:
                    {
                        return 220;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 202:
            {
                switch (cls)
                {
                    case 15:
                    {
                        return 204;
                    }
                    case 25:
                    {
                        return 205;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 206;
                    }
                    case 47:
                    {
                        return 207;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 62:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 47:
                    {
                        return 104;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 61:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 47:
                    {
                        return 104;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 60:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 22:
                    {
                        return 258;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 47:
                    {
                        return 260;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 260:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 22:
                    {
                        return 258;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 47:
                    {
                        return 261;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 261:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 22:
                    {
                        return 258;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 259:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 264:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(4, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 263:
            {
                switch (cls)
                {
                    case 9:
                    {
                        return 265;
                    }
                    case 13:
                    {
                        return 266;
                    }
                    case 14:
                    {
                        return 267;
                    }
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 268;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 269;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 269:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 270;
                    }
                    case 47:
                    {
                        return 271;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 271:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 272;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 272:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 273;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 273:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 274;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 274:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 270:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 271;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 275;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 275:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 272;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 268:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 273;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 267:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 276;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 276:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 277;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 277:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 278;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 278:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 279;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 279:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 280;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 280:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 281;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 281:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 282;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 282:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 283;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 283:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 284;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 284:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 266:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 285;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 285:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 286;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 286:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 287;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 287:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 288;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 288:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 284;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 265:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 289;
                    }
                    case 47:
                    {
                        return 290;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 290:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 289;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 289:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 289;
                    }
                    case 47:
                    {
                        return 291;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 291:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 274;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 289;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 262:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 258:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 292;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 292:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(5, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 59:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 22:
                    {
                        return 258;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 37:
                    {
                        return 293;
                    }
                    case 47:
                    {
                        return 294;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 294:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 22:
                    {
                        return 258;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 47:
                    {
                        return 260;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 293:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 22:
                    {
                        return 258;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 47:
                    {
                        return 294;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 57:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 74;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 47:
                    {
                        return 295;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 295:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 74;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 47:
                    {
                        return 296;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 296:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 74;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 56:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 297;
                    }
                    case 3:
                    {
                        return 298;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 298:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 2:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 300:
            {
                switch (cls)
                {
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 301;
                    }
                    case 2:
                    {
                        return 302;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 302:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 305;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 305:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 306;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 306:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 307;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 307:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 308;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 308:
            {
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 309;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 309:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 304:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 2:
                    {
                        return 310;
                    }
                    case 3:
                    {
                        return 311;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 311:
            {
                switch (cls)
                {
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 301;
                    }
                    case 2:
                    {
                        return 302;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 310:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 312;
                    }
                    case 1:
                    {
                        return 313;
                    }
                    case 2:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 315:
            {
                switch (cls)
                {
                    case 3:
                    {
                        return 315;
                    }
                    case 0:
                    {
                        return 316;
                    }
                    case 1:
                    {
                        return 317;
                    }
                    case 2:
                    {
                        return 318;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 319;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 319:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 312;
                    }
                    case 1:
                    {
                        return 313;
                    }
                    case 2:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 318:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    case 0:
                    {
                        return 320;
                    }
                    case 1:
                    {
                        return 321;
                    }
                    case 2:
                    {
                        return 322;
                    }
                    case 44:
                    case 45:
                    {
                        return 323;
                    }
                    case 47:
                    {
                        return 324;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 324:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    case 0:
                    {
                        return 320;
                    }
                    case 1:
                    {
                        return 321;
                    }
                    case 2:
                    {
                        return 322;
                    }
                    case 44:
                    case 45:
                    {
                        return 323;
                    }
                    case 47:
                    {
                        return 325;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 325:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    case 0:
                    {
                        return 320;
                    }
                    case 1:
                    {
                        return 321;
                    }
                    case 2:
                    {
                        return 322;
                    }
                    case 44:
                    case 45:
                    {
                        return 323;
                    }
                    case 47:
                    {
                        return 326;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 326:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    case 0:
                    {
                        return 320;
                    }
                    case 1:
                    {
                        return 321;
                    }
                    case 2:
                    {
                        return 322;
                    }
                    case 44:
                    case 45:
                    {
                        return 323;
                    }
                    case 47:
                    {
                        return 327;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 327:
            {
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    case 0:
                    {
                        return 320;
                    }
                    case 1:
                    {
                        return 321;
                    }
                    case 2:
                    {
                        return 322;
                    }
                    case 44:
                    case 45:
                    {
                        return 323;
                    }
                    case 47:
                    {
                        return 328;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 328:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 312;
                    }
                    case 1:
                    {
                        return 313;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    case 2:
                    {
                        return 322;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 323:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    case 0:
                    {
                        return 320;
                    }
                    case 1:
                    {
                        return 321;
                    }
                    case 2:
                    {
                        return 322;
                    }
                    case 44:
                    case 45:
                    {
                        return 323;
                    }
                    case 47:
                    {
                        return 325;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 322:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 310;
                    }
                    case 0:
                    {
                        return 312;
                    }
                    case 1:
                    {
                        return 313;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 329;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 329:
            {
                switch (cls)
                {
                    case 3:
                    {
                        return 315;
                    }
                    case 0:
                    {
                        return 316;
                    }
                    case 1:
                    {
                        return 317;
                    }
                    case 2:
                    {
                        return 318;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 319;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 321:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 0:
                    {
                        return 330;
                    }
                    case 47:
                    {
                        return 331;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 331:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 305;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 330:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 332;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 332:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 331;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 320:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 332;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 317:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 0:
                    {
                        return 330;
                    }
                    case 47:
                    {
                        return 331;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 316:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 332;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 314:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 312;
                    }
                    case 1:
                    {
                        return 313;
                    }
                    case 2:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 314;
                    }
                    case 3:
                    {
                        return 315;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 313:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 0:
                    {
                        return 330;
                    }
                    case 47:
                    {
                        return 331;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 312:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 332;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 303:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 303;
                    }
                    case 2:
                    {
                        return 304;
                    }
                    case 47:
                    {
                        return 306;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 301:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 2:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 299:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 2:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 299;
                    }
                    case 3:
                    {
                        return 300;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 297:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 333;
                    }
                    case 1:
                    {
                        return 334;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 335;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 335:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 333;
                    }
                    case 1:
                    {
                        return 334;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 335;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 334:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 0:
                    {
                        return 336;
                    }
                    case 47:
                    {
                        return 337;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 337:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 338;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 338:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 339;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 339:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 340;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 340:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 341;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 341:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 342;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 342:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 56;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 336:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 343;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 343:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 337;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 333:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 343;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 19:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 344;
                    }
                    case 1:
                    {
                        return 345;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 346;
                    }
                    case 47:
                    {
                        return 347;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 347:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 344;
                    }
                    case 1:
                    {
                        return 345;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 346;
                    }
                    case 47:
                    {
                        return 348;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 348:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 344;
                    }
                    case 1:
                    {
                        return 345;
                    }
                    case 47:
                    {
                        return 349;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 349:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 344;
                    }
                    case 1:
                    {
                        return 350;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 350:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 351;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 351:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 352;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 352:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 353;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 353:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 346:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 344;
                    }
                    case 1:
                    {
                        return 345;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 346;
                    }
                    case 47:
                    {
                        return 347;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 345:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 351;
                    }
                    case 47:
                    {
                        return 353;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 344:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 352;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 1;
                    }
                    case 44:
                    case 45:
                    {
                        return 18;
                    }
                    case 46:
                    {
                        return 19;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 354;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 354:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 1;
                    }
                    case 44:
                    case 45:
                    {
                        return 18;
                    }
                    case 46:
                    {
                        return 19;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 340;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 37:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 32:
                    {
                        return 101;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 38:
                    {
                        return 103;
                    }
                    case 9:
                    {
                        return 202;
                    }
                    case 10:
                    {
                        return 203;
                    }
                    case 11:
                    case 12:
                    {
                        return 355;
                    }
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 25:
                    {
                        return 359;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 360;
                    }
                    case 47:
                    {
                        return 361;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 361:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 37:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 355;
                    }
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 25:
                    {
                        return 359;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 360;
                    }
                    case 47:
                    {
                        return 362;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 362:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 37:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 355;
                    }
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 25:
                    {
                        return 359;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 360;
                    }
                    case 47:
                    {
                        return 363;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 363:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 47:
                    {
                        return 364;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 364:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 365;
                    }
                    case 21:
                    {
                        return 366;
                    }
                    case 47:
                    {
                        return 367;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 367:
            {
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 365;
                    }
                    case 21:
                    {
                        return 366;
                    }
                    case 47:
                    {
                        return 368;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 368:
            {
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 369;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 369:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 370;
                    }
                    case 21:
                    {
                        return 371;
                    }
                    case 47:
                    {
                        return 372;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 372:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 373;
                    }
                    case 21:
                    {
                        return 374;
                    }
                    case 47:
                    {
                        return 375;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 375:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 376;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 376:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 377;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 377:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 378;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 378:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 379;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 379:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 140;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 374:
            {
                switch (cls)
                {
                    case 21:
                    {
                        return 380;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 380:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 381;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 381:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 375;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 373:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 382;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 382:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 381;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 371:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 375;
                    }
                    case 21:
                    {
                        return 380;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 370:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 375;
                    }
                    case 20:
                    {
                        return 382;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 366:
            {
                switch (cls)
                {
                    case 21:
                    {
                        return 383;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 383:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 384;
                    }
                    case 47:
                    {
                        return 385;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 385:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 384;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 384:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 377;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 365:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 386;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 386:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 384;
                    }
                    case 47:
                    {
                        return 385;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 360:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 37:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 355;
                    }
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 25:
                    {
                        return 359;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 360;
                    }
                    case 47:
                    {
                        return 387;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 387:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 37:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 355;
                    }
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 25:
                    {
                        return 359;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 360;
                    }
                    case 47:
                    {
                        return 388;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 388:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 37:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 355;
                    }
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 25:
                    {
                        return 359;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 360;
                    }
                    case 47:
                    {
                        return 389;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 389:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 37:
                    {
                        return 62;
                    }
                    case 11:
                    case 12:
                    {
                        return 355;
                    }
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 25:
                    {
                        return 359;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 360;
                    }
                    case 47:
                    {
                        return 390;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 390:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 47:
                    {
                        return 364;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 359:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 37:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 355;
                    }
                    case 13:
                    case 14:
                    {
                        return 356;
                    }
                    case 20:
                    {
                        return 357;
                    }
                    case 21:
                    {
                        return 358;
                    }
                    case 25:
                    {
                        return 359;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 360;
                    }
                    case 47:
                    {
                        return 387;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 358:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 21:
                    {
                        return 383;
                    }
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 391;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 391:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 378;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 357:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 386;
                    }
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 391;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 356:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 370;
                    }
                    case 21:
                    {
                        return 371;
                    }
                    case 47:
                    {
                        return 372;
                    }
                    case 11:
                    case 12:
                    {
                        return 392;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 392:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 376;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 355:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 393;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 393:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 379;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 16:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 394;
                    }
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 25:
                    {
                        return 398;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 399;
                    }
                    case 47:
                    {
                        return 400;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 400:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 394;
                    }
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 25:
                    {
                        return 398;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 399;
                    }
                    case 47:
                    {
                        return 401;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 401:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 394;
                    }
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 25:
                    {
                        return 398;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 399;
                    }
                    case 47:
                    {
                        return 402;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 402:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 47:
                    {
                        return 403;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 403:
            {
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 404;
                    }
                    case 21:
                    {
                        return 405;
                    }
                    case 47:
                    {
                        return 406;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 406:
            {
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 404;
                    }
                    case 21:
                    {
                        return 405;
                    }
                    case 47:
                    {
                        return 407;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 407:
            {
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 408;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 408:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 409;
                    }
                    case 21:
                    {
                        return 410;
                    }
                    case 47:
                    {
                        return 411;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 411:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 412;
                    }
                    case 21:
                    {
                        return 413;
                    }
                    case 47:
                    {
                        return 414;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 414:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 415;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 415:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 416;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 416:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 417;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 417:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 418;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 418:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 141;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 413:
            {
                switch (cls)
                {
                    case 21:
                    {
                        return 419;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 419:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 420;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 420:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 414;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 412:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 421;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 421:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 420;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 410:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 414;
                    }
                    case 21:
                    {
                        return 419;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 409:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 414;
                    }
                    case 20:
                    {
                        return 421;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 405:
            {
                switch (cls)
                {
                    case 21:
                    {
                        return 422;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 422:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 423;
                    }
                    case 47:
                    {
                        return 424;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 424:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 423;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 423:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 416;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 404:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 425;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 425:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 423;
                    }
                    case 47:
                    {
                        return 424;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 399:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 394;
                    }
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 25:
                    {
                        return 398;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 399;
                    }
                    case 47:
                    {
                        return 426;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 426:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 394;
                    }
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 25:
                    {
                        return 398;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 399;
                    }
                    case 47:
                    {
                        return 427;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 427:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 394;
                    }
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 25:
                    {
                        return 398;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 399;
                    }
                    case 47:
                    {
                        return 428;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 428:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 11:
                    case 12:
                    {
                        return 394;
                    }
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 25:
                    {
                        return 398;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 399;
                    }
                    case 47:
                    {
                        return 429;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 429:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 47:
                    {
                        return 403;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 398:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 11:
                    case 12:
                    {
                        return 394;
                    }
                    case 13:
                    case 14:
                    {
                        return 395;
                    }
                    case 20:
                    {
                        return 396;
                    }
                    case 21:
                    {
                        return 397;
                    }
                    case 25:
                    {
                        return 398;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 399;
                    }
                    case 47:
                    {
                        return 426;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 397:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 21:
                    {
                        return 422;
                    }
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 430;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 430:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 417;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 396:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 425;
                    }
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 430;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 395:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 409;
                    }
                    case 21:
                    {
                        return 410;
                    }
                    case 47:
                    {
                        return 411;
                    }
                    case 11:
                    case 12:
                    {
                        return 431;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 431:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 415;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 394:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 13:
                    case 14:
                    case 47:
                    {
                        return 432;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 432:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 47:
                    {
                        return 418;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(21, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                switch (cls)
                {
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
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 15:
                    {
                        return 433;
                    }
                    case 25:
                    {
                        return 434;
                    }
                    case 33:
                    case 34:
                    {
                        return 435;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 436;
                    }
                    case 47:
                    {
                        return 437;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 437:
            {
                switch (cls)
                {
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
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 15:
                    {
                        return 433;
                    }
                    case 25:
                    {
                        return 434;
                    }
                    case 33:
                    case 34:
                    {
                        return 435;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 436;
                    }
                    case 47:
                    {
                        return 438;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 438:
            {
                switch (cls)
                {
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
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 15:
                    {
                        return 433;
                    }
                    case 25:
                    {
                        return 434;
                    }
                    case 33:
                    case 34:
                    {
                        return 435;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 436;
                    }
                    case 47:
                    {
                        return 439;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 439:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 434;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 436;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 436:
            {
                switch (cls)
                {
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
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 15:
                    {
                        return 433;
                    }
                    case 25:
                    {
                        return 434;
                    }
                    case 33:
                    case 34:
                    {
                        return 435;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 436;
                    }
                    case 47:
                    {
                        return 437;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 435:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 16:
                    {
                        return 440;
                    }
                    case 17:
                    {
                        return 441;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 47:
                    {
                        return 444;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 444:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 16:
                    {
                        return 440;
                    }
                    case 17:
                    {
                        return 441;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 47:
                    {
                        return 445;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 445:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 47:
                    {
                        return 446;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 446:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 443:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 47:
                    {
                        return 449;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 449:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 47:
                    {
                        return 450;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 450:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 47:
                    {
                        return 451;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 451:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 47:
                    {
                        return 452;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 452:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 37:
                    case 38:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 47:
                    {
                        return 453;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 453:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 448:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 454;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 454:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 453;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 447:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 47:
                    {
                        return 454;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 442:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 154;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 155;
                    }
                    case 47:
                    {
                        return 159;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 441:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 47:
                    {
                        return 455;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 455:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 47:
                    {
                        return 445;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 440:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 442;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 443;
                    }
                    case 47:
                    {
                        return 455;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 434:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(4, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 61;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 62;
                    }
                    case 15:
                    {
                        return 70;
                    }
                    case 33:
                    case 34:
                    {
                        return 102;
                    }
                    case 47:
                    {
                        return 104;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 433:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 456;
                    }
                    case 33:
                    case 34:
                    {
                        return 457;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 458;
                    }
                    case 47:
                    {
                        return 459;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 459:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 456;
                    }
                    case 33:
                    case 34:
                    {
                        return 457;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 458;
                    }
                    case 47:
                    {
                        return 460;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 460:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 456;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 458;
                    }
                    case 47:
                    {
                        return 461;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 461:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 37:
                    case 38:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 47:
                    {
                        return 452;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 458:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 456;
                    }
                    case 33:
                    case 34:
                    {
                        return 457;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 458;
                    }
                    case 47:
                    {
                        return 462;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 462:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 456;
                    }
                    case 33:
                    case 34:
                    {
                        return 457;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 458;
                    }
                    case 47:
                    {
                        return 463;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 463:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 456;
                    }
                    case 33:
                    case 34:
                    {
                        return 457;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 458;
                    }
                    case 47:
                    {
                        return 464;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 464:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 456;
                    }
                    case 33:
                    case 34:
                    {
                        return 457;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 458;
                    }
                    case 47:
                    {
                        return 465;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 465:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 37:
                    case 38:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 264;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 47:
                    {
                        return 461;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 457:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 16:
                    {
                        return 466;
                    }
                    case 17:
                    {
                        return 467;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    case 47:
                    {
                        return 470;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 470:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 16:
                    {
                        return 466;
                    }
                    case 17:
                    {
                        return 467;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    case 47:
                    {
                        return 471;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 471:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    case 47:
                    {
                        return 472;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 472:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 469:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    case 47:
                    {
                        return 473;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 473:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    case 47:
                    {
                        return 474;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 474:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    case 47:
                    {
                        return 475;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 475:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    case 19:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 38:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 20:
                    case 21:
                    {
                        return 447;
                    }
                    case 36:
                    case 39:
                    {
                        return 448;
                    }
                    case 47:
                    {
                        return 452;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 468:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 25:
                    {
                        return 90;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 91;
                    }
                    case 47:
                    {
                        return 95;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 467:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    case 47:
                    {
                        return 476;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 476:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    case 47:
                    {
                        return 471;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 466:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 262;
                    }
                    case 23:
                    {
                        return 263;
                    }
                    case 25:
                    {
                        return 468;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 469;
                    }
                    case 47:
                    {
                        return 476;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 456:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 73;
                    }
                    case 25:
                    {
                        return 74;
                    }
                    case 33:
                    case 34:
                    {
                        return 75;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 36:
                    case 39:
                    {
                        return 77;
                    }
                    case 47:
                    {
                        return 84;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 13:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 479:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 478:
            {
                switch (cls)
                {
                    case 9:
                    {
                        return 480;
                    }
                    case 13:
                    {
                        return 481;
                    }
                    case 14:
                    {
                        return 482;
                    }
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 483;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 484;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 484:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 485;
                    }
                    case 47:
                    {
                        return 486;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 486:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 47:
                    {
                        return 487;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 487:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 47:
                    {
                        return 488;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 488:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 47:
                    {
                        return 489;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 489:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 485:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 47:
                    {
                        return 486;
                    }
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 490;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 490:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 47:
                    {
                        return 487;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 483:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 47:
                    {
                        return 488;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 482:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 491;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 491:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 492;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 492:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 493;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 493:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 494;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 494:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 495;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 495:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 496;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 496:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 497;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 497:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 498;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 498:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 47:
                    {
                        return 499;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 499:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 481:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 500;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 500:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 501;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 501:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 502;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 502:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 503;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 503:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 47:
                    {
                        return 499;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 480:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 504;
                    }
                    case 47:
                    {
                        return 505;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 505:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 504;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 504:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 504;
                    }
                    case 47:
                    {
                        return 506;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 506:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 44:
                    case 45:
                    case 46:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    case 47:
                    {
                        return 489;
                    }
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 504;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 477:
            {
                switch (cls)
                {
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
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
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
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 477;
                    }
                    case 23:
                    {
                        return 478;
                    }
                    case 24:
                    {
                        return 479;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 12:
            {
                switch (cls)
                {
                    case 13:
                    {
                        return 507;
                    }
                    case 14:
                    {
                        return 508;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 508:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 509;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 509:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 510;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 510:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 511;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 511:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 512;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 512:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 513;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 513:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 514;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 514:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 515;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 515:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 516;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 516:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 519;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 519:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 520;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 520:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 521;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 521:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 522;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 522:
            {
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 523;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 523:
            {
                switch (cls)
                {
                    case 23:
                    {
                        return 518;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 518:
            {
                switch (cls)
                {
                    case 13:
                    {
                        return 524;
                    }
                    case 14:
                    {
                        return 525;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 525:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 526;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 526:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 527;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 527:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 528;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 528:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 529;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 529:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 530;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 530:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 531;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 531:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 532;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 532:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 533;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 533:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 534;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 534:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 535;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 535:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 521;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 524:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 536;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 536:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 537;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 537:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 538;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 538:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 539;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 539:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 534;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 517:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 535;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 507:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 540;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 540:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 541;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 541:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 542;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 542:
            {
                switch (cls)
                {
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 543;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 543:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 519;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 11:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 292;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 520;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 10:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    case 47:
                    {
                        return 545;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 545:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 521;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 544:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 292;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 535;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 9:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(38, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 17:
                    {
                        return 546;
                    }
                    case 50:
                    {
                        return 547;
                    }
                    case 52:
                    {
                        return 548;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 548:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(53, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    {
                        return 549;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 549:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(43, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 547:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(15, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 546:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(47, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(37, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 16:
                    {
                        return 550;
                    }
                    case 50:
                    {
                        return 551;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 551:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(14, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 550:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(46, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(52, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 74;
                    }
                    case 35:
                    case 37:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 76;
                    }
                    case 47:
                    {
                        return 295;
                    }
                    case 3:
                    {
                        return 552;
                    }
                    case 15:
                    {
                        return 553;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 553:
            {
                switch (cls)
                {
                    case 15:
                    {
                        return 554;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 554:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(55, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 552:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(42, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    case 47:
                    {
                        return 555;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 555:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    case 47:
                    {
                        return 556;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 556:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 522;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 5:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    case 37:
                    {
                        return 557;
                    }
                    case 47:
                    {
                        return 558;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 558:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    case 47:
                    {
                        return 559;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 559:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    case 47:
                    {
                        return 560;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 560:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 523;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 557:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    case 47:
                    {
                        return 561;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 561:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 259;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 22:
                    {
                        return 544;
                    }
                    case 47:
                    {
                        return 559;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 4:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    {
                        return 517;
                    }
                    case 23:
                    {
                        return 518;
                    }
                    case 47:
                    {
                        return 520;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(39, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 562;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 562:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(11, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(40, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 297;
                    }
                    case 3:
                    {
                        return 298;
                    }
                    case 50:
                    {
                        return 563;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 563:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(12, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 44:
                    case 45:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 56;
                    }
                    case 47:
                    {
                        return 339;
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

    static int64_t GetTokenId(int32_t ruleIndex, soul::lexer::LexerBase<Char>& lexer)
    {
        switch (ruleIndex)
        {
            case 0:
            {
                lexer.Retract();
                break;
            }
            case 1:
            {
                lexer.Retract();
                int64_t kw = lexer.GetKeywordToken(lexer.CurrentToken().match);
                if (kw == INVALID_TOKEN) return ID;
                else return kw;
                break;
            }
            case 2:
            {
                lexer.Retract();
                return INTEGER_LITERAL;
                break;
            }
            case 3:
            {
                lexer.Retract();
                return FLOATING_LITERAL;
                break;
            }
            case 4:
            {
                lexer.Retract();
                return CHARACTER_LITERAL;
                break;
            }
            case 5:
            {
                lexer.Retract();
                return BEGIN_RAW_STRING_LITERAL;
                break;
            }
            case 6:
            {
                lexer.Retract();
                return STRING_LITERAL;
                break;
            }
            case 7:
            {
                lexer.Retract();
                if (lexer.Skipping()) return PP_LINE;
                else lexer.PreprocessCurrentToken();
                break;
            }
            case 8:
            {
                lexer.Retract();
                return COLON_COLON;
                break;
            }
            case 9:
            {
                lexer.Retract();
                return COMMA;
                break;
            }
            case 10:
            {
                lexer.Retract();
                return ASSIGN;
                break;
            }
            case 11:
            {
                lexer.Retract();
                return MUL_ASSIGN;
                break;
            }
            case 12:
            {
                lexer.Retract();
                return DIV_ASSIGN;
                break;
            }
            case 13:
            {
                lexer.Retract();
                return REM_ASSIGN;
                break;
            }
            case 14:
            {
                lexer.Retract();
                return ADD_ASSIGN;
                break;
            }
            case 15:
            {
                lexer.Retract();
                return SUB_ASSIGN;
                break;
            }
            case 16:
            {
                lexer.Retract();
                return SHIFT_RIGHT_ASSIGN;
                break;
            }
            case 17:
            {
                lexer.Retract();
                return SHIFT_LEFT_ASSIGN;
                break;
            }
            case 18:
            {
                lexer.Retract();
                return AND_ASSIGN;
                break;
            }
            case 19:
            {
                lexer.Retract();
                return XOR_ASSIGN;
                break;
            }
            case 20:
            {
                lexer.Retract();
                return OR_ASSIGN;
                break;
            }
            case 21:
            {
                lexer.Retract();
                return QUEST;
                break;
            }
            case 22:
            {
                lexer.Retract();
                return COLON;
                break;
            }
            case 23:
            {
                lexer.Retract();
                return OR_OR;
                break;
            }
            case 24:
            {
                lexer.Retract();
                return AMP_AMP;
                break;
            }
            case 25:
            {
                lexer.Retract();
                return OR;
                break;
            }
            case 26:
            {
                lexer.Retract();
                return XOR;
                break;
            }
            case 27:
            {
                lexer.Retract();
                return AMP;
                break;
            }
            case 28:
            {
                lexer.Retract();
                return EQ;
                break;
            }
            case 29:
            {
                lexer.Retract();
                return NEQ;
                break;
            }
            case 30:
            {
                lexer.Retract();
                return LEQ;
                break;
            }
            case 31:
            {
                lexer.Retract();
                return GEQ;
                break;
            }
            case 32:
            {
                lexer.Retract();
                return SPACE_SHIP;
                break;
            }
            case 33:
            {
                lexer.Retract();
                return LANGLE;
                break;
            }
            case 34:
            {
                lexer.Retract();
                return RANGLE;
                break;
            }
            case 35:
            {
                lexer.Retract();
                return SHIFT_LEFT;
                break;
            }
            case 36:
            {
                auto vars = static_cast<Variables*>(lexer.GetVariables());
                if (vars->langleCount > 0) return INVALID_TOKEN;
                lexer.Retract();
                return SHIFT_RIGHT;
                break;
            }
            case 37:
            {
                lexer.Retract();
                return PLUS;
                break;
            }
            case 38:
            {
                lexer.Retract();
                return MINUS;
                break;
            }
            case 39:
            {
                lexer.Retract();
                return STAR;
                break;
            }
            case 40:
            {
                lexer.Retract();
                return DIV;
                break;
            }
            case 41:
            {
                lexer.Retract();
                return MOD;
                break;
            }
            case 42:
            {
                lexer.Retract();
                return DOT_STAR;
                break;
            }
            case 43:
            {
                lexer.Retract();
                return ARROW_STAR;
                break;
            }
            case 44:
            {
                lexer.Retract();
                return LPAREN;
                break;
            }
            case 45:
            {
                lexer.Retract();
                return RPAREN;
                break;
            }
            case 46:
            {
                lexer.Retract();
                return PLUS_PLUS;
                break;
            }
            case 47:
            {
                lexer.Retract();
                return MINUS_MINUS;
                break;
            }
            case 48:
            {
                lexer.Retract();
                return EXCLAMATION;
                break;
            }
            case 49:
            {
                lexer.Retract();
                return TILDE;
                break;
            }
            case 50:
            {
                lexer.Retract();
                return LBRACKET;
                break;
            }
            case 51:
            {
                lexer.Retract();
                return RBRACKET;
                break;
            }
            case 52:
            {
                lexer.Retract();
                return DOT;
                break;
            }
            case 53:
            {
                lexer.Retract();
                return ARROW;
                break;
            }
            case 54:
            {
                lexer.Retract();
                return SEMICOLON;
                break;
            }
            case 55:
            {
                lexer.Retract();
                return ELLIPSIS;
                break;
            }
            case 56:
            {
                lexer.Retract();
                return LBRACE;
                break;
            }
            case 57:
            {
                lexer.Retract();
                return RBRACE;
                break;
            }
        }
        return CONTINUE_TOKEN;
    }
};

template<typename Char>
ClassMap<Char>* GetClassMap()
{
    static ClassMap<Char>* classmap = MakeClassMap<Char>("otava.lexer.classmap");
    return classmap;
}

template<typename Char>
soul::lexer::KeywordMap<Char>* GetKeywords();

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>();

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>();

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>();

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>();

template<typename Char>
soul::lexer::Lexer<OtavaLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul::lexer::Lexer<OtavaLexer<Char>, Char>(start, end, fileName);
    lexer.SetClassMap(GetClassMap<Char>());
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<Char>());
    return lexer;
}

} // namespace otava::lexer
