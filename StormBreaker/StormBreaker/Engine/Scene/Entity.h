#ifndef ENTITY_H
#define ENTITY_H

#include "Core/Core.h"
#include "Components.h"
#include "Scene.h"
#include "Log.h"
#include <memory> //C++ memory lib

namespace engine
{
	class Entity
	{
	private:
		entt::entity m_entityHandle{ entt::null };
		REF<Scene> m_scene; //TODO Don't want to own the scene. Should be weak pointer. 

		friend class Scene;

	public:
		Entity() = default;
		
		Entity(entt::entity handle, REF<Scene> scene)
			:m_entityHandle (handle),
			 m_scene(scene) 
		{
		}

		~Entity() = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
			{
				//Should get entity label here. would be easier to debug.
				SB_ENGINE_ERROR("Entity already has component!, {0} ", m_entityHandle);
			};
			return m_Scene->m_SceneRegistry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
			m_Scene->m_SceneRegistry.remove<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_Scene->m_SceneRegistry.has<T>(m_EntityHandle);
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
