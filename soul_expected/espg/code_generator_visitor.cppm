// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.code.generator.visitor;

import soul_expected.spg.nonterminal.info;
import soul_expected.ast.spg;
import soul_expected.lexer.file.map;
import util_expected;
import std;

export namespace soul_expected::spg {

enum class CodeGenerationStage
{
    generateInterface, generateImplementation
};

class CodeGeneratorVisitor : public soul_expected::ast::spg::DefaultVisitor
{
public:
    CodeGeneratorVisitor(soul_expected::ast::spg::SpgFile* spgFile_, bool verbose_, bool noDebugSupport_, const std::string& version_, 
        soul_expected::lexer::FileMap& fileMap_);
    void Visit(soul_expected::ast::spg::ChoiceParser& parser) override;
    void Visit(soul_expected::ast::spg::SwitchParser& parser) override;
    void Visit(soul_expected::ast::spg::CaseParser& parser) override;
    void Visit(soul_expected::ast::spg::SequenceParser& parser) override;
    void Visit(soul_expected::ast::spg::DifferenceParser& parser) override;
    void Visit(soul_expected::ast::spg::ListParser& parser) override;
    void Visit(soul_expected::ast::spg::LookaheadParser& parser) override;
    void Visit(soul_expected::ast::spg::KleeneParser& parser) override;
    void Visit(soul_expected::ast::spg::PositiveParser& parser) override;
    void Visit(soul_expected::ast::spg::OptionalParser& parser) override;
    void Visit(soul_expected::ast::spg::ExpectationParser& parser) override;
    void Visit(soul_expected::ast::spg::ActionParser& parser) override;
    void Visit(soul_expected::ast::spg::NonterminalParser& parser) override;
    void Visit(soul_expected::ast::spg::EmptyParser& parser) override;
    void Visit(soul_expected::ast::spg::AnyParser& parser) override;
    void Visit(soul_expected::ast::spg::TokenParser& parser) override;
    void Visit(soul_expected::ast::spg::CharParser& parser) override;
    void Visit(soul_expected::ast::spg::StringParser& parser) override;
    void Visit(soul_expected::ast::spg::CharSetParser& parser) override;
    void Visit(soul_expected::ast::spg::GroupParser& parser) override;
    void Visit(soul_expected::ast::spg::RuleParser& parser) override;
    void Visit(soul_expected::ast::spg::GrammarParser& parser) override;
    void Visit(soul_expected::ast::spg::ParserFile& parserFile) override;
protected:
    soul_expected::ast::spg::SpgFile* spgFile;
    bool verbose;
    bool noDebugSupport;
    std::string version;
    util::CodeFormatter* formatter;
    CodeGenerationStage stage;
    soul_expected::ast::spg::GrammarParser* currentParser;
    soul_expected::ast::spg::RuleParser* currentRule;
    std::vector<NonterminalInfo> nonterminalInfos;
    int parentMatchNumber;
    int setParentMatchNumber;
    int sn;
    soul_expected::lexer::FileMap& fileMap;
};

} // namespace soul_expected::spg
