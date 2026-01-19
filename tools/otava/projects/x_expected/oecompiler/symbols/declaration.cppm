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

std::expected<bool, int> ProcessSimpleDeclaration(otava::ast::Node* node, otava::ast::Node* functionNode, Context* context);
std::expected<Declaration, int> ProcessFunctionDeclaration(otava::ast::Node* node, Context* context);
std::expected<Declaration, int> ProcessParameterDeclaration(otava::ast::Node* node, Context* context);
std::expected<Declaration, int> ProcessExceptionDeclaration(otava::ast::Node* node, Context* context);
std::expected<bool, int> ProcessMemberDeclaration(otava::ast::Node* node, otava::ast::Node* functionNode, Context* context);
std::expected<int, int> BeginFunctionDefinition(otava::ast::Node* declSpecifierSequence, otava::ast::Node* declarator, otava::ast::Node* functionNode, 
    otava::ast::Node* specifierNode, bool& get, Context* context);
std::expected<bool, int> EndFunctionDefinition(otava::ast::Node* functionDefinitionNode, int scopes, Context* context);
std::expected<bool, int> ProcessMemberFunctionDefinition(otava::ast::Node* node, Context* context);
std::expected<TypeSymbol*, int> ProcessExplicitInstantiationDeclaration(otava::ast::Node* node, Context* context);
std::expected<TypeSymbol*, int> MapType(FunctionSymbol* functionSymbol, TypeSymbol* type, Context* context);
std::expected<bool, int> GenerateDynamicInitialization(VariableSymbol* variable, BoundExpressionNode* initializer, const soul::ast::SourcePos& sourcePos, Context* context);
std::expected<std::unique_ptr<BoundFunctionCallNode>, int> MakeAtExitForVariable(VariableSymbol* variable, const soul::ast::SourcePos& sourcePos, Context* context);
std::expected<bool, int> AddConvertingConstructorToConversionTable(FunctionSymbol* functionSymbol, const soul::ast::SourcePos& sourcePos, Context* context);
bool HasNoReturnAttribute(otava::ast::Node* attributes);

std::expected<bool, int> Write(Writer& writer, DeclarationFlags flags);
std::expected<bool, int> Read(Reader& reader, DeclarationFlags& flags);

std::unexpected<int> ReturnDeclarationParsingError(const soul::ast::SourcePos& sourcePos, Context* context);

std::expected<bool, int> ProcessLinkageSpecification(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
