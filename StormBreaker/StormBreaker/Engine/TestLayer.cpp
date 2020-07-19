#include "TestLayer.h"
#include "Log.h"
#include <glm/mat4x4.hpp>


bool TestLayer::open = true;

ImGui::FileBrowser TestLayer::fileDialog;
//void drawGui()
//{
//	// open Dialog Simple
//	if (ImGui::Button("Open File Dialog"))
//		igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", ".");
//
//	// display
//	if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
//	{
//		// action if OK
//		if (igfd::ImGuiFileDialog::Instance()->IsOk == true)
//		{
//			std::string filePathName = igfd::ImGuiFileDialog::Instance()->GetFilepathName();
//			std::string filePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();
//			// action
//		}
//		// close
//		igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
//	}
//}

TestLayer::TestLayer()
	:Layer("Test Scene"),
	m_lightBuffer(sizeof(Light)),
	m_projection(glm::mat4(1)),
	m_isLayerFocused(false),
	m_isLayerHoverd(false)
{
	std::string albedoTexturePath("Assets/Textures/rock.jpg");
	std::string normalTexturePath("Assets/Textures/rockNormals.jpg");
	m_albedoTexture = new Texture(albedoTexturePath);
	m_normalTexture= new Texture(normalTexturePath);
	m_shader = new Shader("Engine/Shader/VertexShader.glsl", "Engine/Shader/FragmentShader.glsl");
	m_material = new Material(m_albedoTexture,m_normalTexture, m_shader);
	//Setup mesh for the object
	std::string objpath("Assets/Models/sphere.obj");
	//Mesh mesh(positions, indices, new Texture(path));
	m_testMesh = new Mesh(objpath, m_material);

	//Camera
	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.01f);
	m_lightColor = {1, 1, 1};
	m_lightDir = { 1.0,0.0,0.0 };
	m_directLight.AmbientIntensity = .1f;
	//This direction is useless, we need to calculate direction agian based on the obj position. 
	m_directLight.Direction = m_lightDir;
	m_directLight.Position = glm::vec3(0.5, 2, 0);
	m_directLight.Color =m_lightColor;
	m_directLight.Type = 0;
	


	SB_ENGINE_INFO("SIZEOF LIGHT = {0}, {1}, {2}", sizeof(int), sizeof(float), sizeof(m_directLight));

	m_lightBuffer.BindBufferRange(0, sizeof(Light));
	SB_ENGINE_INFO("{0}", reinterpret_cast<uintptr_t>((void*)&m_directLight));
	m_lightBuffer.UpdateBufferSubData(0, sizeof(Light), (void*)&m_directLight);

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
	//Setup Uniform blocks
	m_shader->SetUniformBlock("Lights", 0);


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
	//Camera Update

	if(m_isLayerFocused)
		m_camera->OnUpdate(dt);

	//Updating light
	if (m_directLight.Color != m_lightColor)
	{
		m_directLight.Color = m_lightColor;
		m_lightBuffer.UpdateBufferSubData(0, sizeof(Light), (void*)&m_directLight);
	}

	if (m_directLight.Position != m_lightDir)
	{
		m_directLight.Position = m_lightDir;
		m_lightBuffer.UpdateBufferSubData(0, sizeof(Light), (void*)&m_directLight);
	}

	if (m_directLight.AmbientIntensity != m_ambientIntensity)
	{
		m_directLight.AmbientIntensity = m_ambientIntensity;
		m_lightBuffer.UpdateBufferSubData(0, sizeof(Light), (void*)&m_directLight);
	}

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

	//Frambuffer bind
	m_frameBuffer->Bind();

	m_renderer.Clear();
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	glm::mat4 model{ 1.0f };
	//model = glm::translate(model, glm::vec3(0.0f, triOffset,0.0f));
	model = glm::rotate(model, CONVERT_TO_RADIANS(curAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(4.0f,4.0f, 4.0f));

	m_shader->UseShader();
	m_shader->SetMat4("u_Model", model);
	m_shader->SetMat4("u_Projection", m_projection);
	m_testMesh->GetMaterial()->BindTextures();// GetTexture()->Bind();
	m_shader->SetMat4("u_View", m_camera->CalculateViewMatrix());
	m_shader->SetVec3("viewPos", m_camera->GetPostion());
	//m_shader->SetUniformBlock("Lights", 0);
	m_shader->SetInt("u_Texture", 0);
	m_shader->SetInt("u_NormalMap", 1);
	m_renderer.Draw(*m_testMesh->GetVertexArray(), *m_testMesh->GetIndexBuffer(), *m_shader);

	model = glm::mat4{ 1.0f };
	model = glm::translate(model, m_directLight.Position);
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	m_shader->SetMat4("u_Model", model);
	m_renderer.Draw(*m_testMesh->GetVertexArray(), *m_testMesh->GetIndexBuffer(), *m_shader);
	
	//frambuffer unbind
	m_frameBuffer->Unbind();
}

void TestLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::Text("Light Color:  ");
	ImGui::SameLine();
	ImGui::ColorEdit4("", glm::value_ptr(m_lightColor));
	ImGui::NewLine();

	ImGui::Text("Light Position:  ");
	ImGui::SameLine();
	ImGui::SliderFloat3("", glm::value_ptr(m_lightDir),-1.0f, 1.0f);
	ImGui::NewLine();

	ImGui::Text("Light Ambient Intensity:  ");
	ImGui::SameLine();
	ImGui::SliderFloat("", &m_ambientIntensity, 0.1, 2.0);
	ImGui::NewLine();

	ImGui::Text("Textures");
	ImGui::NewLine();
	ImGui::Image((void*)m_material->GetAlbedoTexture()->GetRenderId(), ImVec2{ 100.f,100.f });
	ImGui::NewLine();
	ImGui::Image((void*)m_material->GetNormalMapTexture()->GetRenderId(), ImVec2{ 100.f,100.f });

	
	fileDialog.SetTitle("title");
	fileDialog.SetTypeFilters({ ".h", ".cpp" });

	// open file dialog when user clicks this button
	if (ImGui::Button("open file dialog"))
		fileDialog.Open();

	fileDialog.Display();

	if (fileDialog.HasSelected())
	{
		std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
		fileDialog.ClearSelected();
	}


	ImGui::End();
	ImGui::Begin("ViewPort");
	//ImGui::Text("Test Stats:");
	m_isLayerFocused = ImGui::IsWindowFocused();
	m_isLayerHoverd = ImGui::IsWindowHovered();
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	if (m_viewportSize != *((glm::vec2*) & viewportPanelSize))
	{

		m_viewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		//Should be moved to camera. 
		//Engine::Application::GetInstance().GetWindow().OnViewPortResize(viewportPanelSize.x, viewportPanelSize.y);
		m_projection = glm::perspective(45.0f, (GLfloat)m_viewportSize.x / (GLfloat)m_viewportSize.y, 0.1f, 100.0f);
		m_frameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
	}
	uint32_t textureID = m_frameBuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
	ImGui::End();
}

void TestLayer::OnEvent(Engine::Event& e)
{
	if(m_isLayerFocused)
		m_camera->OnEvent(e);
}


