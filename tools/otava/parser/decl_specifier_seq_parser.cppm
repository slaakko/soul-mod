// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.decl_specifier_seq.parser;

import std;
import otava.ast;
import otava.symbols.context;

export namespace otava::parser {

std::unique_ptr<otava::ast::Node> ParseDeclarationSpecifierSequence(const std::u32string& declsSpecifierSeqStr, otava::symbols::Context* context);

} // otava::parser
