// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import util;
import soul.xml.dom;
import soul.token.lexer;
import soul.token;

using namespace soul::token;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "Parser to HTML converter version " << Version() << std::endl;
    std::cout << "usage: soul2html [options] { FILE.parser | FILE.token | FILE.keyword | FILE.expr | FILE.lexer | FILE.slg }" << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
}

std::string MakeStyleText(int indent)
{
    std::stringstream sstream;
    util::CodeFormatter formatter(sstream);
    formatter.SetIndentSize(1);
    formatter.WriteLine("div.soul");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("background-color: #e6ffee;");
    formatter.WriteLine("margin: 20px;");
    formatter.WriteLine("padding: 20px;");
    formatter.WriteLine("font-family: monospace;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    formatter.WriteLine(".soul .kw");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: #a31515;");
    formatter.WriteLine("font-weight: bold;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".soul .id");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: #000000;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".soul .number");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: #000000;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".soul .other");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: #000000;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".soul .string");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: #a31515;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".soul .comment");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: #006600;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".soul .punctuation");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: #a31515;");
    formatter.WriteLine("font-weight: bold;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    return sstream.str();
}

void AppendSpace(int count, soul::xml::Element* element)
{
    for (int i = 0; i < count; ++i)
    {
        soul::xml::EntityReference* nbsb = soul::xml::MakeEntityReference("nbsp");
        element->AppendChild(nbsb);
    }
}

template<typename Char>
void AppendSpace(const Char* begin, const Char* end, soul::xml::Element* element)
{
    while (begin != end)
    {
        auto chr = *begin;
        switch (chr)
        {
        case ' ':
        {
            AppendSpace(1, element);
            break;
        }
        case '\t':
        {
            AppendSpace(4, element);
            break;
        }
        }
        ++begin;
    }
}

void AppendId(const std::string& id, soul::xml::Element* element);

void AppendKeyword(const std::string& kw, soul::xml::Element* element, bool startOfLine)
{
    if (kw == "parser" || kw == "lexer")
    {
        if (!startOfLine)
        {
            AppendId(kw, element);
            return;
        }
    }
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "kw");
    soul::xml::Text* text = soul::xml::MakeText(kw);
    span->AppendChild(text);
    element->AppendChild(span);
}

void AppendId(const std::string& id, soul::xml::Element* element)
{
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "id");
    soul::xml::Text* text = soul::xml::MakeText(id);
    span->AppendChild(text);
    element->AppendChild(span);
}

void AppendString(const std::string& string, soul::xml::Element* element)
{
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "string");
    soul::xml::Text* text = soul::xml::MakeText(string);
    span->AppendChild(text);
    element->AppendChild(span);
}

void AppendNumber(const std::string& string, soul::xml::Element* element)
{
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "number");
    soul::xml::Text* text = soul::xml::MakeText(string);
    span->AppendChild(text);
    element->AppendChild(span);
}

void AppendComment(const std::string& comment, soul::xml::Element* element)
{
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "comment");
    soul::xml::Text* text = soul::xml::MakeText(comment);
    span->AppendChild(text);
    element->AppendChild(span);
}

void AppendOther(const std::string& other, soul::xml::Element* element)
{
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "other");
    soul::xml::Text* text = soul::xml::MakeText(other);
    span->AppendChild(text);
    element->AppendChild(span);
}

void AppendPunctuation(const std::string& punctuation, soul::xml::Element* element)
{
    if (punctuation == "...")
    {
        AppendOther(punctuation, element);
        return;
    }
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "punctuation");
    soul::xml::Text* text = soul::xml::MakeText(punctuation);
    span->AppendChild(text);
    element->AppendChild(span);
}

