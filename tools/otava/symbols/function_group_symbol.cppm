// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.group.symbol;

import std;
import otava.symbols.symbol;
import otava.symbols.function.kind;

export namespace otava::symbols {

class FunctionSymbol;
class FunctionDefinitionSymbol;
class ParameterSymbol;
class TypeSymbol;

class FunctionGroupSymbol : public Symbol
{
public:
    FunctionGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "function group symbol"; }
    std::string SymbolDocKindStr() const override { return "function_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    Symbol* GetSingleSymbol() noexcept override;
    FunctionDefinitionSymbol* GetSingleDefinition() noexcept;
    void AddFunction(FunctionSymbol* function);
    inline const std::vector<FunctionSymbol*>& Functions() const noexcept { return functions; }
    inline const std::vector<FunctionDefinitionSymbol*>& Definitions() const noexcept { return definitions; }
    FunctionSymbol* ResolveFunction(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers, const std::vector<TypeSymbol*>& specialization,
        TemplateDeclarationSymbol* templateDeclaration, bool isSpecialization, Context* context) const;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(FunctionGroupSymbol* that);
    FunctionDefinitionSymbol* GetFunctionDefinition(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers, Context* context) const;
    void AddFunctionDefinition(FunctionDefinitionSymbol* definition_, Context* context);
    void SetVTabIndex(FunctionSymbol* function, int vtabIndex, Context* context);
    void CollectViableFunctions(int arity, const std::vector<TypeSymbol*>& templateArgs, std::vector<FunctionSymbol*>& viableFunctions, Context* context);
    FunctionSymbol* GetMatchingSpecialization(FunctionSymbol* that, Context* context) const;
private:
    void CollectBestMatchingViableFunctionTemplates(int arity, const std::vector<TypeSymbol*>& templateArgs, std::vector<FunctionSymbol*>& viableFunctions, Context* context);
    std::vector<FunctionSymbol*> functions;
    std::vector<util::uuid> functionIds;
    std::vector<FunctionDefinitionSymbol*> definitions;
    std::vector<util::uuid> functionDefinitionIds;
};

} // namespace otava::symbols
