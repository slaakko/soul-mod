// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.type_element_generator;

import std;
import otava.symbols;
import soul.xml.dom;
import util;

namespace gendoc {

std::string MakeNsText(otava::symbols::NamespaceSymbol* ns)
{
    if (ns->Name().empty())
    {
        return "<global>";
    }
    else
    {
        return util::ToUtf8(ns->FullName());
    }
}

void AddValue(soul::xml::Element* containerElement, otava::symbols::Value* value, otava::symbols::Module* module, otava::symbols::Symbol* containerSymbol)
{
    if (value->IsSymbolValue())
    {
        otava::symbols::SymbolValue* symbolValue = static_cast<otava::symbols::SymbolValue*>(value);
        otava::symbols::Symbol* symbol = symbolValue->GetSymbol();
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        std::string href;
        if (!module && !containerSymbol)
        {
            href = "../../module/" + symbol->GetModule()->Name() + "/index.html#" + symbol->DocName();
        }
        else if (symbol->GetModule() != module)
        {
            href = "../" + symbol->GetModule()->Name() + "/index.html#" + symbol->DocName();
        }
        else
        {
            href = "#" + symbol->DocName();
        }
        containerElement->AppendChild(soul::xml::MakeText(" = "));
        soul::xml::Text* valueText = soul::xml::MakeText(util::ToUtf8(value->ToString()));
        linkElement->AppendChild(valueText);
        linkElement->SetAttribute("href", href);
        containerElement->AppendChild(linkElement);
    }
    else
    {
        soul::xml::Text* valueText = soul::xml::MakeText(" = " + util::ToUtf8(value->ToString()));
        containerElement->AppendChild(valueText);
    }
}

class TypeElementGenerator : public otava::symbols::DefaultVisitor
{
public:
    TypeElementGenerator(otava::symbols::Module* module_, otava::symbols::Symbol* containerSymbol_);
    soul::xml::Element* GetElement() { return element.release(); }
    void Visit(otava::symbols::NamespaceSymbol& symbol) override;
    void Visit(otava::symbols::ConceptSymbol& symbol) override;
    void Visit(otava::symbols::AliasTypeSymbol& symbol) override;
    void Visit(otava::symbols::ClassGroupSymbol& symbol) override;
    void Visit(otava::symbols::ClassTypeSymbol& symbol) override;
    void Visit(otava::symbols::EnumeratedTypeSymbol& symbol) override;
    void Visit(otava::symbols::ForwardClassDeclarationSymbol& symbol) override;
    void Visit(otava::symbols::CompoundTypeSymbol& symbol) override;
    void Visit(otava::symbols::FundamentalTypeSymbol& symbol) override;
    void Visit(otava::symbols::TemplateParameterSymbol& symbol) override;
    void Visit(otava::symbols::ClassTemplateSpecializationSymbol& symbol) override;
    void Visit(otava::symbols::NestedTypeSymbol& symbol) override;
    void Visit(otava::symbols::FunctionTypeSymbol& symbol) override;
    void CompleteBaseType(otava::symbols::Symbol* symbol);
private:
    otava::symbols::Module* module;
    otava::symbols::Symbol* containerSymbol;
    std::unique_ptr<soul::xml::Element> element;
    bool baseTypeIncomplete;
};

TypeElementGenerator::TypeElementGenerator(otava::symbols::Module* module_, otava::symbols::Symbol* containerSymbol_) :
    module(module_), 
    containerSymbol(containerSymbol_),
    element(soul::xml::MakeElement("span")),
    baseTypeIncomplete(false)
{
    element->SetAttribute("xml:space", "preserve");
    element->SetAttribute("class", "type");
}

void TypeElementGenerator::Visit(otava::symbols::NamespaceSymbol& symbol)
{
    soul::xml::Element* linkElement = soul::xml::MakeElement("a");
    linkElement->SetAttribute("href", "../../namespace/" + symbol.DocName() + "/index.html");
}

void TypeElementGenerator::Visit(otava::symbols::ConceptSymbol& symbol)
{
    // todo
}

void TypeElementGenerator::Visit(otava::symbols::AliasTypeSymbol& symbol)
{
    otava::symbols::Symbol* parent = symbol.Parent();
    soul::xml::Element* linkElement = soul::xml::MakeElement("a");
    std::string href;
    if (!module && !containerSymbol)
    {
        href = "../../module/" + symbol.GetModule()->Name() + "/index.html#" + symbol.DocName();
    }
    else if (symbol.GetModule() != module)
    {
        href = "../" + symbol.GetModule()->Name() + "/index.html#" + symbol.DocName();
    }
    else
    {
        href = "#" + symbol.DocName();
    }
    linkElement->SetAttribute("href", href);
    std::string text;
    if (containerSymbol == symbol.Parent())
    {
        text = util::ToUtf8(symbol.Name());
    }
    else
    {
        text = util::ToUtf8(symbol.FullName());
    }
    soul::xml::Text* linkText = soul::xml::MakeText(text);
    linkElement->AppendChild(linkText);
    element->AppendChild(linkElement);
}

void TypeElementGenerator::Visit(otava::symbols::ClassGroupSymbol& symbol)
{
    if (symbol.Classes().size() == 1)
    {
        symbol.Classes().front()->Accept(*this);
    }
    else if (symbol.ForwardDeclarations().size() == 1)
    {
        symbol.ForwardDeclarations().front()->Accept(*this);
    }
}

void TypeElementGenerator::Visit(otava::symbols::ClassTypeSymbol& symbol)
{
    soul::xml::Element* linkElement = soul::xml::MakeElement("a");
    std::string href;
    if (!module && !containerSymbol)
    {
        href = "../../module/" + symbol.GetModule()->Name() + "/" + symbol.DocName() + ".html";
    }
    else if (symbol.GetModule() != module)
    {
        href = "../" + symbol.GetModule()->Name() + "/" + symbol.DocName() + ".html";
    }
    else
    {
        href = symbol.DocName() + ".html";
    }
    linkElement->SetAttribute("href", href);
    std::string text;
    if (containerSymbol == symbol.Parent())
    {
        text = util::ToUtf8(symbol.Name());
    }
    else
    {
        text = util::ToUtf8(symbol.FullName());
    }
    soul::xml::Text* linkText = soul::xml::MakeText(text);
    linkElement->AppendChild(linkText);
    element->AppendChild(linkElement);
}

void TypeElementGenerator::Visit(otava::symbols::EnumeratedTypeSymbol& symbol)
{
    soul::xml::Element* linkElement = soul::xml::MakeElement("a");
    std::string href;
    if (!module && !containerSymbol)
    {
        href = "../../module/" + symbol.GetModule()->Name() + "/" + symbol.DocName() + ".html";
    }
    else if (symbol.GetModule() != module)
    {
        href = "../" + symbol.GetModule()->Name() + "/" + symbol.DocName() + ".html";
    }
    else
    {
        href = symbol.DocName() + ".html";
    }
    linkElement->SetAttribute("href", href);
    std::string text;
    if (containerSymbol == symbol.Parent())
    {
        text = util::ToUtf8(symbol.Name());
    }
    else
    {
        text = util::ToUtf8(symbol.FullName());
    }
    soul::xml::Text* linkText = soul::xml::MakeText(text);
    linkElement->AppendChild(linkText);
    element->AppendChild(linkElement);
}

void TypeElementGenerator::Visit(otava::symbols::ForwardClassDeclarationSymbol& symbol)
{
    otava::symbols::ClassTypeSymbol* classTypeSymbol = symbol.GetClassTypeSymbol();
    if (classTypeSymbol)
    {
        classTypeSymbol->Accept(*this);
    }
    else
    {
        std::string text;
        if (containerSymbol == symbol.Parent())
        {
            text = util::ToUtf8(symbol.Name());
        }
        else
        {
            text = util::ToUtf8(symbol.FullName());
        }
        element->AppendChild(soul::xml::MakeText(text));
    }
}

void TypeElementGenerator::Visit(otava::symbols::CompoundTypeSymbol& symbol)
{
    if (otava::symbols::HasDerivation(symbol.GetDerivations(), otava::symbols::Derivations::constDerivation))
    {
        element->AppendChild(soul::xml::MakeText("const "));
    }
    if (otava::symbols::HasDerivation(symbol.GetDerivations(), otava::symbols::Derivations::volatileDerivation))
    {
        element->AppendChild(soul::xml::MakeText("volatile "));
    }
    if (!symbol.BaseType())
    {
        return; // TODO
    }
    symbol.BaseType()->Accept(*this);
    int pointerCount = otava::symbols::PointerCount(symbol.GetDerivations());
    if (pointerCount > 0)
    {
        std::string pointerText;
        pointerText.append(pointerCount, '*');
        element->AppendChild(soul::xml::MakeText(pointerText));
    }
    if (otava::symbols::HasDerivation(symbol.GetDerivations(), otava::symbols::Derivations::lvalueRefDerivation))
    {
        element->AppendChild(soul::xml::MakeText("&"));
    }
    else if (otava::symbols::HasDerivation(symbol.GetDerivations(), otava::symbols::Derivations::rvalueRefDerivation))
    {
        element->AppendChild(soul::xml::MakeText("&&"));
    }
    if (baseTypeIncomplete)
    {
        baseTypeIncomplete = false;
        CompleteBaseType(symbol.BaseType());
    }
}

void TypeElementGenerator::Visit(otava::symbols::FundamentalTypeSymbol& symbol)
{
    std::string typeText = util::ToUtf8(symbol.Name());
    soul::xml::Text* text = soul::xml::MakeText(typeText);
    element->AppendChild(text);
}

void TypeElementGenerator::Visit(otava::symbols::TemplateParameterSymbol& symbol)
{
    std::string typeText = util::ToUtf8(symbol.Name());
    soul::xml::Text* text = soul::xml::MakeText(typeText);
    element->AppendChild(text);
}

void TypeElementGenerator::Visit(otava::symbols::ClassTemplateSpecializationSymbol& symbol)
{
    soul::xml::Element* classTemplateElement = GenerateTypeXmlElement(module, containerSymbol, symbol.ClassTemplate());
    element->AppendChild(classTemplateElement);
    soul::xml::Text* langleText = soul::xml::MakeText("<");
    element->AppendChild(langleText);
    bool first = true;
    for (const auto& templateArg : symbol.TemplateArguments())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            soul::xml::Text* commaText = soul::xml::MakeText(", ");
            element->AppendChild(commaText);
        }
        soul::xml::Element* templateArgElement = GenerateTypeXmlElement(module, containerSymbol, templateArg);
        element->AppendChild(templateArgElement);
    }
    soul::xml::Text* rangleText = soul::xml::MakeText(">");
    element->AppendChild(rangleText);
}

