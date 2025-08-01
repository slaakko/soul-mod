// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.optimizer.optimizing_code_generator;

import std;
import otava.intermediate;
import otava.assembly;

export namespace otava::optimizer {

class OptimizingCodeGenerator : public otava::intermediate::CodeGenerator
{
public:
    OptimizingCodeGenerator(otava::intermediate::Context* context_, const std::string& assemblyFilePath_);
};

} // otava::optimizer
