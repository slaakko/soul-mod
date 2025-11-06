// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.evaluator;

import otava.ast.literal;
import otava.ast.identifier;
import otava.ast.visitor;
import otava.ast.expression;
import otava.symbols.alias.type.symbol;
import otava.symbols.context;
import otava.symbols.declaration;
import otava.symbols.exception;
import otava.symbols.scope.resolver;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.value;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.type.resolver;
import otava.symbols.emitter;
import otava.symbols.variable.symbol;
import otava.symbols.array.type.symbol;
import otava.symbols.classes;
import otava.symbols.enums;
import otava.symbols.modules;
import util.unicode;

namespace otava::symbols {

TypeSymbol* GetIntegerType(otava::ast::Suffix suffix, const soul::ast::SourcePos& sourcePos, Context* context)
{
    DeclarationFlags flags = DeclarationFlags::intFlag;
    if ((suffix & otava::ast::Suffix::u) != otava::ast::Suffix::none)
    {
        flags = flags | DeclarationFlags::unsignedFlag;
    }
    if ((suffix & otava::ast::Suffix::l) != otava::ast::Suffix::none)
    {
        flags = flags | DeclarationFlags::longFlag;
    }
    if ((suffix & otava::ast::Suffix::ll) != otava::ast::Suffix::none)
    {
        flags = flags | DeclarationFlags::longLongFlag;
    }
    return GetFundamentalType(flags, sourcePos, context);
}

TypeSymbol* GetFloatingPointType(otava::ast::Suffix suffix, const soul::ast::SourcePos& sourcePos, Context* context)
{
    DeclarationFlags flags = DeclarationFlags::doubleFlag;
    if ((suffix & otava::ast::Suffix::l) != otava::ast::Suffix::none)
    {
        flags = flags | DeclarationFlags::longFlag;
    }
    if ((suffix & otava::ast::Suffix::f) != otava::ast::Suffix::none)
    {
        flags = (flags & ~DeclarationFlags::doubleFlag) | DeclarationFlags::floatFlag;
    }
    return GetFundamentalType(flags, sourcePos, context);
}

TypeSymbol* GetStringType(otava::ast::EncodingPrefix encodingPrefix, const soul::ast::SourcePos& sourcePos, Context* context)
{
    switch (encodingPrefix)
    {
        case otava::ast::EncodingPrefix::u8:
        {
            return context->GetSymbolTable()->MakeConstChar8PtrType(context);
        }
        case otava::ast::EncodingPrefix::u:
        {
            return context->GetSymbolTable()->MakeConstChar16PtrType(context);
        }
        case otava::ast::EncodingPrefix::U:
        {
            return context->GetSymbolTable()->MakeConstChar32PtrType(context);
        }
        case otava::ast::EncodingPrefix::L:
        {
            return context->GetSymbolTable()->MakeConstWCharPtrType(context);
        }
        default:
        {
            return context->GetSymbolTable()->MakeConstCharPtrType(context);
        }
    }
}

TypeSymbol* GetCharacterType(otava::ast::EncodingPrefix encodingPrefix, const soul::ast::SourcePos& sourcePos, Context* context)
{
    switch (encodingPrefix)
    {
        case otava::ast::EncodingPrefix::u8:
        {
            return context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char8Type);
        }
        case otava::ast::EncodingPrefix::u:
        {
            return context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char16Type);
        }
        case otava::ast::EncodingPrefix::U:
        {
            return context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char32Type);
        }
        case otava::ast::EncodingPrefix::L:
        {
            return context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::wcharType);
        }
        default:
        {
            return context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::charType);
        }
    }
}
class Evaluator : public otava::ast::DefaultVisitor
{
public:
    Evaluator(Context* context_);
    Value* GetValue() { return value; }
    void Visit(otava::ast::IntegerLiteralNode& node) override;
    void Visit(otava::ast::FloatingLiteralNode& node) override;
    void Visit(otava::ast::CharacterLiteralNode& node) override;
    void Visit(otava::ast::StringLiteralNode& node) override;
    void Visit(otava::ast::BooleanLiteralNode& node) override;
    void Visit(otava::ast::NullPtrLiteralNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::AssignmentInitNode& node) override;
    void Visit(otava::ast::UnaryExprNode& node) override;
    void Visit(otava::ast::BinaryExprNode& node) override;
    void Visit(otava::ast::InvokeExprNode& node) override;
    void Visit(otava::ast::SizeOfTypeExprNode& node) override;
    void Visit(otava::ast::BracedInitListNode& node) override;
    void Visit(otava::ast::CppCastExprNode& node) override;
private:
    Context* context;
    Value* value;
    Scope* scope;
};

