
#include <Engine.h>
#include <iostream>

class Game : public Engine::Application {
public:
	Game() {};
	~Game() {};
};

Engine::Application* Engine::CreateApplication()
{

		return new Game();
}
