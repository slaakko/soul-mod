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
    if (innerClass)
    {
        BeginClass(&node, context);
        VisitSequenceContent(node);
        EndClass(&node, context);
    }
    else
    {
        std::u32string name;
        ClassKind kind;
        TypeSymbol* specialization = nullptr;
        GetClassAttributes(&node, name, kind, specialization, context);
        baseClasses = ResolveBaseClasses(&node, context);
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
    ProcessAliasDeclaration(&node, context);
}

void Instantiator::Visit(otava::ast::MemberDeclarationNode& node)
{
    ProcessMemberDeclaration(&node, functionNode, context);
    if (functionNode)
    {
        specialization = context->GetSpecialization(functionNode);
    }
}

void Instantiator::Visit(otava::ast::SimpleDeclarationNode& node)
{
    ProcessSimpleDeclaration(&node, functionNode, context);
    if (functionNode)
    {
        specialization = context->GetSpecialization(functionNode);
    }
}

void Instantiator::Visit(otava::ast::UsingDeclarationNode& node)
{
    AddUsingDeclaration(&node, context);
}

void Instantiator::Visit(otava::ast::UsingDirectiveNode& node)
{
    AddUsingDirective(&node, context);
}

void Instantiator::Visit(otava::ast::FunctionDefinitionNode& node)
{
    if (context->GetFlag(ContextFlags::skipFunctionDefinitions)) return;
    bool get = false;
    int scopes = BeginFunctionDefinition(node.DeclSpecifiers(), node.Declarator(), functionNode, node.Specifiers(), get, context);
    if (context->GetFlag(ContextFlags::instantiateFunctionTemplate) || 
        context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate) ||
        context->GetFlag(ContextFlags::instantiateInlineFunction))
    {
        if (functionNode)
        {
            specialization = context->GetSpecialization(functionNode);
            if (specialization)
            {
                instantiationScope->PushParentScope(specialization->GetScope());
            }
        }
    }
    if (!get)
    {
        node.FunctionBody()->Accept(*this);
        otava::symbols::EndFunctionDefinition(&node, scopes, context);
    }
}

void Instantiator::Visit(otava::ast::NoDeclSpecFunctionDeclarationNode& node)
{
    ProcessFunctionDeclaration(&node, context);
}

void Instantiator::Visit(otava::ast::TemplateDeclarationNode& node)
{
    // member templates not supported (they are skipped)
}

void Instantiator::Visit(otava::ast::CompoundStatementNode& node)
{
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    VisitSequence(node);
    EndBlock(context);
}

void Instantiator::Visit(otava::ast::IfStatementNode& node)
{
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    node.ThenStatement()->Accept(*this);
    if (node.ElseStatement())
    {
        node.ElseStatement()->Accept(*this);
    }
    EndBlock(context);
}

void Instantiator::Visit(otava::ast::SwitchStatementNode& node)
{
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    node.Statement()->Accept(*this);
    EndBlock(context);
}

void Instantiator::Visit(otava::ast::WhileStatementNode& node)
{
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    node.Statement()->Accept(*this);
    EndBlock(context);
}

void Instantiator::Visit(otava::ast::DoStatementNode& node)
{
    node.Statement()->Accept(*this);
}

void Instantiator::Visit(otava::ast::ForStatementNode& node)
{
    BlockSymbol* block = BeginBlock(node.GetSourcePos(), context);
    context->GetSymbolTable()->MapNode(&node, block);
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    node.Statement()->Accept(*this);
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
    ProcessExceptionDeclaration(&node, context);
}

} // namespace otava::symbols
