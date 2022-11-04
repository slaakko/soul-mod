// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module std.crt;

export {

extern "C" void* malloc(size_t size);
extern "C" void free(void* ptr);

}
