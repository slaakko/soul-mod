// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.error;

namespace otava::ast {

bool exceptionThrown = false;

void SetExceptionThrown()
{
    exceptionThrown = true;
}

bool ExceptionThrown()
{
    return exceptionThrown;
}

} // namespace otava::ast
