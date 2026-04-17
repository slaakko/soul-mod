// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.modules;

import std;
import otava.ast.node;

export namespace otava::ast {

class ModuleDeclarationNode : public CompoundNode
{
public:
    ModuleDeclarationNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ModuleDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* exprt_, Node* modle_, Node* moduleName_, Node* modulePartition_, Node* attributes_,
        Node* semicolon_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Export() const noexcept { return exprt.get(); }
    inline Node* Module() const noexcept { return modle.get(); }
    inline Node* ModuleName() const noexcept { return moduleName.get(); }
    inline Node* ModulePartition() const noexcept { return modulePartition.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
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
    ExportDeclarationNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ExportDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* exprt_, Node* subject_,
        const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Export() const noexcept { return exprt.get(); }
    inline Node* Subject() const noexcept { return subject.get(); }
    inline const soul::ast::SourcePos& LBracePos() const noexcept { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const noexcept { return rbPos; }
private:
    std::unique_ptr<Node> exprt;
    std::unique_ptr<Node> subject;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class ExportNode : public Node
{
public:
    ExportNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ImportNode : public Node
{
public:
    ImportNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ImportDeclarationNode : public CompoundNode
{
public:
    ImportDeclarationNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ImportDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* imprt_, Node* subject_, Node* attributes_, Node* semicolon_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Import() const noexcept { return imprt.get(); }
    inline Node* Subject() const noexcept { return subject.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
private:
    std::unique_ptr<Node> imprt;
    std::unique_ptr<Node> subject;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

class ModulePartitionNode : public UnaryNode
{
public:
    ModulePartitionNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ModulePartitionNode(const soul::ast::SourcePos& sourcePos_, Node* moduleName_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ModuleNode : public Node
{
public:
    ModuleNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class GlobalModuleFragmentNode : public CompoundNode
{
public:
    GlobalModuleFragmentNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    GlobalModuleFragmentNode(const soul::ast::SourcePos& sourcePos_, Node* modle_, Node* semicolon_, Node* declarations_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Module() const noexcept { return modle.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline Node* Declarations() const noexcept { return declarations.get(); }
private:
    std::unique_ptr<Node> modle;
    std::unique_ptr<Node> semicolon;
    std::unique_ptr<Node> declarations;
};

class PrivateModuleFragmentNode : public CompoundNode
{
public:
    PrivateModuleFragmentNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    PrivateModuleFragmentNode(const soul::ast::SourcePos& sourcePos_, Node* modle_, Node* colon_, Node* privat_, Node* semicolon_, Node* declarations_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Module() const noexcept { return modle.get(); }
    inline Node* Colon() const noexcept { return colon.get(); }
    inline Node* Private() const noexcept { return privat.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline Node* Declarations() const noexcept { return declarations.get(); }
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
    AngleHeaderName(const soul::ast::SourcePos& sourcePos_) noexcept;
    AngleHeaderName(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const std::u32string& Rep() const noexcept { return rep; }
private:
    std::u32string rep;
};

class QuoteHeaderName : public Node
{
public:
    QuoteHeaderName(const soul::ast::SourcePos& sourcePos_) noexcept;
    QuoteHeaderName(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const std::u32string& Rep() const noexcept { return rep; }
private:
    std::u32string rep;
};

} // namespace otava::ast
