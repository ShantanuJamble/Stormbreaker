#ifndef SCENE_H
#define SCENE_H

#include <entt.hpp>

namespace engine
{
	class Entity;
	class Event;


	class Scene
	{
	private:

		entt::registry m_SceneRegistry;
		friend class Entity;
	public:
		/**
		* TODO: Need to add support to serialize and deserialize scenes. 
		**/
		Scene();
		
		~Scene();


		//Methods

		Entity CreateEntity();
		void   RemoveEntity(Entity& entity);


		/****
		*** Event Handlers
		****/

		void OnUpdate(float dt);
		void OnEvent(Event& e);

		/*****
		*  Updating methods like OnRender(), OnCollision, should scene have it or the system? 
		***/


		template <typename t> 
		auto GetEntitiesWithCompotnent()
		{
			//look into the views in entt;
			return 1;
		}

	};
}


#endif