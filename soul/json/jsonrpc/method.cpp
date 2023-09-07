// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.json.rpc.method;

import soul.json.rpc.error;

namespace soul::json::rpc {

Parameter::Parameter(util::JsonValueType type_, const std::string& name_) : type(type_), name(name_)
{
}

Method::Method(const std::string& name_) : name(name_)
{
}

Method::~Method()
{
}

void Method::AddParameter(const Parameter& parameter)
{
    parameters.push_back(parameter);
}

void Method::Validate(util::JsonValue* params)
{
    if (params)
    {
        if (params->IsArray())
        {
            util::JsonArray* paramsArray = static_cast<util::JsonArray*>(params);
            ValidatePositional(paramsArray);
        }
        else if (params->IsObject())
        {
            util::JsonObject* paramsObject = static_cast<util::JsonObject*>(params);
            ValidateNamed(paramsObject);
        }
        else
        {
            throw JsonRpcException(invalidParams, "method '" + Name() + "': structured parameters value expected");
        }
    }
    else
    {
        ValidatePositional(nullptr);
    }
}

void Method::ValidatePositional(util::JsonArray* params)
{
    if (params)
    {
        if (params->Count() != Arity())
        {
            JsonRpcException(invalidParams, "method '" + Name() + "': wrong arity: " + std::to_string(Arity()) + " parameters expected, " +
                std::to_string(params->Count()) + " arguments supplied");
        }
        int n = params->Count();
        for (int i = 0; i < n; ++i)
        {
            const Parameter& parameter = Parameters()[i];
            if (params->GetItem(i)->Type() != parameter.Type())
            {
                throw JsonRpcException(invalidParams, "method '" + Name() + "': parameter " + std::to_string(i) + ": " + util::JsonValueTypeStr(parameter.Type()) + " expected, " +
                    util::JsonValueTypeStr(params->GetItem(i)->Type()) + " argument supplied");
            }
        }
    }
    else
    {
        if (Arity() != 0)
        {
            throw JsonRpcException(invalidParams, "method '" + Name() + "': wrong arity: " + std::to_string(Arity()) + " parameters expected, " +
                "no arguments supplied");
        }
    }
}

void Method::ValidateNamed(util::JsonObject* params)
{
    if (params->FieldCount() != Arity())
    {
        throw JsonRpcException(invalidParams, "method '" + Name() + "': wrong arity: " + std::to_string(Arity()) + " parameters expected, " +
            std::to_string(params->FieldCount()) + " arguments supplied");
    }
    for (const Parameter& parameter : Parameters())
    {
        util::JsonValue* fieldValue = params->GetField(util::ToUtf32(parameter.Name()));
        if (!fieldValue)
        {
            throw JsonRpcException(invalidParams, "method '" + Name() + "': parameter '" + parameter.Name() + "' is missing");
        }
        if (fieldValue->Type() != parameter.Type())
        {
            throw JsonRpcException(invalidParams, "method '" + Name() + "': parameter '" + parameter.Name() + "': " + util::JsonValueTypeStr(parameter.Type()) + " expected, " +
                util::JsonValueTypeStr(fieldValue->Type()) + " argument supplied");
        }
    }
}

std::unique_ptr<util::JsonValue> Method::Execute(util::JsonValue* params)
{
    if (params)
    {
        if (params->IsArray())
        {
            util::JsonArray* paramsArray = static_cast<util::JsonArray*>(params);
            return ExecutePositional(paramsArray);
        }
        else if (params->IsObject())
        {
            util::JsonObject* paramsObject = static_cast<util::JsonObject*>(params);
            return ExecuteNamed(paramsObject);
        }
        else
        {
            throw JsonRpcException(invalidParams, "method '" + Name() + "': structured parameters value expected");
        }
    }
    else
    {
        return ExecutePositional(nullptr);
    }
}

} // namespace soul::json::rpc
