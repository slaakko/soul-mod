module otava.symbols.block;

import otava.symbols.context;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.variable.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;

namespace otava::symbols {

BlockSymbol::BlockSymbol() : ContainerSymbol(SymbolKind::blockSymbol, std::u32string()), blockId(-1)
{
    GetScope()->SetKind(ScopeKind::blockScope);
}

BlockSymbol::~BlockSymbol()
{
    FunctionSymbol* function = ParentFunction();
    if (function)
    {
        for (VariableSymbol* variable : localVariables)
        {
            function->RemoveLocalVariable(variable);
        }
    }
    for (const auto& d : destructorCallMap)
    {
        for (const auto* s : d.second)
        {
            delete s;
        }
    }
}

void BlockSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BlockSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ContainerSymbol::AddSymbol(symbol, sourcePos, context);
    if (symbol->IsVariableSymbol())
    {
        VariableSymbol* variable = static_cast<VariableSymbol*>(symbol);
        if (variable->IsLocalVariable())
        {
            localVariables.push_back(variable);
            FunctionSymbol* function = ParentFunction();
            if (function)
            {
                function->AddLocalVariable(variable);
            }
        }
    }
}

void BlockSymbol::AddDestructorCall(int statementIndex, BoundExpressionNode* destructorCall)
{
    destructorCallMap[statementIndex].push_back(destructorCall);
}

bool BlockSymbol::HasDestructorCalls(int statementIndex) const
{
    return destructorCallMap.find(statementIndex) != destructorCallMap.end();
}

std::vector<BoundExpressionNode*> BlockSymbol::GetDestructorCalls(int statementIndex)
{
    std::vector<BoundExpressionNode*> v = destructorCallMap[statementIndex];
    return v;
}

BlockSymbol* BeginBlock(const soul::ast::SourcePos& sourcePos, int blockId, Context* context)
{
    BlockSymbol* block = context->GetSymbolTable()->BeginBlock(sourcePos, context);
    block->SetBlockId(blockId);
    return block;
}

void EndBlock(Context* context)
{
    context->GetSymbolTable()->EndBlock(context);
}

void RemoveBlock(Context* context)
{
    context->GetSymbolTable()->RemoveBlock();
}

void MapNode(otava::ast::Node* node, Context* context)
{
    context->GetSymbolTable()->MapNode(node);
}

} // namespace otava::symbols
