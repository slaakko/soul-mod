export module otava.symbols.argument.conversion.table;

import std;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import soul.ast.span;

export namespace otava::symbols {

class BoundExpressionNode;
class Context;
class TypeSymbol;
class ClassTypeSymbol;

struct ArgumentMatch;
struct FunctionMatch;

class ArgumentConversion
{
public:
    virtual FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg,
        ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::FullSpan& fullSpan, Context* context) = 0;
};

class ArgumentConversionTable
{
public:
    ArgumentConversionTable();
    void AddArgumentConversion(ArgumentConversion* argumentConversion);
    FunctionSymbol* GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, const soul::ast::FullSpan& fullSpan, Context* context);
    FunctionSymbol* GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, const soul::ast::FullSpan& fullSpan,
        ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, Context* context);
    FunctionSymbol* GetAdjustDeletePtrConversionFn(TypeSymbol* thisPtrBaseType, Context* context);
    FunctionSymbol* GetDynamicPtrCastFn(TypeSymbol* baseClassPtr, TypeSymbol* derivedClassPtr, const soul::ast::FullSpan& fullSpan, Context* context);
private:
    std::vector<std::unique_ptr<ArgumentConversion>> argumentConversions;
    std::vector<std::unique_ptr<FunctionSymbol>> conversionFunctions;
    std::map<TypeSymbol*, FunctionSymbol*> adjustDeletePtrConversionFns;
    std::map<std::pair<TypeSymbol*, TypeSymbol*>, FunctionSymbol*> dynamicPtrCastFns;
};

} // namespace otava::symbols
