#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "BaseSystem.h"
#include "Renderer/Renderer.h"
namespace engine 
{
	class RenderSystem : public BaseSystem
	{
	private :
		Renderer m_renderer;

	public :
		virtual void OnCreate()  override;
		virtual void OnUpdate(float dt, Scene* scene)  override;
		virtual void OnShutdown() override ;
	};
}
#endif // !RENDER_SYSTEM_H
