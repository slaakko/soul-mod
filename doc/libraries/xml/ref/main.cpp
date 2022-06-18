// main.cpp:

import std.core;
import util;
import soul.xml.dom;
import soul.xml.dom.parser;
import soul.xml.xpath;

int main()
{
    try
    {
        util::Init();
        std::unique_ptr<soul::xml::Document> doc = soul::xml::ParseXmlFile("C:/soul-4.0.0/soul/xml/xml_test_data/library.xml");
        std::unique_ptr<soul::xml::xpath::NodeSet> nodeSet = soul::xml::xpath::EvaluateToNodeSet("//object/name", doc.get());
        int n = nodeSet->Count();
        for (int i = 0; i < n; ++i)
        {
            soul::xml::Node* node = nodeSet->GetNode(i);
            if (node->IsElementNode())
            {
                soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
                std::cout << element->GetAttribute("value") << std::endl;
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
    return 0;
}
