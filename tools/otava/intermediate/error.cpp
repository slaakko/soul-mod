// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.error;

import otava.intermediate.context;

namespace otava::intermediate {

void Error(const std::string& message, const SourcePos& sourcePos, Context* context)
{
    throw std::runtime_error(message + " at\n'" + context->FilePath() + "':" + std::to_string(sourcePos.line) + ":\n" +
        context->ErrorLines(sourcePos));
}

void Error(const std::string& message, const SourcePos& sourcePos, Context* context, const SourcePos& refSourcePos)
{
    throw std::runtime_error(message + " at\n'" + context->FilePath() + "':" + std::to_string(sourcePos.line) + ":\n" +
        context->ErrorLines(sourcePos) + ": see reference line " + std::to_string(refSourcePos.line) + ":\n" +
        context->ErrorLines(refSourcePos));
}

} // otava::intermediate
