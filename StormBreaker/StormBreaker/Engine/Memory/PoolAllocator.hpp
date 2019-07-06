#ifndef  POOL_ALLOCATOR_H
#define  POOL_ALLOCATOR_H

#include "../Core.h"
#include <cstdlib>

namespace sbmemory {
	class SB_API PoolAllocator
	{
	private:
		void *m_poolref;//Needs to be stored to free the memory 
		void **m_free_list_head;//List of free blocks
		std::size_t m_num_of_elements;
		std::size_t m_element_size_in_bytes;
		std::size_t m_alignment;

	public:
		PoolAllocator();
		PoolAllocator(const std::size_t size_in_bytes, const std::size_t num_of_elements, const std::size_t alignment);
		
		void Alloc(const std::size_t size_in_bytes, const std::size_t num_of_elements, const std::size_t alignment);

		void* GetBlocKFromPool();

		void Release(void* mem_ref);


		/*
			Making sure compiler doesn't create default definations for following functions.
		*/

		//Copy Constructor and copy assignment
		PoolAllocator(PoolAllocator& poolRef) = delete;
		PoolAllocator& operator = (const PoolAllocator& poolRef) = delete;

		//Double pointers related methods
		PoolAllocator(PoolAllocator&& refToPool) = delete;
		PoolAllocator& operator = (const PoolAllocator&& refToPool) = delete;


		~PoolAllocator();
	};


}
#endif // ! POOL_ALLOCATOR_H

