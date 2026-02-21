// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.class_group.symbol;

import otava.symbols.classes;
import otava.symbols.class_templates;
import otava.symbols.inline_functions;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.compound.type.symbol;
import otava.symbols.type_compare;

namespace otava::symbols {

ClassGroupSymbol::ClassGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::classGroupSymbol, name_)
{
}

bool ClassGroupSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const noexcept
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

void ClassGroupSymbol::AddClass(ClassTypeSymbol* classTypeSymbol)
{
    if (std::find(classes.begin(), classes.end(), classTypeSymbol) == classes.end())
    {
        classTypeSymbol->SetGroup(this);
        classes.push_back(classTypeSymbol);
        ForwardClassDeclarationSymbol* fwdDeclaration = GetForwardDeclaration(classTypeSymbol->Arity());
        if (fwdDeclaration)
        {
            fwdDeclaration->SetClassTypeSymbol(classTypeSymbol);
        }
    }
}

Symbol* ClassGroupSymbol::GetSingleSymbol() noexcept
{
    if (classes.size() == 1)
    {
        return classes.front();
    }
    else if (forwardDeclarations.size() == 1)
    {
        return forwardDeclarations.front();
    }
    else
    {
        return this;
    }
}

ClassTypeSymbol* ClassGroupSymbol::GetClass(int arity) const noexcept
{
    for (ClassTypeSymbol* classTypeSymbol : classes)
    {
        if (classTypeSymbol->Arity() == arity)
        {
            return classTypeSymbol;
        }
    }
    return nullptr;
}

void ClassGroupSymbol::AddForwardDeclaration(ForwardClassDeclarationSymbol* forwardDeclaration)
{
    forwardDeclaration->SetGroup(this);
    forwardDeclarations.push_back(forwardDeclaration);
    ClassTypeSymbol* cls = GetClass(forwardDeclaration->Arity());
    if (cls)
    {
        forwardDeclaration->SetClassTypeSymbol(cls);
    }
}

ForwardClassDeclarationSymbol* ClassGroupSymbol::GetForwardDeclaration(int arity) const noexcept
{
    for (ForwardClassDeclarationSymbol* forwardDeclaration : forwardDeclarations)
    {
        if (forwardDeclaration->Arity() == arity)
        {
            return forwardDeclaration;
        }
    }
    return nullptr;
}

void ClassGroupSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    std::uint32_t count = classes.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (ClassTypeSymbol* cls : classes)
    {
        writer.GetBinaryStreamWriter().Write(cls->Id());
    }
}

void ClassGroupSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    std::uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < count; ++i)
    {
        util::uuid classId;
        reader.GetBinaryStreamReader().ReadUuid(classId);
        classIds.push_back(classId);
    }
}

void ClassGroupSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    Symbol::Resolve(symbolTable, context);
    for (const auto& classId : classIds)
    {
        ClassTypeSymbol* cls = symbolTable.GetClass(classId);
        if (std::find(classes.begin(), classes.end(), cls) == classes.end())
        {
            classes.push_back(cls);
        }
    }
}

void ClassGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ClassGroupSymbol::Merge(ClassGroupSymbol* that)
{
    if (this == that) return;
    for (ClassTypeSymbol* cls : that->classes)
    {
        if (std::find(classes.cbegin(), classes.cend(), cls) == classes.end())
        {
            classes.push_back(cls);
        }
    }
    for (ForwardClassDeclarationSymbol* fwd : that->forwardDeclarations)
    {
        ForwardClassDeclarationSymbol* prev = GetForwardDeclaration(fwd->Arity());
        if (!prev)
        {
            forwardDeclarations.push_back(fwd);
        }
    }
}

struct ViableClassGreater
{
    inline bool operator()(const std::pair<ClassTypeSymbol*, TemplateMatchInfo>& left, const std::pair<ClassTypeSymbol*, TemplateMatchInfo>& right) const noexcept
    {
        return left.second.matchValue > right.second.matchValue;
    }
};

