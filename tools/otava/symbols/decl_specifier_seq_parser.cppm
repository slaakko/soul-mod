// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.decl_specifier_seq.parser;

import std;
import otava.ast;
import otava.symbols.context;

export namespace otava::symbols {

using DeclarationSpecifierSequenceParser = std::unique_ptr<otava::ast::Node>(*)(const std::u32string&, otava::symbols::Context*);

void SetDeclarationSpecifierSequenceParser(DeclarationSpecifierSequenceParser declSpecifierSeqParser_);

std::unique_ptr<otava::ast::Node> ParseDeclarationSpecifierSequence(const std::u32string& declSpecifierSeqStr, otava::symbols::Context* context);

} // namespace otava::symbols
