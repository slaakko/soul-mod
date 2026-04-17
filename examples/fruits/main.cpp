import std;
import fruits;
import fruits.lexer;
import fruits.parser;
import fruits.token;
import util;

std::vector<std::unique_ptr<fruits::fruit>> parse_fruit_list(const std::string& fruitListText)
{
    std::u32string fruitList = util::ToUtf32(fruitListText);
    auto lexer = fruits::lexer::MakeLexer(fruitList.c_str(), fruitList.c_str() + fruitList.length(), "<fruitList>");
    using LexerType = decltype(lexer);
    std::vector<std::unique_ptr<fruits::fruit>> fruitVec;
    fruits::parser::FruitParser<LexerType>::Parse(lexer, &fruitVec);
    return fruitVec;
}

int main()
{
    std::vector<std::unique_ptr<fruits::fruit>> fruitVec = parse_fruit_list("(apple, orange, banana)");
    std::cout << "(";
    bool first = true;
    for (const auto& fruit : fruitVec)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            std::cout << ", ";
        }
        fruit->print();
    }
    std::cout << ")" << "\n";
}
