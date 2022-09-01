// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.concepts;

import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.templates;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.evaluator;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.value;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;
import soul.cpp20.ast;

namespace soul::cpp20::symbols {

ConstraintExprSymbol::ConstraintExprSymbol() : 
    Symbol(SymbolKind::constraintExprSymbol, std::u32string()), constraintEprNodeId(-1)
{
}

ConstraintExprSymbol::ConstraintExprSymbol(soul::cpp20::ast::Node* constraintExprNode_) : 
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
    writer.GetBinaryStreamWriter().Write(constraintExprNode->Id());
}

void ConstraintExprSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    constraintEprNodeId = reader.GetBinaryStreamReader().ReadInt();
}

void ConstraintExprSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    soul::cpp20::ast::NodeMap* nodeMap = symbolTable.GetNodeMap();
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
        throw std::runtime_error("soul.cpp20.symbols.concepts: ConceptSymbol::Read(): constraint expression expected");
    }
}

void ConceptSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
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

bool IsConceptName(soul::cpp20::ast::Node* node, Context* context)
{
    std::u32string name = node->Str();
    Symbol* symbol = context->GetSymbolTable()->Lookup(name, SymbolGroupKind::conceptSymbolGroup, node->GetSourcePos(), context);
    if (symbol)
    {
        return symbol->IsConceptSymbol();
    }
    return false;
}

class ConceptProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    ConceptProcessor(Context* context_);
    void Visit(soul::cpp20::ast::ConceptDefinitionNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    ConceptSymbol* conceptSymbol;
};

ConceptProcessor::ConceptProcessor(Context* context_) : context(context_), conceptSymbol(nullptr)
{
}

void ConceptProcessor::Visit(soul::cpp20::ast::ConceptDefinitionNode& node)
{
    node.ConceptName()->Accept(*this);
    ConstraintExprSymbol* constraintExprSymbol = new ConstraintExprSymbol(node.ConstraintExpression());
    context->GetSymbolTable()->MapNode(node.ConstraintExpression(), constraintExprSymbol);
    conceptSymbol->SetConstraintExpr(constraintExprSymbol);
}

void ConceptProcessor::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    conceptSymbol = context->GetSymbolTable()->AddConcept(node.Str(), &node, context);
}

void ProcessConcept(soul::cpp20::ast::Node* node, Context* context)
{
    ConceptProcessor processor(context);
    node->Accept(processor);
}

bool ConceptLess::operator()(ConceptSymbol* left, ConceptSymbol* right) const
{
    return left->Name() < right->Name();
}

} // namespace soul::cpp20::symbols