Evaluator::Evaluator(Context* context_) : context(context_), value(nullptr), scope(context->GetSymbolTable()->CurrentScope())
{
}

void Evaluator::Visit(otava::ast::IntegerLiteralNode& node)
{
    TypeSymbol* type = GetIntegerType(node.GetSuffix(), node.GetSourcePos(), context);
    value = context->GetEvaluationContext()->GetIntegerValue(node.Value(), node.Rep(), type);
}

void Evaluator::Visit(otava::ast::FloatingLiteralNode& node)
{
    TypeSymbol* type = GetFloatingPointType(node.GetSuffix(), node.GetSourcePos(), context);
    value = context->GetEvaluationContext()->GetFloatingValue(node.Value(), node.Rep(), type);
}

void Evaluator::Visit(otava::ast::CharacterLiteralNode& node)
{
    TypeSymbol* type = GetCharacterType(node.GetEncodingPrefix(), node.GetSourcePos(), context);
    value = context->GetEvaluationContext()->GetCharValue(node.Value(), type);
}

void Evaluator::Visit(otava::ast::StringLiteralNode& node)
{
    TypeSymbol* type = GetStringType(node.GetEncodingPrefix(), node.GetSourcePos(), context);
    value = context->GetEvaluationContext()->GetStringValue(util::ToUtf8(node.Value()), type);
}

void Evaluator::Visit(otava::ast::BooleanLiteralNode& node)
{
    value = context->GetEvaluationContext()->GetBoolValue(node.Value());
}

void Evaluator::Visit(otava::ast::NullPtrLiteralNode& node)
{
    value = context->GetEvaluationContext()->GetNullPtrValue();
}

