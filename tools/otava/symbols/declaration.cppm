// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.declaration;

import std;
import otava.ast;
import otava.symbols.declarator;
import otava.symbols.type.symbol;
import otava.symbols.bound.tree;
import soul.ast.source.pos;

export namespace otava::symbols {

enum class DeclarationFlags : std::int32_t
{
    none = 0,
    staticFlag = 1 << 0,
    threadLocalFlag = 1 << 1,
    externFlag = 1 << 2,
    mutableFlag = 1 << 3,
    virtualFlag = 1 << 4,
    explicitFlag = 1 << 5,
    inlineFlag = 1 << 6,
    friendFlag = 1 << 7,
    typedefFlag = 1 << 8,
    constExprFlag = 1 << 9,
    constEvalFlag = 1 << 10,
    constInitFlag = 1 << 11,
    constFlag = 1 << 12,
    volatileFlag = 1 << 13,
    lvalueRefFlag = 1 << 14,
    rvalueRefFlag = 1 << 15,

    charFlag = 1 << 16,
    char8Flag = 1 << 17,
    char16Flag = 1 << 18,
    char32Flag = 1 << 19,
    wcharFlag = 1 << 20,
    boolFlag = 1 << 21,
    shortFlag = 1 << 22,
    intFlag = 1 << 23,
    longFlag = 1 << 24,
    longLongFlag = 1 << 25,
    signedFlag = 1 << 26,
    unsignedFlag = 1 << 27,
    floatFlag = 1 << 28,
    doubleFlag = 1 << 29,
    voidFlag = 1 << 30,
    autoFlag = 1 << 31,

    fundamentalTypeFlags =
        charFlag | char8Flag | char16Flag | char32Flag | wcharFlag | boolFlag | shortFlag | intFlag | longFlag | longLongFlag | signedFlag | unsignedFlag | floatFlag | doubleFlag |
        voidFlag | autoFlag,

    typedefFlagMask = staticFlag | threadLocalFlag | externFlag | mutableFlag | virtualFlag | explicitFlag | inlineFlag | friendFlag | constExprFlag | constEvalFlag | constInitFlag,

    cvQualifierFlagMask = constFlag | volatileFlag
};

constexpr DeclarationFlags operator|(DeclarationFlags left, DeclarationFlags right)
{
    return DeclarationFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr DeclarationFlags operator&(DeclarationFlags left, DeclarationFlags right)
{
    return DeclarationFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr DeclarationFlags operator~(DeclarationFlags flags)
{
    return DeclarationFlags(~std::int32_t(flags));
}

class Context;
class Writer;
class Reader;

std::string DeclarationFlagStr(DeclarationFlags flags);

void ProcessSimpleDeclaration(otava::ast::Node* node, otava::ast::Node* functionNode, Context* context);
Declaration ProcessFunctionDeclaration(otava::ast::Node* node, Context* context);
Declaration ProcessParameterDeclaration(otava::ast::Node* node, Context* context);
Declaration ProcessExceptionDeclaration(otava::ast::Node* node, Context* context);
void ProcessMemberDeclaration(otava::ast::Node* node, otava::ast::Node* functionNode, Context* context);
int BeginFunctionDefinition(otava::ast::Node* declSpecifierSequence, otava::ast::Node* declarator, otava::ast::Node* functionNode, otava::ast::Node* specifierNode, 
    bool& get, Context* context);
void EndFunctionDefinition(otava::ast::Node* functionDefinitionNode, int scopes, Context* context);
void ProcessMemberFunctionDefinition(otava::ast::Node* node, Context* context);
TypeSymbol* ProcessExplicitInstantiationDeclaration(otava::ast::Node* node, Context* context);
TypeSymbol* MapType(FunctionSymbol* functionSymbol, TypeSymbol* type, Context* context);
void GenerateDynamicInitialization(VariableSymbol* variable, BoundExpressionNode* initializer, const soul::ast::SourcePos& sourcePos, Context* context);
std::unique_ptr<BoundFunctionCallNode> MakeAtExitForVariable(VariableSymbol* variable, const soul::ast::SourcePos& sourcePos, Context* context);
void AddConvertingConstructorToConversionTable(FunctionSymbol* functionSymbol, const soul::ast::SourcePos& sourcePos, Context* context);
bool HasNoreturnAttribute(otava::ast::Node* attributes);

void Write(Writer& writer, DeclarationFlags flags);
void Read(Reader& reader, DeclarationFlags& flags);

void ThrowDeclarationParsingError(const soul::ast::SourcePos& sourcePos, Context* context);

void ProcessLinkageSpecification(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
