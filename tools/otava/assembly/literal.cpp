// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.literal;

import util.text.util;

namespace otava::assembly {

std::string ToHexStr(const std::string& hexStr)
{
    if ((hexStr[0] >= 'a' && hexStr[0] <= 'f') || (hexStr[0] >= 'A' && hexStr[0] <= 'F'))
    {
        return "0" + hexStr;
    }
    return hexStr;
}

std::string ToLiteralStr(std::int64_t value, int size)
{
    switch (size)
    {
        case 1: 
        {
            return ToHexStr(util::ToHexString(static_cast<std::uint8_t>(value)) + "h");
        }
        case 2: 
        {
            return ToHexStr(util::ToHexString(static_cast<std::uint16_t>(value)) + "h");
        }
        case 4: 
        {
            return ToHexStr(util::ToHexString(static_cast<std::uint32_t>(value)) + "h");
        }
        case 8: 
        {
            return ToHexStr(util::ToHexString(static_cast<std::uint64_t>(value)) + "h");
        }
    }
    return ToHexStr(util::ToHexString(static_cast<std::uint64_t>(value)) + "h");
}

Literal::Literal(std::int64_t value_, int size_) : Value(ToLiteralStr(value_, size_)), value(value_), size(size_)
{
}

UniqueLiteral::UniqueLiteral(std::int64_t value_, int size_) : Literal(value_, size_)
{
}

void UniqueLiteral::SetValue(std::int64_t value_)
{
    value = value_;
}

std::string UniqueLiteral::ToString() const
{
    return ToLiteralStr(GetValue(), size);
}

} // namespace otava::assembly
