// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.alias.type.templates;

import otava.symbols.alias.type.symbol;
import otava.symbols.error;
import otava.symbols.type.symbol;
import otava.symbols.templates;
import otava.symbols.declaration;
import otava.symbols.type.resolver;
import otava.symbols.instantiator;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;
import util.unicode;

namespace otava::symbols {

AliasTypeTemplateSpecializationSymbol::AliasTypeTemplateSpecializationSymbol(const std::u32string& name_) :
    AliasTypeSymbol(name_, SymbolKind::aliasTypeTemplateSpecializationSymbol), aliasTypeTemplate(nullptr), instantiated(false)
{
}

void AliasTypeTemplateSpecializationSymbol::SetAliasTypeTemplate(TypeSymbol* aliasTypeTemplate_)
{
    aliasTypeTemplate = aliasTypeTemplate_;
}

void AliasTypeTemplateSpecializationSymbol::AddTemplateArgument(Symbol* templateArgument)
{
    templateArguments.push_back(templateArgument);
}

std::string AliasTypeTemplateSpecializationSymbol::SymbolKindStr() const 
{ 
    return "alias type specialization symbol"; 
}

std::string AliasTypeTemplateSpecializationSymbol::SymbolDocKindStr() const 
{ 
    return "alias_type_specialization"; 
}

std::expected<bool, int> AliasTypeTemplateSpecializationSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = AliasTypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(instantiated);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(aliasTypeTemplate->Id());
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(static_cast<std::uint32_t>(templateArguments.size()));
    if (!rv) return rv;
    for (Symbol* templateArg : templateArguments)
    {
        rv = writer.GetBinaryStreamWriter().Write(templateArg->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AliasTypeTemplateSpecializationSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = AliasTypeSymbol::Read(reader);
    if (!rv) return rv;
    std::expected<bool, int> brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    instantiated = *brv;
    util::uuid id;
    rv = reader.GetBinaryStreamReader().ReadUuid(id);
    if (!rv) return rv;
    ids.push_back(id);
    std::expected<std::uint32_t, int> crv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!crv) return std::unexpected<int>(crv.error());
    std::int32_t count = static_cast<std::int32_t>(*crv);
    for (std::int32_t i = 0; i < count; ++i)
    {
        util::uuid id;
        rv = reader.GetBinaryStreamReader().ReadUuid(id);
        if (!rv) return rv;
        ids.push_back(id);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AliasTypeTemplateSpecializationSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = AliasTypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    aliasTypeTemplate = static_cast<AliasTypeSymbol*>(symbolTable.GetType(ids[0]));
    for (int i = 1; i < ids.size(); ++i)
    {
        TypeSymbol* templateArg = symbolTable.GetType(ids[i]);
        templateArguments.push_back(templateArg);
    }
    symbolTable.AddAliasTypeTemplateSpecializationToSet(this);
    return std::expected<bool, int>(true);
}

void AliasTypeTemplateSpecializationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<TypeSymbol*, int> InstantiateAliasTypeSymbol(TypeSymbol* typeSymbol, const std::vector<Symbol*>& templateArgs, otava::ast::TemplateIdNode* node, 
    Context* context)
{
    AliasTypeTemplateSpecializationSymbol* specialization = context->GetSymbolTable()->MakeAliasTypeTemplateSpecialization(typeSymbol, templateArgs);
    if (specialization->Instantiated()) return specialization;
    std::expected<otava::ast::Node*, int> n = context->GetSymbolTable()->GetNode(typeSymbol);
    if (!n) return std::unexpected<int>(n.error());
    otava::ast::Node* aliasTypeNode = *n;
    std::expected<bool, int> arv = specialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope());
    if (!arv) return std::unexpected<int>(arv.error());
    if (typeSymbol->IsAliasTypeSymbol())
    {
        specialization->SetInstantiated();
        AliasTypeSymbol* aliasTypeSymbol = static_cast<AliasTypeSymbol*>(typeSymbol);
        InstantiationScope instantiationScope(aliasTypeSymbol->Parent()->GetScope());
        std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
        TemplateDeclarationSymbol* templateDeclaration = aliasTypeSymbol->ParentTemplateDeclaration();
        if (templateDeclaration)
        {
            int arity = templateDeclaration->Arity();
            int argCount = templateArgs.size();
            if (argCount > arity)
            {
                std::expected<std::string, int> rv = util::ToUtf8(aliasTypeSymbol->Name());
                if (!rv) return std::unexpected<int>(rv.error());
                std::string name = *rv;
                return Error("otava.symbols.alias_type_templates: wrong number of template args for instantiating alias type template '" + name + "'", 
                    node->GetSourcePos(), context);
            }
            for (int i = 0; i < arity; ++i)
            {
                TemplateParameterSymbol* templateParameter = templateDeclaration->TemplateParameters()[i];
                Symbol* templateArg = nullptr;
                if (i >= argCount)
                {
                    otava::ast::Node* defaultTemplateArgNode = templateParameter->DefaultTemplateArg();
                    if (defaultTemplateArgNode)
                    {
                        context->GetSymbolTable()->BeginScope(&instantiationScope);
                        auto rv = ResolveType(defaultTemplateArgNode, DeclarationFlags::none, context);
                        if (!rv) return std::unexpected<int>(rv.error());
                        templateArg = *rv;
                        std::expected<bool, int> erv = context->GetSymbolTable()->EndScope();
                        if (!erv) return std::unexpected<int>(erv.error());
                    }
                    else
                    {
                        return Error("otava.symbols.alias_type_templates: template parameter " + std::to_string(i) + " has no default type argument", 
                            node->GetSourcePos(), context);
                    }
                }
                else
                {
                    templateArg = templateArgs[i];
                }
                BoundTemplateParameterSymbol* boundTemplateParameter = new BoundTemplateParameterSymbol(templateParameter->Name());
                boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                boundTemplateParameter->SetBoundSymbol(templateArg);
                boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                instantiationScope.Install(boundTemplateParameter, context);
            }
            context->GetSymbolTable()->BeginScope(&instantiationScope);
            Instantiator instantiator(context, &instantiationScope);
            context->PushSetFlag(ContextFlags::instantiateAliasTypeTemplate);
            context->SetAliasType(specialization);
            aliasTypeNode->Accept(instantiator);
            if (!instantiator)
            {
                std::expected<std::u32string, int> fname = specialization->FullName();
                if (!fname) return std::unexpected<int>(fname.error());
                std::expected<std::string, int> rv = util::ToUtf8(*fname);
                if (!rv) return std::unexpected<int>(rv.error());
                std::string sp = *rv;
                std::string errorMessage = util::GetErrorMessage(instantiator.Error());
                return Error("otava.symbols.alias_type_templates: error instantiating specialization '" + sp + "': " + errorMessage, node->GetSourcePos(), context);
            }
            context->PopFlags();
            std::expected<bool, int> erv = context->GetSymbolTable()->EndScope();
            if (!erv) return std::unexpected<int>(erv.error());
        }
        else
        {
            std::expected<std::string, int> rv = util::ToUtf8(aliasTypeSymbol->Name());
            if (!rv) return std::unexpected<int>(rv.error());
            std::string name = *rv;
            return Error("otava.symbols.alias_type_templates: template declarator for alias type template '" + name + "' not found", node->GetSourcePos(), context);
        }
    }
    else
    {
        return Error("otava.symbols.alias_type_templates: alias type template expected", node->GetSourcePos(), context);
    }
    return std::expected<TypeSymbol*, int>(specialization);
}

} // namespace otava::symbols
