// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.json.rpc.method;

import std.core;
import util;

export namespace soul::json::rpc {

class Parameter
{
public:
    Parameter(util::JsonValueType type_, const std::string& name_);
    util::JsonValueType Type() const { return type; }
    const std::string& Name() const { return name; }
private:
    util::JsonValueType type; 
    std::string name;
};

enum class MethodKind
{
    positionalParamMethod, namedParamMethod
};

class Method
{
public:
    Method(const std::string& name_);
    virtual ~Method();
    void Validate(util::JsonValue* params);
    std::unique_ptr<util::JsonValue> Execute(util::JsonValue* params);
    virtual std::unique_ptr<util::JsonValue> ExecutePositional(util::JsonArray* params) = 0;
    virtual std::unique_ptr<util::JsonValue> ExecuteNamed(util::JsonObject* params) = 0;
    const std::string& Name() const { return name; }
    void AddParameter(const Parameter& parameter);
    int Arity() const { return parameters.size(); }
    const std::vector<Parameter>& Parameters() const { return parameters; }
private:
    void ValidatePositional(util::JsonArray* params);
    void ValidateNamed(util::JsonObject* params);
    std::string name;
    std::vector<Parameter> parameters;
};

} // namespace soul::json::rpc
