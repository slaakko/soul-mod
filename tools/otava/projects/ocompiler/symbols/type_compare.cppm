export module otava.symbols.type_compare;

import std;

export namespace otava::symbols {

class TypeSymbol;
class Context;

struct TypeIdLess
{
    bool operator()(TypeSymbol* left, TypeSymbol* right) const;
};

bool TypesEqual(TypeSymbol* left, TypeSymbol* right, Context* context);

} // namespace otava::symbols
