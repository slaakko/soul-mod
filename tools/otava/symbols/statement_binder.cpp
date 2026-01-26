// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.statement.binder;

import otava.ast.statement;
import otava.ast.function;
import otava.ast.declaration;
import otava.ast.type;
import otava.ast.classes;
import otava.ast.identifier;
import otava.ast.expression;
import otava.ast.qualifier;
import otava.ast.templates;
import otava.ast.literal;
import otava.ast.simple.type;
import otava.symbols.argument.conversion.table;
import otava.symbols.block;
import otava.symbols.bound.tree;
import otava.symbols.classes;
import otava.symbols.class_group.symbol;
import otava.symbols.context;
import otava.symbols.declarator;
import otava.symbols.declaration;
import otava.symbols.exception;
import otava.symbols.expr.parser;
import otava.symbols.stmt.parser;
import otava.symbols.expression.binder;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.function_return_path_checker;
import otava.symbols.overload.resolution;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.type.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.variable.symbol;
import otava.symbols.class_templates;
import otava.symbols.instantiator;
import otava.symbols.declaration;
import otava.symbols.modules;
import otava.symbols.namespaces;
import otava.symbols.conversion.table;
import otava.symbols.type_compare;
import otava.symbols.alias.type.symbol;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.operation.repository;
import otava.symbols.type.resolver;
import otava.symbols.project;
import otava.symbols.exception_handling;
import util.sha1;
import util.unicode;

namespace otava::symbols {

struct InitializerLess
{
    bool operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const;
};

bool InitializerLess::operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, 
    const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const
{
    return left.first < right.first;
}

struct TerminatorGreater
{
    bool operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const;
};

bool TerminatorGreater::operator()(const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& left, 
    const std::pair<int, std::unique_ptr<BoundFunctionCallNode>>& right) const
{
    return left.first > right.first;
}

constexpr int maxBaseInitializers = 10000;

BoundExpressionNode* MakeBoundBooleanConversionNode(BoundExpressionNode* condition, Context* context)
{
    soul::ast::SourcePos sourcePos = condition->GetSourcePos();
    FunctionSymbol* conversionFunction = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        context->GetSymbolTable()->GetFundamentalType(otava::symbols::FundamentalTypeKind::boolType), condition->GetType(), sourcePos, context);
    if (!conversionFunction)
    {
        ThrowException("condition must be convertible to Boolean type value", condition->GetSourcePos(), context);
    }
    if (conversionFunction->GetFunctionKind() == FunctionKind::conversionMemFn && condition->GetType()->PlainType(context)->IsClassTypeSymbol())
    {
        TypeSymbol* conditionType = condition->GetType();
        if (conditionType->IsReferenceType())
        {
            condition = new BoundRefToPtrNode(condition, sourcePos, conditionType->RemoveReference(context)->AddPointer(context));
        }
        else
        {
            condition = new BoundAddressOfNode(condition, sourcePos, conditionType->GetBaseType()->AddPointer(context));
        }
        BoundFunctionCallNode* functionCall = new BoundFunctionCallNode(conversionFunction, sourcePos, conversionFunction->ReturnType());
        functionCall->AddArgument(condition);
        return functionCall;
    }
    return new BoundConversionNode(condition, conversionFunction, sourcePos);
}

BoundFunctionCallNode* MakeDestructorCall(ClassTypeSymbol* cls, BoundExpressionNode* arg, FunctionDefinitionSymbol* destructor, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* dtorSymbol = nullptr;
    if (destructor)
    {
        dtorSymbol = destructor;
    }
    else
    {
        dtorSymbol = GenerateDestructor(cls, sourcePos, context);
    }
    if (dtorSymbol && (dtorSymbol->IsFunctionSymbol() || dtorSymbol->IsExplicitlyInstantiatedFunctionDefinitionSymbol()))
    {
        FunctionSymbol* dtorFunctionSymbol = static_cast<FunctionSymbol*>(dtorSymbol);
        if (dtorFunctionSymbol->GetFlag(FunctionSymbolFlags::trivialDestructor))
        {
            return nullptr;
        }
        std::string dtorIrName = dtorSymbol->IrName(context);
        std::unique_ptr<BoundFunctionCallNode> destructorCall(new BoundFunctionCallNode(dtorFunctionSymbol, sourcePos, cls));
        destructorCall->AddArgument(arg->Clone());
        return destructorCall.release();
    }
    return nullptr;
}

StatementBinder::StatementBinder(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_) : 
    context(context_), 
    currentClass(nullptr),
    ctorInitializer(nullptr),
    dtorTerminator(nullptr),
    boundStatement(nullptr),
    functionDefinitionSymbol(functionDefinitionSymbol_),
    classTypeSymbol(nullptr),
    memberVariableSymbol(nullptr),
    resolveClass(false),
    resolveMemberVariable(false),
    resolveInitializerArguments(false),
    setVPtrStatementsGenerated(false),
    setLineCodeGenerated(false),
    postfix(false),
    globalStaticVariableSymbol(nullptr),
    catchBlock(nullptr),
    lastElse(nullptr)
{
}

void StatementBinder::Visit(otava::ast::FunctionDefinitionNode& node)
{
    Symbol* symbol = context->GetSymbolTable()->GetSymbol(&node);
    SpecialFunctionKind specialFunctionKind = functionDefinitionSymbol->GetSpecialFunctionKind(context);
    switch (specialFunctionKind)
    {
        case SpecialFunctionKind::defaultCtor:
        case SpecialFunctionKind::copyCtor:
        case SpecialFunctionKind::moveCtor:
        {
            functionDefinitionSymbol->SetFunctionKind(FunctionKind::constructor);
            break;
        }
        case SpecialFunctionKind::dtor:
        {
            functionDefinitionSymbol->SetFunctionKind(FunctionKind::destructor);
            break;
        }
    }
    if (node.FunctionBody()->IsDefaultedOrDeletedFunctionNode())
    {
        otava::ast::DefaultedOrDeletedFunctionNode* bodyNode = static_cast<otava::ast::DefaultedOrDeletedFunctionNode*>(node.FunctionBody());
        if (bodyNode->DefaultOrDelete()->Kind() == otava::ast::NodeKind::defaultNode)
        {
            functionDefinitionSymbol->SetFunctionQualifiers(functionDefinitionSymbol->Qualifiers() | FunctionQualifiers::isDefault);
            ClassTypeSymbol* classType = symbol->ParentClassType();
            if (classType)
            {
                switch (specialFunctionKind)
                {
                    case SpecialFunctionKind::defaultCtor:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        functionDefinitionSymbol = GenerateClassDefaultCtor(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::copyCtor:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        functionDefinitionSymbol = GenerateClassCopyCtor(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::moveCtor:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        functionDefinitionSymbol = GenerateClassMoveCtor(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::copyAssignment:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        functionDefinitionSymbol = GenerateClassCopyAssignment(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                    case SpecialFunctionKind::moveAssignment:
                    {
                        int defIndex = functionDefinitionSymbol->DefIndex();
                        functionDefinitionSymbol = GenerateClassMoveAssignment(classType, node.GetSourcePos(), context);
                        functionDefinitionSymbol->SetDefIndex(defIndex);
                        break;
                    }
                }
                std::unique_ptr<BoundFunctionNode> boundFunction(context->ReleaseBoundFunction());
                context->GetBoundCompileUnit()->AddBoundNode(std::move(boundFunction), context);
                context->PopBoundFunction();
            }
        }
        else if (bodyNode->DefaultOrDelete()->Kind() == otava::ast::NodeKind::deleteNode)
        {
            functionDefinitionSymbol->SetFunctionQualifiers(functionDefinitionSymbol->Qualifiers() | FunctionQualifiers::isDeleted);
        }
        return;
    }
    currentClass = symbol->ParentClassType();
    context->GetSymbolTable()->BeginScopeGeneric(symbol->GetScope(), context);
    node.FunctionBody()->Accept(*this);
    if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::constructor)
    {
        currentClass->SetHasUserDefinedConstructor();
        if (!ctorInitializer)
        {
            GenerateDefaultCtorInitializer(node.GetSourcePos());
        }
    }
    else if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::destructor)
    {
        currentClass->SetHasUserDefinedDestructor();
        GenerateDestructorTerminator(node.GetSourcePos());
    }
    context->GetSymbolTable()->EndScopeGeneric(context);
    functionDefinitionSymbol->CheckGenerateClassCopyCtor(node.GetSourcePos(), context);
}

void StatementBinder::Visit(otava::ast::ConstructorNode& node)
{
    node.Left()->Accept(*this);
    if (ctorInitializer)
    {
        context->GetBoundFunction()->SetCtorInitializer(ctorInitializer);
    }
    node.Right()->Accept(*this);
    boundStatement->SetSourcePos(node.GetSourcePos());
    context->GetBoundFunction()->SetBody(static_cast<BoundCompoundStatementNode*>(boundStatement));
    AddConvertingConstructorToConversionTable(functionDefinitionSymbol, node.GetSourcePos(), context);
}

void StatementBinder::Visit(otava::ast::ConstructorInitializerNode& node)
{
    ctorInitializer = new BoundCtorInitializerNode(node.GetSourcePos());
    node.MemberInitializerListNode()->Accept(*this);
}

void StatementBinder::GenerateDefaultCtorInitializer(const soul::ast::SourcePos& sourcePos)
{
    ctorInitializer = new BoundCtorInitializerNode(sourcePos);
    CompleteBaseInitializers(sourcePos);
    std::sort(baseInitializers.begin(), baseInitializers.end(), InitializerLess());
    for (auto& initializer : baseInitializers)
    {
        ctorInitializer->AddBaseInitializer(initializer.second.release());
    }
    GenerateSetVPtrStatements(sourcePos);
    for (auto& setVPtrStatement : setVPtrStatements)
    {
        ctorInitializer->AddSetVPtrStatement(setVPtrStatement.release());
    }
    setVPtrStatements.clear();
    CompleteMemberInitializers(sourcePos);
    std::sort(memberInitializers.begin(), memberInitializers.end(), InitializerLess());
    for (auto& initializer : memberInitializers)
    {
        ctorInitializer->AddMemberInitializer(initializer.second.release());
    }
    context->GetBoundFunction()->SetCtorInitializer(ctorInitializer);
}

void StatementBinder::GenerateDestructorTerminator(const soul::ast::SourcePos& sourcePos)
{
    dtorTerminator = new BoundDtorTerminatorNode(sourcePos);
    GenerateSetVPtrStatements(sourcePos);
    for (auto& setVPtrStatement : setVPtrStatements)
    {
        dtorTerminator->AddSetVPtrStatement(setVPtrStatement.release());
    }
    setVPtrStatements.clear();
    GenerateBaseTerminators(sourcePos);
    GenerateMemberTerminators(sourcePos);
    std::sort(memberTerminators.begin(), memberTerminators.end(), TerminatorGreater());
    for (auto& terminator : memberTerminators)
    {
        dtorTerminator->AddMemberTerminator(terminator.second.release());
    }
    context->GetBoundFunction()->SetDtorTerminator(dtorTerminator);
}

void StatementBinder::GenerateBaseTerminators(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        for (ClassTypeSymbol* baseClass : currentClass->BaseClasses())
        {
            int index = GetBaseInitializerOrTerminatorIndex(baseClass);
            AddBaseTerminator(baseClass, index, sourcePos);
        }
    }
}

void StatementBinder::AddBaseTerminator(TypeSymbol* baseClass, int index, const soul::ast::SourcePos& sourcePos)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    OperationFlags preConversionFlags = OperationFlags::none;
    FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        baseClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
    if (conversion)
    {
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
        std::vector<TypeSymbol*> templateArgs;
        std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
            context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, args, sourcePos, context);
        memberTerminators.push_back(std::make_pair(index, std::move(boundFunctionCall)));
    }
    else
    {
        ThrowException("base class conversion not found", sourcePos, context);
    }
}

void StatementBinder::GenerateMemberTerminators(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        for (VariableSymbol* mermberVar : currentClass->MemberVariables())
        {
            AddMemberTerminator(mermberVar, sourcePos);
        }
    }
}

void StatementBinder::AddMemberTerminator(VariableSymbol* memberVar, const soul::ast::SourcePos& sourcePos)
{
    TypeSymbol* memberVarType = memberVar->GetType();
    if (memberVarType->IsPointerType() || memberVarType->IsReferenceType()) return;
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVar, sourcePos);
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    boundVariableNode->SetThisPtr(thisPtr);
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariableNode, sourcePos, boundVariableNode->GetType()->AddPointer(context))));
    Exception ex;
    std::vector<TypeSymbol*> templateArgs;
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverload(
        context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, args, sourcePos, context, ex);
    if (boundFunctionCall)
    {
        memberTerminators.push_back(std::make_pair(memberVar->Index(), std::move(boundFunctionCall)));
    }
}

