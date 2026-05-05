// calculator.cppm:

export module calculator;

import std;

export namespace calculator
{
    enum class Operator
    {
        plus, minus, times, divides
    };

    class Memory
    {
    public:
        Memory();
        void SetValue(const std::u32string& variableName, double value);
        double GetValue(const std::u32string& variableName) const;
    private:
        std::map<std::u32string, double> variableMap;
    };
}
