#ifndef CORE_H
#define CORE_H

#define BIT(x) (1 << x)
#define SB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
//#ifdef SB_DEBUG_BUILD
//
//	#define SB_ASSERT(x, ...) { if(!(x)) { SB_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
//	#define SB_CORE_ASSERT(x, ...) { if(!(x)) { SB_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
//#else
//	#define SB_ASSERT(x, ...)
//	#define SB_CORE_ASSERT(x, ...)
//#endif

#endif // !CORE_H1
