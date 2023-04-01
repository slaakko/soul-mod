import std.core;

class FooLexer
{
};

template<typename Lexer>
struct Parser
{
    static void ParseFoo(Lexer& lexer);
};

template<typename Lexer>
void Parser::ParseFoo(Lexer& lexer)
{
}

template struct Parser<FooLexer>;

int main()
{
    return 0;
}
