module otava.symbols.type.symbol;

import otava.symbols.symbol.table;
import otava.symbols.visitor;
import otava.symbols.compound.type.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.exception;
import otava.symbols.context;
import otava.symbols.writer;
import otava.symbols.reader;

namespace otava::symbols {

TypeSymbol::TypeSymbol(SymbolKind kind_, const std::u32string& name_) : ContainerSymbol(kind_, name_)
{
}

TypeSymbol::TypeSymbol(SymbolKind kind_, const util::uuid& id_, const std::u32string& name_) : ContainerSymbol(kind_, id_, name_)
{
}

bool TypeSymbol::IsAutoTypeSymbol() const noexcept
{
    if (IsFundamentalTypeSymbol())
    {
        const FundamentalTypeSymbol* fundamentalTypeSymbol = static_cast<const FundamentalTypeSymbol*>(this);
        return fundamentalTypeSymbol->IsAutoTypeSymbol();
    }
    return false;
}

bool TypeSymbol::IsPointerType() const noexcept
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return otava::symbols::PointerCount(compoundTypeSymbol->GetDerivations()) > 0;
    }
    return false;
}

bool TypeSymbol::IsArrayType() const noexcept
{
    return Kind() == SymbolKind::arrayTypeSymbol;
}

bool TypeSymbol::IsConstType() const noexcept
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivations::constDerivation);
    }
    return false;
}

bool TypeSymbol::IsLValueRefType() const noexcept
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivations::lvalueRefDerivation);
    }
    return false;
}

bool TypeSymbol::IsRValueRefType() const noexcept
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivations::rvalueRefDerivation);
    }
    return false;
}

bool TypeSymbol::IsReferenceType() const noexcept
{
    return IsLValueRefType() || IsRValueRefType();
}

TypeSymbol* TypeSymbol::AddConst(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations = Derivations::constDerivation;
    return symbolTable->MakeCompoundType(this, derivations, context);
}

TypeSymbol* TypeSymbol::RemoveConst(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveConst(compoundTypeSymbol->GetDerivations()), context);
    }
    return this;
}

TypeSymbol* TypeSymbol::AddPointer(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations = Derivations::none;
    derivations = otava::symbols::SetPointerCount(derivations, 1);
    return symbolTable->MakeCompoundType(this, derivations, context);
}

TypeSymbol* TypeSymbol::RemovePointer(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemovePointer(compoundTypeSymbol->GetDerivations()), context);
    }
    return this;
}

TypeSymbol* TypeSymbol::AddLValueRef(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations = Derivations::lvalueRefDerivation;
    return symbolTable->MakeCompoundType(this, derivations, context);
}

TypeSymbol* TypeSymbol::RemoveLValueRef(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveLValueRef(compoundTypeSymbol->GetDerivations()), context);
    }
    return this;
}

TypeSymbol* TypeSymbol::AddRValueRef(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations = Derivations::rvalueRefDerivation;
    return symbolTable->MakeCompoundType(this, derivations, context);
}

TypeSymbol* TypeSymbol::RemoveRValueRef(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveRValueRef(compoundTypeSymbol->GetDerivations()), context);
    }
    return this;
}

TypeSymbol* TypeSymbol::RemoveReference(Context* context)
{
    if (IsLValueRefType())
    {
        return RemoveLValueRef(context);
    }
    else if (IsRValueRefType())
    {
        return RemoveRValueRef(context);
    }
    else
    {
        return this;
    }
}

TypeSymbol* TypeSymbol::RemoveRefOrPtr(Context* context)
{
    if (IsReferenceType())
    {
        return PlainType(context);
    }
    else if (IsPointerType())
    {
        return RemovePointer(context);
    }
    return this;
}

TypeSymbol* TypeSymbol::RemoveDerivations(Derivations derivations, Context* context)
{
    if (IsPointerType()) return nullptr;
    return this;
}

