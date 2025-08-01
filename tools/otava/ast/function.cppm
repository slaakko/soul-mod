// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.function;

import std;
import otava.ast.node;

export namespace otava::ast {

class FunctionDefinitionNode : public CompoundNode
{
public:
    FunctionDefinitionNode(const soul::ast::SourcePos& sourcePos_);
    FunctionDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* declSpecifiers_, Node* declarator_, Node* specifiers_, Node* functionBody_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* DeclSpecifiers() const { return declSpecifiers.get(); }
    inline Node* Declarator() const { return declarator.get(); }
    inline Node* Specifiers() const { return specifiers.get(); }
    inline Node* FunctionBody() const { return functionBody.get(); }
    void ResetFunctionBody(Node* functionBody_);
    inline std::int32_t Index() const { return index; }
    inline void SetIndex(std::int32_t index_) { index = index_; }
private:
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> declSpecifiers;
    std::unique_ptr<Node> declarator;
    std::unique_ptr<Node> specifiers;
    std::unique_ptr<Node> functionBody;
    std::int32_t index;
};

class FunctionBodyNode : public UnaryNode
{
public:
    FunctionBodyNode(const soul::ast::SourcePos& sourcePos_);
    FunctionBodyNode(const soul::ast::SourcePos& sourcePos_, Node* compoundStatement_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DefaultNode : public Node
{
public:
    DefaultNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DeleteNode : public Node
{
public:
    DeleteNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DefaultedOrDeletedFunctionNode : public CompoundNode
{
public:
    DefaultedOrDeletedFunctionNode(const soul::ast::SourcePos& sourcePos_);
    DefaultedOrDeletedFunctionNode(const soul::ast::SourcePos& sourcePos_, Node* assign_, Node* defaultOrDelete_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Assign() const { return assign.get(); }
    inline Node* DefaultOrDelete() const { return defaultOrDelete.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> assign;
    std::unique_ptr<Node> defaultOrDelete;
    std::unique_ptr<Node> semicolon;
};

class NoDeclSpecFunctionDeclarationNode : public CompoundNode
{
public:
    NoDeclSpecFunctionDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    NoDeclSpecFunctionDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* declarator_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Declarator() const { return declarator.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> declarator;
    std::unique_ptr<Node> semicolon;
};

class OperatorNode : public Node
{
public:
    OperatorNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class NewArrayOpNode : public CompoundNode
{
public:
    NewArrayOpNode(const soul::ast::SourcePos& sourcePos_);
    NewArrayOpNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LBracketPos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracketPos() const { return rbPos; }
private:
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class NewOpNode : public Node
{
public:
    NewOpNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DeleteArrayOpNode : public CompoundNode
{
public:
    DeleteArrayOpNode(const soul::ast::SourcePos& sourcePos_);
    DeleteArrayOpNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LBracketPos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracketPos() const { return rbPos; }
private:
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class DeleteOpNode : public Node
{
public:
    DeleteOpNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class CoAwaitOpNode : public Node
{
public:
    CoAwaitOpNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class InvokeOpNode : public Node
{
public:
    InvokeOpNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class SubscriptOpNode : public Node
{
public:
    SubscriptOpNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class OperatorFunctionIdNode : public BinaryNode
{
public:
    OperatorFunctionIdNode(const soul::ast::SourcePos& sourcePos_);
    OperatorFunctionIdNode(const soul::ast::SourcePos& sourcePos_, Node* operatorKwNode_, Node* op_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConversionFunctionIdNode : public BinaryNode
{
public:
    ConversionFunctionIdNode(const soul::ast::SourcePos& sourcePos_);
    ConversionFunctionIdNode(const soul::ast::SourcePos& sourcePos_, Node* operatorKwNode_, Node* conversionTypeId_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConversionTypeIdNode : public CompoundNode
{
public:
    ConversionTypeIdNode(const soul::ast::SourcePos& sourcePos_);
    ConversionTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifierSeq_, Node* conversionDeclarator_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TypeSpecifierSeq() const { return typeSpecifierSeq.get(); }
    inline Node* ConversionDeclarator() const { return conversionDeclarator.get(); }
private:
    std::unique_ptr<Node> typeSpecifierSeq;
    std::unique_ptr<Node> conversionDeclarator;
};

class ConversionDeclaratorNode : public CompoundNode
{
public:
    ConversionDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    ConversionDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* ptrOp_, Node* conversionDeclarator_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* PtrOp() const { return ptrOp.get(); }
    inline Node* ConversionDeclarator() const { return conversionDeclarator.get(); }
private:
    std::unique_ptr<Node> ptrOp;
    std::unique_ptr<Node> conversionDeclarator;
};

class DestructorIdNode : public UnaryNode
{
public:
    DestructorIdNode(const soul::ast::SourcePos& sourcePos_);
    DestructorIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeName_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ParameterNode : public CompoundNode
{
public:
    ParameterNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const { return attributes.get(); }
    void SetAttributes(Node* attributes_);
    inline Node* DeclSpecifiers() const { return declSpecifiers.get(); }
    void SetDeclSpecifiers(Node* declSpecifiers_);
    inline Node* Declarator() const { return declarator.get(); }
    void SetDeclarator(Node* declarator_);
    inline Node* Assign() const { return assign.get(); }
    void SetAssign(Node* assign_);
    inline Node* Initializer() const { return initializer.get(); }
    void SetInitializer(Node* initializer_);
private:
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> declSpecifiers;
    std::unique_ptr<Node> declarator;
    std::unique_ptr<Node> assign;
    std::unique_ptr<Node> initializer;
};

class ParameterListNode : public ListNode
{
public:
    ParameterListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline void SetLParenPos(const soul::ast::SourcePos& lpPos_) { lpPos = lpPos_; }
    inline void SetRParenPos(const soul::ast::SourcePos& rpPos_) { rpPos = rpPos_; }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class NoexceptNode : public Node
{
public:
    NoexceptNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class FunctionTryBlockNode : public CompoundNode
{
public:
    FunctionTryBlockNode(const soul::ast::SourcePos& sourcePos_);
    FunctionTryBlockNode(const soul::ast::SourcePos& sourcePos_, Node* ctorInitializer_, Node* tryBlock_, Node* handlers_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* CtorInitializer() const { return ctorInitializer.get(); }
    inline Node* TryBlock() const { return tryBlock.get(); }
    inline Node* Handlers() const { return handlers.get(); }
private:
    std::unique_ptr<Node> ctorInitializer;
    std::unique_ptr<Node> tryBlock;
    std::unique_ptr<Node> handlers;
};

} // namespace otava::ast
