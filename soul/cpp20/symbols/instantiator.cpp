// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.instantiator;

import soul.cpp20.symbols.alias.type.symbol;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.declaration;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.templates;
import soul.cpp20.symbols.using_declaration;
import soul.cpp20.symbols.using_directive;
import soul.cpp20.ast;

namespace soul::cpp20::symbols {

Instantiator::Instantiator(Context* context_) : context(context_), innerClass(false), index(0)
{
}

void Instantiator::Visit(soul::cpp20::ast::ClassSpecifierNode& node)
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

void Instantiator::Visit(soul::cpp20::ast::BeginAccessGroupNode& node)
{
    switch (node.Child()->Kind())
    {
        case soul::cpp20::ast::NodeKind::publicNode:
        {
            context->GetSymbolTable()->SetCurrentAccess(Access::public_);
            break;
        }
        case soul::cpp20::ast::NodeKind::protectedNode:
        {
            context->GetSymbolTable()->SetCurrentAccess(Access::protected_);
            break;
        }
        case soul::cpp20::ast::NodeKind::privateNode:
        {
            context->GetSymbolTable()->SetCurrentAccess(Access::private_);
            break;
        }
    }
}

void Instantiator::Visit(soul::cpp20::ast::AliasDeclarationNode& node)
{
    ProcessAliasDeclaration(&node, context);
}

void Instantiator::Visit(soul::cpp20::ast::MemberDeclarationNode& node)
{
    ProcessMemberDeclaration(&node, context);
}

void Instantiator::Visit(soul::cpp20::ast::SimpleDeclarationNode& node)
{
    ProcessSimpleDeclaration(&node, context);
}

void Instantiator::Visit(soul::cpp20::ast::UsingDeclarationNode& node)
{
    AddUsingDeclaration(&node, context);
}

void Instantiator::Visit(soul::cpp20::ast::UsingDirectiveNode& node)
{
    AddUsingDirective(&node, context);
}

void Instantiator::Visit(soul::cpp20::ast::FunctionDefinitionNode& node)
{
    ProcessMemberFunctionDefinition(&node, context);
}

void Instantiator::Visit(soul::cpp20::ast::NoDeclSpecFunctionDeclarationNode& node)
{
    ProcessFunctionDeclaration(&node, context);
}

void Instantiator::Visit(soul::cpp20::ast::TemplateDeclarationNode& node)
{
    // member templates not supported (they are skipped)
}

} // namespace soul::cpp20::symbols
