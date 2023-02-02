// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module class_info_index;

import util.binary.resource.ptr;
import util.path;
import util.system;
import util.memory.stream;

namespace info {

class_index* index = nullptr;

class_index* get_index()
{
    if (!index)
    {
        std::string currentExecutableName = util::Path::GetFileName(util::GetFullPath(util::GetPathToExecutable()));
        util::BinaryResourcePtr resource(currentExecutableName, "CLASS_INDEX");
        util::MemoryStream memoryStream(resource.Data(), resource.Size());
        util::BinaryStreamReader reader(memoryStream);
        index = new class_index();
        index->read(reader);
    }
    return index;
}

class_info::class_info() : key(class_key::cls), name(), bases()
{
}

class_info::class_info(class_id id_, class_key key_, const std::string& name_) : id(id_), key(key_), name(name_)
{
}

void class_info::add_base(const class_id& id)
{
    bases.push_back(id);
}

void class_info::read(util::BinaryStreamReader& reader)
{
    uint64_t h = reader.ReadULong();
    uint64_t l = reader.ReadULong();
    id = std::make_pair(h, l);
    key = static_cast<class_key>(reader.ReadByte());
    name = reader.ReadUtf8String();
    int32_t nb = reader.ReadInt();
    for (int i = 0; i < nb; ++i)
    {
        uint64_t h = reader.ReadULong();
        uint64_t l = reader.ReadULong();
        add_base(std::make_pair(h, l));
    }
}

void class_info::write(util::BinaryStreamWriter& writer)
{
    uint64_t h = id.first;
    uint64_t l = id.second;
    writer.Write(h);
    writer.Write(l);
    writer.Write(static_cast<uint8_t>(key));
    writer.Write(name);
    int32_t nb = bases.size();
    writer.Write(nb);
    for (int i = 0; i < nb; ++i)
    {
        uint64_t h = bases[i].first;
        uint64_t l = bases[i].second;
        writer.Write(h);
        writer.Write(l);
    }
}

class_index::class_index()
{
}

void class_index::imp(const class_index& that, bool import_map)
{
    for (const class_info& info : that.get_infos())
    {
        add_class(info);
    }
    if (import_map)
    {
        for (const auto& pair : that.map)
        {
            map_class(pair.second);
        }
    }
}

void class_index::add_class(const class_info& info)
{
    infos.push_back(info);
    map_class(info);
}

void class_index::map_class(const class_info& info)
{
    map[info.get_id()] = info;
}

void class_index::read(util::BinaryStreamReader& reader)
{
    int32_t n = reader.ReadInt();
    for (int32_t i = 0; i < n; ++i)
    {
        class_info info;
        info.read(reader);
        add_class(info);
    }
}

void class_index::write(util::BinaryStreamWriter& writer, bool write_mapped)
{
    if (write_mapped)
    {
        int32_t n = map.size();
        writer.Write(n);
        for (auto& id_info_pair : map)
        {
            class_info& info = id_info_pair.second;
            info.write(writer);
        }
    }
    else
    {
        int32_t n = infos.size();
        writer.Write(n);
        for (int32_t i = 0; i < n; ++i)
        {
            class_info& info = infos[i];
            info.write(writer);
        }
    }
}

void class_index::write(util::BinaryStreamWriter& writer)
{
    write(writer, false);
}

const class_info* class_index::get_class_info(const class_id& id) const
{
    auto it = map.find(id);
    if (it != map.end())
    {
        return &(it->second);
    }
    return nullptr;
}

bool is_same_or_has_base(uint64_t derived_high, uint64_t derived_low, uint64_t base_high, uint64_t base_low)
{
    if (derived_high == base_high && derived_low == base_low)
    {
        return true;
    }
    else
    {
        class_index* index = get_index();
        const class_info* info = index->get_class_info(std::make_pair(derived_high, derived_low));
        if (info)
        {
            int n = info->base_class_ids().size();
            for (int i = 0; i < n; ++i)
            {
                class_id id = info->base_class_ids()[i];
                if (is_same_or_has_base(id.first, id.second, base_high, base_low))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

} // namespace info
