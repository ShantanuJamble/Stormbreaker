#ifndef LOG_H
#define LOG_H

#include "Core/Core.h" 
#include "spdlog/spdlog.h"


namespace engine {
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
	#define SB_ENGINE_INFO(...)  ::engine::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define SB_ENGINE_TRACE(...) ::engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define SB_ENGINE_WARN(...)  ::engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define SB_ENGINE_ERROR(...) ::engine::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define SB_ENGINE_FATAL(...) ::engine::Log::GetEngineLogger()->fatal(__VA_ARGS__)

	//Game Logger
	#define SB_GAME_INFO(...)    ::engine::Log::GetGameLogger()->info(__VA_ARGS__)
	#define SB_GAME_TRACE(...)   ::engine::Log::GetGameLogger()->trace(__VA_ARGS__)
	#define SB_GAME_WARN(...)    ::engine::Log::GetGameLogger()->warn(__VA_ARGS__)
	#define SB_GAME_ERROR(...)   ::engine::Log::GetGameLogger()->error(__VA_ARGS__)
	#define SB_GAME_FATAL(...)   ::engine::Log::GetGameLogger()->fatal(__VA_ARGS__)

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