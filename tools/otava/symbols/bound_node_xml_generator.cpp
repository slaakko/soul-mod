// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.bound.node.xml.generator;

import otava.symbols.bound.tree.visitor;
import otava.symbols.function.symbol;
import otava.symbols.variable.symbol;
import otava.symbols.type.symbol;
import otava.symbols.enums;
import otava.symbols.value;
import otava.symbols.function.group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.alias.group.symbol;
import otava.symbols.classes;
import soul.xml.dom;
import util;

namespace otava::symbols {

class BoundNodeXmlGenerator : public BoundTreeVisitor
{
public:
    std::unique_ptr<soul::xml::Element> GetElement() { return std::unique_ptr<soul::xml::Element>(element); }
    void Visit(BoundCompileUnitNode& node) override;
    void Visit(BoundClassNode& node) override;
    void Visit(BoundCtorInitializerNode& node) override;
    void Visit(BoundDtorTerminatorNode& node) override;
    void Visit(BoundEmptyStatementNode& node) override;
    void Visit(BoundFunctionNode& node) override;
    void Visit(BoundCompoundStatementNode& node) override;
    void Visit(BoundIfStatementNode& node) override;
    void Visit(BoundSwitchStatementNode& node) override;
    void Visit(BoundCaseStatementNode& node) override;
    void Visit(BoundDefaultStatementNode& node) override;
    void Visit(BoundWhileStatementNode& node) override;
    void Visit(BoundDoStatementNode& node) override;
    void Visit(BoundForStatementNode& node) override;
    void Visit(BoundSequenceStatementNode& node) override;
    void Visit(BoundBreakStatementNode& node) override;
    void Visit(BoundContinueStatementNode& node) override;
    void Visit(BoundReturnStatementNode& node) override;
    void Visit(BoundGotoStatementNode& node) override;
    void Visit(BoundLabeledStatementNode& node) override;
    void Visit(BoundConstructionStatementNode& node) override;
    void Visit(BoundExpressionStatementNode& node) override;
    void Visit(BoundSetVPtrStatementNode& node) override;
    void Visit(BoundAliasDeclarationStatementNode& node) override;
    void Visit(BoundLiteralNode& node) override;
    void Visit(BoundStringLiteralNode& node) override;
    void Visit(BoundVariableNode& node) override;
    void Visit(BoundParentVariableNode& node) override;
    void Visit(BoundParameterNode& node) override;
    void Visit(BoundParentParameterNode& node) override;
    void Visit(BoundEnumConstant& node) override;
    void Visit(BoundFunctionGroupNode& node) override;
    void Visit(BoundClassGroupNode& node) override;
    void Visit(BoundAliasGroupNode& node) override;
    void Visit(BoundTypeNode& node) override;
    void Visit(BoundMemberExprNode& node) override;
    void Visit(BoundFunctionCallNode& node) override;
    void Visit(BoundEmptyFunctionCallNode& node) override;
    void Visit(BoundFunctionPtrCallNode& node) override;
    void Visit(BoundInvokeNode& node) override;
    void Visit(BoundExpressionSequenceNode& node) override;
    void Visit(BoundExpressionListNode& node) override;
    void Visit(BoundConjunctionNode& node) override;
    void Visit(BoundDisjunctionNode& node) override;
    void Visit(BoundConditionalExprNode& node) override;
    void Visit(BoundConversionNode& node) override;
    void Visit(BoundAddressOfNode& node) override;
    void Visit(BoundDereferenceNode& node) override;
    void Visit(BoundRefToPtrNode& node) override;
    void Visit(BoundPtrToRefNode& node) override;
    void Visit(BoundDefaultInitNode& node) override;
    void Visit(BoundTemporaryNode& node) override;
    void Visit(BoundConstructTemporaryNode& node) override;
    void Visit(BoundConstructExpressionNode& node) override;
    void Visit(BoundGlobalVariableDefinitionNode& node) override;
    void Visit(BoundEmptyDestructorNode& node) override;
    void Visit(BoundFunctionValueNode& node) override;
    void Visit(BoundVariableAsVoidPtrNode& node) override;
    void Visit(BoundOperatorFnNode& node) override;
private:
    soul::xml::Element* element;
    void SetStatementAttributes(BoundStatementNode* statement);
    void SetCompoundStatementAttributes(BoundCompoundStatementNode* compoundStatement);
    void SetExpressionAttributes(BoundExpressionNode* expr);
};

void BoundNodeXmlGenerator::SetStatementAttributes(BoundStatementNode* statement)
{
    if (statement->Block())
    {
        element->SetAttribute("blockId", std::to_string(statement->Block()->BlockId()));
    }
    element->SetAttribute("statementIndex", std::to_string(statement->StatementIndex()));
}

void BoundNodeXmlGenerator::SetCompoundStatementAttributes(BoundCompoundStatementNode* compoundStatement)
{
    element->SetAttribute("blockId", std::to_string(compoundStatement->BlockId()));
}

void BoundNodeXmlGenerator::SetExpressionAttributes(BoundExpressionNode* expr)
{
    if (expr->GetType())
    {
        element->SetAttribute("type", util::ToUtf8(expr->GetType()->FullName()));
    }
    BoundExpressionFlags flags = expr->Flags();
    if ((flags & BoundExpressionFlags::bindToRvalueRef) != BoundExpressionFlags::none)
    {
        element->SetAttribute("bindToRvalueRef", "true");
    }
    if ((flags & BoundExpressionFlags::virtualCall) != BoundExpressionFlags::none)
    {
        element->SetAttribute("virtualCall", "true");
    }
    if ((flags & BoundExpressionFlags::deref) != BoundExpressionFlags::none)
    {
        element->SetAttribute("deref", "true");
    }
}

void BoundNodeXmlGenerator::Visit(BoundCompileUnitNode& node)
{
    element = soul::xml::MakeElement("compile_unit");
    for (const auto& node : node.BoundNodes())
    {
        node->Accept(*this);
    }
}

void BoundNodeXmlGenerator::Visit(BoundClassNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("class");
    element->SetAttribute("fullName", util::ToUtf8(node.GetClass()->FullName()));
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundCtorInitializerNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* ctorInitalizerElement = soul::xml::MakeElement("ctorInitializer");
    soul::xml::Element* baseInitializersElement = soul::xml::MakeElement("baseInitializers");
    soul::xml::Element* memberInitializersElement = soul::xml::MakeElement("memberInitializers");
    soul::xml::Element* setVPtrStatementsElement = soul::xml::MakeElement("setVPtrStatements");
    ctorInitalizerElement->AppendChild(baseInitializersElement);
    ctorInitalizerElement->AppendChild(memberInitializersElement);
    ctorInitalizerElement->AppendChild(setVPtrStatementsElement);
    for (const auto& baseInitializer : node.BaseInitializers())
    {
        element = baseInitializersElement;
        baseInitializer->Accept(*this);
    }
    for (const auto& memberInitializer : node.MemberInitializers())
    {
        element = memberInitializersElement;
        memberInitializer->Accept(*this);
    }
    for (const auto& setVPtrStatement : node.SetVPtrStatements())
    {
        element = setVPtrStatementsElement;
        setVPtrStatement->Accept(*this);
    }
    prevElement->AppendChild(ctorInitalizerElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundDtorTerminatorNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* dtorTerminatorElement = soul::xml::MakeElement("dtorTerminator");
    soul::xml::Element* setVPtrStatementsElement = soul::xml::MakeElement("setVPtrStatements");
    soul::xml::Element* memberTerminatorsElement = soul::xml::MakeElement("memberTerminators");
    dtorTerminatorElement->AppendChild(setVPtrStatementsElement);
    dtorTerminatorElement->AppendChild(memberTerminatorsElement);
    for (const auto& setVPtrStatement : node.SetVPtrStatements())
    {
        element = setVPtrStatementsElement;
        setVPtrStatement->Accept(*this);
    }
    for (const auto& memberTerminator : node.MemberTerminators())
    {
        element = memberTerminatorsElement;
        memberTerminator->Accept(*this);
    }
    prevElement->AppendChild(dtorTerminatorElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundEmptyStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("emptyStatement");
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundFunctionNode& node)
{
 soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("function");
    element->SetAttribute("name", util::ToUtf8(node.GetFunctionDefinitionSymbol()->FullName()));
    node.Body()->Accept(*this);
    if (prevElement)
    {
        prevElement->AppendChild(element);
        element = prevElement;
    }
}

void BoundNodeXmlGenerator::Visit(BoundCompoundStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("compound");
    SetCompoundStatementAttributes(&node);
    for (const auto& statement : node.Statements())
    {
        statement->Accept(*this);
    }
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundIfStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* ifElement = soul::xml::MakeElement("if");
    element = soul::xml::MakeElement("condition");
    ifElement->AppendChild(element);
    node.GetCondition()->Accept(*this);
    soul::xml::Element* thenElement = soul::xml::MakeElement("then");
    ifElement->AppendChild(thenElement);
    element = thenElement;
    node.ThenStatement()->Accept(*this);
    if (node.ElseStatement())
    {
        soul::xml::Element* elseElement = soul::xml::MakeElement("else");
        ifElement->AppendChild(elseElement);
        element = elseElement;
        node.ElseStatement()->Accept(*this);
    }
    element = ifElement;
    SetStatementAttributes(&node);
    element->SetAttribute("blockId", std::to_string(node.BlockId()));
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundSwitchStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* switchElement = soul::xml::MakeElement("switch");
    element = soul::xml::MakeElement("condition");
    switchElement->AppendChild(element);
    node.GetCondition()->Accept(*this);
    SetStatementAttributes(&node);
    element = switchElement;
    element->SetAttribute("blockId", std::to_string(node.BlockId()));
    node.Statement()->Accept(*this);
    prevElement->AppendChild(switchElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundCaseStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("case");
    SetStatementAttributes(&node);
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundDefaultStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("default");
    SetStatementAttributes(&node);
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundWhileStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* whileElement = soul::xml::MakeElement("while");
    element = whileElement;
    SetStatementAttributes(&node);
    element->SetAttribute("blockId", std::to_string(node.BlockId()));
    element = soul::xml::MakeElement("condition");
    whileElement->AppendChild(element);
    node.GetCondition()->Accept(*this);
    element = whileElement;
    node.Statement()->Accept(*this);
    prevElement->AppendChild(whileElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundDoStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* doElement = soul::xml::MakeElement("do");
    element = doElement;
    SetStatementAttributes(&node);
    element = soul::xml::MakeElement("condition");
    doElement->AppendChild(element);
    node.GetExpr()->Accept(*this);
    element = doElement;
    node.Statement()->Accept(*this);
    prevElement->AppendChild(doElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundForStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* forElement = soul::xml::MakeElement("for");
    element = forElement;
    SetStatementAttributes(&node);
    element->SetAttribute("blockId", std::to_string(node.BlockId()));
    if (node.InitStatement())
    {
        element = soul::xml::MakeElement("init");
        forElement->AppendChild(element);
        node.InitStatement()->Accept(*this);
    }
    if (node.GetCondition())
    {
        element = soul::xml::MakeElement("condition");
        forElement->AppendChild(element);
        node.GetCondition()->Accept(*this);
    }
    if (node.GetLoopExpr())
    {
        element = soul::xml::MakeElement("loop");
        forElement->AppendChild(element);
        node.GetLoopExpr()->Accept(*this);
    }
    element = forElement;
    node.Statement()->Accept(*this);
    prevElement->AppendChild(forElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundSequenceStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("sequence");
    SetStatementAttributes(&node);
    soul::xml::Element* sequenceElement = element;
    soul::xml::Element* firstElement = soul::xml::MakeElement("first");
    element->AppendChild(firstElement);
    element = firstElement;
    node.First()->Accept(*this);
    soul::xml::Element* secondElement = soul::xml::MakeElement("second");
    sequenceElement->AppendChild(secondElement);
    element = secondElement;
    node.Second()->Accept(*this);
    element = sequenceElement;
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundBreakStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("break");
    SetStatementAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundContinueStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("continue");
    SetStatementAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundReturnStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("return");
    SetStatementAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundGotoStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("goto");
    SetStatementAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundLabeledStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("labeled");
    SetStatementAttributes(&node);
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundConstructionStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* constructionElement = soul::xml::MakeElement("construction");
    constructionElement->SetAttribute("variable", util::ToUtf8(node.Variable()->Name()));
    element = constructionElement;
    SetStatementAttributes(&node);
    element = soul::xml::MakeElement("constructor_call");
    constructionElement->AppendChild(element);
    node.ConstructorCall()->Accept(*this);
    if (node.DestructorCall())
    {
        element = soul::xml::MakeElement("destructor_call");
        constructionElement->AppendChild(element);
        node.DestructorCall()->Accept(*this);
    }
    prevElement->AppendChild(constructionElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundExpressionStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* expressionStatementElement = soul::xml::MakeElement("expression");
    element = expressionStatementElement;
    SetStatementAttributes(&node);
    node.GetExpr()->Accept(*this);
    prevElement->AppendChild(expressionStatementElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundSetVPtrStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("vptr");
    SetStatementAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundAliasDeclarationStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("alias");
    SetStatementAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundLiteralNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("literal");
    SetExpressionAttributes(&node);
    soul::xml::Element* valueElement = soul::xml::MakeElement("value");
    valueElement->SetAttribute("kind", ValueKindStr(node.GetValue()->GetValueKind()));
    valueElement->SetAttribute("val", util::ToUtf8(node.GetValue()->Val()));
    element->AppendChild(valueElement);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundStringLiteralNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("string_literal");
    SetExpressionAttributes(&node);
    soul::xml::Element* valueElement = soul::xml::MakeElement("value");
    valueElement->SetAttribute("kind", ValueKindStr(node.GetValue()->GetValueKind()));
    valueElement->SetAttribute("val", util::ToUtf8(node.GetValue()->Val()));
    element->AppendChild(valueElement);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundVariableNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("variable");
    element->SetAttribute("name", util::ToUtf8(node.GetVariable()->Name()));
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundParentVariableNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("parent_variable");
    element->SetAttribute("name", util::ToUtf8(node.GetVariable()->Name()));
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundParameterNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("parameter");
    element->SetAttribute("name", util::ToUtf8(node.GetParameter()->Name()));
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundParentParameterNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("parent_parameter");
    element->SetAttribute("name", util::ToUtf8(node.GetParameter()->Name()));
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundEnumConstant& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("enum_constant");
    element->SetAttribute("name", util::ToUtf8(node.EnumConstant()->Name()));
    SetExpressionAttributes(&node);
    soul::xml::Element* valueElement = soul::xml::MakeElement("value");
    valueElement->SetAttribute("kind", ValueKindStr(node.EnumConstant()->GetValue()->GetValueKind()));
    valueElement->SetAttribute("val", util::ToUtf8(node.EnumConstant()->GetValue()->Val()));
    element->AppendChild(valueElement);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundFunctionGroupNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("function_group");
    element->SetAttribute("name", util::ToUtf8(node.GetFunctionGroupSymbol()->Name()));
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundClassGroupNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("class_group");
    element->SetAttribute("name", util::ToUtf8(node.GetClassGroupSymbol()->Name()));
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundAliasGroupNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("alias_group");
    element->SetAttribute("name", util::ToUtf8(node.GetAliasGroupSymbol()->Name()));
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundTypeNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("bound_type");
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundMemberExprNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* memberElement = soul::xml::MakeElement("bound_member");
    element = soul::xml::MakeElement("subject");
    memberElement->AppendChild(element);
    node.Subject()->Accept(*this);
    element = soul::xml::MakeElement("member");
    node.Member()->Accept(*this);
    memberElement->AppendChild(element);
    element = memberElement;
    SetExpressionAttributes(&node);
    prevElement->AppendChild(memberElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundFunctionCallNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* callElement = soul::xml::MakeElement("call");
    callElement->SetAttribute("fn", util::ToUtf8(node.GetFunctionSymbol()->FullName()));
    soul::xml::Element* args = soul::xml::MakeElement("args");
    callElement->AppendChild(args);
    element = args;
    for (const auto& arg : node.Args())
    {
        arg->Accept(*this);
    }
    element = callElement;
    SetExpressionAttributes(&node);
    prevElement->AppendChild(callElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundEmptyFunctionCallNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("empty_function_call");
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundFunctionPtrCallNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("ptr_call");
    SetExpressionAttributes(&node);
    soul::xml::Element* args = soul::xml::MakeElement("args");
    element = args;
    for (const auto& arg : node.Args())
    {
        arg->Accept(*this);
    }
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundInvokeNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* invokeElement = soul::xml::MakeElement("invoke");
    element = invokeElement;
    SetExpressionAttributes(&node);
    if (node.Result())
    {
        soul::xml::Element* result = soul::xml::MakeElement("result");
        invokeElement->AppendChild(result);
        element = result;
        node.Result()->Accept(*this);
    }
    soul::xml::Element* invokeCall = soul::xml::MakeElement("invoke_call");
    invokeElement->AppendChild(invokeCall);
    element = invokeCall;
    node.InvokeCall()->Accept(*this);
    prevElement->AppendChild(invokeElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundExpressionSequenceNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* sequenceElement = soul::xml::MakeElement("expr_sequence");
    element = sequenceElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("left");
    sequenceElement->AppendChild(element);
    node.Left()->Accept(*this);
    element = soul::xml::MakeElement("right");
    sequenceElement->AppendChild(element);
    node.Right()->Accept(*this);
    prevElement->AppendChild(sequenceElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundExpressionListNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("expression_list");
    for (const auto& expr : node.Exprs())
    {
        expr->Accept(*this);
    }
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundConjunctionNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* conjunctionElement = soul::xml::MakeElement("conjunction");
    element = conjunctionElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("left");
    conjunctionElement->AppendChild(element);
    node.Left()->Accept(*this);
    element = soul::xml::MakeElement("right");
    node.Right()->Accept(*this);
    conjunctionElement->AppendChild(element);
    prevElement->AppendChild(conjunctionElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundDisjunctionNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* disjunctionElement = soul::xml::MakeElement("disjunction");
    element = disjunctionElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("left");
    disjunctionElement->AppendChild(element);
    node.Left()->Accept(*this);
    element = soul::xml::MakeElement("right");
    disjunctionElement->AppendChild(element);
    node.Right()->Accept(*this);
    prevElement->AppendChild(disjunctionElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundConditionalExprNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* conditionalElement = soul::xml::MakeElement("conditional");
    element = conditionalElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("condition");
    conditionalElement->AppendChild(element);
    node.GetCondition()->Accept(*this);
    element = soul::xml::MakeElement("then_expr");
    conditionalElement->AppendChild(element);
    node.GetThenExpr()->Accept(*this);
    element = soul::xml::MakeElement("else_expr");
    conditionalElement->AppendChild(element);
    node.GetElseExpr()->Accept(*this);
    prevElement->AppendChild(conditionalElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundConversionNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* conversionElement = soul::xml::MakeElement("conversion");
    element = conversionElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("subject");
    conversionElement->AppendChild(element);
    node.Subject()->Accept(*this);
    conversionElement->SetAttribute("fn", util::ToUtf8(node.ConversionFunction()->FullName()));
    prevElement->AppendChild(conversionElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundAddressOfNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* addressElement = soul::xml::MakeElement("address");
    element = addressElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("subject");
    addressElement->AppendChild(element);
    node.Subject()->Accept(*this);
    prevElement->AppendChild(addressElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundDereferenceNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* derefElement = soul::xml::MakeElement("dereference");
    element = derefElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("subject");
    derefElement->AppendChild(element);
    node.Subject()->Accept(*this);
    prevElement->AppendChild(derefElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundRefToPtrNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* refToPtrElement = soul::xml::MakeElement("reftoptr");
    element = refToPtrElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("subject");
    refToPtrElement->AppendChild(element);
    node.Subject()->Accept(*this);
    prevElement->AppendChild(refToPtrElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundPtrToRefNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* ptrToRefElement = soul::xml::MakeElement("ptrtoref");
    element = ptrToRefElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("subject");
    ptrToRefElement->AppendChild(element);
    node.Subject()->Accept(*this);
    prevElement->AppendChild(ptrToRefElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundDefaultInitNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* defaultInitElement = soul::xml::MakeElement("default_init");
    element = defaultInitElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("subject");
    defaultInitElement->AppendChild(element);
    node.Subject()->Accept(*this);
    prevElement->AppendChild(defaultInitElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundTemporaryNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* temporaryElement = soul::xml::MakeElement("temporary");
    element = temporaryElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("rvalue");
    temporaryElement->AppendChild(element);
    node.RvalueExpr()->Accept(*this);
    element = soul::xml::MakeElement("backing_store");
    temporaryElement->AppendChild(element);
    node.BackingStore()->Accept(*this);
    prevElement->AppendChild(temporaryElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundConstructTemporaryNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* constructTemporaryElement = soul::xml::MakeElement("construct_temporary");
    element = constructTemporaryElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("constructor_call");
    constructTemporaryElement->AppendChild(element);
    node.ConstructorCall()->Accept(*this);
    element = soul::xml::MakeElement("temporary");
    constructTemporaryElement->AppendChild(element);
    node.Temporary()->Accept(*this);
    prevElement->AppendChild(constructTemporaryElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundConstructExpressionNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* constructExprElement = soul::xml::MakeElement("construct_expr");
    element = constructExprElement;
    if (node.HasPlacement())
    {
        element->SetAttribute("placement", "true");
    }
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("allocation");
    constructExprElement->AppendChild(element);
    node.Allocation()->Accept(*this);
    element = soul::xml::MakeElement("construct_object_call");
    constructExprElement->AppendChild(element);
    node.ConstructObjectCall()->Accept(*this);
    prevElement->AppendChild(constructExprElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundGlobalVariableDefinitionNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("global_variable");
    element->SetAttribute("name", util::ToUtf8(node.GetGlobalVariable()->Name()));
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundEmptyDestructorNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("empty_dtor");
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundFunctionValueNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("fn_value");
    element->SetAttribute("fn", util::ToUtf8(node.GetFunction()->FullName()));
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundVariableAsVoidPtrNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* variableAsVoidPtrElement = soul::xml::MakeElement("variable_as_void_ptr");
    element = variableAsVoidPtrElement;
    SetExpressionAttributes(&node);
    element = soul::xml::MakeElement("variable");
    variableAsVoidPtrElement->AppendChild(element);
    node.AddrOfBoundVariable()->Accept(*this);
    prevElement->AppendChild(variableAsVoidPtrElement);
    element = prevElement;
}

void BoundNodeXmlGenerator::Visit(BoundOperatorFnNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("operator_fn");
    SetExpressionAttributes(&node);
    prevElement->AppendChild(element);
    element = prevElement;
}

std::unique_ptr<soul::xml::Element> ToXml(BoundFunctionNode* fn)
{
    BoundNodeXmlGenerator generator;
    fn->Accept(generator);
    std::unique_ptr<soul::xml::Element> element = generator.GetElement();
    return element;
}

std::unique_ptr<soul::xml::Element> ToXml(BoundCompileUnitNode* cu)
{
    BoundNodeXmlGenerator generator;
    cu->Accept(generator);
    std::unique_ptr<soul::xml::Element> element = generator.GetElement();
    return element;
}

void PrintXml(BoundFunctionNode* fn, std::ostream* s)
{
    if (!s)
    {
        s = &std::cout;
    }
    std::unique_ptr<soul::xml::Element> element = ToXml(fn);
    util::CodeFormatter formatter(*s);
    formatter.SetIndentSize(1);
    element->Write(formatter);
}

void PrintXml(BoundCompileUnitNode* cu, std::ostream* s)
{
    if (!s)
    {
        s = &std::cout;
    }
    std::unique_ptr<soul::xml::Element> element = ToXml(cu);
    util::CodeFormatter formatter(*s);
    formatter.SetIndentSize(1);
    element->Write(formatter);
}

} // namespace otava::symbols

