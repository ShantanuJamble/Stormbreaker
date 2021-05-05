#ifndef ENTITY_H
#define ENTITY_H

#include "Scene.h"
#include "Components/Components.h"
#include "Log.h"
#include <memory> //C++ memory lib

namespace engine
{
	class Entity
	{
	private:
		entt::entity m_entityHandle{ entt::null };
		//TODO Don't want to own the scene. Should be weak pointer. 
		//or may be can have scene id as a component? Doesn't feel clean that way though
		Scene* m_scene; 
		
		friend class Scene;

		//Add pointers or handles to the Children of the entity for the Scene Graph

	public:
		Entity() = default;
		
		Entity(entt::entity handle, Scene* scene)
			:m_entityHandle (handle),
			 m_scene(scene) 
		{
		}

		~Entity() {}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
			{
				//Should get entity label here. would be easier to debug.
				SB_ENGINE_ERROR("Entity doesn't have component!, {0} ", (std::uint32_t)m_entityHandle);
			};
			return m_scene->m_SceneRegistry.emplace<T>(m_entityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>())
			{
				SB_ENGINE_ERROR("Entity already has component!, {0} ", (std::uint32_t)m_entityHandle);
			}
			m_scene->m_SceneRegistry.remove<T>(m_entityHandle);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_scene->m_SceneRegistry.has<T>(m_entityHandle);
		}

		bool operator==(const Entity& other) const noexcept
		{
			return m_entityHandle == other.m_entityHandle && m_scene == other.m_scene;
		}

		bool operator!=(const Entity& other) const noexcept
		{
			return *this == other;
		}

	};

}


#endif
