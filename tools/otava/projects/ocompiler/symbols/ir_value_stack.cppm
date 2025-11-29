// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.ir_value_stack;

import std;
import otava.intermediate.data;

export namespace otava::symbols {

class IrValueStack
{
public:
    inline void Push(otava::intermediate::Value* value)
    {
        s.push_back(value);
    }
    inline otava::intermediate::Value* Pop()
    {
        if (s.empty())
        {
            ort_debug_break();
            int t = ort_generate_stack_trace();
            const char* trace = ort_get_stack_trace(t);
            if (trace)
            {
                std::cout << trace;
            }
            ort_free_stack_trace(t);
        }
        otava::intermediate::Value* top = s.back();
        s.pop_back();
        return top;
    }
    inline void Dup()
    {
        s.push_back(s.back());
    }
    inline void Swap()
    {
        std::swap(s.back(), s[s.size() - 2]);
    }
    inline void Rotate()
    {
        std::swap(s[s.size() - 3], s[s.size() - 2]);
        std::swap(s.back(), s[s.size() - 2]);
    }
    inline bool IsEmpty() const
    {
        return s.empty();
    }
private:
    std::vector<otava::intermediate::Value*> s;
};

} // namespace otava::symbols
