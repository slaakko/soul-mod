// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.specialization;

import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.symbol.table;

namespace soul::cpp20::symbols {

SpecializationSymbol::SpecializationSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::specializationSymbol, name_)
{
}

void SpecializationSymbol::SetClassTemplate(TypeSymbol* classTemplate_)
{
    classTemplate = classTemplate_;
}

void SpecializationSymbol::AddTemplateArgument(TypeSymbol* templateArgument)
{
    templateArguments.push_back(templateArgument);
}

void SpecializationSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(classTemplate->Id());
    writer.GetBinaryStreamWriter().WriteULEB128UInt(templateArguments.size());
    for (TypeSymbol* templateArg : templateArguments)
    {
        writer.GetBinaryStreamWriter().Write(templateArg->Id());
    }
}

void SpecializationSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    util::uuid id;
    reader.GetBinaryStreamReader().ReadUuid(id);
    ids.push_back(id);
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        util::uuid id;
        reader.GetBinaryStreamReader().ReadUuid(id);
        ids.push_back(id);
    }
}

void SpecializationSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    classTemplate = static_cast<ClassTypeSymbol*>(symbolTable.GetType(ids[0]));
    for (int i = 1; i < ids.size(); ++i)
    {
        TypeSymbol* templateArg = symbolTable.GetType(ids[i]);
        templateArguments.push_back(templateArg);
    }
}

void SpecializationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::u32string MakeSpecializationName(TypeSymbol* classTemplate, const std::vector<TypeSymbol*>& templateArguments)
{
    std::u32string specializationName;
    specializationName.append(classTemplate->Name());
    specializationName.append(1, '<');
    bool first = true;
    for (TypeSymbol* templateArg : templateArguments)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            specializationName.append(1, ',');
        }
        specializationName.append(templateArg->Name());
    }
    specializationName.append(1, '>');
    return specializationName;
}

} // namespace soul::cpp20::symbols
