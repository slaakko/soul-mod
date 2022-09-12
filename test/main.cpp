import std.core;
import util;
import test.lexer;
import test.parser;

int main()
{
    std::string fileContent = "union";
    std::u32string content = util::ToUtf32(fileContent);
    auto lexer = test::lexer::MakeLexer(content.c_str(), content.c_str() + content.length(), "filePath");
    int x = test::parser::TestParser<decltype(lexer)>::Parse(lexer);
}