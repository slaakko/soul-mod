import std;
import soul.xml.dom;

int main()
{
    soul::xml::Element* root = soul::xml::MakeElement("root");
    root->SetAttribute("attr", "value");
    soul::xml::Document doc;
    doc.AppendChild(root);
}
