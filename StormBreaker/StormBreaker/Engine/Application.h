#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "framework.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Renderer/WindowHandler.h"
#include "Renderer/ImGuiLayer.h"
#include "ImGui/SBImGuiWindow.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"
#include <glm/vec3.hpp>
//#include "ImGui/imgui.h"

namespace Engine {
	class Application
	{

	private:
		static Application* s_Instance;
		Window* m_Window;
		ImGuiLayer * m_ImGuiLayer;
		LayerStack m_LayerStack;
		//Demo stuff
		Renderer m_renderer;
		std::vector<Mesh*> m_meshes;
		//Imgui values
		glm::vec3 scaling;
	public:
		static inline Application& GetInstance() { return *s_Instance; }
		Application();
		//Game classes are supposed to extend the application and define destructor
		virtual ~Application();
		void Run();
		inline const Window&  GetWindow() const { return *m_Window; }
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	
	
	};


	//To be defined by client
	Application* CreateApplication();
}
#endif // !APPLICATION_H