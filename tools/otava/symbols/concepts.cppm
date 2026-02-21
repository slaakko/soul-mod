// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.concepts;

import std;
import otava.symbols.symbol;
import otava.ast.node;

export namespace otava::symbols {

class Context;
class Value;

class ConstraintExprSymbol : public Symbol
{
public:
    ConstraintExprSymbol();
    ConstraintExprSymbol(otava::ast::Node* constraintExprNode_);
    inline otava::ast::Node* GetConstraintExprNode() const noexcept { return constraintExprNode; }
    std::string SymbolKindStr() const override { return "concept expression symbol"; }
    std::string SymbolDocKindStr() const override { return "concept_expr"; }
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
private:
    otava::ast::Node* constraintExprNode;
    std::int64_t constraintEprNodeId;
};

class ConceptSymbol : public Symbol
{
public:
    ConceptSymbol(const std::u32string& name_);
    int Arity() noexcept;
    std::string SymbolKindStr() const override { return "concept symbol"; }
    std::string SymbolDocKindStr() const override { return "concept"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration() noexcept;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void SetConstraintExpr(ConstraintExprSymbol* constraintExpr_);
    inline ConstraintExprSymbol* GetConstraintExpr() const noexcept { return constraintExpr.get(); }
private:
    std::unique_ptr<ConstraintExprSymbol> constraintExpr;
};

bool IsConceptName(otava::ast::Node* node, Context* context) noexcept;

struct ConceptLess
{
    bool operator()(ConceptSymbol* left, ConceptSymbol* right) const noexcept;
};

void ProcessConcept(otava::ast::Node* node, Context* context);
ConstraintExprSymbol* ProcessConstraintExpression(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
