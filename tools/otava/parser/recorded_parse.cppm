// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.parser.recorded.parse;

import std;
import otava.ast.statement;
import otava.ast.classes;
import soul.ast.source.pos;
import soul.lexer;
import otava.lexer;
import otava.symbols.context;
import soul.ast.lexer.pos.pair;

export namespace otava::parser::recorded::parse {

void Init();
soul::ast::lexer::pos::pair::LexerPosPair RecordCompoundStatement(soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>& lexer);
soul::ast::lexer::pos::pair::LexerPosPair RecordCtorInitializer(soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>& lexer);
void PushSavedCompoundStatementNode(otava::ast::CompoundStatementNode* node, otava::symbols::Context* context);
void PopSavedCompoundStatementNode(otava::symbols::Context* context);
otava::ast::CompoundStatementNode* GetSavedCompoundStatementNode(otava::symbols::Context* context);
void PushSavedCtorInitializerNode(otava::ast::ConstructorInitializerNode* node, otava::symbols::Context* context);
void PopSavedCtorInitializerNode(otava::symbols::Context* context);
otava::ast::ConstructorInitializerNode* GetSavedCtorInitializerNode(otava::symbols::Context* context);
void RecordedParseCompoundStatement(otava::ast::CompoundStatementNode* node, otava::symbols::Context* context);
void RecordedParseCtorInitializer(otava::ast::ConstructorInitializerNode* node, otava::symbols::Context* context);

} // namespace otava::parser::recorded::parse
