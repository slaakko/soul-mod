// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import util;
import soul.xml.dom;
import cpp.token.lexer;
import cpp.token;

using namespace cpp::token;

std::string Version()
{
    return "4.0.0";
}

std::string KeywordColor()
{
    return "#0000ff";
}

std::string IdColor()
{
    return "#000000";
}

std::string NumberColor()
{
    return "#000000";
}

std::string StringColor()
{
    return "#a31515";
}

std::string PPColor()
{
    return "#e6e7e8";
}

std::string OtherColor()
{
    return "#000000";
}

std::string CommentColor()
{
    return "#57a64a";
}

void PrintHelp()
{
    std::cout << "C++ to HTML converter version " << Version() << std::endl;
    std::cout << "usage: cpp2html [options] { FILE.cpp | FILE.ixx }" << std::endl;
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
    formatter.WriteLine("div.cpp");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("background-color: #e6f7ff;");
    formatter.WriteLine("margin: 20px;");
    formatter.WriteLine("padding: 20px;");
    formatter.WriteLine("font-family: monospace;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
    formatter.WriteLine(".cpp .kw");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: " + KeywordColor() + ";");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".cpp .id");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: " + IdColor() + ";");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".cpp .number");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: " + NumberColor() + ";");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".cpp .string");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: " + StringColor() + ";");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".cpp .pp");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: " + PPColor() + ";");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".cpp .other");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: " + OtherColor() + ";");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    formatter.WriteLine(".cpp .comment");
    formatter.WriteLine("{");
    formatter.IncIndent();
    formatter.WriteLine("color: " + CommentColor() + ";");
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();

    return sstream.str();
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

void AppendKeyword(const std::string& kw, soul::xml::Element* element)
{
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

void AppendNumber(const std::string& number, soul::xml::Element* element)
{
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "number");
    soul::xml::Text* text = soul::xml::MakeText(number);
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

void AppendPPToken(const std::string& ppToken, soul::xml::Element* element)
{
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "pp");
    soul::xml::Text* text = soul::xml::MakeText(ppToken);
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

void AppendComment(const std::string& comment, soul::xml::Element* element)
{
    soul::xml::Element* span = soul::xml::MakeElement("span");
    span->SetAttribute("class", "comment");
    soul::xml::Text* text = soul::xml::MakeText(comment);
    span->AppendChild(text);
    element->AppendChild(span);
}

template<typename Token>
void ProcessToken(const Token& token, soul::xml::Element* element)
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
            AppendKeyword(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case ID:
        {
            AppendId(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case NUMBER:
        {
            AppendNumber(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case CHARLIT:
        case STRINGLIT:
        {
            AppendString(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case PP:
        {
            AppendPPToken(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case OTHER:
        {
            AppendOther(util::ToUtf8(token.match.ToString()), element);
            break;
        }
        case LINECOMMENT:
        case BLOCKCOMMENT:
        case BLOCKCOMMENTLINE:
        {
            AppendComment(util::ToUtf8(token.match.ToString()), element);
            break;
        }
    }
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
    std::ofstream htmlFile(htmlFilePath);
    util::CodeFormatter formatter(htmlFile);
    formatter.SetIndentSize(1);
    std::unique_ptr<soul::xml::Document> doc = soul::xml::MakeDocument();
    formatter.WriteLine("<!DOCTYPE html>");
    formatter.WriteLine();
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
    soul::xml::Element* divElement = soul::xml::MakeElement("div");
    divElement->SetAttribute("class", "cpp");
    bodyElement->AppendChild(divElement);
    doc->AppendChild(htmlElement);
    soul::xml::Element* currentElement = nullptr;
    int n = lines.size();
    for (int i = 0; i < n; ++i)
    {
        std::u32string line = lines[i];
        line.append(U"\n\n");
        auto tokenLexer = cpp::token::lexer::MakeLexer(line.c_str(), line.c_str() + line.length(), "");
        soul::xml::Element* lineElement = soul::xml::MakeElement("span");
        lineElement->SetAttribute("xml:space", "preserve");
        currentElement = lineElement;
        ++tokenLexer;
        while (*tokenLexer != soul::lexer::END_TOKEN)
        {
            auto token = tokenLexer.GetToken(tokenLexer.GetPos());
            ProcessToken(token, currentElement);
            ++tokenLexer;
        }
        soul::xml::Element* brElement = soul::xml::MakeElement("br");
        divElement->AppendChild(lineElement);
        divElement->AppendChild(brElement);
    }
    doc->Write(formatter);
    if (verbose)
    {
        std::cout << "==> " << htmlFilePath << std::endl;
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
    return 0;
}
