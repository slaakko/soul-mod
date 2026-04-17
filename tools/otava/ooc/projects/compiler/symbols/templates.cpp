// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.templates;

import otava.ast;
import otava.symbols.context;
import otava.symbols.declaration;
import otava.symbols.declarator;
import otava.symbols.evaluator;
import otava.symbols.exception;
import otava.symbols.symbol.table;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.value;
import otava.symbols.visitor;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.class_templates;
import otava.symbols.modules;
import util;

namespace otava::symbols {

util::uuid MakeTemplateParameterId(const util::uuid& id, const std::u32string& name) noexcept
{
    util::uuid x = id;
    util::Xor(x, util::ToUuid(name));
    return x;
}

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

TemplateParameterSymbol::TemplateParameterSymbol(Symbol* constraint_, const std::u32string& name_, const util::uuid& id_, int index_,
    otava::ast::Node* defaultTemplateArgNode_) :
    TypeSymbol(SymbolKind::templateParameterSymbol, MakeTemplateParameterId(id_, name_), name_),
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
        writer.GetBinaryStreamWriter().Write(defaultTemplateArgNode->InternalId());
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

void TemplateParameterSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol::Resolve(symbolTable, context);
    symbolTable.MapType(this);
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

TypeSymbol* TemplateParameterSymbol::UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    auto it = templateParameterMap.find(this);
    if (it != templateParameterMap.cend())
    {
        TypeSymbol* templateArgumentType = it->second;
        return templateArgumentType;
    }
    else
    {
        return nullptr;
    }
}

bool TemplateParameterSymbol::IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const
{
    const Symbol* thisSymbol = this;
    if (visited.find(thisSymbol) == visited.end())
    {
        visited.insert(thisSymbol);
    }
    return true;
}

BoundTemplateParameterSymbol::BoundTemplateParameterSymbol(const std::u32string& name_) :
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
        ThrowException("otava.symbols.templates: EndTemplateDeclaration(): template scope expected", node->GetSourcePos(), context);
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
        parameter->SetDefaultValue(node.Initializer());
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

ExplicitInstantiationSymbol::ExplicitInstantiationSymbol() :
    Symbol(SymbolKind::explicitInstantiationSymbol, U"@explicit_instantiation"), specialization(nullptr), destructor(nullptr)
{
}

ExplicitInstantiationSymbol::ExplicitInstantiationSymbol(ClassTemplateSpecializationSymbol* specialization_) :
    Symbol(SymbolKind::explicitInstantiationSymbol, U"@explicit_instantiation"), specialization(specialization_), destructor(nullptr)
{
}

ExplicitInstantiationSymbol::~ExplicitInstantiationSymbol()
{
    for (ExplicitlyInstantiatedFunctionDefinitionSymbol* functionDefinitionSymbol : functionDefinitionSymbols)
    {
        delete functionDefinitionSymbol;
    }
}

void ExplicitInstantiationSymbol::AddFunctionDefinitionSymbol(FunctionDefinitionSymbol* functionDefinitionSymbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    functionDefinitionSymbol->SetFlag(FunctionSymbolFlags::fixedIrName);
    if (functionDefinitionSymbol->Declaration())
    {
        FunctionSymbol* declaration = functionDefinitionSymbol->Declaration();
        declaration->SetFlag(FunctionSymbolFlags::fixedIrName);
    }
    ExplicitlyInstantiatedFunctionDefinitionSymbol* explicitlyInstantiatedSymbol = new ExplicitlyInstantiatedFunctionDefinitionSymbol(
        functionDefinitionSymbol, sourcePos, context);
    explicitlyInstantiatedSymbol->SetFunctionKind(functionDefinitionSymbol->GetFunctionKind());
    functionDefinitionSymbols.push_back(explicitlyInstantiatedSymbol);
    functionDefinitionSymbolMap[functionDefinitionSymbol->DefIndex()] = explicitlyInstantiatedSymbol;
    if (explicitlyInstantiatedSymbol->GetFunctionKind() == FunctionKind::destructor)
    {
        destructor = explicitlyInstantiatedSymbol;
    }
}

FunctionDefinitionSymbol* ExplicitInstantiationSymbol::GetFunctionDefinitionSymbol(int index)  const noexcept
{
    auto it = functionDefinitionSymbolMap.find(index);
    if (it != functionDefinitionSymbolMap.end())
    {
        FunctionDefinitionSymbol* functionDefinitionSymbol = it->second;
        functionDefinitionSymbol->SetParent(specialization);
        return functionDefinitionSymbol;
    }
    else
    {
        ThrowException("explicitly instantiated function " + std::to_string(index) + " not found");
    }
    return nullptr;
}

