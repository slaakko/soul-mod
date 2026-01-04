// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.code.formatter;

import std;

export namespace util {

class CodeFormatter
{
public:
    CodeFormatter(std::ostream& stream_) :
        stream(stream_), indent(0), indentSize(4), atBeginningOfLine(true), line(1), start(false), preserveSpace(false), contentCount(0), logging(false), error(0) 
    {
    }
    inline int Indent() const { return indent; }
    inline int IndentSize() const { return indentSize; }
    inline void SetIndentSize(int indentSize_) { indentSize = indentSize_; }
    inline int CurrentIndent() const { return indentSize * indent; }
    void Write(const std::string& text);
    void WriteLine(const std::string& text);
    void NewLine();
    inline void WriteLine() { NewLine(); }
    void Flush();
    inline void IncIndent()
    {
        ++indent;
    }
    inline void DecIndent()
    {
        --indent;
    }
    inline int Line() const { return line; }
    inline void SetLine(int line_) { line = line_; }
    inline bool Start() const { return start; }
    inline void SetStart() { start = true; }
    inline void ResetStart() { start = false; }
    inline void SetStartText(const std::string& startText_) { startText = startText_; }
    inline const std::string& StartText() const { return startText; }
    inline bool PreserveSpace() const { return preserveSpace; }
    inline void SetPreserveSpace(bool preserveSpace_) { preserveSpace = preserveSpace_; }
    inline void SetLogging() { logging = true; }
    inline void BeginContent() { ++contentCount; }
    inline void EndContent() { --contentCount; }
    inline int Error() const { return error; }
    inline void SetError(int error_) { error = error_; }
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
using StandardEndLine = CoutType& (*)(CoutType&);

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
