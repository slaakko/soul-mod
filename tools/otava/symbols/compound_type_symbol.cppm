// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.compound.type.symbol;

import std.core;
import otava.symbols.type.symbol;
import otava.symbols.derivations;

export namespace otava::symbols {

class CompoundTypeSymbol : public TypeSymbol
{
public:
    CompoundTypeSymbol(const std::u32string& name_);
    CompoundTypeSymbol(TypeSymbol* baseType_, const Derivations& derivations_);
    TypeSymbol* GetBaseType() override { return baseType; }
    std::string SymbolKindStr() const override { return "compound type symbol"; }
    std::string SymbolDocKindStr() const override { return "compound_type"; }
    TypeSymbol* PlainType(Context* context) override;
    bool IsVoidPtrType() const override { return baseType->IsVoidType(); }
    int PointerCount() const override;
    TypeSymbol* BaseType() const { return baseType; }
    const Derivations& GetDerivations() const override { return derivations; }
    TypeSymbol* RemoveDerivations(const Derivations& sourceDerivations, Context* context) override;
    TypeSymbol* Unify(TypeSymbol* argType, Context* context) override;
    TypeSymbol* UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context) override;
    std::string IrName(Context* context) const override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    TypeSymbol* FinalType(const soul::ast::SourcePos& sourcePos, Context* context) override;
    TypeSymbol* DirectType(Context* context) override;
    bool IsComplete(std::set<const TypeSymbol*>& visited) const override;
private:
    TypeSymbol* baseType;
    Derivations derivations;
    util::uuid baseTypeId;
};

std::u32string MakeCompoundTypeName(TypeSymbol* baseType, const Derivations& derivations);

} // namespace otava::symbols
