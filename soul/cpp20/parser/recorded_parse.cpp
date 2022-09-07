// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.parser.recorded.parse;

import soul.cpp20.token;
import soul.cpp20.parser.statement;
import soul.cpp20.lexer;
import soul.cpp20.symbols;

namespace soul::cpp20::parser::recorded::parse {

void RecordedParse(soul::cpp20::ast::CompoundStatementNode* node, soul::cpp20::symbols::Context* context);

void Init()
{
    soul::cpp20::symbols::SetRecordedParseFn(RecordedParse);
}
    
soul::ast::lexer::pos::pair::LexerPosPair RecordCompoundStatement(soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>& lexer)
{
    int64_t start = lexer.GetPos();
    int braceCount = 0;
    while (*lexer != soul::lexer::END_TOKEN)
    {
        if (*lexer == soul::cpp20::token::LBRACE)
        {
            ++braceCount;
        }
        else if (*lexer == soul::cpp20::token::RBRACE)
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

void PushSavedCompoundStatementNode(soul::cpp20::ast::CompoundStatementNode* node, soul::cpp20::symbols::Context* context)
{
    context->PushNode(node);
}

void PopSavedCompoundStatementNode(soul::cpp20::symbols::Context* context)
{
    context->PopNode();
}

soul::cpp20::ast::CompoundStatementNode* GetSavedCompoundStatementNode(soul::cpp20::symbols::Context* context)
{
    soul::cpp20::ast::CompoundStatementNode* compoundStatementNode = nullptr;
    soul::cpp20::ast::Node* n = context->GetNode();
    if (n && n->IsCompoundStatementNode())
    {
        return static_cast<soul::cpp20::ast::CompoundStatementNode*>(n);
    }
    else
    {
        throw std::runtime_error("context has no compound statement node");
    }
    return compoundStatementNode;
}

void RecordedParse(soul::cpp20::ast::CompoundStatementNode* node, soul::cpp20::symbols::Context* context)
{
    context->PushSetFlag(soul::cpp20::symbols::ContextFlags::parseSavedMemberFunctionBody);
    PushSavedCompoundStatementNode(node, context);
    using Lexer = soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>;
    soul::cpp20::parser::statement::StatementParser<Lexer>::CompoundStatement(*static_cast<Lexer*>(context->GetLexer()), context);
    PopSavedCompoundStatementNode(context);
    context->PopFlags();
}

} // namespace soul::cpp20::parser::recorded::parse
