// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.class_templates;

import otava.symbols.modules;
import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.exception;
import otava.symbols.templates;
import otava.symbols.declaration;
import otava.symbols.type.resolver;
import otava.symbols.compound.type.symbol;
import otava.symbols.instantiator;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;
import otava.ast;
import util.unicode;

namespace otava::symbols {

ClassTemplateSpecializationSymbol::ClassTemplateSpecializationSymbol(const std::u32string& name_) : 
    ClassTypeSymbol(SymbolKind::classTemplateSpecializationSymbol, name_), classTemplate(nullptr), instantiated(false), symbolTable(nullptr)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

void ClassTemplateSpecializationSymbol::SetClassTemplate(TypeSymbol* classTemplate_)
{
    classTemplate = classTemplate_;
}

void ClassTemplateSpecializationSymbol::AddTemplateArgument(Symbol* templateArgument)
{
    templateArguments.push_back(templateArgument);
}

void ClassTemplateSpecializationSymbol::Write(Writer& writer)
{
    ClassTypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(instantiated);
    writer.GetBinaryStreamWriter().Write(classTemplate->Id());
    writer.GetBinaryStreamWriter().WriteULEB128UInt(templateArguments.size());
    for (Symbol* templateArg : templateArguments)
    {
        if (templateArg->IsTypeSymbol())
        {
            writer.GetBinaryStreamWriter().Write(true);
            writer.GetBinaryStreamWriter().Write(templateArg->Id());
        }
        else
        {
            writer.GetBinaryStreamWriter().Write(false);
            writer.GetBinaryStreamWriter().Write(templateArg->Id());
        }
    }
}

void ClassTemplateSpecializationSymbol::Read(Reader& reader)
{
    ClassTypeSymbol::Read(reader);
    instantiated = reader.GetBinaryStreamReader().ReadBool();
    util::uuid id;
    reader.GetBinaryStreamReader().ReadUuid(id);
    ids.push_back(std::make_pair(id, true));
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        util::uuid id;
        bool isType = reader.GetBinaryStreamReader().ReadBool();
        reader.GetBinaryStreamReader().ReadUuid(id);
        ids.push_back(std::make_pair(id, isType));
    }
}

void ClassTemplateSpecializationSymbol::Resolve(SymbolTable& symbolTable)
{
    // note: not calling ClassTypeSymbol::Resolve(symbolTable); on purpose
    classTemplate = static_cast<ClassTypeSymbol*>(symbolTable.GetType(ids[0].first));
    for (int i = 1; i < ids.size(); ++i)
    {
        const std::pair<util::uuid, bool>& idType = ids[i];
        if (idType.second)
        {
            TypeSymbol* templateArg = symbolTable.GetType(idType.first);
            templateArguments.push_back(templateArg);
        }
        else
        {
            EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
            Value* value = evaluationContext->GetValue(idType.first);
            templateArguments.push_back(value);
        }
    }
}

void ClassTemplateSpecializationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SymbolTable* ClassTemplateSpecializationSymbol::GetSymbolTable()
{
    return classTemplate->GetSymbolTable();
}

std::u32string MakeSpecializationName(TypeSymbol* templateSymbol, const std::vector<Symbol*>& templateArguments)
{
    std::u32string specializationName;
    specializationName.append(templateSymbol->Name());
    specializationName.append(1, '<');
    bool first = true;
    for (Symbol* templateArg : templateArguments)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            specializationName.append(U", ");
        }
        specializationName.append(templateArg->Name());
    }
    specializationName.append(1, '>');
    return specializationName;
}

CompoundTypeSymbol* GetSpecializationArgType(TypeSymbol* specialization, int index)
{
    if (specialization->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specializationSymbol = static_cast<ClassTemplateSpecializationSymbol*>(specialization);
        if (index >= 0 && index < specializationSymbol->TemplateArguments().size())
        {
            Symbol* specializationArg = specializationSymbol->TemplateArguments()[index];
            if (specializationArg->IsCompoundTypeSymbol())
            {
                CompoundTypeSymbol* specializationArgType = static_cast<CompoundTypeSymbol*>(specializationArg);
                return specializationArgType;
            }
        }
    }
    return nullptr;
}

