module std.new_delete_op;

void* operator new(size_t size)
{
    return malloc(size);
}

void* operator new(size_t size, void* placement)
{
    return placement;
}

void operator delete(void* object)
{
    free(object);

}