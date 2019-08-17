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
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"

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
		m_Window = new Window(1200, 780);
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
		/*std::vector<int, sbmemory::STLAllocator<int>> mynewvec = { 10,20,30 };

		for (int i : mynewvec)
			SB_GAME_INFO("{0}", i);*/


		Renderer renderer;

		/*float positions[] =*/

		std::vector<float> positions{
			//x		y		z	u	 v
		   -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,  0.5f, 0.0f,
			1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
			0.0f,  1.0f, 0.0f,  0.5f, 1.0f
		};

		//unsigned int indices[] = 
		std::vector<unsigned int> indices{
			0, 3, 1,
			1, 3, 2,
			2, 3, 0,
			0, 1, 2
		};
		std::string texturepath("../Assets/Textures/meme.png");
		std::string objpath ("../Assets/obj_files/sphere.obj");
		//Mesh mesh(positions, indices, new Texture(path));
		Mesh mesh(objpath, texturepath);
		Shader tempShader("Engine/Shader/VertexShader.vert", "Engine/Shader/FragmentShader.frag");

		//Animation stuff
		float r = 0.0f;
		float incr = 0.05f;

		float trans_incr = 0.005f;
		float triOffset = 0.0f;
		float max_limit = 0.7f;
		int direction = 1;

		float curAngle = 0.0f;
		const float toRadians = 3.14159265f / 180.0f;


		int bufferWidth, bufferHeight;
		bufferHeight = m_Window->GetBufferHeight();
		bufferWidth = m_Window->GetBufferWidth();
		glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);
		//glm::mat4 ortho = glm::ortho(-1.6f, 1.6f, -0.9f, 0.9f);

		//Camera
		Camera camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.01f);
		glm::mat4 view;

		glm::mat4 model{ 1.0f };
		glm::vec3 scaling_vec(0.4f, 0.4f, 1.0f);



		Texture tmpTexture;
		// Main loop
		while (!m_Window->GetWindowShouldClose())
		{
			// Poll and handle events (inputs, window resize, etc.)
			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			m_Window->PollEvents();

			//Camera Input
			camera.KeyControl(m_Window->GetKeys(), m_Window->GetTimeDelta());
			camera.MouseControl(m_Window->GetXchanged(), m_Window->GetYchanged());

			renderer.Clear();
			m_ImGuiLayer->Begin();


			//Translation stuff
			if (direction)
			{
				triOffset += trans_incr;
			}
			else {
				triOffset -= trans_incr;
			}

			if (abs(triOffset) >= max_limit)
			{
				direction = !direction;
			}

			//Rotation stuff
			curAngle += 0.5f;
			if (curAngle >= 360)
			{
				curAngle -= 360;
			}


			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			glm::mat4 model{ 1.0f };
			model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
			model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, scaling);

			tempShader.UseShader();
			tempShader.SetMat4("u_Model", model);
			tempShader.SetMat4("u_Projection", projection);
			view = camera.CalculateViewMatrix();
			/*view = glm::translate(glm::mat4(1.0f), camera.GetPostion()) *
				glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0, 0, 1));
				*/
			tmpTexture = *(mesh.GetTexture());
			tmpTexture.Bind();
			tempShader.SetMat4("u_View", view);
			
			tempShader.SetInt("u_Texture", 0);
			renderer.Draw(*mesh.GetVertexArray(), *mesh.GetIndexBuffer(), tempShader);



			m_ImGuiLayer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->SwapBuffers();
		}


		m_ImGuiLayer->OnDetach();

		return;
	}
}