TypeSymbol* TypeSymbol::Unify(TypeSymbol* argType, Context* context)
{
    return nullptr;
}

otava::intermediate::Type* TypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("IRTYPE not implemented for " + SymbolKindToString(Kind()), sourcePos, context);
    return nullptr;
}

void TypeSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ContainerSymbol::AddSymbol(symbol, sourcePos, context);
}

NestedTypeSymbol::NestedTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::nestedTypeSymbol, name_)
{
}

void NestedTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DependentTypeSymbol::DependentTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::dependentTypeSymbol, name_), node()
{
}

DependentTypeSymbol::DependentTypeSymbol(otava::ast::Node* node_) : TypeSymbol(SymbolKind::dependentTypeSymbol, U"@dependent_type"), node(node_)
{
    if (node->IsTypenameSpecifierNode())
    {
        otava::ast::TypenameSpecifierNode* s = static_cast<otava::ast::TypenameSpecifierNode*>(node.get());
        SetName(s->GetId()->Str());
    }
}

void DependentTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    otava::ast::Writer astWriter(&writer.GetBinaryStreamWriter());
    astWriter.Write(node.get());
}

void DependentTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    otava::ast::Reader astReader(&reader.GetBinaryStreamReader());
    astReader.SetNodeMap(reader.GetSymbolTable()->GetNodeMap());
    node.reset(astReader.ReadNode());
}

void DependentTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ErrorTypeSymbol::ErrorTypeSymbol() : TypeSymbol(SymbolKind::errorSymbol, U"<error_type>")
{
}

void ErrorTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FunctionGroupTypeSymbol::FunctionGroupTypeSymbol(FunctionGroupSymbol* functionGroupSymbol_) :
    TypeSymbol(SymbolKind::functionGroupTypeSymbol, U"@function_group_type"), functionGroupSymbol(functionGroupSymbol_)
{
}

FunctionGroupTypeSymbol::FunctionGroupTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::functionGroupTypeSymbol, name_), functionGroupSymbol(nullptr)
{
}

void FunctionGroupTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(functionGroupSymbol->Id());
}

void FunctionGroupTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(functionGroupSymbolId);
}

void FunctionGroupTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol::Resolve(symbolTable, context);
    functionGroupSymbol = symbolTable.GetFunctionGroup(functionGroupSymbolId);
}

void FunctionGroupTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ClassGroupTypeSymbol::ClassGroupTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::classGroupTypeSymbol, name_), classGroupSymbol(nullptr)
{
}

ClassGroupTypeSymbol::ClassGroupTypeSymbol(ClassGroupSymbol* classGroupSymbol_) :
    TypeSymbol(SymbolKind::classGroupTypeSymbol, U"@classGroupType:" + classGroupSymbol_->Name()), classGroupSymbol(classGroupSymbol_)
{
}

void ClassGroupTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(classGroupSymbol->Id());
}

void ClassGroupTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(classGroupSymbolId);
}

void ClassGroupTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol::Resolve(symbolTable, context);
    classGroupSymbol = symbolTable.GetClassGroup(classGroupSymbolId);
}

void ClassGroupTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AliasGroupTypeSymbol::AliasGroupTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::aliasGroupTypeSymbol, name_), aliasGroupSymbol(nullptr)
{
}

AliasGroupTypeSymbol::AliasGroupTypeSymbol(AliasGroupSymbol* aliasGroupSymbol_) :
    TypeSymbol(SymbolKind::aliasGroupTypeSymbol, U"@alias_group_type"), aliasGroupSymbol(aliasGroupSymbol_)
{
}

void AliasGroupTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(aliasGroupSymbol->Id());
}

void AliasGroupTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(aliasGroupSymbolId);
}

void AliasGroupTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol::Resolve(symbolTable, context);
    aliasGroupSymbol = symbolTable.GetAliasGroup(aliasGroupSymbolId);
}

void AliasGroupTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeSymbol* GenericTypeSymbol::Instance()
{
    static GenericTypeSymbol instance;
    return &instance;
}

GenericTypeSymbol::GenericTypeSymbol() : TypeSymbol(SymbolKind::genericTypeSymbol, U"@generic_type")
{
}

void GenericTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeSymbol* ConvertRefToPtrType(TypeSymbol* type, Context* context)
{
    if (type->IsLValueRefType())
    {
        return type->RemoveLValueRef(context)->AddPointer(context);
    }
    else if (type->IsRValueRefType())
    {
        return type->RemoveRValueRef(context)->AddPointer(context);
    }
    return type;
}

std::pair<std::unique_ptr<otava::ast::Node>, std::unique_ptr<otava::ast::Node>> TypeToAst(TypeSymbol* type, const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<otava::ast::Node> node;
    std::unique_ptr<otava::ast::Node> declarator;
    if (type->GetBaseType()->IsFundamentalTypeSymbol())
    {
        FundamentalTypeSymbol* fundamentalType = static_cast<FundamentalTypeSymbol*>(type->GetBaseType());
        std::unique_ptr<otava::ast::TypeSpecifierSequenceNode> typeSpecifiers(new otava::ast::TypeSpecifierSequenceNode(sourcePos));
        if (type->IsConstType())
        {
            typeSpecifiers->AddNode(new otava::ast::ConstNode(sourcePos));
        }
        MakeFundamentaTypeSequence(fundamentalType, sourcePos, typeSpecifiers.get());
        node.reset(typeSpecifiers.release());
    }
    else if (type->GetBaseType()->IsEnumeratedTypeSymbol())
    {
        node.reset(new otava::ast::IdentifierNode(sourcePos, type->GetBaseType()->Name()));
    }
    else if (type->GetBaseType()->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(type->GetBaseType());
        node.reset(new otava::ast::TemplateIdNode(sourcePos, new otava::ast::IdentifierNode(sourcePos, specialization->ClassTemplate()->Name())));
        bool first = true;
        for (auto* templateArg : specialization->TemplateArguments())
        {
            if (first)
            {
                first = false;
            }
            else
            {
                node->AddNode(new otava::ast::CommaNode(sourcePos));
            }
            if (templateArg->IsTypeSymbol())
            {
                TypeSymbol* templateArgType = static_cast<TypeSymbol*>(templateArg);
                std::pair<std::unique_ptr<otava::ast::Node>, std::unique_ptr<otava::ast::Node>> nodeDeclarator = TypeToAst(templateArgType, sourcePos);
                std::unique_ptr<otava::ast::Node> argNode = std::move(nodeDeclarator.first);
                std::unique_ptr<otava::ast::Node> argDeclarator = std::move(nodeDeclarator.second);
                std::unique_ptr<otava::ast::TypeSpecifierSequenceNode> typeSpecifiers;
                if (argNode->IsTypeSpecifierSequenceNode())
                {
                    typeSpecifiers.reset(static_cast<otava::ast::TypeSpecifierSequenceNode*>(argNode.release()));
                }
                else
                {
                    typeSpecifiers.reset(new otava::ast::TypeSpecifierSequenceNode(sourcePos));
                    if (templateArgType->IsConstType())
                    {
                        typeSpecifiers->AddNode(new otava::ast::ConstNode(sourcePos));
                    }
                    typeSpecifiers->AddNode(argNode.release());
                }
                std::unique_ptr<otava::ast::TypeIdNode> typeIdNode(new otava::ast::TypeIdNode(sourcePos, typeSpecifiers.release(), argDeclarator.release()));
                node->AddNode(typeIdNode.release());
            }
        }
    }
    else if (type->GetBaseType()->IsClassTypeSymbol())
    {
        node.reset(new otava::ast::IdentifierNode(sourcePos, type->GetBaseType()->Name()));
    }
    NamespaceSymbol* ns = type->ParentNamespace();
    if (ns)
    {
        std::unique_ptr<otava::ast::NestedNameSpecifierNode> nns(new otava::ast::NestedNameSpecifierNode(sourcePos));
        std::u32string nsFullName = ns->FullName();
        if (!nsFullName.empty())
        {
            std::vector<std::u32string> components = util::Split(nsFullName, std::u32string(U"::"));
            bool first = true;
            for (const auto& component : components)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    nns->AddNode(new otava::ast::ColonColonNode(sourcePos));
                }
                nns->AddNode(new otava::ast::IdentifierNode(sourcePos, component));
            }
            nns->AddNode(new otava::ast::ColonColonNode(sourcePos));
            otava::ast::QualifiedIdNode* qid = new otava::ast::QualifiedIdNode(sourcePos, nns.release(), node.release());
            node.reset(qid);
        }
    }
    declarator.reset(new otava::ast::AbstractDeclaratorNode(sourcePos));
    if (type->IsPointerType() || type->IsReferenceType())
    {
        declarator.reset(new otava::ast::PtrDeclaratorNode(sourcePos));
        int n = type->PointerCount();
        for (int i = 0; i < n; ++i)
        {
            declarator->AddNode(new otava::ast::PtrNode(sourcePos));
        }
        if (type->IsLValueRefType())
        {
            declarator->AddNode(new otava::ast::LvalueRefNode(sourcePos));
        }
        else if (type->IsRValueRefType())
        {
            declarator->AddNode(new otava::ast::RvalueRefNode(sourcePos));
        }
        declarator->AddNode(new otava::ast::AbstractDeclaratorNode(sourcePos));
    }
    return std::make_pair(std::move(node), std::move(declarator));
}

