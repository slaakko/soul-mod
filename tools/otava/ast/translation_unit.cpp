// =================================
// Copyright (c) 2023 Seppo Laakko
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

void TranslationUnitNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    unit.reset(reader.ReadNode());
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

void ModuleUnitNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    globalModuleFragment.reset(reader.ReadNode());
    moduleDeclaration.reset(reader.ReadNode());
    declarations.reset(reader.ReadNode());
    privateModuleFragment.reset(reader.ReadNode());
}

} // namespace otava::ast
