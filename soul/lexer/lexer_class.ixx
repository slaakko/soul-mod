// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.cls;

import std.core;
import soul.ast.source.pos;
import util.unicode;
import soul.ast.slg;
import soul.lexer.token.parser;
import soul.lexer.base;
import soul.lexer.concepts;
import soul.lexer.error;
import soul.lexer.parsing.log;
import soul.lexer.token;
import soul.ast.lexer.pos.pair;

export namespace soul::lexer {

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

bool parsing_error_thrown = false;

template<class Char, class LexerBaseT>
struct LexerState
{
    LexerState(LexerBaseT* lexer) : token(lexer), line(0), lexeme(), pos(), tokens(), flags(), recordedPosPair(), farthestPos(), currentPos()
    {
    }
    soul::lexer::Token<Char, LexerBaseT> token;
    int line;
    Lexeme<Char> lexeme;
    const Char* pos;
    std::vector<soul::lexer::Token<Char, LexerBaseT>> tokens;
    LexerFlags flags;
    soul::ast::lexer::pos::pair::LexerPosPair recordedPosPair;
    int64_t farthestPos;
    std::vector<int64_t> ruleContext;
    std::vector<int64_t> farthestRuleContext;
    int64_t currentPos;
};

template<typename Stack>
    requires RuleStack<Stack>
struct RuleGuard
{
    RuleGuard(Stack& stack_, int64_t ruleId) : stack(stack_)
    {
        stack.PushRule(ruleId);
    }
    ~RuleGuard()
    {
        stack.PopRule();
    }
    Stack& stack;
};

template<typename Char>
const Char* LineStart(const Char* start, const Char* p)
{
    while (p != start && *p != '\n' && *p != '\r')
    {
        --p;
    }
    if (p != start)
    {
        ++p;
    }
    return p;
}

template<typename Char>
const Char* LineEnd(const Char* end, const Char* p)
{
    while (p != end && *p != '\n' && *p != '\r')
    {
        ++p;
    }
    return p;
}

template<typename Machine, typename Char>
    requires FiniteStateMachine<Machine, Char>
class Lexer : public LexerBase<Char>
{
public:
    using LexerType = Lexer<Machine, Char>;
    using CharType = Char;
    using TokenType = Token<Char, LexerBase<Char>>;
    using VariableClassType = Machine::Variables;
    using PPHook = void (*)(LexerType& lexer, TokenType& token);

