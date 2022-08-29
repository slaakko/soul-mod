// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.parser.recorded.parse;

import soul.cpp20.token;

namespace soul::cpp20::parser::recorded::parse {

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
    int x = 0;
}

void PopSavedCompoundStatementNode(soul::cpp20::symbols::Context* context)
{
    int x = 0;
}

soul::cpp20::ast::CompoundStatementNode* GetSavedCompoundStatementNode(soul::cpp20::symbols::Context* context)
{
    soul::cpp20::ast::CompoundStatementNode* compoundStatementNode = nullptr;
    return compoundStatementNode;
}

void RecordedParse(soul::cpp20::ast::CompoundStatementNode* node, soul::cpp20::symbols::Context* context)
{
    int x = 0;
}

} // namespace soul::cpp20::parser::recorded::parse
