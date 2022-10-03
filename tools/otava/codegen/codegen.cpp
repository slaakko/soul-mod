// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.codegen;

import otava.symbols.emitter;
import otava.symbols.function.symbol;
import otava.intermediate.code;
import otava.intermediate.compile.unit;
import otava.intermediate.context;
import otava.intermediate.metadata;
import otava.intermediate.parser;
import otava.intermediate.register_allocator;
import otava.intermediate.verify;
import otava.intermediate.code.generator;
import otava.symbols.bound.tree;
import std.core;
import std.filesystem;
import util;

namespace otava::codegen {

class CodeGenerator : public otava::symbols::DefaultBoundTreeVisitor
{
public:
    CodeGenerator(otava::symbols::Context& context_, bool verbose_);
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
    bool verbose;
    otava::symbols::Emitter emitter;
};

CodeGenerator::CodeGenerator(otava::symbols::Context& context_, bool verbose_) : context(context_), verbose(verbose_)
{
    std::string config = "debug";
    std::string intermediateCodeFilePath = util::GetFullPath(
        util::Path::Combine(
            util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
            util::Path::GetFileName(context.FileName()) + ".i"));
    emitter.SetFilePath(intermediateCodeFilePath);
    std::filesystem::create_directories(util::Path::GetDirectoryName(intermediateCodeFilePath));
}

void CodeGenerator::Visit(otava::symbols::BoundCompileUnitNode& node)
{
    emitter.SetCompileUnitInfo(node.Id(), context.FileName());
    int n = node.BoundNodes().size();
    for (int i = 0; i < n; ++i)
    {
        otava::symbols::BoundNode* boundNode = node.BoundNodes()[i].get();
        boundNode->Accept(*this);
    }
    emitter.Emit();
    otava::intermediate::Context intermediateContext;
    otava::intermediate::ParseIntermediateCodeFile(emitter.FilePath(), intermediateContext);
    otava::intermediate::Verify(intermediateContext);
    otava::intermediate::GenerateCode(intermediateContext, verbose);
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionNode& node)
{
    otava::symbols::FunctionDefinitionSymbol* functionDefinition = node.GetFunctionDefinitionSymbol();
    otava::intermediate::Type* functionType = functionDefinition->IrType(emitter, node.GetSourcePos(), &context);
    bool once = false;
    emitter.CreateFunction(functionDefinition->IrName(), functionType, once);
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

void GenerateCode(otava::symbols::Context& context, bool verbose)
{
    CodeGenerator codeGenerator(context, verbose);
    context.GetBoundCompileUnit()->Accept(codeGenerator);
}

} // namespace otava::ast
