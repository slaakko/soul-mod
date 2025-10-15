// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.alias.type.templates;

import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.alias.type.symbol;
import otava.symbols.type.symbol;
import otava.symbols.templates;
import otava.symbols.exception;
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

void AliasTypeTemplateSpecializationSymbol::Write(Writer& writer)
{
    AliasTypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(instantiated);
    writer.GetBinaryStreamWriter().Write(aliasTypeTemplate->Id());
    writer.GetBinaryStreamWriter().WriteULEB128UInt(templateArguments.size());
    for (Symbol* templateArg : templateArguments)
    {
        writer.GetBinaryStreamWriter().Write(templateArg->Id());
    }
}

void AliasTypeTemplateSpecializationSymbol::Read(Reader& reader)
{
    AliasTypeSymbol::Read(reader);
    instantiated = reader.GetBinaryStreamReader().ReadBool();
    util::uuid id;
    reader.GetBinaryStreamReader().ReadUuid(id);
    ids.push_back(id);
    std::uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < count; ++i)
    {
        util::uuid id;
        reader.GetBinaryStreamReader().ReadUuid(id);
        ids.push_back(id);
    }
}

void AliasTypeTemplateSpecializationSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    AliasTypeSymbol::Resolve(symbolTable, context);
    aliasTypeTemplate = static_cast<AliasTypeSymbol*>(symbolTable.GetType(ids[0]));
    for (int i = 1; i < ids.size(); ++i)
    {
        TypeSymbol* templateArg = symbolTable.GetType(ids[i]);
        templateArguments.push_back(templateArg);
    }
    symbolTable.AddAliasTypeTemplateSpecializationToSet(this);
}

void AliasTypeTemplateSpecializationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeSymbol* InstantiateAliasTypeSymbol(TypeSymbol* typeSymbol, const std::vector<Symbol*>& templateArgs, otava::ast::TemplateIdNode* node, Context* context)
{
    AliasTypeTemplateSpecializationSymbol* specialization = context->GetSymbolTable()->MakeAliasTypeTemplateSpecialization(typeSymbol, templateArgs);
    if (specialization->Instantiated()) return specialization;
    otava::ast::Node* aliasTypeNode = context->GetSymbolTable()->GetNode(typeSymbol);
    specialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope());
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
                ThrowException("otava.symbols.alias_type_templates: wrong number of template args for instantiating alias type template '" +
                    util::ToUtf8(aliasTypeSymbol->Name()) + "'",
                    node->GetSourcePos(),
                    context);
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
                        templateArg = ResolveType(defaultTemplateArgNode, DeclarationFlags::none, context);
                        context->GetSymbolTable()->EndScope();
                    }
                    else
                    {
                        ThrowException("otava.symbols.alias_type_templates: template parameter " + std::to_string(i) + " has no default type argument", node->GetSourcePos(), context);
                    }
                }
                else
                {
                    templateArg = templateArgs[i];
                }
                BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
                boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                boundTemplateParameter->SetBoundSymbol(templateArg);
                boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                instantiationScope.Install(boundTemplateParameter, context);
            }
            context->GetSymbolTable()->BeginScope(&instantiationScope);
            Instantiator instantiator(context, &instantiationScope);
            try
            {
                context->PushSetFlag(ContextFlags::instantiateAliasTypeTemplate);
                context->SetAliasType(specialization);
                aliasTypeNode->Accept(instantiator);
                context->PopFlags();
            }
            catch (const std::exception& ex)
            {
                ThrowException("otava.symbols.alias_type_templates: error instantiating specialization '" +
                    util::ToUtf8(specialization->FullName()) + "': " + std::string(ex.what()), node->GetSourcePos(), context);
            }
            context->GetSymbolTable()->EndScope();
        }
        else
        {
            ThrowException("otava.symbols.alias_type_templates: template declarator for alias type template '" + 
                util::ToUtf8(aliasTypeSymbol->Name()) + "' not found", node->GetSourcePos(), context);
        }
    }
    else
    {
        ThrowException("otava.symbols.alias_type_templates: alias type template expected", node->GetSourcePos(), context);
    }
    return specialization;
}

} // namespace otava::symbols
