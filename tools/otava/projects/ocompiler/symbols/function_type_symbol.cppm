// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.type.symbol;

import std;
import otava.symbols.type.symbol;
import otava.symbols.context;

export namespace otava::symbols {

class FunctionTypeSymbol : public TypeSymbol
{
public:
    FunctionTypeSymbol();
    FunctionTypeSymbol(const std::u32string& name_);
    bool IsFunctionType() const override { return true; }
    void MakeName();
    std::string SymbolKindStr() const override { return "function type symbol"; }
    std::string SymbolDocKindStr() const override { return "function_type"; }
    inline TypeSymbol* ReturnType() const { return returnType; }
    inline void SetReturnType(TypeSymbol* returnType_) { returnType = returnType_; }
    inline const std::vector<TypeSymbol*>& ParameterTypes() const { return parameterTypes; }
    void AddParameterType(TypeSymbol* parameterType);
    int PtrIndex() const override { return ptrIndex; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    std::expected<otava::intermediate::Type*, int> IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
private:
    TypeSymbol* returnType;
    util::uuid returnTypeId;
    std::vector<TypeSymbol*> parameterTypes;
    std::vector<util::uuid> parameterTypeIds;
    int ptrIndex;
};

bool FunctionTypesEqual(FunctionTypeSymbol* left, FunctionTypeSymbol* right, Context* context);

} // namespace otava::symbols
