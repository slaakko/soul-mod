// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.declaration;

import soul.cpp20.symbols.context;
import soul.cpp20.symbols.declarator;
import soul.cpp20.symbols.evaluator;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.function.group.symbol;
import soul.cpp20.symbols.fundamental.type.symbol;
import soul.cpp20.symbols.type.resolver;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.ast.error;
import util;

namespace soul::cpp20::symbols {

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

class DeclarationProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    DeclarationProcessor(Context* context_);
    std::vector<Declaration> GetDeclarations() { return std::move(declarations); }
    void BeginProcessFunctionDefinition(soul::cpp20::ast::Node* declSpecifierSeq, soul::cpp20::ast::Node* declarator);
    void Visit(soul::cpp20::ast::SimpleDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::MemberDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::NoDeclSpecFunctionDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::FunctionDefinitionNode& node) override;
    void Visit(soul::cpp20::ast::ParameterNode& node) override;
    void Visit(soul::cpp20::ast::ClassSpecifierNode& node) override;
    void Visit(soul::cpp20::ast::EnumSpecifierNode& node) override;
    void Visit(soul::cpp20::ast::ElaboratedTypeSpecifierNode & override);
    TypeSymbol* ResolveBaseType(soul::cpp20::ast::Node* node);
    void Visit(soul::cpp20::ast::CharNode& node) override;
    void Visit(soul::cpp20::ast::Char8Node& node) override;
    void Visit(soul::cpp20::ast::Char16Node& node) override;
    void Visit(soul::cpp20::ast::Char32Node& node) override;
    void Visit(soul::cpp20::ast::WCharNode& node) override;
    void Visit(soul::cpp20::ast::BoolNode& node) override;
    void Visit(soul::cpp20::ast::ShortNode& node) override;
    void Visit(soul::cpp20::ast::IntNode& node) override;
    void Visit(soul::cpp20::ast::LongNode& node) override;
    void Visit(soul::cpp20::ast::SignedNode& node) override;
    void Visit(soul::cpp20::ast::UnsignedNode& node) override;
    void Visit(soul::cpp20::ast::FloatNode& node) override;
    void Visit(soul::cpp20::ast::DoubleNode& node) override;
    void Visit(soul::cpp20::ast::VoidNode& node) override;
    void Visit(soul::cpp20::ast::ConstNode& node) override;
    void Visit(soul::cpp20::ast::VolatileNode& node) override;
    void Visit(soul::cpp20::ast::PlaceholderTypeSpecifierNode& node) override;

    void Visit(soul::cpp20::ast::FriendNode& node) override;
    void Visit(soul::cpp20::ast::TypedefNode& node) override;
    void Visit(soul::cpp20::ast::ConstExprNode& node) override;
    void Visit(soul::cpp20::ast::ConstEvalNode& node) override;
    void Visit(soul::cpp20::ast::ConstInitNode& node) override;
    void Visit(soul::cpp20::ast::InlineNode& node) override;
    void Visit(soul::cpp20::ast::StaticNode& node) override;
    void Visit(soul::cpp20::ast::ThreadLocalNode& node) override;
    void Visit(soul::cpp20::ast::ExternNode& node) override;
    void Visit(soul::cpp20::ast::VirtualNode& node) override;

