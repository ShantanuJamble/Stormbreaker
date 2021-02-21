#include "Scene.h"
#include "Entity.h"
#include "Components/Components.h"

namespace engine {
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity()
	{
		auto entity = Entity { m_SceneRegistry.create(), this };
		auto& labelComponent = entity.AddComponent<TagComponent>();
		labelComponent.m_label = "Test Entity";

		entity.AddComponent<TransformComponent>(glm::mat4(1.0f));
		return entity;
	}

	void Scene::RemoveEntity(Entity& entity)
	{
		m_SceneRegistry.destroy(entity.m_entityHandle);
	}
}
