// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.parser.recorded.parse;

namespace soul::cpp20::parser::recorded::parse {

soul::ast::lexer::pos::pair::LexerPosPair RecordCompoundStatement(soul::lexer::LexerBase<char32_t>& lexer)
{
    soul::ast::lexer::pos::pair::LexerPosPair lpp;
    return lpp;
}

void PushSavedCompoundStatementNode(soul::cpp20::ast::CompoundStatementNode* node, soul::cpp20::symbols::Context* context)
{

}

void PopSavedCompoundStatementNode(soul::cpp20::symbols::Context* context)
{

}

soul::cpp20::ast::CompoundStatementNode* GetSavedCompoundStatementNode(soul::cpp20::symbols::Context* context)
{
    soul::cpp20::ast::CompoundStatementNode* compoundStatementNode = nullptr;
    return compoundStatementNode;
}

void RecordedParse(soul::cpp20::ast::CompoundStatementNode* node, soul::cpp20::symbols::Context* context)
{

}

} // namespace soul::cpp20::parser::recorded::parse
