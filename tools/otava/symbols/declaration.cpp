// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.declaration;

import otava.symbols.context;
import otava.symbols.declarator;
import otava.symbols.evaluator;
import otava.symbols.exception;
import otava.symbols.function.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.type.resolver;
import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.bound.tree;
import otava.symbols.statement.binder;
import otava.symbols.classes;
import otava.symbols.alias.type.symbol;
import otava.symbols.templates;
import otava.symbols.variable.symbol;
import otava.symbols.class_templates;
import otava.symbols.array.type.symbol;
import otava.symbols.overload.resolution;
import otava.symbols.modules;
import otava.symbols.conversion.table;
import otava.symbols.expression.binder;
import otava.symbols.type_compare;
import otava.symbols.type.symbol;
import otava.symbols.value;
import otava.ast.error;
import otava.ast.attribute;
import otava.ast.visitor;
import util;

namespace otava::symbols {

class NoreturnAttributeMatcher : public otava::ast::DefaultVisitor
{
public:
    NoreturnAttributeMatcher();
    void Visit(otava::ast::AttributeNode& node);
    void Visit(otava::ast::IdentifierNode& node);
    bool Value() const { return value; }
private:
    bool matchId;
    bool value;
};

NoreturnAttributeMatcher::NoreturnAttributeMatcher() : matchId(false), value(false)
{
}

void NoreturnAttributeMatcher::Visit(otava::ast::AttributeNode& node)
{
    matchId = true;
    node.AttributeToken()->Accept(*this);
    matchId = false;
}

void NoreturnAttributeMatcher::Visit(otava::ast::IdentifierNode& node)
{
    if (!matchId) return;
    if (node.Str() == U"noreturn")
    {
        value = true;
    }
}

bool HashNoreturnAttribute(otava::ast::Node* attributes)
{
    if (!attributes) return false;
    NoreturnAttributeMatcher noreturnAttributeMatcher;
    attributes->Accept(noreturnAttributeMatcher);
    return noreturnAttributeMatcher.Value();
}

std::string DeclarationFlagStr(DeclarationFlags flags)
{
    std::string str;
    if ((flags & DeclarationFlags::typedefFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("typedef");
    }
    if ((flags & DeclarationFlags::staticFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("static");
    }
    if ((flags & DeclarationFlags::threadLocalFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("thread_local");
    }
    if ((flags & DeclarationFlags::externFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("extern");
    }
    if ((flags & DeclarationFlags::mutableFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("mutable");
    }
    if ((flags & DeclarationFlags::virtualFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("virtual");
    }
    if ((flags & DeclarationFlags::explicitFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("explicit");
    }
    if ((flags & DeclarationFlags::inlineFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("inline");
    }
    if ((flags & DeclarationFlags::friendFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("friend");
    }
    if ((flags & DeclarationFlags::constExprFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("constexpr");
    }
    if ((flags & DeclarationFlags::constEvalFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("consteval");
    }
    if ((flags & DeclarationFlags::constInitFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("constinit");
    }
    return str;
}

class DeclarationProcessor : public otava::ast::DefaultVisitor
{
public:
    DeclarationProcessor(Context* context_);
    std::unique_ptr<DeclarationList> GetDeclarations();
    TypeSymbol* GetType() const { return type; }
    void BeginProcessFunctionDefinition(otava::ast::Node* declSpecifierSeq, otava::ast::Node* declarator);
    void Visit(otava::ast::SimpleDeclarationNode& node) override;
    void Visit(otava::ast::MemberDeclarationNode& node) override;
    void Visit(otava::ast::NoDeclSpecFunctionDeclarationNode& node) override;
    void Visit(otava::ast::FunctionDefinitionNode& node) override;
    void Visit(otava::ast::ParameterNode& node) override;
    void Visit(otava::ast::ExceptionDeclarationNode& node) override;
    void Visit(otava::ast::ClassSpecifierNode& node) override;
    void Visit(otava::ast::EnumSpecifierNode& node) override;
    void Visit(otava::ast::ElaboratedTypeSpecifierNode & override);
    TypeSymbol* ResolveBaseType(otava::ast::Node* node);
    void Visit(otava::ast::CharNode& node) override;
    void Visit(otava::ast::Char8Node& node) override;
    void Visit(otava::ast::Char16Node& node) override;
    void Visit(otava::ast::Char32Node& node) override;
    void Visit(otava::ast::WCharNode& node) override;
    void Visit(otava::ast::BoolNode& node) override;
    void Visit(otava::ast::ShortNode& node) override;
    void Visit(otava::ast::IntNode& node) override;
    void Visit(otava::ast::LongNode& node) override;
    void Visit(otava::ast::SignedNode& node) override;
    void Visit(otava::ast::UnsignedNode& node) override;
    void Visit(otava::ast::FloatNode& node) override;
    void Visit(otava::ast::DoubleNode& node) override;
    void Visit(otava::ast::VoidNode& node) override;
    void Visit(otava::ast::ConstNode& node) override;
    void Visit(otava::ast::VolatileNode& node) override;
    void Visit(otava::ast::PlaceholderTypeSpecifierNode& node) override;

    void Visit(otava::ast::FriendNode& node) override;
    void Visit(otava::ast::TypedefNode& node) override;
    void Visit(otava::ast::ConstExprNode& node) override;
    void Visit(otava::ast::ConstEvalNode& node) override;
    void Visit(otava::ast::ConstInitNode& node) override;
    void Visit(otava::ast::InlineNode& node) override;
    void Visit(otava::ast::StaticNode& node) override;
    void Visit(otava::ast::ThreadLocalNode& node) override;
    void Visit(otava::ast::ExternNode& node) override;
    void Visit(otava::ast::VirtualNode& node) override;
    void Visit(otava::ast::ExplicitNode& node) override;

    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::TemplateIdNode& node) override;

    void Visit(otava::ast::TypenameSpecifierNode& node) override;
private:
    Context* context;
    DeclarationFlags flags;
    bool isClassSpecifier;
    TypeSymbol* type;
    std::unique_ptr<DeclarationList> declarationList;
};

DeclarationProcessor::DeclarationProcessor(Context* context_) : 
    context(context_), flags(DeclarationFlags::none), isClassSpecifier(false), type(nullptr), declarationList(new DeclarationList())
{
}

std::unique_ptr<DeclarationList> DeclarationProcessor::GetDeclarations()
{ 
    return std::move(declarationList);
}

void DeclarationProcessor::BeginProcessFunctionDefinition(otava::ast::Node* declSpecifierSeq, otava::ast::Node* declarator)
{
    if (declSpecifierSeq)
    {
        declSpecifierSeq->Accept(*this);
    }
    TypeSymbol* baseType = ResolveBaseType(declSpecifierSeq);
    Declaration declaration = ProcessDeclarator(baseType, declarator, nullptr, flags, context);
    declarationList->declarations.push_back(std::move(declaration));
}

TypeSymbol* DeclarationProcessor::ResolveBaseType(otava::ast::Node* node)
{
    TypeSymbol* baseType = nullptr;
    DeclarationFlags fundamentalTypeFlags = flags & DeclarationFlags::fundamentalTypeFlags;
    if (fundamentalTypeFlags != DeclarationFlags::none)
    {
        baseType = GetFundamentalType(fundamentalTypeFlags, node->GetSourcePos(), context);
    }
    else 
    {
        while (type && type->IsAliasTypeSymbol())
        {
            AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(type);
            type = aliasType->ReferredType();
        }
        baseType = type;
    }
    return baseType;
}

void DeclarationProcessor::Visit(otava::ast::SimpleDeclarationNode& node)
{
    node.DeclarationSpecifiers()->Accept(*this);
    if (node.InitDeclaratorList())
    {
        TypeSymbol* baseType = ResolveBaseType(&node);
        declarationList = ProcessInitDeclaratorList(baseType, &node, node.InitDeclaratorList(), flags, context);
    }
}

void DeclarationProcessor::Visit(otava::ast::MemberDeclarationNode& node)
{
    if (node.DeclSpecifiers())
    {
        node.DeclSpecifiers()->Accept(*this);
    }
    if (node.MemberDeclarators())
    {
        TypeSymbol* baseType = ResolveBaseType(&node);
        declarationList = ProcessMemberDeclaratorList(baseType, &node, node.MemberDeclarators(), flags, context);
    }
}

void DeclarationProcessor::Visit(otava::ast::NoDeclSpecFunctionDeclarationNode& node)
{
    declarationList->declarations.push_back(ProcessDeclarator(nullptr, &node, &node, flags, context));
}

void DeclarationProcessor::Visit(otava::ast::FunctionDefinitionNode& node)
{
    if (node.DeclSpecifiers())
    {
        node.DeclSpecifiers()->Accept(*this);
    }
    TypeSymbol* baseType = ResolveBaseType(&node);
    if (!baseType)
    {
        return;
    }
    while (baseType->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(baseType);
        baseType = aliasType->ReferredType();
    }
    Declaration declaration = ProcessDeclarator(baseType, node.Declarator(), &node, flags, context);
    if (node.FunctionBody() && node.FunctionBody()->Kind() == otava::ast::NodeKind::defaultedOrDeletedFunctionNode)
    {
        if (declaration.declarator->IsFunctionDeclarator())
        {
            FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declaration.declarator.get());
            otava::ast::DefaultedOrDeletedFunctionNode* ddNode = static_cast<otava::ast::DefaultedOrDeletedFunctionNode*>(node.FunctionBody());
            switch (ddNode->DefaultOrDelete()->Kind())
            {
                case otava::ast::NodeKind::defaultNode:
                {
                    functionDeclarator->AddQualifier(FunctionQualifiers::isDefault);
                    break;
                }
                case otava::ast::NodeKind::deleteNode:
                {
                    functionDeclarator->AddQualifier(FunctionQualifiers::isDeleted);
                    break;
                }
            }
        }
    }
    declarationList->declarations.push_back(std::move(declaration));
}

void DeclarationProcessor::Visit(otava::ast::ParameterNode& node)
{
    node.DeclSpecifiers()->Accept(*this);
    TypeSymbol* baseType = ResolveBaseType(&node);
    Declaration declaration = ProcessDeclarator(baseType, node.Declarator(), &node, flags, context);
    if (node.Initializer())
    {
        declaration.value = Evaluate(node.Initializer(), context);
        declaration.initializer = node.Initializer();
    }
    declarationList->declarations.push_back(std::move(declaration));
}

void DeclarationProcessor::Visit(otava::ast::ExceptionDeclarationNode& node)
{
    if (node.Ellipsis())
    {
        Declaration emptyDeclaration;
        declarationList->declarations.push_back(std::move(emptyDeclaration));
    }
    else
    {
        node.TypeSpecifiers()->Accept(*this);
        TypeSymbol* baseType = ResolveBaseType(&node);
        Declaration declaration = ProcessDeclarator(baseType, node.Declarator(), &node, flags, context);
        declarationList->declarations.push_back(std::move(declaration));
    }
}

void DeclarationProcessor::Visit(otava::ast::ClassSpecifierNode& node)
{
}

void DeclarationProcessor::Visit(otava::ast::EnumSpecifierNode& node)
{
}

void DeclarationProcessor::Visit(otava::ast::ElaboratedTypeSpecifierNode& node)
{
    type = ResolveType(node.Id(), DeclarationFlags::none, context);
}

void DeclarationProcessor::Visit(otava::ast::CharNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::charFlag, "char", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::charFlag;
}

void DeclarationProcessor::Visit(otava::ast::Char8Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char8Flag, "char8_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char8Flag;
}

void DeclarationProcessor::Visit(otava::ast::Char16Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char16Flag, "char16_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char16Flag;
}

void DeclarationProcessor::Visit(otava::ast::Char32Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char32Flag, "char32_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char32Flag;
}

void DeclarationProcessor::Visit(otava::ast::WCharNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "wchar_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::wcharFlag;
}

void DeclarationProcessor::Visit(otava::ast::BoolNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "bool", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::boolFlag;
}

void DeclarationProcessor::Visit(otava::ast::ShortNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::shortFlag, "short", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::shortFlag;
}

void DeclarationProcessor::Visit(otava::ast::IntNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::intFlag, "int", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::intFlag;
}

void DeclarationProcessor::Visit(otava::ast::LongNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::longLongFlag, "long long", node.GetSourcePos(), context);
    if ((flags & DeclarationFlags::longFlag) != DeclarationFlags::none)
    {
        flags = (flags | DeclarationFlags::longLongFlag) & ~DeclarationFlags::longFlag;
    }
    else
    {
        flags = flags | DeclarationFlags::longFlag;
    }
}

void DeclarationProcessor::Visit(otava::ast::SignedNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::signedFlag, "signed", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::signedFlag;
}

void DeclarationProcessor::Visit(otava::ast::UnsignedNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::unsignedFlag, "unsigned", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::unsignedFlag;
}

void DeclarationProcessor::Visit(otava::ast::FloatNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::floatFlag, "float", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::floatFlag;
}

void DeclarationProcessor::Visit(otava::ast::DoubleNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::doubleFlag, "double", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::doubleFlag;
}

void DeclarationProcessor::Visit(otava::ast::VoidNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::voidFlag, "void", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::voidFlag;
}

void DeclarationProcessor::Visit(otava::ast::ConstNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constFlag, "const", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constFlag;
}

void DeclarationProcessor::Visit(otava::ast::VolatileNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::volatileFlag, "volatile", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::volatileFlag;
}

void DeclarationProcessor::Visit(otava::ast::PlaceholderTypeSpecifierNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::autoFlag, "auto", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::autoFlag;
}

void DeclarationProcessor::Visit(otava::ast::FriendNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::friendFlag, "friend", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::friendFlag;
}

void DeclarationProcessor::Visit(otava::ast::TypedefNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::typedefFlag, "typedef", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::typedefFlag;
}

void DeclarationProcessor::Visit(otava::ast::ConstExprNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constExprFlag, "constexpr", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constExprFlag;
}

void DeclarationProcessor::Visit(otava::ast::ConstEvalNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constEvalFlag, "consteval", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constEvalFlag;
}

void DeclarationProcessor::Visit(otava::ast::ConstInitNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constInitFlag, "constinit", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constInitFlag;
}

void DeclarationProcessor::Visit(otava::ast::InlineNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::inlineFlag, "inline", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::inlineFlag;
}

void DeclarationProcessor::Visit(otava::ast::StaticNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::staticFlag, "static", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::staticFlag;
}

void DeclarationProcessor::Visit(otava::ast::ThreadLocalNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::threadLocalFlag, "thread_local", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::threadLocalFlag;
}

void DeclarationProcessor::Visit(otava::ast::ExternNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::externFlag, "extern", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::externFlag;
}

void DeclarationProcessor::Visit(otava::ast::VirtualNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::externFlag, "virtual", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::virtualFlag;
}

void DeclarationProcessor::Visit(otava::ast::ExplicitNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::explicitFlag, "explicit", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::explicitFlag;
}

void DeclarationProcessor::Visit(otava::ast::QualifiedIdNode& node)
{
    type = ResolveType(&node, flags, context);
}

void DeclarationProcessor::Visit(otava::ast::IdentifierNode& node)
{
    type = ResolveType(&node, flags, context);
}

void DeclarationProcessor::Visit(otava::ast::TemplateIdNode& node)
{
    type = ResolveType(&node, flags, context);
}

void DeclarationProcessor::Visit(otava::ast::TypenameSpecifierNode& node)
{
    type = ResolveType(&node, flags, context);
}

VariableSymbol* ProcessSimpleDeclarator(SimpleDeclarator* simpleDeclarator, TypeSymbol* type, Value* value, DeclarationFlags flags, Context* context)
{
    VariableSymbol* variable = context->GetSymbolTable()->AddVariable(simpleDeclarator->Name(), simpleDeclarator->Node(), type, nullptr, value, flags, context);
    return variable;
}

VariableSymbol* ProcessArrayDeclarator(ArrayDeclarator* arrayDeclarator, TypeSymbol* elementType, DeclarationFlags flags, Context* context)
{
    ArrayTypeSymbol* arrayTypeSymbol = context->GetSymbolTable()->MakeArrayType(elementType, arrayDeclarator->Size());
    arrayTypeSymbol->Bind(arrayDeclarator->Node()->GetSourcePos(), context);
    VariableSymbol* variable = context->GetSymbolTable()->AddVariable(arrayDeclarator->Name(), arrayDeclarator->Node(), arrayTypeSymbol, nullptr, nullptr, flags, context);
    return variable;
}

void ProcessFunctionDeclarator(FunctionDeclarator* functionDeclarator, TypeSymbol* type, DeclarationFlags flags, Context* context)
{
    FunctionSymbol* functionSymbol = context->GetSymbolTable()->AddFunction(
        functionDeclarator->Name(),
        functionDeclarator->TemplateArgs(),
        functionDeclarator->Node(),
        functionDeclarator->GetFunctionKind(),
        functionDeclarator->GetFunctionQualifiers(),
        flags,
        context);
    context->SetSpecialization(functionSymbol);
    TypeSymbol* returnType = MapType(functionSymbol, type, context);
    functionSymbol->SetReturnType(returnType, context);
    for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
    {
        soul::ast::SourcePos sourcePos;
        std::u32string name;
        otava::ast::Node* node = nullptr;
        if (parameterDeclaration.declarator)
        {
            name = parameterDeclaration.declarator->Name();
            node = parameterDeclaration.declarator->Node();
            sourcePos = parameterDeclaration.declarator->Node()->GetSourcePos();
        }
        TypeSymbol* parameterType = MapType(functionSymbol, parameterDeclaration.type, context);
        ParameterSymbol* parameter = context->GetSymbolTable()->CreateParameter(name, node, parameterType, context);
        if (parameterDeclaration.initializer)
        {
            parameter->SetDefaultValue(parameterDeclaration.initializer);
        }
        functionSymbol->AddParameter(parameter, sourcePos, context);
    }
    ClassTypeSymbol* classType = functionSymbol->ParentClassType();
    if (classType)
    {
        int32_t functionIndex = 0;
        SpecialFunctionKind specialFunctionKind = functionSymbol->GetSpecialFunctionKind(context);
        if (specialFunctionKind != SpecialFunctionKind::none)
        {
            functionIndex = GetSpecialFunctionIndex(specialFunctionKind);
            if (specialFunctionKind == SpecialFunctionKind::dtor)
            {
                classType->SetHasUserDefinedDestructor();
            }
        }
        else
        {
            functionIndex = classType->NextFunctionIndex();
        }
        functionSymbol->SetIndex(functionIndex);
        classType->MapFunction(functionSymbol);
        context->GetSymbolTable()->MapFunction(functionSymbol);
    }
    AddConvertingConstructorToConversionTable(functionSymbol, functionDeclarator->Node()->GetSourcePos(), context);
}

void ProcessSimpleDeclaration(otava::ast::Node* node, Context* context)
{
    if (context->GetFlag(ContextFlags::linkageDeclaration)) return;
    DeclarationProcessor processor(context);
    node->Accept(processor);
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    for (auto& declaration : declarationList->declarations)
    {
        Declarator* declarator = declaration.declarator.get();
        switch (declarator->Kind())
        {
            case DeclaratorKind::simpleDeclarator:
            {
                SimpleDeclarator* simpleDeclarator = static_cast<SimpleDeclarator*>(declarator);
                if (!simpleDeclarator->Name().empty())
                {
                    VariableSymbol* variable = ProcessSimpleDeclarator(simpleDeclarator, declaration.type, declaration.value, declaration.flags, context);
                    if (variable->IsGlobalVariable())
                    {
                        std::unique_ptr<BoundExpressionNode> variableInitializer(nullptr);
                        if (declaration.initializer)
                        {
                            variableInitializer.reset(BindExpression(declaration.initializer, context));
                        }
                        if (!variable->IsExtern())
                        {
                            context->GetBoundCompileUnit()->AddBoundNode(new BoundGlobalVariableDefinitionNode(variable, node->GetSourcePos()), context);
                            GenerateDynamicInitialization(variable, variableInitializer.get(), node->GetSourcePos(), context);
                        }
                    }
                    declaration.variable = variable;
                }
                break;
            }
            case DeclaratorKind::functionDeclarator:
            {
                FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declarator);
                ProcessFunctionDeclarator(functionDeclarator, declaration.type, declaration.flags, context);
                break;
            }
            case DeclaratorKind::arrayDeclarator:
            {
                ArrayDeclarator* arrayDeclarator = static_cast<ArrayDeclarator*>(declarator);
                VariableSymbol* variable = ProcessArrayDeclarator(arrayDeclarator, declaration.type, declaration.flags, context);
                if (declaration.value)
                {
                    variable->SetValue(declaration.value);
                    variable->SetDeclaredType(declaration.value->GetType());
                }
                if (variable->IsGlobalVariable())
                {
                    context->GetBoundCompileUnit()->AddBoundNode(new BoundGlobalVariableDefinitionNode(variable, node->GetSourcePos()), context);
                }
                declaration.variable = variable;
                break;
            }
        }
    }
    if (context->GetFlag(ContextFlags::saveDeclarations))
    {
        context->SetDeclarationList(node, declarationList.release());
    }
}

Declaration ProcessParameterDeclaration(otava::ast::Node* node, Context* context)
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    if (declarationList->declarations.size() == 1)
    {
        return std::move(declarationList->declarations.front());
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.declaration: single declaration expected");
    }
}

Declaration ProcessExceptionDeclaration(otava::ast::Node* node, Context* context)
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    if (declarationList->declarations.size() == 1)
    {
        return std::move(declarationList->declarations.front());
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.declaration: single declaration expected");
    }
}

void ProcessMemberDeclaration(otava::ast::Node* node, Context* context)
{
    ProcessSimpleDeclaration(node, context);
}

Declaration ProcessFunctionDeclaration(otava::ast::Node* node, Context* context) 
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    if (declarationList->declarations.size() == 1)
    {
        return std::move(declarationList->declarations.front());
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.declaration: single declaration expected");
    }
}

int BeginFunctionDefinition(otava::ast::Node* declSpecifierSequence, otava::ast::Node* declarator, Context* context)
{   
    int scopes = 0;
    if (!context->GetFlag(ContextFlags::instantiateFunctionTemplate) && !context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate))
    {
        context->GetSymbolTable()->CurrentScope()->PopParentScope();
    }
    DeclarationProcessor processor(context);
    processor.BeginProcessFunctionDefinition(declSpecifierSequence, declarator);
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    if (declarationList->declarations.size() == 1)
    {
        Declaration declaration = std::move(declarationList->declarations.front());
        if (declaration.declarator->Kind() == DeclaratorKind::functionDeclarator)
        {
            FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declaration.declarator.get());
            FunctionQualifiers qualifiers = functionDeclarator->GetFunctionQualifiers();
            FunctionKind kind = functionDeclarator->GetFunctionKind();
            std::vector<TypeSymbol*> parameterTypes;
            for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
            {
                parameterTypes.push_back(parameterDeclaration.type);
            }
            FunctionDefinitionSymbol* definition = context->GetSymbolTable()->AddFunctionDefinition(functionDeclarator->GetScope(), functionDeclarator->Name(),
                functionDeclarator->TemplateArgs(), parameterTypes, qualifiers, kind, declaration.flags, declarator, context);
            if (context->GetFlag(ContextFlags::instantiateFunctionTemplate) || 
                context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate) || 
                context->GetFlag(ContextFlags::generateMainWrapper))
            {
                context->SetSpecialization(definition);
            }
            int parameterIndex = 0;
            for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
            {
                soul::ast::SourcePos sourcePos;
                std::u32string name;
                otava::ast::Node* node = nullptr;
                if (parameterDeclaration.declarator)
                {
                    name = parameterDeclaration.declarator->Name();
                    node = parameterDeclaration.declarator->Node();
                    sourcePos = parameterDeclaration.declarator->Node()->GetSourcePos();
                }
                TypeSymbol* parameterType = MapType(definition, parameterDeclaration.type, context);
                ParameterSymbol* parameter = context->GetSymbolTable()->CreateParameter(name, node, parameterType, context);
                if (parameterDeclaration.initializer)
                {
                    parameter->SetDefaultValue(parameterDeclaration.initializer);
                }
                FunctionSymbol* declaration = definition->Declaration();
                if (declaration)
                {
                    if (parameterIndex >= 0 && parameterIndex < declaration->Parameters().size())
                    {
                        ParameterSymbol* declarationParam = declaration->Parameters()[parameterIndex];
                        if (declarationParam->DefaultValue() && !parameter->DefaultValue())
                        {
                            parameter->SetDefaultValue(declarationParam->DefaultValue());
                        }
                    }
                }
                definition->AddParameter(parameter, sourcePos, context);
                ++parameterIndex;
            }
            definition->AddDefinitionToGroup(context);
            TypeSymbol* returnType = MapType(definition, declaration.type, context);
            definition->SetReturnType(returnType, context);
            context->GetSymbolTable()->BeginScopeGeneric(definition->GetScope(), context);
            if (!context->GetFlag(ContextFlags::instantiateFunctionTemplate) && !context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate))
            {
                definition->GetScope()->AddParentScope(functionDeclarator->GetScope());
            }
            ++scopes;
            BoundFunctionNode* boundFunctionNode = new BoundFunctionNode(definition, declarator->GetSourcePos());
            context->PushBoundFunction(boundFunctionNode);
        }
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.declaration: single declaration expected");
    }
    return scopes;
}

void EndFunctionDefinition(otava::ast::Node* node, int scopes, Context* context)
{
    if (node->IsFunctionDefinitionNode())
    {
        otava::ast::FunctionDefinitionNode* functionDefinitionNode = static_cast<otava::ast::FunctionDefinitionNode*>(node);
        FunctionDefinitionSymbol* functionDefinitionSymbol = nullptr;
        Symbol* symbol = context->GetSymbolTable()->CurrentScope()->SymbolScope()->GetSymbol();
        if (symbol && symbol->IsFunctionDefinitionSymbol())
        {
            functionDefinitionSymbol = static_cast<FunctionDefinitionSymbol*>(symbol);
            if (HashNoreturnAttribute(functionDefinitionNode->Attributes()))
            {
                functionDefinitionSymbol->SetFunctionQualifiers(functionDefinitionSymbol->Qualifiers() | FunctionQualifiers::noreturn);
            }
            context->GetSymbolTable()->MapNode(functionDefinitionNode, functionDefinitionSymbol);
            ClassTypeSymbol* classType = functionDefinitionSymbol->ParentClassType();
            if (classType)
            {
                int32_t functionIndex = 0;
                SpecialFunctionKind specialFunctionKind = functionDefinitionSymbol->GetSpecialFunctionKind(context);
                if (specialFunctionKind != SpecialFunctionKind::none)
                {
                    functionIndex = GetSpecialFunctionIndex(specialFunctionKind);
                }
                else
                {
                    functionIndex = classType->NextFunctionIndex();
                }
                functionDefinitionSymbol->SetIndex(functionIndex);
                functionDefinitionNode->SetIndex(functionIndex);
                if (!classType->GetFunction(functionIndex))
                {
                    classType->MapFunction(functionDefinitionSymbol);
                }
                classType->AddMemFunDefSymbol(functionDefinitionSymbol);
                context->GetSymbolTable()->MapFunctionDefinition(functionDefinitionSymbol);
            }
        }
        for (int i = 0; i < scopes; ++i)
        {
            context->GetSymbolTable()->EndScopeGeneric(context); 
        }
        if (!context->GetFlag(ContextFlags::dontBind) && functionDefinitionSymbol)
        {
            BindFunction(functionDefinitionNode, functionDefinitionSymbol, context);
        }
        if (functionDefinitionSymbol && functionDefinitionSymbol->IsTemplate())
        {
            InstantiateEnqueuedRequests(functionDefinitionSymbol, node->GetSourcePos(), context);
        }
    }
    else
    {
        int x = 0;
    }
    if (context->GetBoundFunction())
    {
        if (context->GetBoundFunction()->GetFunctionDefinitionSymbol()->IsBound())
        {
            context->GetBoundCompileUnit()->AddBoundNode(context->ReleaseBoundFunction(), context);
        }
        context->PopBoundFunction();
    }
}

void ProcessMemberFunctionDefinition(otava::ast::Node* node, Context* context)
{
    ProcessSimpleDeclaration(node, context); 
}

void Write(Writer& writer, DeclarationFlags flags)
{
    writer.GetBinaryStreamWriter().Write(static_cast<int32_t>(flags));
}

void Read(Reader& reader, DeclarationFlags& flags)
{
    flags = static_cast<DeclarationFlags>(reader.GetBinaryStreamReader().ReadInt());
}

void ThrowDeclarationParsingError(const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("declaration parsing error", sourcePos, context);
}

class LinkageProcessor : public otava::ast::DefaultVisitor
{
public:
    LinkageProcessor(Context* context_);
    void Visit(otava::ast::LinkageSpecificationNode& node) override;
    void Visit(otava::ast::StringLiteralNode& node) override;
    void Visit(otava::ast::SimpleDeclarationNode& node) override;
private:
    Context* context;
    Linkage linkage;
};

LinkageProcessor::LinkageProcessor(Context* context_) : context(context_), linkage(Linkage::cpp_linkage)
{
}

void LinkageProcessor::Visit(otava::ast::LinkageSpecificationNode& node)
{
    node.Linkage()->Accept(*this);
    context->GetSymbolTable()->PushLinkage(linkage);
    node.Declarations()->Accept(*this);
    context->GetSymbolTable()->PopLinkage();
}

void LinkageProcessor::Visit(otava::ast::StringLiteralNode& node) 
{
    if (node.Value() == U"C")
    {
        linkage = Linkage::c_linkage;
    }
    else if (node.Value() == U"C++")
    {
        linkage = Linkage::cpp_linkage;
    }
    else
    {
        ThrowException("unknown linkage", node.GetSourcePos(), context);
    }
}

void LinkageProcessor::Visit(otava::ast::SimpleDeclarationNode& node)
{
    ProcessSimpleDeclaration(&node, context);
}

void ProcessLinkageSpecification(otava::ast::Node* node, Context* context)
{
    LinkageProcessor linkageProcessor(context);
    node->Accept(linkageProcessor);
}

TypeSymbol* ProcessExplicitInstantiationDeclaration(otava::ast::Node* node, Context* context)
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    return processor.GetType();
}

TypeSymbol* MapType(FunctionSymbol* functionSymbol, TypeSymbol* type, Context* context)
{
    if (type)
    {
        ClassTypeSymbol* parentClassType = functionSymbol->ParentClassType();
        if (parentClassType && parentClassType->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(parentClassType);
            if (type->GetBaseType()->IsClassTypeSymbol())
            {
                if (TypesEqual(type->GetBaseType(), specialization->ClassTemplate()))
                {
                    type = context->GetSymbolTable()->MakeCompoundType(specialization, type->GetDerivations());
                }
            }
        }
    }
    return type;
}

void GenerateDynamicInitialization(VariableSymbol* variable, BoundExpressionNode* initializer, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!variable->GetType()->IsClassTypeSymbol()) return;
    if (context->GetFlag(ContextFlags::noDynamicInit)) return;
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    BoundVariableNode* boundGlobalVariable(new BoundVariableNode(variable, sourcePos));
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundGlobalVariable, sourcePos, variable->GetType()->AddPointer(context))));
    if (initializer)
    {
        if (initializer->IsBoundExpressionListNode())
        {
            BoundExpressionListNode* expressionList = static_cast<BoundExpressionListNode*>(initializer);
            int n = expressionList->Count();
            for (int i = 0; i < n; ++i)
            {
                args.push_back(std::unique_ptr<BoundExpressionNode>(expressionList->ReleaseExpr(i)));
            }
        }
        else
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(initializer->Clone()));
        }
    }
    Exception ex;
    std::vector<TypeSymbol*> templateArgs;
    std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context, ex);
    if (constructorCall)
    {
        std::unique_ptr<BoundFunctionCallNode> atExitCall = MakeAtExitForVariable(variable, sourcePos, context);
        context->GetBoundCompileUnit()->AddDynamicInitialization(constructorCall.release(), atExitCall.release(), sourcePos, context);
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
}

