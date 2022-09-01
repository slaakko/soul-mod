// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.concepts;

import std.core;
import soul.cpp20.symbols.symbol;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class Context;
class Value;

class ConstraintExprSymbol : public Symbol
{
public:
    ConstraintExprSymbol();
    ConstraintExprSymbol(soul::cpp20::ast::Node* constraintExprNode_);
    soul::cpp20::ast::Node* GetConstraintExprNode() const { return constraintExprNode; }
    std::string SymbolKindStr() const override { return "concept expression symbol"; }
    std::string SymbolDocKindStr() const override { return "concept_expr"; }
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
private:
    soul::cpp20::ast::Node* constraintExprNode;
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

bool IsConceptName(soul::cpp20::ast::Node* node, Context* context);

struct ConceptLess
{
    bool operator()(ConceptSymbol* left, ConceptSymbol* right) const;
};

void ProcessConcept(soul::cpp20::ast::Node* node, Context* context);
ConstraintExprSymbol* ProcessConstraintExpression(soul::cpp20::ast::Node* node, Context* context);

} // namespace soul::cpp20::symbols
