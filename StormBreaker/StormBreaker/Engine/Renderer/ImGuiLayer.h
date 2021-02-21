#ifndef IMGUILAYER
#define IMGUILAYER

#include "framework.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_glfw.h"
#include "Layer.h"

namespace engine {
	class ImGuiLayer : public engine::Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
		void Begin();
		void End();
	};
}
#endif // ! IMGUILAYER