std::unique_ptr<BoundFunctionCallNode> MakeAtExitForVariable(VariableSymbol* variable, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> dtorArgs;
    BoundVariableNode* boundGlobalVariable(new BoundVariableNode(variable, sourcePos));
    dtorArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundGlobalVariable, sourcePos, variable->GetType()->AddPointer(context))));
    Exception ex;
    std::vector<TypeSymbol*> templateArgs;
    std::unique_ptr<BoundFunctionCallNode> destructorCall = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, dtorArgs, sourcePos, context, ex);
    std::unique_ptr<BoundFunctionCallNode> atExitCall;
    if (destructorCall && !destructorCall->GetFunctionSymbol()->IsTrivialDestructor())
    {
        TypeSymbol* voidPtrType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType)->AddPointer(context);
        std::vector<std::unique_ptr<BoundExpressionNode>> atExitArgs;
        atExitArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundFunctionValueNode(destructorCall->GetFunctionSymbol(), sourcePos, voidPtrType)));
        BoundVariableNode* boundGlobalVariable(new BoundVariableNode(variable, sourcePos));
        atExitArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundVariableAsVoidPtrNode(new BoundAddressOfNode(
            boundGlobalVariable, sourcePos, boundGlobalVariable->GetType()->AddPointer(context)), sourcePos, voidPtrType)));
        Exception ex;
        Scope* stdScope = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
        std::vector<TypeSymbol*> templateArgs;
        atExitCall = ResolveOverload(stdScope, U"at_exit", templateArgs, atExitArgs, sourcePos, context, ex);
    }
    return atExitCall;
}

void AddConvertingConstructorToConversionTable(FunctionSymbol* functionSymbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!functionSymbol->IsExplicit() && functionSymbol->GetFunctionKind() == FunctionKind::constructor && functionSymbol->MemFunArity(context) == 2)
    {
        TypeSymbol* conversionParamType = functionSymbol->MemFunParameters(context)[0]->GetType()->RemovePointer(context)->DirectType(context)->FinalType(sourcePos, context);
        TypeSymbol* conversionArgType = functionSymbol->MemFunParameters(context)[1]->GetType()->PlainType(context)->DirectType(context)->FinalType(sourcePos, context);
        if (!TypesEqual(conversionParamType, conversionArgType))
        {
            FunctionSymbol* conversion = context->GetSymbolTable()->GetConversionTable().GetConversion(conversionParamType, conversionArgType, context);
            if (!conversion)
            {
                functionSymbol->SetConversion();
                functionSymbol->SetConversionParamType(conversionParamType);
                functionSymbol->SetConversionArgType(conversionArgType);
                functionSymbol->SetConversionDistance(10);
                context->GetSymbolTable()->GetConversionTable().AddConversion(functionSymbol);
            }
        }
    }
}

} // namespace otava::symbols
