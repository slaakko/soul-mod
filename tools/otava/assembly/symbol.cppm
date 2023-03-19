// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.symbol;

import std.core;
import otava.assembly.value;

export namespace otava::assembly {

class Symbol : public Value
{
public:
    Symbol(const std::string& name_);
};

} // namespace otava::assembly
