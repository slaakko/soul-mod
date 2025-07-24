// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.document.fragment;

namespace soul_expected::xml {

DocumentFragment::DocumentFragment(const soul_expected::ast::SourcePos& sourcePos_) : ParentNode(NodeKind::documentFragmentNode, sourcePos_, "document_fragment")
{
}

DocumentFragment* MakeDocumentFragment()
{
    return new DocumentFragment(soul_expected::ast::SourcePos());
}

} // namespace soul_expected::xml
