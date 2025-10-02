// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.array.generator;

namespace soul::spg {

class ArrayGeneratorVisitor : public soul::ast::spg::DefaultVisitor
{
public:
    ArrayGeneratorVisitor(util::CodeFormatter& formatter_, int& sn_);
    void Visit(soul::ast::spg::StringParser& parser) override;
    void Visit(soul::ast::spg::CharSetParser& parser) override;
private:
    util::CodeFormatter& formatter;
    int& sn;
};

ArrayGeneratorVisitor::ArrayGeneratorVisitor(util::CodeFormatter& formatter_, int& sn_) : formatter(formatter_), sn(sn_)
{
}

void ArrayGeneratorVisitor::Visit(soul::ast::spg::StringParser& parser)
{
    if (!Valid()) return;
    std::string s = "s" + std::to_string(sn);
    ++sn;
    parser.SetArrayName(s);
    formatter.Write("static constexpr std::int32_t " + s + "[] = {");
    bool first = true;
    for (char32_t c : parser.Str())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.Write(", ");
        }
        formatter.Write(std::to_string(static_cast<std::int32_t>(c)));
    }
    formatter.WriteLine("};");
    formatter.WriteLine();
}

void ArrayGeneratorVisitor::Visit(soul::ast::spg::CharSetParser& parser)
{
    if (!Valid()) return;
    std::string s = "s" + std::to_string(sn);
    ++sn;
    parser.SetArrayName(s);
    formatter.Write("static constexpr soul::ast::spg::Range " + s + "[] = {");
    bool first = true;
    for (const soul::ast::spg::Range& range : parser.GetCharSet()->Ranges())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.Write(", ");
        }
        formatter.Write("{ " + std::to_string(range.first) + ", " + std::to_string(range.last) + " }");
    }
    formatter.WriteLine("};");
    formatter.WriteLine();
}

std::expected<bool, int> GenerateArrays(soul::ast::spg::ParserFile& parserFile, util::CodeFormatter& formatter, int& sn)
{
    ArrayGeneratorVisitor visitor(formatter, sn);
    parserFile.Accept(visitor);
    if (!visitor) return std::unexpected<int>(visitor.Error());
    return std::expected<bool, int>(true);
}

} // namespace soul::spg
