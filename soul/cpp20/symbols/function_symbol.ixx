// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.function.symbol;

import std.core;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.container.symbol;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

enum class FunctionKind
{
    constructor, destructor, special, function
};

enum class FunctionQualifiers : int32_t
{
    none = 0, isConst = 1 << 0, isVolatile = 1 << 1, isOverride = 1 << 2, isFinal = 1 << 3, isDefault = 1 << 4, isDeleted = 1 << 5
};

constexpr FunctionQualifiers operator|(FunctionQualifiers left, FunctionQualifiers right)
{
    return FunctionQualifiers(int32_t(left) | int32_t(right));
}

constexpr FunctionQualifiers operator&(FunctionQualifiers left, FunctionQualifiers right)
{
    return FunctionQualifiers(int32_t(left) & int32_t(right));
}

constexpr FunctionQualifiers operator~(FunctionQualifiers qualifiers)
{
    return FunctionQualifiers(~int32_t(qualifiers));
}

std::string MakeFunctionQualifierStr(FunctionQualifiers qualifiers);

class TypeSymbol;
class Value;

class ParameterSymbol : public Symbol
{
public:
    ParameterSymbol(const std::u32string& name_);
    ParameterSymbol(const std::u32string& name_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "parameter symbol"; }
    std::string SymbolDocKindStr() const override { return "paremeter"; }
    TypeSymbol* Type() const { return type; }
    Value* DefaultValue() const { return defaultValue; }
    void SetDefaultValue(Value* defaultValue_) { defaultValue = defaultValue_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    TypeSymbol* type;
    util::uuid typeId;
    Value* defaultValue;
    util::uuid defaultValueId;
};

class FunctionSymbol : public ContainerSymbol
{
public:
    FunctionSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "function symbol"; }
    std::string SymbolDocKindStr() const override { return "function"; }
    FunctionKind GetFunctionKind() const { return kind; }
    void SetFunctionKind(FunctionKind kind_) { kind = kind_; }
    FunctionQualifiers Qualifiers() const { return qualifiers; }
    void SetFunctionQualifiers(FunctionQualifiers qualifiers_) { qualifiers = qualifiers_; }
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    void SetReturnType(TypeSymbol* returnType_) { returnType = returnType_; }
    TypeSymbol* ReturnType() const { return returnType; }
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    const std::vector<ParameterSymbol*>& Parameters() const { return parameters; }
    void AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    FunctionKind kind;
    FunctionQualifiers qualifiers;
    TypeSymbol* returnType;
    util::uuid returnTypeId;
    std::vector<ParameterSymbol*> parameters;
};

struct FunctionLess
{
    bool operator()(FunctionSymbol* left, FunctionSymbol* right) const;
};

} // namespace soul::cpp20::symbols
