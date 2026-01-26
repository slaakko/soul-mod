// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <csetjmp>

module ort.eh;

import class_info_index;
import ort.trace;

const int numContexts = 16384;

std::jmp_buf jbufs[numContexts];

void* exception = nullptr;
std::uint64_t ext1 = 0;
std::uint64_t ext2 = 0;
void* bad_alloc = nullptr;
std::uint64_t bad_alloc_ext1 = 0;
std::uint64_t bad_alloc_ext2 = 0;
int currentContext = 0;
int stackTrace = -1;

void ort_throw(void* ex, std::uint64_t ext1_, std::uint64_t ext2_)
{
    if (currentContext > 0)
    {
        exception = ex;
        ext1 = ext1_;
        ext2 = ext2_;
        if (ext1 != bad_alloc_ext1 || ext2 != bad_alloc_ext2)
        {
            //stackTrace = ort_generate_stack_trace();
        }
        std::longjmp(jbufs[currentContext - 1], 1);
    }
    else
    {
        std::cerr << "throw failed: no exception handler found" << "\n";
        std::exit(1);
    }
}

void ort_rethrow()
{
    ort_resume();
}

void ort_try(TryFn tryFn, HandlerFn handlerFn, void* parentFrame)
{
    if (currentContext >= 0 && currentContext < numContexts)
    {
        if (std::setjmp(jbufs[currentContext++]) == 0)
        {
            tryFn(parentFrame);
            --currentContext;
        }
        else
        {
            --currentContext;
            handlerFn(parentFrame);
        }
    }
    else if (currentContext >= numContexts)
    {
        std::cerr << "try failed: maximum number of contexts (" << numContexts << ") exceeded" << "\n";
        std::exit(1);
    }
    else
    {
        std::cerr << "try failed: invalid context value" << "\n";
        std::exit(1);
    }
}

void ort_invoke(InvokeFn invokeFn, CleanUpFn cleanupFn, void* parentFrame)
{
    if (currentContext >= 0 && currentContext < numContexts)
    {
        if (std::setjmp(jbufs[currentContext++]) == 0)
        {
            invokeFn(parentFrame);
            --currentContext;
        }
        else
        {
            --currentContext;
            cleanupFn(parentFrame);
            ort_resume();
        }
    }
    else if (currentContext >= numContexts)
    {
        std::cerr << "invoke failed: maximum number of contexts (" << numContexts << ") exceeded" << "\n";
        std::exit(1);
    }
    else
    {
        std::cerr << "invoke failed: invalid context value" << "\n";
        std::exit(1);
    }
}

bool ort_begin_catch(std::uint64_t ext1_, std::uint64_t ext2_)
{
    if (ext1 == ext1_ && ext2 == ext2_)
    {
        return true;
    }
    if (ort_is_same_or_has_base(ext1, ext2, ext1_, ext2_))
    {
        return true;
    }
    return false;
}

void ort_end_catch()
{
    exception = nullptr;
    ext1 = 0;
    ext2 = 0;
    ort_free_stack_trace(stackTrace);
}

void ort_resume()
{
    if (exception)
    {
        if (currentContext > 0)
        {
            std::longjmp(jbufs[currentContext - 1], 1);
        }
        else
        {
            std::cerr << "resume failed: no exception handler found" << "\n";
            std::exit(1);
        }
    }
    else
    {
        std::cerr << "resume failed: not handling exception" << "\n";
        std::exit(1);
    }
}

void* ort_get_exception()
{
    return exception;
}

void ort_print_exception_stack_trace()
{
    if (stackTrace != -1)
    {
        const char* traceStr = ort_get_stack_trace(stackTrace);
        if (traceStr)
        {
            std::cout << traceStr;
        }
    }
}

void ort_set_bad_alloc(void* ex, std::uint64_t ext1_, std::uint64_t ext2_)
{
    bad_alloc = ex;
    bad_alloc_ext1 = ext1_;
    bad_alloc_ext2 = ext2_;
}

bool ort_is_bad_alloc(std::uint64_t ext1_, std::uint64_t ext2_)
{
    return ext1_ == bad_alloc_ext1 && ext2_ == bad_alloc_ext2;
}

bool ort_current_ex_is_bad_alloc()
{
    return ext1 == bad_alloc_ext1 && ext2 == bad_alloc_ext2;
}

void* ort_get_bad_alloc()
{
    return bad_alloc;
}
