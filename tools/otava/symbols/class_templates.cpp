// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.class_templates;

import otava.symbols.bound.tree;
import otava.symbols.modules;
import otava.symbols.context;
import otava.symbols.function.symbol;
import otava.symbols.symbol.table;
import otava.symbols.exception;
import otava.symbols.templates;
import otava.symbols.declaration;
import otava.symbols.type.resolver;
import otava.symbols.compound.type.symbol;
import otava.symbols.instantiator;
import otava.symbols.statement.binder;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;
import otava.symbols.namespaces;
import otava.ast;
import util.unicode;
import util.sha1;

namespace otava::symbols {

ClassTemplateSpecializationSymbol::ClassTemplateSpecializationSymbol(const std::u32string& name_) : 
    ClassTypeSymbol(SymbolKind::classTemplateSpecializationSymbol, name_), classTemplate(nullptr), instantiated(false)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

void ClassTemplateSpecializationSymbol::SetClassTemplate(ClassTypeSymbol* classTemplate_)
{
    classTemplate = classTemplate_;
}

void ClassTemplateSpecializationSymbol::AddTemplateArgument(Symbol* templateArgument)
{
    templateArguments.push_back(templateArgument);
}

std::string ClassTemplateSpecializationSymbol::IrName(Context* context) const
{
    std::string fullIrName = classTemplate->IrName(context);
    std::string templateArgIrNames;
    for (const auto& templateArg : templateArguments)
    {
        templateArgIrNames.append(1, '_').append(templateArg->IrName(context));
    }
    fullIrName.append(1, '_').append(util::GetSha1MessageDigest(templateArgIrNames));
    return fullIrName;
}

void ClassTemplateSpecializationSymbol::Write(Writer& writer)
{
    ClassTypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(instantiated);
    writer.GetBinaryStreamWriter().Write(classTemplate->Id());
    writer.GetBinaryStreamWriter().WriteULEB128UInt(templateArguments.size());
    for (Symbol* templateArg : templateArguments)
    {
        if (templateArg->IsTypeSymbol())
        {
            writer.GetBinaryStreamWriter().Write(true);
            writer.GetBinaryStreamWriter().Write(templateArg->Id());
        }
        else
        {
            writer.GetBinaryStreamWriter().Write(false);
            writer.GetBinaryStreamWriter().Write(templateArg->Id());
        }
    }
}

void ClassTemplateSpecializationSymbol::Read(Reader& reader)
{
    ClassTypeSymbol::Read(reader);
    instantiated = reader.GetBinaryStreamReader().ReadBool();
    util::uuid id;
    reader.GetBinaryStreamReader().ReadUuid(id);
    ids.push_back(std::make_pair(id, true));
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        util::uuid id;
        bool isType = reader.GetBinaryStreamReader().ReadBool();
        reader.GetBinaryStreamReader().ReadUuid(id);
        ids.push_back(std::make_pair(id, isType));
    }
    
}

void ClassTemplateSpecializationSymbol::Resolve(SymbolTable& symbolTable)
{
    ClassTypeSymbol::Resolve(symbolTable);
    classTemplate = static_cast<ClassTypeSymbol*>(symbolTable.GetType(ids[0].first));
    for (int i = 1; i < ids.size(); ++i)
    {
        const std::pair<util::uuid, bool>& idType = ids[i];
        if (idType.second)
        {
            TypeSymbol* templateArg = symbolTable.GetType(idType.first);
            templateArguments.push_back(templateArg);
        }
        else
        {
            EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
            Value* value = evaluationContext->GetValue(idType.first);
            templateArguments.push_back(value);
        }
    }
}

void ClassTemplateSpecializationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeSymbol* ClassTemplateSpecializationSymbol::UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*>& templateParameterMap, Context* context)
{
    std::vector<Symbol*> targetTemplateArguments;
    for (int i = 0; i < templateArguments.size(); ++i)
    {
        Symbol* sourceTemplateArgumentSymbol = templateArguments[i];
        TypeSymbol* sourceTemplateArgumentType = nullptr;
        if (sourceTemplateArgumentSymbol->IsTypeSymbol())
        {
            sourceTemplateArgumentType = static_cast<TypeSymbol*>(sourceTemplateArgumentSymbol);
        }
        else
        {
            return nullptr;
        }
        TypeSymbol* templateArgumentType = sourceTemplateArgumentType->UnifyTemplateArgumentType(templateParameterMap, context);
        if (templateArgumentType)
        {
            targetTemplateArguments.push_back(templateArgumentType);
        }
        else
        {
            return nullptr;
        }
    }
    return context->GetSymbolTable()->MakeClassTemplateSpecialization(classTemplate, targetTemplateArguments);
}

