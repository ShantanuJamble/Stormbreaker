#ifndef  INPUT_H
#define  INPUT_H

#include <utility>

#include "framework.h"
#include "Application.h"

namespace engine
{

	class Input
	{
	public:
		static bool IsKeyPressed(int32_t keyCode);
		static bool IsKeyRelesed(int32_t keyCode);
		static bool IsMouseButtonPressed(int32_t button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}

#define INPUT engine::Input

#endif // ! INPUT_H
