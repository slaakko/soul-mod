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

std::expected<Node*, int> FunctionDefinitionNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    Node* clonedDeclSpecifiers = nullptr;
    if (declSpecifiers)
    {
        std::expected<Node*, int> d = declSpecifiers->Clone();
        if (!d) return d;
        clonedDeclSpecifiers = *d;
    }
    Node* clonedSpecifiers = nullptr;
    if (specifiers)
    {
        std::expected<Node*, int> s = specifiers->Clone();
        if (!s) return s;
        clonedSpecifiers = *s;
    }
    std::expected<Node*, int> d = declarator->Clone();
    if (!d) return d;
    std::expected<Node*, int> b = functionBody->Clone();
    if (!b)  return b;
    FunctionDefinitionNode* clone = new FunctionDefinitionNode(GetSourcePos(), clonedAttributes, clonedDeclSpecifiers, *d, clonedSpecifiers, *b);
    return std::expected<Node*, int>(clone);
}

void FunctionDefinitionNode::ResetFunctionBody(Node* functionBody_)
{
    functionBody.reset(functionBody_);
}

void FunctionDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> FunctionDefinitionNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(declSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(declarator.get());
    if (!rv) return rv;
    rv = writer.Write(specifiers.get());
    if (!rv) return rv;
    rv = writer.Write(functionBody.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> FunctionBodyNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    FunctionBodyNode* clone = new FunctionBodyNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
}

void FunctionBodyNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultNode::DefaultNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::defaultNode, sourcePos_)
{
}

std::expected<Node*, int> DefaultNode::Clone() const
{
    DefaultNode* clone = new DefaultNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DefaultNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DeleteNode::DeleteNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::deleteNode, sourcePos_)
{
}

