// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.document.fragment;

import std;
import soul.xml.parent.node;

export namespace soul::xml {

class DocumentFragment : public ParentNode
{
public:
    DocumentFragment(const soul::ast::SourcePos& sourcePos_);
};

DocumentFragment* MakeDocumentFragment();

} // namespace soul::xml
