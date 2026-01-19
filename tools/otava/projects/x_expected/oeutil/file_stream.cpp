// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.file.stream;

import std;
import util.error;
import util.text.util;

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
    file = std::fopen(filePath.c_str(), mode.c_str());
    if (!file)
    {
        std::string msg("could not open file '");
        int errorNumber = ort_error_number();
        msg.append(filePath).append("': ").append(ort_error_str(errorNumber));
        error = AllocateError(msg);
        return;
    }
    needToClose = true;
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
            int errorNumber = ort_error_number();
            std::string errorStr = ort_error_str(errorNumber);
            return std::unexpected<int>(AllocateError("could not read from file '" + filePath + "': " + errorStr));
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
        int errorNumber = ort_error_number();
        std::string errorStr = ort_error_str(errorNumber);
        return std::unexpected<int>(AllocateError("could not read from file '" + filePath + "': " + errorStr));
    }
    SetPosition(Position() + result);
    return std::expected<std::int64_t, int>(result);
}

std::expected<bool, int> FileStream::Write(std::uint8_t x)
{
    int result = std::fputc(x, file);
    if (result == EOF)
    {
        int errorNumber = ort_error_number();
        std::string errorStr = ort_error_str(errorNumber);
        return std::unexpected<int>(AllocateError("could not write to file '" + filePath + "': " + errorStr));
    }
    SetPosition(Position() + 1);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FileStream::Write(std::uint8_t* buf, std::int64_t count)
{
    std::int64_t result = std::fwrite(buf, 1, count, file);
    if (result != count)
    {
        int errorNumber = ort_error_number();
        std::string errorStr = ort_error_str(errorNumber);
        return std::unexpected<int>(AllocateError("could not write to file '" + filePath + "': " + errorStr));
    }
    SetPosition(Position() + result);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FileStream::Flush()
{
    int result = std::fflush(file);
    if (result != 0)
    {
        int errorNumber = ort_error_number();
        std::string errorStr = ort_error_str(errorNumber);
        return std::unexpected<int>(AllocateError("could not flush file '" + filePath + "': " + errorStr));
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
    int result = std::fseek(file, static_cast<long>(pos), seekOrigin);
    if (result != 0)
    {
        int errorNumber = ort_error_number();
        std::string errorStr = ort_error_str(errorNumber);
        return std::unexpected<int>(AllocateError("could not seek file '" + filePath + "': " + errorStr));
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
        int errorNumber = ort_error_number();
        std::string errorStr = ort_error_str(errorNumber);
        return std::unexpected<int>(AllocateError("could not tell file '" + filePath + "': " + errorStr));
    }
    return std::expected<std::int64_t, int>(result);
}

std::int64_t FileStream::Size() const
{
    return ort_file_size(filePath.c_str());
}

std::expected<std::string, int> ReadFile(const std::string& filePath)
{
    return ReadFile(filePath, false);
}

std::expected<std::string, int> ReadFile(const std::string& filePath, bool doNotSkipBOM)
{
    std::string s;
    FileStream fs(filePath, OpenMode::read | OpenMode::binary);
    if (!fs) return std::unexpected<int>(fs.Error());
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
                s.append(1, static_cast<char>(c));
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
