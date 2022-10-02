// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module std.c;

export {

using errno_t = int;
using FILE = void;
const int stdin = 0;
const int stdout = 1;
const int stderr = 2;
int EOF = -1;

errno_t errno;
char* strerror(int errorNum);
FILE* fopen(const char* fileName, const char* mode);
int fclose(FILE* stream);
int fgetc(FILE* stream);
int fputc (int character, FILE* stream);
size_t fread(void* ptr, size_t size, size_t count, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);
int feof(FILE* stream);
int ferror(FILE* stream);
int fflush(FILE* stream);
int fseek (FILE* stream, long int offset, int origin);
long int ftell (FILE* stream);
int SEEK_SET = 0;
int SEEK_CUR = 1;
int SEEK_END = 2;

} 
