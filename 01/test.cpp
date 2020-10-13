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
    allocator.reset();
    char* hello_world = allocator.alloc(10);
    assert(hello_world);
    const char* HelloWorld = "helloWorld";
    for (int i = 0; i < 10; ++i)
    {
        hello_world[i] = HelloWorld[i];
    }
    std::cout << "SUCCESS!!!!!!!!!!!\n";
    return 0;
}