// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.processing.instruction;

import soul_expected.xml.visitor;

namespace soul_expected::xml {

ProcessingInstruction::ProcessingInstruction(const soul_expected::ast::SourcePos& sourcePos_) :
    Node(NodeKind::processingInstructionNode, sourcePos_, "processing_instruction")
{
}

ProcessingInstruction::ProcessingInstruction(const soul_expected::ast::SourcePos& sourcePos_, const std::string& target_, const std::string& data_) :
    Node(NodeKind::processingInstructionNode, sourcePos_, "processing_instruction"), target(target_), data(data_)
{
}

void ProcessingInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ProcessingInstruction::Write(util::CodeFormatter& formatter)
{
    return formatter.WriteLine("<?" + target + " " + data + "?>");
}

ProcessingInstruction* MakeProcessingInstruction(const std::string& target, const std::string& data)
{
    return new ProcessingInstruction(soul_expected::ast::SourcePos(), target, data);
}

} // namespace soul_expected::xml
