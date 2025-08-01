// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.optimizer.optimizing_code_generator;

namespace otava::optimizer {

OptimizingCodeGenerator::OptimizingCodeGenerator(otava::intermediate::Context* context_, const std::string& assemblyFilePath_) : 
    otava::intermediate::CodeGenerator(context_, assemblyFilePath_)
{
}

} // otava::optimizer
