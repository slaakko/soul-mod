// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.error;

namespace soul::cpp20::ast {

bool exceptionThrown = false;

void SetExceptionThrown()
{
    exceptionThrown = true;
}

bool ExceptionThrown()
{
    return exceptionThrown;
}

} // namespace soul::cpp20::ast
