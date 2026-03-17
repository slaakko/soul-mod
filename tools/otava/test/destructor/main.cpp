import std;

class Symbol
{
public:
    Symbol() {}
    virtual ~Symbol() { std::cout << "~Symbol called\n"; }
};

class FunctionSymbol : public Symbol
{
public:
    FunctionSymbol() {}
};

class ClassCopyCtor : public FunctionSymbol
{
public:
    ClassCopyCtor() {}
    ~ClassCopyCtor() { std::cout << "~ClassCopyCtor called!"; }
};

class Operation
{
public:
    Operation() {}
    virtual ~Operation() {}
};

class ClassCopyCtorOperation : public Operation
{
public:
    ClassCopyCtorOperation() {}
    void AddFunction(FunctionSymbol* fn) { functions.push_back(std::unique_ptr<FunctionSymbol>(fn)); }
private:
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

int main()
{
    ClassCopyCtorOperation o;
    o.AddFunction(new ClassCopyCtor());
}