int Match(Symbol* templateArg, TypeSymbol* specialization, int index, TemplateMatchInfo& info, Context* context)
{
    if (templateArg->IsCompoundTypeSymbol())
    {
        CompoundTypeSymbol* templateArgType = static_cast<CompoundTypeSymbol*>(templateArg);
        Derivations argDerivations = templateArgType->GetDerivations();
        CompoundTypeSymbol* specializationArgType = GetCompoundSpecializationArgType(specialization, index);
        if (specializationArgType)
        {
            Derivations specializationDerivations = specializationArgType->GetDerivations();
            int numMatchingDerivations = CountMatchingDerivations(argDerivations, specializationDerivations);
            if (numMatchingDerivations > 0)
            {
                info.kind = TemplateMatchKind::partialSpecialization;
                return numMatchingDerivations;
            }
        }
    }
    else if (templateArg->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* templateArgType = static_cast<ClassTemplateSpecializationSymbol*>(templateArg);
        ClassTemplateSpecializationSymbol* specializationArgType = GetClassTemplateSpecializationArgType(specialization, index);
        if (specializationArgType)
        {
            if (TypesEqual(templateArgType->ClassTemplate(), specializationArgType->ClassTemplate(), context))
            {
                int n = templateArgType->TemplateArguments().size();
                int m = specializationArgType->TemplateArguments().size();
                if (n == m)
                {
                    for (int i = 0; i < n; ++i)
                    {
                        Symbol* argSymbol = templateArgType->TemplateArguments()[i];
                        TypeSymbol* argTypeSymbol = nullptr;
                        if (argSymbol->IsTypeSymbol())
                        {
                            argTypeSymbol = static_cast<TypeSymbol*>(argSymbol);
                        }
                        Symbol* templateSymbol = specializationArgType->TemplateArguments()[i];
                        TypeSymbol* templateTypeSymbol = nullptr;
                        if (templateSymbol->IsTypeSymbol())
                        {
                            templateTypeSymbol = static_cast<TypeSymbol*>(templateSymbol);
                        }
                        if (argTypeSymbol && templateTypeSymbol)
                        {
                            TypeSymbol* templateArgumentType = nullptr;
                            if (templateTypeSymbol->GetBaseType()->IsTemplateParameterSymbol())
                            {
                                TemplateParameterSymbol* templateParameter = static_cast<TemplateParameterSymbol*>(argTypeSymbol->GetBaseType());
                                auto it = info.templateParameterMap.find(templateParameter);
                                if (it == info.templateParameterMap.end())
                                {
                                    templateArgumentType = argTypeSymbol->RemoveDerivations(templateTypeSymbol->GetDerivations(), context);
                                    if (templateArgumentType)
                                    {
                                        info.templateParameterMap[templateParameter] = templateArgumentType;
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
                            }
                            templateTypeSymbol = templateTypeSymbol->Unify(templateArgumentType, context);
                            if (!templateTypeSymbol)
                            {
                                return -1;
                            }
                            if (!TypesEqual(argTypeSymbol, templateTypeSymbol, context))
                            {
                                return -1;
                            }
                        }
                    }
                    info.kind = TemplateMatchKind::explicitSpecialization;
                    return 1;
                }
            }
        }
    }
    return -1;
}

std::vector<Symbol*> MakeTemplateArgs(const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParamMap)
{
    std::vector<Symbol*> templateArgs;
    for (const auto& p : templateParamMap)
    {
        templateArgs.push_back(p.second);
    }
    return templateArgs;
}

ClassTypeSymbol* ClassGroupSymbol::GetBestMatchingClass(const std::vector<Symbol*>& templateArgs, TemplateMatchInfo& matchInfo, Context* context) const noexcept
{
    std::vector<std::pair<ClassTypeSymbol*, TemplateMatchInfo>> viableClasses;
    int arity = templateArgs.size();
    for (ClassTypeSymbol* cls : classes)
    {
        if (cls->Arity() == arity)
        {
            TypeSymbol* specialization = cls->Specialization();
            if (specialization)
            {
                int score = -1;
                TemplateMatchInfo info;
                for (int i = 0; i < arity; ++i)
                {
                    Symbol* templateArg = templateArgs[i];
                    int matchValue = Match(templateArg, specialization, i, info, context);
                    if (matchValue >= 0)
                    {
                        score += 2 * matchValue;
                    }
                }
                info.matchValue = score;
                viableClasses.push_back(std::make_pair(cls, info));
            }
            else
            {
                TemplateMatchInfo info;
                viableClasses.push_back(std::make_pair(cls, info));
            }
        }
    }
    std::sort(viableClasses.begin(), viableClasses.end(), ViableClassGreater());
    if (!viableClasses.empty())
    {
        matchInfo = viableClasses[0].second;
        if (matchInfo.kind == TemplateMatchKind::explicitSpecialization)
        {
            matchInfo.templateArgs = MakeTemplateArgs(matchInfo.templateParameterMap);
        }
        return viableClasses[0].first;
    }
    return nullptr;
}

} // namespace otava::symbols
