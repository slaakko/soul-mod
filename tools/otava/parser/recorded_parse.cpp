// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.parser.recorded.parse;

import otava.token;
import otava.parser.statement;
import otava.parser.classes;
import otava.lexer;
import otava.symbols;

namespace otava::parser::recorded::parse {

void RecordedParseCompoundStatement(otava::ast::CompoundStatementNode* node, otava::symbols::Context* context);

void RecordedParseCtorInitializer(otava::ast::ConstructorInitializerNode* node, otava::symbols::Context* context);

void Init()
{
    otava::symbols::SetRecordedParseCompoundStatementFn(RecordedParseCompoundStatement);
    otava::symbols::SetRecordedParseCtorInitializerFn(RecordedParseCtorInitializer);
}
    
soul::ast::lexer::pos::pair::LexerPosPair RecordCompoundStatement(soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>& lexer)
{
    int64_t start = lexer.GetPos();
    int braceCount = 0;
    while (*lexer != soul::lexer::END_TOKEN)
    {
        if (*lexer == otava::token::LBRACE)
        {
            ++braceCount;
        }
        else if (*lexer == otava::token::RBRACE)
        {
            if (braceCount > 0)
            {
                --braceCount;
                if (braceCount == 0)
                {
                    ++lexer;
                    int64_t end = lexer.GetPos();
                    return soul::ast::lexer::pos::pair::LexerPosPair(start, end);
                }
            }
            else
            {
                lexer.SetPos(start);
                return soul::ast::lexer::pos::pair::LexerPosPair();
            }
        }
        else if (braceCount == 0)
        {
            lexer.SetPos(start);
            return soul::ast::lexer::pos::pair::LexerPosPair();
        }
        ++lexer;
    }
    lexer.SetPos(start);
    return soul::ast::lexer::pos::pair::LexerPosPair();
}

soul::ast::lexer::pos::pair::LexerPosPair RecordCtorInitializer(soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>& lexer)
{
    int64_t start = lexer.GetPos();
    while (*lexer != soul::lexer::END_TOKEN)
    {
        if (*lexer == otava::token::LBRACE)
        {
            int64_t end = lexer.GetPos();
            return soul::ast::lexer::pos::pair::LexerPosPair(start, end);
        }
        else
        {
            ++lexer;
        }
    }
    lexer.SetPos(start);
    return soul::ast::lexer::pos::pair::LexerPosPair();
}

void PushSavedCompoundStatementNode(otava::ast::CompoundStatementNode* node, otava::symbols::Context* context)
{
    context->PushNode(node);
}

void PopSavedCompoundStatementNode(otava::symbols::Context* context)
{
    context->PopNode();
}

otava::ast::CompoundStatementNode* GetSavedCompoundStatementNode(otava::symbols::Context* context)
{
    otava::ast::CompoundStatementNode* compoundStatementNode = nullptr;
    otava::ast::Node* n = context->GetNode();
    if (n && n->IsCompoundStatementNode())
    {
        return static_cast<otava::ast::CompoundStatementNode*>(n);
    }
    else
    {
        throw std::runtime_error("context has no compound statement node");
    }
    return compoundStatementNode;
}

void PushSavedCtorInitializerNode(otava::ast::ConstructorInitializerNode* node, otava::symbols::Context* context)
{
    context->PushNode(node);
}

void PopSavedCtorInitializerNode(otava::symbols::Context* context)
{
    context->PopNode();
}

otava::ast::ConstructorInitializerNode* GetSavedCtorInitializerNode(otava::symbols::Context* context)
{
    otava::ast::ConstructorInitializerNode* ctorInitializerNode = nullptr;
    otava::ast::Node* n = context->GetNode();
    if (n && n->IsCtorInitializerNode())
    {
        return static_cast<otava::ast::ConstructorInitializerNode*>(n);
    }
    else
    {
        throw std::runtime_error("context has no constructor initializer node");
    }
    return ctorInitializerNode;
}

void RecordedParseCompoundStatement(otava::ast::CompoundStatementNode* node, otava::symbols::Context* context)
{
    context->PushSetFlag(otava::symbols::ContextFlags::parseSavedMemberFunctionBody);
    PushSavedCompoundStatementNode(node, context);
    using Lexer = soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>;
    otava::parser::statement::StatementParser<Lexer>::CompoundStatement(*static_cast<Lexer*>(context->GetLexer()), context);
    PopSavedCompoundStatementNode(context);
    context->PopFlags();
}

void RecordedParseCtorInitializer(otava::ast::ConstructorInitializerNode* node, otava::symbols::Context* context)
{
    context->PushSetFlag(otava::symbols::ContextFlags::parseSavedCtorInitializer);
    PushSavedCtorInitializerNode(node, context);
    using Lexer = soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>;
    otava::parser::classes::ClassParser<Lexer>::CtorInitializer(*static_cast<Lexer*>(context->GetLexer()), context);
    PopSavedCtorInitializerNode(context);
    context->PopFlags();
}

} // namespace otava::parser::recorded::parse
