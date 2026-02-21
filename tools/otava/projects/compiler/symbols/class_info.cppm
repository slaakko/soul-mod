// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.class_info_index;

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
    class_info(class_id id_, class_key key_, const std::string& name_, std::int64_t size_);
    inline const class_id& get_id() const { return id; }
    inline class_key get_key() const { return key; }
    inline const std::string& get_name() const { return name; }
    inline std::int64_t get_size() const { return size; }
    inline void set_size(std::int64_t size_) { size = size_; }
    void add_base(const class_id& id);
    inline const std::vector<class_id>& base_class_ids() const { return bases; }
    void read(util::BinaryStreamReader& reader);
    void write(util::BinaryStreamWriter& writer);
private:
    class_id id;
    class_key key;
    std::string name;
    std::int64_t size;
    std::vector<class_id> bases;
};

class class_index
{
public:
    class_index();
    void import(const class_index& that);
    void add_class(std::unique_ptr<class_info>& info);
    class_info* get_class_info(const class_id& id);
    void read(util::BinaryStreamReader& reader);
    void write(util::BinaryStreamWriter& writer);
private:
    std::vector<std::unique_ptr<class_info>> infos;
    std::map<class_id, class_info*> map;
};

} // namespace info
