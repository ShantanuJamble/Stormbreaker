#ifndef MEMORY_H
#define MEMORY_H

#include "Memory/Allocator.hpp"
#include "Memory/PoolAllocator.hpp"
#include "Memory/MemoryInterface.h"
#include "Memory/STLMemoryInterface.h"

#define sbnew(size)        sbmemory::Allocate(size)
#define sbdelete(ptr,size) sbmemory::Free(ptr,size)

#endif // !MEMORY_H
