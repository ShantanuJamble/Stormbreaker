#include "Application.h"

#include <vector>


#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "sbmemory.h"


namespace Engine {
	Application::Application()
	{
		sbmemory::MemoryManagetInit();
	}


	Application::~Application()
	{
		//sbmemory::MeoryManagerShutDown();
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
	/*	std::vector<int, sbmemory::STLAllocator<int>> mynewvec = { 10,20,30 };
		
		for (int i : mynewvec)
			SB_GAME_INFO("{0}", i);
*/
		if (e.IsInCategory(EventCategoryApplication))
		{
			SB_GAME_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			SB_GAME_TRACE(e.ToString());
		}

		while (true);
	}
}
