// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.derivations;

import otava.symbols.reader;
import otava.symbols.writer;

namespace otava::symbols {

Derivations Merge(const Derivations& left, const Derivations& right)
{
    Derivations merged;
    if (HasDerivation(left, Derivation::constDerivation))
    {
        merged.vec.push_back(Derivation::constDerivation);
    }
    else if (HasDerivation(right, Derivation::constDerivation))
    {
        merged.vec.push_back(Derivation::constDerivation);
    }
    if (HasDerivation(left, Derivation::volatileDerivation))
    {
        merged.vec.push_back(Derivation::volatileDerivation);
    }
    else if (HasDerivation(right, Derivation::volatileDerivation))
    {
        merged.vec.push_back(Derivation::volatileDerivation);
    }
    int leftPointerCount = PointerCount(left);
    int rightPointerCount = PointerCount(right);
    int pointerCount = leftPointerCount + rightPointerCount;
    if (pointerCount > 0)
    {
        for (int i = 0; i < pointerCount; ++i)
        {
            merged.vec.push_back(Derivation::pointerDerivation);
        }
    }
    if (HasDerivation(left, Derivation::lvalueRefDerivation))
    {
        merged.vec.push_back(Derivation::lvalueRefDerivation);
    }
    else if (HasDerivation(right, Derivation::lvalueRefDerivation))
    {
        merged.vec.push_back(Derivation::lvalueRefDerivation);
    }
    if (HasDerivation(left, Derivation::rvalueRefDerivation))
    {
        merged.vec.push_back(Derivation::rvalueRefDerivation);
    }
    else if (HasDerivation(right, Derivation::rvalueRefDerivation))
    {
        merged.vec.push_back(Derivation::rvalueRefDerivation);
    }
    return merged;
}

bool HasDerivation(const Derivations& derivations, Derivation derivation)
{
    return std::find(derivations.vec.cbegin(), derivations.vec.cend(), derivation) != derivations.vec.cend();
}

int PointerCount(const Derivations& derivations)
{
    return static_cast<int>(std::count(derivations.vec.cbegin(), derivations.vec.cend(), Derivation::pointerDerivation));
}

Derivations Plain(const Derivations& derivations)
{
    Derivations modifiedDerivations;
    for (const auto& derivation : derivations.vec)
    {
        if (derivation == Derivation::pointerDerivation)
        {
            modifiedDerivations.vec.push_back(derivation);
        }
    }
    return modifiedDerivations;
}

Derivations RemoveConst(const Derivations& derivations)
{
    Derivations modifiedDerivations;
    bool first = true;
    for (const auto& derivation : derivations.vec)
    {
        if (first && derivation == Derivation::constDerivation)
        {
            first = false;
        }
        else
        {
            modifiedDerivations.vec.push_back(derivation);
        }
    }
    return modifiedDerivations;
}

Derivations RemovePointer(const Derivations& derivations)
{
    Derivations modifiedDerivations;
    bool first = true;
    for (const auto& derivation : derivations.vec)
    {
        if (first && derivation == Derivation::pointerDerivation)
        {
            first = false;
        }
        else
        {
            modifiedDerivations.vec.push_back(derivation);
        }
    }
    return modifiedDerivations;
}

Derivations RemoveLValueRef(const Derivations& derivations)
{
    Derivations modifiedDerivations;
    bool first = true;
    for (const auto& derivation : derivations.vec)
    {
        if (first && derivation == Derivation::lvalueRefDerivation)
        {
            first = false;
        }
        else
        {
            modifiedDerivations.vec.push_back(derivation);
        }
    }
    return modifiedDerivations;
}

Derivations RemoveRValueRef(const Derivations& derivations)
{
    Derivations modifiedDerivations;
    bool first = true;
    for (const auto& derivation : derivations.vec)
    {
        if (first && derivation == Derivation::rvalueRefDerivation)
        {
            first = false;
        }
        else
        {
            modifiedDerivations.vec.push_back(derivation);
        }
    }
    return modifiedDerivations;
}

Derivations UnifyDerivations(const Derivations& left, const Derivations& right)
{
    Derivations result;
    if (HasDerivation(left, Derivation::constDerivation) || HasDerivation(right, Derivation::constDerivation))
    {
        result.vec.push_back(Derivation::constDerivation);
    }
    int pointerCount = PointerCount(left) + PointerCount(right);
    for (int i = 0; i < pointerCount; ++i)
    {
        result.vec.push_back(Derivation::pointerDerivation);
    }
    if (HasDerivation(left, Derivation::lvalueRefDerivation))
    {
        result.vec.push_back(Derivation::lvalueRefDerivation);
    }
    else if (HasDerivation(left, Derivation::rvalueRefDerivation))
    {
        result.vec.push_back(Derivation::rvalueRefDerivation);
    }
    else if (HasDerivation(right, Derivation::lvalueRefDerivation))
    {
        result.vec.push_back(Derivation::lvalueRefDerivation);
    }
    else if (HasDerivation(right, Derivation::rvalueRefDerivation))
    {
        result.vec.push_back(Derivation::rvalueRefDerivation);
    }
    return result;
}

int CountMatchingDerivations(const Derivations& left, const Derivations& right)
{
    int matchingDerivationsCount = 0;
    if (HasDerivation(left, Derivation::constDerivation) && HasDerivation(right, Derivation::constDerivation))
    {
        ++matchingDerivationsCount;
    }
    if (!HasDerivation(left, Derivation::constDerivation) && !HasDerivation(right, Derivation::constDerivation))
    {
        ++matchingDerivationsCount;
    }
    int leftPointerCount = PointerCount(left);
    int rightPointerCount = PointerCount(right);
    matchingDerivationsCount += std::min(leftPointerCount, rightPointerCount);
    if (HasDerivation(left, Derivation::lvalueRefDerivation) && HasDerivation(right, Derivation::lvalueRefDerivation))
    {
        ++matchingDerivationsCount;
    }
    else if (HasDerivation(left, Derivation::rvalueRefDerivation) && HasDerivation(right, Derivation::rvalueRefDerivation))
    {
        ++matchingDerivationsCount;
    }
    return matchingDerivationsCount;
}

void Write(Writer& writer, const Derivations& derivations)
{
    std::uint8_t count = static_cast<std::uint8_t>(derivations.vec.size());
    writer.GetBinaryStreamWriter().Write(count);
    for (const auto d : derivations.vec)
    {
        writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(d));
    }
}

void Read(Reader& reader, Derivations& derivations)
{
    derivations.vec.clear();
    std::uint8_t count = reader.GetBinaryStreamReader().ReadByte();
    for (std::uint8_t i = 0; i < count; ++i)
    {
        std::uint8_t b = reader.GetBinaryStreamReader().ReadByte();
        Derivation d = static_cast<Derivation>(b);
        derivations.vec.push_back(d);
    }
}

} // namespace otava::symbols
