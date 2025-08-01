// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;

#include <cstdio>
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#else
#include <unistd.h>
#endif 

module util.code.formatter;

import util.ansi;
import util.unicode;

namespace util {

#ifdef _WIN32

void SetStdHandlesToUtf16Mode()
{
    _setmode(0, _O_U16TEXT);
    _setmode(1, _O_U16TEXT);
    _setmode(2, _O_U16TEXT);
}

void SetStdHandlesToNarrowMode()
{
    _setmode(0, _O_TEXT);
    _setmode(1, _O_TEXT);
    _setmode(2, _O_TEXT);
}

bool IsHandleRedirected(int handle)
{
    return !_isatty(handle);
}

struct UnicodeWriteGuard
{
    UnicodeWriteGuard()
    {
        SetStdHandlesToUtf16Mode();
    }
    ~UnicodeWriteGuard()
    {
        SetStdHandlesToNarrowMode();
    }
};

void WriteUtf16StrToStdOutOrStdErr(const std::u16string& str, FILE* file)
{
    //  precondition: file must be stdout or stderr
    if (file != stdout && file != stderr)
    {
        throw std::runtime_error("WriteUtf16StrToStdOutOrStdErr: precondition violation: file must be stdout or stderr");
    }
    UnicodeWriteGuard unicodeWriteGuard;
    size_t result = std::fwrite(str.c_str(), sizeof(char16_t), str.length(), file);
    if (result != str.length())
    {
        throw std::runtime_error("could not write Unicode text");
    }
}

void WriteUtf8(std::ostream& s, const std::string& str)
{
    if (&s == &std::cout && !IsHandleRedirected(1))
    {
        std::string ps = AnsiIntercept(1, str);
        if (!ps.empty())
        {
            std::u16string utf16Str = ToUtf16(ps);
            WriteUtf16StrToStdOutOrStdErr(utf16Str, stdout);
        }
    }
    else if (&s == &std::cerr && !IsHandleRedirected(2))
    {
        std::string ps = AnsiIntercept(2, str);
        if (!ps.empty())
        {
            std::u16string utf16Str = ToUtf16(ps);
            WriteUtf16StrToStdOutOrStdErr(utf16Str, stderr);
        }
    }
    else
    {
        s << str;
    }
}

#elif defined(__linux) || defined(__unix) || defined(__posix)

bool IsHandleRedirected(int handle)
{
    return !isatty(handle);
}

void WriteUtf8(std::ostream& s, const std::string& str)
{
    s << str;
}

#else

#error unknown platform

#endif

void CodeFormatter::Write(const std::string& text)
{
    if (atBeginningOfLine)
    {
        if (indent > 0)
        {
            stream << std::string(indentSize * indent, ' ');
            atBeginningOfLine = false;
        }
    }
    if (logging && contentCount > 0)
    {
        WriteUtf8(stream, "length=" + std::to_string(text.length()));
    }
    else
    {
        WriteUtf8(stream, text);
    }
}

void CodeFormatter::WriteLine(const std::string& text)
{
    Write(text);
    NewLine();
}

void CodeFormatter::NewLine()
{
    stream << "\n";
    atBeginningOfLine = true;
    ++line;
}

void CodeFormatter::Flush()
{
    stream.flush();
}

CodeFormatter& operator<<(CodeFormatter& f, StandardEndLine manip)
{
    f.WriteLine();
    f.Flush();
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, const std::string& s)
{
    f.Write(s);
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, const char* s)
{
    f.Write(s);
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, char c)
{
    f.Write(std::string(1, c));
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, bool b)
{
    if (b)
    {
        f.Write("true");
    }
    else
    {
        f.Write("false");
    }
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, int x)
{
    f.Write(std::to_string(x));
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, double x)
{
    f.Write(std::to_string(x));
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, std::int64_t x)
{
    f.Write(std::to_string(x));
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, std::uint64_t x)
{
    f.Write(std::to_string(x));
    return f;
}

} // namespace util
