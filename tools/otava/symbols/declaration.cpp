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
import otava.ast.error;
import util;

namespace otava::symbols {

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
    void BeginProcessFunctionDefinition(otava::ast::Node* declSpecifierSeq, otava::ast::Node* declarator);
    void Visit(otava::ast::SimpleDeclarationNode& node) override;
    void Visit(otava::ast::MemberDeclarationNode& node) override;
    void Visit(otava::ast::NoDeclSpecFunctionDeclarationNode& node) override;
    void Visit(otava::ast::FunctionDefinitionNode& node) override;
    void Visit(otava::ast::ParameterNode& node) override;
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
    Declaration declaration = ProcessDeclarator(baseType, declarator, flags, context);
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
        declarationList = ProcessInitDeclaratorList(baseType, node.InitDeclaratorList(), flags, context);
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
        declarationList = ProcessMemberDeclaratorList(baseType, node.MemberDeclarators(), flags, context);
    }
}

void DeclarationProcessor::Visit(otava::ast::NoDeclSpecFunctionDeclarationNode& node)
{
    declarationList->declarations.push_back(ProcessDeclarator(nullptr, &node, flags, context));
}

void DeclarationProcessor::Visit(otava::ast::FunctionDefinitionNode& node)
{
    if (node.DeclSpecifiers())
    {
        node.DeclSpecifiers()->Accept(*this);
    }
    TypeSymbol* baseType = ResolveBaseType(&node);
    Declaration declaration = ProcessDeclarator(baseType, node.Declarator(), flags, context);
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
    Declaration declaration = ProcessDeclarator(baseType, node.Declarator(), flags, context);
    if (node.Initializer())
    {
        declaration.value = Evaluate(node.Initializer(), context);
    }
    declarationList->declarations.push_back(std::move(declaration));
}

void DeclarationProcessor::Visit(otava::ast::ClassSpecifierNode& node)
{
}

void DeclarationProcessor::Visit(otava::ast::EnumSpecifierNode& node)
{
}

void DeclarationProcessor::Visit(otava::ast::ElaboratedTypeSpecifierNode& node)
{
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

void ProcessFunctionDeclarator(FunctionDeclarator* functionDeclarator, TypeSymbol* type, DeclarationFlags flags, Context* context)
{
    FunctionSymbol* functionSymbol = context->GetSymbolTable()->AddFunction(
        functionDeclarator->Name(), 
        functionDeclarator->Node(), 
        functionDeclarator->GetFunctionKind(), 
        functionDeclarator->GetFunctionQualifiers(), 
        flags,
        context);
    functionSymbol->SetReturnType(type);
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
        ParameterSymbol* parameter = context->GetSymbolTable()->CreateParameter(name, node, parameterDeclaration.type, context);
        if (parameterDeclaration.value)
        {
            parameter->SetDefaultValue(parameterDeclaration.value);
        }
        functionSymbol->AddParameter(parameter, sourcePos, context);
    }
}

void ProcessSimpleDeclaration(otava::ast::Node* node, Context* context)
{
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
                VariableSymbol* variable = ProcessSimpleDeclarator(simpleDeclarator, declaration.type, declaration.value, declaration.flags, context);
                declaration.variable = variable;
                break;
            }
            case DeclaratorKind::functionDeclarator:
            {
                FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declarator);
                ProcessFunctionDeclarator(functionDeclarator, declaration.type, declaration.flags, context);
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