std::unique_ptr<otava::ast::SimpleDeclarationNode> DeclarationToSimpleDeclarationAst(TypeSymbol* type, const std::u32string& variableName, otava::ast::Node* initializer,
    const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<otava::ast::SimpleDeclarationNode> node(new otava::ast::SimpleDeclarationNode(sourcePos));
    std::unique_ptr<otava::ast::DeclSpecifierSequenceNode> sequence(new otava::ast::DeclSpecifierSequenceNode(sourcePos));
    if (type->IsConstType())
    {
        sequence->AddNode(new otava::ast::ConstNode(sourcePos));
    }
    std::unique_ptr<otava::ast::Node> name;
    if (type->GetBaseType()->IsFundamentalTypeSymbol())
    {
        FundamentalTypeSymbol* fundamentalType = static_cast<FundamentalTypeSymbol*>(type->GetBaseType());
        MakeFundamentaTypeSequence(fundamentalType, sourcePos, sequence.get());
    }
    else if (type->GetBaseType()->IsEnumeratedTypeSymbol())
    {
        name.reset(new otava::ast::IdentifierNode(sourcePos, type->GetBaseType()->Name()));
    }
    else if (type->GetBaseType()->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(type->GetBaseType());
        name.reset(new otava::ast::TemplateIdNode(sourcePos, new otava::ast::IdentifierNode(sourcePos, specialization->ClassTemplate()->Name())));
        bool first = true;
        for (auto* templateArg : specialization->TemplateArguments())
        {
            if (first)
            {
                first = false;
            }
            else
            {
                name->AddNode(new otava::ast::CommaNode(sourcePos));
            }
            if (templateArg->IsTypeSymbol())
            {
                TypeSymbol* templateArgType = static_cast<TypeSymbol*>(templateArg);
                std::pair<std::unique_ptr<otava::ast::Node>, std::unique_ptr<otava::ast::Node>> nodeDeclarator = TypeToAst(templateArgType, sourcePos);
                std::unique_ptr<otava::ast::Node> argNode = std::move(nodeDeclarator.first);
                std::unique_ptr<otava::ast::Node> argDeclarator = std::move(nodeDeclarator.second);
                std::unique_ptr<otava::ast::TypeSpecifierSequenceNode> typeSpecifiers;
                if (argNode->IsTypeSpecifierSequenceNode())
                {
                    typeSpecifiers.reset(static_cast<otava::ast::TypeSpecifierSequenceNode*>(argNode.release()));
                }
                else
                {
                    typeSpecifiers.reset(new otava::ast::TypeSpecifierSequenceNode(sourcePos));
                    if (templateArgType->IsConstType())
                    {
                        typeSpecifiers->AddNode(new otava::ast::ConstNode(sourcePos));
                    }
                    typeSpecifiers->AddNode(argNode.release());
                }
                std::unique_ptr<otava::ast::TypeIdNode> typeIdNode(new otava::ast::TypeIdNode(sourcePos, typeSpecifiers.release(), argDeclarator.release()));
                name->AddNode(typeIdNode.release());
            }
        }
    }
    else if (type->GetBaseType()->IsClassTypeSymbol())
    {
        name.reset(new otava::ast::IdentifierNode(sourcePos, type->GetBaseType()->Name()));
    }
    NamespaceSymbol* ns = type->ParentNamespace();
    if (ns)
    {
        std::unique_ptr<otava::ast::NestedNameSpecifierNode> nns(new otava::ast::NestedNameSpecifierNode(sourcePos));
        std::u32string nsFullName = ns->FullName();
        if (!nsFullName.empty())
        {
            std::vector<std::u32string> components = util::Split(nsFullName, std::u32string(U"::"));
            bool first = true;
            for (const auto& component : components)
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    nns->AddNode(new otava::ast::ColonColonNode(sourcePos));
                }
                nns->AddNode(new otava::ast::IdentifierNode(sourcePos, component));
            }
            nns->AddNode(new otava::ast::ColonColonNode(sourcePos));
            otava::ast::QualifiedIdNode* qid = new otava::ast::QualifiedIdNode(sourcePos, nns.release(), name.release());
            sequence->AddNode(qid);
        }
    }
    node->SetDeclarationSpecifiers(sequence.release());
    std::unique_ptr<otava::ast::InitDeclaratorListNode> initDeclarators(new otava::ast::InitDeclaratorListNode(sourcePos));
    std::unique_ptr<otava::ast::Node> declarator;
    if (type->IsReferenceType() || type->IsPointerType())
    {
        declarator.reset(new otava::ast::PtrDeclaratorNode(sourcePos));
        int n = type->PointerCount();
        for (int i = 0; i < n; ++i)
        {
            declarator->AddNode(new otava::ast::PtrNode(sourcePos));
        }
        if (type->IsLValueRefType())
        {
            declarator->AddNode(new otava::ast::LvalueRefNode(sourcePos));
        }
        else if (type->IsRValueRefType())
        {
            declarator->AddNode(new otava::ast::RvalueRefNode(sourcePos));
        }
        declarator->AddNode(new otava::ast::IdentifierNode(sourcePos, variableName));
    }
    else
    {
        declarator.reset(new otava::ast::IdentifierNode(sourcePos, variableName));
    }
    std::unique_ptr<otava::ast::InitDeclaratorNode> initDeclarator(new otava::ast::InitDeclaratorNode(sourcePos, declarator.release(), initializer));
    initDeclarators->AddNode(initDeclarator.release());
    node->SetInitDeclaratorList(initDeclarators.release());
    return node;
}

std::unique_ptr<otava::ast::DeclarationStatementNode> DeclarationToAst(TypeSymbol* type, const std::u32string& variableName, otava::ast::Node* initializer,
    const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<otava::ast::SimpleDeclarationNode> simpleDeclarationNode = DeclarationToSimpleDeclarationAst(type, variableName, initializer, sourcePos);
    std::unique_ptr<otava::ast::DeclarationStatementNode> statementNode(new otava::ast::DeclarationStatementNode(sourcePos, simpleDeclarationNode.release()));
    return statementNode;
}

} // namespace otava::symbols
