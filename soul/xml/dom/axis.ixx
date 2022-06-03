// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.axis;

import std.core;

export namespace soul::xml {

enum class Axis
{
    child, descendant, parent, ancestor, followingSibling, precedingSibling, following, preceding, attribute, ns, self, descendantOrSelf, ancestorOrSelf
};

} // namespace soul::xml