void StatementBinder::GenerateSetVPtrStatements(const soul::ast::SourcePos& sourcePos)
{
    if (!currentClass || !currentClass->IsPolymorphic() || setVPtrStatementsGenerated) return;
    if (HasThisInitializer()) return;
    context->GetBoundCompileUnit()->AddBoundNodeForClass(currentClass, sourcePos, context);
    setVPtrStatementsGenerated = true;
    if (!currentClass->ObjectLayoutComputed())
    {
        currentClass->MakeObjectLayout(sourcePos, context);
    }
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    std::vector<ClassTypeSymbol*> vptrHolderClasses = currentClass->VPtrHolderClasses();
    if (vptrHolderClasses.empty())
    {
        ThrowException("no vptr holder classes for the class '" + util::ToUtf8(currentClass->FullName()) + "'", sourcePos, context);
    }
    for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
    {
        if (vptrHolderClass != currentClass)
        {
            FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                vptrHolderClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
            if (conversion)
            {
                BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr->Clone(), conversion, sourcePos);
                setVPtrStatements.push_back(std::unique_ptr<BoundSetVPtrStatementNode>(
                    new BoundSetVPtrStatementNode(thisPtrConverted, currentClass, vptrHolderClass, sourcePos)));
            }
            else
            {
                ThrowException("vptr holder class conversion not found", sourcePos, context);
            }
        }
        else
        {
            setVPtrStatements.push_back(std::unique_ptr<BoundSetVPtrStatementNode>(new BoundSetVPtrStatementNode(thisPtr->Clone(), 
                currentClass, currentClass, sourcePos)));
        }
    }
}

void StatementBinder::Visit(otava::ast::MemberInitializerListNode& node)
{
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* initializer = node.Items()[i];
        initializer->Accept(*this);
    }
    CompleteBaseInitializers(node.GetSourcePos());
    std::sort(baseInitializers.begin(), baseInitializers.end(), InitializerLess());
    for (auto& initializer : baseInitializers)
    {
        ctorInitializer->AddBaseInitializer(initializer.second.release());
    }
    GenerateSetVPtrStatements(node.GetSourcePos());
    for (auto& setVPtrStatement : setVPtrStatements)
    {
        ctorInitializer->AddSetVPtrStatement(setVPtrStatement.release());
    }
    setVPtrStatements.clear();
    CompleteMemberInitializers(node.GetSourcePos());
    std::sort(memberInitializers.begin(), memberInitializers.end(), InitializerLess());
    for (auto& initializer : memberInitializers)
    {
        ctorInitializer->AddMemberInitializer(initializer.second.release());
    }
}

void StatementBinder::CompleteMemberInitializers(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        if (HasThisInitializer()) return;
        for (VariableSymbol* memberVar : currentClass->MemberVariables())
        {
            int index = memberVar->Index();
            bool found = false;
            for (const auto& memberInitilizer : memberInitializers)
            {
                if (memberInitilizer.first == index)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                AddDefaultMemberInitializer(memberVar, sourcePos);
            }
        }
    }
}

void StatementBinder::AddDefaultMemberInitializer(VariableSymbol* memberVar, const soul::ast::SourcePos& sourcePos)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVar, sourcePos);
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    boundVariableNode->SetThisPtr(thisPtr);
    std::vector<TypeSymbol*> templateArgs;
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariableNode, sourcePos, boundVariableNode->GetType()->AddPointer(context))));
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
    memberInitializers.push_back(std::make_pair(memberVar->Index(), std::move(boundFunctionCall)));
}

int StatementBinder::GetBaseInitializerOrTerminatorIndex(TypeSymbol* baseClass) const
{
    int n = currentClass->BaseClasses().size();
    for (int i = 0; i < n; ++i)
    {
        TypeSymbol* baseCls = currentClass->BaseClasses()[i];
        if (TypesEqual(baseCls, baseClass, context))
        {
            return i - maxBaseInitializers;
        }
    }
    return -1;
}

void StatementBinder::CompleteBaseInitializers(const soul::ast::SourcePos& sourcePos)
{
    if (currentClass)
    {
        if (HasThisInitializer()) return;
        for (ClassTypeSymbol* baseClass : currentClass->BaseClasses())
        {
            int index = GetBaseInitializerOrTerminatorIndex(baseClass);
            bool found = false;
            for (const auto& baseInitializer : baseInitializers)
            {
                if (baseInitializer.first == index)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                AddDefaultBaseInitializer(baseClass, index, sourcePos);
            }
        }
    }
}

void StatementBinder::AddDefaultBaseInitializer(TypeSymbol* baseClass, int index, const soul::ast::SourcePos& sourcePos)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    BoundExpressionNode* thisPtr = context->GetThisPtr(sourcePos);
    FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        baseClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
    if (conversion)
    {
        std::vector<TypeSymbol*> templateArgs;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
        std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
            context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
        baseInitializers.push_back(std::make_pair(index, std::move(boundFunctionCall))); 
    }
    else
    {
        ThrowException("base class conversion not found", sourcePos, context);
    }
}

void StatementBinder::Visit(otava::ast::MemberInitializerNode& node)
{
    initializerArgs.clear();
    classTypeSymbol = nullptr;
    memberVariableSymbol = nullptr;
    int index = -1;
    resolveClass = true;
    node.Left()->Accept(*this);
    resolveClass = false;
    if (classTypeSymbol)
    {
        BoundExpressionNode* thisPtr = context->GetThisPtr(node.GetSourcePos());
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            classTypeSymbol->AddPointer(context), thisPtr->GetType(), node.GetSourcePos(), context);
        if (conversion)
        {
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, node.GetSourcePos())));
        }
        else
        {
            ThrowException("base class conversion not found", node.GetSourcePos(), context);
        }
        index = GetBaseInitializerOrTerminatorIndex(classTypeSymbol);
    }
    else
    {
        resolveMemberVariable = true;
        node.Left()->Accept(*this);
        resolveMemberVariable = false;
        initializerArgs.clear();
        if (memberVariableSymbol)
        {
            BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVariableSymbol, node.GetSourcePos());
            ParameterSymbol* thisParam = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ThisParam(context);
            BoundParameterNode* thisPtr = new BoundParameterNode(thisParam, node.GetSourcePos(), thisParam->GetType());
            boundVariableNode->SetThisPtr(thisPtr);
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(
                new BoundDefaultInitNode(boundVariableNode, node.GetSourcePos()), node.GetSourcePos(), boundVariableNode->GetType()->AddPointer(context))));
            index = memberVariableSymbol->Index();
        }
    }
    resolveInitializerArguments = true;
    node.Right()->Accept(*this);
    resolveInitializerArguments = false;
    std::vector<TypeSymbol*> templateArgs;
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, initializerArgs, node.GetSourcePos(), context);
    if (index < 0)
    {
        baseInitializers.push_back(std::make_pair(index, std::move(boundFunctionCall)));
    }
    else
    {
        memberInitializers.push_back(std::make_pair(index, std::move(boundFunctionCall)));
    }
}

void StatementBinder::Visit(otava::ast::TemplateIdNode& node)
{
    if (resolveClass)
    {
        TypeSymbol* type = ResolveType(&node, DeclarationFlags::none, context, TypeResolverFlags::none);
        if (type && type->IsClassTypeSymbol())
        {
            classTypeSymbol = static_cast<ClassTypeSymbol*>(type);
        }
    }
}

void StatementBinder::Visit(otava::ast::IdentifierNode& node)
{
    if (resolveClass)
    {
        Symbol* symbol = context->GetSymbolTable()->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, node.GetSourcePos(), context);
        if (symbol && symbol->IsClassTypeSymbol())
        {
            classTypeSymbol = static_cast<ClassTypeSymbol*>(symbol);
        }
    }
    else if (resolveMemberVariable)
    {
        Symbol* symbol = context->GetSymbolTable()->Lookup(node.Str(), SymbolGroupKind::variableSymbolGroup, node.GetSourcePos(), context);
        if (symbol && symbol->IsMemberVariableSymbol())
        {
            memberVariableSymbol = static_cast<VariableSymbol*>(symbol);
        }
    }
}

void StatementBinder::Visit(otava::ast::ExpressionListNode& node)
{
    if (resolveInitializerArguments)
    {
        int n = node.Items().size();
        for (int i = 0; i < n; ++i)
        {
            otava::ast::Node* item = node.Items()[i];
            BoundExpressionNode* arg = BindExpression(item, context);
            if (!arg)
            {
                ThrowException("could not bind expression", item->GetSourcePos(), context);
            }
            initializerArgs.push_back(std::unique_ptr<BoundExpressionNode>(arg));
        }
    }
}

void StatementBinder::Visit(otava::ast::FunctionBodyNode& node)
{
    node.Child()->Accept(*this);
    context->GetBoundFunction()->SetBody(static_cast<BoundCompoundStatementNode*>(boundStatement));
}

void StatementBinder::Visit(otava::ast::CompoundStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    if (node.BlockId() != -1)
    {
        functionDefinitionSymbol->MapBlock(node.BlockId(), block);
    }
    else
    {
        std::cout << "no block: " << util::ToUtf8(functionDefinitionSymbol->FullName()) << "\n";
    }
    context->PushBlockId(node.BlockId());
    BoundCompoundStatementNode* currentCompoundStatement = new BoundCompoundStatementNode(node.GetSourcePos());
    currentCompoundStatement->SetBlockId(node.BlockId());
    context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    if (functionDefinitionSymbol->GetFunctionKind() == FunctionKind::constructor && !setVPtrStatementsGenerated)
    {
        GenerateSetVPtrStatements(node.GetSourcePos());
        for (auto& setVPtrStatement : setVPtrStatements)
        {
            currentCompoundStatement->AddStatement(setVPtrStatement.release());
        }
        setVPtrStatements.clear();
    }
    int n = node.Count();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* statementNode = node.Nodes()[i];
        BoundStatementNode* boundStatement = BindStatement(statementNode, functionDefinitionSymbol, context);
        if (boundStatement)
        {
            currentCompoundStatement->AddStatement(boundStatement);
        }
    }
    if (!setLineCodeGenerated)
    {
        setLineCodeGenerated = true;
        otava::ast::Node* setLineStatementNode = context->GetBoundFunction()->GetSetLineStatementNode();
        if (setLineStatementNode && !context->GetBoundFunction()->GetBoundSetLineStatement())
        {
            BoundStatementNode* boundStatement = BindStatement(setLineStatementNode, functionDefinitionSymbol, context);
            context->GetBoundFunction()->SetBoundSetLineStatement(boundStatement);
        }
    }
    context->GetSymbolTable()->EndScopeGeneric(context);
    currentCompoundStatement->SetSource(node.Clone());
    context->PopBlockId();
    SetStatement(currentCompoundStatement);
}

bool StatementBinder::HasThisInitializer() const
{
    for (const auto& baseInit : baseInitializers)
    {
        if (baseInit.first == -1) return true;
    }
    for (const auto& memberInit : memberInitializers)
    {
        if (memberInit.first == -1) return true;
    }
    return false;
}

void StatementBinder::Visit(otava::ast::SequenceStatementNode& node)
{
    BoundStatementNode* boundFirstStatement = BindStatement(node.FirstStmt(), functionDefinitionSymbol, context);
    BoundStatementNode* boundSecondStatement = BindStatement(node.SecondStmt(), functionDefinitionSymbol, context);
    BoundSequenceStatementNode* boundSequenceStatement = new BoundSequenceStatementNode(node.GetSourcePos(), boundFirstStatement, boundSecondStatement);
    boundSequenceStatement->SetSource(node.Clone());
    SetStatement(boundSequenceStatement);
}

