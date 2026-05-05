// main.cpp:

import std;
import calculator;
import calculator.lexer;
import calculator.parser;
import util;

int main()
{
    try
    {
        calculator::Memory memory;
        while (true)
        {
            std::cout << "enter expression:" << "\n";
            std::string expr;
            std::getline(std::cin, expr);
            if (expr == "exit") break;
            std::u32string e = util::ToUtf32(expr);
            auto lexer = calculator::lexer::MakeLexer(e.c_str(), e.c_str() + e.length(), "<expr>");
            using LexerType = decltype(lexer);
            try
            {
                std::cout << calculator::parser::CalculatorParser<LexerType>::Parse(lexer, &memory) << "\n";
            }
            catch (const std::exception& ex)
            {
                std::cout << ex.what() << "\n";
            }
        }
        std::cout << "bye" << "\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return 1;
    }
}
