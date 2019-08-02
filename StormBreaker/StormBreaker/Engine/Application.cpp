#include "Application.h"

#include <vector>
#include <glm/mat4x4.hpp>

#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "sbmemory.h"
#include "Renderer/Renderer.h"
#include "Renderer/WindowHandler.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include "Renderer/OpenGLErrorHandler.h"

namespace Engine {
	Window *testWindow;
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
		testWindow = new Window(1200,780);
		testWindow->Initialise();
				
	}


	Application::~Application()
	{
		sbmemory::MeoryManagerShutDown();
		delete testWindow;
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

		Renderer renderer;

		float positions[3*3] = {
			-0.5f,-0.5f,0.0f,
			 0.5f,-0.5f,0.0f,
			 0.0f, 0.5f,0.0f,
		};

		unsigned int indices[] = {
			0, 1, 2
		};
		


		VertexBuffer* vbo = new VertexBuffer(positions, sizeof(positions));
		IndexBuffer* ibo = new  IndexBuffer(indices,3);

		VertexArray *vao = new VertexArray();
		
		vao->AddBuffer(vbo);

		Shader tempShader("Engine/Shader/VertexShader.vert", "Engine/Shader/FragmentShader.frag");
		while (!testWindow->GetShouldClose())
		{
			renderer.Clear();

			glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

			renderer.Draw(*vao,*ibo,tempShader);
			testWindow->SwapBuffers();
			testWindow->PollEvents();
		}
		delete vao;
		delete vbo;
		delete ibo;

		return;
	}
}
