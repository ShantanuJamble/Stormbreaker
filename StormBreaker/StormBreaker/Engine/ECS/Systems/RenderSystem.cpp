#include "RenderSystem.h"
#include "Log.h"
#include "Renderer/Camera.h"
#include "Renderer/Mesh.h"


namespace engine
{
	void RenderSystem::OnCreate()
	{
		SB_ENGINE_INFO("Starting Rendering System");
	}

	void RenderSystem::OnUpdate(float dt, Scene* scene)
	{
		SB_ENGINE_INFO("Rendering the scene");
		const Camera camera = scene->GetSceneCamera();

		//auto renderables = scene.GetEntities<MeshComponent>();
	}

	void RenderSystem::OnShutdown() 
	{
		SB_ENGINE_INFO("Shutting down Rendering System");
	}

}