// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.translation.unit;

import otava.ast.visitor;

namespace otava::ast {

TranslationUnitNode::TranslationUnitNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::translationUnitNode, sourcePos_)
{
}

TranslationUnitNode::TranslationUnitNode(const soul::ast::SourcePos& sourcePos_, Node* unit_) : CompoundNode(NodeKind::translationUnitNode, sourcePos_), unit(unit_)
{
}

std::expected<Node*, int> TranslationUnitNode::Clone() const
{
    Node* clonedUnit = nullptr;
    if (unit)
    {
        std::expected<Node*, int> u = unit->Clone();
        if (!u) return u;
        clonedUnit = *u;
    }
    TranslationUnitNode* clone = new TranslationUnitNode(GetSourcePos(), clonedUnit);
    return std::expected<Node*, int>(clone);
}

void TranslationUnitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TranslationUnitNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(unit.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TranslationUnitNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    unit.reset(*nrv);
    return std::expected<bool, int>(true);
}

ModuleUnitNode::ModuleUnitNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::moduleUnitNode, sourcePos_)
{
}

ModuleUnitNode::ModuleUnitNode(const soul::ast::SourcePos& sourcePos_, Node* globalModuleFragment_, Node* moduleDeclaration_, Node* declarations_, Node* privateModuleFragment_) :
    CompoundNode(NodeKind::moduleUnitNode, sourcePos_), globalModuleFragment(globalModuleFragment_), moduleDeclaration(moduleDeclaration_), declarations(declarations_),
    privateModuleFragment(privateModuleFragment_)
{
}

std::expected<Node*, int> ModuleUnitNode::Clone() const
{
    Node* clonedGlobalModuleFragment = nullptr;
    if (globalModuleFragment)
    {
        std::expected<Node*, int> g = globalModuleFragment->Clone();
        if (!g) return g;
        clonedGlobalModuleFragment = *g;
    }
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        std::expected<Node*, int> d = declarations->Clone();
        if (!d) return d;
        clonedDeclarations = *d;
    }
    Node* clonedPrivateModuleFragment = nullptr;
    if (privateModuleFragment)
    {
        std::expected<Node*, int> p = privateModuleFragment->Clone();
        if (!p) return p;
        clonedPrivateModuleFragment = *p;;
    }
    std::expected<Node*, int> m = moduleDeclaration->Clone();
    if (!m) return m;
    ModuleUnitNode* clone = new ModuleUnitNode(GetSourcePos(), clonedGlobalModuleFragment, *m, clonedDeclarations, clonedPrivateModuleFragment);
    return std::expected<Node*, int>(clone);
}

void ModuleUnitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ModuleUnitNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(globalModuleFragment.get());
    if (!rv) return rv;
    rv = writer.Write(moduleDeclaration.get());
    if (!rv) return rv;
    rv = writer.Write(declarations.get());
    if (!rv) return rv;
    rv = writer.Write(privateModuleFragment.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ModuleUnitNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    globalModuleFragment.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    moduleDeclaration.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarations.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    privateModuleFragment.reset(*nrv);
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
