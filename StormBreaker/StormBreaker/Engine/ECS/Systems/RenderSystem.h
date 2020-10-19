#ifndef  RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "framework.h"



#include "Renderer/Renderer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "ECS/Components/RenderComponent.h"




class RenderSystem 
{

private:
	static std::vector<RenderComponent*> m_renderData;
	static Renderer m_renderer;
public:
	static void InitSystem();
	static void ShutDownSystem();
	static void OnUpdate(float dt, std::vector<uint32_t>* renderBucket , uint16_t entityCount);

	static void Add(uint32_t enitity_id,RenderComponent* rc);
};


#endif // ! RENDER_SYSTEM_H