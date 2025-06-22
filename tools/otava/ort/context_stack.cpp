// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module context_stack;

import std;
import ort;

const int nctx = 1024;
const int ctxsz = 256;

struct context_buffer
{
    context_buffer(context_buffer* prev_);
    void* ctx();
    bool empty() const { return top == 0; }
    bool full() const { return top == nctx; }
    void push();
    void pop();
    void clear();
    std::uint8_t* mem;
    int top;
    context_buffer* prev;
    context_buffer* next;
};

context_buffer::context_buffer(context_buffer* prev_) : mem(static_cast<std::uint8_t*>(std::malloc(nctx* ctxsz))), top(0), prev(prev_), next(nullptr)
{
}

void* context_buffer::ctx()
{
    return mem + top * ctxsz;
}

void context_buffer::push()
{
    ++top;
}

void context_buffer::pop()
{
    --top;
}

void context_buffer::clear()
{
    top = 0;
}

struct context_stack
{
    context_stack();
    void push_context();
    bool pop_context();
    context_buffer* current;
};

context_stack::context_stack() : current(new context_buffer(nullptr))
{
}

void context_stack::push_context()
{
    current->push();
    if (current->full())
    {
        current = current->next;
        if (current)
        {
            current->clear();
        }
        else
        {
            current->next = new context_buffer(current);
            current = current->next;
        }
    }
}

bool context_stack::pop_context()
{
    if (current->empty())
    {
        if (current->prev)
        {
            current = current->prev;
            current->pop();
        }
        else
        {
            return false;
        }
    }
    else
    {
        current->pop();
    }
    return true;
}

context_stack* ctxstk = nullptr;

void* push_context()
{
    if (!ctxstk)
    {
        ctxstk = new context_stack();
    }
    void* ctx = ctxstk->current->ctx();
    ctxstk->push_context();
    return ctx;
}

void* pop_context()
{
    if (ctxstk && ctxstk->pop_context())
    {
        void* ctx = ctxstk->current->ctx();
        return ctx;
    }
    return nullptr;
}
