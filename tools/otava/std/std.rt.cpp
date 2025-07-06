// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module std.rt;

namespace std {

rt_init::rt_init()
{
    stdin = static_cast<void*>(&stdin_);
    stdout = static_cast<void*>(&stdout_);
    stderr = static_cast<void*>(&stderr_);
}

bool isspace(int c)
{
    return is_space(c);
}

const char* getenv(const char* env)
{
    return get_env(env);
}

FILE* fopen(const char* path, const char* mode)
{
    return open_file(path, mode);
}

int fclose(FILE* stream)
{
    return close_file(stream);
}

int fgetc(FILE* stream)
{
    return get_char(stream);
}

int fputc(int character, FILE* stream)
{
    return put_char(character, stream);
}

size_t fread(void* ptr, size_t size, size_t count, FILE* stream)
{
    return read_file(ptr, size, count, stream);
}

size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream)
{
    return write_file(ptr, size, count, stream);
}

int fputs(const char* str, FILE* stream)
{
    return puts_file(str, stream);
}

int feof(FILE* stream)
{
    return eof_file(stream);
}

int ferror(FILE* stream)
{
    return error_file(stream);
}

int fflush(FILE* stream)
{
    return flush_file(stream);
}

int fseek(FILE* stream, long int offset, int origin)
{
    return seek_file(stream, offset, origin);
}

long int ftell(FILE* stream)
{
    return tell_file(stream);
}

char* strerror(int errnum)
{
    return str_error(errnum);
}

void* memset(void* dest, int c, size_t count)
{
    return mem_set(dest, c, count);
}

char* getcwd(char* buffer, int maxlen)
{
    return get_cwd(buffer, maxlen);
}

bool fexists(const char* path)
{
    return file_exists(path);
}

bool dexists(const char* path)
{
    return dir_exists(path);
}

bool exists(const char* path)
{
    return path_exists(path);
}

int tolower(int c)
{
    return to_lower(c);
}

int toupper(int c)
{
    return to_upper(c);
}

bool isalpha(int c)
{
    return is_alpha(c);
}

bool isdigit(int c)
{
    return is_digit(c);
}

bool isatty(int handle)
{
    return is_atty(handle);
}

} // namespace std
