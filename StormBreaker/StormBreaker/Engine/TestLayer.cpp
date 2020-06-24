#include "TestLayer.h"
#include "Log.h"
#include <glm/mat4x4.hpp>

TestLayer::TestLayer()
	:Layer("Test Scene")
{
	std::string texturepath1("Assets/Textures/steelplate1_albedo.png");
	m_texture = new Texture(texturepath1);
	m_shader = new Shader("Engine/Shader/VertexShader.glsl", "Engine/Shader/FragmentShader.glsl");
	m_material = new Material(m_texture, m_shader);
	//Setup mesh for the object
	std::string objpath("Assets/Models/sphere.obj");
	//Mesh mesh(positions, indices, new Texture(path));
	m_testMesh = new Mesh(objpath, m_material);

	//Camera
	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.01f);
	
	m_directLight.AmbientIntensity = 2.0f;
	m_directLight.Direction = glm::vec3(1, 0, 0);
	m_directLight.Position = glm::vec3(1, 1, 0);
	m_directLight.Color = glm::vec3(1, 1, 0);
	m_directLight.Type = 0;
	m_directLight.padding1 = 0;


	SB_ENGINE_INFO("SIZEOF LIGHT = {0}, {1}, {2}", sizeof(int), sizeof(float), sizeof(m_directLight));

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
	//glm::mat4 ortho = glm::ortho(-1.6f, 1.6f, -0.9f, 0.9f);

	FrameBufferData fb_data;
	fb_data.Width = 1200;
	fb_data.Height = 720;
	m_frameBuffer = new FrameBuffer (fb_data);
	m_viewportSize = { fb_data.Width, fb_data.Height };
	int a;
}



TestLayer::~TestLayer()
{
	
}

void TestLayer::OnAttach()
{

	UniformBuffer lightBlock(sizeof(Light));
	lightBlock.BindBufferRange(0, sizeof(Light));
	SB_ENGINE_INFO("{0}", reinterpret_cast<uintptr_t>((void*)&m_directLight));
	lightBlock.UpdateBufferSubData(0, sizeof(Light), (void*)&m_directLight);

	Texture* tmpTexture = m_testMesh->GetMaterial()->GetTexture();
	Shader* materialShader = m_testMesh->GetMaterial()->GetShader();
	materialShader->SetUniformBlock("Lights", 0);


	m_viewportSize = { Engine::Application::GetInstance().GetWindow().GetBufferWidth(),
						Engine::Application::GetInstance().GetWindow().GetBufferHeight() };
	m_projection = glm::perspective(45.0f, (GLfloat)m_viewportSize.x / (GLfloat)m_viewportSize.y, 0.1f, 100.0f);

}

void TestLayer::OnDetach()
{
	delete m_camera;
	delete m_testMesh;
	delete m_frameBuffer;
}

void TestLayer::OnUpdate(float dt)
{
	//Frambuffer bind
	m_frameBuffer->Bind();

	m_renderer.Clear();
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
	model = glm::rotate(model, CONVERT_TO_RADIANS(curAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

	m_shader->UseShader();
	m_shader->SetMat4("u_Model", model);
	m_shader->SetMat4("u_Projection", m_projection);
	m_testMesh->GetMaterial()->GetTexture()->Bind();
	m_shader->SetMat4("u_View", m_camera->CalculateViewMatrix());

	m_shader->SetInt("u_Texture", 0);

	m_renderer.Draw(*m_testMesh->GetVertexArray(), *m_testMesh->GetIndexBuffer(), *m_shader);

	m_frameBuffer->Unbind();
	//frambuffer unbind
}

void TestLayer::OnImGuiRender()
{

	ImGui::Begin("ViewPort");
	//ImGui::Text("Test Stats:");

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	if (m_viewportSize != *((glm::vec2*) & viewportPanelSize))
	{
		
		m_viewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		//Should be moved to camera. 
		//Engine::Application::GetInstance().GetWindow().OnViewPortResize(viewportPanelSize.x, viewportPanelSize.y);
		m_projection = glm::perspective(45.0f, (GLfloat)m_viewportSize.x / (GLfloat)m_viewportSize.y, 0.1f, 100.0f);
		m_frameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
		//m_CameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
	}
	uint32_t textureID = m_frameBuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y });
	ImGui::End();
}

void TestLayer::OnEvent(Engine::Event& e)
{
	SB_ENGINE_WARN("{0}", e.ToString());
	//Engine::Window window = Engine::Application::GetInstance().GetWindow();
	//m_camera->KeyControl(window.GetKeys(),window.GetTimeDelta());
	//m_camera->MouseControl(window.GetXchanged(), window.GetYchanged());
}
