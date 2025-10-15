// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.main.parser;

import otava.intermediate.lexer;
import otava.intermediate.parser.rules;
import otava.intermediate.parser;
import util;

namespace otava::intermediate {

std::expected<bool, int> Parse(const std::string& filePath, Context& context, bool verbose)
{
    if (verbose)
    {
        std::cout << "> " << filePath << "\n";
    }
    int fileIndex = context.GetFileMap().MapFile(filePath);
    context.SetFileId(fileIndex);
    std::expected<std::string, int> frv = util::ReadFile(filePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string fileContent = std::move(*frv);
    std::expected<std::u32string, int> crv = util::ToUtf32(fileContent);
    if (!crv) return std::unexpected<int>(crv.error());
    std::u32string content = std::move(*crv);
    auto lexerRv = otava::intermediate::lexer::MakeLexer(content.c_str(), content.c_str() + content.length(), filePath);
    if (!lexerRv) return std::unexpected<int>(lexerRv.error());
    auto& lexer = std::move(*lexerRv);
    lexer.SetFile(fileIndex);
    using LexerType = decltype(lexer);
    lexer.SetRuleNameMapPtr(otava::intermediate::parser::rules::GetRuleNameMapPtr());
    std::expected<bool, int> rv = otava::intermediate::parser::IntermediateParser<LexerType>::Parse(lexer, &context);
    if (!rv) return rv;
    context.GetTypes().ResolveComments();
    context.GetFileMap().AddFileContent(fileIndex, std::move(content), lexer.GetLineStartIndeces());
    return std::expected<bool, int>(true);
}

} // otava::intermediate
