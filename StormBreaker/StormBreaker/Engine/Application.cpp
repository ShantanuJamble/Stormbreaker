#include "Application.h"

#include <vector>
#include <glm/mat4x4.hpp>

#include "Events/ApplicationEvent.h"
#include "Log.h"
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
		m_Window = new Window(1600, 900);
		m_Window->Initialise();

		m_ImGuiLayer = new ImGuiLayer();
		m_ImGuiLayer->OnAttach();


		//Setup material for the object
		std::string texturepath1("../Assets/Textures/paint_albedo.png");
		Texture* texture1 = new Texture(texturepath1);
		
		Shader* tempShader1 = new Shader("Engine/Shader/VertexShader.glsl", "Engine/Shader/FragmentShader.glsl");
		
		Material* sphereMaterial = new Material(texture1, tempShader1);

		//Setup mesh for the object
		std::string objpath("../Assets/obj_files/sphere.obj");
		//Mesh mesh(positions, indices, new Texture(path));
		Mesh* mesh = new Mesh(objpath, sphereMaterial);

		std::string texturepath2("../Assets/Textures/meme.png");
		Texture* texture2 = new Texture(texturepath2);
		Shader* tempShader2 = new Shader("Engine/Shader/VertexShader.glsl", "Engine/Shader/FragmentShader.glsl");
		Material* cubeMaterial = new Material(texture2, tempShader2);

		std::string objpath2("../Assets/obj_files/cube.obj");
		//Mesh mesh(positions, indices, new Texture(path));
		Mesh* cubemesh = new Mesh(objpath2, cubeMaterial);

		m_meshes.push_back(mesh);
		m_meshes.push_back(cubemesh);
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
		/*std::vector<int, sbmemory::STLAllocator<int>> mynewvec = { 10,20,30 };

		for (int i : mynewvec)
			SB_GAME_INFO("{0}", i);*/
		

		///Setting up uniform buffer

		Light light;
		light.AmbientIntensity = 2.0f;
		light.Direction = glm::vec3(1, 0, 0);
		light.Position = glm::vec3(1, 1, 0);
		light.Color = glm::vec3(1, 1, 0);
		light.Type = 0;
		light.padding1 = 0;
	

		SB_ENGINE_INFO("SIZEOF LIGHT = {0}, {1}, {2}", sizeof(int), sizeof(float),sizeof(light));

		//unsigned int uboLights;
		//glGenBuffers(1, &uboLights);

		//glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
		//glBufferData(GL_UNIFORM_BUFFER, sizeof(Light), NULL,GL_STATIC_DRAW);
		//glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboLights, 0, sizeof(Light));
		//glBindBuffer(GL_UNIFORM_BUFFER, 0);


		////Setting up the bufferdata

		//glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
		//glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Light), (void*) &light);
		//glBindBuffer(GL_UNIFORM_BUFFER, 0);



		UniformBuffer lightBlock(sizeof(Light));
		lightBlock.BindBufferRange(0, sizeof(Light));
		SB_ENGINE_INFO("{0}", reinterpret_cast<uintptr_t>((void*)&light));
		lightBlock.UpdateBufferSubData(0, sizeof(Light), (void*)& light);
		 
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
		Camera camera = Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.01f);

		glm::mat4 model{ 1.0f };
		glm::vec3 scaling_vec(3.0f, 3.0f, 3.0f);

		
		Mesh* currentmesh = m_meshes[0];
		int index = 0;
		Texture* tmpTexture = currentmesh->GetMaterial()->GetTexture();
		Shader*  materialShader = currentmesh->GetMaterial()->GetShader();
		materialShader->SetUniformBlock("Lights",0);
		// Main loop
		while (!m_Window->GetWindowShouldClose())
		{
			// Poll and handle events (inputs, window resize, etc.)
			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			m_Window->PollEvents();

			if (m_Window->isKeyDown(GLFW_KEY_X))
			{
				currentmesh = m_meshes[0];
				tmpTexture = currentmesh->GetMaterial()->GetTexture();
				materialShader = currentmesh->GetMaterial()->GetShader();
				materialShader->SetUniformBlock("Lights");
				
			}
			if(m_Window->isKeyDown(GLFW_KEY_C))
			{
				currentmesh = m_meshes[1];
				tmpTexture = currentmesh->GetMaterial()->GetTexture();
				materialShader = currentmesh->GetMaterial()->GetShader();
				materialShader->SetUniformBlock("Lights");
			}
	
			//Camera Input
			camera.KeyControl(m_Window->GetKeys(), m_Window->GetTimeDelta());
			camera.MouseControl(m_Window->GetXchanged(), m_Window->GetYchanged());

			m_renderer.Clear();
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
			//model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
			model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, scaling_vec);
			


			materialShader->UseShader();
			materialShader->SetMat4("u_Model", model);
			materialShader->SetMat4("u_Projection", projection);
			currentmesh->GetMaterial()->GetTexture()->Bind();
			materialShader->SetMat4("u_View", camera.CalculateViewMatrix());
			
			materialShader->SetInt("u_Texture", 0);

			m_renderer.Draw(*currentmesh->GetVertexArray(), *currentmesh->GetIndexBuffer(), *materialShader);



			m_ImGuiLayer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->SwapBuffers();
		}


		m_ImGuiLayer->OnDetach();

		return;
	}
}
