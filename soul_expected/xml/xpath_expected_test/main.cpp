import std;
import util_expected;
import soul_expected.xml.dom.parser;
import soul_expected.xml.xpath;

int main()
{
    auto u = util::Init();
    if (!u)
    {
        std::cerr << util::GetErrorMessage(u.error()) << "\n";
        return 1;
    }
    auto f = util::GetFullPath("D:\\work\\soul-mod\\soul_expected\\test\\espg_test\\parser_file.parser.xml");
    if (!f)
    {
        std::cerr << util::GetErrorMessage(f.error()) << "\n";
        return 1;
    }
    std::string file = *f;
    auto p = soul_expected::xml::ParseXmlFile(file);
    if (!p)
    {
        std::cerr << util::GetErrorMessage(p.error()) << "\n";
        return 1;
    }
    auto d = p->get();
    auto ns = soul_expected::xml::xpath::EvaluateToNodeSet("/parserFile/grammar", d);
    if (!ns)
    {
        std::cerr << util::GetErrorMessage(ns.error()) << "\n";
        return 1;
    }
    soul_expected::xml::xpath::NodeSet* nodeSet = ns->get();
    int n = nodeSet->Count();
    for (int i = 0; i < n; ++i)
    {
        auto nr = nodeSet->GetNode(i);
        if (!nr)
        {
            std::cerr << util::GetErrorMessage(nr.error()) << "\n";
            return 1;
        }
        auto node = *nr;
        if (node->IsElementNode())
        {
            auto element = static_cast<soul_expected::xml::Element*>(node);
            std::cout << element->Name() << " " << element->GetAttribute("name") << "\n";
        }
    }
    util::Done();
}