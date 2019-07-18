#ifndef MEMORY_H
#define MEMORY_H

#include "Engine/Memory/Allocator.hpp"
#include "Engine/Memory/PoolAllocator.hpp"
#include "Engine/Memory/MemoryInterface.h"
#include "Engine/Memory/STLMemoryInterface.h"

#define sbnew(size)        sbmemory::Allocate(size)
#define sbdelete(ptr,size) sbmemory::Free(ptr,size)

#endif // !MEMORY_H
