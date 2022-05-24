// this file has been automatically generated from 'C:/work/soul-mod/soul/lex/re_lexer.lexer' using soul lexer generator slg version 4.0.0

export module soul.lex.re;

import std.core;
import soul.lexer;
import soul.ast.slg;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.punctuation.token;
import soul.tool.token;

using namespace soul;
using namespace soul::lexer;
using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::punctuation::token;
using namespace soul::tool::token;

export namespace soul::lex::re {

std::mutex& MakeLexerMtx();

template<typename Char>
struct RegExLexer;

template<typename Char>
soul::lexer::Lexer<RegExLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName);

soul::ast::slg::TokenCollection* GetTokens();

struct RegExLexer_Variables : public soul::lexer::Variables
{
    RegExLexer_Variables();
};

template<typename Char>
struct RegExLexer
{
    static int32_t NextState(int32_t state, Char chr, soul::lexer::LexerBase<Char>& lxr)
    {
        ClassMap<Char>* classmap = lxr.GetClassMap();
        int32_t cls = classmap->GetClass(chr);
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
                    {
                        return 15;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(14, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 20:
                    case 23:
                    case 32:
                    case 34:
                    case 35:
                    {
                        return 17;
                    }
                    case 16:
                    {
                        return 18;
                    }
                    case 17:
                    {
                        return 19;
                    }
                    case 18:
                    {
                        return 20;
                    }
                    case 19:
                    {
                        return 21;
                    }
                    case 21:
                    {
                        return 22;
                    }
                    case 22:
                    {
                        return 23;
                    }
                    case 24:
                    {
                        return 24;
                    }
                    case 25:
                    {
                        return 25;
                    }
                    case 26:
                    {
                        return 26;
                    }
                    case 27:
                    {
                        return 27;
                    }
                    case 28:
                    {
                        return 28;
                    }
                    case 29:
                    {
                        return 29;
                    }
                    case 30:
                    {
                        return 30;
                    }
                    case 31:
                    {
                        return 31;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 20:
                    case 23:
                    case 32:
                    case 34:
                    case 35:
                    {
                        return 17;
                    }
                    case 16:
                    {
                        return 18;
                    }
                    case 17:
                    {
                        return 19;
                    }
                    case 18:
                    {
                        return 20;
                    }
                    case 19:
                    {
                        return 21;
                    }
                    case 21:
                    {
                        return 22;
                    }
                    case 22:
                    {
                        return 23;
                    }
                    case 24:
                    {
                        return 24;
                    }
                    case 25:
                    {
                        return 25;
                    }
                    case 26:
                    {
                        return 26;
                    }
                    case 27:
                    {
                        return 27;
                    }
                    case 28:
                    {
                        return 28;
                    }
                    case 29:
                    {
                        return 29;
                    }
                    case 30:
                    {
                        return 30;
                    }
                    case 31:
                    {
                        return 31;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 20:
                    case 23:
                    case 32:
                    case 34:
                    case 35:
                    {
                        return 17;
                    }
                    case 16:
                    {
                        return 18;
                    }
                    case 17:
                    {
                        return 19;
                    }
                    case 18:
                    {
                        return 20;
                    }
                    case 19:
                    {
                        return 21;
                    }
                    case 21:
                    {
                        return 22;
                    }
                    case 22:
                    {
                        return 23;
                    }
                    case 24:
                    {
                        return 24;
                    }
                    case 25:
                    {
                        return 25;
                    }
                    case 26:
                    {
                        return 26;
                    }
                    case 27:
                    {
                        return 27;
                    }
                    case 28:
                    {
                        return 28;
                    }
                    case 29:
                    {
                        return 29;
                    }
                    case 30:
                    {
                        return 30;
                    }
                    case 31:
                    {
                        return 31;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 35;
                    }
                    case 17:
                    {
                        return 36;
                    }
                    case 18:
                    {
                        return 37;
                    }
                    case 21:
                    {
                        return 38;
                    }
                    case 22:
                    {
                        return 39;
                    }
                    case 24:
                    {
                        return 40;
                    }
                    case 25:
                    {
                        return 41;
                    }
                    case 26:
                    {
                        return 42;
                    }
                    case 27:
                    {
                        return 43;
                    }
                    case 28:
                    {
                        return 44;
                    }
                    case 29:
                    {
                        return 45;
                    }
                    case 30:
                    {
                        return 46;
                    }
                    case 31:
                    {
                        return 47;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 35;
                    }
                    case 17:
                    {
                        return 36;
                    }
                    case 21:
                    {
                        return 38;
                    }
                    case 22:
                    {
                        return 39;
                    }
                    case 24:
                    {
                        return 40;
                    }
                    case 25:
                    {
                        return 41;
                    }
                    case 26:
                    {
                        return 42;
                    }
                    case 27:
                    {
                        return 43;
                    }
                    case 28:
                    {
                        return 44;
                    }
                    case 29:
                    {
                        return 45;
                    }
                    case 30:
                    {
                        return 46;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 35;
                    }
                    case 17:
                    {
                        return 36;
                    }
                    case 21:
                    {
                        return 38;
                    }
                    case 22:
                    {
                        return 39;
                    }
                    case 24:
                    {
                        return 40;
                    }
                    case 25:
                    {
                        return 41;
                    }
                    case 26:
                    {
                        return 42;
                    }
                    case 27:
                    {
                        return 43;
                    }
                    case 28:
                    {
                        return 44;
                    }
                    case 29:
                    {
                        return 45;
                    }
                    case 33:
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
                    case 16:
                    {
                        return 35;
                    }
                    case 17:
                    {
                        return 36;
                    }
                    case 21:
                    {
                        return 38;
                    }
                    case 22:
                    {
                        return 39;
                    }
                    case 25:
                    {
                        return 41;
                    }
                    case 26:
                    {
                        return 42;
                    }
                    case 27:
                    {
                        return 43;
                    }
                    case 28:
                    {
                        return 44;
                    }
                    case 33:
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
                    case 25:
                    {
                        return 41;
                    }
                    case 26:
                    {
                        return 42;
                    }
                    case 27:
                    {
                        return 43;
                    }
                    case 33:
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
                    case 25:
                    {
                        return 41;
                    }
                    case 26:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
            case 46:
            {
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 40;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 40;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                    case 23:
                    case 24:
                    {
                        return 65;
                    }
                    case 33:
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
                    case 23:
                    case 24:
                    {
                        return 65;
                    }
                    case 33:
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
                    case 23:
                    case 24:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 23:
                    case 24:
                    {
                        return 65;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 23:
                    case 24:
                    {
                        return 65;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                    case 23:
                    case 24:
                    {
                        return 65;
                    }
                    case 33:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 74;
                    }
                    case 33:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 74;
                    }
                    case 33:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 74;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
                    {
                        return 69;
                    }
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 74;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 40;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 40;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 23:
                    case 24:
                    {
                        return 65;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 23:
                    case 24:
                    {
                        return 65;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 23:
                    case 24:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 23:
                    case 24:
                    {
                        return 65;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
                    {
                        return 54;
                    }
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
                    {
                        return 54;
                    }
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 74;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 74;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 74;
                    }
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 33:
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(12, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
            case 12:
            {
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(11, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
            case 11:
            {
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(10, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
            case 10:
            {
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(9, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
            case 9:
            {
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(5, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
            case 5:
            {
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(4, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
            case 4:
            {
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
            case 3:
            {
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
                auto& token = lxr.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lxr.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lxr);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
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
        }
        return -1;
    }

    static int64_t GetTokenId(int32_t ruleIndex, soul::lexer::LexerBase<Char>& lxr)
    {
        switch (ruleIndex)
        {
            case 0:
            {
                lxr.Retract();
                return LPAREN;
                break;
            }
            case 1:
            {
                lxr.Retract();
                return RPAREN;
                break;
            }
            case 2:
            {
                lxr.Retract();
                return LBRACKET;
                break;
            }
            case 3:
            {
                lxr.Retract();
                return RBRACKET;
                break;
            }
            case 4:
            {
                lxr.Retract();
                return LBRACE;
                break;
            }
            case 5:
            {
                lxr.Retract();
                return RBRACE;
                break;
            }
            case 6:
            {
                lxr.Retract();
                return PIPE;
                break;
            }
            case 7:
            {
                lxr.Retract();
                return STAR;
                break;
            }
            case 8:
            {
                lxr.Retract();
                return PLUS;
                break;
            }
            case 9:
            {
                lxr.Retract();
                return QUEST;
                break;
            }
            case 10:
            {
                lxr.Retract();
                return DOT;
                break;
            }
            case 11:
            {
                lxr.Retract();
                return CARET;
                break;
            }
            case 12:
            {
                lxr.Retract();
                return MINUS;
                break;
            }
            case 13:
            {
                lxr.Retract();
                return ESCAPE;
                break;
            }
            case 14:
            {
                lxr.Retract();
                return CHARACTER;
                break;
            }
        }
        return CONTINUE_TOKEN;
    }
};

template<typename Char>
ClassMap<Char>* GetClassMap()
{
    static ClassMap<Char>* classmap = MakeClassMap<Char>("soul.lex.re.classmap");
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
soul::lexer::Lexer<RegExLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul::lexer::Lexer<RegExLexer<Char>, Char>(start, end, fileName);
    lexer.SetClassMap(GetClassMap<Char>());
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<Char>());
    return lexer;
}

} // namespace soul::lex::re