void StatementBinder::Visit(otava::ast::IfStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    if (node.BlockId() != -1)
    {
        functionDefinitionSymbol->MapBlock(node.BlockId(), block);
    }
    else
    {
        std::cout << "no block: " << util::ToUtf8(functionDefinitionSymbol->FullName()) << "\n";
    }
    context->PushBlockId(node.BlockId());
    context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    BoundIfStatementNode* boundIfStatement = new BoundIfStatementNode(node.GetSourcePos());
    boundIfStatement->SetBlockId(node.BlockId());
    context->PushResetFlag(ContextFlags::returnRef);
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    if (!condition)
    {
        ThrowException("could not bind expression", node.Condition()->GetSourcePos(), context);
    }
    if (condition->GetType()->IsReferenceType())
    {
        condition = new BoundDereferenceNode(condition, node.GetSourcePos(), condition->GetType()->GetBaseType());
    }
    if (!condition->GetType()->IsBoolType())
    {
        condition = MakeBoundBooleanConversionNode(condition, context);
    }
    context->PopFlags();
    boundIfStatement->SetCondition(condition);
    BoundStatementNode* boundThenStatement = BindStatement(node.ThenStatement(), functionDefinitionSymbol, context);
    if (boundThenStatement)
    {
        boundIfStatement->SetThenStatement(boundThenStatement);
    }
    if (node.ElseStatement())
    {
        BoundStatementNode* boundElseStatement = BindStatement(node.ElseStatement(), functionDefinitionSymbol, context);
        if (boundElseStatement)
        {
            boundIfStatement->SetElseStatement(boundElseStatement);
        }
    }
    boundIfStatement->SetSource(node.Clone());
    SetStatement(boundIfStatement);
    context->GetSymbolTable()->EndScopeGeneric(context);
    context->PopBlockId();
}

void StatementBinder::Visit(otava::ast::SwitchStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    if (node.BlockId() != -1)
    {
        functionDefinitionSymbol->MapBlock(node.BlockId(), block);
    }
    else
    {
        std::cout << "no block: " << util::ToUtf8(functionDefinitionSymbol->FullName()) << "\n";
    }
    context->PushBlockId(node.BlockId());
    context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    BoundSwitchStatementNode* boundSwitchStatement = new BoundSwitchStatementNode(node.GetSourcePos());
    boundSwitchStatement->SetBlockId(node.BlockId());
    context->PushResetFlag(ContextFlags::returnRef);
    BoundExpressionNode* condition = BindExpression(node.Condition(), context);
    if (!condition)
    {
        ThrowException("could not bind expression", node.Condition()->GetSourcePos(), context);
    }
    boundSwitchStatement->SetCondition(condition);
    context->PopFlags();
    context->PushSwitchCondType(condition->GetType());
    context->PushSetFlag(ContextFlags::skipInvokeChecking);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    context->PopFlags();
    context->PopSwitchCondType();
    if (boundStmt)
    {
        boundSwitchStatement->SetStatement(boundStmt);
    }
    boundSwitchStatement->SetSource(node.Clone());
    SetStatement(boundSwitchStatement);
    context->GetSymbolTable()->EndScopeGeneric(context);
    context->PopBlockId();
}

void StatementBinder::Visit(otava::ast::CaseStatementNode& node)
{
    if (!TerminatesCaseOrDefault(node.Statement()))
    {
        PrintWarning("case statement does not terminate in return, break or continue statement, or throw expression", node.GetSourcePos(), context);
    }
    BoundExpressionNode* caseExpr = BindExpression(node.CaseExpression(), context);
    if (!caseExpr)
    {
        ThrowException("could not bind expression", node.CaseExpression()->GetSourcePos(), context);
    }
    TypeSymbol* switchCondType = context->GetSwitchCondType();
    if (!TypesEqual(caseExpr->GetType(), switchCondType, context))
    {
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            switchCondType, caseExpr->GetType()->DirectType(context)->FinalType(node.GetSourcePos(), context), node.GetSourcePos(), context);
        if (conversion)
        {
            caseExpr = new BoundConversionNode(caseExpr, conversion, node.GetSourcePos());
        }
        else
        {
            ThrowException("no conversion found", node.GetSourcePos(), context);
        }
    }
    context->PushSetFlag(ContextFlags::skipInvokeChecking);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    context->PopFlags();
    if (boundStmt)
    {
        if (boundStmt->IsBoundCaseStatementNode())
        {
            BoundCaseStatementNode* caseStmt = static_cast<BoundCaseStatementNode*>(boundStmt);
            caseStmt->InsertCaseExprToFront(caseExpr);
            boundStmt->SetSource(node.Clone());
            SetStatement(boundStmt);
        }
        else
        {
            BoundCaseStatementNode* boundCaseStatement = new BoundCaseStatementNode(node.GetSourcePos());
            boundCaseStatement->AddCaseExpr(caseExpr);
            boundCaseStatement->SetStatement(boundStmt);
            boundCaseStatement->SetSource(node.Clone());
            SetStatement(boundCaseStatement);
        }
    }
}

void StatementBinder::Visit(otava::ast::DefaultStatementNode& node)
{
    if (!TerminatesCaseOrDefault(node.Statement()))
    {
        PrintWarning("default statement does not terminate in return, break or continue statement, or throw expression", node.GetSourcePos(), context);
    }
    BoundDefaultStatementNode* boundDefaultStatement = new BoundDefaultStatementNode(node.GetSourcePos());
    context->PushSetFlag(ContextFlags::skipInvokeChecking);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    context->PopFlags();
    if (boundStmt)
    {
        boundDefaultStatement->SetStatement(boundStmt);
    }
    boundDefaultStatement->SetSource(node.Clone());
    SetStatement(boundDefaultStatement);
}

void StatementBinder::Visit(otava::ast::WhileStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    if (!node.Condition()->IsInitConditionNode())
    {
        if (node.BlockId() != -1)
        {
            functionDefinitionSymbol->MapBlock(node.BlockId(), block);
        }
        else
        {
            std::cout << "no block: " << util::ToUtf8(functionDefinitionSymbol->FullName()) << "\n";
        }
        context->PushBlockId(node.BlockId());
        context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
        BoundWhileStatementNode* boundWhileStatement = new BoundWhileStatementNode(node.GetSourcePos());
        boundWhileStatement->SetBlockId(node.BlockId());
        context->PushResetFlag(ContextFlags::returnRef);
        BoundExpressionNode* condition = BindExpression(node.Condition(), context);
        if (!condition)
        {
            ThrowException("could not bind expression", node.Condition()->GetSourcePos(), context);
        }
        if (condition->GetType()->IsReferenceType())
        {
            condition = new BoundDereferenceNode(condition, node.GetSourcePos(), condition->GetType()->GetBaseType());
        }
        if (!condition->GetType()->IsBoolType())
        {
            condition = MakeBoundBooleanConversionNode(condition, context);
        }
        context->PopFlags();
        boundWhileStatement->SetCondition(condition);
        BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
        if (boundStmt)
        {
            boundWhileStatement->SetStatement(boundStmt);
        }
        boundWhileStatement->SetSource(node.Clone());
        SetStatement(boundWhileStatement);
        context->GetSymbolTable()->EndScopeGeneric(context);
        context->PopBlockId();
    }
    else
    {
        bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
        std::u32string label = U"__label" + util::ToUtf32(std::to_string(context->NextLabelSerial()));
        std::unique_ptr<otava::ast::CompoundStatementNode> whileBlock(new otava::ast::CompoundStatementNode(node.GetSourcePos()));
        std::unique_ptr<otava::ast::CompoundStatementNode> ifBlock(new otava::ast::CompoundStatementNode(node.GetSourcePos()));
        ifBlock->AddNode(node.Statement()->Clone());
        ifBlock->AddNode(new otava::ast::GotoStatementNode(node.GetSourcePos(), new otava::ast::IdentifierNode(node.GetSourcePos(), label), nullptr, 
            nullptr, soul::ast::SourcePos()));
        std::unique_ptr<otava::ast::IfStatementNode> ifStatement(new otava::ast::IfStatementNode(node.GetSourcePos(), node.Condition()->Clone(), 
            ifBlock.release(), nullptr, nullptr, node.GetSourcePos(), node.GetSourcePos(), node.GetSourcePos(), node.GetSourcePos(), node.GetSourcePos()));
        whileBlock->AddNode(ifStatement.release());
        std::unique_ptr<otava::ast::LabeledStatementNode> labeledStatement(new otava::ast::LabeledStatementNode(node.GetSourcePos(),
            new otava::ast::IdentifierNode(node.GetSourcePos(), label), whileBlock.release(), nullptr, node.GetSourcePos()));
        InstantiationScope instantiationScope(context->GetSymbolTable()->CurrentScope());
        Instantiator instantiator(context, &instantiationScope);
        context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
        labeledStatement->Accept(instantiator);
        context->PopFlags();
        BoundStatementNode* boundLabeledStatement = BindStatement(labeledStatement.get(), functionDefinitionSymbol, context);
        SetStatement(boundLabeledStatement);
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    }
}

void StatementBinder::Visit(otava::ast::DoStatementNode& node)
{
    BoundDoStatementNode* boundDoStatement = new BoundDoStatementNode(node.GetSourcePos());
    context->PushResetFlag(ContextFlags::returnRef);
    BoundExpressionNode* condition = BindExpression(node.Expression(), context);
    if (!condition)
    {
        ThrowException("could not bind expression", node.Expression()->GetSourcePos(), context);
    }
    if (condition->GetType()->IsReferenceType())
    {
        condition = new BoundDereferenceNode(condition, node.GetSourcePos(), condition->GetType()->GetBaseType());
    }
    if (!condition->GetType()->IsBoolType())
    {
        condition = MakeBoundBooleanConversionNode(condition, context);
    }
    context->PopFlags();
    boundDoStatement->SetExpr(condition);
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundDoStatement->SetStatement(boundStmt);
    }
    boundDoStatement->SetSource(node.Clone());
    SetStatement(boundDoStatement);
}

class RangeForDeclarationExtractor : public otava::ast::DefaultVisitor
{
public:
    RangeForDeclarationExtractor();
    otava::ast::DeclSpecifierSequenceNode* GetDeclSpecifierSequence() { return declSpecifierSequence; }
    otava::ast::Node* GetDeclarator() const { return declarator; }
    void Visit(otava::ast::ForRangeDeclarationNode& node) override;
    void Visit(otava::ast::DeclSpecifierSequenceNode& node) override;
private:
    otava::ast::DeclSpecifierSequenceNode* declSpecifierSequence;
    otava::ast::Node* declarator;
};

RangeForDeclarationExtractor::RangeForDeclarationExtractor() : declSpecifierSequence(nullptr), declarator(nullptr)
{
}

void RangeForDeclarationExtractor::Visit(otava::ast::ForRangeDeclarationNode& node)
{
    node.Left()->Accept(*this);
    declarator = node.Right();
}

void RangeForDeclarationExtractor::Visit(otava::ast::DeclSpecifierSequenceNode& node)
{
    declSpecifierSequence = &node;
}

