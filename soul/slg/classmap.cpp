// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.classmap;

import util;

namespace soul::slg {

using namespace util;

void MakeClassMap(const std::string& root, const std::string& classMapName, int32_t upperBound)
{
    std::string classMapFileName = Path::Combine(root, classMapName);
    std::string compressedClassMapFileName = Path::Combine(root, classMapName + ".compressed");
    FileStream inputFileStream(classMapFileName, OpenMode::read | OpenMode::binary);
    int64_t size = inputFileStream.Size();
    BufferedStream bufferedInputFileStream(inputFileStream);
    BinaryStreamReader reader(bufferedInputFileStream);
    FileStream outputFileStream(compressedClassMapFileName, OpenMode::write | OpenMode::binary);
    BufferedStream bufferedOutputFileStream(outputFileStream);
    BinaryStreamWriter rawWriter(bufferedOutputFileStream);
    rawWriter.Write(size);
    rawWriter.Write(upperBound);
    DeflateStream compressedStream(CompressionMode::compress, bufferedOutputFileStream);
    BufferedStream bufferedCompressedStream(compressedStream);
    BinaryStreamWriter writer(bufferedCompressedStream);
    for (int64_t i = 0; i < size; ++i)
    {
        uint8_t x = reader.ReadByte();
        writer.Write(x);
    }
}

void MakeResourceFile(const std::string& root, const std::string& classMapName)
{
    std::string resourceFileName = Path::Combine(root, classMapName + ".rc");
    std::string compressedClassMapFileName = Path::Combine(root, classMapName + ".compressed");
    std::ofstream resourceFile(resourceFileName);
    CodeFormatter formatter(resourceFile);
    formatter.WriteLine(classMapName + " RCDATA \"" + compressedClassMapFileName + "\"");
}

} // namespace soul::slg
