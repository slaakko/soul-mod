// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.parser;

import otava.intermediate.lexer;
import otava.intermediate.context;
import otava.intermediate.spg.rules;
import otava.intermediate.code.parser;
import util;

namespace otava::intermediate {

void ParseIntermediateCodeFile(const std::string& filePath, Context& context)
{
    std::string codeFileContent = util::ReadFile(filePath);
    std::u32string content = util::ToUtf32(codeFileContent);
    auto lexer = otava::intermediate::lexer::MakeLexer(content.c_str(), content.c_str() + content.length(), filePath);
    lexer.SetRuleNameMapPtr(otava::intermediate::spg::rules::GetRuleNameMapPtr());
    int32_t fileId = context.GetFileMap().MapFile(filePath);
    lexer.SetFile(fileId);
    using LexerType = decltype(lexer);
    otava::intermediate::code::parser::IntermediateCodeParser<LexerType>::Parse(lexer, &context);
    context.GetFileMap().AddFileContent(fileId, std::move(content), std::move(lexer.GetLineStartIndeces()));
}

} // namespace otava::intermediate
