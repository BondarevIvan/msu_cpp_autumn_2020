#include "allocator.h"
#include <cstring>

namespace NAllocator
{
    void Allocator::makeAllocator(size_t maxSize)
    {
        if (offset + maxSize <= currentSize)
            return;
        auto oldSize = currentSize; 
        currentSize = offset + maxSize;
        auto* pNewMemory = new char[currentSize];
        std::memcpy(pNewMemory, memory, oldSize * sizeof(*pNewMemory));
        delete[] memory;
        memory = pNewMemory;
    }

    void Allocator::reset()
    {
        offset = 0;
    }

    Allocator::~Allocator()
    {
        delete[] memory;
    }

    char* Allocator::alloc(size_t size)
    {
        if (size + offset <= currentSize)
        {
            auto* returnMemory = memory + offset;
            offset += size;
            return returnMemory;
        }
        return nullptr;
    }
}