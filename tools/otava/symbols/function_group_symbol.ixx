// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.group.symbol;

import std.core;
import otava.symbols.symbol;

export namespace otava::symbols {

class FunctionSymbol;
class FunctionDefinitionSymbol;
class ParameterSymbol;
class TypeSymbol;

enum class FunctionQualifiers : int32_t;

class FunctionGroupSymbol : public Symbol
{
public:
    FunctionGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "function group symbol"; }
    std::string SymbolDocKindStr() const override { return "function_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddFunction(FunctionSymbol* function);
    const std::vector<FunctionSymbol*>& Functions() const { return functions; }
    FunctionSymbol* ResolveFunction(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers) const;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    void Merge(FunctionGroupSymbol* that);
    FunctionDefinitionSymbol* GetFunctionDefinition(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers) const;
    void AddFunctionDefinition(FunctionDefinitionSymbol* definition_);
    void CollectViableFunctions(int arity, std::vector<FunctionSymbol*>& viableFunctions);
private:
    std::vector<FunctionSymbol*> functions;
    std::vector<util::uuid> functionIds;
    std::vector<FunctionDefinitionSymbol*> definitions;
    std::vector<util::uuid> functionDefinitionIds;
};

} // namespace otava::symbols
