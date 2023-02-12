// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module std.crt;

namespace std {

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

} // namespace std
