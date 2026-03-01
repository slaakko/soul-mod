import std;

class StatementBinder
{
public:
    StatementBinder() {}
    ~StatementBinder() {}
};

int BindFunction()
{
    bool bound = false;
    bool isTemplate = false;
    bool parse = true;
    if (bound) return 1;
    if (isTemplate) return 2;
    if (parse) return 3;
    StatementBinder binder;
    return 4;
}
