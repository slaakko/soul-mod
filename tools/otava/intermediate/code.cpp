// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.code;

import otava.intermediate.error;
import otava.intermediate.function;
import otava.intermediate.type;
import otava.intermediate.util;
import otava.intermediate.visitor;

namespace otava::intermediate {

Code::Code() : functions(this), context(nullptr), currentFunction(nullptr)
{
}

Function* Code::FirstFunction()
{
    return static_cast<Function*>(functions.FirstChild());
}

Function* Code::LastFunction() 
{ 
    return static_cast<Function*>(functions.LastChild());
}

void Code::Finalize()
{
    Function* f = FirstFunction();
    while (f)
    {
        f->Finalize();
        f = f->Next();
    }
}

void Code::Write(util::CodeFormatter& formatter)
{
    bool first = true;
    bool written = false;
    Function* f = FirstFunction();
    while (f)
    {
        if (first)
        {
            first = false;
        }
        else if (written)
        {
            formatter.WriteLine();
        }
        written = f->Write(formatter);
        f = f->Next();
    }
}

void Code::AddFunction(Function* fn)
{
    functions.AddChild(fn);
}

std::unique_ptr<Function> Code::RemoveFunction(Function* fn)
{
    return std::unique_ptr<Function>(static_cast<Function*>(functions.RemoveChild(fn).release()));
}

void Code::SetCurrentFunction(Function* function)
{
    currentFunction = function;
}

Function* Code::GetFunction(const std::string& functionId) const
{
    auto it = functionMap.find(functionId);
    if (it != functionMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

Function* Code::GetOrInsertFunction(const std::string& functionId, FunctionType* functionType)
{
    Function* function = GetFunction(functionId);
    if (function)
    {
        if (function->GetType() != functionType)
        {
            Error("function type conflicts with earlier declaration", SourcePos(), context);
            return nullptr;
        }
        else
        {
            return function;
        }
    }
    else
    {
        return AddFunctionDeclaration(SourcePos(), functionType, functionId);
    }
}

Function* Code::AddFunctionDefinition(const SourcePos& sourcePos, FunctionType* functionType, const std::string& functionId, bool once, MetadataRef* metadataRef, Context* context)
{
    Function* prev = GetFunction(functionId);
    if (prev)
    {
        if (prev->IsDefined())
        {
            Warning("Warning: '" + functionId + "': function id not unique", sourcePos, context, prev->GetSourcePos());
            return prev;
        }
        else
        {
            if (prev->GetType() != functionType)
            {
                Error("error adding function '" + functionId + "': type '" + functionType->Name() + "' conflicts with earlier declaration", sourcePos, context, prev->GetSourcePos());
            }
            prev->SetDefined();
            return prev;
        }
    }
    Function* function = new Function(sourcePos, functionType, functionId, once, true, metadataRef, context);
    AddFunction(function);
    functionMap[function->Name()] = function;
    return function;
}

Function* Code::AddFunctionDeclaration(const SourcePos& sourcePos, FunctionType* functionType, const std::string& functionId)
{
    Function* prev = GetFunction(functionId);
    if (prev)
    {
        if (prev->GetType() != functionType)
        {
            Error("error adding function declaration '" + functionId + "': type '" + functionType->Name() + "' conflicts with earlier declaration", sourcePos, context, prev->GetSourcePos());
        }
        return prev;
    }
    Function* function = new Function(sourcePos, functionType, functionId, false, false, nullptr, context);
    AddFunction(function);
    functionMap[function->Name()] = function;
    return function;
}

void Code::VisitFunctions(Visitor& visitor)
{
    Function* function = FirstFunction();
    while (function)
    {
        function->Accept(visitor);
        function = function->Next();
    }
}

} // otava::intermediate
