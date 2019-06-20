#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"
namespace Engine {
	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
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
