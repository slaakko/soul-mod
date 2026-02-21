// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.class_info_index;

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

class_info::class_info() : id(), key(class_key::cls), name(), bases(), size(0)
{
}

class_info::class_info(class_id id_, class_key key_, const std::string& name_, std::int64_t size_) : id(id_), key(key_), name(name_), size(size_)
{
}

void class_info::add_base(const class_id& id)
{
    bases.push_back(id);
}

void class_info::read(util::BinaryStreamReader& reader)
{
    std::uint64_t h = reader.ReadULong();
    std::uint64_t l = reader.ReadULong();
    id = std::make_pair(h, l);
    key = static_cast<class_key>(reader.ReadByte());
    name = reader.ReadUtf8String();
    size = reader.ReadLong();
    std::int32_t nb = reader.ReadInt();
    for (int i = 0; i < nb; ++i)
    {
        std::uint64_t h = reader.ReadULong();
        std::uint64_t l = reader.ReadULong();
        add_base(std::make_pair(h, l));
    }
}

void class_info::write(util::BinaryStreamWriter& writer)
{
    std::uint64_t h = id.first;
    std::uint64_t l = id.second;
    writer.Write(h);
    writer.Write(l);
    writer.Write(static_cast<std::uint8_t>(key));
    writer.Write(name);
    writer.Write(size);
    std::int32_t nb = bases.size();
    writer.Write(nb);
    for (int i = 0; i < nb; ++i)
    {
        std::uint64_t h = bases[i].first;
        std::uint64_t l = bases[i].second;
        writer.Write(h);
        writer.Write(l);
    }
}

class_index::class_index()
{
}

void class_index::add_class(std::unique_ptr<class_info>& info)
{
    class_info* prev = get_class_info(info->get_id());
    if (!prev)
    {
        map[info->get_id()] = info.get();
        infos.push_back(std::unique_ptr<class_info>(info.release()));
    }
}

void class_index::import(const class_index& that)
{
    for (const auto& info : that.infos)
    {
        if (!get_class_info(info->get_id()))
        {
            std::unique_ptr<class_info> i(new class_info(*info.get()));
            add_class(i);
        }
    }
}

void class_index::read(util::BinaryStreamReader& reader)
{
    std::int32_t n = reader.ReadInt();
    for (std::int32_t i = 0; i < n; ++i)
    {
        std::unique_ptr<class_info> info(new class_info());
        info->read(reader);
        add_class(info);
    }
}

void class_index::write(util::BinaryStreamWriter& writer)
{
    std::int32_t n = infos.size();
    writer.Write(n);
    for (std::int32_t i = 0; i < n; ++i)
    {
        class_info* info = infos[i].get();
        info->write(writer);
    }
}

class_info* class_index::get_class_info(const class_id& id)
{
    auto it = map.find(id);
    if (it != map.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

std::pair<std::int64_t, bool> compute_delta(class_index* index, class_info* derived, class_info* base)
{
    if (derived == base) return std::make_pair(static_cast<std::int64_t>(0), true);
    std::int64_t delta = 0;
    int n = derived->base_class_ids().size();
    for (int i = 0; i < n; ++i)
    {
        class_id id = derived->base_class_ids()[i];
        class_info* bc = index->get_class_info(id);
        if (bc)
        {
            std::pair<std::int64_t, bool> bcp = compute_delta(index, bc, base);
            std::int64_t bc_delta = bcp.first;
            bool bc_found = bcp.second;
            if (bc_found)
            {
                return std::make_pair(delta + bc_delta, true);
            }
            std::int64_t bc_size = bc->get_size();
            delta += bc_size;
        }
    }
    return std::make_pair(static_cast<std::int64_t>(0), false);
}

} // namespace info
