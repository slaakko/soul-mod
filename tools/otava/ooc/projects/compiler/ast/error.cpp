module otava.ast.error;

namespace otava::ast {

bool exceptionThrown = false;

void SetExceptionThrown() noexcept
{
    exceptionThrown = true;
}

bool ExceptionThrown() noexcept
{
    return exceptionThrown;
}

} // namespace otava::ast