FunctionDefinitionSymbol* ExplicitInstantiationSymbol::Destructor() const noexcept
{
    if (destructor)
    {
        destructor->SetParent(specialization);
    }
    return destructor;
}

void ExplicitInstantiationSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(specialization->Id());
    std::int32_t n = functionDefinitionSymbols.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(n);
    for (auto* fnDefSymbol : functionDefinitionSymbols)
    {
        writer.Write(fnDefSymbol);
    }
}

void ExplicitInstantiationSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(specializationId);
    std::int32_t n = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::int32_t i = 0; i < n; ++i)
    {
        Symbol* symbol = reader.ReadSymbol();
        if (symbol->IsExplicitlyInstantiatedFunctionDefinitionSymbol())
        {
            ExplicitlyInstantiatedFunctionDefinitionSymbol* explicitlyInstantiatedSymbol = static_cast<ExplicitlyInstantiatedFunctionDefinitionSymbol*>(symbol);
            functionDefinitionSymbols.push_back(explicitlyInstantiatedSymbol);
            if (explicitlyInstantiatedSymbol->GetFunctionKind() == FunctionKind::destructor)
            {
                destructor = explicitlyInstantiatedSymbol;
            }
            functionDefinitionSymbolMap[explicitlyInstantiatedSymbol->DefIndex()] = explicitlyInstantiatedSymbol;
        }
        else
        {
            otava::symbols::SetExceptionThrown();
            throw std::runtime_error("explicitly instantiated function definition symbol expected");
        }
    }
}

void ExplicitInstantiationSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol* specializationType = symbolTable.GetType(specializationId);
    if (specializationType && specializationType->IsClassTemplateSpecializationSymbol())
    {
        specialization = static_cast<ClassTemplateSpecializationSymbol*>(specializationType);
        symbolTable.MapExplicitInstantiation(this);
    }
    for (auto* functionDefSymbol : functionDefinitionSymbols)
    {
        functionDefSymbol->Resolve(symbolTable, context);
    }
}

void ExplicitInstantiationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

class ExplicitInstantiationProcessor : public otava::ast::DefaultVisitor
{
public:
    ExplicitInstantiationProcessor(Context* context_);
    void Visit(otava::ast::ExplicitInstantiationNode& node) override;
private:
    Context* context;
};

ExplicitInstantiationProcessor::ExplicitInstantiationProcessor(Context* context_) : context(context_)
{
}

void ExplicitInstantiationProcessor::Visit(otava::ast::ExplicitInstantiationNode& node)
{
    TypeSymbol* type = ProcessExplicitInstantiationDeclaration(node.Declaration(), context);
    if (type && type->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(type);
        specialization->MakeVTab(context, node.GetSourcePos());
        ExplicitInstantiationSymbol* explicitInstantiationSymbol = context->GetSymbolTable()->GetExplicitInstantiation(specialization);
        if (!explicitInstantiationSymbol)
        {
            explicitInstantiationSymbol = new ExplicitInstantiationSymbol(specialization);
            TypeSymbol* classTemplateType = specialization->ClassTemplate();
            if (classTemplateType->IsClassTypeSymbol())
            {
                ClassTypeSymbol* classTemplate = static_cast<ClassTypeSymbol*>(classTemplateType);
                bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
                context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
                for (const auto& memFnDefSymbolPair : classTemplate->MemFnDefSymbolMap())
                {
                    FunctionDefinitionSymbol* memFnDefSymbol = memFnDefSymbolPair.second;
                    std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
                    FunctionSymbol* instantiatedFunctionSymbol = InstantiateMemFnOfClassTemplate(
                        memFnDefSymbol, specialization, templateParameterMap, node.GetSourcePos(), context);
                    if (instantiatedFunctionSymbol->IsFunctionDefinitionSymbol())
                    {
                        FunctionDefinitionSymbol* instantiatedMemFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(instantiatedFunctionSymbol);
                        explicitInstantiationSymbol->AddFunctionDefinitionSymbol(instantiatedMemFnDefSymbol, node.GetSourcePos(), context);
                    }
                    else
                    {
                        ThrowException("function definition symbol expected", node.GetSourcePos(), context);
                    }
                }
                context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
            }
            else
            {
                ThrowException("class type symbol expected", node.GetSourcePos(), context);
            }
            context->GetSymbolTable()->AddExplicitInstantiation(explicitInstantiationSymbol);
        }
    }
    else
    {
        ThrowException("class template specialization expected", node.GetSourcePos(), context);
    }
}

void ProcessExplicitInstantiation(otava::ast::Node* node, Context* context)
{
    ExplicitInstantiationProcessor processor(context);
    node->Accept(processor);
}

} // namespace otava::symbols
