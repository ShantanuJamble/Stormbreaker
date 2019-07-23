#ifndef LOG_H
#define LOG_H

#include "Core.h"
#include "spdlog/spdlog.h"


namespace Engine {
	class  Log
	{

	public:
		
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return m_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetGameLogger()   { return m_GameLogger; }

	private:
		static std::shared_ptr<spdlog::logger> m_EngineLogger;
		static std::shared_ptr<spdlog::logger> m_GameLogger;
	};
}

#ifdef SB_DEBUG_BUILD

	//Engine Logger
	#define SB_ENGINE_INFO(...)  ::Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define SB_ENGINE_TRACE(...) ::Engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define SB_ENGINE_WARN(...)  ::Engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define SB_ENGINE_ERROR(...) ::Engine::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define SB_ENGINE_FATAL(...) ::Engine::Log::GetEngineLogger()->fatal(__VA_ARGS__)

	//Game Logger
	#define SB_GAME_INFO(...)    ::Engine::Log::GetGameLogger()->info(__VA_ARGS__)
	#define SB_GAME_TRACE(...)   ::Engine::Log::GetGameLogger()->trace(__VA_ARGS__)
	#define SB_GAME_WARN(...)    ::Engine::Log::GetGameLogger()->warn(__VA_ARGS__)
	#define SB_GAME_ERROR(...)   ::Engine::Log::GetGameLogger()->error(__VA_ARGS__)
	#define SB_GAME_FATAL(...)   ::Engine::Log::GetGameLogger()->fatal(__VA_ARGS__)

#else
	#define SB_ENGINE_INFO(...)  
	#define SB_ENGINE_TRACE(...) 
	#define SB_ENGINE_WARN(...)  
	#define SB_ENGINE_ERROR(...) 
	#define SB_ENGINE_FATAL(...) 

	#define SB_GAME_INFO(...)    
	#define SB_GAME_TRACE(...)   
	#define SB_GAME_WARN(...)    
	#define SB_GAME_ERROR(...)   
	#define SB_GAME_FATAL(...)   

#endif
#endif //LOG_H