bool ClassTemplateSpecializationSymbol::IsTemplateParameterInstantiation() const
{
    for (const auto& templateArg : templateArguments)
    {
        if (templateArg->IsTemplateParameterSymbol()) return true;
        if (templateArg->IsClassTypeSymbol())
        {
            ClassTypeSymbol* classTypeTemplateArg = static_cast<ClassTypeSymbol*>(templateArg);
            if (classTypeTemplateArg->IsTemplateParameterInstantiation()) return true;
        }
    }
    return false;
}

std::u32string MakeSpecializationName(TypeSymbol* templateSymbol, const std::vector<Symbol*>& templateArguments)
{
    std::u32string specializationName;
    specializationName.append(templateSymbol->Name());
    specializationName.append(1, '<');
    bool first = true;
    for (Symbol* templateArg : templateArguments)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            specializationName.append(U", ");
        }
        specializationName.append(templateArg->Name());
    }
    specializationName.append(1, '>');
    return specializationName;
}

CompoundTypeSymbol* GetSpecializationArgType(TypeSymbol* specialization, int index)
{
    if (specialization->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specializationSymbol = static_cast<ClassTemplateSpecializationSymbol*>(specialization);
        if (index >= 0 && index < specializationSymbol->TemplateArguments().size())
        {
            Symbol* specializationArg = specializationSymbol->TemplateArguments()[index];
            if (specializationArg->IsCompoundTypeSymbol())
            {
                CompoundTypeSymbol* specializationArgType = static_cast<CompoundTypeSymbol*>(specializationArg);
                return specializationArgType;
            }
        }
    }
    return nullptr;
}

TypeSymbol* InstantiateClassTemplate(ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArgs, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ClassTemplateSpecializationSymbol* specialization = context->GetSymbolTable()->MakeClassTemplateSpecialization(classTemplate, templateArgs);
    context->GetBoundCompileUnit()->AddBoundNodeForClass(specialization, sourcePos);
    if (specialization->Instantiated()) return specialization;
    otava::ast::Node* classNode = context->GetSymbolTable()->GetSpecifierNode(classTemplate);
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
    TemplateDeclarationSymbol* templateDeclaration = classTemplate->ParentTemplateDeclaration();
    if (templateDeclaration)
    {
        int arity = templateDeclaration->Arity();
        int argCount = templateArgs.size();
        if (argCount > arity)
        {
            ThrowException("otava.symbols.templates: wrong number of template args for instantiating class template '" +
                util::ToUtf8(classTemplate->Name()) + "'",
                sourcePos, context);
        }
        specialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope());
        specialization->GetScope()->AddParentScope(specialization->ClassTemplate()->GetScope()->GetNamespaceScope());
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
                    ThrowException("otava.symbols.templates: template parameter " + std::to_string(i) + " has no default type argument", sourcePos, context);
                }
            }
            else
            {
                templateArg = templateArgs[i];
            }
            if (templateArg->IsTypeSymbol())
            {
                TypeSymbol* templateArgType = static_cast<TypeSymbol*>(templateArg);
                TypeSymbol* specialization = classTemplate->Specialization();
                if (specialization)
                {
                    CompoundTypeSymbol* specializationArgType = GetSpecializationArgType(specialization, i);
                    if (specializationArgType)
                    {
                        templateArg = templateArgType->RemoveDerivations(specializationArgType->GetDerivations(), context);
                    }
                    else
                    {
                        ThrowException("otava.symbols.templates: specialization argument type not resolved", sourcePos, context);
                    }
                }
            }
            BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
            boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
            boundTemplateParameter->SetBoundSymbol(templateArg);
            boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
            instantiationScope.Install(boundTemplateParameter);
        }
        context->GetSymbolTable()->BeginScope(&instantiationScope);
        Instantiator instantiator(context, &instantiationScope);
        try
        {
            context->PushSetFlag(ContextFlags::dontBind | ContextFlags::skipFunctionDefinitions);
            classNode->Accept(instantiator);
            std::vector<ClassTypeSymbol*> baseClasses = instantiator.GetBaseClasses();
            for (ClassTypeSymbol* baseClass : baseClasses)
            {
                specialization->AddBaseClass(baseClass, sourcePos, context);
            }
            context->PopFlags();
        }
        catch (const std::exception& ex)
        {
            ThrowException("otava.symbols.templates: error instantiating specialization '" +
                util::ToUtf8(specialization->FullName()) + "': " + std::string(ex.what()), sourcePos, context);
        }
        context->GetSymbolTable()->EndScope();
        context->GetSymbolTable()->EndScope();
        specialization->GetScope()->ClearParentScopes();
    }
    else
    {
        ThrowException("otava.symbols.templates: template declarator for class template '" + util::ToUtf8(classTemplate->Name()) + " not found", sourcePos, context);
    }
    return specialization;
}

