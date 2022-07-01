// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.symbol;

import soul.cpp20.symbols.declaration;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.templates;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.value;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.alias.group.symbol;
import soul.cpp20.symbols.concept_group.symbol;
import soul.cpp20.symbols.class_group.symbol;
import soul.cpp20.symbols.function.group.symbol;
import soul.cpp20.symbols.variable.group.symbol;
import util.unicode;

namespace soul::cpp20::symbols {

std::vector<SymbolGroupKind> SymbolGroupKindstoSymbolGroupKindVec(SymbolGroupKind symbolGroupKinds)
{
    std::vector<SymbolGroupKind> symbolGroupKindVec;
    if ((symbolGroupKinds & SymbolGroupKind::functionSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::functionSymbolGroup);
    }
    if ((symbolGroupKinds & SymbolGroupKind::typeSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::typeSymbolGroup);
    }
    if ((symbolGroupKinds & SymbolGroupKind::variableSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::variableSymbolGroup);
    }
    if ((symbolGroupKinds & SymbolGroupKind::conceptSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::conceptSymbolGroup);
    }
    if ((symbolGroupKinds & SymbolGroupKind::blockSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::blockSymbolGroup);
    }
    return symbolGroupKindVec;
}

Symbol::Symbol(SymbolKind kind_, const std::u32string& name_) : kind(kind_), id(util::random_uuid()), name(name_), parent(nullptr)
{
}

Symbol::~Symbol()
{
}

std::u32string Symbol::FullName() const
{
    std::u32string fullName;
    if (parent)
    {
        fullName = parent->FullName();
    }
    if (!fullName.empty())
    {
        fullName.append(U"::");
    }
    fullName.append(name);
    return fullName;
}

void Symbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot add " + symbol->SymbolKindStr() + " '" + util::ToUtf8(symbol->FullName()) + "' to " + SymbolKindStr() + " '" + util::ToUtf8(FullName()), 
        sourcePos, context);
}

void Symbol::RemoveSymbol(Symbol* symbol)
{
    throw std::runtime_error("cannot remove symbol");
}

void Symbol::Write(Writer& writer)
{
    writer.GetBinaryStreamWriter().Write(id);
    soul::cpp20::symbols::Write(writer, declarationFlags);
}

void Symbol::Read(Reader& reader)
{
    reader.GetBinaryStreamReader().ReadUuid(id);
    soul::cpp20::symbols::Read(reader, declarationFlags);
}

void Symbol::Resolve(SymbolTable& symbolTable)
{
}

bool Symbol::CanInstall() const
{
    switch (kind)
    {
        case SymbolKind::aliasTypeSymbol:
        case SymbolKind::classTypeSymbol:
        case SymbolKind::conceptSymbol:
        case SymbolKind::functionSymbol:
        case SymbolKind::parameterSymbol:
        case SymbolKind::variableSymbol:
        case SymbolKind::templateDeclarationSymbol:
        {
            return false; 
        }
        case SymbolKind::templateParameterSymbol:
        {
            return !Name().empty();
        }
    }
    return true;
}

bool Symbol::IsTypeSymbol() const
{
    switch (kind)
    {
        case SymbolKind::aliasGroupSymbol: 
        case SymbolKind::classGroupSymbol:
        case SymbolKind::aliasTypeSymbol:
        case SymbolKind::arrayTypeSymbol:
        case SymbolKind::classTypeSymbol:
        case SymbolKind::compoundTypeSymbol:
        case SymbolKind::enumTypeSymbol:
        case SymbolKind::errorSymbol:
        case SymbolKind::functionTypeSymbol:
        case SymbolKind::fundamentalTypeSymbol:
        case SymbolKind::genericTypeSymbol:
        case SymbolKind::nullPtrTypeSymbol:
        case SymbolKind::templateParameterSymbol:
        case SymbolKind::varArgTypeSymbol:
        {
            return true;
        }
    }
    return false;
}

SymbolGroupKind Symbol::GetSymbolGroupKind() const
{
    switch (kind)
    {
        case SymbolKind::aliasGroupSymbol:
        case SymbolKind::classGroupSymbol:
        case SymbolKind::namespaceSymbol:
        case SymbolKind::aliasTypeSymbol:
        case SymbolKind::classTypeSymbol:
        case SymbolKind::compoundTypeSymbol:
        case SymbolKind::fundamentalTypeSymbol:
        {
            return SymbolGroupKind::typeSymbolGroup;
        }
        case SymbolKind::conceptGroupSymbol:
        {
            return SymbolGroupKind::conceptSymbolGroup;
        }
        case SymbolKind::functionGroupSymbol:
        {
            return SymbolGroupKind::functionSymbolGroup;
        }
        case SymbolKind::variableGroupSymbol:
        {
            return SymbolGroupKind::variableSymbolGroup;
        }
    }
    return SymbolGroupKind::none;
}

