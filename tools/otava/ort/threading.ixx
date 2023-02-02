// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module ort.threading;

import std.core;

export extern "C" void* create_mutex();
export extern "C" void destroy_mutex(void* mtx);
export extern "C" void lock_mutex(void* mtx);
export extern "C" void unlock_mutex(void* mtx);
export extern "C" bool trylock_mutex(void* mtx);
export extern "C" void* create_recursive_mutex();
export extern "C" void destroy_recursive_mutex(void* mtx);
export extern "C" void lock_recursive_mutex(void* mtx);
export extern "C" void unlock_recursive_mutex(void* mtx);
export extern "C" bool trylock_recursive_mutex(void* mtx);
export extern "C" void* create_atomic_bool();
export extern "C" void destroy_atomic_bool(void* handle);
export extern "C" bool load_atomic_bool(void* handle);
export extern "C" void store_atomic_bool(void* handle, bool value);