void StatementBinder::Visit(otava::ast::RangeForStatementNode& node)
{
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    soul::ast::SourcePos sourcePos = node.GetSourcePos();
    context->PushBlockId(node.BlockId());
    std::unique_ptr<otava::ast::CompoundStatementNode> rangeForCompound(new otava::ast::CompoundStatementNode(sourcePos));
    rangeForCompound->SetBlockId(node.BlockId());
    if (node.InitStatement())
    {
        rangeForCompound->AddNode(node.InitStatement()->Clone());
    }
    otava::ast::DeclSpecifierSequenceNode* endIteratorDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    endIteratorDeclSpecifiers->AddNode(new otava::ast::PlaceholderTypeSpecifierNode(sourcePos));
    otava::ast::InitDeclaratorListNode* endIteratorDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
    otava::ast::IdentifierNode* endIteratorDeclarator = new otava::ast::IdentifierNode(sourcePos, U"@end");
    otava::ast::Node* invokeChild = node.Initializer()->Clone();
    otava::ast::IdentifierNode* invokeId = new otava::ast::IdentifierNode(sourcePos, U"end");
    otava::ast::MemberExprNode* invokeSubject = new otava::ast::MemberExprNode(sourcePos, invokeChild, new otava::ast::DotNode(sourcePos), invokeId);
    otava::ast::InvokeExprNode* endIteratorInitializer = new otava::ast::InvokeExprNode(sourcePos, invokeSubject);
    otava::ast::AssignmentInitNode* endIteratorAssignmentInitializer = new otava::ast::AssignmentInitNode(sourcePos, endIteratorInitializer);
    otava::ast::InitDeclaratorNode* endIteratorInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, endIteratorDeclarator, endIteratorAssignmentInitializer);
    endIteratorDeclarators->AddNode(endIteratorInitDeclarator);
    otava::ast::SimpleDeclarationNode* endIteratorDeclaration = new otava::ast::SimpleDeclarationNode(
        sourcePos, endIteratorDeclSpecifiers, endIteratorDeclarators, nullptr, nullptr);
    rangeForCompound->AddNode(endIteratorDeclaration);
    otava::ast::DeclSpecifierSequenceNode* forInitDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    forInitDeclSpecifiers->AddNode(new otava::ast::PlaceholderTypeSpecifierNode(sourcePos));
    otava::ast::InitDeclaratorListNode* forInitDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
    otava::ast::Node* forInitInvokeChild = node.Initializer()->Clone();
    otava::ast::MemberExprNode* forInitInvokeSubject = new otava::ast::MemberExprNode(sourcePos, forInitInvokeChild, new otava::ast::DotNode(sourcePos), 
        new otava::ast::IdentifierNode(sourcePos, U"begin"));
    otava::ast::InvokeExprNode* forInitInitializer = new otava::ast::InvokeExprNode(sourcePos, forInitInvokeSubject);
    otava::ast::AssignmentInitNode* forInitAssignmentInitializer = new otava::ast::AssignmentInitNode(sourcePos, forInitInitializer);
    otava::ast::IdentifierNode* forInitDeclarator = new otava::ast::IdentifierNode(sourcePos, U"@it");
    otava::ast::InitDeclaratorNode* forInitInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, forInitDeclarator, forInitAssignmentInitializer);
    forInitDeclarators->AddNode(forInitInitDeclarator);
    otava::ast::SimpleDeclarationNode* forInitStmt = new otava::ast::SimpleDeclarationNode(sourcePos, forInitDeclSpecifiers, forInitDeclarators, nullptr, nullptr);
    otava::ast::BinaryExprNode* forCond = new otava::ast::BinaryExprNode(
        sourcePos, new otava::ast::NotEqualNode(sourcePos), new otava::ast::IdentifierNode(sourcePos, U"@it"),
        new otava::ast::IdentifierNode(sourcePos, U"@end"));
    otava::ast::UnaryExprNode* forLoopExpr = new otava::ast::UnaryExprNode(
        sourcePos, new otava::ast::PrefixIncNode(sourcePos), new otava::ast::IdentifierNode(sourcePos, U"@it"));
    otava::ast::CompoundStatementNode* forActionStmt = new otava::ast::CompoundStatementNode(sourcePos);
    forActionStmt->SetBlockId(context->NextBlockId());
    RangeForDeclarationExtractor extractor;
    node.Declaration()->Accept(extractor);
    otava::ast::DeclSpecifierSequenceNode* forActionDeclSpecifiers = extractor.GetDeclSpecifierSequence();
    otava::ast::Node* declarator = extractor.GetDeclarator();
    otava::ast::AssignmentInitNode* forActionAssignmentInit = new otava::ast::AssignmentInitNode(sourcePos, new otava::ast::UnaryExprNode(sourcePos, 
        new otava::ast::DerefNode(sourcePos), new otava::ast::IdentifierNode(sourcePos, U"@it")));
    otava::ast::InitDeclaratorNode* forActionInitDeclarator = new otava::ast::InitDeclaratorNode(sourcePos, declarator->Clone(), forActionAssignmentInit);
    otava::ast::InitDeclaratorListNode* forActionInitDeclaratorList = new otava::ast::InitDeclaratorListNode(sourcePos);
    forActionInitDeclaratorList->AddNode(forActionInitDeclarator);
    otava::ast::SimpleDeclarationNode* forActionDeclaration = new otava::ast::SimpleDeclarationNode(
        sourcePos, forActionDeclSpecifiers->Clone(), forActionInitDeclaratorList, nullptr, nullptr);
    otava::ast::DeclarationStatementNode* forActionDeclarationStmt = new otava::ast::DeclarationStatementNode(sourcePos, forActionDeclaration);
    forActionStmt->AddNode(forActionDeclarationStmt);
    forActionStmt->AddNode(node.Statement()->Clone());
    otava::ast::ForStatementNode* forStmt = new otava::ast::ForStatementNode(sourcePos, forInitStmt, forCond, forLoopExpr, forActionStmt, nullptr, nullptr,
        sourcePos, sourcePos, sourcePos);
    rangeForCompound->AddNode(forStmt);
    InstantiationScope instantiationScope(context->GetSymbolTable()->CurrentScope());
    Instantiator instantiator(context, &instantiationScope);
    context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
    rangeForCompound->Accept(instantiator);
    context->PopFlags();
    rangeForCompound->Accept(*this);
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    if (boundStatement)
    {
        boundStatement->SetSource(node.Clone());
    }
    context->PopBlockId();
}

void StatementBinder::Visit(otava::ast::ForStatementNode& node)
{
    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(&node);
    if (!block) return;
    if (node.BlockId() != -1)
    {
        functionDefinitionSymbol->MapBlock(node.BlockId(), block);
    }
    else
    {
        std::cout << "no block: " << util::ToUtf8(functionDefinitionSymbol->FullName()) << "\n";
    }
    context->PushBlockId(node.BlockId());
    context->GetSymbolTable()->BeginScopeGeneric(block->GetScope(), context);
    BoundForStatementNode* boundForStatement = new BoundForStatementNode(node.GetSourcePos());
    boundForStatement->SetBlockId(node.BlockId());
    if (node.InitStatement())
    {
        BoundStatementNode* boundInitStatement = BindStatement(node.InitStatement(), functionDefinitionSymbol, context);
        if (boundInitStatement)
        {
            boundForStatement->SetInitStatement(boundInitStatement);
        }
    }
    if (node.Condition())
    {
        context->PushResetFlag(ContextFlags::returnRef);
        BoundExpressionNode* condition = BindExpression(node.Condition(), context);
        if (!condition)
        {
            ThrowException("could not bind expression", node.Condition()->GetSourcePos(), context);
        }
        if (condition->GetType()->IsReferenceType())
        {
            condition = new BoundDereferenceNode(condition, node.GetSourcePos(), condition->GetType()->GetBaseType());
        }
        if (!condition->GetType()->IsBoolType())
        {
            condition = MakeBoundBooleanConversionNode(condition, context);
        }
        context->PopFlags();
        boundForStatement->SetCondition(condition);
    }
    if (node.LoopExpr())
    {
        BoundExpressionNode* loopExpr = BindExpression(node.LoopExpr(), context);
        if (!loopExpr)
        {
            ThrowException("could not bind expression", node.LoopExpr()->GetSourcePos(), context);
        }
        boundForStatement->SetLoopExpr(loopExpr);
    }
    BoundStatementNode* boundStmt = BindStatement(node.Statement(), functionDefinitionSymbol, context);
    if (boundStmt)
    {
        boundForStatement->SetStatement(boundStmt);
    }
    boundForStatement->SetSource(node.Clone());
    SetStatement(boundForStatement);
    context->GetSymbolTable()->EndScopeGeneric(context);
    context->PopBlockId();
}

void StatementBinder::Visit(otava::ast::BreakStatementNode& node)
{
    BoundBreakStatementNode* boundBreakStatement = new BoundBreakStatementNode(node.GetSourcePos());
    boundBreakStatement->SetSource(node.Clone());
    SetStatement(boundBreakStatement);
}

void StatementBinder::Visit(otava::ast::ContinueStatementNode& node)
{
    BoundContinueStatementNode* boundContinueStatement = new BoundContinueStatementNode(node.GetSourcePos());
    boundContinueStatement->SetSource(node.Clone());
    SetStatement(boundContinueStatement);
}

void StatementBinder::Visit(otava::ast::ReturnStatementNode& node)
{
    if (context->GetFlag(ContextFlags::makeChildFn))
    {
        BoundStatementNode* boundStatement = ConvertReturnStatement(&node, functionDefinitionSymbol, context);
        SetStatement(boundStatement);
    }
    else
    {
        TypeSymbol* voidType = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::voidType);
        BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode(node.GetSourcePos());
        if (node.ReturnValue())
        {
            if (!context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnType() ||
                TypesEqual(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnType()->DirectType(context)->FinalType(node.GetSourcePos(), context),
                    voidType, context))
            {
                ThrowException("cannot return a value", node.ReturnValue()->GetSourcePos(), context);
            }
            if (context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnsClass())
            {
                std::vector<std::unique_ptr<BoundExpressionNode>> classReturnArgs;
                ParameterSymbol* returnValueParam = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnValueParam();
                classReturnArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundParameterNode(returnValueParam,
                    node.GetSourcePos(), returnValueParam->GetReferredType(context))));
                BoundExpressionNode* expression = BindExpression(node.ReturnValue(), context);
                if (!expression)
                {
                    ThrowException("could not bind expression", node.ReturnValue()->GetSourcePos(), context);
                }
                if (expression->IsBoundLocalVariable())
                {
                    std::vector<std::unique_ptr<BoundExpressionNode>> moveArgs;
                    moveArgs.push_back(std::unique_ptr<BoundExpressionNode>(expression));
                    Scope* scope = context->GetSymbolTable()->GetNamespaceScope(U"std", node.GetSourcePos(), context);
                    std::vector<TypeSymbol*> templateArgs;
                    std::unique_ptr<BoundFunctionCallNode> moveExpr = ResolveOverloadThrow(
                        scope, U"move", templateArgs, moveArgs, node.GetSourcePos(), context, OverloadResolutionFlags::dontSearchArgumentScopes);
                    expression = moveExpr.release();
                }
                classReturnArgs.push_back(std::unique_ptr<BoundExpressionNode>(expression));
                std::vector<TypeSymbol*> templateArgs;
                std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverloadThrow(
                    context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, classReturnArgs, node.GetSourcePos(), context);
                std::unique_ptr<BoundExpressionStatementNode> expressionStatement(new BoundExpressionStatementNode(node.GetSourcePos()));
                expressionStatement->SetExpr(constructorCall.release(), node.GetSourcePos(), context);
                SetStatement(expressionStatement.release());
            }
            else
            {
                TypeSymbol* returnType = functionDefinitionSymbol->ReturnType()->DirectType(context)->FinalType(node.GetSourcePos(), context);
                bool flagsPushed = false;
                if (returnType->IsReferenceType())
                {
                    context->PushSetFlag(ContextFlags::returnRef);
                    flagsPushed = true;
                }
                BoundExpressionNode* returnValueExpr = BindExpression(node.ReturnValue(), context);
                if (!returnValueExpr)
                {
                    ThrowException("could not bind expression", node.ReturnValue()->GetSourcePos(), context);
                }
                if (!TypesEqual(returnValueExpr->GetType(), returnType, context))
                {
                    if (TypesEqual(returnValueExpr->GetType()->PlainType(context), returnType->PlainType(context), context))
                    {
                        if (!(
                            returnType->IsLValueRefType() && returnValueExpr->GetType()->IsRValueRefType() ||
                            returnType->IsRValueRefType() && returnValueExpr->GetType()->IsLValueRefType()))
                        {

                            if (returnType->IsLValueRefType())
                            {
                                returnValueExpr = new BoundAddressOfNode(returnValueExpr, node.GetSourcePos(), returnValueExpr->GetType()->AddLValueRef(context));
                            }
                            else if (returnValueExpr->GetType()->IsLValueRefType())
                            {
                                returnValueExpr = new BoundDereferenceNode(returnValueExpr, node.GetSourcePos(), returnValueExpr->GetType()->RemoveReference(context));
                            }
                        }
                    }
                    else
                    {
                        ArgumentMatch argumentMatch;
                        FunctionMatch functionMatch;
                        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                            returnType, returnValueExpr->GetType()->DirectType(context)->FinalType(node.GetSourcePos(), context), returnValueExpr,
                            node.GetSourcePos(), argumentMatch, functionMatch, context);
                        if (conversion)
                        {
                            if (argumentMatch.preConversionFlags == OperationFlags::addr)
                            {
                                returnValueExpr = new BoundConversionNode(
                                    new BoundAddressOfNode(returnValueExpr, node.GetSourcePos(), returnValueExpr->GetType()->AddPointer(context)), conversion,
                                    node.GetSourcePos());
                            }
                            else
                            {
                                returnValueExpr = new BoundConversionNode(returnValueExpr, conversion, node.GetSourcePos());
                            }
                        }
                        else
                        {
                            ThrowException("no conversion found", node.GetSourcePos(), context);
                        }
                    }
                }
                boundReturnStatement->SetExpr(returnValueExpr, node.GetSourcePos(), context);
                if (flagsPushed)
                {
                    context->PopFlags();
                }
            }
        }
        else if (context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnType() &&
            !TypesEqual(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ReturnType()->DirectType(context)->FinalType(node.GetSourcePos(), context),
                voidType, context))
        {
            ThrowException("must return a value", node.GetSourcePos(), context);
        }
        boundReturnStatement->SetSource(node.Clone());
        SetStatement(boundReturnStatement);
    }
}

