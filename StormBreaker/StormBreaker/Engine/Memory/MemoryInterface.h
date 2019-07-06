#ifndef MEMORYINTERFACE_H
#define MEMORYINTERFACE_H
#include "../Core.h"
#include <cstddef>
namespace sbmemory
{
	SB_API extern bool  MemoryManagetInit();
	SB_API extern void* Allocate(const std::size_t size);
	SB_API extern void  Free(void * ref, const std::size_t size);
	SB_API extern bool  MeoryManagerShutDown();
}
#endif // !MEMORYINTERFACE_H
