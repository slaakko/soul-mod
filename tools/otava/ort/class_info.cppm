// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module class_info_index;

import std;
import util.binary.stream.reader;
import util.binary.stream.writer;

export namespace info {

using class_id = std::pair<std::uint64_t, std::uint64_t>;

enum class class_key : std::uint8_t
{
    cls = 0, strct = 1, uni = 2
};

class class_info
{
public:
    class_info();
    class_info(class_id id_, class_key key_, const std::string& name_);
    inline const class_id& get_id() const { return id; }
    inline class_key get_key() const { return key; }
    inline const std::string& get_name() const { return name; }
    void add_base(const class_id& id);
    inline const std::vector<class_id>& base_class_ids() const { return bases; }
    void read(util::BinaryStreamReader& reader);
    void write(util::BinaryStreamWriter& writer);
private:
    class_id id;
    class_key key;
    std::string name;
    std::vector<class_id> bases;
};

class class_index
{
public:
    class_index();
    void imp(const class_index& that, bool import_map);
    void add_class(const class_info& info);
    void map_class(const class_info& info);
    const class_info* get_class_info(const class_id& id) const;
    inline const std::vector<class_info>& get_infos() const { return infos; }
    inline const std::map<class_id, class_info>& get_map() const { return map; }
    void read(util::BinaryStreamReader& reader);
    void write(util::BinaryStreamWriter& writer);
    void write(util::BinaryStreamWriter& writer, bool write_mapped);
private:
    std::vector<class_info> infos;
    std::map<class_id, class_info> map;
};

bool is_same_or_has_base(std::uint64_t derived_high, std::uint64_t derived_low, std::uint64_t base_high, std::uint64_t base_low);

} // namespace info
