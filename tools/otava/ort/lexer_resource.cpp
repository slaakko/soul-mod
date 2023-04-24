// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module lexer_resource;

import util.path;
import util.system;
import util.binary.resource.ptr;
import util.memory.stream;
import util.binary.stream.reader;
import util.deflate.stream;
import soul.lexer.classmap;

int32_t* read_lexer_resource(const char* resource_name, int32_t& size)
{
    std::string currentExecutableName = util::Path::GetFileName(util::GetFullPath(util::GetPathToExecutable()));
    util::BinaryResourcePtr resource(currentExecutableName, resource_name);
    util::MemoryStream memoryStream(resource.Data(), resource.Size());
    util::BinaryStreamReader rawReader(memoryStream);
    size = rawReader.ReadInt();
    int32_t* data = new int32_t[size];
    util::DeflateStream compressedStream(util::CompressionMode::decompress, memoryStream);
    util::BinaryStreamReader reader(compressedStream);
    for (int64_t i = 0; i < size; ++i)
    {
        int32_t x = reader.ReadInt();
        data[i] = x;
    }
    return data;
}

void free_lexer_resource(int32_t* lexer_resource)
{
    delete[](lexer_resource);
}
