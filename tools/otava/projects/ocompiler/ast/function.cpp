// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.function;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

FunctionDefinitionNode::FunctionDefinitionNode(const soul::ast::SourcePos& sourcePos_) :
    CompoundNode(NodeKind::functionDefinitionNode, sourcePos_), index(0)
{
}

FunctionDefinitionNode::FunctionDefinitionNode(const soul::ast::SourcePos& sourcePos_,
    Node* attributes_, Node* declSpecifiers_, Node* declarator_, Node* specifiers_, Node* functionBody_) :
    CompoundNode(NodeKind::functionDefinitionNode, sourcePos_),
    attributes(attributes_),
    declSpecifiers(declSpecifiers_),
    declarator(declarator_),
    specifiers(specifiers_),
    functionBody(functionBody_),
    index(0)
{
}

Node* FunctionDefinitionNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    Node* clonedDeclSpecifiers = nullptr;
    if (declSpecifiers)
    {
        clonedDeclSpecifiers = declSpecifiers->Clone();
    }
    Node* clonedSpecifiers = nullptr;
    if (specifiers)
    {
        clonedSpecifiers = specifiers->Clone();
    }
    FunctionDefinitionNode* clone = new FunctionDefinitionNode(GetSourcePos(), clonedAttributes, clonedDeclSpecifiers, declarator->Clone(), clonedSpecifiers, functionBody->Clone());
    return clone;
}

void FunctionDefinitionNode::ResetFunctionBody(Node* functionBody_)
{
    functionBody.reset(functionBody_);
}

void FunctionDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionDefinitionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(attributes.get());
    writer.Write(declSpecifiers.get());
    writer.Write(declarator.get());
    writer.Write(specifiers.get());
    writer.Write(functionBody.get());
}

std::expected<bool, int> FunctionDefinitionNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarator.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    specifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    functionBody.reset(*nrv);
    return std::expected<bool, int>(true);
}

FunctionBodyNode::FunctionBodyNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::functionBodyNode, sourcePos_, nullptr)
{
}

FunctionBodyNode::FunctionBodyNode(const soul::ast::SourcePos& sourcePos_, Node* compoundStatement_) : UnaryNode(NodeKind::functionBodyNode, sourcePos_, compoundStatement_)
{
}

Node* FunctionBodyNode::Clone() const
{
    FunctionBodyNode* clone = new FunctionBodyNode(GetSourcePos(), Child()->Clone());
    return clone;
}

void FunctionBodyNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultNode::DefaultNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::defaultNode, sourcePos_)
{
}

Node* DefaultNode::Clone() const
{
    DefaultNode* clone = new DefaultNode(GetSourcePos());
    return clone;
}

void DefaultNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DeleteNode::DeleteNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::deleteNode, sourcePos_)
{
}

Node* DeleteNode::Clone() const
{
    DeleteNode* clone = new DeleteNode(GetSourcePos());
    return clone;
}

void DeleteNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultedOrDeletedFunctionNode::DefaultedOrDeletedFunctionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::defaultedOrDeletedFunctionNode, sourcePos_)
{
}

DefaultedOrDeletedFunctionNode::DefaultedOrDeletedFunctionNode(const soul::ast::SourcePos& sourcePos_, Node* assign_, Node* defaultOrDelete_, Node* semicolon_) :
    CompoundNode(NodeKind::defaultedOrDeletedFunctionNode, sourcePos_), assign(assign_), defaultOrDelete(defaultOrDelete_), semicolon(semicolon_)
{
}

Node* DefaultedOrDeletedFunctionNode::Clone() const
{
    DefaultedOrDeletedFunctionNode* clone = new DefaultedOrDeletedFunctionNode(GetSourcePos(), assign->Clone(), defaultOrDelete->Clone(), semicolon->Clone());
    return clone;
}

void DefaultedOrDeletedFunctionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DefaultedOrDeletedFunctionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(assign.get());
    writer.Write(defaultOrDelete.get());
    writer.Write(semicolon.get());
}

std::expected<bool, int> DefaultedOrDeletedFunctionNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    assign.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    defaultOrDelete.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

NoDeclSpecFunctionDeclarationNode::NoDeclSpecFunctionDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::noDeclSpecFunctionDeclarationNode, sourcePos_)
{
}

NoDeclSpecFunctionDeclarationNode::NoDeclSpecFunctionDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* declarator_, Node* semicolon_) :
    CompoundNode(NodeKind::noDeclSpecFunctionDeclarationNode, sourcePos_), attributes(attributes_), declarator(declarator_), semicolon(semicolon_)
{
}

Node* NoDeclSpecFunctionDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    NoDeclSpecFunctionDeclarationNode* clone = new NoDeclSpecFunctionDeclarationNode(GetSourcePos(), clonedAttributes, declarator->Clone(), semicolon->Clone());
    return clone;
}

void NoDeclSpecFunctionDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NoDeclSpecFunctionDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declarator.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
}

std::expected<bool, int> NoDeclSpecFunctionDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarator.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

