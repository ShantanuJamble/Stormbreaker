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
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		#ifdef SB_DEBUG_BUILD
				// Enable memory leak detection as a quick and dirty
				// way of determining if we forgot to clean something up
				//  - You may want to use something more advanced, like Visual Leak Detector
				_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		#endif
		//SB_ASSERT(s_Instance == nullptr_t,"Application already exists");
		s_Instance = this;
		SB_GAME_INFO("Inititaitng memory manager.");
		sbmemory::MemoryManagetInit();
		m_Window = new Window(1200,780);
		m_Window->Initialise();

		m_ImGuiLayer = new ImGuiLayer();
		m_ImGuiLayer->OnAttach();
	}


	Application::~Application()
	{
		delete m_Window;
		delete m_ImGuiLayer;
		sbmemory::MeoryManagerShutDown();
		
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		
		/*std::vector<int, sbmemory::STLAllocator<int>> mynewvec = { 10,20,30 };
		
		for (int i : mynewvec)
			SB_GAME_INFO("{0}", i);*/

		
	
		//Testing imgui


		
		
		GLFWwindow* window = static_cast<GLFWwindow*>(m_Window->GetGLFWWindow());

		

		// Main loop
		while (!m_Window->GetShouldClose())
		{
			// Poll and handle events (inputs, window resize, etc.)
			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			m_Window->PollEvents();

			m_ImGuiLayer->Begin();
			
			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			
			m_ImGuiLayer->OnImGuiRender();
			
			m_ImGuiLayer->End();

			m_Window->SwapBuffers();
		}

	
		m_ImGuiLayer->OnDetach();
		
	//	delete vao;
	//	delete vbo;
	//	delete ibo;

		return;
	}
}