std::expected<Node*, int>  DeleteNode::Clone() const
{
    DeleteNode* clone = new DeleteNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> DefaultedOrDeletedFunctionNode::Clone() const
{
    std::expected<Node*, int> a = assign->Clone();
    if (!a) return a;
    std::expected<Node*, int> d = defaultOrDelete->Clone();
    if (!d) return d;
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    DefaultedOrDeletedFunctionNode* clone = new DefaultedOrDeletedFunctionNode(GetSourcePos(), *a, *d, *s);
    return std::expected<Node*, int>(clone);
}

void DefaultedOrDeletedFunctionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DefaultedOrDeletedFunctionNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(assign.get());
    if (!rv) return rv;
    rv = writer.Write(defaultOrDelete.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> NoDeclSpecFunctionDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> d = declarator->Clone();
    if (!d) return d;
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    NoDeclSpecFunctionDeclarationNode* clone = new NoDeclSpecFunctionDeclarationNode(GetSourcePos(), clonedAttributes, *d, *s);
    return std::expected<Node*, int>(clone);
}

void NoDeclSpecFunctionDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NoDeclSpecFunctionDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(declarator.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> OperatorNode::Clone() const
{
    OperatorNode* clone = new OperatorNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> NewArrayOpNode::Clone() const
{
    NewArrayOpNode* clone = new NewArrayOpNode(GetSourcePos(), lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void NewArrayOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NewArrayOpNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> NewOpNode::Clone() const
{
    NewOpNode* clone = new NewOpNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> DeleteArrayOpNode::Clone() const
{
    DeleteArrayOpNode* clone = new DeleteArrayOpNode(GetSourcePos(), lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void DeleteArrayOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DeleteArrayOpNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> DeleteOpNode::Clone() const
{
    DeleteOpNode* clone = new DeleteOpNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DeleteOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CoAwaitOpNode::CoAwaitOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::coAwaitOpNode, sourcePos_)
{
}

std::expected<Node*, int> CoAwaitOpNode::Clone() const
{
    CoAwaitOpNode* clone = new CoAwaitOpNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void CoAwaitOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InvokeOpNode::InvokeOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::invokeOpNode, sourcePos_)
{
}

std::expected<Node*, int> InvokeOpNode::Clone() const
{
    InvokeOpNode* clone = new InvokeOpNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void InvokeOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SubscriptOpNode::SubscriptOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::subscriptOpNode, sourcePos_)
{
}

std::expected<Node*, int> SubscriptOpNode::Clone() const
{
    SubscriptOpNode* clone = new SubscriptOpNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> OperatorFunctionIdNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    OperatorFunctionIdNode* clone = new OperatorFunctionIdNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> ConversionFunctionIdNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    ConversionFunctionIdNode* clone = new ConversionFunctionIdNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> ConversionTypeIdNode::Clone() const
{
    Node* clonedConversionDeclarator = nullptr;
    if (conversionDeclarator)
    {
        std::expected<Node*, int> c = conversionDeclarator->Clone();
        if (!c) return c;
        clonedConversionDeclarator = *c;
    }
    std::expected<Node*, int> t = typeSpecifierSeq->Clone();
    if (!t) return t;
    ConversionTypeIdNode* clone = new ConversionTypeIdNode(GetSourcePos(), *t, clonedConversionDeclarator);
    return std::expected<Node*, int>(clone);
}

void ConversionTypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ConversionTypeIdNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(typeSpecifierSeq.get());
    if (!rv) return rv;
    rv = writer.Write(conversionDeclarator.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> ConversionDeclaratorNode::Clone() const
{
    Node* clonedConversionDeclarator = nullptr;
    if (conversionDeclarator)
    {
        std::expected<Node*, int> c = conversionDeclarator->Clone();
        if (!c) return c;
        clonedConversionDeclarator = *c;
    }
    std::expected<Node*, int> p = ptrOp->Clone();
    if (!p) return p;
    ConversionDeclaratorNode* clone = new ConversionDeclaratorNode(GetSourcePos(), *p, clonedConversionDeclarator);
    return std::expected<Node*, int>(clone);
}

void ConversionDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ConversionDeclaratorNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(ptrOp.get());
    if (!rv) return rv;
    rv = writer.Write(conversionDeclarator.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> DestructorIdNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    DestructorIdNode* clone = new DestructorIdNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
}

void DestructorIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ParameterNode::ParameterNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::parameterNode, sourcePos_)
{
}

std::expected<Node*, int> ParameterNode::Clone() const
{
    ParameterNode* clone = new ParameterNode(GetSourcePos());
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clone->SetAttributes(*a);
    }
    std::expected<Node*, int> d = declSpecifiers->Clone();
    if (!d) return d;
    clone->SetDeclSpecifiers(*d);
    if (declarator)
    {
        std::expected<Node*, int> d = declarator->Clone();
        if (!d) return d;
        clone->SetDeclarator(*d);
    }
    if (assign)
    {
        std::expected<Node*, int> a = assign->Clone();
        if (!a) return a;
        clone->SetAssign(*a);
    }
    if (initializer)
    {
        std::expected<Node*, int> i = initializer->Clone();
        if (!i) return i;
        clone->SetInitializer(*i);
    }
    return std::expected<Node*, int>(clone);
}

void ParameterNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ParameterNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(declSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(declarator.get());
    if (!rv) return rv;
    rv = writer.Write(assign.get());
    if (!rv) return rv;
    rv = writer.Write(initializer.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> ParameterListNode::Clone() const
{
    ParameterListNode* clone = new ParameterListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    clone->SetLParenPos(lpPos);
    clone->SetRParenPos(rpPos);
    return std::expected<Node*, int>(clone);
}

void ParameterListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ParameterListNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = ListNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> NoexceptNode::Clone() const
{
    NoexceptNode* clone = new NoexceptNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> FunctionTryBlockNode::Clone() const
{
    Node* clonedCtorInitializer = nullptr;
    if (ctorInitializer)
    {
        std::expected<Node*, int> c = ctorInitializer->Clone();
        if (!c) return c;
        clonedCtorInitializer = *c;
    }
    std::expected<Node*, int> t = tryBlock->Clone();
    if (!t) return t;
    std::expected<Node*, int> h = handlers->Clone();
    if (!h) return h;
    FunctionTryBlockNode* clone = new FunctionTryBlockNode(GetSourcePos(), clonedCtorInitializer, *t, *h);
    return std::expected<Node*, int>(clone);
}

void FunctionTryBlockNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> FunctionTryBlockNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(ctorInitializer.get());
    if (!rv) return rv;
    rv = writer.Write(tryBlock.get());
    if (!rv) return rv;
    rv = writer.Write(handlers.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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
