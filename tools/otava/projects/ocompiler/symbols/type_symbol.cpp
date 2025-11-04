// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.type.symbol;

import otava.symbols.symbol.table;
import otava.symbols.visitor;
import otava.symbols.compound.type.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.error;
import otava.symbols.context;
import otava.symbols.writer;
import otava.symbols.reader;

namespace otava::symbols {

TypeSymbol::TypeSymbol(SymbolKind kind_, const std::u32string& name_) : ContainerSymbol(kind_, name_)
{
}

TypeSymbol::TypeSymbol(SymbolKind kind_, const util::uuid& id_, const std::u32string& name_) : ContainerSymbol(kind_, id_, name_)
{
}

bool TypeSymbol::IsAutoTypeSymbol() const
{
    if (IsFundamentalTypeSymbol())
    {
        const FundamentalTypeSymbol* fundamentalTypeSymbol = static_cast<const FundamentalTypeSymbol*>(this);
        return fundamentalTypeSymbol->IsAutoTypeSymbol();
    }
    return false;
}

bool TypeSymbol::IsPointerType() const
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return otava::symbols::PointerCount(compoundTypeSymbol->GetDerivations()) > 0;
    }
    return false;
}

bool TypeSymbol::IsArrayType() const
{
    return Kind() == SymbolKind::arrayTypeSymbol;
}

bool TypeSymbol::IsConstType() const
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivations::constDerivation);
    }
    return false;
}

bool TypeSymbol::IsLValueRefType() const
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivations::lvalueRefDerivation);
    }
    return false;
}

bool TypeSymbol::IsRValueRefType() const
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivations::rvalueRefDerivation);
    }
    return false;
}

bool TypeSymbol::IsReferenceType() const
{
    return IsLValueRefType() || IsRValueRefType();
}

std::expected<TypeSymbol*, int> TypeSymbol::AddConst(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations = Derivations::constDerivation;
    return symbolTable->MakeCompoundType(this, derivations);
}

std::expected<TypeSymbol*, int> TypeSymbol::RemoveConst(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveConst(compoundTypeSymbol->GetDerivations()));
    }
    return std::expected<TypeSymbol*, int>(this);
}

std::expected<TypeSymbol*, int> TypeSymbol::AddPointer(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations = Derivations::none;
    derivations = otava::symbols::SetPointerCount(derivations, 1);
    return symbolTable->MakeCompoundType(this, derivations);
}

std::expected<TypeSymbol*, int>TypeSymbol::RemovePointer(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemovePointer(compoundTypeSymbol->GetDerivations()));
    }
    return std::expected<TypeSymbol*, int>(this);
}

std::expected<TypeSymbol*, int> TypeSymbol::AddLValueRef(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations = Derivations::lvalueRefDerivation;
    return symbolTable->MakeCompoundType(this, derivations);
}

std::expected<TypeSymbol*, int> TypeSymbol::RemoveLValueRef(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveLValueRef(compoundTypeSymbol->GetDerivations()));
    }
    return std::expected<TypeSymbol*, int>(this);
}

std::expected<TypeSymbol*, int> TypeSymbol::AddRValueRef(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations = Derivations::rvalueRefDerivation;
    return symbolTable->MakeCompoundType(this, derivations);
}

std::expected<TypeSymbol*, int> TypeSymbol::RemoveRValueRef(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveRValueRef(compoundTypeSymbol->GetDerivations()));
    }
    return std::expected<TypeSymbol*, int>(this);
}

std::expected<TypeSymbol*, int> TypeSymbol::RemoveReference(Context* context)
{
    if (IsLValueRefType())
    {
        return RemoveLValueRef(context);
    }
    else if (IsRValueRefType())
    {
        return RemoveRValueRef(context);
    }
    else
    {
        return this;
    }
}

std::expected<TypeSymbol*, int> TypeSymbol::RemoveRefOrPtr(Context* context)
{
    if (IsReferenceType())
    {
        return PlainType(context);
    }
    else if (IsPointerType())
    {
        return RemovePointer(context);
    }
    return this;
}

std::expected<TypeSymbol*, int> TypeSymbol::RemoveDerivations(Derivations derivations, Context* context)
{
    if (IsPointerType()) return std::expected<TypeSymbol*, int>(nullptr);
    return std::expected<TypeSymbol*, int>(this);
}

std::expected<TypeSymbol*, int> TypeSymbol::Unify(TypeSymbol* argType, Context* context)
{
    return std::expected<TypeSymbol*, int>(nullptr);
}

std::expected<otava::intermediate::Type*, int> TypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return Error("IRTYPE not implemented", sourcePos, context);
}

std::expected<bool, int> TypeSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return ContainerSymbol::AddSymbol(symbol, sourcePos, context);
}

NestedTypeSymbol::NestedTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::nestedTypeSymbol, name_)
{
}

std::string NestedTypeSymbol::SymbolKindStr() const 
{ 
    return "nested type symbol"; 
}

std::string NestedTypeSymbol::SymbolDocKindStr() const 
{ 
    return "nested_type"; 
}

void NestedTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DependentTypeSymbol::DependentTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::dependentTypeSymbol, name_), node()
{
}

