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

module util_expected.code.formatter;

import util_expected.ansi;
import util_expected.error;
import util_expected.unicode;

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

std::expected<bool, int> WriteUtf16StrToStdOutOrStdErr(const std::u16string& str, FILE* file)
{
    //  precondition: file must be stdout or stderr
    if (file != stdout && file != stderr)
    {
        return std::unexpected<int>(AllocateError("WriteUtf16StrToStdOutOrStdErr: precondition violation : file must be stdout or stderr"));
    }
    UnicodeWriteGuard unicodeWriteGuard;
    size_t result = std::fwrite(str.c_str(), sizeof(char16_t), str.length(), file);
    if (result != str.length())
    {
        return std::unexpected<int>(AllocateError("could not write Unicode text"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> WriteUtf8(std::ostream& s, const std::string& str)
{
    if (&s == &std::cout && !IsHandleRedirected(1))
    {
        std::expected<std::string, int> rv = AnsiIntercept(1, str);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string ps = std::move(*rv);
        if (!ps.empty())
        {
            std::expected<std::u16string, int> rv = ToUtf16(ps);
            if (!rv) return std::unexpected<int>(rv.error());
            std::u16string utf16Str = std::move(*rv);
            std::expected<bool, int> wrv = WriteUtf16StrToStdOutOrStdErr(utf16Str, stdout);
            if (!wrv) return std::unexpected<int>(wrv.error());
        }
    }
    else if (&s == &std::cerr && !IsHandleRedirected(2))
    {
        std::expected<std::string, int> rv = AnsiIntercept(2, str);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string ps = std::move(*rv);
        if (!ps.empty())
        {
            std::expected<std::u16string, int> rv = ToUtf16(ps);
            if (!rv) return std::unexpected<int>(rv.error());
            std::u16string utf16Str = std::move(*rv);
            std::expected<bool, int> wrv = WriteUtf16StrToStdOutOrStdErr(utf16Str, stderr);
            if (!wrv) return std::unexpected<int>(wrv.error());
        }
    }
    else
    {
        s << str;
    }
    return std::expected<bool, int>(true);
}

#elif defined(__linux) || defined(__unix) || defined(__posix)

bool IsHandleRedirected(int handle)
{
    return !isatty(handle);
}

std::expected<bool, int> WriteUtf8(std::ostream& s, const std::string& str)
{
    s << str;
    return std::expected<bool, int>(true);
}

#else

#error unknown platform

#endif

std::expected<bool, int> CodeFormatter::Write(const std::string& text)
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
        std::expected<bool, int> rv = WriteUtf8(stream, "length=" + std::to_string(text.length()));
        if (!rv) return rv;
    }
    else
    {
        std::expected<bool, int> rv = WriteUtf8(stream, text);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CodeFormatter::WriteLine(const std::string& text)
{
    std::expected<bool, int> rv = Write(text);
    if (!rv) return rv;
    NewLine();
    return std::expected<bool, int>(true);
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
    std::expected<bool, int> rv = f.Write(s);
    if (!rv) f.SetError(rv.error());
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, const char* s)
{
    std::expected<bool, int> rv = f.Write(s);
    if (!rv) f.SetError(rv.error());
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, char c)
{
    std::expected<bool, int> rv = f.Write(std::string(1, c));
    if (!rv) f.SetError(rv.error());
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, bool b)
{
    if (b)
    {
        std::expected<bool, int> rv = f.Write("true");
        if (!rv) f.SetError(rv.error());
    }
    else
    {
        std::expected<bool, int> rv = f.Write("false");
        if (!rv) f.SetError(rv.error());
    }
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, int x)
{
    std::expected<bool, int> rv = f.Write(std::to_string(x));
    if (!rv) f.SetError(rv.error());
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, double x)
{
    std::expected<bool, int> rv = f.Write(std::to_string(x));
    if (!rv) f.SetError(rv.error());
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, std::int64_t x)
{
    std::expected<bool, int> rv = f.Write(std::to_string(x));
    if (!rv) f.SetError(rv.error());
    return f;
}

CodeFormatter& operator<<(CodeFormatter& f, std::uint64_t x)
{
    std::expected<bool, int> rv = f.Write(std::to_string(x));
    if (!rv) f.SetError(rv.error());
    return f;
}

} // namespace util
