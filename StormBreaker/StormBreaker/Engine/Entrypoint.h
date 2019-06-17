#ifndef Entrypoint_h
#define Entrypoint_h

#include "Core.h"
#include "Application.h"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char **argv)
{
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif //Entrypoint_h
