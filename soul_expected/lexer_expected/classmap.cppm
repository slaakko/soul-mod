// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.classmap;

import std;
import util_expected;

export namespace soul_expected::lexer {

template<typename Char>
class ClassMap
{
public:
    ClassMap(const std::int32_t* data_, std::int32_t upperBound_) : data(data_), upperBound(upperBound_) {}
    std::int32_t GetClass(Char c) const
    {
        std::int32_t i = static_cast<std::int32_t>(c);
        if (i < upperBound)
        {
            return data[i];
        }
        else
        {
            return -1;
        }
    }
private:
    const std::int32_t* data;
    std::int32_t upperBound;
};

template<typename Char>
std::expected<ClassMap<Char>*, int> MakeClassMap(const std::string& classMapName)
{
    auto p = util::GetPathToExecutable();
    if (!p) return std::unexpected<int>(p.error());
    auto u = util::GetFullPath(*p);
    if (!u) return std::unexpected<int>(u.error());
    std::string currentExecutableName = util::Path::GetFileName(*u);
    util::BinaryResourcePtr resource(currentExecutableName, classMapName);
    if (!resource) return std::unexpected<int>(resource.Error());
    util::MemoryStream memoryStream(resource.Data(), resource.Size());
    util::BinaryStreamReader rawReader(memoryStream);
    std::expected<int32_t, int> rv = rawReader.ReadInt();
    if (!rv) return std::unexpected<int>(rv.error());
    std::int32_t size = *rv;
    std::int32_t* data = new std::int32_t[size];
    util::DeflateStream compressedStream(util::CompressionMode::decompress, memoryStream);
    if (!compressedStream) return std::unexpected<int>(compressedStream.Error());
    util::BinaryStreamReader reader(compressedStream);
    for (std::int64_t i = 0; i < size; ++i)
    {
        std::expected<int32_t, int> rv = reader.ReadInt();
        if (!rv) return std::unexpected<int>(rv.error());
        std::int32_t x = *rv;
        data[i] = x;
    }
    ClassMap<Char>* classMap = new ClassMap<Char>(data, size);
    return std::expected<ClassMap<Char>*, int>(classMap);
}

template<typename Char>
std::expected<ClassMap<Char>*, int> MakeClassMap(const std::string& moduleFileName, const std::string& classMapName, util::ResourceFlags resourceFlags)
{
    util::BinaryResourcePtr resource(moduleFileName, classMapName, resourceFlags);
    if (!resource) return std::unexpected<int>(resource.Error());
    util::MemoryStream memoryStream(resource.Data(), resource.Size());
    util::BinaryStreamReader rawReader(memoryStream);
    std::int32_t size = rawReader.ReadInt();
    std::expected<int32_t, int> rv = rawReader.ReadInt();
    if (!rv) return std::unexpected<int>(rv.error());
    std::int32_t* data = new std::int32_t[size];
    util::DeflateStream compressedStream(util::CompressionMode::decompress, memoryStream);
    if (!compressedStream) return std::unexpected<int>(compressedStream.Error());
    util::BinaryStreamReader reader(compressedStream);
    for (std::int64_t i = 0; i < size; ++i)
    {
        std::expected<int32_t, int> rv = reader.ReadInt();
        if (!rv) return std::unexpected<int>(rv.error());
        std::int32_t x = *rv;
        data[i] = x;
    }
    ClassMap<Char>* classMap = new ClassMap<Char>(data, size);
    return std::expected<ClassMap<Char>*, int>(classMap);
}

} // soul_expected::lexer
