// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.concepts;

import otava.symbols.visitor;
import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.evaluator;
import otava.symbols.exception;
import otava.symbols.value;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.ast;

namespace otava::symbols {

ConstraintExprSymbol::ConstraintExprSymbol() :
    Symbol(SymbolKind::constraintExprSymbol, std::u32string()), constraintEprNodeId(-1), constraintExprNode()
{
}

ConstraintExprSymbol::ConstraintExprSymbol(otava::ast::Node* constraintExprNode_) :
    Symbol(SymbolKind::constraintExprSymbol, std::u32string()),
    constraintExprNode(constraintExprNode_), constraintEprNodeId(-1)
{
}

void ConstraintExprSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConstraintExprSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(constraintExprNode->InternalId());
}

void ConstraintExprSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    constraintEprNodeId = reader.GetBinaryStreamReader().ReadLong();
}

void ConstraintExprSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    Symbol::Resolve(symbolTable, context);
    otava::ast::NodeMap* nodeMap = symbolTable.GetNodeMap();
    constraintExprNode = nodeMap->GetNode(constraintEprNodeId);
}

ConceptSymbol::ConceptSymbol(const std::u32string& name_) : Symbol(SymbolKind::conceptSymbol, name_), constraintExpr(nullptr)
{
}

void ConceptSymbol::SetConstraintExpr(ConstraintExprSymbol* constraintExpr_)
{
    constraintExpr.reset(constraintExpr_);
}

void ConceptSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConceptSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.Write(constraintExpr.get());
}

void ConceptSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    Symbol* symbol = reader.ReadSymbol();
    if (symbol->IsConstraintExprSymbol())
    {
        constraintExpr.reset(static_cast<ConstraintExprSymbol*>(symbol));
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.concepts: ConceptSymbol::Read(): constraint expression expected");
    }
}

void ConceptSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    Symbol::Resolve(symbolTable, context);
    // todo
}

TemplateDeclarationSymbol* ConceptSymbol::ParentTemplateDeclaration() noexcept
{
    Symbol* parentSymbol = Parent();
    if (parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

bool ConceptSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const noexcept
{
    switch (scopeKind)
    {
    case ScopeKind::namespaceScope:
    case ScopeKind::templateDeclarationScope:
    case ScopeKind::classScope:
    {
        return true;
    }
    }
    return false;
}

int ConceptSymbol::Arity() noexcept
{
    TemplateDeclarationSymbol* templateDeclaration = ParentTemplateDeclaration();
    if (templateDeclaration)
    {
        return templateDeclaration->Arity();
    }
    return 0;
}

bool IsConceptName(otava::ast::Node* node, Context* context) noexcept
{
    std::u32string name = node->Str();
    Symbol* symbol = context->GetSymbolTable()->Lookup(name, SymbolGroupKind::conceptSymbolGroup, node->GetSourcePos(), context);
    if (symbol)
    {
        return symbol->IsConceptSymbol();
    }
    return false;
}

class ConceptProcessor : public otava::ast::DefaultVisitor
{
public:
    ConceptProcessor(Context* context_);
    void Visit(otava::ast::ConceptDefinitionNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
private:
    Context* context;
    ConceptSymbol* conceptSymbol;
};

ConceptProcessor::ConceptProcessor(Context* context_) : context(context_), conceptSymbol(nullptr)
{
}

void ConceptProcessor::Visit(otava::ast::ConceptDefinitionNode& node)
{
    node.ConceptName()->Accept(*this);
    ConstraintExprSymbol* constraintExprSymbol = new ConstraintExprSymbol(node.ConstraintExpression());
    context->GetSymbolTable()->MapNode(node.ConstraintExpression(), constraintExprSymbol);
    conceptSymbol->SetConstraintExpr(constraintExprSymbol);
}

void ConceptProcessor::Visit(otava::ast::IdentifierNode& node)
{
    conceptSymbol = context->GetSymbolTable()->AddConcept(node.Str(), &node, context);
}

void ProcessConcept(otava::ast::Node* node, Context* context)
{
    ConceptProcessor processor(context);
    node->Accept(processor);
}

bool ConceptLess::operator()(ConceptSymbol* left, ConceptSymbol* right) const noexcept
{
    return left->Name() < right->Name();
}

} // namespace otava::symbols
