// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.index;

import std;
import soul_expected.xml.visitor;
import soul_expected.xml.document;
import soul_expected.xml.element;

namespace soul_expected::xml {

class BuildIndexVisitor : public Visitor
{
public:
    BuildIndexVisitor(std::map<std::string, Element*>& index_);
    void BeginVisit(Element& element) override;
private:
    std::map<std::string, Element*>& index;
};

BuildIndexVisitor::BuildIndexVisitor(std::map<std::string, Element*>& index_) : index(index_)
{
}

void BuildIndexVisitor::BeginVisit(Element& element)
{
    std::string id = element.GetAttribute("id");
    if (!id.empty())
    {
        index[id] = &element;
    }
}

void BuildIndex(Document* document)
{
    BuildIndexVisitor visitor(document->Index());
    document->Accept(visitor);
}

} // namespace soul_expected::xml
