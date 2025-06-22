// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.eh;

import std.core;
import otava.intermediate.function;
import otava.intermediate.type;

export namespace otava::symbols {

class Emitter;

class ExceptionHandlingFunctions
{
public:
    ExceptionHandlingFunctions(Emitter& emitter);
    otava::intermediate::Function* PushContextFunction() const { return pushContextFunction; }
    otava::intermediate::Function* PopContextFunction() const { return popContextFunction; }
    otava::intermediate::Function* SaveContextFunction() const { return saveContextFunction; }
    otava::intermediate::Function* RestoreContextFunction() const { return restoreContextFunction; }
    otava::intermediate::Function* SetExceptionFunction() const { return setExceptionFunction; }
    otava::intermediate::Function* ThrowExceptionFunction() const { return throwExceptionFunction; }
    otava::intermediate::Function* HandleExceptionFunction() const { return handleExceptionFunction; }
private:
    otava::intermediate::FunctionType* pushPopContextFunctionType;
    otava::intermediate::FunctionType* saveContextFunctionType;
    otava::intermediate::FunctionType* restoreContextFunctionType;
    otava::intermediate::FunctionType* setExceptionFunctionType;
    otava::intermediate::FunctionType* throwExceptionFunctionType;
    otava::intermediate::FunctionType* handleExceptionFunctionType;
    otava::intermediate::Function* pushContextFunction;
    otava::intermediate::Function* popContextFunction;
    otava::intermediate::Function* saveContextFunction;
    otava::intermediate::Function* restoreContextFunction;
    otava::intermediate::Function* setExceptionFunction;
    otava::intermediate::Function* throwExceptionFunction;
    otava::intermediate::Function* handleExceptionFunction;
};

} // namespace otava::symbols
