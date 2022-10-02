// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.specialization;

import otava.symbols.modules;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.value;

namespace otava::symbols {

SpecializationSymbol::SpecializationSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::specializationSymbol, name_), instantiated(false), symbolTable(nullptr)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

void SpecializationSymbol::SetClassTemplate(TypeSymbol* classTemplate_)
{
    classTemplate = classTemplate_;
}

void SpecializationSymbol::AddTemplateArgument(Symbol* templateArgument)
{
    templateArguments.push_back(templateArgument);
}

void SpecializationSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
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

void SpecializationSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
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

void SpecializationSymbol::Resolve(SymbolTable& symbolTable)
{
    // note: not calling TypeSymbol::Resolve(symbolTable); on purpose
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

void SpecializationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SymbolTable* SpecializationSymbol::GetSymbolTable()
{
    return classTemplate->GetSymbolTable();
}

std::u32string MakeSpecializationName(TypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments)
{
    std::u32string specializationName;
    specializationName.append(classTemplate->Name());
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

} // namespace otava::symbols
