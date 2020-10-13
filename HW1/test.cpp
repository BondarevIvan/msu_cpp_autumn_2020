#include "allocator.h"
#include <iostream>
#include <cassert>


int main()
{
    NAllocator::Allocator allocator;
    allocator.makeAllocator(10);
    char* hello = allocator.alloc(5);
    assert(hello);
    char* world = allocator.alloc(5);
    assert(world);
    char* cell = allocator.alloc(1);
    assert(!cell);
    return 0;
}