MemFunKey::MemFunKey(FunctionSymbol* memFun_, const std::vector<TypeSymbol*>& templateArgumentTypes_) : memFun(memFun_), templateArgumentTypes(templateArgumentTypes_)
{
}

bool MemFunKeyLess::operator()(const MemFunKey& left, const MemFunKey& right) const
{
    if (left.memFun < right.memFun) return true;
    if (left.memFun > right.memFun) return false;
    return left.templateArgumentTypes < right.templateArgumentTypes;
}

ClassTemplateRepository::ClassTemplateRepository() 
{
}

FunctionDefinitionSymbol* ClassTemplateRepository::GetFunctionDefinition(const MemFunKey& key) const
{
    auto it = memFunMap.find(key);
    if (it != memFunMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void ClassTemplateRepository::AddFunctionDefinition(const MemFunKey& key, FunctionDefinitionSymbol* functionDefinitionSymbol, otava::ast::Node* functionDefinitionNode)
{
    memFunMap[key] = functionDefinitionSymbol;
    functionDefinitionNodes.push_back(std::unique_ptr<otava::ast::Node>(functionDefinitionNode));
}

FunctionDefinitionSymbol* InstantiateMemFnOfClassTemplate(FunctionSymbol* memFn, ClassTemplateSpecializationSymbol* classTemplateSpecialization, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::string specializationName = util::ToUtf8(memFn->Name());
    if (specializationName == "insert")
    {
        int x = 0;
    }
    InstantiateClassTemplate(classTemplateSpecialization->ClassTemplate(), classTemplateSpecialization->TemplateArguments(), sourcePos, context);
    context->GetBoundCompileUnit()->AddBoundNodeForClass(classTemplateSpecialization, sourcePos);
    ClassTemplateRepository* classTemplateRepository = context->GetBoundCompileUnit()->GetClassTemplateRepository();
    std::vector<TypeSymbol*> templateArgumentTypes;
    int n = classTemplateSpecialization->TemplateArguments().size();
    for (int i = 0; i < n; ++i)
    {
        Symbol* templateArg = classTemplateSpecialization->TemplateArguments()[i];
        if (templateArg->IsTypeSymbol())
        {
            TypeSymbol* templateArgumentType = static_cast<TypeSymbol*>(templateArg);
            templateArgumentTypes.push_back(templateArgumentType);
        }
    }
    MemFunKey key(memFn, templateArgumentTypes);
    FunctionDefinitionSymbol* functionDefinitionSymbol = classTemplateRepository->GetFunctionDefinition(key);
    if (functionDefinitionSymbol)
    {
        return functionDefinitionSymbol;
    }
    ExplicitInstantiationSymbol* explicitInstantiation = context->GetSymbolTable()->GetExplicitInstantiation(classTemplateSpecialization);
    if (explicitInstantiation)
    {
        if (memFn->IsFunctionDefinitionSymbol())
        {
            FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(memFn);
            FunctionDefinitionSymbol* functionDefinitionSymbol = explicitInstantiation->GetFunctionDefinitionSymbol(memFnDefSymbol->DefIndex());
            functionDefinitionSymbol->SetDestructor(explicitInstantiation->Destructor());
            return functionDefinitionSymbol;
        }
        else 
        { 
            ThrowException("otava.symbols.class_templates: function definition symbol expected", sourcePos, context);
        }
    }
    otava::ast::Node* node = context->GetSymbolTable()->GetNode(memFn)->Clone();
    if (node->IsFunctionDefinitionNode())
    {
        otava::ast::FunctionDefinitionNode* functionDefinitionNode = static_cast<otava::ast::FunctionDefinitionNode*>(node);
        ClassTypeSymbol* parentClass = memFn->ParentClassType();
        if (parentClass)
        {
            TemplateDeclarationSymbol* templateDeclaration = parentClass->ParentTemplateDeclaration();
            if (templateDeclaration)
            {
                int arity = templateDeclaration->Arity();
                int argCount = templateArgumentTypes.size();
                if (argCount > arity)
                {
                    ThrowException("otava.symbols.class_templates: wrong number of template args for instantiating class template member function '" +
                        util::ToUtf8(memFn->Name()) + "'",
                        node->GetSourcePos(),
                        context);
                }
                classTemplateSpecialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
                InstantiationScope instantiationScope(classTemplateSpecialization->GetScope());
                std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
                for (int i = 0; i < arity; ++i)
                {
                    Symbol* templateArg = templateArgumentTypes[i];
                    TemplateParameterSymbol* templateParameter = templateDeclaration->TemplateParameters()[i];
                    BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
                    boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                    boundTemplateParameter->SetBoundSymbol(templateArg);
                    boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                    instantiationScope.Install(boundTemplateParameter);
                }
                BoundTemplateParameterSymbol* templateNameParameter(new BoundTemplateParameterSymbol(classTemplateSpecialization->ClassTemplate()->Name()));
                templateNameParameter->SetBoundSymbol(classTemplateSpecialization);
                boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(templateNameParameter));
                instantiationScope.Install(templateNameParameter);
                context->GetSymbolTable()->BeginScope(&instantiationScope);
                Instantiator instantiator(context, &instantiationScope);
                FunctionDefinitionSymbol* specialization = nullptr;
                try
                {
                    context->PushSetFlag(ContextFlags::instantiateMemFnOfClassTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
                    context->SetFunctionDefinitionNode(functionDefinitionNode);
                    if (memFn->IsFunctionDefinitionSymbol())
                    {
                        FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(memFn);
                        context->SetMemFunDefSymbolIndex(memFnDefSymbol->DefIndex());
                    }
                    functionDefinitionNode->Accept(instantiator);
                    context->SetMemFunDefSymbolIndex(-1);
                    specialization = context->GetSpecialization();
                    specializationName = util::ToUtf8(specialization->FullName());
                    classTemplateRepository->AddFunctionDefinition(key, specialization, node);
                    context->PushBoundFunction(new BoundFunctionNode(specialization, sourcePos));
                    Scope* nsScope = classTemplateSpecialization->ClassTemplate()->GetScope()->GetNamespaceScope();
                    instantiationScope.PushParentScope(nsScope);
                    BindFunction(functionDefinitionNode, specialization, context);
                    context->PopFlags();
                    if (specialization->IsBound())
                    {
                        context->GetBoundCompileUnit()->AddBoundNode(context->ReleaseBoundFunction());
                    }
                    context->PopBoundFunction();
                    specialization->GetScope()->ClearParentScopes();
                }
                catch (const std::exception& ex)
                {
                    ThrowException("otava.symbols.class_templates: error instantiating specialization '" + specializationName + 
                        "': " + std::string(ex.what()), node->GetSourcePos(), context);
                }
                context->GetSymbolTable()->EndScope();
                return specialization;
            }
            else
            {
                ThrowException("otava.symbols.class_templates: parent class template declaration not found", node->GetSourcePos(), context);
            }
        }
        else
        {
            ThrowException("otava.symbols.class_templates: parent class template not found", node->GetSourcePos(), context);
        }
    }
    else
    {
        ThrowException("otava.symbols.class_templates: function definition node expected", node->GetSourcePos(), context);
    }
}

} // namespace otava::symbols

