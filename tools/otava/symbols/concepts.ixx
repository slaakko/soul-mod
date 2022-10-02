// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.concepts;

import std.core;
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
    otava::ast::Node* GetConstraintExprNode() const { return constraintExprNode; }
    std::string SymbolKindStr() const override { return "concept expression symbol"; }
    std::string SymbolDocKindStr() const override { return "concept_expr"; }
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
private:
    otava::ast::Node* constraintExprNode;
    int32_t constraintEprNodeId;
};

class ConceptSymbol : public Symbol
{
public:
    ConceptSymbol(const std::u32string& name_);
    int Arity();
    std::string SymbolKindStr() const override { return "concept symbol"; }
    std::string SymbolDocKindStr() const override { return "concept"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void SetConstraintExpr(ConstraintExprSymbol* constraintExpr_);
    ConstraintExprSymbol* GetConstraintExpr() const { return constraintExpr.get(); }
private:
    std::unique_ptr<ConstraintExprSymbol> constraintExpr;
};

bool IsConceptName(otava::ast::Node* node, Context* context);

struct ConceptLess
{
    bool operator()(ConceptSymbol* left, ConceptSymbol* right) const;
};

void ProcessConcept(otava::ast::Node* node, Context* context);
ConstraintExprSymbol* ProcessConstraintExpression(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
