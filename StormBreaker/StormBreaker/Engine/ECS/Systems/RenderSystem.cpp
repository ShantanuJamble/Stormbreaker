#include "RenderSystem.h"


std::vector<RenderComponent*> RenderSystem::m_renderData;
Renderer RenderSystem::m_renderer;

void RenderSystem::InitSystem()
{
	
}

void RenderSystem::ShutDownSystem()
{
	for (auto rc : m_renderData)
		if (rc)
			delete rc;

}

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