void ProcessMemberDeclaration(otava::ast::Node* node, Context* context)
{
    if (node->GetSourcePos().file == 16 && node->GetSourcePos().line == 128)
    {
        int x = 0;
    }
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
    DeclarationProcessor processor(context);
    processor.BeginProcessFunctionDefinition(declSpecifierSequence, declarator);
    context->GetSymbolTable()->CurrentScope()->PopParentScope();
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    if (declarationList->declarations.size() == 1)
    {
        Declaration declaration = std::move(declarationList->declarations.front());
        if (declaration.declarator->Kind() == DeclaratorKind::functionDeclarator)
        {
            FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declaration.declarator.get());
            FunctionQualifiers qualifiers = functionDeclarator->GetFunctionQualifiers();
            Symbol* symbol = context->GetSymbolTable()->Lookup(functionDeclarator->Name(), SymbolGroupKind::functionSymbolGroup, declarator->GetSourcePos(), context, LookupFlags::dontResolveSingle);
            if (symbol)
            {
                if (symbol->IsFunctionGroupSymbol())
                {
                    FunctionGroupSymbol* functionGroup = static_cast<FunctionGroupSymbol*>(symbol);
                    std::vector<TypeSymbol*> parameterTypes;
                    for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
                    {
                        parameterTypes.push_back(parameterDeclaration.type);
                    }
                    FunctionSymbol* functionSymbol = functionGroup->ResolveFunction(parameterTypes, qualifiers);
                    FunctionDefinitionSymbol* definition = context->GetSymbolTable()->AddFunctionDefinition(functionDeclarator->GetScope(), functionDeclarator->Name(),
                        parameterTypes, qualifiers, declarator, functionSymbol, context);
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
                        ParameterSymbol* parameter = context->GetSymbolTable()->CreateParameter(name, node, parameterDeclaration.type, context);
                        if (parameterDeclaration.value)
                        {
                            parameter->SetDefaultValue(parameterDeclaration.value);
                        }
                        definition->AddParameter(parameter, sourcePos, context);
                    }
                    definition->SetReturnType(declaration.type);
                    context->GetSymbolTable()->BeginScope(definition->GetScope());
                    definition->GetScope()->AddParentScope(functionDeclarator->GetScope());
                    ++scopes;
                    BoundFunctionNode* boundFunctionNode = new BoundFunctionNode(definition, declarator->GetSourcePos());
                    context->GetBoundCompileUnit()->AddBoundNode(boundFunctionNode);
                    context->SetBoundFunction(boundFunctionNode);
                }
            }
            else
            {
                std::vector<TypeSymbol*> parameterTypes;
                for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
                {
                    parameterTypes.push_back(parameterDeclaration.type);
                }
                FunctionDefinitionSymbol* definition = context->GetSymbolTable()->AddFunctionDefinition(functionDeclarator->GetScope(), functionDeclarator->Name(),
                    parameterTypes, qualifiers, declarator, nullptr, context);
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
                    ParameterSymbol* parameter = context->GetSymbolTable()->CreateParameter(name, node, parameterDeclaration.type, context);
                    if (parameterDeclaration.value)
                    {
                        parameter->SetDefaultValue(parameterDeclaration.value);
                    }
                    definition->AddParameter(parameter, sourcePos, context);
                }
                definition->SetReturnType(declaration.type);
                context->GetSymbolTable()->BeginScope(definition->GetScope());
                definition->GetScope()->AddParentScope(functionDeclarator->GetScope());
                ++scopes;
                BoundFunctionNode* boundFunctionNode = new BoundFunctionNode(definition, declarator->GetSourcePos());
                context->GetBoundCompileUnit()->AddBoundNode(boundFunctionNode);
                context->SetBoundFunction(boundFunctionNode);
            }
        }
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.declaration: single declaration expected");
    }
    return scopes;
}

void EndFunctionDefinition(otava::ast::Node* functionDefinitionNode, int scopes, Context* context)
{
    FunctionDefinitionSymbol* functionDefinitionSymbol = nullptr;
    Symbol* symbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (symbol && symbol->IsFunctionDefinitionSymbol())
    {
        functionDefinitionSymbol = static_cast<FunctionDefinitionSymbol*>(symbol);
        context->GetSymbolTable()->MapNode(functionDefinitionNode, symbol, MapKind::nodeToSymbol);
    }
    for (int i = 0; i < scopes; ++i)
    {
        context->GetSymbolTable()->EndScope(); 
    }
    BindFunction(functionDefinitionNode, functionDefinitionSymbol, context);
}

void ProcessMemberFunctionDefinition(otava::ast::Node* node, Context* context)
{
    ProcessSimpleDeclaration(node, context);
}

void Write(Writer& writer, DeclarationFlags flags)
{
    writer.GetBinaryStreamWriter().WriteULEB128UInt(static_cast<uint32_t>(flags));
}

void Read(Reader& reader, DeclarationFlags& flags)
{
    flags = static_cast<DeclarationFlags>(reader.GetBinaryStreamReader().ReadULEB128UInt());
}

void ThrowDeclarationParsingError(const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("declaration parsing error", sourcePos, context);
}

} // namespace otava::symbols
