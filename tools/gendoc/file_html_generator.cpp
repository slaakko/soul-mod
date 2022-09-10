// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.file_html_generator;

import soul.cpp20.lexer.line_tokenizer;
import soul.cpp20.token;
import soul.cpp20.symbols;
import soul.cpp20.ast;
import soul.xml.dom;
import util;
import std.filesystem;

namespace gendoc {

std::vector<std::string> SplitIntoLines(const std::string& fileContent)
{
    std::vector<std::string> lines;
    std::string line;
    int state = 0;
    for (char c : fileContent)
    {
        switch (state)
        {
            case 0:
            {
                switch (c)
                {
                    case '\n': 
                    {
                        lines.push_back(line);
                        line.clear();
                        break;
                    }
                    case '\r':
                    {
                        state = 1;
                        break;
                    }
                    case '\t':
                    {
                        line.append(4, ' ');
                        break;
                    }
                    default:
                    {
                        line.append(1, c);
                        break;
                    }
                }
                break;
            }
            case 1:
            {
                switch (c)
                {
                    case '\n':
                    {
                        lines.push_back(line);
                        line.clear();
                        state = 0;
                        break;
                    }
                }
                break;
            }
        }
    }
    if (!line.empty())
    {
        lines.push_back(line);
    }
    return lines;
}

std::vector<std::string> ReadLines(const std::string& sourceFilePath)
{
    std::string fileContent = util::ReadFile(sourceFilePath);
    return SplitIntoLines(fileContent);
}

class FileHtmlGenerator : public soul::cpp20::ast::DefaultVisitor
{
public:
    FileHtmlGenerator(soul::cpp20::symbols::Module* module_, soul::cpp20::ast::File* file_, const std::string& moduleDir_);
    void BeginVisit(soul::cpp20::ast::Node& node) override;
    void EndVisit(soul::cpp20::ast::Node& node) override;
    void VisitIdentifier(const std::u32string& id, const soul::ast::SourcePos& sourcePos) override;
    void VisitKeyword(const std::string& keyword, const soul::ast::SourcePos& sourcePos) override;
    void VisitOperator(const std::string& symbol, const soul::ast::SourcePos& sourcePos) override;
    void VisitToken(const std::u32string& tokenStr, const soul::ast::SourcePos& sourcePos) override;
    void VisitLiteral(const std::u32string& rep, const soul::ast::SourcePos& sourcePos) override;
    void VisitHeaderName(const std::u32string& rep, const soul::ast::SourcePos& sourcePos) override;
    void WriteDoc();
private:
    void Advance(const soul::ast::SourcePos& sourcePos);
    void GenerateLine(int lineNumber);
    void AddLineNumberField(int lineNumber);
    soul::cpp20::symbols::Module* module;
    soul::cpp20::ast::File* file;
    std::string moduleDir;
    std::string filePath;
    soul::xml::Document doc;
    soul::xml::Element* bodyElement;
    soul::xml::Element* divElement;
    soul::xml::Element* currentElement;
    std::vector<std::string> lines;
    int currentLine;
    int nextLineToGenerate;
    int currentColumn;
    bool atBeginningOfLine;
    bool inBlockComment;
    int lineNumberFieldLength;
};

FileHtmlGenerator::FileHtmlGenerator(soul::cpp20::symbols::Module* module_, soul::cpp20::ast::File* file_, const std::string& moduleDir_) : 
    module(module_), file(file_), moduleDir(moduleDir_), currentLine(1), currentColumn(1), atBeginningOfLine(true), inBlockComment(false), nextLineToGenerate(1), lineNumberFieldLength(0)
{
    filePath = util::GetFullPath(util::Path::Combine(util::Path::Combine(moduleDir, "file"), util::Path::GetFileName(file->filePath) + ".html"));
    std::filesystem::create_directories(util::Path::GetDirectoryName(filePath));
    std::string sourceFilePath = util::GetFullPath(util::Path::Combine(util::Path::GetDirectoryName(module->FilePath()), util::Path::GetFileName(file->filePath)));
    lines = ReadLines(sourceFilePath);
    lineNumberFieldLength = util::Log10(lines.size());
    soul::xml::Element* htmlElement = soul::xml::MakeElement("html");
    doc.AppendChild(htmlElement);
    soul::xml::Element* headElement = soul::xml::MakeElement("head");
    htmlElement->AppendChild(headElement);
    soul::xml::Element* metaElement = soul::xml::MakeElement("meta");
    metaElement->SetAttribute("charset", "utf-8");
    headElement->AppendChild(metaElement);
    soul::xml::Element* titleElement = soul::xml::MakeElement("title");
    std::string title = util::Path::GetFileName(file->filePath);
    soul::xml::Text* titleText = soul::xml::MakeText(title);
    titleElement->AppendChild(titleText);
    headElement->AppendChild(titleElement);
    soul::xml::Element* linkElement = soul::xml::MakeElement("link");
    std::string styleFilePath = "../../../style/style.css";
    linkElement->SetAttribute("href", styleFilePath);
    linkElement->SetAttribute("rel", "stylesheet");
    linkElement->SetAttribute("type", "text/css");
    headElement->AppendChild(linkElement);
    bodyElement = soul::xml::MakeElement("body");
    soul::xml::Element* h1Element = soul::xml::MakeElement("h1");
    soul::xml::Text* h1Text = soul::xml::MakeText(title);
    h1Element->AppendChild(h1Text);
    bodyElement->AppendChild(h1Element);
    htmlElement->AppendChild(bodyElement);
    divElement = soul::xml::MakeElement("div");
    divElement->SetAttribute("class", "code");
    bodyElement->AppendChild(divElement);
    currentElement = divElement;
}

void FileHtmlGenerator::Advance(const soul::ast::SourcePos& sourcePos)
{
    while (nextLineToGenerate < sourcePos.line)
    {
        GenerateLine(nextLineToGenerate);
        divElement->AppendChild(soul::xml::MakeElement("br"));
        ++nextLineToGenerate;
        ++currentLine;
        currentColumn = 1;
        atBeginningOfLine = true;
    }
    while (currentLine < sourcePos.line)
    {
        divElement->AppendChild(soul::xml::MakeElement("br"));
        ++currentLine;
        currentColumn = 1;
        atBeginningOfLine = true;
    }
    if (atBeginningOfLine)
    {
        atBeginningOfLine = false;
        soul::xml::Element* lineElement = soul::xml::MakeElement("span");
        lineElement->SetAttribute("class", "line");
        lineElement->SetAttribute("xml:space", "preserve");
        lineElement->SetAttribute("id", std::to_string(currentLine));
        divElement->AppendChild(lineElement);
        currentElement = lineElement;
        AddLineNumberField(currentLine);
    }
    while (currentColumn < sourcePos.col)
    {
        soul::xml::EntityReference* entityRef = soul::xml::MakeEntityReference("nbsp");
        currentElement->AppendChild(entityRef);
        ++currentColumn;
    }
}

void FileHtmlGenerator::GenerateLine(int lineNumber)
{
    while (currentLine < lineNumber)
    {
        divElement->AppendChild(soul::xml::MakeElement("br"));
        ++currentLine;
    }
    soul::xml::Element* lineElement = soul::xml::MakeElement("span");
    lineElement->SetAttribute("class", "line");
    lineElement->SetAttribute("xml:space", "preserve");
    lineElement->SetAttribute("id", std::to_string(lineNumber));
    divElement->AppendChild(lineElement);
    currentElement = lineElement;
    AddLineNumberField(currentLine);
    const std::string& line = lines[lineNumber - 1];
    std::u32string lineContent;
    std::vector<soul::cpp20::lexer::Token> tokens = soul::cpp20::lexer::TokenizeLine(line, lineContent);
    for (const auto& token : tokens)
    {
        if (inBlockComment && token.id != soul::cpp20::token::BLOCK_COMMENT_END)
        {
            soul::xml::Element* spanElement = soul::xml::MakeElement("span");
            spanElement->SetAttribute("class", "comment");
            spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(token.match.ToString())));
            currentElement->AppendChild(spanElement);
            continue;
        }
        switch (token.id)
        {
            case soul::cpp20::token::KEYWORD:
            {
                soul::xml::Element* spanElement = soul::xml::MakeElement("span");
                spanElement->SetAttribute("class", "keyword");
                spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(token.match.ToString())));
                currentElement->AppendChild(spanElement);
                break;
            }
            case soul::cpp20::token::ID:
            {
                soul::xml::Element* spanElement = soul::xml::MakeElement("span");
                spanElement->SetAttribute("class", "identifier");
                spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(token.match.ToString())));
                currentElement->AppendChild(spanElement);
                break;
            }
            case soul::cpp20::token::FLOATING_LITERAL:
            case soul::cpp20::token::INTEGER_LITERAL:
            case soul::cpp20::token::CHARACTER_LITERAL:
            case soul::cpp20::token::STRING_LITERAL:
            {
                soul::xml::Element* spanElement = soul::xml::MakeElement("span");
                spanElement->SetAttribute("class", "literal");
                spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(token.match.ToString())));
                currentElement->AppendChild(spanElement);
                break;
            }
            case soul::cpp20::token::WS:
            {
                int n = static_cast<int>(token.match.end - token.match.begin);
                for (int i = 0; i < n; ++i)
                {
                    soul::xml::EntityReference* entityRef = soul::xml::MakeEntityReference("nbsp");
                    currentElement->AppendChild(entityRef);
                }
                break;
            }
            case soul::cpp20::token::LINE_COMMENT:
            {
                soul::xml::Element* spanElement = soul::xml::MakeElement("span");
                spanElement->SetAttribute("class", "comment");
                spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(token.match.ToString())));
                currentElement->AppendChild(spanElement);
                break;
            }
            case soul::cpp20::token::BLOCK_COMMENT_START:
            {
                soul::xml::Element* spanElement = soul::xml::MakeElement("span");
                spanElement->SetAttribute("class", "comment");
                spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(token.match.ToString())));
                currentElement->AppendChild(spanElement);
                inBlockComment = true;
                break;
            }
            case soul::cpp20::token::BLOCK_COMMENT_END:
            {
                soul::xml::Element* spanElement = soul::xml::MakeElement("span");
                spanElement->SetAttribute("class", "comment");
                spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(token.match.ToString())));
                currentElement->AppendChild(spanElement);
                inBlockComment = false;
                break;
            }
            case soul::cpp20::token::PP_LINE:
            {
                soul::xml::Element* spanElement = soul::xml::MakeElement("span");
                spanElement->SetAttribute("class", "pp");
                spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(token.match.ToString())));
                currentElement->AppendChild(spanElement);
                break;
            }
            case soul::cpp20::token::OTHER:
            {
                soul::xml::Element* spanElement = soul::xml::MakeElement("span");
                spanElement->SetAttribute("class", "other");
                spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(token.match.ToString())));
                currentElement->AppendChild(spanElement);
                break;
            }
        }
    }
}

