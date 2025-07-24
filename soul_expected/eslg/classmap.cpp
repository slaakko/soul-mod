// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.slg.classmap;

import util_expected;

namespace soul_expected::slg {

std::expected<bool, int> MakeCompressedClassMap(const std::string& root, const std::string& classMapName, bool verbose)
{
    std::string classMapFileName = util::Path::Combine(root, classMapName);
    std::string compressedClassMapFileName = util::Path::Combine(root, classMapName + ".compressed");
    util::FileStream inputFileStream(classMapFileName, util::OpenMode::read | util::OpenMode::binary);
    if (!inputFileStream) return std::unexpected<int>(inputFileStream.Error());
    util::BufferedStream bufferedInputFileStream(inputFileStream);
    util::BinaryStreamReader reader(bufferedInputFileStream);
    std::expected<int32_t, int> rv = reader.ReadInt();
    if (!rv) return std::unexpected<int>(rv.error());
    std::int32_t size = *rv;
    util::FileStream outputFileStream(compressedClassMapFileName, util::OpenMode::write | util::OpenMode::binary);
    if (!outputFileStream) return std::unexpected<int>(outputFileStream.Error());
    util::BinaryStreamWriter rawWriter(outputFileStream);
    std::expected<bool, int> wrv = rawWriter.Write(size);
    if (!wrv) return wrv;
    util::DeflateStream compressedStream(util::CompressionMode::compress, outputFileStream);
    if (!compressedStream) return std::unexpected<int>(compressedStream.Error());
    util::BinaryStreamWriter writer(compressedStream);
    for (std::int64_t i = 0; i < size; ++i)
    {
        rv = reader.ReadInt();
        if (!rv) return std::unexpected<int>(rv.error());
        std::uint32_t cls = *rv;
        wrv = writer.Write(cls);
        if (!wrv) return wrv;
    }
    if (verbose)
    {
        std::cout << "==> " << compressedClassMapFileName << std::endl;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MakeResourceFile(const std::string& root, const std::string& classMapName, bool verbose)
{
    std::string resourceFileName = util::Path::Combine(root, classMapName + ".rc");
    std::string compressedClassMapFileName = "./" + classMapName + ".compressed";
    std::ofstream resourceFile(resourceFileName);
    if (!resourceFile) return std::unexpected<int>(util::AllocateError("could not create file '" + resourceFileName + "'"));
    util::CodeFormatter formatter(resourceFile);
    std::expected<bool, int> rv = formatter.WriteLine(classMapName + " RCDATA \"" + compressedClassMapFileName + "\"");
    if (!rv) return rv;
    if (verbose)
    {
        std::cout << "==> " << resourceFileName << std::endl;
    }
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::slg
