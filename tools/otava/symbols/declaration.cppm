// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.declaration;

import std;
import otava.ast;
import otava.symbols.declarator;
import otava.symbols.symbol;
import otava.symbols.type.symbol;
import otava.symbols.bound.tree;
import soul.ast.source.pos;

export namespace otava::symbols {

class Context;
class Writer;
class Reader;

std::string DeclarationFlagStr(DeclarationFlags flags);

VariableSymbol* ResolveParentVariable(const std::u32string& variableName, const soul::ast::SourcePos& sourcePos, int& level, Context* context);
void ProcessSimpleDeclaration(otava::ast::Node* node, otava::ast::Node* functionNode, Context* context);
Declaration ProcessFunctionDeclaration(otava::ast::Node* node, Context* context);
Declaration ProcessParameterDeclaration(otava::ast::Node* node, Context* context);
Declaration ProcessExceptionDeclaration(otava::ast::Node* node, Context* context);
Declaration ProcessInitCondition(otava::ast::InitConditionNode* initCondition, Context* context);
VariableSymbol* ProcessSimpleDeclarator(SimpleDeclarator* simpleDeclarator, TypeSymbol* type, TypeSymbol* initialierType, 
    Value* value, DeclarationFlags flags, Context* context);
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
bool HasNoReturnAttribute(otava::ast::Node* attributes);

void Write(Writer& writer, DeclarationFlags flags);
void Read(Reader& reader, DeclarationFlags& flags);

void ThrowDeclarationParsingError(const soul::ast::SourcePos& sourcePos, Context* context);

void ProcessLinkageSpecification(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
