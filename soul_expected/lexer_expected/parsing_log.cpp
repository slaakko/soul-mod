// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.lexer.parsing.log;

namespace soul_expected::lexer {

ParsingLog::ParsingLog() : maxLineLength(80)
{
}

ParsingLog::ParsingLog(int maxLineLength_) : maxLineLength(maxLineLength_)
{
}

ParsingLog::~ParsingLog()
{
}

int ParsingLog::MaxLineLength() const
{
    return maxLineLength;
}

} // namespace soul_expected::lexer
