// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module ort.memory;

import std;

export namespace ort::memory {

void allocate(void* block, std::int64_t size);
void free(void* block);

} // namespace ort::memory
