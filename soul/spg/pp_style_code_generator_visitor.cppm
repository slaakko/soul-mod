// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.pp.style.code.generator.visitor;

import soul.spg.code.generator.visitor;
import soul.common.module_map;

export namespace soul::spg {

class PPStyleCodeGeneratorVisitor : public CodeGeneratorVisitor
{
public:
    PPStyleCodeGeneratorVisitor(soul::ast::spg::SpgFile* spgFile_, bool verbose_, bool noDebugSupport_, const std::string& version_, soul::lexer::FileMap& fileMap_, 
        soul::common::ModuleMap& moduleMap_);
    void Visit(soul::ast::spg::ParserFile& parserFile) override;
private:
    soul::common::ModuleMap& moduleMap;
};

} // namespace soul::spg
