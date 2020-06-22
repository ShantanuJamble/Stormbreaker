#ifndef Entrypoint_h
#define Entrypoint_h
#include "Core.h"
#include "Application.h"
#include "Log.h"
#ifdef SB_DEBUG_BUILD
#include "vld.h"
#endif
extern Engine::Application* Engine::CreateApplication();

int main(int argc, char **argv)
{
	Engine::Log::Init();
	SB_ENGINE_INFO("Logs reporting for duty.");
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif //Entrypoint_h