bool SymbolsEqual(Symbol* left, Symbol* right)
{
    if (left->IsTypeSymbol() && right->IsTypeSymbol())
    {
        if (left->Kind() == SymbolKind::errorSymbol && right->Kind() == SymbolKind::errorSymbol) return true;
        if (left->Kind() == SymbolKind::templateParameterSymbol && right->Kind() == SymbolKind::templateParameterSymbol)
        {
            TemplateParameterSymbol* leftTemplateParam = static_cast<TemplateParameterSymbol*>(left);
            TemplateParameterSymbol* rightTemplateParam = static_cast<TemplateParameterSymbol*>(right);
            return leftTemplateParam->Index() == rightTemplateParam->Index();
        }
        if (left->IsCompoundTypeSymbol() && right->IsCompoundTypeSymbol())
        {
            if (left->Kind() != right->Kind()) return false;
            CompoundTypeSymbol* leftCompound = static_cast<CompoundTypeSymbol*>(left);
            CompoundTypeSymbol* rightCompound = static_cast<CompoundTypeSymbol*>(right);
            return SymbolsEqual(leftCompound->BaseType(), rightCompound->BaseType());
        }
        return left == right;
    }
    else if (left->Kind() == SymbolKind::boolValueSymbol && right->Kind() == SymbolKind::boolValueSymbol)
    {
        BoolValue* leftValue = static_cast<BoolValue*>(left);
        BoolValue* rightValue = static_cast<BoolValue*>(right);
        return leftValue->GetValue() == rightValue->GetValue();
    }
    else if (left->Kind() == SymbolKind::integerValueSymbol && right->Kind() == SymbolKind::integerValueSymbol)
    {
        IntegerValue* leftInteger = static_cast<IntegerValue*>(left);
        IntegerValue* rightInteger = static_cast<IntegerValue*>(right);
        return leftInteger->GetValue() == rightInteger->GetValue();
    }
    else
    {
        return left == right;
    }
}

bool SymbolsEqual(const std::vector<Symbol*>& left, const std::vector<Symbol*>& right)
{
    if (left.size() != right.size()) return false;
    int n = left.size();
    for (int i = 0; i < n; ++i)
    {
        if (!SymbolsEqual(left[i], right[i])) return false;
    }
    return true;
}

int Match(const std::vector<Symbol*>& left, const std::vector<Symbol*>& right)
{
    if (left.size() != right.size()) return -1;
    int totalScore = 0;
    int n = left.size();
    for (int i = 0; i < n; ++i)
    {
        int score = Match(left[i], right[i]);
        if (score == -1) return -1;
        totalScore += score;
    }
    return totalScore;
}

int Match(Symbol* left, Symbol* right)
{
    if (SymbolsEqual(left, right)) return 0;
    if (left->IsCompoundTypeSymbol())
    {
        if (right->IsCompoundTypeSymbol())
        {
            if (left->Kind() == right->Kind())
            {
                CompoundTypeSymbol* leftCompound = static_cast<CompoundTypeSymbol*>(left);
                CompoundTypeSymbol* rightCompound = static_cast<CompoundTypeSymbol*>(right);
                return Match(leftCompound->BaseType(), rightCompound->BaseType());
            }
            else
            {
                return -1;
            }
        }
        else if (right->Kind() == SymbolKind::templateParameterSymbol)
        {
            return 2;
        }
    }
    else if (right->Kind() == SymbolKind::templateParameterSymbol)
    {
        return 1;
    }
    return -1;
}

Symbol* CreateSymbol(SymbolKind symbolKind, const std::u32string& name)
{
    switch (symbolKind)
    {
        case SymbolKind::classGroupSymbol:
        {
            return new ClassGroupSymbol(name);
        }
        case SymbolKind::conceptGroupSymbol:
        {
            return new ConceptGroupSymbol(name);
        }
        case SymbolKind::functionGroupSymbol:
        {
            return new FunctionGroupSymbol(name);
        }
        case SymbolKind::variableGroupSymbol:
        {
            return new VariableGroupSymbol(name);
        }
        case SymbolKind::aliasGroupSymbol:
        {
            return new AliasGroupSymbol(name);
        }
        case SymbolKind::boolValueSymbol:
        {
            return new BoolValue(name);
        }
        case SymbolKind::integerValueSymbol:
        {
            return new IntegerValue(name);
        }
        case SymbolKind::floatingValueSymbol:
        {
            return new FloatingValue(name);
        }
    }
    return nullptr;
}

} // namespace soul::cpp20::symbols
