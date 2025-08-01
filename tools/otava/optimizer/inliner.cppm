// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.optimizer.inliner;

import std;
import otava.intermediate;

export namespace otava::optimizer {

void Inline(otava::intermediate::Function* fn, otava::intermediate::Context* context);

} // otava::optimizer
