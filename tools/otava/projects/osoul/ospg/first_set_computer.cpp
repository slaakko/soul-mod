// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.first.set.computer;

import std;

namespace soul::spg {

class FirstSetComputer : public soul::ast::spg::DefaultVisitor
{
public:
    FirstSetComputer();
    bool Changed() const { return changed; }
    void Visit(soul::ast::spg::ChoiceParser& parser) override;
    void Visit(soul::ast::spg::CaseParser& parser) override;
    void Visit(soul::ast::spg::SwitchParser& parser) override;
    void Visit(soul::ast::spg::SequenceParser& parser) override;
    void Visit(soul::ast::spg::DifferenceParser& parser) override;
    void Visit(soul::ast::spg::ListParser& parser) override;
    void Visit(soul::ast::spg::LookaheadParser& parser) override;
    void Visit(soul::ast::spg::KleeneParser& parser) override;
    void Visit(soul::ast::spg::PositiveParser& parser) override;
    void Visit(soul::ast::spg::OptionalParser& parser) override;
    void Visit(soul::ast::spg::ExpectationParser& parser) override;
    void Visit(soul::ast::spg::ActionParser& parser) override;
    void Visit(soul::ast::spg::NonterminalParser& parser) override;
    void Visit(soul::ast::spg::EmptyParser& parser) override;
    void Visit(soul::ast::spg::AnyParser& parser) override;
    void Visit(soul::ast::spg::TokenParser& parser) override;
    void Visit(soul::ast::spg::CharParser& parser) override;
    void Visit(soul::ast::spg::StringParser& parser) override;
    void Visit(soul::ast::spg::CharSetParser& parser) override;
    void Visit(soul::ast::spg::GroupParser& parser) override;
    void Visit(soul::ast::spg::RuleParser& parser) override;
    void Visit(soul::ast::spg::GrammarParser& parser) override;
private:
    bool changed;
    std::set<soul::ast::spg::Parser*> visited;
};

FirstSetComputer::FirstSetComputer() : changed(false)
{
}

void FirstSetComputer::Visit(soul::ast::spg::ChoiceParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::CaseParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::SwitchParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::SequenceParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::DifferenceParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::ListParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::LookaheadParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::KleeneParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::PositiveParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::OptionalParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::ExpectationParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::ActionParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::NonterminalParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::EmptyParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::AnyParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::TokenParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::CharParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::StringParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::CharSetParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::GroupParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::RuleParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

void FirstSetComputer::Visit(soul::ast::spg::GrammarParser& parser)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = parser.ComputeFirst(changed, visited);
    if (!rv)
    {
        SetError(rv.error());
        return;;
    }
}

std::expected<bool, int> ComputeFirstSets(soul::ast::spg::SpgFile* spgFile, bool verbose)
{
    if (verbose)
    {
        std::cout << "computing first sets..." << "\n";
    }
    int round = 1;
    bool changed = true;
    while (changed)
    {
        if (verbose)
        {
            std::cout << "round " << round << "..." << "\n";
        }
        FirstSetComputer firstSetComputer;
        spgFile->Accept(firstSetComputer);
        if (!firstSetComputer.Valid()) return std::unexpected<int>(firstSetComputer.Error());
        changed = firstSetComputer.Changed();
        ++round;
    }
    return std::expected<bool, int>(true);
}

} // namespace soul::spg
