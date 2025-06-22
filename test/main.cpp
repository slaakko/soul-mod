import std;
import util;
import test.lexer;
import test.parser;

int main()
{
    std::string fileContent = "union";
    std::u32string content = util::ToUtf32(fileContent);
    auto lexer = test::lexer::MakeLexer(content.c_str(), content.c_str() + content.length(), "filePath");
    using LexerType = decltype(lexer);
    int x = test::parser::TestParser<LexerType>::Parse(lexer);
}