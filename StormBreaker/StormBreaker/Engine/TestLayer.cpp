#include "TestLayer.h"
#include "Log.h"
void TestLayer::OnAttach()
{
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate(float dt)
{
}

void TestLayer::OnImGuiRender()
{

	ImGui::Begin("Test");
	ImGui::Text("Test Stats:");
	ImGui::End();
}

void TestLayer::OnEvent(Engine::Event& e)
{
}