void StatementBinder::Visit(otava::ast::ExpressionStatementNode& node)
{
    BoundExpressionStatementNode* boundExpressionStatement = new BoundExpressionStatementNode(node.GetSourcePos());
    if (node.Expression())
    {
        BoundExpressionNode* expr = BindExpression(node.Expression(), context);
        if (!expr)
        {
            ThrowException("could not bind expression", node.Expression()->GetSourcePos(), context);
        }
        if (expr->IsBoundConstructTemporaryNode())
        {
            BoundConstructTemporaryNode* ctNode = static_cast<BoundConstructTemporaryNode*>(expr);
            BoundExpressionNode* call = ctNode->ConstructorCall();
            if (call->IsBoundFunctionCallNode())
            {
                BoundFunctionCallNode* fnCall = static_cast<BoundFunctionCallNode*>(call);
                FunctionSymbol* fn = fnCall->GetFunctionSymbol();
                TypeSymbol* returnType = fn->ReturnType();
                if (returnType && returnType->IsClassTemplateSpecializationSymbol())
                {
                    ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(returnType);
                    ClassTypeSymbol* ct = sp->ClassTemplate();
                    ClassGroupSymbol* group = ct->Group();
                    if (group->Name() == U"expected")
                    {
                        PrintWarning("discarding return value of function '" + util::ToUtf8(fn->FullName()) + "", node.GetSourcePos(), context);
                    }
                }
            }
        }
        boundExpressionStatement->SetExpr(expr, node.GetSourcePos(), context);
    }
    boundExpressionStatement->SetSource(node.Clone());
    SetStatement(boundExpressionStatement);
}

void StatementBinder::Visit(otava::ast::DeclarationStatementNode& node)
{
    node.Declaration()->Accept(*this);
    if (boundStatement)
    {
        boundStatement->SetSource(node.Clone());
    }
}

void StatementBinder::Visit(otava::ast::TryStatementNode& node)
{
    std::u32string tryResultVar = context->NextResultVarName();
    std::u32string handlerResultVar = context->NextResultVarName();
    std::u32string ehReturnFromVar = context->NextEhReturnFromVarName();
    std::u32string childControlResultVar = context->NextChildControlResultVarName();
    TypeSymbol* resultType = functionDefinitionSymbol->NonChildFunctionResultType(context);
    std::unique_ptr<otava::ast::Node> tryVarDeclarationStmtNode;
    std::unique_ptr<otava::ast::Node> handlerVarDeclarationStmtNode;
    std::unique_ptr<BoundStatementNode> boundTryVarDeclarationStatement;
    std::unique_ptr<BoundStatementNode> boundHandlerVarDeclarationStatement;
    std::unique_ptr<BoundStatementNode> boundChildControlResultStatement;
    std::unique_ptr<BoundStatementNode> boundEhReturnFromStatement;
    if (resultType)
    {
        TypeSymbol* nonReferenceType = ConvertRefToPtrType(resultType, context);
        std::u32string tryVarDeclarationStatementText;
        tryVarDeclarationStatementText.append(nonReferenceType->FullName()).append(1, ' ').append(tryResultVar);
        if (nonReferenceType->IsPointerType())
        {
            tryVarDeclarationStatementText.append(U" = nullptr;");
        }
        else
        {
            tryVarDeclarationStatementText.append(U";");
        }
        tryVarDeclarationStmtNode = ParseStatement(tryVarDeclarationStatementText, context);
        boundTryVarDeclarationStatement.reset(BindStatement(tryVarDeclarationStmtNode.get(), functionDefinitionSymbol, context));
        std::u32string handlerVarDeclarationStatementText;
        handlerVarDeclarationStatementText.append(nonReferenceType->FullName()).append(1, ' ').append(handlerResultVar);
        if (nonReferenceType->IsPointerType())
        {
            handlerVarDeclarationStatementText.append(U" = nullptr;");
        }
        else
        {
            handlerVarDeclarationStatementText.append(U";");
        }
        handlerVarDeclarationStmtNode = ParseStatement(handlerVarDeclarationStatementText, context);
        boundHandlerVarDeclarationStatement.reset(BindStatement(handlerVarDeclarationStmtNode.get(), functionDefinitionSymbol, context));
    }
    std::u32string childControlResultStatementText;
    childControlResultStatementText.append(U"std::child_control_result ").append(childControlResultVar).append(U" = std::child_control_result::none;");
    std::unique_ptr<otava::ast::Node> setChildControlResultStmtNode = ParseStatement(childControlResultStatementText, context);
    boundChildControlResultStatement.reset(BindStatement(setChildControlResultStmtNode.get(), functionDefinitionSymbol, context));
    boundChildControlResultStatement->SetSource(setChildControlResultStmtNode.release());
    std::u32string ehReturnFromTryBlockStatementText;
    ehReturnFromTryBlockStatementText.append(U"std::eh_return_from ").append(ehReturnFromVar).append(U" = std::eh_return_from::try_block;");
    std::unique_ptr<otava::ast::Node> ehReturnFromTryBlockStmtNode = ParseStatement(ehReturnFromTryBlockStatementText, context);
    boundEhReturnFromStatement.reset(BindStatement(ehReturnFromTryBlockStmtNode.get(), functionDefinitionSymbol, context));
    boundEhReturnFromStatement->SetSource(ehReturnFromTryBlockStmtNode.release());
    FunctionDefinitionSymbol* parentFn = context->GetBoundFunction()->GetFunctionDefinitionSymbol();
    Scope* parentFnScope = context->GetSymbolTable()->CurrentScope();
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    otava::ast::CompoundStatementNode* tryBlock = static_cast<otava::ast::CompoundStatementNode*>(node.TryBlock()->Clone());
    otava::ast::DeclSpecifierSequenceNode* tryDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(node.GetSourcePos());
    tryDeclSpecifiers->AddNode(new otava::ast::VoidNode(node.GetSourcePos()));
    int trySerial = context->NextTrySerial();
    otava::ast::ParameterListNode* tryParameters = new otava::ast::ParameterListNode(node.GetSourcePos());
    otava::ast::ParameterNode* tryParameter = new otava::ast::ParameterNode(node.GetSourcePos());
    otava::ast::DeclSpecifierSequenceNode* tryParamDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(node.GetSourcePos());
    tryParamDeclSpecifiers->AddNode(new otava::ast::VoidNode(node.GetSourcePos()));
    tryParameter->SetDeclSpecifiers(tryParamDeclSpecifiers);
    otava::ast::PtrDeclaratorNode* tryPtrDeclarator = new otava::ast::PtrDeclaratorNode(node.GetSourcePos());
    tryPtrDeclarator->AddNode(new otava::ast::PtrNode(node.GetSourcePos()));
    tryPtrDeclarator->AddNode(new otava::ast::IdentifierNode(node.GetSourcePos(), U"__parentFrame"));
    tryParameter->SetDeclarator(tryPtrDeclarator);
    tryParameters->AddNode(tryParameter);
    otava::ast::FunctionDeclaratorNode* tryDeclarator = new otava::ast::FunctionDeclaratorNode(node.GetSourcePos(), 
        new otava::ast::IdentifierNode(node.GetSourcePos(), U"try_" + 
            util::ToUtf32(std::to_string(trySerial)) + U"_" + util::ToUtf32(context->GetBoundCompileUnit()->Id())), tryParameters);
    std::unique_ptr<otava::ast::FunctionDefinitionNode> tryFn(new otava::ast::FunctionDefinitionNode(
        node.GetSourcePos(), nullptr, tryDeclSpecifiers, tryDeclarator, nullptr, new otava::ast::FunctionBodyNode(node.GetSourcePos(), tryBlock)));
    InstantiationScope tryInstantiationScope(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->Parent()->GetScope());
    //tryInstantiationScope.PushParentScope(context->GetSymbolTable()->GetNamespaceScope(U"std", node.GetSourcePos(), context));
    tryInstantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
    context->GetSymbolTable()->BeginScope(&tryInstantiationScope);
    Instantiator tryInstantiator(context, &tryInstantiationScope);
    tryInstantiator.SetFunctionNode(tryFn.get());
    context->PushSetFlag(ContextFlags::instantiateInlineFunction | ContextFlags::saveDeclarations | ContextFlags::dontBind);
    tryFn->Accept(tryInstantiator);
    int tryfnScopeCount = tryInstantiator.ScopeCount();
    FunctionDefinitionSymbol* tryFnSymbol = static_cast<FunctionDefinitionSymbol*>(tryInstantiator.GetSpecialization());
    tryFnSymbol->SetParentFn(parentFn);
    tryFnSymbol->SetParentFnScope(parentFnScope);
    context->PushBoundFunction(new BoundFunctionNode(tryFnSymbol, node.GetSourcePos()));
    context->PushSetFlag(ContextFlags::makeChildFn);
    context->PushResultVarName(tryResultVar);
    context->PushChildControlResultVarName(childControlResultVar);
    tryFnSymbol->SetResultVarName(tryResultVar);
    tryFnSymbol = BindFunction(tryFn.get(), tryFnSymbol, context);
    otava::symbols::EndFunctionDefinition(tryFn.get(), tryfnScopeCount, context);
    context->PopChildControlResultVarName();
    context->PopResultVarName();
    context->PopFlags();
    context->PopFlags();
    //if (tryFnSymbol->IsBound())
    //{
        //context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
    //}
    //context->PopBoundFunction();
    context->GetSymbolTable()->EndScope();
    tryInstantiationScope.PopParentScope();
    tryInstantiationScope.PopParentScope();
    tryFnSymbol->SetFnDefNode(tryFn.release());
    otava::ast::CompoundStatementNode* prevHandlerBlock = handlerBlock;
    handlerBlock = new otava::ast::CompoundStatementNode(node.GetSourcePos());
    handlerBlock->SetBlockId(context->NextBlockId());
    node.Handlers()->Accept(*this);
    std::u32string ehReturnFromHandlerStmtText;
    ehReturnFromHandlerStmtText.append(ehReturnFromVar).append(U" = std::eh_return_from::handler_block;");
    std::unique_ptr<otava::ast::Node> ehReturnFromHandlerStmt = ParseStatement(ehReturnFromHandlerStmtText, context);
    handlerBlock->AddNode(ehReturnFromHandlerStmt.release());
    otava::ast::DeclSpecifierSequenceNode* handlerDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(node.GetSourcePos());
    handlerDeclSpecifiers->AddNode(new otava::ast::VoidNode(node.GetSourcePos()));
    otava::ast::ParameterListNode* handlerParameters = new otava::ast::ParameterListNode(node.GetSourcePos());
    otava::ast::ParameterNode* handlerParameter = new otava::ast::ParameterNode(node.GetSourcePos());
    otava::ast::DeclSpecifierSequenceNode* handlerParamDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(node.GetSourcePos());
    handlerParamDeclSpecifiers->AddNode(new otava::ast::VoidNode(node.GetSourcePos()));
    handlerParameter->SetDeclSpecifiers(handlerParamDeclSpecifiers);
    otava::ast::PtrDeclaratorNode* handlerPtrDeclarator = new otava::ast::PtrDeclaratorNode(node.GetSourcePos());
    handlerPtrDeclarator->AddNode(new otava::ast::PtrNode(node.GetSourcePos()));
    handlerPtrDeclarator->AddNode(new otava::ast::IdentifierNode(node.GetSourcePos(), U"__parentFrame"));
    handlerParameter->SetDeclarator(handlerPtrDeclarator);
    handlerParameters->AddNode(handlerParameter);
    otava::ast::FunctionDeclaratorNode* handlerDeclarator = new otava::ast::FunctionDeclaratorNode(node.GetSourcePos(),
        new otava::ast::IdentifierNode(node.GetSourcePos(), U"handler_" + 
            util::ToUtf32(std::to_string(trySerial)) + U"_" + util::ToUtf32(context->GetBoundCompileUnit()->Id())), handlerParameters);
    std::unique_ptr<otava::ast::FunctionDefinitionNode> handlerFn(new otava::ast::FunctionDefinitionNode(node.GetSourcePos(), nullptr, 
        handlerDeclSpecifiers, handlerDeclarator, nullptr, new otava::ast::FunctionBodyNode(node.GetSourcePos(), handlerBlock)));
    InstantiationScope handlerInstantiationScope(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->Parent()->GetScope());
    //handlerInstantiationScope.PushParentScope(context->GetSymbolTable()->GetNamespaceScope(U"std", node.GetSourcePos(), context));
    handlerInstantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
    context->GetSymbolTable()->BeginScope(&handlerInstantiationScope);
    Instantiator handlerInstantiator(context, &handlerInstantiationScope);
    handlerInstantiator.SetFunctionNode(handlerFn.get());
    context->PushSetFlag(ContextFlags::instantiateInlineFunction | ContextFlags::saveDeclarations | ContextFlags::dontBind);
    handlerFn->Accept(handlerInstantiator);
    int handlerFnScopeCount = handlerInstantiator.ScopeCount();
    FunctionDefinitionSymbol* handlerFnSymbol = static_cast<FunctionDefinitionSymbol*>(handlerInstantiator.GetSpecialization());
    handlerFnSymbol->SetParentFn(parentFn);
    handlerFnSymbol->SetParentFnScope(parentFnScope);
    context->PushBoundFunction(new BoundFunctionNode(handlerFnSymbol, node.GetSourcePos()));
    context->PushSetFlag(ContextFlags::makeChildFn);
    context->PushResultVarName(handlerResultVar);
    context->PushChildControlResultVarName(childControlResultVar);
    handlerFnSymbol->SetResultVarName(handlerResultVar);
    handlerFnSymbol = BindFunction(handlerFn.get(), handlerFnSymbol, context);
    otava::symbols::EndFunctionDefinition(handlerFn.get(), handlerFnScopeCount, context);
    context->PopChildControlResultVarName();
    context->PopResultVarName();
    context->PopFlags();
    context->PopFlags();
    //if (handlerFnSymbol->IsBound())
    //{
        //context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
    //}
    //context->PopBoundFunction();
    context->GetSymbolTable()->EndScope();
    handlerInstantiationScope.PopParentScope();
    handlerInstantiationScope.PopParentScope();
    handlerFnSymbol->SetFnDefNode(handlerFn.release());
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    std::unique_ptr<otava::ast::CompoundStatementNode> invokeOrtTryBlock(new otava::ast::CompoundStatementNode(node.GetSourcePos()));
    int blockId = -1;
    if (!functionDefinitionSymbol->Blocks().empty())
    {
        blockId = functionDefinitionSymbol->Blocks().front()->BlockId();
    }
    invokeOrtTryBlock->SetBlockId(blockId);
    if (resultType && tryVarDeclarationStmtNode && handlerVarDeclarationStmtNode)
    {
        invokeOrtTryBlock->AddNode(tryVarDeclarationStmtNode.release());
        invokeOrtTryBlock->AddNode(handlerVarDeclarationStmtNode.release());
    }
    invokeOrtTryBlock->AddNode(new otava::ast::BoundStatementNode(boundChildControlResultStatement.release(), node.GetSourcePos()));
    invokeOrtTryBlock->AddNode(new otava::ast::BoundStatementNode(boundEhReturnFromStatement.release(), node.GetSourcePos()));
    otava::ast::InvokeExprNode* invokeOrtTry = new otava::ast::InvokeExprNode(node.GetSourcePos(), new otava::ast::IdentifierNode(node.GetSourcePos(), U"ort_try"));
    invokeOrtTry->AddNode(new otava::ast::IdentifierNode(node.GetSourcePos(), tryFnSymbol->Name()));
    invokeOrtTry->AddNode(new otava::ast::IdentifierNode(node.GetSourcePos(), handlerFnSymbol->Name()));
    otava::ast::InvokeExprNode* getFramePtrIntrics = new otava::ast::InvokeExprNode(node.GetSourcePos(), new otava::ast::IdentifierNode(node.GetSourcePos(), U"__intrinsic_get_frame_ptr"));
    invokeOrtTry->AddNode(getFramePtrIntrics);
    std::unique_ptr<otava::ast::ExpressionStatementNode> ortTryStmt(new otava::ast::ExpressionStatementNode(node.GetSourcePos(), invokeOrtTry, nullptr, nullptr));
    invokeOrtTryBlock->AddNode(ortTryStmt.release());
    if (tryFnSymbol->GetFlag(FunctionSymbolFlags::containsReturnStatement))
    {
        std::u32string tryBlockReturnStmtText;
        tryBlockReturnStmtText.append(U"if (").append(ehReturnFromVar).append(U" == std::eh_return_from::try_block && ").
            append(childControlResultVar).append(U" == std::child_control_result::ret) return ").append(tryFnSymbol->ResultVarExprStr(resultType)).append(U";");
        std::unique_ptr<otava::ast::Node> tryBlockReturnFromStmt = ParseStatement(tryBlockReturnStmtText, context);
        invokeOrtTryBlock->AddNode(tryBlockReturnFromStmt.release());
    }
    if (handlerFnSymbol->GetFlag(FunctionSymbolFlags::containsReturnStatement))
    {
        std::u32string handlerBlockReturnStmtText;
        handlerBlockReturnStmtText.append(U"if (").append(ehReturnFromVar).append(U" == std::eh_return_from::handler_block && ").
            append(childControlResultVar).append(U" == std::child_control_result::ret) return ").append(handlerFnSymbol->ResultVarExprStr(resultType)).append(U";");
        std::unique_ptr<otava::ast::Node> handlerBlockReturnStmt = ParseStatement(handlerBlockReturnStmtText, context);
        invokeOrtTryBlock->AddNode(handlerBlockReturnStmt.release());
    }
    InstantiationScope ortTryBlockInstantiationScope(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->Parent()->GetScope());
    ortTryBlockInstantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope());
    context->GetSymbolTable()->BeginScope(&ortTryBlockInstantiationScope);
    Instantiator ortTryBlockInstantiator(context, &ortTryBlockInstantiationScope);
    context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
    invokeOrtTryBlock->Accept(ortTryBlockInstantiator);
    context->PopFlags();
    BoundStatementNode* stmt = BindStatement(invokeOrtTryBlock.get(), functionDefinitionSymbol, context);
    stmt->SetSource(node.Clone());
    SetStatement(stmt);
    context->GetSymbolTable()->EndScope();
    handlerBlock = prevHandlerBlock;
}

