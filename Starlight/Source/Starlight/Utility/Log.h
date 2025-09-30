#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"


class Logger
{
public:
	enum ELogLevel
	{
		Display,
		Info,
		Warning,
		Error,
		Critical
	};

public:
	static void Initialize();
	static void Shutdown();

	static Logger* GetLogger() { return sLoggerInstance; }


	template<typename... Args>
	void Log(ELogLevel level, const std::string& category, const std::string& message, Args&&... args)
	{
		LogMessage_Int(level, category, std::vformat(message, std::make_format_args(args...)));
	}

private:
	void LogMessage_Int(ELogLevel level, const std::string& category, const std::string& message);

	inline static Logger* sLoggerInstance = nullptr;

	int MinFlushLevelConsole;
	int MinFlushLevelFile;

	std::ofstream LogFile;
	bool bConsoleOpened;
};

template<>
struct std::formatter<glm::vec2>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	auto format(const glm::vec2& vec, std::format_context& ctx) const
	{
		return std::format_to(ctx.out(), "({}, {})", vec.x, vec.y);
	}
};

template<>
struct std::formatter<glm::vec3>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	auto format(const glm::vec3& vec, std::format_context& ctx) const
	{
		return std::format_to(ctx.out(), "({}, {}, {})", vec.x, vec.y, vec.z);
	}
};

template<>
struct std::formatter<glm::vec4>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	auto format(const glm::vec4& vec, std::format_context& ctx) const
	{
		return std::format_to(ctx.out(), "({}, {}, {}, {})", vec.x, vec.y, vec.z, vec.w);
	}
};

#define LOG_DISPLAY(...) Logger::GetLogger()->Log(Logger::Display, "Core", __VA_ARGS__)
#define LOG_INFO(...) Logger::GetLogger()->Log(Logger::Info, "Core", __VA_ARGS__)
#define LOG_WARNING(...) Logger::GetLogger()->Log(Logger::Warning, "Core", __VA_ARGS__)
#define LOG_ERROR(...) Logger::GetLogger()->Log(Logger::Error, "Core", __VA_ARGS__)
#define LOG_CRITICAL(...) Logger::GetLogger()->Log(Logger::Critical, "Core", __VA_ARGS__)

#define LOG(...) LOG_DISPLAY(__VA_ARGS__)

#ifdef CF_DEBUG
#define INTERNAL_ASSERT_IMPL(check, msg, ...) { if (!(check)) { LOG_ERROR(msg, __VA_ARGS__); __debugbreak(); } }
#define ASSERT(check, msg) INTERNAL_ASSERT_IMPL(check, "Assertion failed: {0}", msg)
#define RAW_ASSERT(check, ...) assert(check)
#else
#define ASSERT(...) 
#define RAW_ASSERT(...) 
#endif