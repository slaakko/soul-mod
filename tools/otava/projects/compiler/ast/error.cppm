export module otava.ast.error;

import std;

export namespace otava::ast {

void SetExceptionThrown() noexcept;
bool ExceptionThrown() noexcept;

} // namespace otava::ast