void TypeElementGenerator::Visit(otava::symbols::NestedTypeSymbol& symbol)
{
    std::string str;
    otava::symbols::Symbol* templateParameterSymbol = nullptr;
    otava::symbols::Symbol* parentSymbol = symbol.Parent();
    while (parentSymbol)
    {
        if (parentSymbol->IsTemplateParameterSymbol())
        {
            templateParameterSymbol = parentSymbol;
            break;
        }
        parentSymbol = parentSymbol->Parent();
    }
    if (templateParameterSymbol)
    {
        str = util::ToUtf8(templateParameterSymbol->Name()) + "::" + util::ToUtf8(symbol.Name());
    }
    else
    {
        str = util::ToUtf8(symbol.FullName());
    }
    soul::xml::Text* text = soul::xml::MakeText(str);
    element->AppendChild(text);
}

void TypeElementGenerator::Visit(otava::symbols::FunctionTypeSymbol& symbol)
{
    soul::xml::Element* returnTypeElement = GenerateTypeXmlElement(module, containerSymbol, symbol.ReturnType());
    element->AppendChild(returnTypeElement);
    element->AppendChild(soul::xml::MakeText(" ("));
    baseTypeIncomplete = true;
}

void TypeElementGenerator::CompleteBaseType(otava::symbols::Symbol* symbol)
{
    if (symbol->IsFunctionTypeSymbol())
    {
        otava::symbols::FunctionTypeSymbol* functionTypeSymbol = static_cast<otava::symbols::FunctionTypeSymbol*>(symbol);
        element->AppendChild(soul::xml::MakeText(")("));
        bool first = true;
        for (const auto& parameterType : functionTypeSymbol->ParameterTypes())
        {
            if (first)
            {
                first = false;
            }
            else
            {
                soul::xml::Text* commaText = soul::xml::MakeText(", ");
                element->AppendChild(commaText);
            }
            soul::xml::Element* parameterTypeElement = GenerateTypeXmlElement(module, containerSymbol, parameterType);
            element->AppendChild(parameterTypeElement);
        }
        element->AppendChild(soul::xml::MakeText(")"));
    }
}

soul::xml::Element* GenerateTypeXmlElement(otava::symbols::Module* module, otava::symbols::Symbol* containerSymbol, otava::symbols::Symbol* symbol)
{
    TypeElementGenerator generator(module, containerSymbol);
    symbol->Accept(generator);
    return generator.GetElement();
}

} // namespace gendoc
