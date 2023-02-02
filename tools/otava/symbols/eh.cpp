// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.eh;

import otava.symbols.emitter;

namespace otava::symbols {

std::vector<otava::intermediate::Type*> MakeRestoreContextFunctionParamTypes(Emitter& emitter)
{
    std::vector<otava::intermediate::Type*> paramTypes;
    paramTypes.push_back(emitter.MakePtrType(emitter.GetVoidType()));
    paramTypes.push_back(emitter.GetIntType());
    return paramTypes;
}

std::vector<otava::intermediate::Type*> MakeSetExceptionFunctionParamTypes(Emitter& emitter)
{
    std::vector<otava::intermediate::Type*> paramTypes;
    paramTypes.push_back(emitter.MakePtrType(emitter.GetVoidType()));
    paramTypes.push_back(emitter.GetULongType());
    paramTypes.push_back(emitter.GetULongType());
    return paramTypes;
}

std::vector<otava::intermediate::Type*> MakeHandleExceptionFunctionParamTypes(Emitter& emitter)
{
    std::vector<otava::intermediate::Type*> paramTypes;
    paramTypes.push_back(emitter.GetULongType());
    paramTypes.push_back(emitter.GetULongType());
    return paramTypes;
}

ExceptionHandlingFunctions::ExceptionHandlingFunctions(Emitter& emitter) :
    pushPopContextFunctionType(static_cast<otava::intermediate::FunctionType*>(
        emitter.MakeFunctionType(emitter.MakePtrType(emitter.GetVoidType()), std::vector<otava::intermediate::Type*>()))),
    saveContextFunctionType(static_cast<otava::intermediate::FunctionType*>(
        emitter.MakeFunctionType(emitter.GetIntType(), std::vector<otava::intermediate::Type*>(1, emitter.MakePtrType(emitter.GetVoidType()))))),
    restoreContextFunctionType(static_cast<otava::intermediate::FunctionType*>(
        emitter.MakeFunctionType(emitter.GetVoidType(), MakeRestoreContextFunctionParamTypes(emitter)))),
    setExceptionFunctionType(static_cast<otava::intermediate::FunctionType*>(
        emitter.MakeFunctionType(emitter.GetVoidType(), MakeSetExceptionFunctionParamTypes(emitter)))),
    throwExceptionFunctionType(static_cast<otava::intermediate::FunctionType*>(
        emitter.MakeFunctionType(emitter.GetVoidType(), std::vector<otava::intermediate::Type*>()))),
    handleExceptionFunctionType(static_cast<otava::intermediate::FunctionType*>(
        emitter.MakeFunctionType(emitter.GetBoolType(), MakeHandleExceptionFunctionParamTypes(emitter)))),
    pushContextFunction(emitter.GetOrInsertFunction("push_context", pushPopContextFunctionType)),
    popContextFunction(emitter.GetOrInsertFunction("pop_context", pushPopContextFunctionType)),
    saveContextFunction(emitter.GetOrInsertFunction("save_context", saveContextFunctionType)),
    restoreContextFunction(emitter.GetOrInsertFunction("restore_context", restoreContextFunctionType)),
    setExceptionFunction(emitter.GetOrInsertFunction("set_exception", setExceptionFunctionType)),
    throwExceptionFunction(emitter.GetOrInsertFunction("throw_exception", throwExceptionFunctionType)),
    handleExceptionFunction(emitter.GetOrInsertFunction("handle_exception", handleExceptionFunctionType))
{
}

} // namespace otava::symbols