void Evaluator::Visit(otava::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void Evaluator::Visit(otava::ast::IdentifierNode& node)
{
    Symbol* symbol = scope->Lookup(node.Str(), 
        SymbolGroupKind::variableSymbolGroup | SymbolGroupKind::enumConstantSymbolGroup | SymbolGroupKind::typeSymbolGroup, 
        ScopeLookup::allScopes, 
        node.GetSourcePos(), 
        context, 
        LookupFlags::none);
    if (symbol)
    {
        switch (symbol->Kind())
        {
            case SymbolKind::variableSymbol:
            {
                VariableSymbol* variableSymbol = static_cast<VariableSymbol*>(symbol);
                if (variableSymbol->GetValue())
                {
                    value = variableSymbol->GetValue();
                }
                else
                {
                    value = context->GetEvaluationContext()->GetSymbolValue(symbol);
                }
                break;
            }
            case SymbolKind::enumConstantSymbol:
            {
                EnumConstantSymbol* enumConstant = static_cast<EnumConstantSymbol*>(symbol);
                value = enumConstant->GetValue();
                break;
            }
            default:
            {
                value = context->GetEvaluationContext()->GetSymbolValue(symbol);
                break;
            }
        }
    }
}

void Evaluator::Visit(otava::ast::AssignmentInitNode& node)
{
    node.Child()->Accept(*this);
}

void Evaluator::Visit(otava::ast::UnaryExprNode& node)
{
    value = Evaluate(node.Child(), context);
    if (value)
    {
        switch (node.Op()->Kind())
        {
            case otava::ast::NodeKind::plusNode:
            {
                if (value->IsIntegerValue())
                {
                    IntegerValue* integerValue = static_cast<IntegerValue*>(value);
                    value = context->GetEvaluationContext()->GetIntegerValue(integerValue->GetValue(), U"+" + value->Rep(), integerValue->GetType());
                }
                else if (value->IsFloatingValue())
                {
                    FloatingValue* floatingValue = static_cast<FloatingValue*>(value);
                    value = context->GetEvaluationContext()->GetFloatingValue(floatingValue->GetValue(), U"+" + value->Rep(), floatingValue->GetType());
                }
                break;
            }
            case otava::ast::NodeKind::minusNode:
            {
                if (value->IsIntegerValue())
                {
                    IntegerValue* integerValue = static_cast<IntegerValue*>(value);
                    value = context->GetEvaluationContext()->GetIntegerValue(-integerValue->GetValue(), U"-" + value->Rep(), integerValue->GetType());
                }
                else if (value->IsFloatingValue())
                {
                    FloatingValue* floatingValue = static_cast<FloatingValue*>(value);
                    value = context->GetEvaluationContext()->GetFloatingValue(-floatingValue->GetValue(), U"-" + value->Rep(), floatingValue->GetType());
                }
                break;
            }
            case otava::ast::NodeKind::complementNode:
            {
                if (value->IsIntegerValue())
                {
                    IntegerValue* integerValue = static_cast<IntegerValue*>(value);
                    value = context->GetEvaluationContext()->GetIntegerValue(~integerValue->GetValue(), U"~" + value->Rep(), integerValue->GetType());
                }
                break;
            }
            case otava::ast::NodeKind::notNode:
            {
                if (value->IsBoolValue())
                {
                    BoolValue* boolValue = static_cast<BoolValue*>(value);
                    value = context->GetEvaluationContext()->GetBoolValue(!boolValue->GetValue());
                }
                break;
            }
        }
    }
}

void Evaluator::Visit(otava::ast::BinaryExprNode& node)
{
    Value* left = Evaluate(node.Left(), context);
    Value* right = Evaluate(node.Right(), context);
    if (left && right)
    {
        ValueKind commonKind = CommonValueKind(left->GetValueKind(), right->GetValueKind());
        EvaluationContext* evaluationContext = context->GetEvaluationContext();
        Value* leftConv = left->Convert(commonKind, *evaluationContext);
        Value* rightConv = right->Convert(commonKind, *evaluationContext);
        switch (commonKind)
        {
            case ValueKind::integerValue:
            {
                IntegerValue* leftInt = static_cast<IntegerValue*>(leftConv);
                IntegerValue* rightInt = static_cast<IntegerValue*>(rightConv);
                switch (node.Op()->Kind())
                {
                    case otava::ast::NodeKind::plusNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() + rightInt->GetValue(), leftInt->ToString() + U" + " + rightInt->ToString(), 
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::minusNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() - rightInt->GetValue(), leftInt->ToString() + U" - " + rightInt->ToString(),
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::mulNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() * rightInt->GetValue(), leftInt->ToString() + U" * " + rightInt->ToString(),
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::divNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() / rightInt->GetValue(), leftInt->ToString() + U" / " + rightInt->ToString(),
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::modNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() % rightInt->GetValue(), leftInt->ToString() + U" % " + rightInt->ToString(),
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::shiftLeftNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() << rightInt->GetValue(), leftInt->ToString() + U" << " + rightInt->ToString(),
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::shiftRightNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() >> rightInt->GetValue(), leftInt->ToString() + U" >> " + rightInt->ToString(),
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::inclusiveOrNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() | rightInt->GetValue(), leftInt->ToString() + U" | " + rightInt->ToString(),
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::exclusiveOrNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() ^ rightInt->GetValue(), leftInt->ToString() + U" ^ " + rightInt->ToString(),
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::andNode:
                    {
                        value = evaluationContext->GetIntegerValue(leftInt->GetValue() & rightInt->GetValue(), leftInt->ToString() + U" & " + rightInt->ToString(),
                            leftInt->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::equalNode:
                    {
                        value = evaluationContext->GetBoolValue(leftInt->GetValue() == rightInt->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::notEqualNode:
                    {
                        value = evaluationContext->GetBoolValue(leftInt->GetValue() != rightInt->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::greaterNode:
                    {
                        value = evaluationContext->GetBoolValue(leftInt->GetValue() > rightInt->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::lessNode:
                    {
                        value = evaluationContext->GetBoolValue(leftInt->GetValue() < rightInt->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::greaterOrEqualNode:
                    {
                        value = evaluationContext->GetBoolValue(leftInt->GetValue() >= rightInt->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::lessOrEqualNode:
                    {
                        value = evaluationContext->GetBoolValue(leftInt->GetValue() <= rightInt->GetValue());
                        break;
                    }
                }
                break;
            }
            case ValueKind::floatingValue:
            {
                FloatingValue* leftFloat = static_cast<FloatingValue*>(leftConv);
                FloatingValue* rightFloat = static_cast<FloatingValue*>(rightConv);
                switch (node.Op()->Kind())
                {
                    case otava::ast::NodeKind::plusNode:
                    {
                        value = evaluationContext->GetFloatingValue(leftFloat->GetValue() + rightFloat->GetValue(), leftFloat->ToString() + U" + " + rightFloat->ToString(),
                            leftFloat->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::minusNode:
                    {
                        value = evaluationContext->GetFloatingValue(leftFloat->GetValue() - rightFloat->GetValue(), leftFloat->ToString() + U" - " + rightFloat->ToString(),
                            leftFloat->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::mulNode:
                    {
                        value = evaluationContext->GetFloatingValue(leftFloat->GetValue() * rightFloat->GetValue(), leftFloat->ToString() + U" * " + rightFloat->ToString(),
                            leftFloat->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::divNode:
                    {
                        value = evaluationContext->GetFloatingValue(leftFloat->GetValue() / rightFloat->GetValue(), leftFloat->ToString() + U" / " + rightFloat->ToString(),
                            leftFloat->GetType());
                        break;
                    }
                    case otava::ast::NodeKind::equalNode:
                    {
                        value = evaluationContext->GetBoolValue(leftFloat->GetValue() == rightFloat->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::notEqualNode:
                    {
                        value = evaluationContext->GetBoolValue(leftFloat->GetValue() != rightFloat->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::greaterNode:
                    {
                        value = evaluationContext->GetBoolValue(leftFloat->GetValue() > rightFloat->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::lessNode:
                    {
                        value = evaluationContext->GetBoolValue(leftFloat->GetValue() < rightFloat->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::greaterOrEqualNode:
                    {
                        value = evaluationContext->GetBoolValue(leftFloat->GetValue() >= rightFloat->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::lessOrEqualNode:
                    {
                        value = evaluationContext->GetBoolValue(leftFloat->GetValue() <= rightFloat->GetValue());
                        break;
                    }
                }
                break;
            }
            case ValueKind::boolValue:
            {
                BoolValue* leftBool = static_cast<BoolValue*>(leftConv);
                BoolValue* rightBool = static_cast<BoolValue*>(rightConv);
                switch (node.Op()->Kind())
                {
                    case otava::ast::NodeKind::disjunctionNode:
                    {
                        value = evaluationContext->GetBoolValue(leftBool->GetValue() || rightBool->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::conjunctionNode:
                    {
                        value = evaluationContext->GetBoolValue(leftBool->GetValue() && rightBool->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::equalNode:
                    {
                        value = evaluationContext->GetBoolValue(leftBool->GetValue() == rightBool->GetValue());
                        break;
                    }
                    case otava::ast::NodeKind::notEqualNode:
                    {
                        value = evaluationContext->GetBoolValue(leftBool->GetValue() != rightBool->GetValue());
                        break;
                    }
                }
                break;
            }
        }
    }
}

void Evaluator::Visit(otava::ast::InvokeExprNode& node)
{
    value = Evaluate(node.Subject(), context);
    if (value)
    {
        EvaluationContext* evaluationContext = context->GetEvaluationContext();
        value = evaluationContext->GetInvokeValue(value);
    }
}

void Evaluator::Visit(otava::ast::SizeOfTypeExprNode& node)
{
    TypeSymbol* type = ResolveType(node.Child(), DeclarationFlags::none, context);
    type = type->DirectType(context)->FinalType(node.GetSourcePos(), context);
    otava::intermediate::Type* irType = type->IrType(*context->GetEmitter(), node.GetSourcePos(), context);
    std::int64_t size = irType->Size();
    value = context->GetEvaluationContext()->GetIntegerValue(size, util::ToUtf32(std::to_string(size)), 
        context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::unsignedLongLongIntType));
}

void Evaluator::Visit(otava::ast::BracedInitListNode& node)
{
    TypeSymbol* type = context->DeclaredInitializerType();
    if (type)
    {
        if (type->IsArrayTypeSymbol())
        {
            ArrayTypeSymbol* arrayTypeSymbol = static_cast<ArrayTypeSymbol*>(type);
            ArrayValue* arrayValue = context->GetSymbolTable()->GetModule()->GetEvaluationContext()->GetArrayValue(type);
            std::int64_t count = 0;
            for (otava::ast::Node* element : node.Items())
            {
                if (element->IsLBraceNode() || element->IsRBraceNode()) continue;
                context->SetDeclaredInitializerType(arrayTypeSymbol->ElementType());
                Value* elementValue = Evaluate(element, context);
                arrayValue->AddElementValue(elementValue);
                context->SetDeclaredInitializerType(type);
                ++count;
            }
            if (arrayTypeSymbol->Size() == -1)
            {
                arrayTypeSymbol->SetSize(count);
            }
            else if (arrayTypeSymbol->Size() != count)
            {
                ThrowException("conflicting array size: size=" + std::to_string(arrayTypeSymbol->Size()) + ", number of elements in initializer=" + std::to_string(count), 
                    node.GetSourcePos(), context);
            }
            value = arrayValue;
        }
        else if (type->PlainType(context)->IsClassTypeSymbol())
        {
            ClassTypeSymbol* classTypeSymbol = static_cast<ClassTypeSymbol*>(type->PlainType(context));
            StructureValue* structureValue = context->GetSymbolTable()->GetModule()->GetEvaluationContext()->GetStructureValue(type);
            int index = 0;
            for (otava::ast::Node* field : node.Items())
            {
                if (field->IsLBraceNode() || field->IsRBraceNode()) continue;
                context->SetDeclaredInitializerType(nullptr);
                Value* fieldValue = Evaluate(field, context);
                structureValue->AddFieldValue(fieldValue);
                context->SetDeclaredInitializerType(type);
                ++index;
            }
            value = structureValue;
        }
    }
    else
    {
        value = nullptr;
    }
}

void Evaluator::Visit(otava::ast::CppCastExprNode& node)
{
    TypeSymbol* type = ResolveType(node.TypeId(), DeclarationFlags(), context);
    node.Child()->Accept(*this);
    if (value)
    {
        switch (value->GetValueKind())
        {
            case ValueKind::integerValue:
            {
                IntegerValue* integerValue = static_cast<IntegerValue*>(value);
                value = context->GetEvaluationContext()->GetIntegerValue(integerValue->GetValue(), integerValue->Rep(), type);
                break;
            }
            case ValueKind::floatingValue:
            {
                FloatingValue* floatingValue = static_cast<FloatingValue*>(value);
                value = context->GetEvaluationContext()->GetFloatingValue(floatingValue->GetValue(), floatingValue->Rep(), type);
                break;
            }
            case ValueKind::stringValue:
            {
                StringValue* stringValue = static_cast<StringValue*>(value);
                value = context->GetEvaluationContext()->GetStringValue(stringValue->GetValue(), type);
                break;
            }
            case ValueKind::charValue:
            {
                CharValue* charValue = static_cast<CharValue*>(value);
                value = context->GetEvaluationContext()->GetCharValue(charValue->GetValue(), type);
                break;
            }
        }
    }
}

Value* Evaluate(otava::ast::Node* node, Context* context)
{
    Evaluator evaluator(context);
    node->Accept(evaluator);
    return evaluator.GetValue();
}

} // namespace otava::symbols