OperatorNode::OperatorNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::operatorNode, sourcePos_)
{
}

Node* OperatorNode::Clone() const
{
    OperatorNode* clone = new OperatorNode(GetSourcePos());
    return clone;
}

void OperatorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NewArrayOpNode::NewArrayOpNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::newArrayOpNode, sourcePos_)
{
}

NewArrayOpNode::NewArrayOpNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::newArrayOpNode, sourcePos_), lbPos(lbPos_), rbPos(rbPos_)
{
}

Node* NewArrayOpNode::Clone() const
{
    NewArrayOpNode* clone = new NewArrayOpNode(GetSourcePos(), lbPos, rbPos);
    return clone;
}

void NewArrayOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NewArrayOpNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(lbPos);
    writer.Write(rbPos);

}

std::expected<bool, int> NewArrayOpNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

NewOpNode::NewOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::newOpNode, sourcePos_)
{
}

Node* NewOpNode::Clone() const
{
    NewOpNode* clone = new NewOpNode(GetSourcePos());
    return clone;
}

void NewOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DeleteArrayOpNode::DeleteArrayOpNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::deleteArrayOpNode, sourcePos_)
{
}

DeleteArrayOpNode::DeleteArrayOpNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::deleteArrayOpNode, sourcePos_)
{
}

Node* DeleteArrayOpNode::Clone() const
{
    DeleteArrayOpNode* clone = new DeleteArrayOpNode(GetSourcePos(), lbPos, rbPos);
    return clone;
}

void DeleteArrayOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DeleteArrayOpNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(lbPos);
    writer.Write(rbPos);
}

std::expected<bool, int> DeleteArrayOpNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

DeleteOpNode::DeleteOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::deleteOpNode, sourcePos_)
{
}

Node* DeleteOpNode::Clone() const
{
    DeleteOpNode* clone = new DeleteOpNode(GetSourcePos());
    return clone;
}

void DeleteOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CoAwaitOpNode::CoAwaitOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::coAwaitOpNode, sourcePos_)
{
}

Node* CoAwaitOpNode::Clone() const
{
    CoAwaitOpNode* clone = new CoAwaitOpNode(GetSourcePos());
    return clone;
}

void CoAwaitOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InvokeOpNode::InvokeOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::invokeOpNode, sourcePos_)
{
}

Node* InvokeOpNode::Clone() const
{
    InvokeOpNode* clone = new InvokeOpNode(GetSourcePos());
    return clone;
}

void InvokeOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SubscriptOpNode::SubscriptOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::subscriptOpNode, sourcePos_)
{
}

Node* SubscriptOpNode::Clone() const
{
    SubscriptOpNode* clone = new SubscriptOpNode(GetSourcePos());
    return clone;
}

void SubscriptOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OperatorFunctionIdNode::OperatorFunctionIdNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::operatorFnIdNode, sourcePos_, nullptr, nullptr)
{
}

OperatorFunctionIdNode::OperatorFunctionIdNode(const soul::ast::SourcePos& sourcePos_, Node* operatorKwNode_, Node* op_) :
    BinaryNode(NodeKind::operatorFnIdNode, sourcePos_, operatorKwNode_, op_)
{
}

Node* OperatorFunctionIdNode::Clone() const
{
    OperatorFunctionIdNode* clone = new OperatorFunctionIdNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void OperatorFunctionIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConversionFunctionIdNode::ConversionFunctionIdNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::conversionFnIdNode, sourcePos_, nullptr, nullptr)
{
}

ConversionFunctionIdNode::ConversionFunctionIdNode(const soul::ast::SourcePos& sourcePos_, Node* operatorKwNode_, Node* conversionTypeId_) :
    BinaryNode(NodeKind::conversionFnIdNode, sourcePos_, operatorKwNode_, conversionTypeId_)
{
}

Node* ConversionFunctionIdNode::Clone() const
{
    ConversionFunctionIdNode* clone = new ConversionFunctionIdNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void ConversionFunctionIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConversionTypeIdNode::ConversionTypeIdNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::conversionTypeIdNode, sourcePos_)
{
}

ConversionTypeIdNode::ConversionTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifierSeq_, Node* conversionDeclarator_) :
    CompoundNode(NodeKind::conversionTypeIdNode, sourcePos_), typeSpecifierSeq(typeSpecifierSeq_), conversionDeclarator(conversionDeclarator_)
{
}

Node* ConversionTypeIdNode::Clone() const
{
    Node* clonedConversionDeclarator = nullptr;
    if (conversionDeclarator)
    {
        clonedConversionDeclarator = conversionDeclarator->Clone();
    }
    ConversionTypeIdNode* clone = new ConversionTypeIdNode(GetSourcePos(), typeSpecifierSeq->Clone(), clonedConversionDeclarator);
    return clone;
}

void ConversionTypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConversionTypeIdNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(typeSpecifierSeq.get());
    writer.Write(conversionDeclarator.get());
}

