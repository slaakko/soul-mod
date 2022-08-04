// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.context;

import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.scope;
import soul.cpp20.symbols.symbol;

namespace soul::cpp20::symbols {

Context::Context() : symbolTable(nullptr), lexer(nullptr), flags(ContextFlags::none)
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

bool Context::IsConstructorNameNode(soul::cpp20::ast::Node* node) const
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
    return false;
}

} // namespace soul::cpp20::symbols
