// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.class_info_index;

import util.binary.resource.ptr;
import util.error;
import util.path;
import util.system;
import util.memory.stream;

namespace otava::symbols {

class_index* index = nullptr;

class_index* get_index()
{
    if (!index)
    {
        std::expected<std::string, int> rv = util::GetPathToExecutable();
        if (!rv)
        {
            std::cerr << util::GetErrorMessage(rv.error(), true) << "\n";
            std::exit(1);
        }
        std::string exePath = std::move(*rv);
        rv = util::GetFullPath(exePath);
        if (!rv)
        {
            std::cerr << util::GetErrorMessage(rv.error(), true) << "\n";
            std::exit(1);
        }
        std::string fullPath = std::move(*rv);
        std::string currentExecutableName = util::Path::GetFileName(fullPath);
        util::BinaryResourcePtr resource(currentExecutableName, "CLASS_INDEX");
        util::MemoryStream memoryStream(resource.Data(), resource.Size());
        util::BinaryStreamReader reader(memoryStream);
        index = new class_index();
        std::expected<bool, int> irv = index->read(reader);
        if (!irv)
        {
            std::cerr << util::GetErrorMessage(irv.error(), true) << "\n";
            std::exit(1);
        }
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

std::expected<bool, int> class_info::read(util::BinaryStreamReader& reader)
{
    std::expected<std::uint64_t, int> lrv = reader.ReadULong();
    if (!lrv) return std::unexpected<int>(lrv.error());
    std::uint64_t h = *lrv;
    lrv = reader.ReadULong();
    if (!lrv) return std::unexpected<int>(lrv.error());
    std::uint64_t l = *lrv;
    id = std::make_pair(h, l);
    std::expected<std::uint8_t, int> brv = reader.ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t b = *brv;
    key = static_cast<class_key>(b);
    std::expected<std::string, int> srv = reader.ReadUtf8String();
    if (!srv) return std::unexpected<int>(srv.error());
    name = *srv;
    std::expected<std::int64_t, int> orv = reader.ReadLong();
    if (!orv) return std::unexpected<int>(orv.error());
    size = *orv;
    std::expected<std::int32_t, int> irv = reader.ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    std::int32_t nb = *irv;
    for (int i = 0; i < nb; ++i)
    {
        lrv = reader.ReadULong();
        if (!lrv) return std::unexpected<int>(lrv.error());
        std::uint64_t h = *lrv;
        lrv = reader.ReadULong();
        if (!lrv) return std::unexpected<int>(lrv.error());
        std::uint64_t l = *lrv;
        add_base(std::make_pair(h, l));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> class_info::write(util::BinaryStreamWriter& writer)
{
    std::uint64_t h = id.first;
    std::uint64_t l = id.second;
    std::expected<bool, int>  rv = writer.Write(h);
    if (!rv) return rv;
    rv = writer.Write(l);
    if (!rv) return rv;
    rv = writer.Write(static_cast<std::uint8_t>(key));
    if (!rv) return rv;
    rv = writer.Write(name);
    if (!rv) return rv;
    rv = writer.Write(size);
    if (!rv) return rv;
    std::int32_t nb = bases.size();
    rv = writer.Write(nb);
    if (!rv) return rv;
    for (int i = 0; i < nb; ++i)
    {
        std::uint64_t h = bases[i].first;
        std::uint64_t l = bases[i].second;
        rv = writer.Write(h);
        if (!rv) return rv;
        rv = writer.Write(l);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
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

std::expected<bool, int> class_index::read(util::BinaryStreamReader& reader)
{
    std::expected<std::int32_t, int> irv = reader.ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    std::int32_t n = *irv;
    for (std::int32_t i = 0; i < n; ++i)
    {
        std::unique_ptr<class_info> info(new class_info());
        std::expected<bool, int> rv = info->read(reader);
        if (!rv) return rv;
        add_class(info);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> class_index::write(util::BinaryStreamWriter& writer)
{
    std::int32_t n = infos.size();
    std::expected<bool, int> rv = writer.Write(n);
    if (!rv) return rv;
    for (std::int32_t i = 0; i < n; ++i)
    {
        class_info* info = infos[i].get();
        rv = info->write(writer);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
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

} // namespace otava::symbols
