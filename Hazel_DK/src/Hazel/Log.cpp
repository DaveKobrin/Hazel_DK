#include "hzpch.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	
	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$"); //sets log pattern to colored, timestamp, name, and message 

		s_CoreLogger = spdlog::stdout_color_mt("HAZEL"); //create logger for engine
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP"); //create looger for application
		s_ClientLogger->set_level(spdlog::level::trace);

	}
}
