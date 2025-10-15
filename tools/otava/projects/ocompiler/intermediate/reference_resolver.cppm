// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.reference_resolver;

import std;

export namespace otava::intermediate {

class Context;

std::expected<bool, int> ResolveReferences(Context& context);

} // otava::intermediate
