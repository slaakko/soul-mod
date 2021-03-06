// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.declaration;

import soul.cpp20.symbols.context;
import soul.cpp20.symbols.declarator;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.fundamental.type.symbol;
import soul.cpp20.symbols.type.resolver;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;

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
    if ((flags & DeclarationFlags::constFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("const");
    }
    if ((flags & DeclarationFlags::volatileFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("volatile");
    }
    return str;
}

class DeclarationProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    DeclarationProcessor(Context* context_);
    std::vector<Declaration> GetDeclarations() { return std::move(declarations); }
    void Visit(soul::cpp20::ast::SimpleDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::ParameterNode& node) override;
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

    void Visit(soul::cpp20::ast::FriendNode& node) override;
    void Visit(soul::cpp20::ast::TypedefNode& node) override;
    void Visit(soul::cpp20::ast::ConstExprNode& node) override;
    void Visit(soul::cpp20::ast::ConstEvalNode& node) override;
    void Visit(soul::cpp20::ast::ConstInitNode& node) override;
    void Visit(soul::cpp20::ast::InlineNode& node) override;
    void Visit(soul::cpp20::ast::StaticNode& node) override;
    void Visit(soul::cpp20::ast::ThreadLocalNode& node) override;
    void Visit(soul::cpp20::ast::ExternNode& node) override;
private:
    Context* context;
    DeclarationFlags flags;
    std::vector<Declaration> declarations;
};

DeclarationProcessor::DeclarationProcessor(Context* context_) : context(context_), flags(DeclarationFlags::none)
{
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
        // todo
    }
    return baseType;
}

void DeclarationProcessor::Visit(soul::cpp20::ast::SimpleDeclarationNode& node)
{
    node.DeclarationSpecifiers()->Accept(*this);
    TypeSymbol* baseType = ResolveBaseType(&node);
    declarations = ProcessInitDeclaratorList(baseType, node.InitDeclaratorList(), context);
}

void DeclarationProcessor::Visit(soul::cpp20::ast::ParameterNode& node)
{
    node.DeclSpecifiers()->Accept(*this);
    TypeSymbol* baseType = ResolveBaseType(&node);
    Declaration declaration = ProcessDeclarator(baseType, node.Declarator(), context);
    declarations.push_back(std::move(declaration));
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

void ProcessSimpleDeclarator(SimpleDeclarator* simpleDeclarator, TypeSymbol* type, Context* context)
{
    context->GetSymbolTable()->AddVariable(simpleDeclarator->Name(), simpleDeclarator->Node(), type, context);
}

void ProcessFunctionDeclarator(FunctionDeclarator* functionDeclarator, TypeSymbol* type, Context* context)
{
    FunctionSymbol* functionSymbol = context->GetSymbolTable()->AddFunction(functionDeclarator->Name(), functionDeclarator->Node(), context);
    functionSymbol->SetReturnType(type);
    for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
    {
        ParameterSymbol* parameter = context->GetSymbolTable()->CreateParameter(parameterDeclaration.declarator->Name(), parameterDeclaration.declarator->Node(), 
            parameterDeclaration.type, context);
        functionSymbol->AddParameter(parameter, parameterDeclaration.declarator->Node()->GetSourcePos(), context);
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
                ProcessSimpleDeclarator(simpleDeclarator, declaration.type, context);
                break;
            }
            case DeclaratorKind::functionDeclarator:
            {
                FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declarator);
                ProcessFunctionDeclarator(functionDeclarator, declaration.type, context);
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
        throw std::runtime_error("single declaration expected");
    }
}

void Write(Writer& writer, DeclarationFlags flags)
{
    writer.GetBinaryStreamWriter().WriteULEB128UInt(static_cast<uint32_t>(flags));
}

void Read(Reader& reader, DeclarationFlags& flags)
{
    flags = static_cast<DeclarationFlags>(reader.GetBinaryStreamReader().ReadULEB128UInt());
}

} // namespace soul::cpp20::symbols
