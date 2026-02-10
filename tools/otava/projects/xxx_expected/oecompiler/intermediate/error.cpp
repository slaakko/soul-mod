// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.error;

namespace otava::intermediate {

std::unexpected<int> Error(const std::string& message, const soul::ast::Span& span, Context* context)
{
    if (span.IsValid())
    {
        soul::ast::LineColLen lineColLen;
        const std::vector<int>* lineStartIndeces = context->GetFileMap().LineStartIndeces(context->FileId());
        if (lineStartIndeces)
        {
            lineColLen = soul::ast::SpanToLineColLen(span, *lineStartIndeces);
        }
        if (lineColLen.IsValid())
        {
            std::expected<std::string, int> rv = context->ErrorLines(lineColLen);
            if (!rv) return std::unexpected<int>(rv.error());
            std::string errorLines = std::move(*rv);
            return std::unexpected<int>(util::AllocateError(message + " at\n'" + context->FilePath() + "':" + std::to_string(lineColLen.line) + ":\n" + errorLines));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError(message));
        }
    }
    else
    {
        return std::unexpected<int>(util::AllocateError(message));
    }
}

std::unexpected<int> Error(const std::string& message, const soul::ast::Span& span, Context* context, const soul::ast::Span& refSpan)
{
    if (span.IsValid() && refSpan.IsValid())
    {
        soul::ast::LineColLen lineColLen;
        soul::ast::LineColLen refLineColLen;
        const std::vector<int>* lineStartIndeces = context->GetFileMap().LineStartIndeces(context->FileId());
        if (lineStartIndeces)
        {
            lineColLen = soul::ast::SpanToLineColLen(span, *lineStartIndeces);
            refLineColLen = soul::ast::SpanToLineColLen(refSpan, *lineStartIndeces);
        }
        if (lineColLen.IsValid() && refLineColLen.IsValid())
        {
            std::expected<std::string, int> rv = context->ErrorLines(lineColLen);
            if (!rv) return std::unexpected<int>(rv.error());
            std::string errorLines = std::move(*rv);
            std::expected<std::string, int> refRv = context->ErrorLines(refLineColLen);
            if (!refRv) return std::unexpected<int>(refRv.error());
            std::string refErrorLines = std::move(*refRv);
            return std::unexpected<int>(util::AllocateError(message + " at\n'" + context->FilePath() + "':" + std::to_string(lineColLen.line) + ":\n" +
                errorLines + ": see reference line " + std::to_string(refLineColLen.line) + ":\n" + refErrorLines));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError(message));
        }
    }
    else
    {
        return std::unexpected<int>(util::AllocateError(message));
    }
}

void Warning(const std::string& message, const soul::ast::Span& span, Context* context)
{
    if (span.IsValid())
    {
        soul::ast::LineColLen lineColLen;
        const std::vector<int>* lineStartIndeces = context->GetFileMap().LineStartIndeces(context->FileId());
        if (lineStartIndeces)
        {
            lineColLen = soul::ast::SpanToLineColLen(span, *lineStartIndeces);
        }
        if (lineColLen.IsValid())
        {
            std::cout << "warning: " << message << " at\n'" + context->FilePath() << "':" << std::to_string(lineColLen.line) << ":\n" <<
                context->ErrorLines(lineColLen) << "\n";
        }
        else
        {
            std::cout << "warning: " << message << "\n";
        }
    }
    else
    {
        std::cout << "warning: " << message << "\n";
    }
}

} // otava::intermediate
