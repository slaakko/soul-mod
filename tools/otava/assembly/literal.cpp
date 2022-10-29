// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.literal;

import util.text.util;

namespace otava::assembly {

std::string ToLiteralStr(int64_t value, int size)
{
    switch (size)
    {
        case 1: return util::ToHexString(static_cast<uint8_t>(value)) + "h";
        case 2: return util::ToHexString(static_cast<uint16_t>(value)) + "h";
        case 4: return util::ToHexString(static_cast<uint32_t>(value)) + "h";
        case 8: return util::ToHexString(static_cast<uint64_t>(value)) + "h";
    }
    return util::ToHexString(static_cast<uint64_t>(value)) + "h";
}

Literal::Literal(int64_t value_, int size_) : Value(ToLiteralStr(value_, size_)), value(value_), size(size_)
{
}

UniqueLiteral::UniqueLiteral(int64_t value_, int size_) : Literal(value_, size_)
{
}

void UniqueLiteral::SetValue(int64_t value_)
{
    value = value_;
    name = ToLiteralStr(value_, size);
}

} // namespace otava::assembly
