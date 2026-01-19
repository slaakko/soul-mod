// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.group.symbol;

import std;
import otava.symbols.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.context;

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
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    FunctionDefinitionSymbol* GetSingleDefinition();
    void AddFunction(FunctionSymbol* function);
    inline const std::vector<FunctionSymbol*>& Functions() const { return functions; }
    inline const std::vector<FunctionDefinitionSymbol*>& Definitions() const { return definitions; }
    FunctionSymbol* ResolveFunction(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers, const std::vector<TypeSymbol*>& specialization,
        TemplateDeclarationSymbol* templateDeclaration, bool isSpecialization) const;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(FunctionGroupSymbol* that);
    FunctionDefinitionSymbol* GetFunctionDefinition(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers) const;
    void AddFunctionDefinition(FunctionDefinitionSymbol* definition_, Context* context);
    void SetVTabIndex(FunctionSymbol* function, int vtabIndex, Context* context);
    std::expected<bool, int> CollectViableFunctions(int arity, const std::vector<TypeSymbol*>& templateArgs, std::vector<FunctionSymbol*>& viableFunctions, 
        Context* context);
    FunctionSymbol* GetMatchingSpecialization(FunctionSymbol* that, Context* context) const;
private:
    std::expected<bool, int> CollectBestMatchingViableFunctionTemplates(int arity, const std::vector<TypeSymbol*>& templateArgs, 
        std::vector<FunctionSymbol*>& viableFunctions, Context* context);
    std::vector<FunctionSymbol*> functions;
    std::vector<util::uuid> functionIds;
    std::vector<FunctionDefinitionSymbol*> definitions;
    std::vector<util::uuid> functionDefinitionIds;
};

} // namespace otava::symbols
