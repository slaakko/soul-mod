module otava.optimizer.error;

namespace otava::optimizer {

bool exceptionThrown = false;

bool ExceptionThrown()
{
    return exceptionThrown;
}

void SetExceptionThrown()
{
    exceptionThrown = true;
}

} // otava::optimizer
