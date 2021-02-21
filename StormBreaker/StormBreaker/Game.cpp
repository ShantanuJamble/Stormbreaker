
#include "TestLayer.h"
#include <Engine.h>
#include <iostream>

class Game : public engine::Application {
public:
	Game()
	{
		PushLayer(new TestLayer());
	}
	~Game() = default;
};

engine::Application* engine::CreateApplication()
{
		return new Game();
}
