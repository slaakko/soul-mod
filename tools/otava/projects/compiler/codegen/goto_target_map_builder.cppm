// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.codegen.goto_target_map_builder;

import std;
import otava.symbols.bound.tree;
import otava.symbols.context;
import otava.intermediate.code;

export namespace otava::codegen {

void BuildGotoTargetMap(otava::symbols::BoundCompoundStatementNode* functionBody, otava::symbols::Context* context);

} // namespace otava::codegen