    void Visit(soul::cpp20::ast::QualifiedIdNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
    void Visit(soul::cpp20::ast::TemplateIdNode& node) override;

    void Visit(soul::cpp20::ast::TypenameSpecifierNode& node) override;
private:
    Context* context;
    DeclarationFlags flags;
    std::vector<Declaration> declarations;
    bool isClassSpecifier;
    TypeSymbol* type;
};

DeclarationProcessor::DeclarationProcessor(Context* context_) : context(context_), flags(DeclarationFlags::none), isClassSpecifier(false), type(nullptr)
{
}

void DeclarationProcessor::BeginProcessFunctionDefinition(soul::cpp20::ast::Node* declSpecifierSeq, soul::cpp20::ast::Node* declarator)
{
    if (declSpecifierSeq)
    {
        declSpecifierSeq->Accept(*this);
    }
    TypeSymbol* baseType = ResolveBaseType(declSpecifierSeq);
    Declaration declaration = ProcessDeclarator(baseType, declarator, flags, context);
    declarations.push_back(std::move(declaration));
}

TypeSymbol* DeclarationProcessor::ResolveBaseType(soul::cpp20::ast::Node* node)
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

void DeclarationProcessor::Visit(soul::cpp20::ast::SimpleDeclarationNode& node)
{
    node.DeclarationSpecifiers()->Accept(*this);
    if (node.InitDeclaratorList())
    {
        TypeSymbol* baseType = ResolveBaseType(&node);
        declarations = ProcessInitDeclaratorList(baseType, node.InitDeclaratorList(), flags, context);
    }
}

void DeclarationProcessor::Visit(soul::cpp20::ast::MemberDeclarationNode& node)
{
    if (node.DeclSpecifiers())
    {
        node.DeclSpecifiers()->Accept(*this);
    }
    if (node.MemberDeclarators())
    {
        TypeSymbol* baseType = ResolveBaseType(&node);
        declarations = ProcessMemberDeclaratorList(baseType, node.MemberDeclarators(), flags, context);
    }
}

void DeclarationProcessor::Visit(soul::cpp20::ast::NoDeclSpecFunctionDeclarationNode& node)
{
    declarations.push_back(ProcessDeclarator(nullptr, &node, flags, context));
}

void DeclarationProcessor::Visit(soul::cpp20::ast::FunctionDefinitionNode& node)
{
    if (node.DeclSpecifiers())
    {
        node.DeclSpecifiers()->Accept(*this);
    }
    TypeSymbol* baseType = ResolveBaseType(&node);
    Declaration declaration = ProcessDeclarator(baseType, node.Declarator(), flags, context);
    if (node.FunctionBody() && node.FunctionBody()->Kind() == soul::cpp20::ast::NodeKind::defaultedOrDeletedFunctionNode)
    {
        if (declaration.declarator->IsFunctionDeclarator())
        {
            FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declaration.declarator.get());
            soul::cpp20::ast::DefaultedOrDeletedFunctionNode* ddNode = static_cast<soul::cpp20::ast::DefaultedOrDeletedFunctionNode*>(node.FunctionBody());
            switch (ddNode->DefaultOrDelete()->Kind())
            {
                case soul::cpp20::ast::NodeKind::defaultNode:
                {
                    functionDeclarator->AddQualifier(FunctionQualifiers::isDefault);
                    break;
                }
                case soul::cpp20::ast::NodeKind::deleteNode:
                {
                    functionDeclarator->AddQualifier(FunctionQualifiers::isDeleted);
                    break;
                }
            }
        }
    }
    declarations.push_back(std::move(declaration));
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ParameterNode& node)
{
    node.DeclSpecifiers()->Accept(*this);
    TypeSymbol* baseType = ResolveBaseType(&node);
    Declaration declaration = ProcessDeclarator(baseType, node.Declarator(), flags, context);
    if (node.Initializer())
    {
        declaration.value = Evaluate(node.Initializer(), context);
    }
    declarations.push_back(std::move(declaration));
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ClassSpecifierNode& node)
{
}

void DeclarationProcessor::Visit(soul::cpp20::ast::EnumSpecifierNode& node)
{
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ElaboratedTypeSpecifierNode& node)
{
}

void DeclarationProcessor::Visit(soul::cpp20::ast::CharNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::charFlag, "char", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::charFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::Char8Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char8Flag, "char8_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char8Flag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::Char16Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char16Flag, "char16_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char16Flag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::Char32Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char32Flag, "char32_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char32Flag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::WCharNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "wchar_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::wcharFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::BoolNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "bool", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::boolFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ShortNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::shortFlag, "short", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::shortFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::IntNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::intFlag, "int", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::intFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::LongNode& node)
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

void DeclarationProcessor::Visit(soul::cpp20::ast::SignedNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::signedFlag, "signed", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::signedFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::UnsignedNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::unsignedFlag, "unsigned", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::unsignedFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::FloatNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::floatFlag, "float", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::floatFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::DoubleNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::doubleFlag, "double", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::doubleFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::VoidNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::voidFlag, "void", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::voidFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ConstNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constFlag, "const", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::VolatileNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::volatileFlag, "volatile", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::volatileFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::PlaceholderTypeSpecifierNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::autoFlag, "auto", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::autoFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::FriendNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::friendFlag, "friend", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::friendFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::TypedefNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::typedefFlag, "typedef", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::typedefFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ConstExprNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constExprFlag, "constexpr", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constExprFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ConstEvalNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constEvalFlag, "consteval", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constEvalFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ConstInitNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constInitFlag, "constinit", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constInitFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::InlineNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::inlineFlag, "inline", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::inlineFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::StaticNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::staticFlag, "static", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::staticFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ThreadLocalNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::threadLocalFlag, "thread_local", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::threadLocalFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ExternNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::externFlag, "extern", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::externFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::VirtualNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::externFlag, "virtual", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::virtualFlag;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::QualifiedIdNode& node)
{
    type = ResolveType(&node, flags, context);
}

void DeclarationProcessor::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    type = ResolveType(&node, flags, context);
}

