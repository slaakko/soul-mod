// =================================
// Copyright (c) 2023 Seppo Laakko
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
    virtual std::string ToString() const { return Name(); }
private:
    std::string name;
};

} // namespace otava::assembly
