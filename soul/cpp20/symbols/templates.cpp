// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.templates;

import soul.cpp20.ast;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.specialization;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.type.resolver;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.instantiator;
import util;

namespace soul::cpp20::symbols {

TypenameConstraintSymbol::TypenameConstraintSymbol() : TypeSymbol(SymbolKind::typenameConstraintSymbol, std::u32string(U"typename"))
{
}

void TypenameConstraintSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TemplateParameterSymbol::TemplateParameterSymbol(const std::u32string& name_) : 
    TypeSymbol(SymbolKind::templateParameterSymbol, name_), 
    constraint(), 
    index(-1), 
    defaultTemplateArgNode(nullptr),
    defaultTemplateArgNodeId(-1)
{
}

TemplateParameterSymbol::TemplateParameterSymbol(Symbol* constraint_, const std::u32string& name_, int index_, soul::cpp20::ast::Node* defaultTemplateArgNode_) :
    TypeSymbol(SymbolKind::templateParameterSymbol, name_), constraint(constraint_), index(index_), defaultTemplateArgNode(defaultTemplateArgNode_), defaultTemplateArgNodeId(-1)
{
}

void TemplateParameterSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(constraint->Id());
    writer.GetBinaryStreamWriter().Write(index);
    bool hasDefaultTemplateArg = defaultTemplateArgNode != nullptr;
    writer.GetBinaryStreamWriter().Write(hasDefaultTemplateArg);
    if (hasDefaultTemplateArg)
    {
        writer.GetBinaryStreamWriter().Write(defaultTemplateArgNode->Id());
    }
}

void TemplateParameterSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(constraintId);
    index = reader.GetBinaryStreamReader().ReadInt();
    bool hasDefaultTemplateArg = reader.GetBinaryStreamReader().ReadBool();
    if (hasDefaultTemplateArg)
    {
        defaultTemplateArgNodeId = reader.GetBinaryStreamReader().ReadInt();
    }
}

void TemplateParameterSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    constraint = symbolTable.GetConstraint(constraintId);
    if (defaultTemplateArgNodeId != -1)
    {
        soul::cpp20::ast::NodeMap* nodeMap = symbolTable.GetNodeMap();
        defaultTemplateArgNode = nodeMap->GetNode(defaultTemplateArgNodeId);
    }
}

void TemplateParameterSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BoundTemplateParameterSymbol::BoundTemplateParameterSymbol(const std::u32string & name_) : 
    TypeSymbol(SymbolKind::boundTemplateParameterSymbol, name_), 
    templateParameterSymbol(nullptr), 
    boundSymbol(nullptr)
{
}

void BoundTemplateParameterSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TemplateDeclarationSymbol::TemplateDeclarationSymbol() : ContainerSymbol(SymbolKind::templateDeclarationSymbol, std::u32string())
{
    GetScope()->SetKind(ScopeKind::templateDeclarationScope);
}

void TemplateDeclarationSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ContainerSymbol::AddSymbol(symbol, sourcePos, context);
    if (symbol->IsTemplateParameterSymbol())
    {
        templateParameters.push_back(static_cast<TemplateParameterSymbol*>(symbol));
    }
}

void TemplateDeclarationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BeginTemplateDeclaration(soul::cpp20::ast::Node* node, Context* context)
{
    context->GetSymbolTable()->BeginTemplateDeclaration(node, context);
    context->PushSetFlag(ContextFlags::parsingTemplateDeclaration);
}

void EndTemplateDeclaration(soul::cpp20::ast::Node* node, Context* context)
{
    Symbol* symbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (!symbol->IsTemplateDeclarationSymbol())
    {
        ThrowException("cpp20.symbols.templates: EndTemplateDeclaration(): template scope expected", node->GetSourcePos(), context);
    }
    context->PopFlags();
    context->GetSymbolTable()->EndTemplateDeclaration();
}

void RemoveTemplateDeclaration(Context* context)
{
    context->GetSymbolTable()->RemoveTemplateDeclaration();
}

