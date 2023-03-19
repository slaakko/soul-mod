// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module context_stack;

import std.core;

export extern "C" void* push_context();
export extern "C" void* pop_context();
