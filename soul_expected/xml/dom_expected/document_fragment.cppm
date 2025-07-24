// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.document.fragment;

import std;
import soul_expected.xml.parent.node;

export namespace soul_expected::xml {

class DocumentFragment : public ParentNode
{
public:
    DocumentFragment(const soul_expected::ast::SourcePos& sourcePos_);
};

DocumentFragment* MakeDocumentFragment();

} // namespace soul_expected::xml
