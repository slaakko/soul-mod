// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.optimizer.dead_code_elimination;

import std;
import otava.intermediate;

export namespace otava::optimizer {

void DeadCodeElimination(otava::intermediate::Function* fn);

} // otava::optimizer