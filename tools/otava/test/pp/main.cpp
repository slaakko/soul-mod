import std;

template<typename Machine, typename Char>
class Lexer
{
public:
    using LexerType = Lexer<Machine, Char>;
    using TokenType = int;
    using PPHook = void (*)(LexerType* lexer, TokenType* token);

    Lexer()
    {
    }
    void SetPPHook(PPHook ppHook_) noexcept
    {
        ppHook = ppHook_;
    }
private:
    PPHook ppHook;
};

template<typename Char>
struct OtavaLexer
{
    OtavaLexer()
    {
    }
};

void PreprocessPPLine(Lexer<OtavaLexer<char32_t>, char32_t>* lxr, int* token)
{
}

int main()
{
    Lexer<OtavaLexer<char32_t>, char32_t> lxr;
    lxr.SetPPHook(PreprocessPPLine);
}
