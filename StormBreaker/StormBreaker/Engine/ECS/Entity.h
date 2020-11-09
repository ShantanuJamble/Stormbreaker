#ifndef ENTITY_H
#define ENTITY_H

#include "Components/TransformComponent.h"
#include "Components/RenderComponent.h"

/**
*Basic Entity definition
*/
namespace Engine {
	namespace ecs {
		class Entity
		{
		private:
			std::string m_label; 
			uint16_t m_id;
			Transform* m_transform = nullptr;
			RenderComponent* m_renderComponent = nullptr;

		public:

			Entity(const char* label, const uint16_t id)
				:m_label(label),
				 m_id(id)

			{
				m_transform = new Transform();
			}

			Entity(const char* label, const uint16_t id,glm::vec3 pos, glm::quat rot, glm::vec3 scale)
				:m_label(label),
				 m_id(id)
			{
				m_transform = new Transform(pos, rot, scale);
			}

			~Entity()
			{
				if (m_transform)
					delete m_transform;
				if (m_renderComponent)
					delete m_renderComponent;
			}

			inline Transform* GetTransform() const { return m_transform; }

			inline const uint16_t GetEntityID() const  { return m_id; }
			

			template<typename F>
			inline void AddComponent() {};


			template<typename T>
			inline T* GetComponent() {};
		};


		template<>
		inline void Entity::AddComponent<RenderComponent>()
		{
			if (m_renderComponent)
			{
				SB_ENGINE_ERROR("This entity already has this component!");
			}
			else
			{
				m_renderComponent = new RenderComponent();
			}
		}


		template<>
		inline RenderComponent* Entity::GetComponent<RenderComponent>() { return m_renderComponent; }

	}
}

#endif // !1