DependentTypeSymbol::DependentTypeSymbol(otava::ast::Node* node_) : TypeSymbol(SymbolKind::dependentTypeSymbol, U"@dependent_type"), node(node_)
{
    if (node->IsTypenameSpecifierNode())
    {
        otava::ast::TypenameSpecifierNode* s = static_cast<otava::ast::TypenameSpecifierNode*>(node.get());
        SetName(s->Id()->Str());
    }
}

std::string DependentTypeSymbol::SymbolKindStr() const 
{ 
    return "dependent type symbol"; 
}

std::string DependentTypeSymbol::SymbolDocKindStr() const 
{ 
    return "dependent_type"; 
}

std::expected<bool, int> DependentTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    otava::ast::Writer astWriter(&writer.GetBinaryStreamWriter());
    rv = astWriter.Write(node.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DependentTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    otava::ast::Reader astReader(&reader.GetBinaryStreamReader());
    astReader.SetNodeMap(reader.GetSymbolTable()->GetNodeMap());
    std::expected<otava::ast::Node*, int> n = astReader.ReadNode();
    if (!n) return std::unexpected<int>(n.error());
    node.reset(*n);
    return std::expected<bool, int>(true);
}

void DependentTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ErrorTypeSymbol::ErrorTypeSymbol() : TypeSymbol(SymbolKind::errorSymbol, U"<error_type>")
{
}

std::string ErrorTypeSymbol::SymbolKindStr() const 
{ 
    return "error type symbol"; 
}

std::string ErrorTypeSymbol::SymbolDocKindStr() const 
{ 
    return "error_type"; 
}

void ErrorTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FunctionGroupTypeSymbol::FunctionGroupTypeSymbol(FunctionGroupSymbol* functionGroupSymbol_) :
    TypeSymbol(SymbolKind::functionGroupTypeSymbol, U"@function_group_type"), functionGroupSymbol(functionGroupSymbol_)
{
}

FunctionGroupTypeSymbol::FunctionGroupTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::functionGroupTypeSymbol, name_), functionGroupSymbol(nullptr)
{
}

std::string FunctionGroupTypeSymbol::SymbolKindStr() const 
{ 
    return "function group type symbol"; 
}

std::string FunctionGroupTypeSymbol::SymbolDocKindStr() const 
{ 
    return "function_group_type"; 
}

std::expected<bool, int> FunctionGroupTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(functionGroupSymbol->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionGroupTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(functionGroupSymbolId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionGroupTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    std::expected<FunctionGroupSymbol*, int> f = symbolTable.GetFunctionGroup(functionGroupSymbolId);
    if (!f) return std::unexpected<int>(f.error());
    functionGroupSymbol = *f;
    return std::expected<bool, int>(true);
}

void FunctionGroupTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ClassGroupTypeSymbol::ClassGroupTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::classGroupTypeSymbol, name_), classGroupSymbol(nullptr)
{
}

ClassGroupTypeSymbol::ClassGroupTypeSymbol(ClassGroupSymbol* classGroupSymbol_) :
    TypeSymbol(SymbolKind::classGroupTypeSymbol, U"@classGroupType:" + classGroupSymbol_->Name()), classGroupSymbol(classGroupSymbol_)
{
}

std::string ClassGroupTypeSymbol::SymbolKindStr() const 
{ 
    return "class group type symbol"; 
}

std::string ClassGroupTypeSymbol::SymbolDocKindStr() const 
{ 
    return "class_group_type"; 
}

std::expected<bool, int> ClassGroupTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(classGroupSymbol->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ClassGroupTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(classGroupSymbolId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ClassGroupTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    std::expected<ClassGroupSymbol*, int> c = symbolTable.GetClassGroup(classGroupSymbolId);
    if (!c) return std::unexpected<int>(c.error());
    classGroupSymbol = *c;
    return std::expected<bool, int>(true);
}

void ClassGroupTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AliasGroupTypeSymbol::AliasGroupTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::aliasGroupTypeSymbol, name_), aliasGroupSymbol(nullptr)
{
}

AliasGroupTypeSymbol::AliasGroupTypeSymbol(AliasGroupSymbol* aliasGroupSymbol_) :
    TypeSymbol(SymbolKind::aliasGroupTypeSymbol, U"@alias_group_type"), aliasGroupSymbol(aliasGroupSymbol_)
{
}

std::string AliasGroupTypeSymbol::SymbolKindStr() const 
{ 
    return "alias group type symbol"; 
}

std::string AliasGroupTypeSymbol::SymbolDocKindStr() const 
{ 
    return "alias_group_type"; 
}

std::expected<bool, int> AliasGroupTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(aliasGroupSymbol->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AliasGroupTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(aliasGroupSymbolId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AliasGroupTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    std::expected<AliasGroupSymbol*, int> a = symbolTable.GetAliasGroup(aliasGroupSymbolId);
    if (!a) return std::unexpected<int>(a.error());
    aliasGroupSymbol = *a;
    return std::expected<bool, int>(true);
}

void AliasGroupTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeSymbol* GenericTypeSymbol::Instance()
{
    static GenericTypeSymbol instance;
    return &instance;
}

GenericTypeSymbol::GenericTypeSymbol() : TypeSymbol(SymbolKind::genericTypeSymbol, U"@generic_type")
{
}

std::string GenericTypeSymbol::SymbolKindStr() const 
{ 
    return "generic type symbol"; 
}

std::string GenericTypeSymbol::SymbolDocKindStr() const 
{ 
    return "generic_type"; 
}

void GenericTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::symbols
