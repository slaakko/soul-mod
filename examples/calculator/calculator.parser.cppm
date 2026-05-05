
// this file has been automatically generated from 'D:/work/soul-mod/examples/calculator/calculator.parser' using soul parser generator spg version 5.1.0

export module calculator.parser;

import std;
import soul.lexer;
import soul.parser;
import calculator;

export namespace calculator::parser {

template<typename LexerT>
struct CalculatorParser
{
    static double Parse(LexerT& lexer, calculator::Memory* memory);
    static soul::parser::Match expression(LexerT& lexer, calculator::Memory* memory);
    static soul::parser::Match assignment(LexerT& lexer, calculator::Memory* memory);
    static soul::parser::Match term(LexerT& lexer, calculator::Memory* memory);
    static soul::parser::Match weak_operator(LexerT& lexer);
    static soul::parser::Match factor(LexerT& lexer, calculator::Memory* memory);
    static soul::parser::Match strong_operator(LexerT& lexer);
    static soul::parser::Match unary(LexerT& lexer, calculator::Memory* memory);
    static soul::parser::Match primary(LexerT& lexer, calculator::Memory* memory);
};

} // namespace calculator::parser
