// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.decl_specifier_seq.parser;

import otava.lexer;
import otava.parser.declaration;
import otava.symbols;

namespace otava::parser {

std::unique_ptr<otava::ast::Node> ParseDeclarationSpecifierSequence(const std::u32string& declsSpecifierSeqStr, otava::symbols::Context* context)
{
    auto lexer = otava::lexer::MakeLexer(
        declsSpecifierSeqStr.c_str(), declsSpecifierSeqStr.c_str() + declsSpecifierSeqStr.length(), "<declSpecifierSeq>");
    using LexerType = decltype(lexer);
    otava::symbols::Lexer* prevLexer = context->GetLexer();
    context->SetLexer(&lexer);
    std::unique_ptr<otava::ast::Node> node = otava::parser::declaration::DeclarationParser<LexerType>::Parse(lexer, context);
    context->SetLexer(prevLexer);
    return node;
}

} // otava::parser