void FileHtmlGenerator::BeginVisit(soul::cpp20::ast::Node& node)
{
    Advance(node.GetSourcePos());
    nextLineToGenerate = node.GetSourcePos().line + 1;
}

void FileHtmlGenerator::EndVisit(soul::cpp20::ast::Node& node)
{
}

void FileHtmlGenerator::AddLineNumberField(int lineNumber)
{
    soul::xml::Element* spanElement = soul::xml::MakeElement("span");
    spanElement->SetAttribute("class", "lineNumber");
    std::string lineNumberStr = util::Format(std::to_string(lineNumber), lineNumberFieldLength, util::FormatJustify::right);;
    for (const auto ch : lineNumberStr)
    {
        if (ch == ' ')
        {
            soul::xml::EntityReference* entityRef = soul::xml::MakeEntityReference("nbsp");
            spanElement->AppendChild(entityRef);
        }
        else
        {
            spanElement->AppendChild(soul::xml::MakeText(std::string(1, ch)));
        }
    }
    soul::xml::EntityReference* entityRef = soul::xml::MakeEntityReference("nbsp");
    spanElement->AppendChild(entityRef);
    currentElement->AppendChild(spanElement);
}

void FileHtmlGenerator::VisitIdentifier(const std::u32string& id, const soul::ast::SourcePos& sourcePos)
{
    Advance(sourcePos);
    soul::xml::Element* spanElement = soul::xml::MakeElement("span");
    spanElement->SetAttribute("class", "identifier");
    spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(id)));
    currentElement->AppendChild(spanElement);
    currentColumn += id.length();
    nextLineToGenerate = sourcePos.line + 1;
}

