// =================================
// Copyright (c) 2022 Seppo Laakko
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

std::string ToLiteralStr(int64_t value, int size)
{
    switch (size)
    {
        case 1: 
        {
            return ToHexStr(util::ToHexString(static_cast<uint8_t>(value)) + "h");
        }
        case 2: 
        {
            return ToHexStr(util::ToHexString(static_cast<uint16_t>(value)) + "h");
        }
        case 4: 
        {
            return ToHexStr(util::ToHexString(static_cast<uint32_t>(value)) + "h");
        }
        case 8: 
        {
            return ToHexStr(util::ToHexString(static_cast<uint64_t>(value)) + "h");
        }
    }
    return ToHexStr(util::ToHexString(static_cast<uint64_t>(value)) + "h");
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
}

std::string UniqueLiteral::ToString() const
{
    return ToLiteralStr(GetValue(), size);
}

} // namespace otava::assembly
