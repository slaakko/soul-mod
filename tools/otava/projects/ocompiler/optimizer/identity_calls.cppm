// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.optimizer.identity_calls;

import std;
import otava.intermediate;

export namespace otava::optimizer {

std::expected<bool, int> OptimizeIdentityCalls(otava::intermediate::Function* fn, otava::intermediate::Context* context);

} // otava::optimizer
