// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.classmap;

import util;

namespace soul::slg {

void MakeCompressedClassMap(const std::string& root, const std::string& classMapName, bool verbose)
{
    std::string classMapFileName = util::Path::Combine(root, classMapName);
    std::string compressedClassMapFileName = util::Path::Combine(root, classMapName + ".compressed");
    util::FileStream inputFileStream(classMapFileName, util::OpenMode::read | util::OpenMode::binary);
    util::BufferedStream bufferedInputFileStream(inputFileStream);
    util::BinaryStreamReader reader(bufferedInputFileStream);
    std::int32_t size = reader.ReadInt();
    util::FileStream outputFileStream(compressedClassMapFileName, util::OpenMode::write | util::OpenMode::binary);
    util::BinaryStreamWriter rawWriter(outputFileStream);
    rawWriter.Write(size);
    util::DeflateStream compressedStream(util::CompressionMode::compress, outputFileStream);
    util::BinaryStreamWriter writer(compressedStream);
    for (std::int64_t i = 0; i < size; ++i)
    {
        std::uint32_t cls = reader.ReadInt();
        writer.Write(cls);
    }
    if (verbose)
    {
        std::cout << "==> " << compressedClassMapFileName << std::endl;
    }
}

void MakeResourceFile(const std::string& root, const std::string& classMapName, bool verbose)
{
    std::string resourceFileName = util::Path::Combine(root, classMapName + ".rc");
    std::string compressedClassMapFileName = "./" + classMapName + ".compressed";
    std::ofstream resourceFile(resourceFileName);
    util::CodeFormatter formatter(resourceFile);
    formatter.WriteLine(classMapName + " RCDATA \"" + compressedClassMapFileName + "\"");
    if (verbose)
    {
        std::cout << "==> " << resourceFileName << std::endl;
    }
}

} // namespace soul::slg
