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

Method::Method(MethodKind kind_, const std::string& name_) : kind(kind_), name(name_)
{
}

Method::~Method()
{
}

void Method::AddParameter(const Parameter& parameter)
{
    parameters.push_back(parameter);
}

PositionalParamMethod::PositionalParamMethod(const std::string& name_) : Method(MethodKind::positionalParamMethod, name_)
{
}

void PositionalParamMethod::Validate(util::JsonValue* params)
{
    if (params)
    {
        if (params->IsArray())
        {
            util::JsonArray* array = static_cast<util::JsonArray*>(params);
            if (array->Count() != Arity())
            {
                JsonRpcException(invalidParams, "method '" + Name() + "': wrong arity: " + std::to_string(Arity()) + " parameters expected, " + 
                    std::to_string(array->Count()) + " arguments supplied");
            }
            int n = array->Count();
            for (int i = 0; i < n; ++i)
            {
                const Parameter& parameter = Parameters()[i];
                if (array->GetItem(i)->Type() != parameter.Type())
                {
                    throw JsonRpcException(invalidParams, "method '" + Name() + "': parameter " + std::to_string(i) + ": " + util::JsonValueTypeStr(parameter.Type()) + " expected, " +
                        util::JsonValueTypeStr(array->GetItem(i)->Type()) + " argument supplied");
                }
            }
        }
        else
        {
            throw JsonRpcException(invalidParams, "method '" + Name() + "': array of parameters expected in call");
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

std::unique_ptr<util::JsonValue> PositionalParamMethod::Exec(util::JsonValue* params)
{
    util::JsonArray* paramArray = nullptr;
    if (params)
    {
        if (params->IsArray())
        {
            paramArray = static_cast<util::JsonArray*>(params);
        }
        else
        {
            throw JsonRpcException(invalidParams, "method '" + Name() + "': array of parameters expected in call");
        }
    }
    return Execute(paramArray);
}

NamedParamMethod::NamedParamMethod(const std::string& name_) : Method(MethodKind::namedParamMethod, name_)
{
}

void NamedParamMethod::Validate(util::JsonValue* params)
{
    if (params)
    {
        if (params->IsObject())
        {
            util::JsonObject* object = static_cast<util::JsonObject*>(params);
            if (object->FieldCount() != Arity())
            {
                throw JsonRpcException(invalidParams, "method '" + Name() + "': wrong arity: " + std::to_string(Arity()) + " parameters expected, " +
                    std::to_string(object->FieldCount()) + " arguments supplied");
            }
            for (const Parameter& parameter : Parameters())
            {
                util::JsonValue* fieldValue = object->GetField(util::ToUtf32(parameter.Name()));
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
        else
        {
            throw JsonRpcException(invalidParams, "method '" + Name() + "': named parameters expected in call");
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

std::unique_ptr<util::JsonValue> NamedParamMethod::Exec(util::JsonValue* params)
{
    util::JsonObject* paramsObject = nullptr;
    if (params)
    {
        if (params->IsObject())
        {
            paramsObject = static_cast<util::JsonObject*>(params);
        }
        else
        {
            throw JsonRpcException(invalidParams, "method '" + Name() + "': named parameters expected in call");
        }
    }
    return Execute(paramsObject);
}

} // namespace soul::json::rpc
