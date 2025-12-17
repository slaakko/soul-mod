// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module ort.memory;

import ort;
import ort.trace;

namespace ort::memory {

struct memory_info
{
    memory_info(void* block_, std::int64_t size_, int serial_);
    void* block;
    std::int64_t size;
    int serial;
    bool freed;
};

memory_info::memory_info(void* block_, std::int64_t size_, int serial_) : block(block_), size(size_), serial(serial_), freed(false)
{
}

class memory_map
{
public:
    static memory_map& instance();
    memory_info* get(void* block) const;
    void allocate(void* block, std::int64_t size);
    void free(void* block);
private:
    std::map<void*, memory_info*> map;
    int serial;
    memory_map();
};

memory_map& memory_map::instance()
{
    static memory_map inst;
    return inst;
}

memory_map::memory_map() : map(), serial(0)
{
}

memory_info* memory_map::get(void* block) const
{
    auto it = map.find(block);
    if (it != map.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void memory_map::allocate(void* block, std::int64_t size)
{
    memory_info* info = get(block);
    if (info)
    {
        if (!info->freed)
        {
            std::cout << "memory block=" << block << ", size=" << info->size << ", serial=" << info->serial << " not freed" << "\n";
            ort_debug_break();
        }
        delete info;
    }
    info = new memory_info(block, size, serial++);
    map[block] = info;
}

void memory_map::free(void* block)
{
    memory_info* info = get(block);
    if (!info)
    {
        std::cout << "memory block=" << block << " not found" << "\n";
        ort_debug_break();
    }
    else
    {
        if (info->freed)
        {
            std::cout << "memory block=" << block << ", size=" << info->size << ", serial=" << info->serial << " already freed" << "\n";
            ort_debug_break();
        }
        else
        {
            info->freed = true;
        }
    }
}

void allocate(void* block, std::int64_t size)
{
    memory_map::instance().allocate(block, size);
}

void free(void* block)
{
    memory_map::instance().free(block);
}

} // namespace ort::memory
