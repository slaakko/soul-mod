// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module context_stack;

import std;

export extern "C" void* push_context();
export extern "C" void* pop_context();
