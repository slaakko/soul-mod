// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.intrinsics;

import std;
import otava.symbols.function.symbol;

export namespace otava::symbols {

class GetFramePtrIntrinsic : public FunctionSymbol
{
public:
    GetFramePtrIntrinsic();
    GetFramePtrIntrinsic(Context* context);
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
};

void MakeIntrinsics(Context* context);

} // namespace otava::symbols
