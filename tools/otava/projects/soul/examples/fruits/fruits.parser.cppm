
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/soul/examples/fruits/fruits.parser' using soul parser generator ospg version 5.0.0

export module fruits.parser;

import std;
import soul.lexer;
import soul.parser;
import fruits;

export namespace fruits::parser {

template<typename LexerT>
struct FruitParser
{
    static void Parse(LexerT& lexer, std::vector<std::unique_ptr<fruits::fruit>>* fruitList);
    static soul::parser::Match FruitList(LexerT& lexer, std::vector<std::unique_ptr<fruits::fruit>>* fruitList);
    static soul::parser::Match Fruit(LexerT& lexer);
};

} // namespace fruits::parser
