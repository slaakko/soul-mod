import std;

class Symbol
{
public:
    Symbol(int kind_) : kind(kind_)
    {
    }
    virtual ~Symbol()
    {
    }
    int Kind() const
    {
        return kind;
    }
    int kind;
};

class VariableSymbol : public Symbol
{
public:
    VariableSymbol() : Symbol(1) {}
};

class GroupSymbol : public Symbol
{
public:
    GroupSymbol() : Symbol(0)
    {
        variableSymbols.push_back(new VariableSymbol());
    }
    Symbol* GetSymbol() const
    {
        return variableSymbols.front();
    }
private:
    std::vector<VariableSymbol*> variableSymbols;
};

int main()
{
    GroupSymbol group;
    Symbol* sym = group.GetSymbol();
    std::cout << sym->Kind() << "\n";
}
