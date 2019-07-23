#ifndef MEMORYINTERFACE_H
#define MEMORYINTERFACE_H
#include "../Core.h"
#include <cstddef>
namespace sbmemory
{
	extern bool  MemoryManagetInit();
	extern void* Allocate(const std::size_t size);
	extern void  Free(void * ref, const std::size_t size);
	extern bool  MeoryManagerShutDown();
}
#endif // !MEMORYINTERFACE_H
