// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.derivations;

import std.core;

export namespace soul::cpp20::symbols {

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

class Writer;
class Reader;

void Write(Writer& writer, const Derivations& derivations);
void Read(Reader& reader, Derivations& derivations);

} // namespace soul::cpp20::symbols
