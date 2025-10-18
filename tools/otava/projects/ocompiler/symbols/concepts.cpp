// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.concepts;

import otava.symbols.visitor;
import otava.symbols.context;
import otava.symbols.templates;
import otava.symbols.symbol.table;
import otava.symbols.evaluator;
import otava.symbols.error;
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

std::expected<bool, int> ConstraintExprSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(constraintExprNode->InternalId());
    if (1rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ConstraintExprSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::int64_t, int> lrv = reader.GetBinaryStreamReader().ReadLong();
    if (!lrv) return std::unexpected<int>(lrv.error());
    constraintEprNodeId = *lrv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ConstraintExprSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    otava::ast::NodeMap* nodeMap = symbolTable.GetNodeMap();
    std::expected<otava::ast::Node*, int> nrv = nodeMap->GetNode(constraintEprNodeId);
    if (!nrv) return std::unexpected<int>(nrv.error());
    constraintExprNode = *nrv;
    return std::expected<bool, int>(true);
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

std::expected<bool, int> ConceptSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(constraintExpr.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ConceptSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    std::expected<Symbol*, int> srv = reader.ReadSymbol();
    if (!srv) return std::unexpected<int>(srv.error());
    Symbol* symbol = *srv;
    if (symbol->IsConstraintExprSymbol())
    {
        constraintExpr.reset(static_cast<ConstraintExprSymbol*>(symbol));
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.concepts: ConceptSymbol::Read(): constraint expression expected"));
    }
}

std::expected<bool, int> ConceptSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    return rv;
    // todo
}

TemplateDeclarationSymbol* ConceptSymbol::ParentTemplateDeclaration()
{
    Symbol* parentSymbol = Parent();
    if (parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

bool ConceptSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
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

int ConceptSymbol::Arity()
{
    TemplateDeclarationSymbol* templateDeclaration = ParentTemplateDeclaration();
    if (templateDeclaration)
    {
        return templateDeclaration->Arity();
    }
    return 0;
}

bool IsConceptName(otava::ast::Node* node, Context* context)
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

bool ConceptLess::operator()(ConceptSymbol* left, ConceptSymbol* right) const
{
    return left->Name() < right->Name();
}

} // namespace otava::symbols