class TemplateParameterCreator : public soul::cpp20::ast::DefaultVisitor
{
public:
    TemplateParameterCreator(Context* context_, int index_);
    void Visit(soul::cpp20::ast::TypeParameterNode& node) override;
    void Visit(soul::cpp20::ast::TypenameNode& node) override;
    void Visit(soul::cpp20::ast::ClassNode& node) override;
    void Visit(soul::cpp20::ast::ParameterNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    int index;
    Symbol* constraint;
    bool resolveConstraint;
    bool resolveTemplateParamName;
    std::u32string templateParamName;
};

TemplateParameterCreator::TemplateParameterCreator(Context* context_, int index_) :
    context(context_), index(index_), constraint(nullptr), resolveConstraint(false), resolveTemplateParamName(false)
{
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::TypeParameterNode& node)
{
    resolveConstraint = true;
    node.TypeConstraint()->Accept(*this);
    resolveConstraint = false;
    if (node.Identifier())
    {
        resolveTemplateParamName = true;
        node.Identifier()->Accept(*this);
        resolveTemplateParamName = false;
    }
    soul::cpp20::ast::Node* defaultTemplateArgNode = nullptr;
    if (node.TypeId())
    {
        defaultTemplateArgNode = node.TypeId();
    }
    context->GetSymbolTable()->AddTemplateParameter(templateParamName, &node, constraint, index, defaultTemplateArgNode, context);
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::TypenameNode& node)
{
    constraint = context->GetSymbolTable()->GetTypenameConstraintSymbol();
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::ClassNode& node)
{
    constraint = context->GetSymbolTable()->GetTypenameConstraintSymbol();
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::ParameterNode& node)
{
    // todo
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    if (resolveTemplateParamName)
    {
        templateParamName = node.Str();
    }
}

void AddTemplateParameter(soul::cpp20::ast::Node* templateParameterNode, int index, Context* context)
{
    TemplateParameterCreator creator(context, index);
    templateParameterNode->Accept(creator);
}

bool TemplateArgCanBeTypeId(soul::cpp20::ast::Node* templateIdNode, int index)
{
    return true; // TODO
}

TypeSymbol* Instantiate(TypeSymbol* typeSymbol, const std::vector<TypeSymbol*>& templateArgs, soul::cpp20::ast::TemplateIdNode* node, Context* context)
{
    SpecializationSymbol* specialization = context->GetSymbolTable()->MakeSpecialization(typeSymbol, templateArgs);
    if (specialization->Instantiated()) return specialization;
    soul::cpp20::ast::Node* classNode = context->GetSymbolTable()->GetSpecifierNode(typeSymbol);
    if (!classNode)
    {
        return specialization;
    }
    if (classNode->IsClassSpecifierNode())
    {
        soul::cpp20::ast::ClassSpecifierNode* classSpecifierNode = static_cast<soul::cpp20::ast::ClassSpecifierNode*>(classNode);
        if (!classSpecifierNode->Complete())
        {
            return specialization;
        }
    }
    specialization->SetInstantiated();
    if (typeSymbol->IsClassTypeSymbol())
    {
        ClassTypeSymbol* classTemplate = static_cast<ClassTypeSymbol*>(typeSymbol);
        TemplateDeclarationSymbol* templateDeclaration = classTemplate->ParentTemplateDeclaration();
        if (templateDeclaration)
        {
            int arity = templateDeclaration->Arity();
            int argCount = templateArgs.size();
            if (argCount > arity)
            {
                ThrowException("soul.cpp20.symbols.templates: wrong number of template args for instantiating class template '" + 
                    util::ToUtf8(classTemplate->Name()) + "'", 
                    node->GetSourcePos(), 
                    context);
            }
            specialization->GetScope()->SetParentScope(context->GetSymbolTable()->CurrentScope());
            context->GetSymbolTable()->BeginScope(specialization->GetScope());
            InstantiationScope instantiationScope(specialization->GetScope());
            std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
            for (int i = 0; i < arity; ++i)
            {
                TemplateParameterSymbol* templateParameter = templateDeclaration->TemplateParameters()[i];
                TypeSymbol* templateArg = nullptr;
                if (i >= argCount)
                {
                    soul::cpp20::ast::Node* defaultTemplateArgNode = templateParameter->DefaultTemplateArg();
                    context->GetSymbolTable()->BeginScope(&instantiationScope);
                    templateArg = ResolveType(defaultTemplateArgNode, DeclarationFlags::none, context);
                    context->GetSymbolTable()->EndScope();
                }
                else
                {
                    templateArg = templateArgs[i];
                }
                BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
                boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                boundTemplateParameter->SetBoundSymbol(templateArg);
                boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                instantiationScope.Install(boundTemplateParameter);
            }
            context->GetSymbolTable()->BeginScope(&instantiationScope);
            Instantiator instantiator(context);
            classNode->Accept(instantiator);
            context->GetSymbolTable()->EndScope();
            context->GetSymbolTable()->EndScope();
            specialization->GetScope()->SetParentScope(nullptr);
        }
        else
        {
            ThrowException("soul.cpp20.symbols.templates: template declarator for class template '" + util::ToUtf8(classTemplate->Name()) + " not found", node->GetSourcePos(), context);
        }
    }
    else
    {
        ThrowException("soul.cpp20.symbols.templates: class template expected", node->GetSourcePos(), context);
    }
    return specialization;
}

} // namespace soul::cpp20::symbols
