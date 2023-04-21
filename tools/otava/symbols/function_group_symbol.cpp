// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.group.symbol;

import otava.symbols.function.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.type_compare;
import otava.symbols.type.symbol;
import otava.symbols.compound.type.symbol;
import otava.symbols.templates;

namespace otava::symbols {

FunctionGroupSymbol::FunctionGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::functionGroupSymbol, name_)
{
}

bool FunctionGroupSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope: 
        case ScopeKind::templateDeclarationScope: 
        case ScopeKind::classScope: 
        case ScopeKind::enumerationScope:
        case ScopeKind::arrayScope:
        {
            return true;
        }
    }
    return false;
}

Symbol* FunctionGroupSymbol::GetSingleSymbol() 
{
    if (functions.size() == 1)
    {
        return functions.front();
    }
    else
    {
        return this;
    }
}

FunctionDefinitionSymbol* FunctionGroupSymbol::GetSingleDefinition()
{
    if (definitions.size() == 1)
    {
        return definitions.front();
    }
    else
    {
        return nullptr;
    }
}

void FunctionGroupSymbol::AddFunction(FunctionSymbol* function)
{
    functions.push_back(function);
    function->SetGroup(this);
}

void FunctionGroupSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    uint32_t count = functions.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (FunctionSymbol* function : functions)
    {
        writer.GetBinaryStreamWriter().Write(function->Id());
    }
    uint32_t fdCount = definitions.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(fdCount);
    for (FunctionDefinitionSymbol* definition : definitions)
    {
        writer.GetBinaryStreamWriter().Write(definition->Id());
    }
}

void FunctionGroupSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        util::uuid functionId;
        reader.GetBinaryStreamReader().ReadUuid(functionId);
        functionIds.push_back(functionId);
    }
    uint32_t fdCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < fdCount; ++i)
    {
        util::uuid functionDefinitionId;
        reader.GetBinaryStreamReader().ReadUuid(functionDefinitionId);
        functionDefinitionIds.push_back(functionDefinitionId);
    }
}

void FunctionGroupSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    for (const auto& functionId : functionIds)
    {
        FunctionSymbol* function = symbolTable.GetFunction(functionId);
        functions.push_back(function);
    }
    for (const auto& functionDefinitionId : functionDefinitionIds)
    {
        FunctionDefinitionSymbol* functionDefinition = symbolTable.GetFunctionDefinition(functionDefinitionId);
        if (functionDefinition)
        {
            definitions.push_back(functionDefinition);
        }
    }
}

void FunctionGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionGroupSymbol::Merge(FunctionGroupSymbol* that)
{
    for (const auto& function : that->functions)
    {
        if (std::find(functions.cbegin(), functions.cend(), function) == functions.end())
        {
            functions.push_back(function);
        }
    }
    for (const auto& definition : that->definitions)
    {
        if (std::find(definitions.cbegin(), definitions.cend(), definition) == definitions.end())
        {
            definitions.push_back(definition);
        }
    }
}

