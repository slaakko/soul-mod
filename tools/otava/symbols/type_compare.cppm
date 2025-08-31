export module otava.symbols.type_compare;

import std;

export namespace otava::symbols {

class TypeSymbol;

struct TypeIdLess
{
    bool operator()(TypeSymbol* left, TypeSymbol* right) const;
};

bool TypesEqual(TypeSymbol* left, TypeSymbol* right);

} // namespace otava::symbols
