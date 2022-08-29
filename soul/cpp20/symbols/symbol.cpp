// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.symbol;

import soul.cpp20.symbols.alias.type.symbol;
import soul.cpp20.symbols.block;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.concepts;
import soul.cpp20.symbols.declaration;
import soul.cpp20.symbols.enums;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.fundamental.type.symbol;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.templates;
import soul.cpp20.symbols.variable.symbol;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.value;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.alias.group.symbol;
import soul.cpp20.symbols.concept_group.symbol;
import soul.cpp20.symbols.class_group.symbol;
import soul.cpp20.symbols.function.group.symbol;
import soul.cpp20.symbols.variable.group.symbol;
import soul.cpp20.symbols.specialization;
import soul.cpp20.symbols.symbol.table;
import util.unicode;
import util.sha1;

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
    if ((symbolGroupKinds & SymbolGroupKind::enumConstantSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::enumConstantSymbolGroup);
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

std::string AccessStr(Access access)
{
    switch (access)
    {
        case Access::private_:
        {
            return "private";
        }
        case Access::protected_:
        {
            return "protected";
        }
        case Access::public_:
        {
            return "public";
        }
    }
    return std::string();
}

Symbol::Symbol(SymbolKind kind_, const std::u32string& name_) : kind(kind_), id(util::random_uuid()), name(name_), parent(nullptr), access(Access::none)
{
}

Symbol::~Symbol()
{
}

void Symbol::SetName(const std::u32string& name_)
{
    name = name_;
}

std::u32string Symbol::FullName() const
{
    std::u32string fullName;
    if (parent)
    {
        fullName = parent->FullName();
    }
    if (!fullName.empty() && !name.empty())
    {
        fullName.append(U"::");
    }
    if (!name.empty())
    {
        fullName.append(name);
    }
    return fullName;
}

void Symbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add " + symbol->SymbolKindStr() + " '" + util::ToUtf8(symbol->FullName()) + "' to " + SymbolKindStr() + " '" + util::ToUtf8(FullName()), 
        sourcePos, context);
}

std::unique_ptr<Symbol> Symbol::RemoveSymbol(Symbol* symbol)
{
    throw std::runtime_error("cannot remove symbol");
}

void Symbol::Write(Writer& writer)
{
    writer.GetBinaryStreamWriter().Write(id);
    soul::cpp20::symbols::Write(writer, declarationFlags);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(access));
}

void Symbol::Read(Reader& reader)
{
    reader.GetBinaryStreamReader().ReadUuid(id);
    soul::cpp20::symbols::Read(reader, declarationFlags);
    access = static_cast<Access>(reader.GetBinaryStreamReader().ReadByte());
}

void Symbol::Resolve(SymbolTable& symbolTable)
{
}

SymbolTable* Symbol::GetSymbolTable() 
{
    NamespaceSymbol* ns = ParentNamespace();
    if (ns)
    {
        return ns->GetSymbolTable();
    }
    return nullptr;
}

Module* Symbol::GetModule()
{
    SymbolTable* symbolTable = GetSymbolTable();
    if (symbolTable)
    {
        return symbolTable->GetModule();
    }
    return nullptr;
}

ClassTypeSymbol* Symbol::ParentClass() const
{
    Symbol* parentSymbol = parent;
    while (parentSymbol)
    {
        if (parentSymbol->IsClassTypeSymbol())
        {
            return static_cast<ClassTypeSymbol*>(parentSymbol);
        }
        parentSymbol = parentSymbol->Parent();
    }
    return nullptr;
}

NamespaceSymbol* Symbol::ParentNamespace() const
{
    Symbol* parentSymbol = parent;
    while (parentSymbol)
    {
        if (parentSymbol->IsNamespaceSymbol())
        {
            return static_cast<NamespaceSymbol*>(parentSymbol);
        }
        parentSymbol = parentSymbol->Parent();
    }
    return nullptr;
}

std::string Symbol::DocName() const
{
    std::string docName = SymbolDocKindStr();
    docName.append("_").append(util::ToUtf8(Name())).append("_").append(util::GetSha1MessageDigest(util::ToUtf8(FullName())));
    return docName;
}

