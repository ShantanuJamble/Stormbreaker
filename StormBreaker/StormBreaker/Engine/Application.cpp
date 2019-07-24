#include "Application.h"

#include <vector>


#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "sbmemory.h"


namespace Engine {
	Application::Application()
	{



		#ifdef SB_DEBUG_BUILD
				// Enable memory leak detection as a quick and dirty
				// way of determining if we forgot to clean something up
				//  - You may want to use something more advanced, like Visual Leak Detector
				_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		#endif
		SB_GAME_INFO("Inititaitng memory manager.");
		sbmemory::MemoryManagetInit();
	}


	Application::~Application()
	{
		sbmemory::MeoryManagerShutDown();
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		/*std::vector<int, sbmemory::STLAllocator<int>> mynewvec = { 10,20,30 };
		
		for (int i : mynewvec)
			SB_GAME_INFO("{0}", i);*/

		if (e.IsInCategory(EventCategoryApplication))
		{
			SB_GAME_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			SB_GAME_TRACE(e.ToString());
		}

		//while (true);
		return;
	}
}
