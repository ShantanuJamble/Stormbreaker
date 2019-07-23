#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Events/Event.h"

namespace Engine {
	class Application
	{
	public:
		Application();
		//Game classes are supposed to extend the application and define destructor
		virtual ~Application();
		void Run();
	};

	//To be defined by client
	Application* CreateApplication();


}
#endif // !APPLICATION_H