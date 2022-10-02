// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.modules;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

ModuleDeclarationNode::ModuleDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::moduleDeclarationNode, sourcePos_)
{
}

ModuleDeclarationNode::ModuleDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* exprt_, Node* modle_, Node* moduleName_, Node* modulePartition_, Node* attributes_, Node* semicolon_) :
    CompoundNode(NodeKind::moduleDeclarationNode, sourcePos_), exprt(exprt_), modle(modle_), moduleName(moduleName_), modulePartition(modulePartition_), attributes(attributes_), semicolon(semicolon_)
{
}

Node* ModuleDeclarationNode::Clone() const
{
    Node* clonedExport = nullptr;
    if (exprt)
    {
        clonedExport = exprt->Clone();
    }
    Node* clonedModulePartition = nullptr;
    if (modulePartition)
    {
        clonedModulePartition = modulePartition->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ModuleDeclarationNode* clone = new ModuleDeclarationNode(GetSourcePos(), clonedExport, modle->Clone(), moduleName->Clone(), clonedModulePartition, clonedAttributes, 
        semicolon->Clone());
    return clone;
}

void ModuleDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ModuleDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(exprt.get());
    writer.Write(modle.get());
    writer.Write(moduleName.get());
    writer.Write(modulePartition.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
}

void ModuleDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    exprt.reset(reader.ReadNode());
    modle.reset(reader.ReadNode());
    moduleName.reset(reader.ReadNode());
    modulePartition.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

ExportDeclarationNode::ExportDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::exportDeclarationNode, sourcePos_)
{
}

ExportDeclarationNode::ExportDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* exprt_, Node* subject_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::exportDeclarationNode, sourcePos_), exprt(exprt_), subject(subject_), lbPos(lbPos_), rbPos(rbPos_)
{
}

Node* ExportDeclarationNode::Clone() const
{
    Node* clonedSubject = nullptr;
    if (subject)
    {
        clonedSubject = subject->Clone();
    }
    ExportDeclarationNode* clone = new ExportDeclarationNode(GetSourcePos(), exprt->Clone(), clonedSubject, lbPos, rbPos);
    return clone;
}

void ExportDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ExportDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(exprt.get());
    writer.Write(subject.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void ExportDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    exprt.reset(reader.ReadNode());
    subject.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

ExportNode::ExportNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::exportNode, sourcePos_)
{
}

Node* ExportNode::Clone() const
{
    ExportNode* clone = new ExportNode(GetSourcePos());
    return clone;
}

void ExportNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ImportNode::ImportNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::importNode, sourcePos_)
{
}

Node* ImportNode::Clone() const
{
    ImportNode* clone = new ImportNode(GetSourcePos());
    return clone;
}

void ImportNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ImportDeclarationNode::ImportDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::importDeclarationNode, sourcePos_)
{
}

ImportDeclarationNode::ImportDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* imprt_, Node* subject_, Node* attributes_, Node* semicolon_) :
    CompoundNode(NodeKind::importDeclarationNode, sourcePos_), imprt(imprt_), subject(subject_), attributes(attributes_), semicolon(semicolon_)
{
}

Node* ImportDeclarationNode::Clone() const
{
    Node* clonedAtributes = nullptr;
    if (attributes)
    {
        clonedAtributes = attributes->Clone();
    }
    ImportDeclarationNode* clone = new ImportDeclarationNode(GetSourcePos(), imprt->Clone(), subject->Clone(), clonedAtributes, semicolon->Clone());
    return clone;
}

void ImportDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ImportDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(imprt.get());
    writer.Write(subject.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
}

void ImportDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    imprt.reset(reader.ReadNode());
    subject.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

ModulePartitionNode::ModulePartitionNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::modulePartitionNode, sourcePos_, nullptr)
{
}

ModulePartitionNode::ModulePartitionNode(const soul::ast::SourcePos& sourcePos_, Node* moduleName_) : UnaryNode(NodeKind::modulePartitionNode, sourcePos_, moduleName_)
{
}

Node* ModulePartitionNode::Clone() const
{
    ModulePartitionNode* clone = new ModulePartitionNode(GetSourcePos(), Child()->Clone());
    return clone;
}

void ModulePartitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ModuleNode::ModuleNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::moduleNode, sourcePos_)
{
}

Node* ModuleNode::Clone() const
{
    ModuleNode* clone = new ModuleNode(GetSourcePos());
    return clone;
}

void ModuleNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

GlobalModuleFragmentNode::GlobalModuleFragmentNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::globalModuleFragmentNode, sourcePos_)
{
}

GlobalModuleFragmentNode::GlobalModuleFragmentNode(const soul::ast::SourcePos& sourcePos_, Node* modle_, Node* semicolon_, Node* declarations_) :
    CompoundNode(NodeKind::globalModuleFragmentNode, sourcePos_), modle(modle_), semicolon(semicolon_), declarations(declarations_)
{
}

Node* GlobalModuleFragmentNode::Clone() const
{
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        clonedDeclarations = declarations->Clone();
    }
    GlobalModuleFragmentNode* clone = new GlobalModuleFragmentNode(GetSourcePos(), modle->Clone(), semicolon->Clone(), clonedDeclarations);
    return clone;
}

void GlobalModuleFragmentNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void GlobalModuleFragmentNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(modle.get());
    writer.Write(semicolon.get());
    writer.Write(declarations.get());
}

void GlobalModuleFragmentNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    modle.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    declarations.reset(reader.ReadNode());
}

PrivateModuleFragmentNode::PrivateModuleFragmentNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::privateModuleFragmentNode, sourcePos_)
{
}

PrivateModuleFragmentNode::PrivateModuleFragmentNode(const soul::ast::SourcePos& sourcePos_, Node* modle_, Node* colon_, Node* privat_, Node* semicolon_, Node* declarations_) :
    CompoundNode(NodeKind::privateModuleFragmentNode, sourcePos_), modle(modle_), colon(colon_), privat(privat_), semicolon(semicolon_), declarations(declarations_)
{
}

Node* PrivateModuleFragmentNode::Clone() const
{
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        clonedDeclarations = declarations->Clone();
    }
    PrivateModuleFragmentNode* clone = new PrivateModuleFragmentNode(GetSourcePos(), modle->Clone(), colon->Clone(), privat->Clone(), semicolon->Clone(), clonedDeclarations);
    return clone;
}

void PrivateModuleFragmentNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void PrivateModuleFragmentNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(modle.get());
    writer.Write(colon.get());
    writer.Write(privat.get());
    writer.Write(semicolon.get());
    writer.Write(declarations.get());
}

void PrivateModuleFragmentNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    modle.reset(reader.ReadNode());
    colon.reset(reader.ReadNode());
    privat.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    declarations.reset(reader.ReadNode());
}

AngleHeaderName::AngleHeaderName(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::angleHeaderNameNode, sourcePos_)
{
}

AngleHeaderName::AngleHeaderName(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_) : Node(NodeKind::angleHeaderNameNode, sourcePos_), rep(rep_)
{
}

Node* AngleHeaderName::Clone() const
{
    AngleHeaderName* clone = new AngleHeaderName(GetSourcePos(), rep);
    return clone;
}

void AngleHeaderName::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AngleHeaderName::Write(Writer& writer)
{
    Node::Write(writer);
    writer.Write(rep);
}

void AngleHeaderName::Read(Reader& reader)
{
    Node::Read(reader);
    rep = reader.ReadStr();
}

QuoteHeaderName::QuoteHeaderName(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::quoteHeaderNameNode, sourcePos_)
{
}

QuoteHeaderName::QuoteHeaderName(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_) : Node(NodeKind::quoteHeaderNameNode, sourcePos_), rep(rep_)
{
}

Node* QuoteHeaderName::Clone() const
{
    QuoteHeaderName* clone = new QuoteHeaderName(GetSourcePos(), rep);
    return clone;
}

void QuoteHeaderName::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void QuoteHeaderName::Write(Writer& writer)
{
    Node::Write(writer);
    writer.Write(rep);
}

void QuoteHeaderName::Read(Reader& reader)
{
    Node::Read(reader);
    rep = reader.ReadStr();
}

} // namespace otava::ast
