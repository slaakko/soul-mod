// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.emitter;

import otava.symbols.bound.tree;
import otava.intermediate;

namespace otava::symbols {

Emitter::Emitter() : context(new otava::intermediate::Context()), stack(new IrValueStack()), retValue(nullptr)
{
}

Emitter::~Emitter()
{
    delete context;
    delete stack;
}

void Emitter::Emit()
{
    context->WriteFile();
}

void Emitter::SetCompileUnitInfo(const std::string& compileUnitId, const std::string& sourceFilePath)
{
    context->SetCompileUnitInfo(compileUnitId, sourceFilePath);
}

void Emitter::ResolveReferences()
{
    otava::intermediate::ResolveReferences(*context);
}

otava::intermediate::Function* Emitter::CreateFunction(const std::string& name, otava::intermediate::Type* type, bool inline_, bool once)
{
    otava::intermediate::Function* function = context->AddFunctionDefinition(soul::ast::Span(), type, name, inline_, once, true, nullptr);
    context->SetCurrentFunction(function);
    return function;
}

void Emitter::SetRegNumbers()
{
    context->CurrentFunction()->SetNumbers();
}

otava::intermediate::Type* Emitter::MakeStructureType(const std::vector<otava::intermediate::Type*>& elementTypes, const std::string& comment)
{
    std::vector< otava::intermediate::TypeRef> fieldTypeRefs;
    for (const auto& elementType : elementTypes)
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
    for (const auto& paramType : paramTypes)
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

otava::intermediate::Value* Emitter::EmitStringValue(const std::string& value)
{
    otava::intermediate::Value* stringValue = context->MakeStringValue(soul::ast::Span(), value, false);
    otava::intermediate::GlobalVariable* globalVar = context->GetGlobalVariableForString(stringValue);
    return globalVar;
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

otava::intermediate::Value* Emitter::GetVTabVariable(void* cls) const
{
    auto it = vtabVariableMap.find(cls);
    if (it != vtabVariableMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Emitter::SetVTabVariable(void* cls, otava::intermediate::Value* vtabVariable)
{
    vtabVariableMap[cls] = vtabVariable;
}

otava::intermediate::Value* Emitter::EmitClassPtrConversion(otava::intermediate::Value* classPtr, otava::intermediate::Value* delta, otava::intermediate::Type* destType)
{
    if (delta->IsZero()) return EmitBitcast(classPtr, destType);
    otava::intermediate::Type* bytePtrType = MakePtrType(GetByteType());
    otava::intermediate::Value* adjustableClassPtr = EmitBitcast(classPtr, bytePtrType);
    otava::intermediate::Value* adjustedClassPtr = EmitPtrOffset(adjustableClassPtr, delta);
    return EmitBitcast(adjustedClassPtr, destType);
}

} // namespace otava::symbols
