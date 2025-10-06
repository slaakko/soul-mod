// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.translation.unit;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

TranslationUnitNode::TranslationUnitNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::translationUnitNode, sourcePos_)
{
}

TranslationUnitNode::TranslationUnitNode(const soul::ast::SourcePos& sourcePos_, Node* unit_) : CompoundNode(NodeKind::translationUnitNode, sourcePos_), unit(unit_)
{
}

Node* TranslationUnitNode::Clone() const
{
    Node* clonedUnit = nullptr;
    if (unit)
    {
        clonedUnit = unit->Clone();
    }
    TranslationUnitNode* clone = new TranslationUnitNode(GetSourcePos(), clonedUnit);
    return clone;
}

void TranslationUnitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TranslationUnitNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(unit.get());
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

Node* ModuleUnitNode::Clone() const
{
    Node* clonedGlobalModuleFragment = nullptr;
    if (globalModuleFragment)
    {
        clonedGlobalModuleFragment = globalModuleFragment->Clone();
    }
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        clonedDeclarations = declarations->Clone();
    }
    Node* clonedPrivateModuleFragment = nullptr;
    if (privateModuleFragment)
    {
        clonedPrivateModuleFragment = privateModuleFragment->Clone();
    }
    ModuleUnitNode* clone = new ModuleUnitNode(GetSourcePos(), clonedGlobalModuleFragment, moduleDeclaration->Clone(), clonedDeclarations, clonedPrivateModuleFragment);
    return clone;
}

void ModuleUnitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ModuleUnitNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(globalModuleFragment.get());
    writer.Write(moduleDeclaration.get());
    writer.Write(declarations.get());
    writer.Write(privateModuleFragment.get());
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
