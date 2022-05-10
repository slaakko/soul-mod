import std.core; 
import soul.lexer;
import soul.parser;

using namespace soul;

const int64_t ID = 1234;

const int32_t tokenClassId = std::hash<std::string>{}("abc") & 0x7FFFFFFF;
const int64_t FOO = (static_cast<int64_t>(tokenClassId) << 32) | 1;

template<typename Char>
KeywordMap<Char>* GetKeywordMap()
{
    throw std::runtime_error("unsupported char type");
}

template<>
KeywordMap<char>* GetKeywordMap()
{
    static Keyword<char> keywords[]{ {"foo", 1}, {"bar", 2} };
    static KeywordMap<char> map(keywords);
    return &map;
}

template<>
KeywordMap<char8_t>* GetKeywordMap()
{
    static Keyword<char8_t> keywords[]{ {u8"foo", 1}, {u8"bar", 2} };
    static KeywordMap<char8_t> map(keywords);
    return &map;
}

template<>
KeywordMap<char16_t>* GetKeywordMap()
{
    static Keyword<char16_t> keywords[]{ {u"foo", 1}, {u"bar", 2} };
    static KeywordMap<char16_t> map(keywords);
    return &map;
}

template<>
KeywordMap<char32_t>* GetKeywordMap()
{
    static Keyword<char32_t> keywords[]{ {U"foo", 1}, {U"bar", 2} };
    static KeywordMap<char32_t> map(keywords);
    return &map;
}

template<typename Char>
class MyLexer
{
public:
    static int NextState(int state, Char c, LexerBase<Char>& lexer)
    {
        return 0;
    }
private:
    int64_t GetTokenId(int ruleIndex, LexerBase<Char>& lexer);
};

template<typename Char>
int64_t MyLexer<Char>::GetTokenId(int ruleIndex, LexerBase<Char>& lexer)
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
    }
    return CONTINUE_TOKEN;
}

template<typename Lexer>
    requires LexicalIterator<Lexer>
struct Parser
{
    static Match Parse(Lexer& lexer)
    {
        int64_t save = lexer.GetPos();
        if (*lexer == 1)
        {
            int64_t pos = lexer.GetPos();
            const auto& token = lexer.GetToken(pos);
            int32_t x = token.ToInt();
            ++lexer;
            return Match(true);
        }
        lexer.SetPos(save);
        return Match(false);
    }
};

int main()
{
    using ConcreteLexer = Lexer<MyLexer<char32_t>, char32_t>;
    std::basic_string<char32_t> s{ U"foo" };
    ConcreteLexer lexer(s.c_str(), s.c_str() + s.length(), "foo");
    ++lexer;
    Parser<ConcreteLexer>::Parse(lexer);
}
