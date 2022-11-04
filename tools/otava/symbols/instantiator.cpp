// =================================
// Copyright (c) 2022 Seppo Laakko
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
import otava.ast;

namespace otava::symbols {

Instantiator::Instantiator(Context* context_) : context(context_), innerClass(false), index(0)
{
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
        GetClassAttributes(&node, name, kind);
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
    ProcessMemberDeclaration(&node, context);
}

void Instantiator::Visit(otava::ast::SimpleDeclarationNode& node)
{
    ProcessSimpleDeclaration(&node, context);
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
    if (context->GetFlag(ContextFlags::instantiateFunctionTemplate))
    {
        ProcessSimpleDeclaration(&node, context);
    }
    else
    {
        ProcessMemberFunctionDefinition(&node, context);
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

} // namespace otava::symbols
