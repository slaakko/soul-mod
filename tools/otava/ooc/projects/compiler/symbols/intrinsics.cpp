// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.intrinsics;

import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.type.symbol;
import otava.symbols.emitter;
import otava.symbols.namespaces;

namespace otava::symbols {

GetFramePtrIntrinsic::GetFramePtrIntrinsic() : FunctionSymbol(SymbolKind::intrinsicGetRbp, U"__intrinsic_get_frame_ptr")
{
}

GetFramePtrIntrinsic::GetFramePtrIntrinsic(Context* context) : FunctionSymbol(SymbolKind::intrinsicGetRbp, U"__intrinsic_get_frame_ptr")
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType)->AddPointer(context), context);
    SetNoExcept();
}

void GetFramePtrIntrinsic::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    emitter.Stack().Push(emitter.EmitGetRbp());
}

void MakeIntrinsics(Context* context)
{
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new GetFramePtrIntrinsic(context), context);
}

} // namespace otava::symbols
