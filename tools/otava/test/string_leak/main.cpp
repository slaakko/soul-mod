import std;

class Foo
{
public:
    Foo(const std::string& s_) : s(s_) {}
private:
    std::string s;
};

class Lexeme
{
public:
    std::string ToString() const
    {
        return "abc";
    }
};

class Token
{
public:
    std::string ToString() const
    {
        return lexeme.ToString();
    }
private:
    Lexeme lexeme;
};

Foo* foo(Token& token)
{
    std::string x;
    return new Foo(token.ToString());
}

int main()
{
    Token token;
    std::unique_ptr<Foo> f(foo(token));
}
