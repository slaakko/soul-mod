// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module std.crt;

export {

extern "C" void* malloc(ssize_t size);
extern "C" void free(void* ptr);
extern "C" void prints(const char* s, int handle);
extern "C" int save_context(void* ctx);
extern "C" void restore_context(void* ctx, int retval);

}
