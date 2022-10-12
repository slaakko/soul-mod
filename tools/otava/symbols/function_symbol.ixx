// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.symbol;

import std.core;
import otava.symbols.symbol;
import otava.symbols.container.symbol;
import otava.symbols.bound.tree.util;
import otava.ast.node;
import otava.intermediate.type;

export namespace otava::symbols {

class BoundExpressionNode;

enum class FunctionKind
{
    constructor, destructor, special, function, conversion
};

enum class FunctionQualifiers : int32_t
{
    none = 0, isConst = 1 << 0, isVolatile = 1 << 1, isOverride = 1 << 2, isFinal = 1 << 3, isDefault = 1 << 4, isDeleted = 1 << 5
};

enum class ConversionKind : int32_t;

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
    TypeSymbol* GetType() const { return type; }
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
    FunctionSymbol(SymbolKind kind_, const std::u32string& name_);
    int Arity() const { return parameters.size(); }
    std::string SymbolKindStr() const override { return "function symbol"; }
    std::string SymbolDocKindStr() const override { return "function"; }
    FunctionKind GetFunctionKind() const { return kind; }
    void SetFunctionKind(FunctionKind kind_) { kind = kind_; }
    FunctionQualifiers Qualifiers() const { return qualifiers; }
    void SetFunctionQualifiers(FunctionQualifiers qualifiers_) { qualifiers = qualifiers_; }
    bool IsConversion() const { return kind == FunctionKind::conversion; }
    void SetConversion() { kind = FunctionKind::conversion; }
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    void SetReturnType(TypeSymbol* returnType_) { returnType = returnType_; }
    TypeSymbol* ReturnType() const { return returnType; }
    virtual TypeSymbol* ConversionParamType() const { return nullptr; }
    virtual TypeSymbol* ConversionArgType() const { return nullptr; }
    virtual ConversionKind GetConversionKind() const;
    virtual int32_t ConversionDistance() const { return 0; }
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    const std::vector<ParameterSymbol*>& Parameters() const { return parameters; }
    const std::vector<ParameterSymbol*>& MemFunParameters();
    void AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    virtual void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    std::string IrName() const;
    void AddLocalVariable(VariableSymbol* localVariable, const soul::ast::SourcePos& sourcePos, Context* context);
    const std::vector<VariableSymbol*>& LocalVariables() const { return  localVariables; }
    bool IsVirtual() const;
    ParameterSymbol* ThisParam() const { return thisParam.get(); }
    bool IsMemberFunction() const;
private:
    bool memFunParamsConstructed;
    FunctionKind kind;
    FunctionQualifiers qualifiers;
    TypeSymbol* returnType;
    util::uuid returnTypeId;
    std::vector<ParameterSymbol*> parameters;
    std::unique_ptr<ParameterSymbol> thisParam;
    std::vector<ParameterSymbol*> memFunParameters;
    std::vector<VariableSymbol*> localVariables;
};

class FunctionDefinitionSymbol : public FunctionSymbol
{
public:
    FunctionDefinitionSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "function definition symbol"; }
    std::string SymbolDocKindStr() const override { return "function_definition"; }
    void SetDeclaration(FunctionSymbol* declaration_) { declaration = declaration_; }
    FunctionSymbol* Declaration() const { return declaration; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    FunctionSymbol* declaration;
    util::uuid declarationId;
};

struct FunctionLess
{
    bool operator()(FunctionSymbol* left, FunctionSymbol* right) const;
};

} // namespace otava::symbols
