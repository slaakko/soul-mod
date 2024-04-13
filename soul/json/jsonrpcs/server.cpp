// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module json.rpc.math.server;

import soul.json.rpc;

namespace json::rpc::math::server {

class AddMethod : public soul::json::rpc::Method
{
public:
    AddMethod();
    std::unique_ptr<util::JsonValue> ExecutePositional(soul::json::rpc::ExecutionContext& context, util::JsonArray* params) override;
    std::unique_ptr<util::JsonValue> ExecuteNamed(soul::json::rpc::ExecutionContext& context, util::JsonObject* params) override;
};

AddMethod::AddMethod() : soul::json::rpc::Method("add")
{
    AddParameter(soul::json::rpc::Parameter(util::JsonValueType::number, "x", false));
    AddParameter(soul::json::rpc::Parameter(util::JsonValueType::number, "y", false));
}

std::unique_ptr<util::JsonValue> AddMethod::ExecutePositional(soul::json::rpc::ExecutionContext& context, util::JsonArray* params)
{
    if (params)
    {
        util::JsonValue* xp = params->GetItem(0);
        util::JsonValue* yp = params->GetItem(1);
        if (xp->IsNumber() && yp->IsNumber())
        {
            util::JsonNumber* x = static_cast<util::JsonNumber*>(xp);
            util::JsonNumber* y = static_cast<util::JsonNumber*>(yp);
            std::unique_ptr<util::JsonValue> result(new util::JsonNumber(x->Value() + y->Value()));
            return result;
        }
    }
    throw soul::json::rpc::JsonRpcException(soul::json::rpc::invalidParams, Name() + " method got invalid prameters");
}

std::unique_ptr<util::JsonValue> AddMethod::ExecuteNamed(soul::json::rpc::ExecutionContext& context, util::JsonObject* params)
{
    if (params)
    {
        util::JsonValue* xp = params->GetField(U"x");
        util::JsonValue* yp = params->GetField(U"y");
        if (xp && yp && xp->IsNumber() && yp->IsNumber())
        {
            util::JsonNumber* x = static_cast<util::JsonNumber*>(xp);
            util::JsonNumber* y = static_cast<util::JsonNumber*>(yp);
            std::unique_ptr<util::JsonValue> result(new util::JsonNumber(x->Value() + y->Value()));
            return result;
        }
    }
    throw soul::json::rpc::JsonRpcException(soul::json::rpc::invalidParams, Name() + " method got invalid prameters");
}

void Init()
{
    soul::json::rpc::AddMethod(new AddMethod());
}

} // namespace json::rpc::math::server
