import std;

class FunctionSymbol
{
public:
    FunctionSymbol(const std::u32string& fullName_) : fullName(fullName_)
    {
    }
    std::u32string FullName() const
    {
        return fullName;
    }
    inline bool IsFunctionDefinitionSymbol() const noexcept { return true; }
private:
    std::u32string fullName;
};

int main()
{
    FunctionSymbol fn(U"abc");
    std::set<std::u32string> viableFunctionFullNameSet;
    FunctionSymbol* viableFunction = &fn;
    if (viableFunction->IsFunctionDefinitionSymbol() &&
        viableFunctionFullNameSet.find(viableFunction->FullName()) != viableFunctionFullNameSet.end())
    {
        return 0;
    }
}
