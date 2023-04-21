// =================================
// Copyright (c) 2023 Seppo Laakko
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
    std::string s = "s" + std::to_string(sn++);
    parser.SetArrayName(s);
    formatter.Write("static constexpr int32_t " + s + "[] = {");
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
        formatter.Write(std::to_string(static_cast<int32_t>(c)));
    }
    formatter.WriteLine("};");
    formatter.WriteLine();
}

void ArrayGeneratorVisitor::Visit(soul::ast::spg::CharSetParser& parser)
{
    std::string s = "s" + std::to_string(sn++);
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

void GenerateArrays(soul::ast::spg::ParserFile& parserFile, util::CodeFormatter& formatter, int& sn)
{
    ArrayGeneratorVisitor visitor(formatter, sn);
    parserFile.Accept(visitor);
}

} // namespace soul::spg
