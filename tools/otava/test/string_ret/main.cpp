import std;

class Lexer
{
public:
    Lexer(const char* start_, const char* end_, const std::string& fileName_) : 
        start(start_),
        end(end_),
        pos(start),
        fileName(fileName_),
    {
    }
private:
    const char* start;
    const char* end;
    const char* pos;
    std::string fileName;
};

void foo()
{
}

Lexer get_lexer()
{
    foo();
    auto lxr = Lexer("foo", "bar", "file");
    return lxr;
}

int main()
{
    auto lxr = get_lexer();
}
