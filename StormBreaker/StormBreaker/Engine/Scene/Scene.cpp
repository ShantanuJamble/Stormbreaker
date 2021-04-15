#include "Scene.h"
#include "Entity.h"
#include "Components/Components.h"

namespace engine {
	/*Scene::Scene()
	{

	}

	Scene::~Scene()
	{
	}*/

	Entity Scene::CreateEntity()
	{
		entt::entity entt_entity = m_SceneRegistry.create();
		Entity entity(entt_entity, this);
		TagComponent labelComponent = entity.AddComponent<TagComponent>();
		labelComponent.m_tag = "Test Entity";

		//entity.AddComponent<TransformComponent>(glm::mat4(1.0f));
		return entity;
	}

	void Scene::RemoveEntity(Entity& entity)
	{
		m_SceneRegistry.destroy(entity.m_entityHandle);
	}
	void Scene::OnUpdate(float dt)
	{
	}
	void Scene::OnEvent(Event& e)
	{
	}
}
