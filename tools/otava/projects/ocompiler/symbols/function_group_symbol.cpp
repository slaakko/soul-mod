// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.group.symbol;

import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.type_compare;
import otava.symbols.type.symbol;
import otava.symbols.compound.type.symbol;
import otava.symbols.templates;
import otava.symbols.context;

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

std::expected<bool, int> FunctionGroupSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    std::uint32_t count = functions.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    if (!rv) return rv;
    for (FunctionSymbol* function : functions)
    {
        rv = writer.GetBinaryStreamWriter().Write(function->Id());
        if (!rv) return rv;
    }
    std::uint32_t fdCount = definitions.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(fdCount);
    if (!rv) return rv;
    for (FunctionDefinitionSymbol* definition : definitions)
    {
        rv = writer.GetBinaryStreamWriter().Write(definition->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionGroupSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t count = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < count; ++i)
    {
        util::uuid functionId;
        rv = reader.GetBinaryStreamReader().ReadUuid(functionId);
        if (!rv) return rv;
        functionIds.push_back(functionId);
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t fdCount = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < fdCount; ++i)
    {
        util::uuid functionDefinitionId;
        rv = reader.GetBinaryStreamReader().ReadUuid(functionDefinitionId);
        if (!rv) return rv;
        functionDefinitionIds.push_back(functionDefinitionId);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionGroupSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    for (const auto& functionId : functionIds)
    {
        std::expected<FunctionSymbol*, int> f = symbolTable.GetFunction(functionId);
        if (!f) return std::unexpected<int>(f.error());
        FunctionSymbol* function = *f;
        functions.push_back(function);
    }
    for (const auto& functionDefinitionId : functionDefinitionIds)
    {
        std::expected<FunctionDefinitionSymbol*, int> f = symbolTable.GetFunctionDefinition(functionDefinitionId);
        if (!f) return std::unexpected<int>(f.error());
        FunctionDefinitionSymbol* functionDefinition = *f;
        if (functionDefinition)
        {
            definitions.push_back(functionDefinition);
        }
    }
    return std::expected<bool, int>(true);
}

void FunctionGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionGroupSymbol::Merge(FunctionGroupSymbol* that)
{
    for (FunctionSymbol* function : that->functions)
    {
        if (std::find(functions.cbegin(), functions.cend(), function) == functions.end())
        {
            functions.push_back(function);
        }
    }
    for (FunctionDefinitionSymbol* definition : that->definitions)
    {
        if (std::find(definitions.cbegin(), definitions.cend(), definition) == definitions.end())
        {
            definitions.push_back(definition);
        }
    }
}

FunctionSymbol* FunctionGroupSymbol::ResolveFunction(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers,
    const std::vector<TypeSymbol*>& specialization, TemplateDeclarationSymbol* templateDeclaration, bool isSpecialization, Context* context) const
{
    for (FunctionSymbol* function : functions)
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
                if (!TypesEqual(templateDeclaration->TemplateParameters()[i], functionTemplateDeclaration->TemplateParameters()[i], context)) continue;
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
                            if (!TypesEqual(specialization[i], function->Specialization()[i], context))
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
                        if (!TypesEqual(function->Parameters()[i]->GetType(), parameterTypes[i], context))
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

FunctionDefinitionSymbol* FunctionGroupSymbol::GetFunctionDefinition(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers, Context* context) const
{
    for (FunctionDefinitionSymbol* functionDefinition : definitions)
    {
        if (functionDefinition->Arity() == parameterTypes.size())
        {
            bool found = qualifiers == functionDefinition->Qualifiers();
            if (found)
            {
                for (int i = 0; i < functionDefinition->Arity(); ++i)
                {
                    if (!TypesEqual(functionDefinition->Parameters()[i]->GetType(), parameterTypes[i], context))
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
    for (FunctionSymbol* decl : functions)
    {
        if (decl != function && FunctionMatches(decl, function, context))
        {
            decl->SetVTabIndex(vtabIndex);
        }
    }
    for (FunctionDefinitionSymbol* def : definitions)
    {
        if (static_cast<FunctionSymbol*>(def) != function && FunctionMatches(static_cast<FunctionSymbol*>(def), function, context))
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

std::expected<int, int> MatchFunctionTemplate(FunctionSymbol* function, const std::vector<TypeSymbol*>& templateArgs, Context* context)
{
    if (function->Specialization().empty())
    {
        return std::expected<int, int>(0);
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
                    Derivations argDerivations = templateArgCompoundType->GetDerivations();
                    if (specializationType->IsCompoundTypeSymbol())
                    {
                        CompoundTypeSymbol* specializationCompoundType = static_cast<CompoundTypeSymbol*>(specializationType);
                        Derivations specializationDerivations = specializationCompoundType->GetDerivations();
                        int numMatchingDerivations = CountMatchingDerivations(argDerivations, specializationDerivations);
                        if (numMatchingDerivations > 0)
                        {
                            score += numMatchingDerivations;
                        }
                    }
                    else
                    {
                        return std::expected<int, int>(-1);
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
                            std::expected<TypeSymbol*, int> rd = templateArg->RemoveDerivations(specializationType->GetDerivations(), context);
                            if (!rd) return std::unexpected<int>(rd.error());
                            templateArgumentType = *rd;
                            if (templateArgumentType)
                            {
                                templateParameterMap[templateParameter] = templateArgumentType;
                            }
                            else
                            {
                                return std::expected<int, int>(-1);
                            }
                        }
                        else
                        {
                            templateArgumentType = it->second;
                        }
                        std::expected<TypeSymbol*, int> ud = specializationType->Unify(templateArgumentType, context);
                        if (!ud) return std::unexpected<int>(ud.error());
                        specializationType = *ud;
                        if (!specializationType)
                        {
                            return std::expected<int, int>(-1);
                        }
                    }
                    if (!TypesEqual(templateArg, specializationType, context))
                    {
                        return std::expected<int, int>(-1);
                    }
                    else
                    {
                        score += 1;
                    }
                }
            }
            else
            {
                return std::expected<int, int>(-1);
            }
        }
        return std::expected<int, int>(score);
    }
    return std::expected<int, int>(-1);
}

std::expected<bool, int> FunctionGroupSymbol::CollectBestMatchingViableFunctionTemplates(
    int arity, const std::vector<TypeSymbol*>& templateArgs, std::vector<FunctionSymbol*>& viableFunctions, Context* context)
{
    std::vector<std::pair<FunctionSymbol*, int>> functionScores;
    for (FunctionSymbol* function : functions)
    {
        if (!function->IsTemplate()) continue;
        std::expected<int, int> m = MatchFunctionTemplate(function, templateArgs, context);
        if (!m) return std::unexpected<int>(m.error());
        int score = *m;
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
    for (FunctionDefinitionSymbol* functionDefinition : definitions)
    {
        if (!functionDefinition->IsTemplate()) continue;
        std::expected<int, int> m = MatchFunctionTemplate(functionDefinition, templateArgs, context);
        if (!m) return std::unexpected<int>(m.error());
        int score = *m;
        if (score >= 0)
        {
            functionDefScores.push_back(std::make_pair(static_cast<FunctionSymbol*>(functionDefinition), score));
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
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionGroupSymbol::CollectViableFunctions(int arity, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<FunctionSymbol*>& viableFunctions, Context* context)
{
    if (!templateArgs.empty())
    {
        std::expected<bool, int> m = CollectBestMatchingViableFunctionTemplates(arity, templateArgs, viableFunctions, context);
        if (!m) return m;
    }
    else
    {
        for (FunctionSymbol* function : functions)
        {
            if (arity >= function->MinMemFunArity(context) && arity <= function->MemFunArity(context))
            {
                if (std::find(viableFunctions.begin(), viableFunctions.end(), function) == viableFunctions.end())
                {
                    if (function->Skip()) continue;
                    if (context->GetFlag(ContextFlags::skipNonstaticMemberFunctions) && !function->IsStatic() && function->IsMemberFunction()) continue;
                    viableFunctions.push_back(function);
                }
            }
        }
        for (FunctionDefinitionSymbol* functionDefinition : definitions)
        {
            if ((functionDefinition->Qualifiers() & FunctionQualifiers::isDeleted) != FunctionQualifiers::none)
            {
                continue;
            }
            if (functionDefinition->Skip()) continue;
            if (context->GetFlag(ContextFlags::skipNonstaticMemberFunctions) && functionDefinition->IsStatic() && functionDefinition->IsMemberFunction()) continue;
            if (arity >= functionDefinition->MinMemFunArity(context) && arity <= functionDefinition->MemFunArity(context))
            {
                if (std::find(viableFunctions.begin(), viableFunctions.end(), functionDefinition) == viableFunctions.end())
                {
                    viableFunctions.push_back(functionDefinition);
                }
            }
        }
    }
    return std::expected<bool, int>(true);
}

FunctionSymbol* FunctionGroupSymbol::GetMatchingSpecialization(FunctionSymbol* specialization, Context* context) const
{
    for (FunctionSymbol* function : functions)
    {
        if (function->IsSpecialization() && FunctionMatches(function, specialization, context))
        {
            return function;
        }
    }
    for (FunctionDefinitionSymbol* functionDefinition : definitions)
    {
        if (functionDefinition->IsSpecialization() && FunctionMatches(functionDefinition, specialization, context))
        {
            return functionDefinition;
        }
    }
    return nullptr;
}

} // namespace otava::symbols