FunctionSymbol* FunctionGroupSymbol::ResolveFunction(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers,
    const std::vector<TypeSymbol*>& specialization, TemplateDeclarationSymbol* templateDeclaration, bool isSpecialization) const
{
    for (const auto& function : functions)
    {
        TemplateDeclarationSymbol* functionTemplateDeclaration = function->ParentTemplateDeclaration();
        if (templateDeclaration && !functionTemplateDeclaration || !templateDeclaration && functionTemplateDeclaration)
        {
            continue;
        }
        if (templateDeclaration)
        {
            if (templateDeclaration->Arity() != functionTemplateDeclaration->Arity()) continue;
            for (int i = 0; i < templateDeclaration->Arity(); ++i)
            {
                if (!TypesEqual(templateDeclaration->TemplateParameters()[i], functionTemplateDeclaration->TemplateParameters()[i])) continue;
            }
        }
        if (!function->IsMemberFunction() && function->IsSpecialization() != isSpecialization) continue;
        if (function->Arity() == parameterTypes.size())
        {
            bool found = (qualifiers & FunctionQualifiers::isConst) == (function->Qualifiers() & FunctionQualifiers::isConst);
            if (found)
            {
                if (!specialization.empty())
                {
                    int n = specialization.size();
                    if (n != function->Specialization().size())
                    {
                        found = false;
                    }
                    else
                    {
                        for (int i = 0; i < n; ++i)
                        {
                            if (!TypesEqual(specialization[i], function->Specialization()[i]))
                            {
                                found = false;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < function->Arity(); ++i)
                    {
                        if (!TypesEqual(function->Parameters()[i]->GetType(), parameterTypes[i]))
                        {
                            found = false;
                            break;
                        }
                    }
                }
                if (found)
                {
                    return function;
                }
            }
        }
    }
    return nullptr;
}

FunctionDefinitionSymbol* FunctionGroupSymbol::GetFunctionDefinition(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers) const
{
    for (const auto& functionDefinition : definitions)
    {
        if (functionDefinition->Arity() == parameterTypes.size())
        {
            bool found = qualifiers == functionDefinition->Qualifiers();
            if (found)
            {
                for (int i = 0; i < functionDefinition->Arity(); ++i)
                {
                    if (!TypesEqual(functionDefinition->Parameters()[i]->GetType(), parameterTypes[i]))
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    return functionDefinition;
                }
            }
        }
    }
    return nullptr;
}

void FunctionGroupSymbol::SetVTabIndex(FunctionSymbol* function, int vtabIndex, Context* context)
{
    for (const auto& decl :  functions)
    {
        if (decl != function && FunctionMatches(decl, function, context))
        {
            decl->SetVTabIndex(vtabIndex);
        }
    }
    for (const auto& def : definitions)
    {
        if (def != function && FunctionMatches(def, function, context))
        {
            def->SetVTabIndex(vtabIndex);
        }
    }
}

void FunctionGroupSymbol::AddFunctionDefinition(FunctionDefinitionSymbol* definition, Context* context)
{
    definitions.push_back(definition);
    definition->SetGroup(this);
}

struct FunctionScoreGreater
{
    bool operator()(const std::pair<FunctionSymbol*, int>& left, const std::pair<FunctionSymbol*, int>& right) const
    {
        return left.second > right.second;
    }
};

int MatchFunctionTemplate(FunctionSymbol* function, const std::vector<TypeSymbol*>& templateArgs, Context* context)
{
    if (function->Specialization().empty())
    {
        return 0;
    }
    else
    {
        int score = 0;
        int n = templateArgs.size();
        std::map<TemplateParameterSymbol*, TypeSymbol*> templateParameterMap;
        for (int i = 0; i < n; ++i)
        {
            TypeSymbol* templateArg = templateArgs[i];
            if (function->Specialization().size() >= i)
            {
                TypeSymbol* specializationType = function->Specialization()[i];
                if (templateArg->IsCompoundTypeSymbol())
                {
                    CompoundTypeSymbol* templateArgCompoundType = static_cast<CompoundTypeSymbol*>(templateArg);
                    const Derivations& argDerivations = templateArgCompoundType->GetDerivations();
                    if (specializationType->IsCompoundTypeSymbol())
                    {
                        CompoundTypeSymbol* specializationCompoundType = static_cast<CompoundTypeSymbol*>(specializationType);
                        const Derivations& specializationDerivations = specializationCompoundType->GetDerivations();
                        int numMatchingDerivations = CountMatchingDerivations(argDerivations, specializationDerivations);
                        if (numMatchingDerivations > 0)
                        {
                            score += numMatchingDerivations;
                        }
                    }
                    else
                    {
                        return -1;
                    }
                }
                else
                {
                    TypeSymbol* templateArgumentType = nullptr;
                    if (specializationType->GetBaseType()->IsTemplateParameterSymbol())
                    {
                        TemplateParameterSymbol* templateParameter = static_cast<TemplateParameterSymbol*>(specializationType->GetBaseType());
                        auto it = templateParameterMap.find(templateParameter);
                        if (it == templateParameterMap.end())
                        {
                            templateArgumentType = templateArg->RemoveDerivations(specializationType->GetDerivations(), context);
                            if (templateArgumentType)
                            {
                                templateParameterMap[templateParameter] = templateArgumentType;
                            }
                            else
                            {
                                return -1;
                            }
                        }
                        else
                        {
                            templateArgumentType = it->second;
                        }
                        specializationType = specializationType->Unify(templateArgumentType, context);
                        if (!specializationType)
                        {
                            return -1;
                        }
                    }
                    if (!TypesEqual(templateArg, specializationType))
                    {
                        return -1;
                    }
                    else
                    {
                        score += 1;
                    }
                }
            }
            else
            {
                return -1;
            }
        }
        return score;
    }
    return -1;
}

void FunctionGroupSymbol::CollectBestMatchingViableFunctionTemplates(int arity, const std::vector<TypeSymbol*>& templateArgs, std::vector<FunctionSymbol*>& viableFunctions, 
    Context* context)
{
    std::vector<std::pair<FunctionSymbol*, int>> functionScores;
    for (const auto& function : functions)
    {
        if (!function->IsTemplate()) continue;
        int score = MatchFunctionTemplate(function, templateArgs, context);
        if (score >= 0)
        {
            functionScores.push_back(std::make_pair(function, score));
        }
    }
    std::sort(functionScores.begin(), functionScores.end(), FunctionScoreGreater());
    if (!functionScores.empty())
    {
        FunctionSymbol* function = functionScores[0].first;
        if (arity >= function->MinMemFunArity(context) && arity <= function->MemFunArity(context))
        {
            if (std::find(viableFunctions.begin(), viableFunctions.end(), function) == viableFunctions.end())
            {
                viableFunctions.push_back(function);
            }
        }
    }
    std::vector<std::pair<FunctionSymbol*, int>> functionDefScores;
    for (const auto& functionDefinition : definitions)
    {
        if (!functionDefinition->IsTemplate()) continue;
        int score = MatchFunctionTemplate(functionDefinition, templateArgs, context);
        if (score >= 0)
        {
            functionDefScores.push_back(std::make_pair(functionDefinition, score));
        }
    }
    std::sort(functionDefScores.begin(), functionDefScores.end(), FunctionScoreGreater());
    if (!functionDefScores.empty())
    {
        FunctionSymbol* function = functionDefScores[0].first;
        if (arity >= function->MinMemFunArity(context) && arity <= function->MemFunArity(context))
        {
            if (std::find(viableFunctions.begin(), viableFunctions.end(), function) == viableFunctions.end())
            {
                viableFunctions.push_back(function);
            }
        }
    }
}

void FunctionGroupSymbol::CollectViableFunctions(int arity, const std::vector<TypeSymbol*>& templateArgs, std::vector<FunctionSymbol*>& viableFunctions, Context* context)
{
    if (!templateArgs.empty())
    {
        CollectBestMatchingViableFunctionTemplates(arity, templateArgs, viableFunctions, context);
    }
    else
    {
        for (const auto& function : functions)
        {
            if (arity >= function->MinMemFunArity(context) && arity <= function->MemFunArity(context))
            {
                if (std::find(viableFunctions.begin(), viableFunctions.end(), function) == viableFunctions.end())
                {
                    viableFunctions.push_back(function);
                }
            }
        }
        for (const auto& functionDefinition : definitions)
        {
            if ((functionDefinition->Qualifiers() & FunctionQualifiers::isDeleted) != FunctionQualifiers::none)
            {
                continue;
            }
            if (arity >= functionDefinition->MinMemFunArity(context) && arity <= functionDefinition->MemFunArity(context))
            {
                if (std::find(viableFunctions.begin(), viableFunctions.end(), functionDefinition) == viableFunctions.end())
                {
                    viableFunctions.push_back(functionDefinition);
                }
            }
        }
    }
}

FunctionSymbol* FunctionGroupSymbol::GetMatchingSpecialization(FunctionSymbol* specialization, Context* context) const
{
    for (const auto& function : functions)
    {
        if (function->IsSpecialization() && FunctionMatches(function, specialization, context))
        {
            return function;
        }
    }
    for (const auto& functionDefinition : definitions)
    {
        if (functionDefinition->IsSpecialization() && FunctionMatches(functionDefinition, specialization, context))
        {
            return functionDefinition;
        }
    }
    return nullptr;
}

} // namespace otava::symbols
