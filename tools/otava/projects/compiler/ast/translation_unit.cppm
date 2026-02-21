// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.translation.unit;

import std;
import otava.ast.node;
import otava.ast.reader;

export namespace otava::ast {

class TranslationUnitNode : public CompoundNode
{
public:
    TranslationUnitNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    TranslationUnitNode(const soul::ast::SourcePos& sourcePos_, Node* unit_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Unit() const noexcept { return unit.get(); }
private:
    std::unique_ptr<Node> unit;
};

class ModuleUnitNode : public CompoundNode
{
public:
    ModuleUnitNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ModuleUnitNode(const soul::ast::SourcePos& sourcePos_, Node* globalModuleFragment_, Node* moduleDeclaration_, Node* declarations_,
        Node* privateModuleFragment_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* GlobalModuleFragment() const noexcept { return globalModuleFragment.get(); }
    inline Node* ModuleDeclaration() const noexcept { return moduleDeclaration.get(); }
    inline Node* Declarations() const noexcept { return declarations.get(); }
    inline Node* PrivateModuleFragment() const noexcept { return privateModuleFragment.get(); }
private:
    std::unique_ptr<Node> globalModuleFragment;
    std::unique_ptr<Node> moduleDeclaration;
    std::unique_ptr<Node> declarations;
    std::unique_ptr<Node> privateModuleFragment;
};

} // namespace otava::ast
