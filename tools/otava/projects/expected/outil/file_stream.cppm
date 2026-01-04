// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.file.stream;

import std;
import util.stream;

export namespace util {

enum class OpenMode : int
{
    none = 0,
    read = 1 << 0,
    write = 1 << 1,
    append = 1 << 2,
    binary = 1 << 3
};

inline constexpr OpenMode operator|(OpenMode left, OpenMode right)
{
    return OpenMode(int(left) | int(right));
}

inline constexpr OpenMode operator&(OpenMode left, OpenMode right)
{
    return OpenMode(int(left) & int(right));
}

inline constexpr OpenMode operator~(OpenMode mode)
{
    return OpenMode(~int(mode));
}

class FileStream : public Stream
{
public:
    explicit FileStream(int handle);
    FileStream(const std::string& filePath_, OpenMode openMode);
    ~FileStream() override;
    inline const std::string& FilePath() const { return filePath; }
    std::expected<int, int> ReadByte() override;
    std::expected<std::int64_t, int> Read(std::uint8_t* buf, std::int64_t count) override;
    std::expected<bool, int> Write(std::uint8_t x) override;
    std::expected<bool, int> Write(std::uint8_t* buf, std::int64_t count) override;
    std::expected<bool, int> Flush() override;
    std::expected<bool, int> Seek(std::int64_t pos, Origin origin) override;
    std::expected<std::int64_t, int> Tell() override;
    std::int64_t Size() const;
    inline bool Valid() const { return error == 0; }
    inline explicit operator bool() const { return Valid(); }
    inline int Error() const { return error; }
private:
    std::string filePath;
    std::FILE* file;
    bool needToClose;
    int error;
};

std::expected<std::string, int> ReadFile(const std::string& filePath);
std::expected<std::string, int> ReadFile(const std::string& filePath, bool doNotSkipBOM);

} // util
