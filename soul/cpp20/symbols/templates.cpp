// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.templates;

import soul.cpp20.ast;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;

namespace soul::cpp20::symbols {

TypenameConstraintSymbol::TypenameConstraintSymbol() : TypeSymbol(SymbolKind::typenameConstraintSymbol, std::u32string())
{
}

TemplateParameterSymbol::TemplateParameterSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::templateParameterSymbol, name_), constraint(), index(-1)
{
}

TemplateParameterSymbol::TemplateParameterSymbol(Symbol* constraint_, const std::u32string& name_, int index_) :
    TypeSymbol(SymbolKind::templateParameterSymbol, name_), constraint(constraint_), index(index_)
{
}

void TemplateParameterSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(constraint->Id());
    writer.GetBinaryStreamWriter().Write(index);
}

void TemplateParameterSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(constraintId);
    index = reader.GetBinaryStreamReader().ReadInt();
}

void TemplateParameterSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    constraint = symbolTable.GetConstraint(constraintId);
}

TemplateDeclarationSymbol::TemplateDeclarationSymbol() : ContainerSymbol(SymbolKind::templateDeclarationSymbol, std::u32string())
{
    GetScope()->SetKind(ScopeKind::templateDeclarationScope);
}

void TemplateDeclarationSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ContainerSymbol::AddSymbol(symbol, sourcePos, context);
    if (symbol->IsTemplateParameterSymbol())
    {
        templateParameters.push_back(static_cast<TemplateParameterSymbol*>(symbol));
    }
}

void BeginTemplateDeclaration(soul::cpp20::ast::Node* node, Context* context)
{
    context->GetSymbolTable()->BeginTemplateDeclaration(node, context);
    context->PushSetFlag(ContextFlags::parsingTemplateDeclaration);
}

void EndTemplateDeclaration(Context* context)
{
    context->PopFlags();
    context->GetSymbolTable()->EndTemplateDeclaration();
}

void RemoveTemplateDeclaration(Context* context)
{
    context->GetSymbolTable()->RemoveTemplateDeclaration();
}

class TemplateParameterCreator : public soul::cpp20::ast::DefaultVisitor
{
public:
    TemplateParameterCreator(Context* context_, int index_);
    void Visit(soul::cpp20::ast::TypeParameterNode& node) override;
    void Visit(soul::cpp20::ast::TypenameNode& node) override;
    void Visit(soul::cpp20::ast::ClassNode& node) override;
    void Visit(soul::cpp20::ast::ParameterNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    int index;
    Symbol* constraint;
    bool resolveConstraint;
    bool resolveTemplateParamName;
    std::u32string templateParamName;
};

TemplateParameterCreator::TemplateParameterCreator(Context* context_, int index_) : 
    context(context_), index(index_), constraint(nullptr), resolveConstraint(false), resolveTemplateParamName(false)
{
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::TypeParameterNode& node)
{
    resolveConstraint = true;
    node.TypeConstraint()->Accept(*this);
    resolveConstraint = false;
    if (node.Identifier())
    {
        resolveTemplateParamName = true;
        node.Identifier()->Accept(*this);
        resolveTemplateParamName = false;
    }
    context->GetSymbolTable()->AddTemplateParameter(templateParamName, &node, constraint, index, context);
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::TypenameNode& node)
{
    constraint = context->GetSymbolTable()->GetTypenameConstraintSymbol();
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::ClassNode& node)
{
    constraint = context->GetSymbolTable()->GetTypenameConstraintSymbol();
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::ParameterNode& node)
{
    // todo
}

void TemplateParameterCreator::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    if (resolveTemplateParamName)
    {
        templateParamName = node.Str();
    }
}

void AddTemplateParameter(soul::cpp20::ast::Node* templateParameterNode, int index, Context* context)
{
    TemplateParameterCreator creator(context, index);
    templateParameterNode->Accept(creator);
}

bool TemplateArgCanBeTypeId(soul::cpp20::ast::Node* templateIdNode, int index)
{
    return true; // TODO
}

} // namespace soul::cpp20::symbols
