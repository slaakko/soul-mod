// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.modules;

import std.core;
import otava.ast.node;

export namespace otava::ast {

class ModuleDeclarationNode : public CompoundNode
{
public:
    ModuleDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    ModuleDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* exprt_, Node* modle_, Node* moduleName_, Node* modulePartition_, Node* attributes_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Export() const { return exprt.get(); }
    Node* Module() const { return modle.get(); }
    Node* ModuleName() const { return moduleName.get(); }
    Node* ModulePartition() const { return modulePartition.get(); }
    Node* Attributes() const { return attributes.get(); }
    Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> exprt;
    std::unique_ptr<Node> modle;
    std::unique_ptr<Node> moduleName;
    std::unique_ptr<Node> modulePartition;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

class ExportDeclarationNode : public CompoundNode
{
public:
    ExportDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    ExportDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* exprt_, Node* subject_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Export() const { return exprt.get(); }
    Node* Subject() const { return subject.get(); }
    const soul::ast::SourcePos& LBracePos() const { return lbPos; }
    const soul::ast::SourcePos& RBracePos() const { return rbPos; }
private:
    std::unique_ptr<Node> exprt;
    std::unique_ptr<Node> subject;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class ExportNode : public Node
{
public:
    ExportNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ImportNode : public Node
{
public:
    ImportNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ImportDeclarationNode : public CompoundNode
{
public:
    ImportDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    ImportDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* imprt_, Node* subject_, Node* attributes_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Import() const { return imprt.get(); }
    Node* Subject() const { return subject.get(); }
    Node* Attributes() const { return attributes.get(); }
    Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> imprt;
    std::unique_ptr<Node> subject;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

class ModulePartitionNode : public UnaryNode
{
public:
    ModulePartitionNode(const soul::ast::SourcePos& sourcePos_);
    ModulePartitionNode(const soul::ast::SourcePos& sourcePos_, Node* moduleName_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ModuleNode : public Node
{
public:
    ModuleNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class GlobalModuleFragmentNode : public CompoundNode
{
public:
    GlobalModuleFragmentNode(const soul::ast::SourcePos& sourcePos_);
    GlobalModuleFragmentNode(const soul::ast::SourcePos& sourcePos_, Node* modle_, Node* semicolon_, Node* declarations_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Module() const { return modle.get(); }
    Node* Semicolon() const { return semicolon.get(); }
    Node* Declarations() const { return declarations.get(); }
private:
    std::unique_ptr<Node> modle;
    std::unique_ptr<Node> semicolon;
    std::unique_ptr<Node> declarations;
};

class PrivateModuleFragmentNode : public CompoundNode
{
public:
    PrivateModuleFragmentNode(const soul::ast::SourcePos& sourcePos_);
    PrivateModuleFragmentNode(const soul::ast::SourcePos& sourcePos_, Node* modle_, Node* colon_, Node* privat_, Node* semicolon_, Node* declarations_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Module() const { return modle.get(); }
    Node* Colon() const { return colon.get(); }
    Node* Private() const { return privat.get(); }
    Node* Semicolon() const { return semicolon.get(); }
    Node* Declarations() const { return declarations.get(); }
private:
    std::unique_ptr<Node> modle;
    std::unique_ptr<Node> colon;
    std::unique_ptr<Node> privat;
    std::unique_ptr<Node> semicolon;
    std::unique_ptr<Node> declarations;
};

class AngleHeaderName : public Node
{
public:
    AngleHeaderName(const soul::ast::SourcePos& sourcePos_);
    AngleHeaderName(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const std::u32string& Rep() const { return rep; }
private:
    std::u32string rep;
};

class QuoteHeaderName : public Node
{
public:
    QuoteHeaderName(const soul::ast::SourcePos& sourcePos_);
    QuoteHeaderName(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const std::u32string& Rep() const { return rep; }
private:
    std::u32string rep;
};

} // namespace otava::ast
