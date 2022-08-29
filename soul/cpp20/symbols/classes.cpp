// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module soul.cpp20.symbols.classes;

import soul.cpp20.ast;
import soul.cpp20.symbols.class_group.symbol;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.templates;
import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;

namespace soul::cpp20::symbols {

ClassTypeSymbol::ClassTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::classTypeSymbol, name_), classKind(ClassKind::class_)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

bool ClassTypeSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope: 
        case ScopeKind::templateDeclarationScope: 
        case ScopeKind::classScope: 
        case ScopeKind::blockScope: 
        {
            return true;
        }
    }
    return false;
}

void ClassTypeSymbol::AddBaseClass(Symbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context)
{
    baseClasses.push_back(baseClass);
    GetScope()->AddBaseScope(baseClass->GetScope(), sourcePos, context);
}

void ClassTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ClassTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    uint32_t nb = baseClasses.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(nb);
    for (const auto& baseClass : baseClasses)
    {
        writer.GetBinaryStreamWriter().Write(baseClass->Id());
    }
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(classKind));
}

void ClassTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    uint32_t nb = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nb; ++i)
    {
        util::uuid baseClassId;
        reader.GetBinaryStreamReader().ReadUuid(baseClassId);
        baseClassIds.push_back(baseClassId);
    }
    classKind = static_cast<ClassKind>(reader.GetBinaryStreamReader().ReadByte());
}

void ClassTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    for (const util::uuid& baseClassId : baseClassIds)
    {
        Symbol* baseClassSymbol = GetSymbol(baseClassId);
        baseClasses.push_back(baseClassSymbol);
    }
}

TemplateDeclarationSymbol* ClassTypeSymbol::ParentTemplateDeclaration() 
{
    Symbol* parentSymbol = Parent();
    if (parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

int ClassTypeSymbol::Arity() 
{
    TemplateDeclarationSymbol* templateDeclaration = ParentTemplateDeclaration();
    if (templateDeclaration)
    {
        return templateDeclaration->Arity();
    }
    else
    {
        return 0;
    }
}

ForwardClassDeclarationSymbol::ForwardClassDeclarationSymbol(const std::u32string& name_) : 
    TypeSymbol(SymbolKind::forwardClassDeclarationSymbol, name_), 
    classKind(ClassKind::class_),
    classTypeSymbol(nullptr)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

bool ForwardClassDeclarationSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope:
        case ScopeKind::templateDeclarationScope:
        case ScopeKind::classScope:
        case ScopeKind::blockScope:
        {
            return true;
        }
    }
    return false;
}

TemplateDeclarationSymbol* ForwardClassDeclarationSymbol::ParentTemplateDeclaration()
{
    Symbol* parentSymbol = Parent();
    if (parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

void ForwardClassDeclarationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ForwardClassDeclarationSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(classKind));
    writer.GetBinaryStreamWriter().Write(classTypeSymbol != nullptr);
    if (classTypeSymbol)
    {
        writer.GetBinaryStreamWriter().Write(classTypeSymbol->Id());
    }
}

void ForwardClassDeclarationSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    classKind = static_cast<ClassKind>(reader.GetBinaryStreamReader().ReadByte());
    bool hasClassType = reader.GetBinaryStreamReader().ReadBool();
    if (hasClassType)
    {
        reader.GetBinaryStreamReader().ReadUuid(classTypeSymbolId);
    }
}

void ForwardClassDeclarationSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    if (classTypeSymbolId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(classTypeSymbolId);
        if (type->IsClassTypeSymbol())
        {
            classTypeSymbol = static_cast<ClassTypeSymbol*>(type);
        }
        else
        {
            throw std::runtime_error("soul.cpp20.symbols.classes: class type expected");
        }
    }
}

int ForwardClassDeclarationSymbol::Arity()
{
    TemplateDeclarationSymbol* templateDeclaration = ParentTemplateDeclaration();
    if (templateDeclaration)
    {
        return templateDeclaration->Arity();
    }
    else
    {
        return 0;
    }
}

