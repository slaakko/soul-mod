// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.literal;

import util.text.util;

namespace otava::assembly {

std::string ToLiteralStr(int64_t value)
{
    return util::ToHexString(static_cast<uint64_t>(value)) + "h";
}

Literal::Literal(int64_t value_) : Value(ToLiteralStr(value_)), value(value_)
{
}

} // namespace otava::assembly
