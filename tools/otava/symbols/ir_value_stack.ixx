// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.ir_value_stack;

import std.core;
import otava.intermediate.value;

export namespace otava::symbols {

class IrValueStack
{
public:
    void Push(otava::intermediate::Value* value)
    {
        s.push_back(value);
    }
    otava::intermediate::Value* Pop()
    {
        otava::intermediate::Value* top = s.back();
        s.pop_back();
        return top;
    }
    void Dup()
    {
        s.push_back(s.back());
    }
    void Swap()
    {
        std::swap(s.back(), s[s.size() - 2]);
    }
    void Rotate()
    {
        std::swap(s[s.size() - 3], s[s.size() - 2]);
        std::swap(s.back(), s[s.size() - 2]);
    }
private:
    std::vector<otava::intermediate::Value*> s;
};

} // namespace otava::symbols
