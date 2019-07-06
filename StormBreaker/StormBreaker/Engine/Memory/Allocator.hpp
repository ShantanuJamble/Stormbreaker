#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <cstddef>
#include "Core.h"
#include "Log.h"

namespace sbmemory {
	SB_API void* AllocateUnaligned(std::size_t sz_in_byte);
	SB_API void  Deallocate(void * memref);

	SB_API void* AllocateAligned(std::size_t sz_in_byte, std::size_t alignment);
	SB_API void  DeallocateAligned(void * memref);
}

#endif
