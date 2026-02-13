// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.optimizer.arithmetics;

import std;
import otava.intermediate;

export namespace otava::optimizer {

bool OptimizeArithmetics(otava::intermediate::Function* fn, otava::intermediate::IntermediateContext* context);

} // otava::optimizer
