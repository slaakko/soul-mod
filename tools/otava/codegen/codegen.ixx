// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.codegen;

import otava.symbols.context;

export namespace otava::codegen {

void GenerateCode(otava::symbols::Context& context, bool verbose);

} // namespace otava::ast
