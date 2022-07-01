// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.util;

import std.core;

export namespace soul::cpp20::ast {

std::string UniversalCharacterName(char32_t c);
std::u32string ToUniversalId(const std::u32string& id);

} // namespace soul::cpp20::ast
