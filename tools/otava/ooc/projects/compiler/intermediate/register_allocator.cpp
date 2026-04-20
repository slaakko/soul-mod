module otava.intermediate.register_allocator;

namespace otava::intermediate {

RegisterAllocator::RegisterAllocator()
{
}

RegisterAllocator::~RegisterAllocator()
{
}

SpillData::SpillData() noexcept : registerGroupToSpill(nullptr), instToSpill(nullptr)
{
}

} // otava::intermediate
