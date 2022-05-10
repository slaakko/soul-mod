// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer;

export import soul.lexer.concepts;
export import soul.lexer.lexeme;
export import soul.lexer.token;
export import soul.lexer.keyword;
export import soul.lexer.base;

import std.core;
import util.unicode;

using namespace util;

export namespace soul {

enum class LexerFlags : int32_t
{
    none = 0, synchronize = 1 << 0, synchronized = 1 << 1, synchronizedAtLeastOnce = 1 << 2, cursorSeen = 1 << 3, recordedParse = 1 << 4, farthestError = 1 << 5
};

constexpr LexerFlags operator|(LexerFlags left, LexerFlags right)
{
    return static_cast<LexerFlags>(static_cast<int32_t>(left) | static_cast<int32_t>(right));
}

constexpr LexerFlags operator&(LexerFlags left, LexerFlags right)
{
    return static_cast<LexerFlags>(static_cast<int32_t>(left) & static_cast<int32_t>(right));
}

constexpr LexerFlags operator~(LexerFlags flag)
{
    return static_cast<LexerFlags>(~static_cast<int32_t>(flag));
}

template<typename Stack>
    requires RuleStack<Stack>
struct RuleGuard
{
    RuleGuard(Stack& stack_, int ruleId) : stack(stack_)
    {
        stack.PushRule(ruleId);
    }
    ~RuleGuard()
    {
        stack.PopRule();
    }
    Stack& stack;
};

template<typename Machine, typename Char>
    requires FiniteStateMachine<Machine, Char>
class Lexer : public LexerBase<Char>
{
public:
    using CharType = Char;
    using TokenType = Token<Char, LexerBase<Char>>;

    Lexer(const Char* start_, const Char* end_, const std::string& fileName_) :
        flags(LexerFlags::none), 
        line(1), 
        current(tokens.end()), 
        token(this),
        separatorChar('\0'), 
        start(start_), 
        end(end_), 
        pos(start), 
        fileName(fileName_), 
        countLines(true), 
        keywordMap(nullptr), 
        farthestPos(GetPos())
    {
        SetKeywordMap(GetKeywordMap<Char>());
    }
    int64_t operator*() const
    {
        return current->id;
    }
    void operator++()
    {
        if (current != tokens.end())
        {
            ++current;
        }
        if (current == tokens.end())
        {
            NextToken();
        }
        else
        {
            line = current->line;
        }
        if (GetFlag(LexerFlags::farthestError))
        {
            int64_t p = GetPos();
            if (p > farthestPos)
            {
                farthestPos = p;
                farthestRuleContext = ruleContext;
            }
        }
    }
    int64_t GetPos() const
    {
        int32_t p = static_cast<int32_t>(current - tokens.begin());
        return (static_cast<int64_t>(line) << 32) | static_cast<int64_t>(p);
    }
    void SetPos(int64_t pos)
    {
        current = tokens.begin() + static_cast<int32_t>(pos);
        line = static_cast<int32_t>(pos >> 32);
    }
    const Token<Char, LexerBase<Char>>& GetToken(int64_t pos) const override
    {
        int32_t tokenIndex = static_cast<int32_t>(pos);
        if (tokenIndex >= 0 && tokenIndex < tokens.size())
        {
            return tokens[tokenIndex];
        }
        else
        {
            throw std::runtime_error("invalid token index");
        }
    }
    const std::string& FileName() const override
    {
        return fileName;
    }
    int Line() const override
    {
        return line;
    }
    void SetKeywordMap(KeywordMap<Char>* keywordMap_) 
    { 
        keywordMap = keywordMap_; 
    }
    LexerFlags Flags() const { return flags; }
    bool GetFlag(LexerFlags flag) const { return (flags & flag) != LexerFlags::none; }
    void SetFlag(LexerFlags flag) { flags = flags | flag; }
    void ResetFlag(LexerFlags flag) { flags = flags & ~flag; }
    void PushRule(int ruleId)
    {
        ruleContext.push_back(ruleId);
    }
    void PopRule()
    {
        ruleContext.pop_back();
    }
    int64_t GetKeywordToken(const Lexeme<Char>& lexeme) const override
    {
        if (keywordMap)
        {
            return keywordMap->GetKeywordToken(lexeme);
        }
        else
        {
            return INVALID_TOKEN;
        }
    }
    void Retract() override
    { 
        token.match.end = pos; 
    }
    const Token<Char, LexerBase<Char>>& CurrentToken() const override
    {
        return token;
    }
private:
    void NextToken()
    {
        int state = 0;
        while (true)
        {
            Char c = separatorChar;
            if (pos != end)
            {
                c = *pos;
            }
            else if (c == '\0')
            {
                break;
            }
            if (state == 0)
            {
                lexeme.begin = pos;
                token.id = INVALID_TOKEN;
                token.line = line;
            }
            if (pos == end)
            {
                lexeme.end = end;
            }
            else
            {
                lexeme.end = pos + 1;
            }
            state = Machine::NextState(state, c, *this);
            if (state == -1)
            {
                if (token.id == CONTINUE_TOKEN)
                {
                    if (pos == end)
                    {
                        break;
                    }
                    else
                    {
                        pos = token.match.end;
                    }
                    state = 0;
                    continue;
                }
                else if (token.id == INVALID_TOKEN)
                {
                    if (pos == end)
                    {
                        break;
                    }
                    else
                    {
                        throw std::runtime_error("soul::lexer::Lexer::NextToken(): error: invalid character '" + ToUtf8(std::u32string(1, c)) + "' in file '" + fileName + "' at line " + std::to_string(line));
                    }
                }
                else
                {
                    tokens.push_back(token);
                    current = tokens.end() - 1;
                    pos = token.match.end;
                    return;
                }
            }
            if (c == '\n' && countLines)
            {
                ++line;
            }
            ++pos;
        }
        token.id = INVALID_TOKEN;
        state = Machine::NextState(state, '\0', *this);
        int64_t p = -1;
        if (token.id != INVALID_TOKEN && token.id != CONTINUE_TOKEN)
        {
            tokens.push_back(token);
            current = tokens.end() - 1;
            p = GetPos();
        }
        Token<Char, LexerBase<Char>> endToken(END_TOKEN, this);
        endToken.match.begin = end;
        endToken.match.end = end;
        tokens.push_back(endToken);
        if (p == -1)
        {
            current = tokens.end() - 1;
            p = GetPos();
        }
        SetPos(p);
    }
    LexerFlags flags;
    Char separatorChar;
    std::vector<Token<Char, LexerBase<Char>>> tokens;
    std::vector<Token<Char, LexerBase<Char>>>::iterator current;
    Token<Char, LexerBase<Char>> token;
    Lexeme<Char> lexeme;
    int32_t line;
    const Char* start;
    const Char* end;
    const Char* pos;
    std::string fileName;
    bool countLines;
    KeywordMap<Char>* keywordMap;
    int64_t farthestPos;
    std::vector<int> ruleContext;
    std::vector<int> farthestRuleContext;
};

} // namespace soul

