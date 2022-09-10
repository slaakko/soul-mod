module soul.cpp20.lexer.line_tokenizer;

import soul.cpp20.token.line.lexer;
import util.unicode;

namespace soul::cpp20::lexer {

std::vector<Token> TokenizeLine(const std::string& line, std::u32string& lineContent)
{
    lineContent = util::ToUtf32(line);
    lineContent.append(1, '\n');
    std::vector<Token> tokens;
    auto lexer = soul::cpp20::token::line::lexer::MakeLexer(lineContent.c_str(), lineContent.c_str() + lineContent.length(), "");
    ++lexer;
    while (*lexer != soul::lexer::END_TOKEN)
    {
        tokens.push_back(lexer.CurrentToken());
        ++lexer;
    }
    return tokens;
}

} // namespace soul::cpp20::lexer
