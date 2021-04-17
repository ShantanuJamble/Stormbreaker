#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "Renderer/Camera.h"

namespace engine
{
	namespace component
	{
		struct CameraComponent
		{
			Camera camera;

			CameraComponent() = default;
			CameraComponent(const CameraComponent& otherCamera) = default;
			CameraComponent(CameraComponent&& other) = default;
			CameraComponent& operator=(CameraComponent&& other) = default;

			CameraComponent(const Camera& otherCamera)
				:camera(otherCamera) {}

			
			//const Camera* GetCameraRef() const { return &camera; }
			
			Camera& GetCamera() { return camera; }

			operator Camera& () { return camera; }
			operator const Camera& () const { return camera; }
		};
	}
}
#endif // !CAMERA_COMPONENT_H
