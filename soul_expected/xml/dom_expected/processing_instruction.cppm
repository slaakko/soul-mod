// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.processing.instruction;

import std;
import soul_expected.xml.node;

export namespace soul_expected::xml {

class ProcessingInstruction : public Node
{
public:
    ProcessingInstruction(const soul_expected::ast::SourcePos& sourcePos_);
    ProcessingInstruction(const soul_expected::ast::SourcePos& sourcePos_, const std::string& target_, const std::string& data_);
    inline const std::string& Target() const { return target; }
    inline const std::string& Data() const { return data; }
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(util::CodeFormatter& formatter) override;
private:
    std::string target;
    std::string data;
};

ProcessingInstruction* MakeProcessingInstruction(const std::string& target, const std::string& data);

} // namespace soul_expected::xml
