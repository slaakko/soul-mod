// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module json.rpc.math.server;

import soul.json.rpc;

namespace json::rpc::math::server {

class AddMethod : public soul::json::rpc::PositionalParamMethod
{
public:
    AddMethod();
    std::unique_ptr<util::JsonValue> Execute(util::JsonArray* params) override;
};

AddMethod::AddMethod() : soul::json::rpc::PositionalParamMethod("add")
{
    AddParameter(soul::json::rpc::Parameter(util::JsonValueType::number, "x"));
    AddParameter(soul::json::rpc::Parameter(util::JsonValueType::number, "y"));
}

std::unique_ptr<util::JsonValue> AddMethod::Execute(util::JsonArray* params)
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

void Init()
{
    soul::json::rpc::AddMethod(new AddMethod());
}

} // namespace json::rpc::math::server
