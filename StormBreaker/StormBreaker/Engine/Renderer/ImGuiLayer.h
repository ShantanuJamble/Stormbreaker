#ifndef IMGUILAYER
#define IMGUILAYER

#include "framework.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_glfw.h"
#include "Layer.h"


class ImGuiLayer : public Engine::Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;

	void Begin();
	void End();
};

#endif // ! IMGUILAYER