
#include "TestLayer.h"
#include <Engine.h>
#include <iostream>

class Game : public Engine::Application {
public:
	Game()
	{
		PushLayer(new TestLayer());
	}
	~Game() = default;
};

Engine::Application* Engine::CreateApplication()
{
		return new Game();
}
