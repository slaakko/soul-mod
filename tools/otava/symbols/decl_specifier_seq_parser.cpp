// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.decl_specifier_seq.parser;

namespace otava::symbols {

DeclarationSpecifierSequenceParser declSpecifierSeqParser;

void SetDeclarationSpecifierSequenceParser(DeclarationSpecifierSequenceParser declSpecifierSeqParser_)
{
    declSpecifierSeqParser = declSpecifierSeqParser_;
}

std::unique_ptr<otava::ast::Node> ParseDeclarationSpecifierSequence(const std::u32string& declSpecifierSeqStr, otava::symbols::Context* context)
{
    return declSpecifierSeqParser(declSpecifierSeqStr, context);
}

} // namespace otava::symbols
