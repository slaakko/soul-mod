// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.parser.recorded.parse;

import std.core;
import soul.cpp20.ast.statement;
import soul.ast.source.pos;
import soul.lexer;
import soul.cpp20.lexer;
import soul.cpp20.symbols.context;
import soul.ast.lexer.pos.pair;

export namespace soul::cpp20::parser::recorded::parse {

soul::ast::lexer::pos::pair::LexerPosPair RecordCompoundStatement(soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>& lexer);
void PushSavedCompoundStatementNode(soul::cpp20::ast::CompoundStatementNode* node, soul::cpp20::symbols::Context* context);
void PopSavedCompoundStatementNode(soul::cpp20::symbols::Context* context);
soul::cpp20::ast::CompoundStatementNode* GetSavedCompoundStatementNode(soul::cpp20::symbols::Context* context);
void RecordedParse(soul::cpp20::ast::CompoundStatementNode* node, soul::cpp20::symbols::Context* context);

} // namespace soul::cpp20::parser::recorded::parse