void StatementBinder::Visit(otava::ast::HandlerSequenceNode& node)
{
    lastElse = nullptr;
    for (const auto& handlerNode : node.Nodes())
    {
        handlerNode->Accept(*this);
    }
    if (lastElse)
    {
        context->PushFlags();
        context->ResetFlags();
        std::unique_ptr<otava::ast::Node> resume = ParseStatement(U"ort_resume();", context);
        context->PopFlags();
        lastElse->AddNode(resume.release());
        lastElse = nullptr;
    }
}

void StatementBinder::Visit(otava::ast::HandlerNode& node)
{
    catchBlock = node.CatchBlock();
    node.Exception()->Accept(*this);
}

void StatementBinder::Visit(otava::ast::ExceptionDeclarationNode& node)
{
    context->PushFlags();
    context->ResetFlags();
    Declaration declaration = ProcessExceptionDeclaration(&node, context);
    TypeSymbol* type = declaration.type;
    if (type)
    {
        TypeSymbol* plainType = type->PlainType(context);
        std::uint64_t ext1;
        std::uint64_t ext2;
        util::UuidToInts(plainType->Id(), ext1, ext2);
        std::u32string beginCatchStr;
        beginCatchStr.append(U"ort_begin_catch(").append(util::ToUtf32(std::to_string(ext1)).append(U"ull, ").append(
            util::ToUtf32(std::to_string(ext2)).append(U"ull)")));
        std::unique_ptr<otava::ast::Node> beginCatchNode = ParseExpression(beginCatchStr, context->GetModule());
        std::unique_ptr<otava::ast::CompoundStatementNode> completeCatchBlock(new otava::ast::CompoundStatementNode(node.GetSourcePos()));
        std::unique_ptr<otava::ast::CompoundStatementNode> elseBlock(new otava::ast::CompoundStatementNode(node.GetSourcePos()));
        otava::ast::CompoundStatementNode* thisElse = elseBlock.get();
        TypeSymbol* exceptionPtrType = plainType->AddPointer(context);
        std::u32string makeExPtrStmtStr;
        makeExPtrStmtStr.append(exceptionPtrType->FullName());
        makeExPtrStmtStr.append(U" __ex = static_cast<").append(exceptionPtrType->FullName()).append(U">(ort_get_exception());");
        std::unique_ptr<otava::ast::Node> makeExPtrStmtNode = ParseStatement(makeExPtrStmtStr, context);
        completeCatchBlock->AddNode(makeExPtrStmtNode.release());
        std::u32string makeExRefStmtStr;
        makeExRefStmtStr.append(plainType->FullName());
        makeExRefStmtStr.append(U" ").append(node.Declarator()->Str()).append(U" = *__ex;");
        std::unique_ptr<otava::ast::Node> makeExRefStmtNode = ParseStatement(makeExRefStmtStr, context);
        completeCatchBlock->AddNode(makeExRefStmtNode.release());
        completeCatchBlock->AddNode(catchBlock->Clone());
        std::u32string deleteExceptionStmtStr;
        deleteExceptionStmtStr.append(U"if (!ort_current_ex_is_bad_alloc()) delete __ex;");
        std::unique_ptr<otava::ast::Node> deleteExceptionStmtNode = ParseStatement(deleteExceptionStmtStr, context);
        completeCatchBlock->AddNode(deleteExceptionStmtNode.release());
        std::unique_ptr<otava::ast::Node>  endCatchStmt = ParseStatement(U"ort_end_catch();", context);
        completeCatchBlock->AddNode(endCatchStmt.release());
        otava::ast::IfStatementNode* ifStmt(new otava::ast::IfStatementNode(node.GetSourcePos(), 
            beginCatchNode.release(), completeCatchBlock.release(), elseBlock.release(), nullptr, soul::ast::SourcePos(), soul::ast::SourcePos(), 
            soul::ast::SourcePos(), soul::ast::SourcePos(), soul::ast::SourcePos()));
        if (lastElse)
        {
            lastElse->AddNode(ifStmt);
        }
        else
        {
            handlerBlock->AddNode(ifStmt);
        }
        lastElse = thisElse;
    }
    else
    {
        if (lastElse)
        {
            lastElse->AddNode(catchBlock->Clone());
        }
        else
        {
            handlerBlock->AddNode(catchBlock->Clone());
        }
        lastElse = nullptr;
    }
    context->PopFlags();
}

void StatementBinder::Visit(otava::ast::AliasDeclarationNode& node)
{
    ProcessAliasDeclaration(&node, context);
    BoundAliasDeclarationStatementNode* boundAliasDeclarationStatment = new BoundAliasDeclarationStatementNode(node.GetSourcePos());
    SetStatement(boundAliasDeclarationStatment);
}

