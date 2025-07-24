// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.code.formatter;

import std;

export namespace util {

class CodeFormatter
{
public:
    CodeFormatter(std::ostream& stream_) : 
        stream(stream_), indent(0), indentSize(4), atBeginningOfLine(true), line(1), start(false), preserveSpace(false), contentCount(0), logging(false), error(0) {}
    int Indent() const { return indent; }
    int IndentSize() const { return indentSize; }
    void SetIndentSize(int indentSize_) { indentSize = indentSize_; }
    int CurrentIndent() const { return indentSize * indent; }
    std::expected<bool, int> Write(const std::string& text);
    std::expected<bool, int> WriteLine(const std::string& text);
    void NewLine();
    void WriteLine() { NewLine(); }
    void Flush();
    void IncIndent()
    {
        ++indent;
    }
    void DecIndent()
    {
        --indent;
    }
    int Line() const { return line; }
    void SetLine(int line_) { line = line_; }
    bool Start() const { return start; }
    void SetStart() { start = true; }
    void ResetStart() { start = false; }
    void SetStartText(const std::string& startText_) { startText = startText_; }
    const std::string& StartText() const { return startText; }
    bool PreserveSpace() const { return preserveSpace; }
    void SetPreserveSpace(bool preserveSpace_) { preserveSpace = preserveSpace_; }
    void SetLogging() { logging = true; }
    void BeginContent() { ++contentCount; }
    void EndContent() { --contentCount; }
    int Error() const { return error; }
    void SetError(int error_) { error = error_; }
private:
    std::ostream& stream;
    int indent;
    int indentSize;
    bool atBeginningOfLine;
    int line;
    bool start;
    std::string startText;
    bool preserveSpace;
    int contentCount;
    bool logging;
    int error;
};

using CoutType = std::ostream;
using StandardEndLine = CoutType & (*)(CoutType&);

CodeFormatter& operator<<(CodeFormatter& f, StandardEndLine manip);
CodeFormatter& operator<<(CodeFormatter& f, const std::string& s);
CodeFormatter& operator<<(CodeFormatter& f, const char* s);
CodeFormatter& operator<<(CodeFormatter& f, char c);
CodeFormatter& operator<<(CodeFormatter& f, bool b);
CodeFormatter& operator<<(CodeFormatter& f, int x);
CodeFormatter& operator<<(CodeFormatter& f, double x);
CodeFormatter& operator<<(CodeFormatter& f, std::int64_t x);
CodeFormatter& operator<<(CodeFormatter& f, std::uint64_t x);

std::expected<bool, int> WriteUtf8(std::ostream& s, const std::string& str);
bool IsHandleRedirected(int handle);

} // namespace util
