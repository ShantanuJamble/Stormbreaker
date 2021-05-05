#ifndef BASE_SYSTEM_H
#define BASE_SYSTEM_H
#include "ECS/Scene.h"

namespace engine
{
	class BaseSystem
	{
	public:
		virtual void OnCreate()  = 0;
		virtual void OnUpdate(float dt, Scene* scene)	 = 0;
		virtual void OnShutdown() = 0;

	};
}

#endif // !BASE_SYSTEM_H
