// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.context;

import otava.symbols.declarator;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.scope;
import otava.symbols.symbol;
import otava.symbols.bound.tree;

namespace otava::symbols {

Context::Context() : 
    symbolTable(nullptr), 
    lexer(nullptr), 
    flags(ContextFlags::none), 
    node(nullptr), 
    boundCompileUnit(new BoundCompileUnitNode()),
    boundFunction(nullptr), 
    currentCompoundStatement(nullptr)
{
}

void Context::SetLexer(Lexer* lexer_)
{
    lexer = lexer_;
}

void Context::SetSymbolTable(SymbolTable* symbolTable_)
{
    symbolTable = symbolTable_;
}

OperationRepository* Context::GetOperationRepository() const
{
    return GetBoundCompileUnit()->GetOperationRepository();
}

void Context::SetBoundFunction(BoundFunctionNode* boundFunction_)
{
    boundFunction = boundFunction_;
}

void Context::BeginCompoundStatement()
{
    compoundStatementStack.push(currentCompoundStatement);
    currentCompoundStatement = new BoundCompoundStatementNode();
}

void Context::EndCompoundStatement()
{
    if (!compoundStatementStack.top())
    {
        boundFunction->SetBody(currentCompoundStatement);
        currentCompoundStatement = nullptr;
    }
    else
    {
        compoundStatementStack.top()->AddStatement(currentCompoundStatement);
        currentCompoundStatement = compoundStatementStack.top();
        compoundStatementStack.pop();
    }
}

EvaluationContext* Context::GetEvaluationContext()
{
    return symbolTable->GetModule()->GetEvaluationContext();
}

std::string Context::FileName() const
{
    return lexer->FileName();
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
    declarationMap[node] = std::unique_ptr<DeclarationList>(declarations);
}

std::unique_ptr<DeclarationList> Context::ReleaseDeclarationList(otava::ast::Node* node)
{
    std::unique_ptr<DeclarationList> declarationList;
    auto it = declarationMap.find(node);
    if (it != declarationMap.cend())
    {
        declarationList = std::move(it->second);
    }
    declarationMap.erase(node);
    return declarationList;
}

} // namespace otava::symbols
