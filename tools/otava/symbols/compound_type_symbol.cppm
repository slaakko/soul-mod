// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.compound.type.symbol;

import std;
import otava.symbols.type.symbol;
import otava.symbols.derivations;

export namespace otava::symbols {

class CompoundTypeSymbol : public TypeSymbol
{
public:
    CompoundTypeSymbol(const std::u32string& name_);
    CompoundTypeSymbol(TypeSymbol* baseType_, Derivations derivations_, const util::uuid& id_);
    util::uuid IrId(Context* context) const override;
    TypeSymbol* GetBaseType() override { return baseType; }
    const TypeSymbol* GetBaseType() const override { return baseType; }
    std::string SymbolKindStr() const override { return "compound type symbol"; }
    std::string SymbolDocKindStr() const override { return "compound_type"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    TypeSymbol* PlainType(Context* context) override;
    bool IsVoidPtrType() const override { return baseType->IsVoidType(); }
    int PointerCount() const override;
    inline TypeSymbol* BaseType() const { return baseType; }
    Derivations GetDerivations() const override { return derivations; }
    TypeSymbol* RemoveDerivations(Derivations sourceDerivations, Context* context) override;
    TypeSymbol* Unify(TypeSymbol* argType, Context* context) override;
    TypeSymbol* UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::string IrName(Context* context) const override;
    std::u32string FullName() const override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    bool IsExportSymbol(Context* context) const override;
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    TypeSymbol* FinalType(const soul::ast::SourcePos& sourcePos, Context* context) override;
    TypeSymbol* DirectType(Context* context) override;
    bool IsComplete(std::set<const TypeSymbol*>& visited, const TypeSymbol*& incompleteType) const override;
    bool IsBasicStringCharType(Context* context) override { return PointerCount() == 0 && PlainType(context)->IsBasicStringCharType(context); }
    bool IsBasicStringChar16Type(Context* context) override { return PointerCount() == 0 && PlainType(context)->IsBasicStringChar16Type(context); }
    bool IsBasicStringChar32Type(Context* context) override { return PointerCount() == 0 && PlainType(context)->IsBasicStringChar32Type(context); }
private:
    TypeSymbol* baseType;
    Derivations derivations;
    util::uuid baseTypeId;
};

std::u32string MakeCompoundTypeName(TypeSymbol* baseType, Derivations derivations);
util::uuid MakeCompoundTypeId(TypeSymbol* baseType, Derivations derivations, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
