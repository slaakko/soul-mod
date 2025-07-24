// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.axis;

import std;

export namespace soul_expected::xml {

enum class Axis
{
    child, descendant, parent, ancestor, followingSibling, precedingSibling, following, preceding, attribute, ns, self, descendantOrSelf, ancestorOrSelf
};

std::string AxisName(Axis axis);

} // namespace soul_expected::xml
