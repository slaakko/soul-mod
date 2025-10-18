// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.emitter;

import otava.symbols.bound.tree;
import otava.intermediate;
import util;

namespace otava::symbols {

Emitter::Emitter() : context(new otava::intermediate::Context()), stack(new IrValueStack()), retValue(nullptr)
{
}

Emitter::~Emitter()
{
    delete context;
    delete stack;
}

std::expected<bool, int> Emitter::Emit()
{
    return context->WriteFile();
}

void Emitter::SetCompileUnitInfo(const std::string& compileUnitId, const std::string& sourceFilePath)
{
    context->SetCompileUnitInfo(compileUnitId, sourceFilePath);
}

std::expected<bool, int> Emitter::ResolveReferences()
{
    return otava::intermediate::ResolveReferences(*context);
}

std::expected<otava::intermediate::Function*, int> Emitter::CreateFunction(const std::string& name, otava::intermediate::Type* type, bool inline_, bool once)
{
    std::expected<otava::intermediate::Function*, int> rv = context->AddFunctionDefinition(soul::ast::Span(), type, name, inline_, once, true, nullptr);
    if (!rv) return rv;
    otava::intermediate::Function* function = *rv;
    context->SetCurrentFunction(function);
    return std::expected<otava::intermediate::Function*, int>(function);
}

void Emitter::SetRegNumbers()
{
    context->CurrentFunction()->SetNumbers();
}

otava::intermediate::Type* Emitter::MakeStructureType(const std::vector<otava::intermediate::Type*>& elementTypes, const std::string& comment)
{
    std::vector<otava::intermediate::TypeRef> fieldTypeRefs;
    for (otava::intermediate::Type* elementType : elementTypes)
    {
        fieldTypeRefs.push_back(elementType->GetTypeRef());
    }
    otava::intermediate::StructureType* structureType = context->GetStructureType(soul::ast::Span(), context->NextTypeId(), fieldTypeRefs);
    structureType->SetComment(comment);
    return structureType;
}

otava::intermediate::Type* Emitter::MakeFunctionType(otava::intermediate::Type* returnType, const std::vector<otava::intermediate::Type*>& paramTypes)
{
    otava::intermediate::TypeRef returnTypeRef = returnType->GetTypeRef();
    std::vector<otava::intermediate::TypeRef> paramTypeRefs;
    for (otava::intermediate::Type* paramType : paramTypes)
    {
        paramTypeRefs.push_back(paramType->GetTypeRef());
    }
    return context->GetFunctionType(soul::ast::Span(), context->NextTypeId(), returnTypeRef, paramTypeRefs);
}

otava::intermediate::Type* Emitter::MakeArrayType(std::int64_t size, otava::intermediate::Type* elementType)
{
    otava::intermediate::TypeRef elementTypeRef = elementType->GetTypeRef();
    return context->GetArrayType(soul::ast::Span(), context->NextTypeId(), size, elementTypeRef);
}

otava::intermediate::Type* Emitter::GetOrInsertFwdDeclaredStructureType(const util::uuid& id, const std::string& comment)
{
    otava::intermediate::Type* type = context->GetFwdDeclaredStructureType(id);
    if (type)
    {
        return type;
    }
    else
    {
        return MakeFwdDeclaredStructureType(id, comment);
    }
}

void Emitter::ResolveForwardReferences(const util::uuid& typeId, otava::intermediate::StructureType* structureType)
{
    context->ResolveForwardReferences(typeId, structureType);
}

otava::intermediate::Value* Emitter::EmitBool(bool value)
{
    if (value)
    {
        return context->GetTrueValue();
    }
    else
    {
        return context->GetFalseValue();
    }
}

std::expected<otava::intermediate::Value*, int> Emitter::EmitStringValue(const std::string& value)
{
    otava::intermediate::Value* stringValue = context->MakeStringValue(soul::ast::Span(), value, false);
    std::expected<otava::intermediate::GlobalVariable*, int> srv = context->GetGlobalVariableForString(stringValue, GetByteType());
    if (!srv) return std::unexpected<int>(srv.error());
    otava::intermediate::GlobalVariable* globalVar = *srv;
    return std::expected<otava::intermediate::Value*, int>(globalVar);
}

std::expected<otava::intermediate::Value*, int> Emitter::EmitString16Value(const std::string& value)
{
    std::expected<std::u16string, int> rv = util::ToUtf16(value);
    if (!rv) return std::unexpected<int>(rv.error());
    std::u16string str = std::move(*rv);
    std::vector<otava::intermediate::Value*> elements;
    for (const char16_t x : str)
    {
        elements.push_back(EmitUShort(static_cast<std::uint16_t>(x)));
    }
    elements.push_back(EmitUShort(static_cast<std::uint16_t>(0)));
    otava::intermediate::Value* string16Value = context->MakeStringArrayValue(soul::ast::Span(), 'w', elements);
    std::expected<otava::intermediate::GlobalVariable*, int> srv = context->GetGlobalVariableForString(string16Value, GetUShortType());
    if (!srv) return std::unexpected<int>(srv.error());
    otava::intermediate::GlobalVariable* globalVar = *srv;
    return std::expected<otava::intermediate::Value*, int>(globalVar);
}

std::expected<otava::intermediate::Value*, int> Emitter::EmitString32Value(const std::string& value)
{
    std::expected<std::u32string, int> rv = util::ToUtf32(value);
    if (!rv) return std::unexpected<int>(rv.error());
    std::u32string str = std::move(*rv);
    std::vector<otava::intermediate::Value*> elements;
    for (const char32_t x : str)
    {
        elements.push_back(EmitUInt(static_cast<std::uint32_t>(x)));
    }
    elements.push_back(EmitUInt(static_cast<std::uint32_t>(0)));
    if (!srv) return std::unexpected<int>(srv.error());
    otava::intermediate::Value* string32Value = context->MakeStringArrayValue(soul::ast::Span(), 'u', elements);
    std::expected<otava::intermediate::GlobalVariable*, int> srv = context->GetGlobalVariableForString(string32Value, GetUIntType());
    if (!srv) return std::unexpected<int>(srv.error());
    otava::intermediate::GlobalVariable* globalVar = *srv;
    return std::expected<otava::intermediate::Value*, int>(globalVar);
}

otava::intermediate::Value* Emitter::EmitCall(otava::intermediate::Value* function, const std::vector<otava::intermediate::Value*>& args)
{
    std::int32_t n = args.size();
    for (std::int32_t i = 0; i < n; ++i)
    {
        otava::intermediate::Value* arg = args[i];
        context->CreateArg(arg);
    }
    return context->CreateCall(function);
}

otava::intermediate::Type* Emitter::GetType(const util::uuid& id) const
{
    auto it = typeMap.find(id);
    if (it != typeMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Emitter::SetType(const util::uuid& id, otava::intermediate::Type* type)
{
    typeMap[id] = type;
}

otava::intermediate::Value* Emitter::GetIrObject(void* symbol) const
{
    auto it = irObjectMap.find(symbol);
    if (it != irObjectMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Emitter::SetIrObject(void* symbol, otava::intermediate::Value* irObject)
{
    irObjectMap[symbol] = irObject;
}

otava::intermediate::Value* Emitter::GetVTabVariable(const std::u32string& className) const
{
    auto it = vtabVariableMap.find(className);
    if (it != vtabVariableMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Emitter::SetVTabVariable(const std::u32string& className, otava::intermediate::Value* vtabVariable)
{
    vtabVariableMap[className] = vtabVariable;
}

std::expected<otava::intermediate::Value*, int> Emitter::EmitClassPtrConversion(otava::intermediate::Value* classPtr, otava::intermediate::Value* delta, 
    otava::intermediate::Type* destType)
{
    if (delta->IsZero()) return EmitBitcast(classPtr, destType);
    std::expected<otava::intermediate::Type*, int> rv = MakePtrType(GetByteType());
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Type* bytePtrType = *rv;
    otava::intermediate::Value* adjustableClassPtr = EmitBitcast(classPtr, bytePtrType);
    otava::intermediate::Value* adjustedClassPtr = EmitPtrOffset(adjustableClassPtr, delta);
    return std::expected<otava::intermediate::Value*, int>(EmitBitcast(adjustedClassPtr, destType));
}

} // namespace otava::symbols