void StatementBinder::Visit(otava::ast::SimpleDeclarationNode& node)
{
    BoundStatementNode* boundStatement = nullptr;
    std::unique_ptr<DeclarationList> declarationList = context->ReleaseDeclarationList(&node);
    if (declarationList )
    {
        bool setStatement = true;
        for (auto& declaration : declarationList->declarations)
        {
            VariableSymbol* variable = declaration.variable;
            if (variable->IsStatic())
            {
                BindStaticLocalVariable(variable, declaration.initializer, &node);
                setStatement = false;
            }
            else
            {
                BoundExpressionNode* initializer = nullptr;
                if (declaration.initializer)
                {
                    bool flagsPushed = false;
                    if (variable->GetDeclaredType()->IsReferenceType())
                    {
                        context->PushSetFlag(ContextFlags::returnRef);
                        flagsPushed = true;
                    }
                    context->SetDeclaredInitializerType(variable->GetDeclaredType());
                    initializer = BindExpression(declaration.initializer, context);
                    context->SetDeclaredInitializerType(nullptr);
                    if (flagsPushed)
                    {
                        context->PopFlags();
                    }
                }
                if (initializer && initializer->GetType())
                {
                    TypeSymbol* initializerType = initializer->GetType()->DirectType(context)->FinalType(node.GetSourcePos(), context);
                    if (variable->GetDeclaredType()->GetBaseType()->IsAutoTypeSymbol() && variable->GetDeclaredType()->GetDerivations() != Derivations::none)
                    {
                        initializerType = context->GetSymbolTable()->MakeCompoundType(initializerType->GetBaseType(), 
                            variable->GetDeclaredType()->GetDerivations(), context);
                    }
                    variable->SetInitializerType(initializerType);
                }
                BoundVariableNode* boundVariable = new BoundVariableNode(variable, node.GetSourcePos());
                std::vector<std::unique_ptr<BoundExpressionNode>> arguments;
                arguments.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariable, node.GetSourcePos(), 
                    boundVariable->GetType()->AddPointer(context))));
                if (initializer)
                {
                    if (initializer->IsBoundExpressionListNode())
                    {
                        BoundExpressionListNode* exprListNode = static_cast<BoundExpressionListNode*>(initializer);
                        int n = exprListNode->Count();
                        for (int i = 0; i < n; ++i)
                        {
                            arguments.push_back(std::unique_ptr<BoundExpressionNode>(exprListNode->ReleaseExpr(i)));
                        }
                    }
                    else
                    {
                        arguments.push_back(std::unique_ptr<BoundExpressionNode>(initializer));
                    }
                }
                std::vector<TypeSymbol*> templateArgs;
                std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope(), 
                    U"@constructor", templateArgs, arguments, node.GetSourcePos(), context);
                BoundConstructionStatementNode* boundConstructionStatement = nullptr;
                otava::symbols::ClassTypeSymbol* cls = nullptr;
                BoundExpressionNode* firstArg = nullptr;
                FunctionDefinitionSymbol* destructor = nullptr;
                if (constructorCall->CallsClassConstructor(cls, firstArg, destructor))
                {
                    boundConstructionStatement = new BoundConstructionStatementNode(node.GetSourcePos(), constructorCall.release());
                    boundConstructionStatement->SetVariable(variable);
                    otava::symbols::BoundFunctionCallNode* destructorCall = MakeDestructorCall(cls, firstArg, destructor, node.GetSourcePos(), context);
                    if (destructorCall)
                    {
                        boundConstructionStatement->SetDestructorCall(destructorCall);
                        functionDefinitionSymbol->SetFlag(FunctionSymbolFlags::containsLocalVariableWithDestructor);
                    }
                }
                else
                {
                    boundConstructionStatement = new BoundConstructionStatementNode(node.GetSourcePos(), constructorCall.release());
                    boundConstructionStatement->SetVariable(variable);
                }
                functionDefinitionSymbol->AddLocalVariable(variable);
                if (!boundStatement)
                {
                    boundStatement = boundConstructionStatement;
                }
                else
                {
                    if (boundStatement->IsBoundConstructionStatementNode())
                    {
                        BoundCompoundStatementNode* compoundStatement = new BoundCompoundStatementNode(node.GetSourcePos());
                        compoundStatement->AddStatement(boundStatement);
                        boundStatement = compoundStatement;
                    }
                    else if (boundStatement->IsBoundCompoundStatementNode())
                    {
                        BoundCompoundStatementNode* compoundStatement = static_cast<BoundCompoundStatementNode*>(boundStatement);
                        compoundStatement->AddStatement(boundConstructionStatement);
                    }
                    else
                    {
                        ThrowException("bound construction statement or bound compound statement expected", node.GetSourcePos(), context);
                    }
                }
            }
        }
        if (setStatement)
        {
            SetStatement(boundStatement);
        }
    }
}

void StatementBinder::SetStatement(BoundStatementNode* statement)
{
    if (postfix)
    {
        statement->SetPostfix();
    }
    if (boundStatement)
    {
        if (boundStatement->Postfix())
        {
            BoundSequenceStatementNode* sequenceStatement = new BoundSequenceStatementNode(statement->GetSourcePos(), statement, boundStatement);
            sequenceStatement->SetSource(statement->Source()->Clone());
            statement = sequenceStatement;
        }
        else
        {
            BoundSequenceStatementNode* sequenceStatement = new BoundSequenceStatementNode(statement->GetSourcePos(), boundStatement, statement);
            sequenceStatement->SetSource(statement->Source()->Clone());
            statement = sequenceStatement;
        }
        if (postfix)
        {
            statement->SetPostfix();
        }
    }
    boundStatement = statement;
}

struct FunctionStaticDeclarationExtractor : public otava::ast::DefaultVisitor
{
    FunctionStaticDeclarationExtractor(const soul::ast::SourcePos& sourcePos_, otava::ast::IdentifierNode* globalVarId_, bool isArrayVar_);
    void Visit(otava::ast::SimpleDeclarationNode& node) override;
    void Visit(otava::ast::DeclSpecifierSequenceNode& node) override;
    void Visit(otava::ast::InitDeclaratorListNode& node) override;
    void Visit(otava::ast::InitDeclaratorNode& node) override;
    void Visit(otava::ast::PtrDeclaratorNode& node) override;
    void Visit(otava::ast::PtrNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::ArrayDeclaratorNode& node) override;
    soul::ast::SourcePos sourcePos;
    otava::ast::IdentifierNode* globalVarId;
    otava::ast::DeclSpecifierSequenceNode* declSpecifiers;
    otava::ast::InitDeclaratorListNode* initDeclarators;
    otava::ast::PtrDeclaratorNode* ptrDeclaratorNode;
    otava::ast::Node* declaratorNode;
    bool isArrayVar;
};

FunctionStaticDeclarationExtractor::FunctionStaticDeclarationExtractor(const soul::ast::SourcePos& sourcePos_, otava::ast::IdentifierNode* globalVarId_, bool isArrayVar_) :
    sourcePos(sourcePos_), globalVarId(globalVarId_), ptrDeclaratorNode(nullptr), declaratorNode(nullptr), isArrayVar(isArrayVar_)
{
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::SimpleDeclarationNode& node)
{
    declSpecifiers = new otava::ast::DeclSpecifierSequenceNode(node.GetSourcePos());
    initDeclarators = new otava::ast::InitDeclaratorListNode(node.GetSourcePos());
    node.DeclarationSpecifiers()->Accept(*this);
    node.InitDeclaratorList()->Accept(*this);
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::DeclSpecifierSequenceNode& node)
{
    for (const auto& declSpecifierNode : node.Nodes())
    {
        if (declSpecifierNode->IsStaticNode())
        {
            continue;
        }
        declSpecifiers->AddNode(declSpecifierNode->Clone());
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::PtrNode& node)
{
    if (ptrDeclaratorNode)
    {
        ptrDeclaratorNode->AddNode(node.Clone());
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::IdentifierNode& node)
{
    if (ptrDeclaratorNode)
    {
        ptrDeclaratorNode->AddNode(globalVarId->Clone());
    }
    else
    {
        declaratorNode = globalVarId->Clone();
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::QualifiedIdNode& node)
{
    if (ptrDeclaratorNode)
    {
        ptrDeclaratorNode->AddNode(globalVarId->Clone());
    }
    else
    {
        declaratorNode = globalVarId->Clone();
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::PtrDeclaratorNode& node)
{
    ptrDeclaratorNode = new otava::ast::PtrDeclaratorNode(sourcePos);
    for (const auto& node : node.Nodes())
    {
        node->Accept(*this);
    }
    initDeclarators->AddNode(ptrDeclaratorNode);
    ptrDeclaratorNode = nullptr;
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::ArrayDeclaratorNode& node)
{
    node.Child()->Accept(*this);
    otava::ast::Node* dimension = nullptr;
    if (node.Dimension())
    {
        dimension = node.Dimension()->Clone();
    }
    declaratorNode = new otava::ast::ArrayDeclaratorNode(sourcePos, declaratorNode, dimension, sourcePos, sourcePos);
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::InitDeclaratorNode& node)
{
    node.Left()->Accept(*this);
    if (isArrayVar)
    {
        declaratorNode = new otava::ast::InitDeclaratorNode(sourcePos, declaratorNode, node.Right()->Clone());
    }
    if (declaratorNode)
    {
        initDeclarators->AddNode(declaratorNode);
        declaratorNode = nullptr;
    }
}

void FunctionStaticDeclarationExtractor::Visit(otava::ast::InitDeclaratorListNode& node)
{
    for (const auto& declNode : node.Nodes())
    {
        declNode->Accept(*this);
        if (declaratorNode)
        {
            initDeclarators->AddNode(declaratorNode);
            declaratorNode = nullptr;
        }
    }
}

void StatementBinder::Visit(otava::ast::BoundStatementNode& node)
{
    SetStatement(static_cast<BoundStatementNode*>(node.GetBoundStatementNode()));
}

void StatementBinder::Visit(otava::ast::GotoStatementNode& node)
{
    functionDefinitionSymbol->SetContainsGotosOrLabels();
    BoundGotoStatementNode* gotoStatement = new BoundGotoStatementNode(node.GetSourcePos(), node.Target()->Str());
    SetStatement(gotoStatement);
}

void StatementBinder::Visit(otava::ast::LabeledStatementNode& node)
{
    functionDefinitionSymbol->SetContainsGotosOrLabels();
    BoundStatementNode* statement = BindStatement(node.Statement(), functionDefinitionSymbol, context);;
    BoundLabeledStatementNode* labeledStatement = new BoundLabeledStatementNode(node.GetSourcePos(), node.Label()->Str(), statement);
    SetStatement(labeledStatement);
}

void StatementBinder::BindStaticLocalVariable(VariableSymbol* variable, otava::ast::Node* initializerNode, 
    otava::ast::SimpleDeclarationNode* declarationNode)
{
    /*
        std::atomic_bool variable_initialized;
        if (!variable_initialized)
        {
            std::lock_guard<std::recursive_mutex> lock(std::get_init_lock());
            if (!variable_initialized)
            {
                type variable(initializer);
                variable_initialized = true;
            }
        }
    */
    functionDefinitionSymbol->SetContainsStatics();
    bool isArrayVar = variable->GetDeclaredType()->IsArrayTypeSymbol();
    soul::ast::SourcePos sourcePos = declarationNode->GetSourcePos();
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    std::string shaMaterial = util::ToUtf8(functionDefinitionSymbol->FullName());
    if (!functionDefinitionSymbol->Specialization().empty())
    {
        for (TypeSymbol* type : functionDefinitionSymbol->Specialization())
        {
            shaMaterial.append(".").append(util::ToUtf8(type->FullName()));
        }
    }
    shaMaterial.append(".").append(context->GetBoundCompileUnit()->Id()).
        append(1, '_').append(std::to_string(context->GetBoundFunction()->Serial()));
    std::string sha = util::GetSha1MessageDigest(shaMaterial);
    otava::ast::Node* atomicBoolType = MakeTypeNameNodes(sourcePos, U"std::atomic_bool");
    otava::ast::DeclSpecifierSequenceNode* declSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    declSpecifiers->AddNode(atomicBoolType);
    otava::ast::InitDeclaratorListNode* initDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
    std::unique_ptr<otava::ast::IdentifierNode> initializedVarName(new otava::ast::IdentifierNode(sourcePos, variable->Name() + U"_initialized_" + util::ToUtf32(sha)));
    initDeclarators->AddNode(initializedVarName->Clone());
    std::unique_ptr<otava::ast::SimpleDeclarationNode> initializedVarDeclaration(new otava::ast::SimpleDeclarationNode(
        sourcePos, declSpecifiers, initDeclarators, nullptr, nullptr));
    context->GetSymbolTable()->BeginScope(context->GetSymbolTable()->GlobalNs()->GetScope());
    ProcessSimpleDeclaration(initializedVarDeclaration.get(), nullptr, context);
    std::u32string globalStaticVarName = variable->Name() + U"_global_" + util::ToUtf32(sha);
    std::unique_ptr<otava::ast::IdentifierNode> globalStaticVarId(new otava::ast::IdentifierNode(sourcePos, globalStaticVarName));
    FunctionStaticDeclarationExtractor extractor(sourcePos, globalStaticVarId.get(), isArrayVar);
    declarationNode->Accept(extractor);
    otava::ast::DeclSpecifierSequenceNode* globalStaticDeclSpecifiers = extractor.declSpecifiers;
    otava::ast::InitDeclaratorListNode* globalStaticInitDeclarators = extractor.initDeclarators;
    context->PushSetFlag(ContextFlags::noDynamicInit);
    std::unique_ptr<otava::ast::SimpleDeclarationNode> globalStaticVarDeclaration(new otava::ast::SimpleDeclarationNode(sourcePos,
        globalStaticDeclSpecifiers, globalStaticInitDeclarators, nullptr, nullptr));
    if (isArrayVar)
    {
        context->SetDeclaredInitializerType(variable->GetDeclaredType());
    }
    ProcessSimpleDeclaration(globalStaticVarDeclaration.get(), nullptr, context);
    context->PopFlags();
    context->GetSymbolTable()->EndScope();
    std::unique_ptr<otava::ast::CompoundStatementNode> compound1;
    std::unique_ptr<otava::ast::UnaryExprNode> inititalizedCond;
    std::unique_ptr<otava::ast::CompoundStatementNode> compound2;
    if (!isArrayVar)
    {
        compound1.reset(new otava::ast::CompoundStatementNode(sourcePos));
        compound1->SetBlockId(context->NextBlockId());
        otava::ast::TemplateIdNode* lockGuardType = new otava::ast::TemplateIdNode(sourcePos, MakeTypeNameNodes(sourcePos, U"std::lock_guard"));
        lockGuardType->AddNode(MakeTypeNameNodes(sourcePos, U"std::recursive_mutex"));
        otava::ast::DeclSpecifierSequenceNode* lockGuardDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
        lockGuardDeclSpecifiers->AddNode(lockGuardType);
        otava::ast::InitDeclaratorListNode* lockGuardInitDeclarators = new otava::ast::InitDeclaratorListNode(sourcePos);
        otava::ast::Node* getInitLock = MakeTypeNameNodes(sourcePos, U"std::get_init_lock");
        otava::ast::InvokeExprNode* lockInit(new otava::ast::InvokeExprNode(sourcePos, getInitLock));
        otava::ast::InitDeclaratorNode* lockGuardInitDeclarator = new otava::ast::InitDeclaratorNode(
            sourcePos, new otava::ast::IdentifierNode(sourcePos, U"lock"), lockInit);
        lockGuardInitDeclarators->AddNode(lockGuardInitDeclarator);
        std::unique_ptr<otava::ast::SimpleDeclarationNode> lockGuardDeclaration(new otava::ast::SimpleDeclarationNode(
            sourcePos, lockGuardDeclSpecifiers, lockGuardInitDeclarators, nullptr, nullptr));
        otava::ast::DeclarationStatementNode* lockGuardDeclarationStmt = new otava::ast::DeclarationStatementNode(sourcePos, lockGuardDeclaration.release());
        compound1->AddNode(lockGuardDeclarationStmt);
        inititalizedCond.reset(new otava::ast::UnaryExprNode(sourcePos, new otava::ast::NotNode(sourcePos), initializedVarName->Clone()));
        compound2.reset(new otava::ast::CompoundStatementNode(sourcePos));
        compound2->SetBlockId(context->NextBlockId());
    }
    globalStaticVariableSymbol = nullptr;
    Symbol* symbol = context->GetSymbolTable()->Lookup(globalStaticVarName, SymbolGroupKind::variableSymbolGroup, sourcePos, context);
    if (symbol && symbol->IsVariableSymbol())
    {
        globalStaticVariableSymbol = static_cast<VariableSymbol*>(symbol);
    }
    else if (symbol && symbol->IsVariableGroupSymbol())
    {
        std::string irName = util::ToUtf8(globalStaticVarName);
        ThrowException("ir name '" + irName + "' of function static global variable not unique", sourcePos, context);
    }
    else
    {
        ThrowException("function static global not found", sourcePos, context);
    }
    if (!isArrayVar)
    {
        BoundVariableNode* boundVariable = new BoundVariableNode(globalStaticVariableSymbol, sourcePos);
        std::vector<std::unique_ptr<BoundExpressionNode>> arguments;
        arguments.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariable, sourcePos, boundVariable->GetType()->AddPointer(context))));
        BoundExpressionNode* initializer = nullptr;
        if (initializerNode)
        {
            initializer = BindExpression(initializerNode, context);
        }
        if (initializer)
        {
            if (initializer->IsBoundExpressionListNode())
            {
                BoundExpressionListNode* exprListNode = static_cast<BoundExpressionListNode*>(initializer);
                int n = exprListNode->Count();
                for (int i = 0; i < n; ++i)
                {
                    arguments.push_back(std::unique_ptr<BoundExpressionNode>(exprListNode->ReleaseExpr(i)));
                }
            }
            else
            {
                arguments.push_back(std::unique_ptr<BoundExpressionNode>(initializer));
            }
        }
        std::vector<TypeSymbol*> templateArgs;
        std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, arguments,
            sourcePos, context);
        constructFunctionStaticStatement.reset(new BoundExpressionStatementNode(sourcePos));
        constructFunctionStaticStatement->SetExpr(constructorCall.release(), sourcePos, context);
        otava::ast::BoundStatementNode* boundStatement = new otava::ast::BoundStatementNode(constructFunctionStaticStatement.release(), sourcePos);
        compound2->AddNode(boundStatement);
        std::unique_ptr<BoundFunctionCallNode> atExitCall = MakeAtExitForVariable(globalStaticVariableSymbol, sourcePos, context);
        if (atExitCall)
        {
            atExitStatement.reset(new BoundExpressionStatementNode(sourcePos));
            atExitStatement->SetExpr(atExitCall.release(), sourcePos, context);
            otava::ast::BoundStatementNode* boundStatement = new otava::ast::BoundStatementNode(atExitStatement.release(), sourcePos);
            compound2->AddNode(boundStatement);
        }
        otava::ast::BinaryExprNode* setInitializedToTrueExpr = new otava::ast::BinaryExprNode(sourcePos, new otava::ast::AssignNode(sourcePos), initializedVarName->Clone(),
            new otava::ast::BooleanLiteralNode(sourcePos, true, U"true"));
        std::unique_ptr<otava::ast::ExpressionStatementNode> setInitializedToTrueStmt(new otava::ast::ExpressionStatementNode(
            sourcePos, setInitializedToTrueExpr, nullptr, nullptr));
        compound2->AddNode(setInitializedToTrueStmt.release());
        std::unique_ptr<otava::ast::IfStatementNode> innerIf(new otava::ast::IfStatementNode(
            sourcePos, inititalizedCond->Clone(), compound2.release(), nullptr, nullptr, sourcePos, sourcePos, sourcePos, sourcePos, sourcePos));
        compound1->AddNode(innerIf.release());
        std::unique_ptr<otava::ast::IfStatementNode> ifStmt(new otava::ast::IfStatementNode(
            sourcePos, inititalizedCond->Clone(), compound1.release(), nullptr, nullptr, sourcePos, sourcePos, sourcePos, sourcePos, sourcePos));
        InstantiationScope instantiationScope(context->GetSymbolTable()->CurrentScope());
        Instantiator instantiator(context, &instantiationScope);
        context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
        ifStmt->Accept(instantiator);
        context->PopFlags();
        context->PushSetFlag(ContextFlags::skipInvokeChecking);
        BoundStatementNode* boundIfStmt = BindStatement(ifStmt.get(), functionDefinitionSymbol, context);
        context->PopFlags();
        SetStatement(boundIfStmt);
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    }
    context->SetDeclaredInitializerType(nullptr);
    variable->SetGlobal(globalStaticVariableSymbol);
}

