// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.visitor;

namespace otava::intermediate {

Visitor::Visitor(Context* context_) : context(context_), error(0)
{
}

void Visitor::SetError(int error_)
{ 
    error = error_; 
}

} // otava::intermediate