std::expected<bool, int> ConversionTypeIdNode::Read(Reader& reader)
{
    std::expected<bool, int>  rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeSpecifierSeq.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    conversionDeclarator.reset(*nrv);
    return std::expected<bool, int>(true);
}

ConversionDeclaratorNode::ConversionDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::conversionDeclaratorNode, sourcePos_)
{
}

ConversionDeclaratorNode::ConversionDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* ptrOp_, Node* conversionDeclarator_) :
    CompoundNode(NodeKind::conversionDeclaratorNode, sourcePos_), ptrOp(ptrOp_), conversionDeclarator(conversionDeclarator_)
{
}

Node* ConversionDeclaratorNode::Clone() const
{
    Node* clonedConversionDeclarator = nullptr;
    if (conversionDeclarator)
    {
        clonedConversionDeclarator = conversionDeclarator->Clone();
    }
    ConversionDeclaratorNode* clone = new ConversionDeclaratorNode(GetSourcePos(), ptrOp->Clone(), clonedConversionDeclarator);
    return clone;
}

void ConversionDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConversionDeclaratorNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(ptrOp.get());
    writer.Write(conversionDeclarator.get());
}

std::expected<bool, int> ConversionDeclaratorNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    ptrOp.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    conversionDeclarator.reset(*nrv);
    return std::expected<bool, int>(true);
}

DestructorIdNode::DestructorIdNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::destructorIdNode, sourcePos_, nullptr)
{
}

DestructorIdNode::DestructorIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeName_) : UnaryNode(NodeKind::destructorIdNode, sourcePos_, typeName_)
{
}

Node* DestructorIdNode::Clone() const
{
    DestructorIdNode* clone = new DestructorIdNode(GetSourcePos(), Child()->Clone());
    return clone;
}

void DestructorIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ParameterNode::ParameterNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::parameterNode, sourcePos_)
{
}

Node* ParameterNode::Clone() const
{
    ParameterNode* clone = new ParameterNode(GetSourcePos());
    if (attributes)
    {
        clone->SetAttributes(attributes->Clone());
    }
    clone->SetDeclSpecifiers(declSpecifiers->Clone());
    if (declarator)
    {
        clone->SetDeclarator(declarator->Clone());
    }
    if (assign)
    {
        clone->SetAssign(assign->Clone());
    }
    if (initializer)
    {
        clone->SetInitializer(initializer->Clone());
    }
    return clone;
}

void ParameterNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ParameterNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(attributes.get());
    writer.Write(declSpecifiers.get());
    writer.Write(declarator.get());
    writer.Write(assign.get());
    writer.Write(initializer.get());
}

std::expected<bool, int> ParameterNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarator.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    assign.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initializer.reset(*nrv);
    return std::expected<bool, int>(true);
}

void ParameterNode::SetAttributes(Node* attributes_)
{
    attributes.reset(attributes_);
}

void ParameterNode::SetDeclSpecifiers(Node* declSpecifiers_)
{
    declSpecifiers.reset(declSpecifiers_);
}

void ParameterNode::SetDeclarator(Node* declarator_)
{
    declarator.reset(declarator_);
}

void ParameterNode::SetAssign(Node* assign_)
{
    assign.reset(assign_);
}

void ParameterNode::SetInitializer(Node* initializer_)
{
    initializer.reset(initializer_);
}

ParameterListNode::ParameterListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::parameterListNode, sourcePos_)
{
}

Node* ParameterListNode::Clone() const
{
    ParameterListNode* clone = new ParameterListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetLParenPos(lpPos);
    clone->SetRParenPos(rpPos);
    return clone;
}

void ParameterListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ParameterListNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

std::expected<bool, int> ParameterListNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = ListNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

NoexceptNode::NoexceptNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::noexceptNode, sourcePos_)
{
}

Node* NoexceptNode::Clone() const
{
    NoexceptNode* clone = new NoexceptNode(GetSourcePos());
    return clone;
}

void NoexceptNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FunctionTryBlockNode::FunctionTryBlockNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::functionTryBlock, sourcePos_)
{
}

FunctionTryBlockNode::FunctionTryBlockNode(const soul::ast::SourcePos& sourcePos_, Node* ctorInitializer_, Node* tryBlock_, Node* handlers_) :
    CompoundNode(NodeKind::functionTryBlock, sourcePos_), ctorInitializer(ctorInitializer_), tryBlock(tryBlock_), handlers(handlers_)
{
}

Node* FunctionTryBlockNode::Clone() const
{
    Node* clonedCtorInitializer = nullptr;
    if (ctorInitializer)
    {
        clonedCtorInitializer = ctorInitializer->Clone();
    }
    FunctionTryBlockNode* clone = new FunctionTryBlockNode(GetSourcePos(), clonedCtorInitializer, tryBlock->Clone(), handlers->Clone());
    return clone;
}

void FunctionTryBlockNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionTryBlockNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(ctorInitializer.get());
    writer.Write(tryBlock.get());
    writer.Write(handlers.get());
}

std::expected<bool, int> FunctionTryBlockNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    ctorInitializer.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    tryBlock.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    handlers.reset(*nrv);
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
