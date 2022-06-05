// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.classmap;

import util;

namespace soul::slg {

using namespace util;

void MakeCompressedClassMap(const std::string& root, const std::string& classMapName, bool verbose)
{
    std::string classMapFileName = Path::Combine(root, classMapName);
    std::string compressedClassMapFileName = Path::Combine(root, classMapName + ".compressed");
    FileStream inputFileStream(classMapFileName, OpenMode::read | OpenMode::binary);
    BufferedStream bufferedInputFileStream(inputFileStream);
    BinaryStreamReader reader(bufferedInputFileStream);
    int32_t size = reader.ReadInt();
    FileStream outputFileStream(compressedClassMapFileName, OpenMode::write | OpenMode::binary);
    BinaryStreamWriter rawWriter(outputFileStream);
    rawWriter.Write(size);
    DeflateStream compressedStream(CompressionMode::compress, outputFileStream);
    BinaryStreamWriter writer(compressedStream);
    for (int64_t i = 0; i < size; ++i)
    {
        uint32_t cls = reader.ReadInt();
        writer.Write(cls);
    }
    if (verbose)
    {
        std::cout << "==> " << compressedClassMapFileName << std::endl;
    }
}

void MakeResourceFile(const std::string& root, const std::string& classMapName, bool verbose)
{
    std::string resourceFileName = Path::Combine(root, classMapName + ".rc");
    std::string compressedClassMapFileName = "./" + classMapName + ".compressed";
    std::ofstream resourceFile(resourceFileName);
    CodeFormatter formatter(resourceFile);
    formatter.WriteLine(classMapName + " RCDATA \"" + compressedClassMapFileName + "\"");
    if (verbose)
    {
        std::cout << "==> " << resourceFileName << std::endl;
    }
}

} // namespace soul::slg
