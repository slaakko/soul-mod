// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.derivations;

import std;

export namespace otava::symbols {

enum class Derivations : std::uint8_t
{
    none = 0, constDerivation = 1 << 0, volatileDerivation = 1 << 1, lvalueRefDerivation = 1 << 2, rvalueRefDerivation = 1 << 3, 
    refMask = lvalueRefDerivation | rvalueRefDerivation, 
    cvRefMask = 0x0Fu, 
    pointerMask = 0xF0u
};

constexpr int pointerShift = 4;
constexpr int maxPointerCount = 15;

constexpr Derivations operator|(Derivations left, Derivations right)
{
    return Derivations(std::uint8_t(left) | std::uint8_t(right));
}

constexpr Derivations operator&(Derivations left, Derivations right)
{
    return Derivations(std::uint8_t(left) & std::uint8_t(right));
}

constexpr Derivations operator~(Derivations derivations)
{
    return Derivations(~std::uint8_t(derivations));
}

constexpr bool HasDerivation(Derivations derivations, Derivations derivation) { return (derivations & derivation) != Derivations::none; }
constexpr int PointerCount(Derivations derivations) { return static_cast<int>(static_cast<std::uint8_t>(derivations & Derivations::pointerMask)) >> pointerShift; }
constexpr Derivations SetPointerCount(Derivations derivations, int pointerCount)
{
    return (derivations & ~Derivations::pointerMask) | static_cast<Derivations>(static_cast<std::uint8_t>(std::min(std::max(0, pointerCount), maxPointerCount) << pointerShift));
}
constexpr Derivations Plain(Derivations derivations) { return derivations & Derivations::pointerMask; }
constexpr Derivations RemoveConst(Derivations derivations) { return derivations & ~Derivations::constDerivation; }
constexpr Derivations RemovePointer(Derivations derivations) { return SetPointerCount(derivations, std::max(0, PointerCount(derivations) - 1)); }
constexpr Derivations RemoveLValueRef(Derivations derivations) { return derivations & ~Derivations::lvalueRefDerivation; }
constexpr Derivations RemoveRValueRef(const Derivations& derivations) { return derivations & ~Derivations::rvalueRefDerivation; }
Derivations Merge(Derivations left, Derivations right);
Derivations UnifyDerivations(Derivations left, Derivations right);
int CountMatchingDerivations(Derivations left, Derivations right);

class Writer;
class Reader;

void Write(Writer& writer, Derivations derivations);
void Read(Reader& reader, Derivations& derivations);

} // namespace otava::symbols
