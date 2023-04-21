// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import util;
import soul.xml.dom;
import soul.xml.parser;
import soul.xml.content.handler;
import soul.xml.dom.parser;
import soul.lexer.test;

std::string Version()
{
    return "4.0.0";
}

void PrintHelp()
{
    std::cout << "XML parser tester version " << Version() << std::endl;
    std::cout << "Usage: xml_parser_test [options] { FILE.xml }"  << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << "--sax | -s" << std::endl;
    std::cout << "  Use SAX-like content handler." << std::endl;
    std::cout << "--empty | -e" << std::endl;
    std::cout << "  Empty content handler." << std::endl;
}

class PrintContentHandler : public soul::xml::XmlContentHandler
{
public:
    void StartDocument(const soul::ast::SourcePos& sourcePos) override;
    void EndDocument() override;
    void XmlVersion(const std::string& xmlVersion) override;
    void XmlEncoding(const std::string& xmlEncoding) override;
    void Standalone(bool standalone) override;
    void Comment(const soul::ast::SourcePos& sourcePos, const std::string& comment) override;
    void PI(const soul::ast::SourcePos& sourcePos, const std::string& target, const std::string& data) override;
    void Text(const soul::ast::SourcePos& sourcePos, const std::string& text) override;
    void CDataSection(const soul::ast::SourcePos& sourcePos, const std::string& cdata) override;
    void StartElement(const soul::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName,
        const soul::xml::processor::Attributes& attributes) override;
    void EndElement(const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName) override;
    void SkippedEntity(const soul::ast::SourcePos& sourcePos, const std::string& entityName) override;
};

void PrintContentHandler::StartDocument(const soul::ast::SourcePos& sourcePos)
{
    std::cout << "START_DOCUMENT(line=" << std::to_string(sourcePos.line) << ")" << std::endl;
}

void PrintContentHandler::EndDocument()
{
    std::cout << "END_DOCUMENT" << std::endl;
}

void PrintContentHandler::XmlVersion(const std::string& xmlVersion)
{
    std::cout << "XML_VERSION(version='" << xmlVersion << "')" << std::endl;
}

void PrintContentHandler::XmlEncoding(const std::string& xmlEncoding)
{
    std::cout << "XML_ENCODING(encoding='" << xmlEncoding << "')" << std::endl;
}

void PrintContentHandler::Standalone(bool standalone)
{
    std::cout << "XML_STANDALONE(standalone=" << (standalone ? "'yes'" : "'no'") << "')" << std::endl;
}

void PrintContentHandler::Comment(const soul::ast::SourcePos& sourcePos, const std::string& comment)
{
    std::cout << "COMMENT(comment='" << util::StringStr(comment) << "', line=" << std::to_string(sourcePos.line) << ")" << std::endl;
}

void PrintContentHandler::PI(const soul::ast::SourcePos& sourcePos, const std::string& target, const std::string& data)
{
    std::cout << "PI(target='" << target << "', data='" << data + "', line=" << std::to_string(sourcePos.line) << ")" << std::endl;
}

void PrintContentHandler::Text(const soul::ast::SourcePos& sourcePos, const std::string& text)
{
    std::cout << "TEXT(text='" << util::StringStr(text) + "', line=" << std::to_string(sourcePos.line) << ")" << std::endl;
}

void PrintContentHandler::CDataSection(const soul::ast::SourcePos& sourcePos, const std::string& cdata)
{
    std::cout << "CDATA_SECTION(cdata='" << util::StringStr(cdata) << "', line=" << std::to_string(sourcePos.line) << ")" << std::endl;
}

void PrintContentHandler::StartElement(const soul::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName,
    const soul::xml::processor::Attributes& attributes)
{
    std::cout << "START_ELEMENT(namespaceURI='" << namespaceUri << "', localName='" << localName << "', qualifiedName='" << qualifiedName << "', attributes=" << 
        attributes.ToString() << ", line=" << std::to_string(sourcePos.line) << ")" << std::endl;
}

void PrintContentHandler::EndElement(const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName)
{
    std::cout << "END_ELEMENT(namespaceURI='" << namespaceUri << "', localName='" << localName << "', qualifiedName='" << qualifiedName << "')" << std::endl;
}

void PrintContentHandler::SkippedEntity(const soul::ast::SourcePos& sourcePos, const std::string& entityName)
{
    std::cout << "SKIPPED_ENTITY(entityName='" << entityName << "', line=" << std::to_string(sourcePos.line) << ")" << std::endl;
}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
        bool verbose = false;
        bool lexer = false;
        bool lexerless = false;
        bool sax = false;
        bool empty = false;
        bool warnings = false;
        std::vector<std::string> fileNames;
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg.starts_with("--"))
            {
                if (arg == "--verbose")
                {
                    verbose = true;
                }
                else if (arg == "--help")
                {
                    PrintHelp();
                    return 1;
                }
                else if (arg == "--sax")
                {
                    sax = true;
                }
                else if (arg == "--empty")
                {
                    empty = true;
                }
                else if (arg == "--warnings")
                {
                    warnings = true;
                }
                else
                {
                    throw std::runtime_error("unknown option '" + arg + "'");
                }
            }
            else if (arg.starts_with("-"))
            {
                std::string options = arg.substr(1);
                for (char o : options)
                {
                    switch (o)
                    {
                        case 'v':
                        {
                            verbose = true;
                            break;
                        }
                        case 'h':
                        {
                            PrintHelp();
                            return 1;
                        }
                        case 's':
                        {
                            sax = true;
                            break;
                        }
                        case 'e':
                        {
                            empty = true;
                            break;
                        }
                        case 'w':
                        {
                            warnings = true;
                            break;
                        }
                        default:
                        {
                            throw std::runtime_error("unknown option '-" + std::string(1, o) + "'");
                        }
                    }
                }
            }
            else
            {
                fileNames.push_back(util::GetFullPath(arg));
            }
        }
        if (fileNames.empty())
        {
            throw std::runtime_error("no files given");
        }
        for (const auto& fileName : fileNames)
        {
            if (verbose)
            {
                std::cout << "> " << fileName << std::endl;
            }
            if (sax)
            {
                soul::xml::XmlContentHandler emptyHandler;
                soul::xml::XmlContentHandler* contentHandler = &emptyHandler;
                PrintContentHandler printContentHandler;
                if (!empty)
                {
                    contentHandler = &printContentHandler;
                }
                soul::xml::parser::ParseXmlFile(fileName, contentHandler);
            }
            else
            {
                soul::xml::ParsingFlags flags = soul::xml::ParsingFlags::none;
                if (warnings)
                {
                    flags = flags | soul::xml::ParsingFlags::generateWarnings;
                }
                std::unique_ptr<soul::xml::Document> document = soul::xml::ParseXmlFile(fileName, flags);
                if (!empty)
                {
                    util::CodeFormatter formatter(std::cout);
                    formatter.SetIndentSize(2);
                    document->Write(formatter);
                }
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
}
