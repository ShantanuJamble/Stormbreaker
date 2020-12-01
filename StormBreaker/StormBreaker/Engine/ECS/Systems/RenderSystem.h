#ifndef  RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "framework.h"



#include "Renderer/Renderer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "ECS/Components/RenderComponent.h"
#include "ECS/Entity.h"

/***
Design choice here - 
- Render system will always hold the data for all possible renderables
- Scene will pass in the list of objects to be draw. 
	Currently we just have opeque objects. Once PBR & transparency comes in, scene will need to send the appropriate data.
	May be we can send in a single structre containing all the arrays,and run Renderpasses for all of them.

***/


namespace Engine {
	namespace ecs {
		class RenderSystem
		{

		private:
			static std::vector<RenderComponent*> m_renderData;
			static Renderer m_renderer;
		public:
			static void InitSystem(std::vector<Entity*> &entities);
			static void ShutDownSystem();
			static void OnUpdate(float dt, std::vector<uint32_t>* renderBucket, uint16_t entityCount);

			static void Add(uint32_t enitity_id, RenderComponent* rc);
		};
	}
}
#endif // ! RENDER_SYSTEM_H