TypeSymbol* InstantiateClassTemplate(TypeSymbol* typeSymbol, const std::vector<Symbol*>& templateArgs, otava::ast::TemplateIdNode* node, Context* context)
{
    ClassTemplateSpecializationSymbol* specialization = context->GetSymbolTable()->MakeClassTemplateSpecialization(typeSymbol, templateArgs);
    if (specialization->Instantiated()) return specialization;
    otava::ast::Node* classNode = context->GetSymbolTable()->GetSpecifierNode(typeSymbol);
    if (!classNode)
    {
        return specialization;
    }
    if (classNode->IsClassSpecifierNode())
    {
        otava::ast::ClassSpecifierNode* classSpecifierNode = static_cast<otava::ast::ClassSpecifierNode*>(classNode);
        if (!classSpecifierNode->Complete())
        {
            return specialization;
        }
    }
    specialization->SetInstantiated();
    if (typeSymbol->IsClassTypeSymbol())
    {
        ClassTypeSymbol* classTemplate = static_cast<ClassTypeSymbol*>(typeSymbol);
        TemplateDeclarationSymbol* templateDeclaration = classTemplate->ParentTemplateDeclaration();
        if (templateDeclaration)
        {
            int arity = templateDeclaration->Arity();
            int argCount = templateArgs.size();
            if (argCount > arity)
            {
                ThrowException("otava.symbols.templates: wrong number of template args for instantiating class template '" +
                    util::ToUtf8(classTemplate->Name()) + "'",
                    node->GetSourcePos(),
                    context);
            }
            specialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope());
            context->GetSymbolTable()->BeginScope(specialization->GetScope());
            InstantiationScope instantiationScope(specialization->GetScope());
            std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
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
                        ThrowException("otava.symbols.templates: template parameter " + std::to_string(i) + " has no default type argument", node->GetSourcePos(), context);
                    }
                }
                else
                {
                    templateArg = templateArgs[i];
                }
                if (templateArg->IsTypeSymbol())
                {
                    TypeSymbol* templateArgType = static_cast<TypeSymbol*>(templateArg);
                    TypeSymbol* specialization = classTemplate->Specialization();
                    if (specialization)
                    {
                        CompoundTypeSymbol* specializationArgType = GetSpecializationArgType(specialization, i);
                        if (specializationArgType)
                        {
                            templateArg = templateArgType->RemoveDerivations(specializationArgType->GetDerivations(), context);
                        }
                        else
                        {
                            ThrowException("otava.symbols.templates: specialization argument type not resolved", node->GetSourcePos(), context);
                        }
                    }
                }
                BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
                boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                boundTemplateParameter->SetBoundSymbol(templateArg);
                boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                instantiationScope.Install(boundTemplateParameter);
            }
            context->GetSymbolTable()->BeginScope(&instantiationScope);
            Instantiator instantiator(context, &instantiationScope);
            try
            {
                context->PushSetFlag(ContextFlags::dontBind);
                classNode->Accept(instantiator);
                context->PopFlags();
            }
            catch (const std::exception& ex)
            {
                ThrowException("otava.symbols.templates: error instantiating specialization '" +
                    util::ToUtf8(specialization->FullName()) + "': " + std::string(ex.what()), node->GetSourcePos(), context);
            }
            context->GetSymbolTable()->EndScope();
            context->GetSymbolTable()->EndScope();
            specialization->GetScope()->ClearParentScopes();
        }
        else
        {
            ThrowException("otava.symbols.templates: template declarator for class template '" + util::ToUtf8(classTemplate->Name()) + " not found", node->GetSourcePos(), context);
        }
    }
    else
    {
        ThrowException("otava.symbols.templates: class template expected", node->GetSourcePos(), context);
    }
    return specialization;
}

} // namespace otava::symbols