class ClassResolver : public soul::cpp20::ast::DefaultVisitor
{
public:
    ClassResolver();
    std::u32string GetName() const { return name; }
    soul::cpp20::symbols::ClassKind GetClassKind() const { return classKind; }
    void Visit(soul::cpp20::ast::ClassSpecifierNode& node) override;
    void Visit(soul::cpp20::ast::ClassHeadNode& node) override;
    void Visit(soul::cpp20::ast::ElaboratedTypeSpecifierNode& node) override;
    void Visit(soul::cpp20::ast::ClassNode& node) override;
    void Visit(soul::cpp20::ast::StructNode& node) override;
    void Visit(soul::cpp20::ast::UnionNode& node) override;
private:
    std::u32string name;
    soul::cpp20::symbols::ClassKind classKind;
};

ClassResolver::ClassResolver() : classKind(soul::cpp20::symbols::ClassKind::class_)
{
}

void ClassResolver::Visit(soul::cpp20::ast::ClassSpecifierNode& node)
{
    node.ClassHead()->Accept(*this);
}

void ClassResolver::Visit(soul::cpp20::ast::ClassHeadNode& node)
{
    node.ClassKey()->Accept(*this);
    name = node.ClassHeadName()->Str();
}

void ClassResolver::Visit(soul::cpp20::ast::ElaboratedTypeSpecifierNode& node)
{
    node.ClassKey()->Accept(*this);
    name = node.Id()->Str();
}

void ClassResolver::Visit(soul::cpp20::ast::ClassNode& node)
{
    classKind = soul::cpp20::symbols::ClassKind::class_;
}

void ClassResolver::Visit(soul::cpp20::ast::StructNode& node)
{
    classKind = soul::cpp20::symbols::ClassKind::struct_;
}

void ClassResolver::Visit(soul::cpp20::ast::UnionNode& node)
{
    classKind = soul::cpp20::symbols::ClassKind::union_;
}

void GetClassAttributeas(soul::cpp20::ast::Node* node, std::u32string& name, soul::cpp20::symbols::ClassKind& kind)
{
    ClassResolver resolver;
    node->Accept(resolver);
    name = resolver.GetName();
    kind = resolver.GetClassKind();
}

void BeginClass(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context)
{
    std::u32string name;
    soul::cpp20::symbols::ClassKind kind;
    GetClassAttributeas(node, name, kind);
    context->GetSymbolTable()->BeginClass(name, kind, node, context);
    context->PushSetFlag(ContextFlags::parseMemberFunction);
}

void EndClass(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context)
{
    Symbol* classTypeSymbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (!classTypeSymbol->IsClassTypeSymbol())
    {
        ThrowException("cpp20.symbols.classes: EndClass(): class scope expected", node->GetSourcePos(), context);
    }
    soul::cpp20::ast::Node* specNode = context->GetSymbolTable()->GetSpecifierNode(classTypeSymbol);
    if (specNode && specNode->IsClassSpecifierNode())
    {
        soul::cpp20::ast::ClassSpecifierNode* specifierNode = static_cast<soul::cpp20::ast::ClassSpecifierNode*>(specNode);
        specifierNode->SetComplete();
    }
    else
    {
        ThrowException("soul.cpp20.symbols.classes: EndClass(): class specifier node expected", node->GetSourcePos(), context);
    }
    context->PopFlags();
    context->GetSymbolTable()->EndClass();
}

void AddForwardClassDeclaration(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context)
{
    std::u32string name;
    soul::cpp20::symbols::ClassKind kind;
    GetClassAttributeas(node, name, kind);
    context->GetSymbolTable()->AddForwardClassDeclaration(name, kind, node, context);
}

void SetCurrentAccess(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context)
{
    switch (node->Kind())
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

bool ClassLess::operator()(ClassTypeSymbol* left, ClassTypeSymbol* right) const
{
    return left->Name() < right->Name();
}

} // namespace soul::cpp20::symbols
