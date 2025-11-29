// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.context;

import otava.symbols.declarator;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.scope;
import otava.symbols.symbol;
import otava.symbols.bound.tree;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;

namespace otava::symbols {

int GetOptLevel(int level, bool release)
{
    if (release)
    {
        if (level == -1)
        {
            return 2;
        }
        else
        {
            return level;
        }
    }
    else
    {
        return 0;
    }
}

Context::Context() :
    symbolTable(nullptr),
    traceInfo(nullptr),
    lexer(nullptr),
    flags(ContextFlags::none),
    optLevel(-1),
    node(nullptr),
    boundCompileUnit(new BoundCompileUnitNode()),
    boundFunction(nullptr),
    fileMap(nullptr),
    functionNode(nullptr),
    aliasType(nullptr),
    ptr(nullptr),
    memFunDefSymbolIndex(-1),
    rejectTemplateId(false),
    switchCondType(nullptr),
    instantiationQueue(nullptr),
    declaredInitializerType(nullptr),
    functionDefinitionSymbolSet(nullptr),
    templateParameterMap(nullptr),
    argType(nullptr),
    paramType(nullptr),
    totalFunctionsCompiled(0),
    functionCallsInlined(0),
    functionsInlined(0),
    emitter(nullptr),
    argIndex(0),
    boundFunctionSerial(0)
{
}

Context::~Context()
{
    for (auto& d : declarationMap)
    {
        delete d.second;
    }
    declarationMap.clear();
}

Lexer* Context::GetLexer() const
{
    return lexer;
}

void Context::SetLexer(Lexer* lexer_)
{
    lexer = lexer_;
}

void Context::SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_)
{
    functionDefinitionSymbolSet = functionDefinitionSymbolSet_;
}

FunctionDefinitionSymbolSet* Context::GetFunctionDefinitionSymbolSet() const
{
    return functionDefinitionSymbolSet;
}

void Context::SetSymbolTable(SymbolTable* symbolTable_)
{
    symbolTable = symbolTable_;
}

SymbolTable* Context::GetSymbolTable()
{ 
    return symbolTable; 
}

Module* Context::GetModule()
{
    return symbolTable->GetModule();
}

OperationRepository* Context::GetOperationRepository() const
{
    return GetBoundCompileUnit()->GetOperationRepository();
}

EvaluationContext* Context::GetEvaluationContext()
{
    return symbolTable->GetModule()->GetEvaluationContext();
}

std::expected<BoundExpressionNode*, int> Context::GetThisPtr(const soul::ast::SourcePos& sourcePos)
{
    FunctionDefinitionSymbol* function = boundFunction->GetFunctionDefinitionSymbol();
    std::expected<ParameterSymbol*, int> tp = function->ThisParam(this);
    if (!tp) return std::unexpected<int>(tp.error());
    ParameterSymbol* thisParam = *tp;
    if (thisParam)
    {
        return std::expected<BoundExpressionNode*, int>(static_cast<BoundExpressionNode*>(new BoundParameterNode(thisParam, sourcePos, thisParam->GetType())));
    }
    else
    {
        return std::expected<BoundExpressionNode*, int>(static_cast<BoundExpressionNode*>(nullptr));
    }
}

void Context::SetFileName(const std::string& fileName_)
{
    fileName = fileName_;
}

std::string Context::FileName() const
{
    if (lexer)
    {
        return lexer->FileName();
    }
    else
    {
        return fileName;
    }
}

void Context::PushFlags()
{
    flagStack.push(flags);
}

void Context::PopFlags()
{
    flags = flagStack.top();
    flagStack.pop();
}

void Context::PushSetFlag(ContextFlags flag)
{
    PushFlags();
    SetFlag(flag);
}

void Context::PushResetFlag(ContextFlags flag)
{
    PushFlags();
    ResetFlag(flag);
}

int Context::OptLevel() const
{
    return GetOptLevel(optLevel, ReleaseConfig());
}

bool Context::IsConstructorNameNode(otava::ast::Node* node) const
{
    if (!GetFlag(ContextFlags::parsingParameters) && !GetFlag(ContextFlags::retMemberDeclSpecifiers) && !GetFlag(ContextFlags::parsingTemplateId))
    {
        Scope* currentScope = symbolTable->CurrentScope();
        if (currentScope->IsClassScope())
        {
            Symbol* symbol = currentScope->GetSymbol();
            if (symbol->Name() == node->Str())
            {
                return true;
            }
        }
    }
    return false;
}

bool Context::EnableNoDeclSpecFunctionDeclaration() const
{
    Scope* currentScope = symbolTable->CurrentScope();
    if (currentScope->IsTemplateDeclarationScope())
    {
        Symbol* symbol = currentScope->GetSymbol();
        Symbol* parent = symbol->Parent();
        if (parent->GetScope()->IsClassScope())
        {
            return true;
        }
    }
    return false;
}

