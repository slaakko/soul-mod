// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.type.symbol;

import std;
import otava.symbols.type.symbol;

export namespace otava::symbols {

class FunctionTypeSymbol : public TypeSymbol
{
public:
    FunctionTypeSymbol();
    FunctionTypeSymbol(const std::u32string& name_);
    bool IsFunctionType() const noexcept override { return true; }
    void MakeName();
    std::string SymbolKindStr() const override { return "function type symbol"; }
    std::string SymbolDocKindStr() const override { return "function_type"; }
    inline TypeSymbol* ReturnType() const { return returnType; }
    inline void SetReturnType(TypeSymbol* returnType_) noexcept { returnType = returnType_; }
    inline const std::vector<TypeSymbol*>& ParameterTypes() const noexcept { return parameterTypes; }
    void AddParameterType(TypeSymbol* parameterType);
    int PtrIndex() const noexcept override { return ptrIndex; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
private:
    TypeSymbol* returnType;
    util::uuid returnTypeId;
    std::vector<TypeSymbol*> parameterTypes;
    std::vector<util::uuid> parameterTypeIds;
    int ptrIndex;
};

bool FunctionTypesEqual(FunctionTypeSymbol* left, FunctionTypeSymbol* right, Context* context) noexcept;

} // namespace otava::symbols
