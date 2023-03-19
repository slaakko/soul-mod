export module otava.symbols.type_compare;

import std.core;

export namespace otava::symbols {

class TypeSymbol;

bool TypesEqual(TypeSymbol* left, TypeSymbol* right);

} // namespace otava::symbols
