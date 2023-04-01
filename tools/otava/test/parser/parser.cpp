import std.core;

namespace soul::parser {

struct Match
{
    Match(bool hit_) : hit(hit_), value(nullptr) {}
    Match(bool hit_, void* value_) : hit(hit_), value(value_) {}
    bool hit;
    void* value;
};

}

template<typename Lexer>
struct DeclarationParser
{
    static soul::parser::Match TypeName(Lexer& lexer);
};
    
template<typename Lexer>
soul::parser::Match DeclarationParser<Lexer>::TypeName(Lexer& lexer)
{
    auto vars = static_cast<typename Lexer::VariableClassType*>(lexer.GetVariables());
}

int main()
{
    return 0;
}
