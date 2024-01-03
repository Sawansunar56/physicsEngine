#pragma once

#include <spdlog/spdlog.h>

class Log {
public:
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
};

#define LOG_TRACE(...) ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Log::GetCoreLogger()->critical(__VA_ARGS__)

#ifdef DEBUG_MODE
    #define LOG_ENABLE_ASSERTS
#endif

#ifdef LOG_ENABLE_ASSERTS
    #ifdef __clang__
        #define LOG_ASSERT(x, ...)
    #else
        #define LOG_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #endif
#else 
    #define LOG_ASSERT(x, ...)
#endif

