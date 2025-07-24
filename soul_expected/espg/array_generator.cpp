// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.array.generator;

namespace soul_expected::spg {

class ArrayGeneratorVisitor : public soul_expected::ast::spg::DefaultVisitor
{
public:
    ArrayGeneratorVisitor(util::CodeFormatter& formatter_, int& sn_);
    void Visit(soul_expected::ast::spg::StringParser& parser) override;
    void Visit(soul_expected::ast::spg::CharSetParser& parser) override;
private:
    util::CodeFormatter& formatter;
    int& sn;
};

ArrayGeneratorVisitor::ArrayGeneratorVisitor(util::CodeFormatter& formatter_, int& sn_) : formatter(formatter_), sn(sn_)
{
}

void ArrayGeneratorVisitor::Visit(soul_expected::ast::spg::StringParser& parser)
{
    if (!Valid()) return;
    std::string s = "s" + std::to_string(sn++);
    parser.SetArrayName(s);
    std::expected<bool, int> rv = formatter.Write("static constexpr std::int32_t " + s + "[] = {");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    bool first = true;
    for (char32_t c : parser.Str())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            rv = formatter.Write(", ");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        rv = formatter.Write(std::to_string(static_cast<std::int32_t>(c)));
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    rv = formatter.WriteLine("};");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter.WriteLine();
}

void ArrayGeneratorVisitor::Visit(soul_expected::ast::spg::CharSetParser& parser)
{
    if (!Valid()) return;
    std::string s = "s" + std::to_string(sn++);
    parser.SetArrayName(s);
    std::expected<bool, int> rv = formatter.Write("static constexpr soul_expected::ast::spg::Range " + s + "[] = {");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    bool first = true;
    for (const soul_expected::ast::spg::Range& range : parser.GetCharSet()->Ranges())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            rv = formatter.Write(", ");
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        rv = formatter.Write("{ " + std::to_string(range.first) + ", " + std::to_string(range.last) + " }");
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    rv = formatter.WriteLine("};");
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    formatter.WriteLine();
}

std::expected<bool, int> GenerateArrays(soul_expected::ast::spg::ParserFile& parserFile, util::CodeFormatter& formatter, int& sn)
{
    ArrayGeneratorVisitor visitor(formatter, sn);
    parserFile.Accept(visitor);
    if (!visitor) return std::unexpected<int>(visitor.Error());
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::spg
