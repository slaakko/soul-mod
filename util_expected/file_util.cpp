// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util_expected.file.util;

import util_expected.error;
import util_expected.file.stream;
import util_expected.buffered.stream;
import util_expected.binary.stream.reader;
import util_expected.binary.stream.writer;
import util_expected.text.util;

namespace util {

std::expected<bool, int> CopyFile(const std::string& source, const std::string& dest, bool force, bool verbose)
{
    if (!std::filesystem::exists(source))
    {
        if (verbose)
        {
            std::cout << "source file '" + source + "' does not exist" << std::endl;
        }
        return std::expected<bool, int>(false);
    }
    if (force || !std::filesystem::exists(dest) || std::filesystem::last_write_time(source) > std::filesystem::last_write_time(dest))
    {
        std::int64_t size = std::filesystem::file_size(source);
        {
            FileStream sourceFile(source, OpenMode::read | OpenMode::binary);
            if (!sourceFile) return std::unexpected<int>(sourceFile.Error());
            BufferedStream bufferedSource(sourceFile);
            BinaryStreamReader reader(bufferedSource);
            FileStream destFile(dest, OpenMode::write | OpenMode::binary);
            if (!destFile) return std::unexpected<int>(destFile.Error());
            BufferedStream bufferedDest(destFile);
            BinaryStreamWriter writer(bufferedDest);
            for (std::int64_t i = 0; i < size; ++i)
            {
                std::expected<uint8_t, int> rv = reader.ReadByte();
                if (!rv) return std::unexpected<int>(rv.error());
                std::uint8_t x = *rv;
                std::expected<bool, int> brv = writer.Write(x);
                if (!brv) return brv;
            }
        }
        std::error_code ec;
        std::filesystem::last_write_time(dest, std::filesystem::last_write_time(source), ec);
        if (ec)
        {
            std::expected<std::string, int> rv = PlatformStringToUtf8(ec.message());
            if (!rv) return std::unexpected<int>(rv.error());
            return std::unexpected<int>(AllocateError("could not set write time of file '" + dest + "': " + *rv));
        }
        if (verbose)
        {
            std::cout << source << " -> " << dest << std::endl;
        }
    }
    return std::expected<bool, int>(true);
}

} // namespace util