void DeclarationProcessor::Visit(soul::cpp20::ast::TemplateIdNode& node)
{
    type = ResolveType(&node, flags, context);
}

void DeclarationProcessor::Visit(soul::cpp20::ast::TypenameSpecifierNode& node)
{
    type = ResolveType(&node, flags, context);
}

void ProcessSimpleDeclarator(SimpleDeclarator* simpleDeclarator, TypeSymbol* type, Value* value, DeclarationFlags flags, Context* context)
{
    context->GetSymbolTable()->AddVariable(simpleDeclarator->Name(), simpleDeclarator->Node(), type, value, flags, context);
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
        soul::cpp20::ast::Node* node = nullptr;
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

void ProcessSimpleDeclaration(soul::cpp20::ast::Node* node, Context* context)
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    std::vector<Declaration> declarations = processor.GetDeclarations();
    for (const auto& declaration : declarations)
    {
        Declarator* declarator = declaration.declarator.get();
        switch (declarator->Kind())
        {
            case DeclaratorKind::simpleDeclarator:
            {
                SimpleDeclarator* simpleDeclarator = static_cast<SimpleDeclarator*>(declarator);
                ProcessSimpleDeclarator(simpleDeclarator, declaration.type, declaration.value, declaration.flags, context);
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
}

Declaration ProcessParameterDeclaration(soul::cpp20::ast::Node* node, Context* context)
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    std::vector<Declaration> declarations = processor.GetDeclarations();
    if (declarations.size() == 1)
    {
        return std::move(declarations.front());
    }
    else
    {
        soul::cpp20::ast::SetExceptionThrown();
        throw std::runtime_error("soul.cpp20.symbols.declaration: single declaration expected");
    }
}

void ProcessMemberDeclaration(soul::cpp20::ast::Node* node, Context* context)
{
    ProcessSimpleDeclaration(node, context);
}

Declaration ProcessFunctionDeclaration(soul::cpp20::ast::Node* node, Context* context) 
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    std::vector<Declaration> declarations = processor.GetDeclarations();
    if (declarations.size() == 1)
    {
        return std::move(declarations.front());
    }
    else
    {
        soul::cpp20::ast::SetExceptionThrown();
        throw std::runtime_error("soul.cpp20.symbols.declaration: single declaration expected");
    }
}

int BeginFunctionDefinition(soul::cpp20::ast::Node* declSpecifierSequence, soul::cpp20::ast::Node* declarator, Context* context)
{
    int scopes = 0;
    if (declarator->GetSourcePos().file == 11 && declarator->GetSourcePos().line == 113)
    {
        int x = 0;
    }
    DeclarationProcessor processor(context);
    processor.BeginProcessFunctionDefinition(declSpecifierSequence, declarator);
    context->GetSymbolTable()->CurrentScope()->PopParentScope();
    std::vector<Declaration> declarations = processor.GetDeclarations();
    if (declarations.size() == 1)
    {
        Declaration declaration = std::move(declarations.front());
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
                    FunctionDefinitionSymbol* definition = context->GetSymbolTable()->AddFunctionDefinition(
                        util::ToUtf32(functionDeclarator->GetScope()->FullName()) + U"::" + functionDeclarator->Name(), parameterTypes, qualifiers, declarator, functionSymbol, context);
                    for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
                    {
                        soul::ast::SourcePos sourcePos;
                        std::u32string name;
                        soul::cpp20::ast::Node* node = nullptr;
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
                }
            }
            else
            {
                std::vector<TypeSymbol*> parameterTypes;
                for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
                {
                    parameterTypes.push_back(parameterDeclaration.type);
                }
                FunctionDefinitionSymbol* definition = context->GetSymbolTable()->AddFunctionDefinition(
                    util::ToUtf32(functionDeclarator->GetScope()->FullName()) + U"::" + functionDeclarator->Name(), parameterTypes, qualifiers, declarator, nullptr, context);
                for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
                {
                    soul::ast::SourcePos sourcePos;
                    std::u32string name;
                    soul::cpp20::ast::Node* node = nullptr;
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
            }
        }
    }
    else
    {
        soul::cpp20::ast::SetExceptionThrown();
        throw std::runtime_error("soul.cpp20.symbols.declaration: single declaration expected");
    }
    return scopes;
}

void EndFunctionDefinition(soul::cpp20::ast::Node* functionDefinitionNode, int scopes, Context* context)
{
    for (int i = 0; i < scopes; ++i)
    {
        context->GetSymbolTable()->EndScope(); 
    }
}

void ProcessMemberFunctionDefinition(soul::cpp20::ast::Node* node, Context* context)
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

} // namespace soul::cpp20::symbols
