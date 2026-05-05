// calculator.cpp:

module calculator;

import util;

namespace calculator 
{
    Memory::Memory()
    {
    }

    void Memory::SetValue(const std::u32string& variableName, double value)
    {
        variableMap[variableName] = value;
    }

    double Memory::GetValue(const std::u32string& variableName) const
    {
        auto it = variableMap.find(variableName);
        if (it != variableMap.end())
        {
            return it->second;
        }
        else
        {
            throw std::runtime_error("variable '" + util::ToUtf8(variableName) + "' not found");
        }
    }
}
