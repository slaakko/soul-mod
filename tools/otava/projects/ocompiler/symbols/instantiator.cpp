// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.instantiator;

import otava.symbols.alias.type.symbol;
import otava.symbols.classes;
import otava.symbols.declaration;
import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.symbol;
import otava.symbols.templates;
import otava.symbols.using_declaration;
import otava.symbols.using_directive;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.block;
import otava.ast;

namespace otava::symbols {

Instantiator::Instantiator(Context* context_, InstantiationScope* instantiationScope_) :
    context(context_), innerClass(false), index(0), instantiationScope(instantiationScope_),
    functionNode(nullptr), specialization(nullptr)
{
}

void Instantiator::SetFunctionNode(otava::ast::Node* functionNode_)
{
    functionNode = functionNode_;
}

void Instantiator::Visit(otava::ast::ClassSpecifierNode& node)
{
    if (!Valid()) return;
    if (innerClass)
    {
        std::expected<bool, int> rv = BeginClass(&node, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        VisitSequenceContent(node);
        if (!Valid()) return;
        rv = EndClass(&node, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        std::u32string name;
        ClassKind kind;
        TypeSymbol* specialization = nullptr;
        std::expected<bool, int> rv = GetClassAttributes(&node, name, kind, specialization, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        std::expected<std::vector<ClassTypeSymbol*>, int> brv = ResolveBaseClasses(&node, context);
        if (!brv)
        {
            SetError(brv.error());
            return;
        }
        baseClasses = *brv;
        switch (kind)
        {
            case ClassKind::class_:
            {
                context->GetSymbolTable()->PushAccess(Access::private_);
                break;
            }
            case ClassKind::struct_:
            case ClassKind::union_:
            {
                context->GetSymbolTable()->PushAccess(Access::public_);
                break;
            }
        }
        innerClass = true;
        VisitSequenceContent(node);
        if (!Valid()) return;
        innerClass = false;
        context->GetSymbolTable()->PopAccess();
    }
}

void Instantiator::Visit(otava::ast::BeginAccessGroupNode& node)
{
    switch (node.Child()->Kind())
    {
        case otava::ast::NodeKind::publicNode:
        {
            context->GetSymbolTable()->SetCurrentAccess(Access::public_);
            break;
        }
        case otava::ast::NodeKind::protectedNode:
        {
            context->GetSymbolTable()->SetCurrentAccess(Access::protected_);
            break;
        }
        case otava::ast::NodeKind::privateNode:
        {
            context->GetSymbolTable()->SetCurrentAccess(Access::private_);
            break;
        }
    }
}

void Instantiator::Visit(otava::ast::AliasDeclarationNode& node)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = ProcessAliasDeclaration(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void Instantiator::Visit(otava::ast::MemberDeclarationNode& node)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = ProcessMemberDeclaration(&node, functionNode, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    if (functionNode)
    {
        specialization = context->GetSpecialization(functionNode);
    }
}

void Instantiator::Visit(otava::ast::SimpleDeclarationNode& node)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = ProcessSimpleDeclaration(&node, functionNode, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    if (functionNode)
    {
        specialization = context->GetSpecialization(functionNode);
    }
}

void Instantiator::Visit(otava::ast::UsingDeclarationNode& node)
{
    if (!Valid()) return;
    AddUsingDeclaration(&node, context);
}

void Instantiator::Visit(otava::ast::UsingDirectiveNode& node)
{
    if (!Valid()) return;
    AddUsingDirective(&node, context);
}

void Instantiator::Visit(otava::ast::FunctionDefinitionNode& node)
{
    if (!Valid()) return;
    if (context->GetFlag(ContextFlags::skipFunctionDefinitions)) return;
    bool get = false;
    std::expected<int, int> rv = BeginFunctionDefinition(node.DeclSpecifiers(), node.Declarator(), functionNode, node.Specifiers(), get, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    int scopes = *rv;
    if (context->GetFlag(ContextFlags::instantiateFunctionTemplate) ||
        context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate) ||
        context->GetFlag(ContextFlags::instantiateInlineFunction))
    {
        if (functionNode)
        {
            specialization = context->GetSpecialization(functionNode);
            if (specialization)
            {
                std::expected<bool, int> prv = instantiationScope->PushParentScope(specialization->GetScope());
                if (!prv)
                {
                    SetError(prv.error());
                    return;
                }
            }
        }
    }
    if (!get)
    {
        node.FunctionBody()->Accept(*this);
        if (!Valid()) return;
        std::expected<bool, int> rv = otava::symbols::EndFunctionDefinition(&node, scopes, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void Instantiator::Visit(otava::ast::NoDeclSpecFunctionDeclarationNode& node)
{
    if (!Valid()) return;
    std::expected<Declaration, int> rv = ProcessFunctionDeclaration(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void Instantiator::Visit(otava::ast::TemplateDeclarationNode& node)
{
    // member templates not supported (they are skipped)
}

void Instantiator::Visit(otava::ast::CompoundStatementNode& node)
{
    if (!Valid()) return;
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    VisitSequence(node);
    if (!Valid()) return;
    EndBlock(context);
}

void Instantiator::Visit(otava::ast::IfStatementNode& node)
{
    if (!Valid()) return;
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
        if (!Valid()) return;
    }
    node.ThenStatement()->Accept(*this);
    if (!Valid()) return;
    if (node.ElseStatement())
    {
        node.ElseStatement()->Accept(*this);
        if (!Valid()) return;
    }
    EndBlock(context);
}

void Instantiator::Visit(otava::ast::SwitchStatementNode& node)
{
    if (!Valid()) return;
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
        if (!Valid()) return;
    }
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndBlock(context);
}

void Instantiator::Visit(otava::ast::WhileStatementNode& node)
{
    if (!Valid()) return;
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndBlock(context);
}

void Instantiator::Visit(otava::ast::DoStatementNode& node)
{
    if (!Valid()) return;
    node.Statement()->Accept(*this);
}

void Instantiator::Visit(otava::ast::ForStatementNode& node)
{
    if (!Valid()) return;
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
        if (!Valid()) return;
    }
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndBlock(context);
}

void Instantiator::Visit(otava::ast::ExpressionStatementNode& node)
{
}

void Instantiator::Visit(otava::ast::ReturnStatementNode& node)
{
}

void Instantiator::Visit(otava::ast::ExceptionDeclarationNode& node)
{
    if (!Valid()) return;
    std::expected<Declaration, int> rv = ProcessExceptionDeclaration(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

} // namespace otava::symbols
