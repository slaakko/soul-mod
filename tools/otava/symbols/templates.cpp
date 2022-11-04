// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module otava.symbols.templates;

import otava.ast;
import otava.symbols.classes;
import otava.symbols.context;
import otava.symbols.declaration;
import otava.symbols.declarator;
import otava.symbols.evaluator;
import otava.symbols.exception;
import otava.symbols.modules;
import otava.symbols.specialization;
import otava.symbols.symbol.table;
import otava.symbols.type.resolver;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.value;
import otava.symbols.visitor;
import otava.symbols.instantiator;
import otava.symbols.function.symbol;
import util;

namespace otava::symbols {

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
    defaultTemplateArgNodeId(-1),
    parameterSymbol(nullptr)
{
}

TemplateParameterSymbol::TemplateParameterSymbol(Symbol* constraint_, const std::u32string& name_, int index_, otava::ast::Node* defaultTemplateArgNode_) :
    TypeSymbol(SymbolKind::templateParameterSymbol, name_), 
    constraint(constraint_),
    index(index_), 
    defaultTemplateArgNode(defaultTemplateArgNode_), 
    defaultTemplateArgNodeId(-1),
    parameterSymbol(nullptr)
{
}

void TemplateParameterSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol::AddSymbol(symbol, sourcePos, context);
    if (symbol->IsParameterSymbol())
    {
        parameterSymbol = static_cast<ParameterSymbol*>(symbol);
    }
}

void TemplateParameterSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    util::uuid constraintId = util::nil_uuid();
    if (constraint)
    {
        constraintId = constraint->Id();
    }
    writer.GetBinaryStreamWriter().Write(constraintId);
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
        defaultTemplateArgNodeId = reader.GetBinaryStreamReader().ReadLong();
    }
}

void TemplateParameterSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    if (constraintId != util::nil_uuid())
    {
        constraint = symbolTable.GetConstraint(constraintId);
    }
    if (defaultTemplateArgNodeId != -1)
    {
        otava::ast::NodeMap* nodeMap = symbolTable.GetNodeMap();
        defaultTemplateArgNode = nodeMap->GetNode(defaultTemplateArgNodeId);
    }
}

void TemplateParameterSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeSymbol* TemplateParameterSymbol::Unify(TypeSymbol* argType, Context* context)
{
    return argType;
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

void TemplateDeclarationSymbol::Write(Writer& writer)
{
    ContainerSymbol::Write(writer);
}

void TemplateDeclarationSymbol::Read(Reader& reader)
{
    ContainerSymbol::Read(reader);
}

void TemplateDeclarationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BeginTemplateDeclaration(otava::ast::Node* node, Context* context)
{
    context->GetSymbolTable()->BeginTemplateDeclaration(node, context);
    context->PushSetFlag(ContextFlags::parsingTemplateDeclaration);
}

void EndTemplateDeclaration(otava::ast::Node* node, Context* context)
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

class TemplateParameterCreator : public otava::ast::DefaultVisitor
{
public:
    TemplateParameterCreator(Context* context_, int index_);
    void Visit(otava::ast::TypeParameterNode& node) override;
    void Visit(otava::ast::TypenameNode& node) override;
    void Visit(otava::ast::ClassNode& node) override;
    void Visit(otava::ast::ParameterNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
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

void TemplateParameterCreator::Visit(otava::ast::TypeParameterNode& node)
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
    otava::ast::Node* defaultTemplateArgNode = nullptr;
    if (node.TypeId())
    {
        defaultTemplateArgNode = node.TypeId();
    }
    context->GetSymbolTable()->AddTemplateParameter(templateParamName, &node, constraint, index, nullptr, defaultTemplateArgNode, context);
}

void TemplateParameterCreator::Visit(otava::ast::TypenameNode& node)
{
    constraint = context->GetSymbolTable()->GetTypenameConstraintSymbol();
}

void TemplateParameterCreator::Visit(otava::ast::ClassNode& node)
{
    constraint = context->GetSymbolTable()->GetTypenameConstraintSymbol();
}

void TemplateParameterCreator::Visit(otava::ast::ParameterNode& node)
{
    Declaration declaration = ProcessParameterDeclaration(&node, context);
    TypeSymbol* type = declaration.type;
    if (declaration.declarator->Kind() == DeclaratorKind::simpleDeclarator)
    {
        SimpleDeclarator* declarator = static_cast<SimpleDeclarator*>(declaration.declarator.get());
        std::u32string templateParamName = declarator->Name();
        Value* value = nullptr;
        if (node.Initializer())
        {
            value = Evaluate(node.Initializer(), context);
        }
        ParameterSymbol* parameter = new ParameterSymbol(templateParamName, type);
        parameter->SetDefaultValue(value);
        context->GetSymbolTable()->AddTemplateParameter(templateParamName, &node, nullptr, index, parameter, nullptr, context);
    }
    else 
    {
        ThrowException("simple declarator expected", node.GetSourcePos(), context);
    }
}

void TemplateParameterCreator::Visit(otava::ast::IdentifierNode& node)
{
    if (resolveTemplateParamName)
    {
        templateParamName = node.Str();
    }
}

void AddTemplateParameter(otava::ast::Node* templateParameterNode, int index, Context* context)
{
    TemplateParameterCreator creator(context, index);
    templateParameterNode->Accept(creator);
}

bool TemplateArgCanBeTypeId(otava::ast::Node* templateIdNode, int index)
{
    return true; // TODO
}

TypeSymbol* Instantiate(TypeSymbol* typeSymbol, const std::vector<Symbol*>& templateArgs, otava::ast::TemplateIdNode* node, Context* context)
{
    SpecializationSymbol* specialization = context->GetSymbolTable()->MakeSpecialization(typeSymbol, templateArgs);
    if (specialization->Instantiated()) return specialization;
    otava::ast::Node* classNode = context->GetSymbolTable()->GetSpecifierNode(typeSymbol);
    if (!classNode)
    {
        return specialization;
    }
    if (classNode->IsClassSpecifierNode())
    {
        otava::ast::ClassSpecifierNode* classSpecifierNode = static_cast<otava::ast::ClassSpecifierNode*>(classNode);
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
                ThrowException("otava.symbols.templates: wrong number of template args for instantiating class template '" + 
                    util::ToUtf8(classTemplate->Name()) + "'", 
                    node->GetSourcePos(), 
                    context);
            }
            specialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope());
            context->GetSymbolTable()->BeginScope(specialization->GetScope());
            InstantiationScope instantiationScope(specialization->GetScope());
            std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
            for (int i = 0; i < arity; ++i)
            {
                TemplateParameterSymbol* templateParameter = templateDeclaration->TemplateParameters()[i];
                Symbol* templateArg = nullptr;
                if (i >= argCount)
                {
                    otava::ast::Node* defaultTemplateArgNode = templateParameter->DefaultTemplateArg();
                    if (defaultTemplateArgNode)
                    {
                        context->GetSymbolTable()->BeginScope(&instantiationScope);
                        templateArg = ResolveType(defaultTemplateArgNode, DeclarationFlags::none, context);
                        context->GetSymbolTable()->EndScope();
                    }
                    else
                    {
                        ThrowException("otava.symbols.templates: template parameter " + std::to_string(i) + " has no default type argument", node->GetSourcePos(), context);
                    }
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
            try
            {
                classNode->Accept(instantiator);
            }
            catch (const std::exception& ex)
            {
                ThrowException("otava.symbols.templates: error instantiating specialization '" + 
                    util::ToUtf8(specialization->FullName()) + "': " + std::string(ex.what()), node->GetSourcePos(), context);
            }
            context->GetSymbolTable()->EndScope();
            context->GetSymbolTable()->EndScope();
            specialization->GetScope()->ClearParentScopes();
        }
        else
        {
            ThrowException("otava.symbols.templates: template declarator for class template '" + util::ToUtf8(classTemplate->Name()) + " not found", node->GetSourcePos(), context);
        }
    }
    else
    {
        ThrowException("otava.symbols.templates: class template expected", node->GetSourcePos(), context);
    }
    return specialization;
}

} // namespace otava::symbols
