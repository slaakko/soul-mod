// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.derivations;

import std.core;

export namespace otava::symbols {

enum class Derivation : uint8_t
{
    none = 0, constDerivation = 1, volatileDerivation = 2, lvalueRefDerivation = 3, rvalueRefDerivation = 4, pointerDerivation = 5, max
};

struct Derivations
{
    std::vector<Derivation> vec;
    bool IsEmpty() const { return vec.empty(); }
};

Derivations Merge(const Derivations& left, const Derivations& right);

inline bool operator==(const Derivations& left, const Derivations& right)
{
    return left.vec == right.vec;
}

inline bool operator<(const Derivations& left, const Derivations& right)
{
    return left.vec < right.vec;
}

bool HasDerivation(const Derivations& derivations, Derivation derivation);
int PointerCount(const Derivations& derivations);
Derivations Plain(const Derivations& derivations);
Derivations RemoveConst(const Derivations& derivations);
Derivations RemovePointer(const Derivations& derivations);
Derivations RemoveLValueRef(const Derivations& derivations);
Derivations RemoveRValueRef(const Derivations& derivations);
Derivations UnifyDerivations(const Derivations& left, const Derivations& right);
int CountMatchingDerivations(const Derivations& left, const Derivations& right);

class Writer;
class Reader;

void Write(Writer& writer, const Derivations& derivations);
void Read(Reader& reader, Derivations& derivations);

} // namespace otava::symbols