void FileHtmlGenerator::VisitKeyword(const std::string& keyword, const soul::ast::SourcePos& sourcePos)
{
    Advance(sourcePos);
    soul::xml::Element* spanElement = soul::xml::MakeElement("span");
    spanElement->SetAttribute("class", "keyword");
    spanElement->AppendChild(soul::xml::MakeText(keyword));
    currentElement->AppendChild(spanElement);
    currentColumn += keyword.length();
    nextLineToGenerate = sourcePos.line + 1;
}

void FileHtmlGenerator::VisitOperator(const std::string& symbol, const soul::ast::SourcePos& sourcePos)
{
    Advance(sourcePos);
    soul::xml::Element* spanElement = soul::xml::MakeElement("span");
    spanElement->SetAttribute("class", "operator");
    spanElement->AppendChild(soul::xml::MakeText(symbol));
    currentElement->AppendChild(spanElement);
    currentColumn += symbol.length();
    nextLineToGenerate = sourcePos.line + 1;
}

void FileHtmlGenerator::VisitToken(const std::u32string& tokenStr, const soul::ast::SourcePos& sourcePos)
{
    Advance(sourcePos);
    soul::xml::Element* spanElement = soul::xml::MakeElement("span");
    spanElement->SetAttribute("class", "token");
    spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(tokenStr)));
    currentElement->AppendChild(spanElement);
    currentColumn += tokenStr.length();
    nextLineToGenerate = sourcePos.line + 1;
}

