#ifndef LOG_H
#define LOG_H

#include "Core.h"
#include "spdlog/spdlog.h"


namespace Engine {
	class  Log
	{

	public:
		SB_API static void Init();
		
		SB_API inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return m_EngineLogger; }
		SB_API inline static std::shared_ptr<spdlog::logger>& GetGameLogger()   { return m_GameLogger; }

	private:
		static std::shared_ptr<spdlog::logger> m_EngineLogger;
		static std::shared_ptr<spdlog::logger> m_GameLogger;
	};
}

#ifdef SB_DEBUG_BUILD

	//Engine Logger
	#define SB_ENGINE_INFO(...)  ::Falcon::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define SB_ENGINE_TRACE(...) ::Falcon::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define SB_ENGINE_WARN(...)  ::Falcon::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define SB_ENGINE_ERROR(...) ::Falcon::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define SB_ENGINE_FATAL(...) ::Falcon::Log::GetEngineLogger()->fatal(__VA_ARGS__)

	//Game Logger
	#define SB_GAME_INFO(...)    ::Falcon::Log::GetGameLogger()->info(__VA_ARGS__)
	#define SB_GAME_TRACE(...)   ::Falcon::Log::GetGameLogger()->trace(__VA_ARGS__)
	#define SB_GAME_WARN(...)    ::Falcon::Log::GetGameLogger()->warn(__VA_ARGS__)
	#define SB_GAME_ERROR(...)   ::Falcon::Log::GetGameLogger()->error(__VA_ARGS__)
	#define SB_GAME_FATAL(...)   ::Falcon::Log::GetGameLogger()->fatal(__VA_ARGS__)

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