export module std.filesystem;

import std.type.fundamental;
import std.error;
import std.chrono.clock;
import std.basic_string;

export namespace std::filesystem {

class path
{
public:
    using value_type = char;
    using string_type = basic_string<value_type>;
    path();
    path(void* handle_);
    bool valid() const;
    path(const path& p);
    path(path&& that);
    path(const char* source);
    ~path();
    path& operator=(const path& p);
    path& operator=(path&& p);
    path& operator=(const char* source);
    path& assign(const char* source);
    path& operator/=(const path& p);
    path& operator+=(const path& p);
    path& operator+=(const char* x);
    path& operator+=(value_type x);
    void clear();
    path& make_preferred();
    path& remove_filename();
    path& replace_filename(const path& p);
    path& replace_extension(const path& ext);
    path& replace_extension();
    friend bool operator==(const path& lhs, const path& rhs);
    friend path operator/(const path& lhs, const path& rhs);
    std::string string() const;
    std::wstring wstring() const;
    std::u8string u8string() const;
    std::u16string u16string() const;
    std::u32string u32string() const;
    std::string generic_string() const;
    std::wstring generic_wstring() const;
    std::u8string generic_u8string() const;
    std::u16string generic_u16string() const;
    std::u32string generic_u32string() const;
    path root_name() const;
    path root_directory() const;
    path root_path() const;
    path relative_path() const;
    path parent_path() const;
    path filename() const;
    path stem() const;
    path extension() const;
    bool empty() const;
    bool has_root_name() const;
    bool has_root_directory() const;
    bool has_root_path() const;
    bool has_relative_path() const;
    bool has_parent_path() const;
    bool has_filename() const;
    bool has_stem() const;
    bool has_extension() const;
    bool is_absolute() const;
    bool is_relative() const;
private:
    void* handle;
};

class filesystem_error;
class directory_entry;
class directory_iterator;
directory_iterator begin(directory_iterator iter);
directory_iterator end(directory_iterator iter);
class recursive_directory_iterator;
recursive_directory_iterator begin(recursive_directory_iterator iter);
recursive_directory_iterator end(recursive_directory_iterator iter);
class file_status;
enum class file_type;
enum class perms;
enum class perm_options;
enum class copy_options;
enum class directory_options;
//using file_time_type = std::chrono::time_point<std::chrono::file_clock>;
using file_time_type = int64_t;
path absolute(const path& p);
path absolute(const path& p, std::error_code& ec);
path canonical(const path& p);
path canonical(const path& p, std::error_code& ec);
void copy(const path& from, const path& to);
void copy(const path& from, const path& to, std::error_code& ec);
void copy(const path& from, const path& to, copy_options options);
void copy(const path& from, const path& to, copy_options options, std::error_code& ec);
bool copy_file(const path& from, const path& to);
bool copy_file(const path& from, const path& to, std::error_code& ec);
bool copy_file(const path& from, const path& to, copy_options options);
bool copy_file(const path& from, const path& to, copy_options options, std::error_code& ec);
void copy_symlink(const path& existing_symlink, const path& new_symlink);
void copy_symlink(const path& existing_symlink, const path& new_symlink, std::error_code& ec);
bool create_directories(const path& p);
bool create_directories(const path& p, std::error_code& ec);
bool create_directory(const path& p, const path& attributes);
bool create_directory(const path& p, const path& attributes, std::error_code& ec);
void create_hard_link(const path& to, const path& new_hard_link);
void create_hard_link(const path& to, const path& new_hard_link, std::error_code& ec);
void create_symlink(const path& to, const path& new_symlink);
void create_symlink(const path& to, const path& new_symlink, std::error_code& ec);
path current_path();
path current_path(std::error_code& ec);
bool current_path(const path& p);
void current_path(const path& p, std::error_code& ec);
bool equivalent(const path& p1, const path& p2);
bool equivalent(const path& p1, const path& p2, std::error_code& ec);
bool exists(file_status s);
bool exists(const path& p);
bool exists(const path& p, std::error_code& ec);
uint64_t file_size(const path& p);
uint64_t file_size(const path& p, std::error_code& ec);
uint64_t hard_link(const path& p);
uint64_t hard_link(const path& p, std::error_code& ec);
bool is_block_file(file_status s);
bool is_block_file(const path& p);
bool is_block_file(const path& p, std::error_code& ec);
bool is_character_file(file_status s);
bool is_character_file(const path& p);
bool is_character_file(const path& p, std::error_code& ec);
bool is_directory(file_status s);
bool is_directory(const path& p);
bool is_directory(const path& p, std::error_code& ec);
bool is_empty(const path& p);
bool is_empty(const path& p, std::error_code& ec);
bool is_fifo(file_status);
bool is_fifo(const path& p);
bool is_fifo(const path& p, std::error_code& ec);
bool is_other(file_status s);
bool is_other(const path& p);
bool is_other(const path& p, std::error_code& ec);
bool is_regular_file(file_status s);
bool is_regular_file(const path& p);
bool is_regular_file(const path& p, std::error_code& ec);
bool is_socket(file_status s);
bool is_socket(const path& p);
bool is_socket(const path& p, std::error_code& ec);
bool is_symlink(file_status s);
bool is_symlink(const path& p);
bool is_symlink(const path& p, std::error_code& ec);
file_time_type last_write_time(const path& p);
file_time_type last_write_time(const path& p, std::error_code& ec);
void last_write_time(const path& p, file_time_type newTime);
void last_write_time(const path& p, file_time_type newTime, std::error_code& ec);
path relative(const path& p);
path relative(const path& p, std::error_code& ec);
path relative(const path& p, const path& base);
path relative(const path& p, const path& base, std::error_code& ec);
bool remove(const path& p);
bool remove(const path& p, std::error_code& ec);
uint64_t remove_all(const path& p);
uint64_t remove_all(const path& p, std::error_code& ec);
void rename(const path& from, const path& to);
void rename(const path& from, const path& to, std::error_code& ec);
void resize_file(const path& p, uint64_t size);
void resize_file(const path& p, uint64_t size, std::error_code& ec);
file_status status(const path& p);
file_status status(const path& p, std::error_code& ec);

} // namespace std::filesystem
