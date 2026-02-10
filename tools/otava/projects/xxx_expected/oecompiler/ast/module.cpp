// =================================
// Copyright (c) 2025 Seppo Laakko
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

ModuleDeclarationNode::ModuleDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* exprt_, Node* modle_, Node* moduleName_, Node* modulePartition_,
    Node* attributes_, Node* semicolon_) :
    CompoundNode(NodeKind::moduleDeclarationNode, sourcePos_), exprt(exprt_), modle(modle_), moduleName(moduleName_), modulePartition(modulePartition_),
    attributes(attributes_), semicolon(semicolon_)
{
}

std::expected<Node*, int> ModuleDeclarationNode::Clone() const
{
    Node* clonedExport = nullptr;
    if (exprt)
    {
        std::expected<Node*, int> e = exprt->Clone();
        if (!e) return e;
        clonedExport = *e;
    }
    Node* clonedModulePartition = nullptr;
    if (modulePartition)
    {
        std::expected<Node*, int> p = modulePartition->Clone();
        if (!p) return p;
        clonedModulePartition = *p;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> m = modle->Clone();
    if (!m) return m;
    std::expected<Node*, int> n = moduleName->Clone();
    if (!n) return n;
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    ModuleDeclarationNode* clone = new ModuleDeclarationNode(GetSourcePos(), clonedExport, *m, *n, clonedModulePartition, clonedAttributes, *s);
    return std::expected<Node*, int>(clone);
}

void ModuleDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ModuleDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(exprt.get());
    if (!rv) return rv;
    rv = writer.Write(modle.get());
    if (!rv) return rv;
    rv = writer.Write(moduleName.get());
    if (!rv) return rv;
    rv = writer.Write(modulePartition.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ModuleDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    exprt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    modle.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    moduleName.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    modulePartition.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

ExportDeclarationNode::ExportDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::exportDeclarationNode, sourcePos_)
{
}

ExportDeclarationNode::ExportDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* exprt_, Node* subject_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::exportDeclarationNode, sourcePos_), exprt(exprt_), subject(subject_), lbPos(lbPos_), rbPos(rbPos_)
{
}

std::expected<Node*, int> ExportDeclarationNode::Clone() const
{
    Node* clonedSubject = nullptr;
    if (subject)
    {
        std::expected<Node*, int> s = subject->Clone();
        if (!s) return s;
        clonedSubject = *s;
    }
    std::expected<Node*, int> e = exprt->Clone();
    if (!e) return e;
    ExportDeclarationNode* clone = new ExportDeclarationNode(GetSourcePos(), *e, clonedSubject, lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void ExportDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ExportDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(exprt.get());
    if (!rv) return rv;
    rv = writer.Write(subject.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExportDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    exprt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    subject.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

ExportNode::ExportNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::exportNode, sourcePos_)
{
}

std::expected<Node*, int> ExportNode::Clone() const
{
    ExportNode* clone = new ExportNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ExportNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ImportNode::ImportNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::importNode, sourcePos_)
{
}

std::expected<Node*, int> ImportNode::Clone() const
{
    ImportNode* clone = new ImportNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> ImportDeclarationNode::Clone() const
{
    Node* clonedAtributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAtributes = *a;
    }
    std::expected<Node*, int> i = imprt->Clone();
    if (!i) return i;
    std::expected<Node*, int> s = subject->Clone();
    if (!s) return s;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    ImportDeclarationNode* clone = new ImportDeclarationNode(GetSourcePos(), *i, *s, clonedAtributes, *sc);
    return std::expected<Node*, int>(clone);
}

void ImportDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ImportDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(imprt.get());
    if (!rv) return rv;
    rv = writer.Write(subject.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ImportDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    imprt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    subject.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

ModulePartitionNode::ModulePartitionNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::modulePartitionNode, sourcePos_, nullptr)
{
}

ModulePartitionNode::ModulePartitionNode(const soul::ast::SourcePos& sourcePos_, Node* moduleName_) : UnaryNode(NodeKind::modulePartitionNode, sourcePos_, moduleName_)
{
}

std::expected<Node*, int> ModulePartitionNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    ModulePartitionNode* clone = new ModulePartitionNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
}

void ModulePartitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ModuleNode::ModuleNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::moduleNode, sourcePos_)
{
}

