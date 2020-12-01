#include "RenderSystem.h"

namespace Engine {
	namespace ecs {
		std::vector<RenderComponent*> RenderSystem::m_renderData;
		Renderer RenderSystem::m_renderer;

		void RenderSystem::InitSystem(std::vector<Entity*> &entities)
		{
			m_renderData.resize(entities.size());
			for (auto itr = 0; itr != entities.size(); itr++)
			{
				m_renderData.emplace_back(entities[itr]->GetComponent<RenderComponent>());
				SB_ENGINE_INFO("RenderSystem: Successfully initiated Render System.");
			}

		}

		void RenderSystem::ShutDownSystem()
		{
			
		}


		/*
		    TODO: This doesn't seem a good approcach. Flesh out renderpasses in renderer itself and then this
            system should just init the render job and pass on relevent buckets. 
		*/
		void RenderSystem::OnUpdate(float dt, std::vector<uint32_t>* renderBucket, uint16_t entityCount)
		{
			VertexBuffer* vbo;
			IndexBuffer* ibo;
			Material* m;
			Shader* s;

			for (uint16_t looper = 0; looper < entityCount; ++looper)
			{
				uint32_t currentId = renderBucket->at(looper);

			}

		}

		void RenderSystem::Add(uint32_t enitity_id, RenderComponent* rc)
		{
		}

	}
}