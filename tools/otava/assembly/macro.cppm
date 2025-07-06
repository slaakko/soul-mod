// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.macro;

import otava.assembly.value;
import std;

export namespace otava::assembly {

class Macro : public Value
{
public:
    Macro(const std::string& name_);
    void SetValue(Value* value_);
    Value* GetValue() const { return value; }
    std::string ToString() const override;
private:
    Value* value;
};

} // namespace otava::assembly
