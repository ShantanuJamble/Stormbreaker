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
#include "Renderer/FrameBuffer.h"
#include "Renderer/Light.h"
#include "Renderer/UniformBuffer.h"
#include "Renderer/Camera.h"
#include "Application.h"
#include <glm/vec3.hpp>
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
	glm::vec4 m_lightColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	//Demo stuff
	Renderer m_renderer;
	std::vector<Mesh*> m_meshes;
	glm::vec3 scaling;
	Texture* m_texture;
	Shader* m_shader;
	FrameBuffer* m_frameBuffer;
	Mesh* m_testMesh;
	Light m_directLight;
	Camera* m_camera;
	Material* m_material;

	//Animation stuff
	float r = 0.0f;
	float incr = 0.05f;

	float trans_incr = 0.005f;
	float triOffset = 0.0f;
	float max_limit = 0.7f;
	int direction = 1;

	float curAngle = 0.0f;
	glm::mat4 m_model{ 1.0f };
	glm::mat4 m_projection;
	glm::vec2 m_viewportSize;

};

#endif //TEST_LAYER_H