void FileHtmlGenerator::VisitLiteral(const std::u32string& rep, const soul::ast::SourcePos& sourcePos)
{
    Advance(sourcePos);
    soul::xml::Element* spanElement = soul::xml::MakeElement("span");
    spanElement->SetAttribute("class", "literal");
    spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(rep)));
    currentElement->AppendChild(spanElement);
    currentColumn += rep.length();
    nextLineToGenerate = sourcePos.line + 1;
}

void FileHtmlGenerator::VisitHeaderName(const std::u32string& rep, const soul::ast::SourcePos& sourcePos)
{
    soul::xml::Element* spanElement = soul::xml::MakeElement("span");
    spanElement->SetAttribute("class", "header");
    spanElement->AppendChild(soul::xml::MakeText(util::ToUtf8(rep)));
    currentElement->AppendChild(spanElement);
    currentColumn += rep.length();
    nextLineToGenerate = sourcePos.line + 1;
}

void FileHtmlGenerator::WriteDoc()
{
    std::ofstream file(filePath);
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    doc.Write(formatter);
}

void GenerateFileHtml(soul::cpp20::symbols::Module* module, const std::string& moduleDir)
{
    soul::cpp20::ast::File* interfaceFile = module->GetFile();
    FileHtmlGenerator generator(module, interfaceFile, moduleDir);
    interfaceFile->content->Accept(generator);
    generator.WriteDoc();
    for (const auto& implementationUnit : module->ImplementationUnits())
    {
        soul::cpp20::ast::File* implementationFile = implementationUnit->GetFile();
        FileHtmlGenerator generator(implementationUnit, implementationFile, moduleDir);
        implementationFile->content->Accept(generator);
        generator.WriteDoc();
    }
}

} // namespace gendoc
