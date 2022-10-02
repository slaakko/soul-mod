// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.codegen.codegen;

import otava.symbols.emitter;
import otava.symbols.bound.tree;
import std.core;
import std.filesystem;
import util;

namespace otava::codegen {

class CodeGenerator : public otava::symbols::DefaultBoundTreeVisitor
{
public:
    CodeGenerator(otava::symbols::Context& context_);
    void Visit(otava::symbols::BoundCompileUnitNode& node) override;
    void Visit(otava::symbols::BoundFunctionNode& node) override;
    void Visit(otava::symbols::BoundCompoundStatementNode& node) override;
    void Visit(otava::symbols::BoundIfStatementNode& node) override;
    void Visit(otava::symbols::BoundSwitchStatementNode& node) override;
    void Visit(otava::symbols::BoundCaseStatementNode& node) override;
    void Visit(otava::symbols::BoundDefaultStatementNode& node) override;
    void Visit(otava::symbols::BoundWhileStatementNode& node) override;
    void Visit(otava::symbols::BoundDoStatementNode& node) override;
    void Visit(otava::symbols::BoundForStatementNode& node) override;
    void Visit(otava::symbols::BoundReturnStatementNode& node) override;
    void Visit(otava::symbols::BoundConstructionStatementNode& node) override;
    void Visit(otava::symbols::BoundExpressionStatementNode& node) override;
    void Visit(otava::symbols::BoundMemberExprNode& node) override;
private:
    otava::symbols::Context& context;
    otava::symbols::Emitter emitter;
};

CodeGenerator::CodeGenerator(otava::symbols::Context& context_) : context(context_)
{
    std::string config = "debug";
    std::string intermediateCodeFilePath = util::GetFullPath(
        util::Path::Combine(
            util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
            util::Path::GetFileNameWithoutExtension(context.FileName()) + ".i"));
    emitter.SetFilePath(context.FileName());
    std::filesystem::create_directories(util::Path::GetDirectoryName(intermediateCodeFilePath));
}

void CodeGenerator::Visit(otava::symbols::BoundCompileUnitNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundFunctionNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundCompoundStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundIfStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundSwitchStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundCaseStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundDefaultStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundWhileStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundDoStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundForStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundReturnStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundConstructionStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundExpressionStatementNode& node)
{

}

void CodeGenerator::Visit(otava::symbols::BoundMemberExprNode& node)
{

}

void GenerateCode(otava::symbols::Context& context)
{
    CodeGenerator codeGenerator(context);
    context.GetBoundCompileUnit()->Accept(codeGenerator);
}

} // namespace otava::ast
