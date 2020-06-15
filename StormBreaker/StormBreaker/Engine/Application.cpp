#include <vector>
#include <glm/mat4x4.hpp>

#include "Events/ApplicationEvent.h"

#include "sbmemory.h"
#include "Renderer/Renderer.h"
#include "Renderer/WindowHandler.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include "Renderer/OpenGLErrorHandler.h"
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"
#include "Renderer/Light.h"
#include "Renderer/UniformBuffer.h"
#include "Log.h"
#include "Application.h"
namespace Engine {

	Application* Application::s_Instance = nullptr;

	Application::Application() :scaling(glm::vec3(2.0f, 2.0f, 2.0f))
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
		m_Window = new Window(1600, 900, SB_BIND_EVENT_FN(Application::OnEvent));
		m_Window->Initialise();
		//m_Window->SetEventCallback(SB_BIND_EVENT_FN(Application::OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
		m_ImGuiLayer->OnAttach();

	}


	Application::~Application()
	{
		delete m_Window;
		delete m_ImGuiLayer;
		SB_ENGINE_INFO("I am here!!");
		for (auto& mesh : m_meshes) delete mesh;
		m_meshes.clear();
		sbmemory::MeoryManagerShutDown();

	}

	void Application::Run()
	{
		
		float m_LastFrameTime = (float)glfwGetTime();
		// Main loop
		while (!m_Window->GetWindowShouldClose())
		{
			float time = (float)glfwGetTime();
			float dt = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Poll and handle events (inputs, window resize, etc.)
			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			m_Window->PollEvents();

			//if (m_Window->isKeyDown(GLFW_KEY_X))
			//{
			//	currentmesh = m_meshes[0];
			//	tmpTexture = currentmesh->GetMaterial()->GetTexture();
			//	materialShader = currentmesh->GetMaterial()->GetShader();
			//	materialShader->SetUniformBlock("Lights");
			//	
			//}
			//if(m_Window->isKeyDown(GLFW_KEY_C))
			//{
			//	currentmesh = m_meshes[1];
			//	tmpTexture = currentmesh->GetMaterial()->GetTexture();
			//	materialShader = currentmesh->GetMaterial()->GetShader();
			//	materialShader->SetUniformBlock("Lights");
			//}
	
			////Camera Input
			//camera.KeyControl(m_Window->GetKeys(),dt);
			//camera.MouseControl(m_Window->GetXchanged(), m_Window->GetYchanged());


			//OnUpdate for layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(dt);

			


		
			m_ImGuiLayer->Begin();
			{
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->SwapBuffers();
		}


		m_ImGuiLayer->OnDetach();

		return;
	}



	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


	void Application::OnEvent(Event& e)
	{
	
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SB_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SB_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return true;
	}
}