    Lexer(const Char* start_, const Char* end_, const std::string& fileName_) :
        flags(LexerFlags::none),
        file(-1),
        line(1),
        current(tokens.end()),
        token(this),
        separatorChar('\0'),
        start(start_),
        end(end_),
        pos(start),
        fileName(fileName_),
        countLines(true),
        classMap(nullptr),
        tokenCollection(nullptr),
        keywordMap(nullptr),
        ruleNameMapPtr(nullptr),
        farthestPos(GetPos()),
        log(nullptr),
        vars(),
        state(this),
        ppHook(nullptr),
        skip(false)
    {
        ComputeLineStarts();
    }
    int64_t operator*() const
    {
        return current->id;
    }
    void operator++()
    {
        if (GetFlag(LexerFlags::recordedParse))
        {
            // precondition: !tokens.empty() && tokens.back().id == END_TOKEN
            int64_t currentPos = GetPos();
            if (currentPos == recordedPosPair.end)
            {
                current = tokens.end() - 1; // set current to last token whose id is END_TOKEN
                pos = tokens.back().match.end;
            }
            else
            {
                ++current;
            }
            line = current->line;
        }
        else
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
            int64_t p = GetPos();
            if (p > farthestPos)
            {
                farthestPos = p;
                farthestRuleContext = ruleContext;
            }
        }
    }
    int64_t GetPos() const override
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
    int File() const override
    {
        return file;
    }
    void SetFile(int file_)
    {
        file = file_;
    }
    int Line() const override
    {
        return line;
    }
    void SetLine(int32_t line_) override
    {
        line = line_;
    }
    ClassMap<Char>* GetClassMap() const override
    {
        return classMap;
    }
    void SetClassMap(ClassMap<Char>* classMap_) override
    {
        classMap = classMap_;
    }
    soul::ast::slg::TokenCollection* GetTokenCollection() const override
    {
        return tokenCollection;
    }
    void SetTokenCollection(soul::ast::slg::TokenCollection* tokenCollection_) override
    {
        tokenCollection = tokenCollection_;
    }
    KeywordMap<Char>* GetKeywordMap() const override
    {
        return keywordMap;
    }
    void SetKeywordMap(KeywordMap<Char>* keywordMap_) override
    {
        keywordMap = keywordMap_;
    }
    std::map<int64_t, std::string>* GetRuleNameMapPtr() const override
    {
        return ruleNameMapPtr;
    }
    void SetRuleNameMapPtr(std::map<int64_t, std::string>* ruleNameMapPtr_) override
    {
        ruleNameMapPtr = ruleNameMapPtr_;
    }
    LexerFlags Flags() const { return flags; }
    bool GetFlag(LexerFlags flag) const { return (flags & flag) != LexerFlags::none; }
    void SetFlag(LexerFlags flag) { flags = flags | flag; }
    void ResetFlag(LexerFlags flag) { flags = flags & ~flag; }
    void PushRule(int64_t ruleId)
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
    Token<Char, LexerBase<Char>>& CurrentToken() override
    {
        return token;
    }
    void EraseTail() override
    {
        tokens.erase(current + 1, tokens.end());
    }
    const Lexeme<Char>& CurrentLexeme() const override
    {
        return lexeme;
    }
    Lexeme<Char>& CurrentLexeme() override
    {
        return lexeme;
    }
    std::string GetTokenName(int64_t tokenID) const
    {
        soul::ast::slg::TokenCollection* tokenCollection = GetTokenCollection();
        auto token = tokenCollection->GetToken(tokenID);
        if (token)
        {
            return token->Name();
        }
        else
        {
            return "<unknown token>";
        }
    }
    std::string GetTokenInfo(int64_t tokenID) const
    {
        soul::ast::slg::TokenCollection* tokenCollection = GetTokenCollection();
        auto token = tokenCollection->GetToken(tokenID);
        if (token)
        {
            return token->Info();
        }
        else
        {
            return "<unknown token>";
        }
    }
    inline int GetLine(int64_t pos) const
    {
        return pos >> 32;
    }
    soul::ast::SourcePos GetSourcePos(int64_t pos) const
    {
        const Char* s = start;
        int line = GetLine(pos);
        if (line < lineStarts.size())
        {
            s = lineStarts[line];
        }
        Token token = GetToken(pos);
        int col = static_cast<int>(token.match.begin - s + 1);
        return soul::ast::SourcePos(pos, file, line, col);
    }
    std::string ErrorLines(int64_t pos) const override
    {
        auto token = GetToken(pos);
        std::basic_string<Char> lines;
        const Char* lineStart = LineStart(start, token.match.begin);
        const Char* lineEnd = LineEnd(end, token.match.end);
        if (token.match.begin > lineStart)
        {
            lines.append(std::basic_string<Char>(lineStart, token.match.begin));
        }
        lines.append(token.match.ToString());
        if (lineEnd > token.match.end)
        {
            lines.append(std::basic_string<Char>(token.match.end, lineEnd));
        }
        lines.append(1, '\n');
        if (token.match.begin > lineStart)
        {
            lines.append(token.match.begin - lineStart, ' ');
        }
        lines.append(std::max(static_cast<int64_t>(1), token.match.end - token.match.begin), '^');
        if (lineEnd > token.match.end)
        {
            lines.append(lineEnd - token.match.end, ' ');
        }
        return util::ToUtf8(lines);
    }
    void ThrowExpectationFailure(int64_t pos, const std::string& name)
    {
        soul::ast::SourcePos sourcePos = GetSourcePos(pos);
        std::string parserStateStr = GetParserStateStr();
        throw ParsingException("parsing error at '" + fileName + ":" + std::to_string(sourcePos.line) + "': " + name + " expected:\n" + ErrorLines(pos) + parserStateStr,
            fileName, sourcePos);
    }
    std::string GetParserStateStr() const
    {
        std::string parserStateStr;
        int n = farthestRuleContext.size();
        if (ruleNameMapPtr && n > 0)
        {
            parserStateStr.append("\nParser state:\n");
            for (int i = 0; i < n; ++i)
            {
                int64_t ruleId = farthestRuleContext[i];
                auto it = (*ruleNameMapPtr).find(ruleId);
                if (it != (*ruleNameMapPtr).cend())
                {
                    std::string ruleName = it->second;
                    parserStateStr.append(ruleName.append("\n"));
                }
            }
        }
        return parserStateStr;
    }
    std::string GetError(int64_t pos) const
    {
        std::string parserStateStr = GetParserStateStr();
        return "parsing error at '" + fileName + ":" + std::to_string(GetLine(pos)) + "':\n" + ErrorLines(pos) + parserStateStr;
    }
    void ThrowFarthestError()
    {
        std::cout.flush();
        soul::ast::SourcePos sourcePos = GetSourcePos(farthestPos);
        parsing_error_thrown = true;
        throw ParsingException(GetError(farthestPos), fileName, sourcePos);
    }
    void SetLog(ParsingLog* log_)
    {
        log = log_;
    }
    ParsingLog* Log() const
    {
        return log;
    }
    std::string RestOfLine(int maxLineLength) const
    {
        std::string restOfLine(util::ToUtf8(current->match.ToString()) + ToString(current->match.end, pos) + ToString(pos, LineEnd(end, pos)));
        if (maxLineLength != 0)
        {
            restOfLine = restOfLine.substr(0, maxLineLength);
        }
        return restOfLine;
    }
    std::vector<int> GetLineStartIndeces() const
    {
        std::vector<int> lineStartIndeces;
        for (int i = 0; i < lineStarts.size(); ++i)
        {
            lineStartIndeces.push_back(static_cast<int>(lineStarts[i] - start));
        }
        return lineStartIndeces;
    }
    soul::lexer::Variables* GetVariables() const override
    {
        return const_cast<soul::lexer::Variables*>(static_cast<const soul::lexer::Variables*>(&vars));
    }
    const Char* Start() const
    {
        return start;
    }
    const Char* Pos() const
    {
        return pos;
    }
    void SetPos(const Char* pos_) override
    {
        pos = pos_;
    }
    const Char* End() const override
    {
        return end;
    }
    const std::vector<Token<Char, LexerBase<Char>>>& Tokens() const
    {
        return tokens;
    }
    void SetCurrentMatchEnd(const Char* end) override
    {
        current->match.end = end;
    }
    void Increment() override
    {
        operator++();
    }
    void MoveToEnd() override
    {
        Token<Char, LexerBase<Char>> endToken(END_TOKEN, this);
        endToken.match.begin = end;
        endToken.match.end = end;
        tokens.push_back(endToken);
        current = tokens.end() - 1;
    }
    void BeginRecordedParse(const soul::ast::lexer::pos::pair::LexerPosPair& lexerPosPair) override
    {
        PushState();
        if (tokens.empty() || tokens.back().id != END_TOKEN)
        {
            Token<Char, LexerBase<Char>> endToken(END_TOKEN, this);
            endToken.match.begin = end;
            endToken.match.end = end;
            tokens.push_back(endToken);
        }
        recordedPosPair = lexerPosPair;
        SetPos(recordedPosPair.start);
        SetFlag(LexerFlags::recordedParse);
    }
    void EndRecordedParse() override
    {
        PopState();
    }
    void SetPPHook(PPHook ppHook_)
    {
        ppHook = ppHook_;
    }
    void PreprocessCurrentToken() override
    {
        if (ppHook)
        {
            ppHook(*this, token); 
        }
    }
    void PushState()
    {
        stateStack.push(GetState());
    }
    void PopState()
    {
        SetState(stateStack.top());
        stateStack.pop();
    }
    LexerState<Char, LexerBase<Char>> GetState()
    {
        LexerState<Char, LexerBase<Char>> state(this);
        state.token = token;
        state.line = line;
        state.lexeme = lexeme;
        state.pos = pos;
        state.tokens = tokens;
        state.flags = flags;
        state.recordedPosPair = recordedPosPair;
        state.farthestPos = farthestPos;
        state.ruleContext = ruleContext;
        state.farthestRuleContext = farthestRuleContext;
        state.currentPos = GetPos();
        return state;
    }
    void SetState(const LexerState<Char, LexerBase<Char>>& state)
    {
        token = state.token;
        line = state.line;
        lexeme = state.lexeme;
        pos = state.pos;
        tokens = state.tokens;
        flags = state.flags;
        recordedPosPair = state.recordedPosPair;
        farthestPos = state.farthestPos;
        ruleContext = state.ruleContext;
        farthestRuleContext = state.farthestRuleContext;
        SetPos(state.currentPos);
    }
    void Skip(bool skip_) 
    {
        skip = skip_;
        current = tokens.end();
    }
    bool Skipping() const
    {
        return skip;
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
                        throw std::runtime_error("soul::lexer::Lexer::NextToken(): error: invalid character '" + util::ToUtf8(std::u32string(1, c)) + "' in file '" + fileName + "' at line " + std::to_string(line));
                    }
                }
                else
                {
                    if (!skip)
                    {
                        tokens.push_back(token);
                        current = tokens.end() - 1;
                        pos = token.match.end;
                        return;
                    }
                    else
                    {
                        pos = token.match.end;
                        return;
                    }
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
    void ComputeLineStarts()
    {
        lineStarts.push_back(pos);
        const Char* p = pos;
        bool startOfLine = true;
        while (p != end)
        {
            if (startOfLine)
            {
                lineStarts.push_back(p);
            }
            startOfLine = *p == '\n';
            ++p;
        }
        lineStarts.push_back(end);
    }
    LexerFlags flags;
    soul::ast::lexer::pos::pair::LexerPosPair recordedPosPair;
    Char separatorChar;
    std::vector<Token<Char, LexerBase<Char>>> tokens;
    std::vector<Token<Char, LexerBase<Char>>>::iterator current;
    Token<Char, LexerBase<Char>> token;
    Lexeme<Char> lexeme;
    int32_t file;
    int32_t line;
    const Char* start;
    const Char* end;
    const Char* pos;
    std::string fileName;
    bool countLines;
    ClassMap<Char>* classMap;
    soul::ast::slg::TokenCollection* tokenCollection;
    KeywordMap<Char>* keywordMap;
    int64_t farthestPos;
    std::vector<int64_t> ruleContext;
    std::vector<int64_t> farthestRuleContext;
    std::vector<const Char*> lineStarts;
    std::map<int64_t, std::string>* ruleNameMapPtr;
    ParsingLog* log;
    Machine::Variables vars;
    LexerState<Char, LexerBase<Char>> state;
    std::stack<LexerState<Char, LexerBase<Char>>> stateStack;
    PPHook ppHook;
    bool skip;
};

inline std::string GetEndTokenInfo()
{
    return "end-of-file";
}

template<typename Lexer>
void WriteBeginRuleToLog(Lexer& lexer, const std::string& ruleName)
{
    lexer.Log()->WriteBeginRule(ruleName);
    lexer.Log()->IncIndent();
    lexer.Log()->WriteTry(lexer.RestOfLine(lexer.Log()->MaxLineLength()));
    lexer.Log()->IncIndent();
}

template<typename Lexer>
void WriteSuccessToLog(Lexer& lexer, int64_t matchPos, const std::string& ruleName)
{
    lexer.Log()->DecIndent();
    lexer.Log()->WriteSuccess(util::ToUtf8(lexer.GetToken(matchPos).ToString()));
    lexer.Log()->DecIndent();
    lexer.Log()->WriteEndRule(ruleName);
}

template<typename Lexer>
void WriteFailureToLog(Lexer& lexer, const std::string& ruleName)
{
    lexer.Log()->DecIndent();
    lexer.Log()->WriteFail();
    lexer.Log()->DecIndent();
    lexer.Log()->WriteEndRule(ruleName);
}

} // namespace soul::lexer
