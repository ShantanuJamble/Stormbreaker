#ifndef TEST_LAYER_H
#define TEST_LAYER_H
#include "Layer.h"
#include "Events/Event.h"
#include "glm/vec4.hpp"

#include "Log.h"
#include "Core.h"
#include "framework.h"
#include "Events/Event.h"

#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Renderer/WindowHandler.h"
#include "Renderer/ImGuiLayer.h"
#include "ImGUIIncludes.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"
#include "Renderer/SkyboxTexture.h"
#include "Renderer/SkyboxMaterial.h"
#include "Renderer/FrameBuffer.h"
#include "Renderer/Light.h"
#include "Renderer/UniformBuffer.h"
#include "Renderer/Camera.h"
#include "Application.h"
#include <glm/vec3.hpp>

//Comp -> Entity ->System

#include "Engine/ECS/Components/RenderComponent.h"
#include "Engine/ECS/Entity.h"
#include "Engine/ECS/Systems/RenderSystem.h"


#include "ImGuiFileUtil/ImGuiFileBrowser.h"

class TestLayer : public Engine::Layer
{
public:
	TestLayer();
	virtual ~TestLayer() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(float dt) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event & e) override;
private:
	glm::vec3 m_lightColor = { 1.0f, 1.0f, 1.0f };
	glm::vec3 m_lightDir = { 1.0,0.0,-1.0 };
	float m_ambientIntensity = 0.1;
	//Demo stuff
	Renderer m_renderer;
	std::vector<Mesh*> m_meshes;
	Engine::ecs::Entity *m_testEntity;
	Engine::ecs::RenderComponent *m_RenderComponent;
	Engine::ecs::RenderSystem *m_renderSystem;
	//glm::vec3 scaling;
	Texture* m_albedoTexture;
	Texture* m_normalTexture;
	SkyboxTexture* m_skyboxTexture;

	Shader* m_shader, *m_skyboxShader;
	FrameBuffer* m_frameBuffer;
	Mesh* m_testMesh, *m_skyboxMesh;
	Light m_directLight;
	UniformBuffer m_lightBuffer;

	Camera* m_camera;
	Material* m_material;
	SkyboxMaterial* m_skyboxMaterial;
	//Animation stuff
	float r = 0.0f;
	float incr = 0.05f;

	float trans_incr = 0.01f;
	float triOffset = 0.0f;
	float max_limit = 1.5f;
	int direction = 1;

	float curAngle = 0.0f;
	glm::mat4 m_model{ 1.0f };
	glm::mat4 m_projection;
	glm::vec2 m_viewportSize;


	//Flags for input and update events
	float m_isLayerFocused;
	float m_isLayerHoverd;

	//Testing file dialog
	bool m_selectingAlbedoTexture;
	bool m_selectingNormalTexture;
	static ImGui::FileBrowser fileDialog;
	std::string m_fileDialogTitle;

	//gameloop stats
	float m_fps;
	float m_dt;
};




#endif //TEST_LAYER_H