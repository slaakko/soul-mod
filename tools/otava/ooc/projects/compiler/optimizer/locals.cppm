// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.optimizer.locals;

import std;
import otava.intermediate;

export namespace otava::optimizer {

void MoveLocalsToEntryBlock(otava::intermediate::Function* fn);

} // namespace otava::optimizer
