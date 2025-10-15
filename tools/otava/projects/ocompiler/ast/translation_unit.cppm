// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.translation.unit;

import std;
import otava.ast.node;

export namespace otava::ast {

class TranslationUnitNode : public CompoundNode
{
public:
    TranslationUnitNode(const soul::ast::SourcePos& sourcePos_);
    TranslationUnitNode(const soul::ast::SourcePos& sourcePos_, Node* unit_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* Unit() const { return unit.get(); }
private:
    std::unique_ptr<Node> unit;
};

class ModuleUnitNode : public CompoundNode
{
public:
    ModuleUnitNode(const soul::ast::SourcePos& sourcePos_);
    ModuleUnitNode(const soul::ast::SourcePos& sourcePos_, Node* globalModuleFragment_, Node* moduleDeclaration_, Node* declarations_, Node* privateModuleFragment_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* GlobalModuleFragment() const { return globalModuleFragment.get(); }
    inline Node* ModuleDeclaration() const { return moduleDeclaration.get(); }
    inline Node* Declarations() const { return declarations.get(); }
    inline Node* PrivateModuleFragment() const { return privateModuleFragment.get(); }
private:
    std::unique_ptr<Node> globalModuleFragment;
    std::unique_ptr<Node> moduleDeclaration;
    std::unique_ptr<Node> declarations;
    std::unique_ptr<Node> privateModuleFragment;
};

} // namespace otava::ast