bool Context::EnableNoDeclSpecFunctionDefinition() const
{
    Scope* currentScope = symbolTable->CurrentScope();
    if (currentScope->IsTemplateDeclarationScope())
    {
        Symbol* symbol = currentScope->GetSymbol();
        Symbol* parent = symbol->Parent();
        if (parent->GetScope()->IsNamespaceScope() || parent->GetScope()->IsClassScope())
        {
            return true;
        }
    }
    return false;
}

void Context::PushNode(otava::ast::Node* node_)
{
    nodeStack.push(node);
    node = node_;
}

void Context::PopNode()
{
    node = nodeStack.top();
    nodeStack.pop();
}

void Context::SetDeclarationList(otava::ast::Node* node, DeclarationList* declarations)
{
    declarationMap[node] = declarations;
}

std::unique_ptr<DeclarationList> Context::ReleaseDeclarationList(otava::ast::Node* node)
{
    std::unique_ptr<DeclarationList> declarationList;
    auto it = declarationMap.find(node);
    if (it != declarationMap.cend())
    {
        declarationList.reset(it->second);
    }
    declarationMap.erase(node);
    return declarationList;
}

void Context::PushBoundFunction(BoundFunctionNode* boundFunction_)
{
    boundFunctionStack.push(std::unique_ptr<BoundFunctionNode>(boundFunction.release()));
    boundFunction.reset(boundFunction_);
    boundFunction->SetSerial(boundFunctionSerial++);
}

void Context::PopBoundFunction()
{
    boundFunction.reset(boundFunctionStack.top().release());
    boundFunctionStack.pop();
}

void Context::AddBoundVTabFunction(BoundFunctionNode* node)
{
    boundVTabFunctions.push_back(std::unique_ptr<BoundFunctionNode>(node));
}

void Context::ClearBoundVTabFunctions()
{
    boundVTabFunctions.clear();
}

void Context::PushSwitchCondType(TypeSymbol* switchCondType_)
{
    switchCondTypeStack.push(switchCondType);
    switchCondType = switchCondType_;
}

void Context::PopSwitchCondType()
{
    switchCondType = switchCondTypeStack.top();
    switchCondTypeStack.pop();
}

void Context::SetInstantiationQueue(InstantiationQueue* instantiationQueue_)
{
    instantiationQueue = instantiationQueue_;
}

void Context::AddTemporaryAliasType(AliasTypeSymbol* temporaryAliasType)
{
    temporaryAliasTypes.push_back(temporaryAliasType);
}

void Context::ClearTemporaryAliasTypes()
{
    temporaryAliasTypes.clear();
}

FunctionSymbol* Context::GetSpecialization(otava::ast::Node* functionNode)  const
{
    auto it = specializationMap.find(functionNode);
    if (it != specializationMap.end())
    {
        FunctionSymbol* specialization = it->second;
        return specialization;
    }
    else
    {
        return nullptr;
    }
}

void Context::SetSpecialization(FunctionSymbol* specialization, otava::ast::Node* functionNode)
{
    if (functionNode)
    {
        specializationMap[functionNode] = specialization;
    }
}

void Context::RemoveSpecialization(otava::ast::Node* functionNode)
{
    specializationMap.erase(functionNode);
}

ClassTemplateSpecializationSymbol* Context::GetClassTemplateSpecialization(otava::ast::Node* functionNode) const
{
    auto it = classTemplateSpecializationMap.find(functionNode);
    if (it != classTemplateSpecializationMap.end())
    {
        ClassTemplateSpecializationSymbol* sp = it->second;
        return sp;
    }
    else
    {
        return nullptr;
    }
}

void Context::SetClassTemplateSpecialization(otava::ast::Node* functionNode, ClassTemplateSpecializationSymbol* sp)
{
    if (functionNode)
    {
        classTemplateSpecializationMap[functionNode] = sp;
    }
}

void Context::RemoveClassTemplateSpecialization(otava::ast::Node* functionNode)
{
    classTemplateSpecializationMap.erase(functionNode);
}

void Context::SetInstantiationIrName(const std::string& instantiationIrName_)
{
    instantiationIrName = instantiationIrName_;
}

void Context::PushTemplateParameterMap(std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>* templateParamMap)
{
    templateParameterMapStack.push(templateParameterMap);
    templateParameterMap = templateParamMap;
}

void Context::PopTemplateParameterMap()
{
    templateParameterMap = templateParameterMapStack.top();
    templateParameterMapStack.pop();
}

} // namespace otava::symbols
