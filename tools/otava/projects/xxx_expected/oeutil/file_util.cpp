// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.file.util;

import util.error;
import util.file.stream;
import util.buffered.stream;
import util.binary.stream.reader;
import util.binary.stream.writer;
import util.text.util;

namespace util {

std::expected<bool, int> CopyFile(const std::string& source, const std::string& dest, bool force, bool verbose)
{
    if (!ort_path_exists(source.c_str()))
    {
        if (verbose)
        {
            std::cout << "source file '" << source << "' does not exist" << "\n";
        }
        return std::expected<bool, int>(false);
    }
    if (force || !ort_path_exists(dest.c_str()) || ort_last_write_time(source.c_str()) > ort_last_write_time(dest.c_str()))
    {
        std::int64_t size = ort_file_size(source.c_str());
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
        ort_set_last_write_time(dest.c_str(), source.c_str());
        if (verbose)
        {
            std::cout << source << " -> " << dest << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

} // namespace util

