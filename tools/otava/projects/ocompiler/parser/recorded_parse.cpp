// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.parser.recorded.parse;

import otava.token;
import otava.parser.statement;
import otava.parser.classes;
import otava.lexer;
import otava.symbols;
import util;

namespace otava::parser::recorded::parse {

std::expected<bool, int> RecordedParseCompoundStatement(otava::ast::CompoundStatementNode* node, otava::symbols::Context* context);

std::expected<bool, int> RecordedParseCtorInitializer(otava::ast::ConstructorInitializerNode* node, otava::symbols::Context* context);

void Init()
{
    otava::symbols::SetRecordedParseCompoundStatementFn(RecordedParseCompoundStatement);
    otava::symbols::SetRecordedParseCtorInitializerFn(RecordedParseCtorInitializer);
}

std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int> RecordCompoundStatement(soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>& lexer)
{
    std::int64_t start = lexer.GetPos();
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
                    auto rv = ++lexer;
                    if (!rv) return std::unexpected<int>(rv.error());
                    std::int64_t end = lexer.GetPos();
                    return std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int>(soul::ast::lexer::pos::pair::LexerPosPair(start, end));
                }
            }
            else
            {
                lexer.SetPos(start);
                return std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int>(soul::ast::lexer::pos::pair::LexerPosPair());
            }
        }
        else if (braceCount == 0)
        {
            lexer.SetPos(start);
            return std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int>(soul::ast::lexer::pos::pair::LexerPosPair());
        }
        auto rv = ++lexer;
        if (!rv) return std::unexpected<int>(rv.error());
    }
    lexer.SetPos(start);
    return std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int>(soul::ast::lexer::pos::pair::LexerPosPair());
}

std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int> RecordCtorInitializer(soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>& lexer)
{
    std::int64_t start = lexer.GetPos();
    while (*lexer != soul::lexer::END_TOKEN)
    {
        if (*lexer == otava::token::LBRACE)
        {
            std::int64_t end = lexer.GetPos();
            return std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int>(soul::ast::lexer::pos::pair::LexerPosPair(start, end));
        }
        else
        {
            auto rv = ++lexer;
            if (!rv) return std::unexpected<int>(rv.error());
        }
    }
    lexer.SetPos(start);
    return std::expected<soul::ast::lexer::pos::pair::LexerPosPair, int>(soul::ast::lexer::pos::pair::LexerPosPair());
}

void PushSavedCompoundStatementNode(otava::ast::CompoundStatementNode* node, otava::symbols::Context* context)
{
    context->PushNode(node);
}

void PopSavedCompoundStatementNode(otava::symbols::Context* context)
{
    context->PopNode();
}

std::expected<otava::ast::CompoundStatementNode*, int> GetSavedCompoundStatementNode(otava::symbols::Context* context)
{
    otava::ast::CompoundStatementNode* compoundStatementNode = nullptr;
    otava::ast::Node* n = context->GetNode();
    if (n && n->IsCompoundStatementNode())
    {
        return std::expected<otava::ast::CompoundStatementNode*, int>(static_cast<otava::ast::CompoundStatementNode*>(n));
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("context has no compound statement node"));
    }
    return std::expected<otava::ast::CompoundStatementNode*, int>(compoundStatementNode);
}

void PushSavedCtorInitializerNode(otava::ast::ConstructorInitializerNode* node, otava::symbols::Context* context)
{
    context->PushNode(node);
}

void PopSavedCtorInitializerNode(otava::symbols::Context* context)
{
    context->PopNode();
}

std::expected<otava::ast::ConstructorInitializerNode*, int> GetSavedCtorInitializerNode(otava::symbols::Context* context)
{
    otava::ast::ConstructorInitializerNode* ctorInitializerNode = nullptr;
    otava::ast::Node* n = context->GetNode();
    if (n && n->IsCtorInitializerNode())
    {
        return std::expected<otava::ast::ConstructorInitializerNode*, int>(static_cast<otava::ast::ConstructorInitializerNode*>(n));
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("context has no constructor initializer node"));
    }
    return std::expected<otava::ast::ConstructorInitializerNode*, int>(ctorInitializerNode);
}

std::expected<bool, int> RecordedParseCompoundStatement(otava::ast::CompoundStatementNode* node, otava::symbols::Context* context)
{
    context->PushSetFlag(otava::symbols::ContextFlags::parseSavedMemberFunctionBody);
    PushSavedCompoundStatementNode(node, context);
    using Lexer = soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>;
    auto rv = otava::parser::statement::StatementParser<Lexer>::CompoundStatement(*static_cast<Lexer*>(context->GetLexer()), context);
    if (!rv) return std::unexpected<int>(rv.error());
    PopSavedCompoundStatementNode(context);
    context->PopFlags();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> RecordedParseCtorInitializer(otava::ast::ConstructorInitializerNode* node, otava::symbols::Context* context)
{
    context->PushSetFlag(otava::symbols::ContextFlags::parseSavedCtorInitializer);
    PushSavedCtorInitializerNode(node, context);
    using Lexer = soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>;
    auto rv = otava::parser::classes::ClassParser<Lexer>::CtorInitializer(*static_cast<Lexer*>(context->GetLexer()), context);
    if (!rv) return std::unexpected<int>(rv.error());
    PopSavedCtorInitializerNode(context);
    context->PopFlags();
    return std::expected<bool, int>(true);
}

} // namespace otava::parser::recorded::parse
