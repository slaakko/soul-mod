// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.value;

import std.core;

export namespace otava::assembly {

class Value
{
public:
    Value(const std::string& name_);
    virtual ~Value();
    const std::string& Name() const { return name; }
private:
    std::string name;
};

} // namespace otava::assembly