/*
BoundStatementNode* BindStatement(otava::ast::Node* statementNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    StatementBinder binder(context, functionDefinitionSymbol);
    statementNode->Accept(binder);
    BoundStatementNode* boundStatement = binder.GetBoundStatement();
    if (boundStatement)
    {
        bool fnDefIsNoExcept = false;
        bool fnDefContainsGotosOrLabels = false;
        bool fnDefContainsStatics = false;
        if (functionDefinitionSymbol)
        {
            fnDefIsNoExcept = functionDefinitionSymbol->IsNoExcept();
            fnDefContainsGotosOrLabels = functionDefinitionSymbol->ContainsGotosOrLabels();
            fnDefContainsStatics = functionDefinitionSymbol->ContainsStatics();
        }
        if (!context->GetFlag(ContextFlags::skipInvokeChecking) && !context->GetFlag(ContextFlags::expected) &&
            functionDefinitionSymbol && !fnDefIsNoExcept && !context->GetCleanup().IsEmpty() && boundStatement->MayThrow() &&
            boundStatement->Source() && !fnDefContainsGotosOrLabels && !fnDefContainsStatics)
        {
            boundStatement = GenerateInvoke(functionDefinitionSymbol, context);
        }
    }
    return boundStatement;
}
*/

BoundStatementNode* BindStatement(otava::ast::Node* statementNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    StatementBinder binder(context, functionDefinitionSymbol);
    statementNode->Accept(binder);
    BoundStatementNode* boundStatement = binder.GetBoundStatement();
    if (!boundStatement->Source())
    {
        functionDefinitionSymbol->SetContainsNodeWithNoSource();
    }
    return boundStatement;
}

FunctionDefinitionSymbol* BindFunction(otava::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    TraceInfo* traceInfo = context->GetTraceInfo();
    if (traceInfo)
    {
        int64_t sourceFileId = traceInfo->GetSourceFileId(context->GetModule()->FilePath());
        if (sourceFileId != -1)
        {
            traceInfo->AddFunctionTraceInfo(sourceFileId, context->GetModule()->Id(), util::ToUtf8(functionDefinitionSymbol->FullName()));
        }
        else
        {
            SetExceptionThrown();
            throw std::runtime_error("source file id for source file '" + context->GetModule()->FilePath() + "' not set");
        }
    }
    if (!functionDefinitionSymbol->IsSpecialization())
    {
        if (functionDefinitionSymbol->Declaration())
        {
            functionDefinitionSymbol->Declaration()->SetFlag(FunctionSymbolFlags::fixedIrName);
        }
        functionDefinitionSymbol->SetFlag(FunctionSymbolFlags::fixedIrName);
    }
    RemoveTemporaryAliasTypeSymbols(context);
    if (functionDefinitionSymbol->IsBound()) return functionDefinitionSymbol;
    if (functionDefinitionSymbol->IsTemplate()) return functionDefinitionSymbol;
    if (context->GetFlag(ContextFlags::parseMemberFunction)) return functionDefinitionSymbol;
    std::set<const Symbol*> visited;
    if (functionDefinitionSymbol->IsTemplateParameterInstantiation(context, visited)) return functionDefinitionSymbol;
#ifdef DEBUG_FUNCTIONS
    std::cout << ">" << util::ToUtf8(functionDefinitionSymbol->FullName()) << "\n";
#endif
    if (functionDefinitionSymbol->IrName(context) == "fn_try_0_compile_unit_D65284C9CDC628A9B1D36320FC2BA40D03C00832_562B5C9B6130E1E57E5DBBEEA358301B8463118A")
    {
        int x = 0;
    }
    functionDefinitionSymbol->SetBound();
    StatementBinder binder(context, functionDefinitionSymbol);
    context->PushStatementBinder(&binder);
    GenerateEnterFunctionCode(functionDefinitionNode, functionDefinitionSymbol, context);
    functionDefinitionNode->Accept(binder);
    functionDefinitionSymbol = binder.GetFunctionDefinitionSymbol();
    bool hasNoReturnAttribute = false;
    if (functionDefinitionNode->IsFunctionDefinitionNode())
    {
        hasNoReturnAttribute = HasNoReturnAttribute(static_cast<otava::ast::FunctionDefinitionNode*>(functionDefinitionNode)->Attributes());
    }
    if (functionDefinitionSymbol->ReturnType() && 
        !functionDefinitionSymbol->ReturnType()->IsVoidType() && 
        functionDefinitionSymbol->GroupName() != U"main" && 
        functionDefinitionSymbol->GroupName() != U"@destructor" && 
        !hasNoReturnAttribute)
    {
        CheckFunctionReturnPaths(functionDefinitionNode, context);
    }
    bool skipInvokeChecking = functionDefinitionSymbol->SkipInvokeChecking();
    bool containsStatics = functionDefinitionSymbol->ContainsStatics();
    bool containsNodeWithNoSource = functionDefinitionSymbol->ContainsNodeWithNoSource();
    if (!functionDefinitionSymbol->IsNoExcept() && !skipInvokeChecking && functionDefinitionSymbol->ContainsLocalVariableWithDestructor() &&
        !containsStatics && !containsNodeWithNoSource)
    {
        context->GetSymbolTable()->BeginScopeGeneric(functionDefinitionSymbol->GetScope(), context);
        std::unique_ptr<BoundCompoundStatementNode> newBody = MakeInvokesAndCleanups(functionDefinitionSymbol, context->GetBoundFunction()->Body(), context);
        context->GetBoundFunction()->SetBody(newBody.release());
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
#ifdef DEBUG_FUNCTIONS
    std::cout << "<" << util::ToUtf8(functionDefinitionSymbol->FullName()) << "\n";
#endif
    context->PopStatementBinder();
    return functionDefinitionSymbol;
}

} // namespace otava::symbols
