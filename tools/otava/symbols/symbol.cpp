// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.symbol;

import otava.ast.error;
import otava.symbols.alias.type.symbol;
import otava.symbols.block;
import otava.symbols.classes;
import otava.symbols.concepts;
import otava.symbols.declaration;
import otava.symbols.emitter;
import otava.symbols.enums;
import otava.symbols.exception;
import otava.symbols.function.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.namespaces;
import otava.symbols.templates;
import otava.symbols.variable.symbol;
import otava.symbols.compound.type.symbol;
import otava.symbols.value;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.alias.group.symbol;
import otava.symbols.concept_group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.variable.group.symbol;
import otava.symbols.enum_group.symbol;
import otava.symbols.symbol.table;
import util.unicode;
import util.sha1;

namespace otava::symbols {

SymbolDestroyedFunc symbolDestroyedFunc = nullptr;

void SetSymbolDestroyedFunc(SymbolDestroyedFunc func)
{
    symbolDestroyedFunc = func;
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

std::string SymbolGroupStr(SymbolGroupKind group)
{
    std::string groupStr;
    if ((group & SymbolGroupKind::functionSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("functionSymbolGroup");
    }
    if ((group & SymbolGroupKind::typeSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("typeSymbolGroup");
    }
    if ((group & SymbolGroupKind::variableSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("variableSymbolGroup");
    }
    if ((group & SymbolGroupKind::enumConstantSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("enumConstantSymbolGroup");
    }
    if ((group & SymbolGroupKind::conceptSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("conceptSymbolGroup");
    }
    if ((group & SymbolGroupKind::blockSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("blockSymbolGroup");
    }
    return groupStr;
}

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

std::string SymbolKindToString(SymbolKind kind)
{
    switch (kind)
    {
        case SymbolKind::null: return "null";
        case SymbolKind::classGroupSymbol: return "classGroup"; 
        case SymbolKind::conceptGroupSymbol: return "conceptGroup";
        case SymbolKind::functionGroupSymbol: return "functionGroup";
        case SymbolKind::variableGroupSymbol: return "variableGroup";
        case SymbolKind::aliasGroupSymbol: return "aliasGroup";
        case SymbolKind::enumGroupSymbol: return "enumGroup";
        case SymbolKind::boolValueSymbol: return "boolValue";
        case SymbolKind::integerValueSymbol: return "integerValue";
        case SymbolKind::floatingValueSymbol: return "floatingValue";
        case SymbolKind::stringValueSymbol: return "stringValue";
        case SymbolKind::charValueSymbol: return "charValue";
        case SymbolKind::genericTypeSymbol: return "genericType";
        case SymbolKind::nullPtrTypeSymbol: return "nullPtrType";
        case SymbolKind::arrayValueSymbol: return "arrayValue";
        case SymbolKind::structureValueSymbol: return "structureValue";
        case SymbolKind::aliasTypeSymbol: return "aliasType";
        case SymbolKind::arrayTypeSymbol: return "arrayType";
        case SymbolKind::blockSymbol: return "block";
        case SymbolKind::classTypeSymbol: return "classType";
        case SymbolKind::compoundTypeSymbol: return "compoundType";
        case SymbolKind::conceptSymbol: return "concept";
        case SymbolKind::enumTypeSymbol: return "enumType";
        case SymbolKind::enumConstantSymbol: return "enumConstant";
        case SymbolKind::functionSymbol: return "function";
        case SymbolKind::functionTypeSymbol: return "functionType";
        case SymbolKind::functionDefinitionSymbol: return "functionDefinition";
        case SymbolKind::explicitlyInstantiatedFunctionDefinitionSymbol: return "explicitlyInstantiatedFunctionDefinition";
        case SymbolKind::fundamentalTypeSymbol: return "fundamentalType";
        case SymbolKind::namespaceSymbol: return "namespace";
        case SymbolKind::templateDeclarationSymbol: return "templateDeclaration";
        case SymbolKind::typenameConstraintSymbol: return "typenameConstraint";
        case SymbolKind::explicitInstantiationSymbol: return "explicitInstantiation";
        case SymbolKind::templateParameterSymbol: return "templateParameter";
        case SymbolKind::varArgTypeSymbol: return "varArgType";
        case SymbolKind::variableSymbol: return "variable";
        case SymbolKind::parameterSymbol: return "parameter";
        case SymbolKind::errorSymbol: return "error";
        case SymbolKind::classTemplateSpecializationSymbol: return "classTemplateSpecialization";
        case SymbolKind::aliasTypeTemplateSpecializationSymbol: return "aliasTypeTemplateSpecialization";
        case SymbolKind::nestedTypeSymbol: return "nestedType";
        case SymbolKind::dependentTypeSymbol: return "dependentType";
        case SymbolKind::nullPtrValueSymbol: return "nullPtrValue";
        case SymbolKind::symbolValueSymbol: return "symbolValue";
        case SymbolKind::invokeValueSymbol: return "invokeValue";
        case SymbolKind::forwardClassDeclarationSymbol: return "forwardClassDeclaration";
        case SymbolKind::forwardEnumDeclarationSymbol: return "forwardEnumDeclaration";
        case SymbolKind::boundTemplateParameterSymbol: return "boundTemplateParameter";
        case SymbolKind::constraintExprSymbol: return "constraintExpr";
        case SymbolKind::fundamentalTypeNot: return "fundamentalTypeNot";
        case SymbolKind::fundamentalTypeUnaryPlus: return "fundamentalTypeUnaryPlus";
        case SymbolKind::fundamentalTypeUnaryMinus: return "fundamentalTypeUnaryMinus";
        case SymbolKind::fundamentalTypeComplement: return "fundamentalTypeComplement";
        case SymbolKind::fundamentalTypeAdd: return "fundamentalTypeAdd";
        case SymbolKind::fundamentalTypeSub: return "fundamentalTypeSub";
        case SymbolKind::fundamentalTypeMul: return "fundamentalTypeMul";
        case SymbolKind::fundamentalTypeDiv: return "fundamentalTypeDiv";
        case SymbolKind::fundamentalTypeMod: return "fundamentalTypeMod";
        case SymbolKind::fundamentalTypeAnd: return "fundamentalTypeAnd";
        case SymbolKind::fundamentalTypeOr: return "fundamentalTypeOr";
        case SymbolKind::fundamentalTypeXor: return "fundamentalTypeXor";
        case SymbolKind::fundamentalTypeShl: return "fundamentalTypeShl";
        case SymbolKind::fundamentalTypeShr: return "fundamentalTypeShr";
        case SymbolKind::fundamentalTypePlusAssign: return "fundamentalTypePlusAssign";
        case SymbolKind::fundamentalTypeMinusAssign: return "fundamentalTypeMinusAssign";
        case SymbolKind::fundamentalTypeMulAssign: return "fundamentalTypeMulAssign";
        case SymbolKind::fundamentalTypeDivAssign: return "fundamentalTypeDivAssign";
        case SymbolKind::fundamentalTypeModAssign: return "fundamentalTypeModAssign";
        case SymbolKind::fundamentalTypeAndAssign: return "fundamentalTypeAndAssign";
        case SymbolKind::fundamentalTypeOrAssign: return "fundamentalTypeOrAssign";
        case SymbolKind::fundamentalTypeXorAssign: return "fundamentalTypeXorAssign";
        case SymbolKind::fundamentalTypeShlAssign: return "fundamentalTypeShlAssign";
        case SymbolKind::fundamentalTypeShrAssign: return "fundamentalTypeShrAssign";
        case SymbolKind::fundamentalTypeEqual: return "fundamentalTypeEqual";
        case SymbolKind::fundamentalTypeLess: return "fundamentalTypeLess";
        case SymbolKind::fundamentalTypeBoolean: return "fundamentalTypeBoolean";
        case SymbolKind::fundamentalTypeSignExtension: return "fundamentalTypeSignExtension";
        case SymbolKind::fundamentalTypeZeroExtension: return "fundamentalTypeZeroExtension";
        case SymbolKind::fundamentalTypeFloatingPointExtension: return "fundamentalTypeFloatingPointExtension";
        case SymbolKind::fundamentalTypeTruncate: return "fundamentalTypeTruncate";
        case SymbolKind::fundamentalTypeBitcast: return "fundamentalTypeBitcast";
        case SymbolKind::fundamentalTypeIntToFloat: return "fundamentalTypeIntToFloat";
        case SymbolKind::fundamentalTypeFloatToInt: return "fundamentalTypeFloatToInt";
        case SymbolKind::fundamentalTypeDefaultCtor: return "fundamentalTypeDefaultCtor";
        case SymbolKind::fundamentalTypeCopyCtor: return "fundamentalTypeCopyCtor";
        case SymbolKind::fundamentalTypeCopyCtorLiteral: return "fundamentalTypeCopyCtorLiteral";
        case SymbolKind::fundamentalTypeMoveCtor: return "fundamentalTypeMoveCtor";
        case SymbolKind::fundamentalTypeCopyAssignment: return "fundamentalTypeCopyAssignment";
        case SymbolKind::fundamentalTypeMoveAssignment: return "fundamentalTypeMoveAssignment";
        case SymbolKind::enumTypeDefaultCtor: return "enumTypeDefaultCtor";
        case SymbolKind::enumTypeCopyCtor: return "enumTypeCopyCtor";
        case SymbolKind::enumTypeMoveCtor: return "enumTypeMoveCtor";
        case SymbolKind::enumTypeCopyAssignment: return "enumTypeCopyAssignment";
        case SymbolKind::enumTypeMoveAssignment: return "enumTypeMoveAssignment";
        case SymbolKind::enumTypeEqual: return "enumTypeEqual";
        case SymbolKind::enumTypeLess: return "enumTypeLess";
        case SymbolKind::arrayTypeDefaultCtor: return "arrayTypeDefaultCtor";
        case SymbolKind::arrayTypeCopyCtor: return "arrayTypeCopyCtor";
        case SymbolKind::arrayTypeMoveCtor: return "arrayTypeMoveCtor";
        case SymbolKind::arrayTypeCopyAssignment: return "arrayTypeCopyAssignment";
        case SymbolKind::arrayTypeMoveAssignment: return "arrayTypeMoveAssignment";
        case SymbolKind::arrayTypeBegin: return "arrayTypeBegin";
        case SymbolKind::arrayTypeEnd: return "arrayTypeEnd";
        case SymbolKind::defaultBool: return "defaultBool";
        case SymbolKind::defaultSByte: return "defaultSByte";
        case SymbolKind::defaultShort: return "defaultShort";
        case SymbolKind::defaultUShort: return "defaultUShort";
        case SymbolKind::defaultInt: return "defaultInt";
        case SymbolKind::defaultUInt: return "defaultUInt";
        case SymbolKind::defaultLong: return "defaultLong";
        case SymbolKind::defaultULong: return "defaultULong";
        case SymbolKind::defaultFloat: return "defaultFloat";
        case SymbolKind::defaultDouble: return "defaultDouble";
        case SymbolKind::defaultChar: return "defaultChar";
        case SymbolKind::defaultChar16: return "defaultChar16";
        case SymbolKind::defaultChar32: return "defaultChar32";
        case SymbolKind::functionGroupTypeSymbol: return "functionGroupType";
        case SymbolKind::classGroupTypeSymbol: return "classGroupType";
        case SymbolKind::aliasGroupTypeSymbol: return "aliasGroupType";
        case SymbolKind::friendSymbol: return "friend";
        case SymbolKind::namespaceTypeSymbol: return "namespaceType";
    }
    return "symbol";
}

Symbol::Symbol(SymbolKind kind_, const std::u32string& name_) : kind(kind_), id(util::random_uuid()), name(name_), parent(nullptr), access(Access::none)
{
}

Symbol::~Symbol()
{
    if (symbolDestroyedFunc)
    {
        symbolDestroyedFunc(this);
    }
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

bool Symbol::IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const
{
    if (visited.find(this) == visited.end())
    {
        visited.insert(this);
    }
    return false;
}

std::string Symbol::IrName(Context* context) const
{
    return util::ToUtf8(Name());
}

void Symbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add " + symbol->SymbolKindStr() + " '" + util::ToUtf8(symbol->FullName()) + "' to " + SymbolKindStr() + " '" + util::ToUtf8(FullName()),
        sourcePos, context);
}

std::unique_ptr<Symbol> Symbol::RemoveSymbol(Symbol* symbol)
{
    otava::ast::SetExceptionThrown();
    throw std::runtime_error("cannot remove symbol");
}

void Symbol::Write(Writer& writer)
{
    writer.GetBinaryStreamWriter().Write(id);
    otava::symbols::Write(writer, declarationFlags);
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(access));
}

void Symbol::Read(Reader& reader)
{
    reader.GetBinaryStreamReader().ReadUuid(id);
    otava::symbols::Read(reader, declarationFlags);
    access = static_cast<Access>(reader.GetBinaryStreamReader().ReadByte());
}

void Symbol::Resolve(SymbolTable& symbolTable)
{
}

FunctionSymbol* Symbol::ParentFunction() const
{
    Symbol* parentSymbol = parent;
    while (parentSymbol)
    {
        if (parentSymbol->IsFunctionSymbol())
        {
            return static_cast<FunctionSymbol*>(parentSymbol);
        }
        parentSymbol = parentSymbol->Parent();
    }
    return nullptr;
}

ClassTypeSymbol* Symbol::ParentClassType() const
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
    std::string fullName = util::ToUtf8(FullName());
    docName.append("_").append(util::ToUtf8(Name())).append("_").append(util::GetSha1MessageDigest(fullName));
    return docName;
}

bool Symbol::IsLocalVariableSymbol() const
{
    if (IsVariableSymbol())
    {
        const VariableSymbol* symbol = static_cast<const VariableSymbol*>(this);
        return symbol->IsLocalVariable();
    }
    return false;
}

bool Symbol::IsMemberVariableSymbol() const
{
    if (IsVariableSymbol())
    {
        const VariableSymbol* symbol = static_cast<const VariableSymbol*>(this);
        return symbol->IsMemberVariable();
    }
    return false;
}

bool Symbol::IsGlobalVariableSymbol() const
{
    if (IsVariableSymbol())
    {
        const VariableSymbol* symbol = static_cast<const VariableSymbol*>(this);
        return symbol->IsGlobalVariable();
    }
    return false;
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
        case SymbolKind::functionDefinitionSymbol:
        case SymbolKind::fundamentalTypeUnaryPlus:
        case SymbolKind::fundamentalTypeUnaryMinus:
        case SymbolKind::fundamentalTypeComplement:
        case SymbolKind::fundamentalTypeNot:
        case SymbolKind::fundamentalTypeAdd:
        case SymbolKind::fundamentalTypeSub:
        case SymbolKind::fundamentalTypeMul:
        case SymbolKind::fundamentalTypeDiv:
        case SymbolKind::fundamentalTypeMod:
        case SymbolKind::fundamentalTypeAnd:
        case SymbolKind::fundamentalTypeOr:
        case SymbolKind::fundamentalTypeXor:
        case SymbolKind::fundamentalTypeShl:
        case SymbolKind::fundamentalTypeShr:
        case SymbolKind::fundamentalTypePlusAssign:
        case SymbolKind::fundamentalTypeMinusAssign:
        case SymbolKind::fundamentalTypeMulAssign:
        case SymbolKind::fundamentalTypeDivAssign:
        case SymbolKind::fundamentalTypeModAssign:
        case SymbolKind::fundamentalTypeAndAssign:
        case SymbolKind::fundamentalTypeOrAssign:
        case SymbolKind::fundamentalTypeXorAssign:
        case SymbolKind::fundamentalTypeShlAssign:
        case SymbolKind::fundamentalTypeShrAssign:
        case SymbolKind::fundamentalTypeEqual:
        case SymbolKind::fundamentalTypeLess:
        case SymbolKind::fundamentalTypeSignExtension:
        case SymbolKind::fundamentalTypeZeroExtension:
        case SymbolKind::fundamentalTypeTruncate:
        case SymbolKind::fundamentalTypeBitcast:
        case SymbolKind::fundamentalTypeIntToFloat:
        case SymbolKind::fundamentalTypeFloatToInt:
        case SymbolKind::fundamentalTypeBoolean:
        case SymbolKind::fundamentalTypeDefaultCtor:
        case SymbolKind::fundamentalTypeCopyCtor:
        case SymbolKind::fundamentalTypeMoveCtor:
        case SymbolKind::fundamentalTypeCopyAssignment:
        case SymbolKind::fundamentalTypeMoveAssignment:
        case SymbolKind::enumTypeDefaultCtor:
        case SymbolKind::enumTypeCopyCtor:
        case SymbolKind::enumTypeMoveCtor:
        case SymbolKind::enumTypeCopyAssignment:
        case SymbolKind::enumTypeMoveAssignment:
        case SymbolKind::enumTypeEqual:
        case SymbolKind::enumTypeLess:
        case SymbolKind::arrayTypeDefaultCtor:
        case SymbolKind::arrayTypeCopyCtor:
        case SymbolKind::arrayTypeMoveCtor:
        case SymbolKind::arrayTypeCopyAssignment:
        case SymbolKind::arrayTypeMoveAssignment:
        case SymbolKind::arrayTypeBegin:
        case SymbolKind::arrayTypeEnd:
        case SymbolKind::templateDeclarationSymbol:
        case SymbolKind::typenameConstraintSymbol:
        case SymbolKind::forwardClassDeclarationSymbol:
        case SymbolKind::friendSymbol:
        case SymbolKind::variableSymbol:
        {
            return false; 
        }
        case SymbolKind::parameterSymbol:
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
        case SymbolKind::aliasTypeSymbol:
        case SymbolKind::arrayTypeSymbol:
        case SymbolKind::classTypeSymbol:
        case SymbolKind::forwardClassDeclarationSymbol:
        case SymbolKind::classTemplateSpecializationSymbol:
        case SymbolKind::aliasTypeTemplateSpecializationSymbol:
        case SymbolKind::compoundTypeSymbol:
        case SymbolKind::enumTypeSymbol:
        case SymbolKind::forwardEnumDeclarationSymbol:
        case SymbolKind::errorSymbol:
        case SymbolKind::nestedTypeSymbol:
        case SymbolKind::dependentTypeSymbol:
        case SymbolKind::functionTypeSymbol:
        case SymbolKind::fundamentalTypeSymbol:
        case SymbolKind::genericTypeSymbol:
        case SymbolKind::nullPtrTypeSymbol:
        case SymbolKind::templateParameterSymbol:
        case SymbolKind::boundTemplateParameterSymbol:
        case SymbolKind::varArgTypeSymbol:
        case SymbolKind::namespaceTypeSymbol:
        {
            return true;
        }
    }
    return false;
}

bool Symbol::IsFunctionSymbol() const
{
    switch (kind)
    {
        case SymbolKind::functionSymbol:
        case SymbolKind::functionDefinitionSymbol:
        case SymbolKind::fundamentalTypeNot:
        case SymbolKind::fundamentalTypeUnaryPlus:
        case SymbolKind::fundamentalTypeUnaryMinus:
        case SymbolKind::fundamentalTypeComplement:
        case SymbolKind::fundamentalTypeAdd:
        case SymbolKind::fundamentalTypeSub:
        case SymbolKind::fundamentalTypeMul:
        case SymbolKind::fundamentalTypeDiv:
        case SymbolKind::fundamentalTypeMod:
        case SymbolKind::fundamentalTypeAnd:
        case SymbolKind::fundamentalTypeOr:
        case SymbolKind::fundamentalTypeXor:
        case SymbolKind::fundamentalTypeShl:
        case SymbolKind::fundamentalTypeShr:
        case SymbolKind::fundamentalTypePlusAssign:
        case SymbolKind::fundamentalTypeMinusAssign:
        case SymbolKind::fundamentalTypeMulAssign:
        case SymbolKind::fundamentalTypeDivAssign:
        case SymbolKind::fundamentalTypeModAssign:
        case SymbolKind::fundamentalTypeAndAssign:
        case SymbolKind::fundamentalTypeOrAssign:
        case SymbolKind::fundamentalTypeXorAssign:
        case SymbolKind::fundamentalTypeShlAssign:
        case SymbolKind::fundamentalTypeShrAssign:
        case SymbolKind::fundamentalTypeEqual:
        case SymbolKind::fundamentalTypeLess:
        case SymbolKind::fundamentalTypeSignExtension:
        case SymbolKind::fundamentalTypeZeroExtension:
        case SymbolKind::fundamentalTypeFloatingPointExtension:
        case SymbolKind::fundamentalTypeTruncate:
        case SymbolKind::fundamentalTypeBitcast:
        case SymbolKind::fundamentalTypeIntToFloat:
        case SymbolKind::fundamentalTypeFloatToInt:
        case SymbolKind::fundamentalTypeBoolean:
        case SymbolKind::fundamentalTypeDefaultCtor:
        case SymbolKind::fundamentalTypeCopyCtor:
        case SymbolKind::fundamentalTypeMoveCtor:
        case SymbolKind::fundamentalTypeCopyAssignment:
        case SymbolKind::fundamentalTypeMoveAssignment:
        case SymbolKind::enumTypeDefaultCtor:
        case SymbolKind::enumTypeCopyCtor:
        case SymbolKind::enumTypeMoveCtor:
        case SymbolKind::enumTypeCopyAssignment:
        case SymbolKind::enumTypeMoveAssignment:
        case SymbolKind::enumTypeEqual:
        case SymbolKind::enumTypeLess:
        case SymbolKind::arrayTypeDefaultCtor:
        case SymbolKind::arrayTypeCopyCtor:
        case SymbolKind::arrayTypeMoveCtor:
        case SymbolKind::arrayTypeCopyAssignment:
        case SymbolKind::arrayTypeMoveAssignment:
        case SymbolKind::arrayTypeBegin:
        case SymbolKind::arrayTypeEnd:
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
        case SymbolKind::stringValueSymbol:
        case SymbolKind::charValueSymbol:
        case SymbolKind::symbolValueSymbol:
        case SymbolKind::invokeValueSymbol:
        case SymbolKind::arrayValueSymbol:
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
        case SymbolKind::enumGroupSymbol:
        case SymbolKind::namespaceSymbol:
        case SymbolKind::aliasTypeSymbol:
        case SymbolKind::classTypeSymbol:
        case SymbolKind::functionTypeSymbol:
        case SymbolKind::forwardClassDeclarationSymbol:
        case SymbolKind::compoundTypeSymbol:
        case SymbolKind::enumTypeSymbol:
        case SymbolKind::forwardEnumDeclarationSymbol:
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
        case SymbolKind::functionSymbol:
        case SymbolKind::functionDefinitionSymbol:
        case SymbolKind::fundamentalTypeNot:
        case SymbolKind::fundamentalTypeUnaryPlus:
        case SymbolKind::fundamentalTypeUnaryMinus:
        case SymbolKind::fundamentalTypeComplement:
        case SymbolKind::fundamentalTypeAdd:
        case SymbolKind::fundamentalTypeSub:
        case SymbolKind::fundamentalTypeMul:
        case SymbolKind::fundamentalTypeDiv:
        case SymbolKind::fundamentalTypeMod:
        case SymbolKind::fundamentalTypeAnd:
        case SymbolKind::fundamentalTypeOr:
        case SymbolKind::fundamentalTypeXor:
        case SymbolKind::fundamentalTypeShl:
        case SymbolKind::fundamentalTypeShr:
        case SymbolKind::fundamentalTypeEqual:
        case SymbolKind::fundamentalTypeLess:
        case SymbolKind::fundamentalTypeBoolean:
        case SymbolKind::fundamentalTypePlusAssign:
        case SymbolKind::fundamentalTypeMinusAssign:
        case SymbolKind::fundamentalTypeMulAssign:
        case SymbolKind::fundamentalTypeDivAssign:
        case SymbolKind::fundamentalTypeModAssign:
        case SymbolKind::fundamentalTypeAndAssign:
        case SymbolKind::fundamentalTypeOrAssign:
        case SymbolKind::fundamentalTypeXorAssign:
        case SymbolKind::fundamentalTypeShlAssign:
        case SymbolKind::fundamentalTypeShrAssign:
        {
            return SymbolGroupKind::functionSymbolGroup;
        }
        case SymbolKind::variableGroupSymbol:
        case SymbolKind::parameterSymbol:
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

bool Symbol::IsDefaultCtor() const
{
    switch (kind)
    {
        case SymbolKind::fundamentalTypeDefaultCtor:
        {
            return true;
        }
    }
    return false;
}

bool Symbol::IsCopyCtor() const
{
    switch (kind)
    {
        case SymbolKind::fundamentalTypeCopyCtor:
        {
            return true;
        }
    }
    return false;
}

bool Symbol::IsMoveCtor() const
{
    switch (kind)
    {
        case SymbolKind::fundamentalTypeMoveCtor:
        {
            return true;
        }
    }
    return false;
}

bool Symbol::IsCopyAssignment() const
{
    switch (kind)
    {
        case SymbolKind::fundamentalTypeCopyAssignment:
        {
            return true;
        }
    }
    return false;
}

bool Symbol::IsMoveAssignment() const
{
    switch (kind)
    {
        case SymbolKind::fundamentalTypeMoveAssignment:
        {
            return true;
        }
    }
    return false;
}

bool Symbol::IsDtor() const
{
    // todo
    return false;
}

void* Symbol::IrObject(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return emitter.GetIrObject(this);
}

bool Symbol::IsExtern() const
{
    return (declarationFlags & DeclarationFlags::externFlag) != DeclarationFlags::none;
}

soul::xml::Element* Symbol::ToXml() const
{
    soul::xml::Element* element = soul::xml::MakeElement(SymbolKindToString(kind));
    element->SetAttribute("name", util::ToUtf8(name));
    element->SetAttribute("id", util::ToString(id));
    element->SetAttribute("symbolGroup", SymbolGroupStr(GetSymbolGroupKind()));
    return element;
}

} // namespace otava::symbols
