#ifndef TEST_LAYER_H
#define TEST_LAYER_H
#include "Layer.h"
#include "Events/Event.h"
#include "glm/vec4.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_glfw.h"
class TestLayer : public Engine::Layer
{
public:
	TestLayer() = default;
	virtual ~TestLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(float dt) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event & e) override;
private:
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

#endif //TEST_LAYER_H