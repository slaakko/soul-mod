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
    Method(MethodKind kind_, const std::string& name_);
    virtual ~Method();
    MethodKind Kind() const { return kind; }
    bool IsPositionalParamMethod() const { return kind == MethodKind::positionalParamMethod; }
    bool IsNamedParamMethod() const { return kind == MethodKind::namedParamMethod; }
    virtual void Validate(util::JsonValue* params) = 0;
    virtual std::unique_ptr<util::JsonValue> Exec(util::JsonValue* params) = 0;
    const std::string& Name() const { return name; }
    void AddParameter(const Parameter& parameter);
    int Arity() const { return parameters.size(); }
    const std::vector<Parameter>& Parameters() const { return parameters; }
private:
    MethodKind kind;
    std::string name;
    std::vector<Parameter> parameters;
};

class PositionalParamMethod : public Method
{
public:
    PositionalParamMethod(const std::string& name_);
    void Validate(util::JsonValue* params) override;
    std::unique_ptr<util::JsonValue> Exec(util::JsonValue* params) override;
    virtual std::unique_ptr<util::JsonValue> Execute(util::JsonArray* params) = 0;
};

class NamedParamMethod : public Method
{
public:
    NamedParamMethod(const std::string& name_);
    void Validate(util::JsonValue* params) override;
    std::unique_ptr<util::JsonValue> Exec(util::JsonValue* params) override;
    virtual std::unique_ptr<util::JsonValue> Execute(util::JsonObject* params) = 0;
};

} // namespace soul::json::rpc
