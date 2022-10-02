// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/command/command.lexer' using soul lexer generator slg version 4.1.0

export module otava.command.lexer;

import std.core;
import soul.lexer;
import soul.ast.slg;
import otava.command.token;

using namespace soul;
using namespace soul::lexer;
using namespace otava::command::token;

export namespace otava::command::lexer {

std::mutex& MakeLexerMtx();

template<typename Char>
struct CommandLexer;

template<typename Char>
soul::lexer::Lexer<CommandLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName);

soul::ast::slg::TokenCollection* GetTokens();

struct CommandLexer_Variables : public soul::lexer::Variables
{
    CommandLexer_Variables();
};

template<typename Char>
struct CommandLexer
{
    using Variables = CommandLexer_Variables;

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
                    case 1:
                    case 3:
                    {
                        return 1;
                    }
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 2;
                    }
                    case 9:
                    {
                        return 3;
                    }
                    case 10:
                    {
                        return 4;
                    }
                    case 11:
                    case 14:
                    case 15:
                    {
                        return 5;
                    }
                    case 12:
                    {
                        return 6;
                    }
                    case 13:
                    {
                        return 7;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 7:
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
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 5;
                    }
                    default:
                    {
                        return -1;
                    }
                }
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
                    case 10:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 5;
                    }
                    case 1:
                    case 2:
                    case 3:
                    {
                        return 8;
                    }
                    case 11:
                    case 12:
                    {
                        return 9;
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
                    case 10:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 5;
                    }
                    case 1:
                    case 2:
                    case 3:
                    {
                        return 8;
                    }
                    case 11:
                    case 12:
                    {
                        return 9;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 8:
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
                    case 1:
                    case 2:
                    case 3:
                    case 11:
                    case 12:
                    {
                        return 8;
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
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 5;
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
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 5;
                    }
                    case 0:
                    {
                        return 10;
                    }
                    case 10:
                    {
                        return 11;
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
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    {
                        return 12;
                    }
                    case 5:
                    {
                        return 13;
                    }
                    case 6:
                    {
                        return 14;
                    }
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
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
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    {
                        return 12;
                    }
                    case 5:
                    {
                        return 13;
                    }
                    case 6:
                    {
                        return 14;
                    }
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 15;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 14:
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
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 2;
                    }
                    case 5:
                    {
                        return 16;
                    }
                    case 10:
                    {
                        return 17;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 17:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 10;
                    }
                    case 10:
                    {
                        return 18;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 18:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 12;
                    }
                    case 5:
                    {
                        return 13;
                    }
                    case 6:
                    {
                        return 14;
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
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 2;
                    }
                    case 10:
                    {
                        return 17;
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
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 2;
                    }
                    case 10:
                    {
                        return 17;
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
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 12;
                    }
                    case 5:
                    {
                        return 13;
                    }
                    case 6:
                    {
                        return 14;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 10:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 19;
                    }
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
                    {
                        return 20;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 20:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 19;
                    }
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
                    {
                        return 20;
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
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 21;
                    }
                    case 10:
                    {
                        return 22;
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
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 23;
                    }
                    case 10:
                    {
                        return 24;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 24:
            {
                switch (cls)
                {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 0:
                    {
                        return 25;
                    }
                    case 10:
                    {
                        return 26;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 26:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 27;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 28;
                    }
                    case 5:
                    {
                        return 29;
                    }
                    case 6:
                    {
                        return 30;
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
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 23;
                    }
                    case 10:
                    {
                        return 24;
                    }
                    case 5:
                    {
                        return 31;
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
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 23;
                    }
                    case 10:
                    {
                        return 24;
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
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 23;
                    }
                    case 10:
                    {
                        return 24;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 28:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 27;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 28;
                    }
                    case 5:
                    {
                        return 29;
                    }
                    case 6:
                    {
                        return 30;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 27:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 27;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 32;
                    }
                    case 5:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 10:
                    {
                        return 35;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 35:
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
                    {
                        return 27;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 28;
                    }
                    case 5:
                    {
                        return 36;
                    }
                    case 6:
                    {
                        return 37;
                    }
                    case 7:
                    case 8:
                    {
                        return 38;
                    }
                    case 10:
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
                switch (cls)
                {
                    case 10:
                    {
                        return 26;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 28;
                    }
                    case 5:
                    {
                        return 29;
                    }
                    case 6:
                    {
                        return 30;
                    }
                    case 0:
                    {
                        return 40;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 40:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 27;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 32;
                    }
                    case 5:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 10:
                    {
                        return 35;
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
                    {
                        return 27;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 28;
                    }
                    case 5:
                    {
                        return 36;
                    }
                    case 6:
                    {
                        return 37;
                    }
                    case 7:
                    case 8:
                    {
                        return 38;
                    }
                    case 10:
                    {
                        return 39;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 37:
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
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 23;
                    }
                    case 10:
                    {
                        return 24;
                    }
                    case 5:
                    {
                        return 31;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 36:
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
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 23;
                    }
                    case 10:
                    {
                        return 24;
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
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 23;
                    }
                    case 10:
                    {
                        return 24;
                    }
                    case 5:
                    {
                        return 31;
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
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 23;
                    }
                    case 10:
                    {
                        return 24;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 32:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 27;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 28;
                    }
                    case 5:
                    {
                        return 29;
                    }
                    case 6:
                    {
                        return 30;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 25:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 21;
                    }
                    case 10:
                    {
                        return 22;
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
                    {
                        return 19;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 9:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    {
                        return 20;
                    }
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 23;
                    }
                    case 10:
                    {
                        return 24;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 21:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 19;
                    }
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
                    {
                        return 20;
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
            case 2:
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
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    {
                        return 2;
                    }
                    case 10:
                    {
                        return 17;
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
                    case 1:
                    case 2:
                    case 3:
                    case 11:
                    case 12:
                    {
                        return 8;
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
                return DOT;
                break;
            }
            case 3:
            {
                lexer.Retract();
                return SEMICOLON;
                break;
            }
            case 4:
            {
                lexer.Retract();
                return FILEPATH;
                break;
            }
        }
        return CONTINUE_TOKEN;
    }
};

template<typename Char>
ClassMap<Char>* GetClassMap()
{
    static ClassMap<Char>* classmap = MakeClassMap<Char>("otava.command.lexer.classmap");
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
soul::lexer::Lexer<CommandLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul::lexer::Lexer<CommandLexer<Char>, Char>(start, end, fileName);
    lexer.SetClassMap(GetClassMap<Char>());
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<Char>());
    return lexer;
}

} // namespace otava::command::lexer
