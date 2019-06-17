#ifndef CORE_H
#define CORE_H

#ifdef SB_PLATFORM_WINDOWS
	#ifdef SB_BUILD_DLL
		#define SB_API __declspec(dllexport) 
	#else 
		#define SB_API __declspec(dllimport)
	#endif
#else
	#error Unsuppported platform
#endif 

#endif // !CORE_H
