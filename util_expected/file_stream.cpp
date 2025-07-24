// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <cstdio>
#include <cerrno>
#include <string.h>

module util_expected.file.stream;

import std;
import util_expected.error;
import util_expected.text.util;
import util_expected.win_error;

namespace util {

FileStream::FileStream(int handle) : filePath(), file(nullptr), needToClose(false), error(0)
{
    switch (handle)
    {
        case 0:
        {
            file = stdin;
            filePath = "STDIN";
            break;
        }
        case 1:
        {
            file = stdout;
            filePath = "STDOUT";
            break;
        }
        case 2:
        {
            file = stderr;
            filePath = "STDERR";
            break;
        }
        default:
        {
            error = AllocateError("invalid handle value");
            return;
        }
    }
}

FileStream::FileStream(const std::string& filePath_, OpenMode openMode) : filePath(filePath_), file(), error(0)
{
    std::string mode;
    if ((openMode & OpenMode::read) != OpenMode::none && (openMode & OpenMode::write) == OpenMode::none)
    {
        mode += "r";
    }
    if ((openMode & OpenMode::write) != OpenMode::none)
    {
        mode += "w";
        if ((openMode & OpenMode::read) != OpenMode::none)
        {
            mode += "+";
        }
    }
    if ((openMode & OpenMode::append) != OpenMode::none)
    {
        if ((openMode & (OpenMode::read | OpenMode::write)) != OpenMode::none)
        {
            std::string msg("could not open file '");
            msg.append(filePath).append("': open mode not supported");
            error = AllocateError(msg);
            return;
        }
        else
        {
            mode += "a";
        }
    }
    if ((openMode & OpenMode::binary) != OpenMode::none)
    {
        mode += "b";
    }
    std::expected<std::string, int> rv = Utf8StringToPlatformString(filePath);
    if (!rv)
    {
        error = rv.error();
        return;
    }
    std::string nativeFilePath = *rv;
#ifdef _WIN32
    errno_t err = fopen_s(&file, nativeFilePath.c_str(), mode.c_str());
    if (err)
    {
        char buf[4096];
        strerror_s(buf, sizeof(buf), err);
        std::expected<std::string, int> rv = PlatformStringToUtf8(buf);
        if (!rv)
        {
            error = rv.error();
            return;
        }
        error = AllocateError("could not open file '" + std::string(filePath) + "': " + *rv);
        return;
    }
    needToClose = true;
#elif defined(__linux) || defined(__unix) || defined(__posix) || defined(OTAVA)
    file = std::fopen(nativeFilePath.c_str(), mode.c_str());
    if (!file)
    {
        std::string msg("could not open file '");
        msg.append(filePath).append("': ").append(std::strerror(ErrorNumber()));
        std::expected<std::string, int> rv = PlatformStringToUtf8(buf);
        if (!rv)
        {
            error = rv.error();
            return;
        }
        error = AllocateError("could not open file '" + std::string(filePath) + "': " + *rv);
        return;
    }
    needToClose = true;
#else

#error unknown platform

#endif
}

FileStream::~FileStream()
{
    if (file && needToClose)
    {
        std::fclose(file);
    }
}

std::expected<int, int> FileStream::ReadByte()
{
    int result = std::fgetc(file);
    if (result == EOF)
    {
        if (std::feof(file))
        {
            return std::expected<int, int>(-1);
        }
        else
        {
#ifdef _WIN32
            char buf[4096];
            strerror_s(buf, sizeof(buf), ErrorNumber());
            std::expected<std::string, int> rv = PlatformStringToUtf8(buf);
            if (!rv) return std::unexpected<int>(rv.error());
            return std::unexpected<int>(AllocateError("could not read from file '" + filePath + "': " + *rv));
#elif defined(__linux) || defined(__unix) || defined(__posix) || defined(OTAVA)
            std::string msg("could not read from file '");
            msg.append(filePath).append(std::strerror(ErrorNumber()));
            return std::unexpected<int>(AllocateError(msg));
#else
#error unknown platform
#endif
        }
    }
    SetPosition(Position() + 1);
    return std::expected<int, int>(result);
}

std::expected<std::int64_t, int> FileStream::Read(std::uint8_t* buf, std::int64_t count)
{
    std::int64_t result = std::fread(buf, 1, count, file);
    if (std::ferror(file))
    {
#ifdef _WIN32
        char buf[4096];
        strerror_s(buf, sizeof(buf), ErrorNumber());
        std::expected<std::string, int> rv = PlatformStringToUtf8(buf);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::unexpected<int>(AllocateError("could not read from file '" + filePath + "': " + *rv));
#elif defined(__linux) || defined(__unix) || defined(__posix) || defined(OTAVA)
        std::string msg("could not read from file '");
        msg.append(filePath).append(std::strerror(ErrorNumber()));
        return std::unexpected<int>(AllocateError(msg));
#else
#error unknown platform
#endif
    }
    SetPosition(Position() + result);
    return std::expected<std::int64_t, int>(result);
}

std::expected<bool, int> FileStream::Write(std::uint8_t x)
{
    int result = std::fputc(x, file);
    if (result == EOF)
    {
#ifdef _WIN32
        char buf[4096];
        strerror_s(buf, sizeof(buf), ErrorNumber());
        std::expected<std::string, int> rv = PlatformStringToUtf8(buf);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::unexpected<int>(AllocateError("could not write to file '" + filePath + "': " + *rv));
#elif defined(__linux) || defined(__unix) || defined(__posix) || defined(OTAVA)
        std::string msg("could not write to file '");
        msg.append(filePath).append(std::strerror(ErrorNumber()));
        return std::unexpected<int>(AllocateError(msg));
#else
#error unknown platform
#endif
    }
    SetPosition(Position() + 1);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FileStream::Write(std::uint8_t* buf, std::int64_t count)
{
    std::int64_t result = std::fwrite(buf, 1, count, file);
    if (result != count)
    {
#ifdef _WIN32
        char buf[4096];
        strerror_s(buf, sizeof(buf), ErrorNumber());
        std::expected<std::string, int> rv = PlatformStringToUtf8(buf);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::unexpected<int>(AllocateError("could not write to file '" + filePath + "': " + *rv));
#elif defined(__linux) || defined(__unix) || defined(__posix) || defined(OTAVA)
        std::string msg("could not write to file '");
        msg.append(filePath).append(std::strerror(ErrorNumber()));
        return std::unexpected<int>(AllocateError(msg));
#else
#error unknown platform
#endif
    }
    SetPosition(Position() + result);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FileStream::Flush()
{
    int result = std::fflush(file);
    if (result != 0)
    {
#ifdef _WIN32
        char buf[4096];
        strerror_s(buf, sizeof(buf), ErrorNumber());
        std::expected<std::string, int> rv = PlatformStringToUtf8(buf);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::unexpected<int>(AllocateError("could not flush file '" + filePath + "': " + *rv));
#elif defined(__linux) || defined(__unix) || defined(__posix) || defined(OTAVA)
        std::string msg("could not flush file '");
        msg.append(filePath).append(std::strerror(ErrorNumber()));
        return std::unexpected<int>(AllocateError(msg));
#else
#error unknown platform
#endif
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FileStream::Seek(std::int64_t pos, Origin origin)
{
    int seekOrigin = SEEK_SET;
    switch (origin)
    {
        case Origin::seekCur:
        {
            seekOrigin = SEEK_CUR;
            break;
        }
        case Origin::seekEnd:
        {
            seekOrigin = SEEK_END;
            break;
        }
        case Origin::seekSet:
        {
            seekOrigin = SEEK_SET;
            break;
        }
    }
#ifdef _WIN32
    int result = _fseeki64(file, pos, seekOrigin);
#else
    int result = std::fseek(file, pos, seekOrigin);
#endif
    if (result != 0)
    {
#ifdef _WIN32
        char buf[4096];
        strerror_s(buf, sizeof(buf), ErrorNumber());
        std::expected<std::string, int> rv = PlatformStringToUtf8(buf);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::unexpected<int>(AllocateError("could not seek file '" + filePath + "': " + *rv));
#elif defined(__linux) || defined(__unix) || defined(__posix) || defined(OTAVA)
        std::string msg("could not seek file '");
        msg.append(filePath).append(std::strerror(ErrorNumber()));
        return std::unexpected<int>(AllocateError(msg));
#else
#error unknown platform
#endif
    }
    switch (origin)
    {
        case Origin::seekCur:
        {
            SetPosition(Position() + pos);
            break;
        }
        case Origin::seekEnd:
        {
            SetPosition(Size() + pos);
            break;
        }
        case Origin::seekSet:
        {
            SetPosition(pos);
            break;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<std::int64_t, int> FileStream::Tell()
{
    std::int64_t result = std::ftell(file);
    if (result == -1)
    {
#ifdef _WIN32
        char buf[4096];
        strerror_s(buf, sizeof(buf), ErrorNumber());
        std::expected<std::string, int> rv = PlatformStringToUtf8(buf);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::unexpected<int>(AllocateError("could not tell file '" + filePath + "': " + *rv));
#elif defined(__linux) || defined(__unix) || defined(__posix) || defined(OTAVA)
        std::string msg("could not tell file '");
        msg.append(filePath).append(std::strerror(ErrorNumber()));
        return std::unexpected<int>(AllocateError(msg));
#else
#error unknown platform
#endif
    }
    return std::expected<std::int64_t, int>(result);
}

std::int64_t FileStream::Size() const
{
    std::filesystem::path path(filePath);
    return std::filesystem::file_size(path);
}

std::expected<std::string, int> ReadFile(const std::string& filePath)
{
    return ReadFile(filePath, false);
}

std::expected<std::string, int> ReadFile(const std::string& filePath, bool doNotSkipBOM)
{
    std::string s;
    FileStream fs(filePath, OpenMode::read | OpenMode::binary);
    if (!fs.Valid()) return std::unexpected<int>(fs.Error());
    std::int64_t n = fs.Size();
    for (std::int64_t i = 0; i < n; ++i)
    {
        std::expected<int, int> rv = fs.ReadByte();
        if (!rv) return std::unexpected<int>(rv.error());
        int c = *rv;
        bool skip = false;
        if (!doNotSkipBOM && i <= 2)
        {
            if (i == 0 && c == 0xEF)
            {
                skip = true;
            }
            else if (i == 1 && c == 0xBB)
            {
                skip = true;
            }
            else if (i == 2 && c == 0xBF)
            {
                skip = true;
            }
        }
        if (!skip)
        {
            if (c != -1)
            {
                s.append(1, c);
            }
            else
            {
                std::string msg("unexpected end of '");
                msg.append(filePath).append("'");
                return std::unexpected<int>(AllocateError(msg));
            }
        }
    }
    return std::expected<std::string, int>(s);
}

} // util