template<typename Token>
void ProcessToken(const Token& token, soul::xml::Element* element, bool startOfLine)
{
    switch (token.id)
    {
        case WS:
        {
            AppendSpace(token.match.begin, token.match.end, element);
            break;
        }
        case KEYWORD:
        {
            AppendKeyword(util::ToUtf8(token.match.ToString()), element, startOfLine);
            break;
        }
        case ID:
        {
            AppendId(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case CHAR_LITERAL:
        case STRING_LITERAL:
        {
            AppendString(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case NUMBER:
        {
            AppendNumber(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case LINE_COMMENT:
        {
            AppendComment(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case PUNCT:
        {
            AppendPunctuation(util::ToUtf8(token.match.ToString()), element);
            break;
        }
    }
}

std::vector<std::u32string> GetLines(const std::u32string& text)
{
    std::vector<std::u32string> lines;
    std::u32string line;
    int state = 0;
    for (char32_t c : text)
    {
        switch (state)
        {
            case 0:
            {
                if (c == '\n')
                {
                    lines.push_back(std::move(line));
                    line.clear();
                    state = 1;
                }
                else if (c != '\r')
                {
                    line.append(1, c);
                }
                break;
            }
            case 1:
            {
                if (c == '\n')
                {
                    lines.push_back(std::move(line));
                    line.clear();
                }
                else if (c != '\r')
                {
                    line.append(1, c);
                    state = 0;
                }
                break;
            }
        }
    }
    if (state == 0)
    {
        lines.push_back(std::move(line));
    }
    return lines;
}

void ProcessFile(const std::string& fileName, const std::string& title, bool verbose)
{
    if (verbose)
    {
        std::cout << "> " << fileName << std::endl;
    }
    std::string content = util::ReadFile(fileName);
    std::u32string ucontent = util::ToUtf32(content);
    std::vector<std::u32string> lines = GetLines(ucontent);
    std::string htmlFilePath = fileName + ".html";
    std::string divFilePath = fileName + ".div";
    std::ofstream htmlFile(htmlFilePath);
    std::ofstream divFile(divFilePath);
    util::CodeFormatter htmlFormatter(htmlFile);
    htmlFormatter.SetIndentSize(1);
    util::CodeFormatter divFormatter(divFile);
    divFormatter.SetIndentSize(1);
    std::unique_ptr<soul::xml::Document> htmlDoc = soul::xml::MakeDocument();
    htmlFormatter.WriteLine("<!DOCTYPE html>");
    htmlFormatter.WriteLine();
    soul::xml::Element* htmlElement = soul::xml::MakeElement("html");
    htmlElement->SetAttribute("lang", "en");
    htmlElement->SetAttribute("xmlns", "http://www.w3.org/1999/xhtml");
    soul::xml::Element* headElement = soul::xml::MakeElement("head");
    soul::xml::Element* metaElement = soul::xml::MakeElement("meta");
    metaElement->SetAttribute("charset", "utf-8");
    headElement->AppendChild(metaElement);
    soul::xml::Element* titleElement = soul::xml::MakeElement("title");
    soul::xml::Text* titleText = soul::xml::MakeText(title);
    titleElement->AppendChild(titleText);
    headElement->AppendChild(titleElement);
    soul::xml::Element* styleElement = soul::xml::MakeElement("style");
    soul::xml::Text* styleText = soul::xml::MakeText(MakeStyleText(3));
    styleElement->AppendChild(styleText);
    headElement->AppendChild(styleElement);
    htmlElement->AppendChild(headElement);
    soul::xml::Element* bodyElement = soul::xml::MakeElement("body");
    htmlElement->AppendChild(bodyElement);
    std::unique_ptr<soul::xml::Document> divDoc = soul::xml::MakeDocument();
    soul::xml::Element* divHtmlElement = soul::xml::MakeElement("div");
    divHtmlElement->SetAttribute("class", "soul");
    bodyElement->AppendChild(divHtmlElement);
    htmlDoc->AppendChild(htmlElement);
    soul::xml::Element* divRootElement = soul::xml::MakeElement("div");
    divRootElement->SetAttribute("class", "soul");
    divDoc->AppendChild(divRootElement);
    soul::xml::Element* currentHtmlElement = nullptr;
    soul::xml::Element* currentDivElement = nullptr;
    int n = lines.size();
    for (int i = 0; i < n; ++i)
    {
        std::u32string line = lines[i];
        line.append(U"\n\n");
        auto tokenLexer = soul::token::lexer::MakeLexer(line.c_str(), line.c_str() + line.length(), "");
        soul::xml::Element* lineHtmlElement = soul::xml::MakeElement("span");
        lineHtmlElement->SetAttribute("xml:space", "preserve");
        currentHtmlElement = lineHtmlElement;
        soul::xml::Element* lineDivElement = soul::xml::MakeElement("span");
        lineDivElement->SetAttribute("xml:space", "preserve");
        currentDivElement = lineDivElement;
        bool startOfLine = true;
        ++tokenLexer;
        while (*tokenLexer != soul::lexer::END_TOKEN)
        {
            auto token = tokenLexer.GetToken(tokenLexer.GetPos());
            ProcessToken(token, currentHtmlElement, startOfLine);
            ProcessToken(token, currentDivElement, startOfLine);
            ++tokenLexer;
            if (token.id != WS)
            {
                startOfLine = false;
            }
        }
        soul::xml::Element* brHtmlElement = soul::xml::MakeElement("br");
        divHtmlElement->AppendChild(lineHtmlElement);
        divHtmlElement->AppendChild(brHtmlElement);
        soul::xml::Element* brDivElement = soul::xml::MakeElement("br");
        divRootElement->AppendChild(lineDivElement);
        divRootElement->AppendChild(brDivElement);
    }
    htmlDoc->Write(htmlFormatter);
    divDoc->Write(divFormatter);
    if (verbose)
    {
        std::cout << "==> " << htmlFilePath << std::endl;
        std::cout << "==> " << divFilePath << std::endl;
    }
}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
        bool verbose = false;
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
                    default:
                    {
                        throw std::runtime_error("unknown option '-" + std::string(1, o) + "'");
                    }
                    }
                }
            }
            else
            {
                fileNames.push_back(arg);
            }
        }
        if (fileNames.empty())
        {
            throw std::runtime_error("no file names given");
        }
        for (const auto& fileName : fileNames)
        {
            ProcessFile(util::GetFullPath(fileName), fileName, verbose);
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
}
