// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module lexer_resource;

import std.core;

export extern "C" int32_t* read_lexer_resource(const char* resource_name, int32_t& size);
export extern "C" void free_lexer_resource(int32_t* lexer_resource);