std::expected<Node*, int> ModuleNode::Clone() const
{
    ModuleNode* clone = new ModuleNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> GlobalModuleFragmentNode::Clone() const
{
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        std::expected<Node*, int> d = declarations->Clone();
        if (!d) return d;
        clonedDeclarations = *d;
    }
    std::expected<Node*, int> m = modle->Clone();
    if (!m) return m;
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    GlobalModuleFragmentNode* clone = new GlobalModuleFragmentNode(GetSourcePos(), *m, *s, clonedDeclarations);
    return std::expected<Node*, int>(clone);
}

void GlobalModuleFragmentNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> GlobalModuleFragmentNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(modle.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(declarations.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> GlobalModuleFragmentNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    modle.reset(*nrv);
    nrv = reader.ReadNode();
    semicolon.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarations.reset(*nrv);
    return std::expected<bool, int>(true);
}

PrivateModuleFragmentNode::PrivateModuleFragmentNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::privateModuleFragmentNode, sourcePos_)
{
}

PrivateModuleFragmentNode::PrivateModuleFragmentNode(const soul::ast::SourcePos& sourcePos_, Node* modle_, Node* colon_, Node* privat_, Node* semicolon_, Node* declarations_) :
    CompoundNode(NodeKind::privateModuleFragmentNode, sourcePos_), modle(modle_), colon(colon_), privat(privat_), semicolon(semicolon_), declarations(declarations_)
{
}

std::expected<Node*, int> PrivateModuleFragmentNode::Clone() const
{
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        std::expected<Node*, int> d = declarations->Clone();
        if (!d) return d;
        clonedDeclarations = *d;
    }
    std::expected<Node*, int> m = modle->Clone();
    if (!m) return m;
    std::expected<Node*, int> c = colon->Clone();
    if (!c) return c;
    std::expected<Node*, int> p = privat->Clone();
    if (!p) return p;
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    PrivateModuleFragmentNode* clone = new PrivateModuleFragmentNode(GetSourcePos(), *m, *c, *p, *s, clonedDeclarations);
    return std::expected<Node*, int>(clone);
}

void PrivateModuleFragmentNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PrivateModuleFragmentNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(modle.get());
    if (!rv) return rv;
    rv = writer.Write(colon.get());
    if (!rv) return rv;
    rv = writer.Write(privat.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(declarations.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> PrivateModuleFragmentNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    modle.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    colon.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    privat.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarations.reset(*nrv);
    return std::expected<bool, int>(true);
}

AngleHeaderName::AngleHeaderName(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::angleHeaderNameNode, sourcePos_)
{
}

AngleHeaderName::AngleHeaderName(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_) : Node(NodeKind::angleHeaderNameNode, sourcePos_), rep(rep_)
{
}

std::expected<Node*, int> AngleHeaderName::Clone() const
{
    AngleHeaderName* clone = new AngleHeaderName(GetSourcePos(), rep);
    return std::expected<Node*, int>(clone);
}

void AngleHeaderName::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> AngleHeaderName::Write(Writer& writer)
{
    std::expected<bool, int> rv = Node::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(rep);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AngleHeaderName::Read(Reader& reader)
{
    std::expected<bool, int> rv = Node::Read(reader);
    if (!rv) return rv;
    std::expected<std::u32string, int> srv = reader.ReadStr();
    if (!srv) return std::unexpected<int>(srv.error());
    rep = *srv;
    return std::expected<bool, int>(true);
}

QuoteHeaderName::QuoteHeaderName(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::quoteHeaderNameNode, sourcePos_)
{
}

QuoteHeaderName::QuoteHeaderName(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_) : Node(NodeKind::quoteHeaderNameNode, sourcePos_), rep(rep_)
{
}

std::expected<Node*, int> QuoteHeaderName::Clone() const
{
    QuoteHeaderName* clone = new QuoteHeaderName(GetSourcePos(), rep);
    return std::expected<Node*, int>(clone);
}

void QuoteHeaderName::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> QuoteHeaderName::Write(Writer& writer)
{
    std::expected<bool, int> rv = Node::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(rep);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> QuoteHeaderName::Read(Reader& reader)
{
    std::expected<bool, int> rv = Node::Read(reader);
    if (!rv) return rv;
    std::expected<std::u32string, int> srv = reader.ReadStr();
    if (!srv) return std::unexpected<int>(srv.error());
    rep = *srv;
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