bool Symbol::CanInstall() const
{
    switch (kind)
    {
        case SymbolKind::aliasTypeSymbol:
        case SymbolKind::blockSymbol:
        case SymbolKind::classTypeSymbol:
        case SymbolKind::conceptSymbol:
        case SymbolKind::functionSymbol:
        case SymbolKind::parameterSymbol:
        case SymbolKind::variableSymbol:
        case SymbolKind::templateDeclarationSymbol:
        case SymbolKind::typenameConstraintSymbol:
        case SymbolKind::forwardClassDeclarationSymbol:
        {
            return false; 
        }
        case SymbolKind::functionTypeSymbol:
        case SymbolKind::templateParameterSymbol:
        case SymbolKind::boundTemplateParameterSymbol:
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
        case SymbolKind::forwardClassDeclarationSymbol:
        case SymbolKind::specializationSymbol:
        case SymbolKind::compoundTypeSymbol:
        case SymbolKind::enumTypeSymbol:
        case SymbolKind::errorSymbol:
        case SymbolKind::nestedTypeSymbol:
        case SymbolKind::functionTypeSymbol:
        case SymbolKind::fundamentalTypeSymbol:
        case SymbolKind::genericTypeSymbol:
        case SymbolKind::nullPtrTypeSymbol:
        case SymbolKind::templateParameterSymbol:
        case SymbolKind::boundTemplateParameterSymbol:
        case SymbolKind::varArgTypeSymbol:
        {
            return true;
        }
    }
    return false;
}

bool Symbol::IsValueSymbol() const
{
    switch (kind)
    {
        case SymbolKind::boolValueSymbol:
        case SymbolKind::integerValueSymbol:
        case SymbolKind::floatingValueSymbol:
        case SymbolKind::nullPtrValueSymbol:
        case SymbolKind::symbolValueSymbol:
        case SymbolKind::invokeValueSymbol:
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
        case SymbolKind::forwardClassDeclarationSymbol:
        case SymbolKind::compoundTypeSymbol:
        case SymbolKind::enumTypeSymbol:
        case SymbolKind::fundamentalTypeSymbol:
        case SymbolKind::templateParameterSymbol:
        case SymbolKind::boundTemplateParameterSymbol:
        case SymbolKind::nestedTypeSymbol:
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
        case SymbolKind::enumConstantSymbol:
        {
            return SymbolGroupKind::enumConstantSymbolGroup;
        }
        case SymbolKind::templateDeclarationSymbol:
        {
            return SymbolGroupKind::blockSymbolGroup;
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
        case SymbolKind::nullPtrValueSymbol:
        {
            return new NullPtrValue();
        }
        case SymbolKind::genericTypeSymbol:
        {
            throw std::runtime_error("not implemented");
        }
        case SymbolKind::nullPtrTypeSymbol:
        {
            throw std::runtime_error("not implemented");
        }
        case SymbolKind::aliasTypeSymbol:
        {
            return new AliasTypeSymbol(name);
        }
        case SymbolKind::arrayTypeSymbol:
        {
            throw std::runtime_error("not implemented");
        }
        case SymbolKind::blockSymbol:
        {
            return new BlockSymbol();
        }
        case SymbolKind::classTypeSymbol:
        {
            return new ClassTypeSymbol(name);
        }
        case SymbolKind::forwardClassDeclarationSymbol:
        {
            return new ForwardClassDeclarationSymbol(name);
        }
        case SymbolKind::compoundTypeSymbol:
        {
            return new CompoundTypeSymbol(name);
        }
        case SymbolKind::conceptSymbol:
        {
            return new ConceptSymbol(name);
        }
        case SymbolKind::enumTypeSymbol:
        {
            return new EnumeratedTypeSymbol(name);
        }
        case SymbolKind::enumConstantSymbol:
        {
            return new EnumConstantSymbol(name);
        }
        case SymbolKind::functionSymbol:
        {
            return new FunctionSymbol(name);
        }
        case SymbolKind::functionTypeSymbol:
        {
            return new FunctionTypeSymbol(name);
        }
        case SymbolKind::fundamentalTypeSymbol:
        {
            return new FundamentalTypeSymbol(name);
        }
        case SymbolKind::namespaceSymbol:
        {
            return new NamespaceSymbol(name);
        }
        case SymbolKind::templateDeclarationSymbol:
        {
            return new TemplateDeclarationSymbol();
        }
        case SymbolKind::typenameConstraintSymbol:
        {
            return new TypenameConstraintSymbol();
        }
        case SymbolKind::templateParameterSymbol:
        {
            return new TemplateParameterSymbol(name);
        }
        case SymbolKind::varArgTypeSymbol:
        {
            throw std::runtime_error("not implemented");
        }
        case SymbolKind::variableSymbol:
        {
            return new VariableSymbol(name);
        }
        case SymbolKind::parameterSymbol:
        {
            return new ParameterSymbol(name);
        }
        case SymbolKind::specializationSymbol:
        {
            return new SpecializationSymbol(name);
        }
        case SymbolKind::nestedTypeSymbol:
        {
            return new NestedTypeSymbol(name);
        }
        case SymbolKind::errorSymbol:
        {
            return new ErrorTypeSymbol();
        }
        case SymbolKind::symbolValueSymbol:
        {
            return new SymbolValue();
        }
        case SymbolKind::invokeValueSymbol:
        {
            return new InvokeValue();
        }
    }
    return nullptr;
}

} // namespace soul::cpp20::symbols
