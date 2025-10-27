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
import otava.symbols.error;
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

util::uuid MakeTemplateParameterId(const util::uuid& id, const std::u32string& name)
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

std::expected<bool, int> TemplateParameterSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::AddSymbol(symbol, sourcePos, context);
    if (!rv) return rv;
    if (symbol->IsParameterSymbol())
    {
        parameterSymbol = static_cast<ParameterSymbol*>(symbol);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TemplateParameterSymbol::Write(Writer& writer)
{
    std::expected<bool, int>  rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    util::uuid constraintId = util::nil_uuid();
    if (constraint)
    {
        constraintId = constraint->Id();
    }
    rv = writer.GetBinaryStreamWriter().Write(constraintId);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(index);
    if (!rv) return rv;
    bool hasDefaultTemplateArg = defaultTemplateArgNode != nullptr;
    rv = writer.GetBinaryStreamWriter().Write(hasDefaultTemplateArg);
    if (!rv) return rv;
    if (hasDefaultTemplateArg)
    {
        rv = writer.GetBinaryStreamWriter().Write(defaultTemplateArgNode->InternalId());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TemplateParameterSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(constraintId);
    if (!rv) return rv;
    std::expected<std::int32_t, int> irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    index = *irv;
    std::expected<bool, int> brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    bool hasDefaultTemplateArg = *brv;
    if (hasDefaultTemplateArg)
    {
        std::expected<std::int64_t, int> lrv = reader.GetBinaryStreamReader().ReadLong();
        if (!lrv) return std::unexpected<int>(lrv.error());
        defaultTemplateArgNodeId = *lrv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TemplateParameterSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    symbolTable.MapType(this);
    if (constraintId != util::nil_uuid())
    {
        std::expected<Symbol*, int> rv = symbolTable.GetConstraint(constraintId);
        if (!rv) return std::unexpected<int>(rv.error());
        constraint = *rv;
    }
    if (defaultTemplateArgNodeId != -1)
    {
        otava::ast::NodeMap* nodeMap = symbolTable.GetNodeMap();
        std::expected<otava::ast::Node*, int> rv = nodeMap->GetNode(defaultTemplateArgNodeId);
        if (!rv) return std::unexpected<int>(rv.error());
        otava::ast::Node* node = *rv;
        defaultTemplateArgNode = node;
    }
    return std::expected<bool, int>(true);
}

void TemplateParameterSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<TypeSymbol*, int> TemplateParameterSymbol::Unify(TypeSymbol* argType, Context* context)
{
    return std::expected<TypeSymbol*, int>(argType);
}

std::expected<TypeSymbol*, int> TemplateParameterSymbol::UnifyTemplateArgumentType(
    const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context)
{
    auto it = templateParameterMap.find(this);
    if (it != templateParameterMap.cend())
    {
        TypeSymbol* templateArgumentType = it->second;
        return std::expected<TypeSymbol*, int>(templateArgumentType);
    }
    else
    {
        return std::expected<TypeSymbol*, int>(nullptr);
    }
}

bool TemplateParameterSymbol::IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const
{
    if (visited.find(this) == visited.end())
    {
        visited.insert(this);
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

std::expected<bool, int> TemplateDeclarationSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = ContainerSymbol::AddSymbol(symbol, sourcePos, context);
    if (!rv) return rv;
    if (symbol->IsTemplateParameterSymbol())
    {
        templateParameters.push_back(static_cast<TemplateParameterSymbol*>(symbol));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TemplateDeclarationSymbol::Write(Writer& writer)
{
    return ContainerSymbol::Write(writer);
}

std::expected<bool, int> TemplateDeclarationSymbol::Read(Reader& reader)
{
    return ContainerSymbol::Read(reader);
}

void TemplateDeclarationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BeginTemplateDeclaration(otava::ast::Node* node, Context* context)
{
    std::expected<bool, int>  rv = context->GetSymbolTable()->BeginTemplateDeclaration(node, context);
    if (!rv) return rv;
    context->PushSetFlag(ContextFlags::parsingTemplateDeclaration);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EndTemplateDeclaration(otava::ast::Node* node, Context* context)
{
    Symbol* symbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (!symbol->IsTemplateDeclarationSymbol())
    {
        return Error("otava.symbols.templates: EndTemplateDeclaration(): template scope expected", node->GetSourcePos(), context);
    }
    context->PopFlags();
    std::expected<bool, int> rv = context->GetSymbolTable()->EndTemplateDeclaration();
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> RemoveTemplateDeclaration(Context* context)
{
    return context->GetSymbolTable()->RemoveTemplateDeclaration();
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
    if (!Valid()) return;
    resolveConstraint = true;
    node.TypeConstraint()->Accept(*this);
    if (!Valid()) return;
    resolveConstraint = false;
    if (node.Identifier())
    {
        resolveTemplateParamName = true;
        node.Identifier()->Accept(*this);
        if (!Valid()) return;
        resolveTemplateParamName = false;
    }
    otava::ast::Node* defaultTemplateArgNode = nullptr;
    if (node.TypeId())
    {
        defaultTemplateArgNode = node.TypeId();
    }
    std::expected<bool, int> rv = context->GetSymbolTable()->AddTemplateParameter(templateParamName, &node, constraint, index, nullptr, defaultTemplateArgNode, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
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
    std::expected<Declaration, int> rv = ProcessParameterDeclaration(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    Declaration declaration = std::move(*rv);
    TypeSymbol* type = declaration.type;
    if (declaration.declarator->Kind() == DeclaratorKind::simpleDeclarator)
    {
        SimpleDeclarator* declarator = static_cast<SimpleDeclarator*>(declaration.declarator.get());
        std::u32string templateParamName = declarator->Name();
        Value* value = nullptr;
        if (node.Initializer())
        {
            std::expected<Value*, int> rv = Evaluate(node.Initializer(), context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            value = *rv;
        }
        ParameterSymbol* parameter = new ParameterSymbol(templateParamName, type);
        parameter->SetDefaultValue(node.Initializer());
        std::expected<bool, int> rv = context->GetSymbolTable()->AddTemplateParameter(templateParamName, &node, nullptr, index, parameter, nullptr, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        std::unexpected<int> result = Error("simple declarator expected", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

void TemplateParameterCreator::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    if (resolveTemplateParamName)
    {
        templateParamName = node.Str();
    }
}

std::expected<bool, int> AddTemplateParameter(otava::ast::Node* templateParameterNode, int index, Context* context)
{
    TemplateParameterCreator creator(context, index);
    templateParameterNode->Accept(creator);
    if (!creator) return std::unexpected<int>(creator.Error());
    return std::expected<bool, int>(true);
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

std::expected<FunctionDefinitionSymbol*, int> ExplicitInstantiationSymbol::GetFunctionDefinitionSymbol(int index)  const
{
    auto it = functionDefinitionSymbolMap.find(index);
    if (it != functionDefinitionSymbolMap.end())
    {
        FunctionDefinitionSymbol* functionDefinitionSymbol = it->second;
        functionDefinitionSymbol->SetParent(specialization);
        return std::expected<FunctionDefinitionSymbol*, int>(functionDefinitionSymbol);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("explicitly instantiated function " + std::to_string(index) + " not found"));
    }
}

FunctionDefinitionSymbol* ExplicitInstantiationSymbol::Destructor() const
{
    if (destructor)
    {
        destructor->SetParent(specialization);
    }
    return destructor;
}

std::expected<bool, int> ExplicitInstantiationSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(specialization->Id());
    if (!rv) return rv;
    std::int32_t n = functionDefinitionSymbols.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(n);
    if (!rv) return rv;
    for (ExplicitlyInstantiatedFunctionDefinitionSymbol* fnDefSymbol : functionDefinitionSymbols)
    {
        rv = writer.Write(fnDefSymbol);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExplicitInstantiationSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(specializationId);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t n = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(n); ++i)
    {
        std::expected<Symbol*, int> s = reader.ReadSymbol();
        if (!s) return std::unexpected<int>(s.error());
        Symbol* symbol = *s;
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
            return std::unexpected<int>(util::AllocateError("explicitly instantiated function definition symbol expected"));
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExplicitInstantiationSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol* specializationType = symbolTable.GetType(specializationId);
    if (specializationType && specializationType->IsClassTemplateSpecializationSymbol())
    {
        specialization = static_cast<ClassTemplateSpecializationSymbol*>(specializationType);
        symbolTable.MapExplicitInstantiation(this);
    }
    for (ExplicitlyInstantiatedFunctionDefinitionSymbol* functionDefSymbol : functionDefinitionSymbols)
    {
        std::expected<bool, int> rv = functionDefSymbol->Resolve(symbolTable, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
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
    std::expected<TypeSymbol*, int> rv = ProcessExplicitInstantiationDeclaration(node.Declaration(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    TypeSymbol* type = *rv;
    if (type && type->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(type);
        std::expected<bool, int> rv = specialization->MakeVTab(context, node.GetSourcePos());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        std::expected<ExplicitInstantiationSymbol*, int> erv = context->GetSymbolTable()->GetExplicitInstantiation(specialization);
        if (!erv)
        {
            SetError(erv.error());
            return;
        }
        ExplicitInstantiationSymbol* explicitInstantiationSymbol = *erv;
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
                    std::expected<FunctionSymbol*, int> mfn = InstantiateMemFnOfClassTemplate(memFnDefSymbol, specialization, templateParameterMap,
                        node.GetSourcePos(), context);
                    if (!mfn)
                    {
                        SetError(mfn.error());
                        return;
                    }
                    FunctionSymbol* instantiatedFunctionSymbol = *mfn;
                    if (instantiatedFunctionSymbol->IsFunctionDefinitionSymbol())
                    {
                        FunctionDefinitionSymbol* instantiatedMemFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(instantiatedFunctionSymbol);
                        explicitInstantiationSymbol->AddFunctionDefinitionSymbol(instantiatedMemFnDefSymbol, node.GetSourcePos(), context);
                    }
                    else
                    {
                        std::unexpected<int> result = Error("function definition symbol expected", node.GetSourcePos(), context);
                        SetError(result.error());
                        return;
                    }
                }
                context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
            }
            else
            {
                std::unexpected<int> result = Error("class type symbol expected", node.GetSourcePos(), context);
                SetError(result.error());
                return;
            }
            context->GetSymbolTable()->AddExplicitInstantiation(explicitInstantiationSymbol);
        }
    }
    else
    {
        std::unexpected<int> result = Error("class template specialization expected", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

std::expected<bool, int> ProcessExplicitInstantiation(otava::ast::Node* node, Context* context)
{
    ExplicitInstantiationProcessor processor(context);
    node->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
