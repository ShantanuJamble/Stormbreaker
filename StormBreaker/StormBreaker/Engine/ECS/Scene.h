#ifndef SCENE_H
#define SCENE_H

#include "entt/entt.hpp"
#include "Renderer/Camera.h"


namespace engine
{
	class Entity;
	class Event;


	class Scene
	{
	private:

		entt::registry m_SceneRegistry;
		Camera m_SceneCamera;
		friend class Entity;

	public:
		/**
		* TODO: Need to add support to serialize and deserialize scenes. 
		*       Camera Should not be hard coded. We should be able to change it. 
		**/
		Scene()
			:m_SceneCamera(glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.01f)
		{

		}
		
		~Scene()
		{
			if(m_SceneRegistry.size()>0)
				m_SceneRegistry.clear();
		}
		

		//Methods

		Entity CreateEntity();
		void   RemoveEntity(Entity& entity);

		inline const Camera& GetSceneCamera() const { return m_SceneCamera; }

		/****
		*** Event Handlers
		****/

		void OnUpdate(float dt);
		void OnEvent(Event& e); //This should act as an dispatcher to the relevent systems?  Need to figure out how to do this in multi-threaded env. 

		/*****
		*  Updating methods like OnRender(), OnCollision, should scene have it or the system? 
		***/


		template <typename t> 
		auto GetEntitiesWithCompotnent()
		{
			//look into the views in entt;
			return 1;
		}


		/****
		* Scene save-load methods
		****/

		static bool LoadScene(std::string& filePath) {}

		static bool SaveScene(Scene* scene, std::string& filePath) {}

	};
}


#endif