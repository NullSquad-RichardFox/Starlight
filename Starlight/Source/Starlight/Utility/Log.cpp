#include "Log.h"


void Logger::Initialize()
{
	ASSERT(sLoggerInstance == nullptr, "Logger already initialized!");
	sLoggerInstance = new Logger();

	// Creates log directory and files
	std::filesystem::path path = "Log/Core.log";
	std::filesystem::create_directories(path.parent_path());
	sLoggerInstance->LogFile.open(path);

	sLoggerInstance->MinFlushLevelConsole = (int32)ELogLevel::Display;
	sLoggerInstance->MinFlushLevelFile = (int32)ELogLevel::Display;

	sLoggerInstance->bConsoleOpened = true;
}

void Logger::Shutdown()
{
	if (sLoggerInstance == nullptr) return;

	sLoggerInstance->LogFile.close();

	delete sLoggerInstance;
	sLoggerInstance = nullptr;
}

void Logger::LogMessage_Int(ELogLevel level, const std::string& category, const std::string& message)
{
	ASSERT(sLoggerInstance != nullptr && (LogFile.is_open() || bConsoleOpened), "Logger has no valid output destination!");

	auto currTime = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
	std::string defaultPrefix = std::format("[{:%H:%M:%S}][{}]", currTime, category);


	if (LogFile.is_open())
	{
		std::string prefix = defaultPrefix + "[";

		switch (level)
		{
		case Logger::Display:
			prefix += "Display]: ";
			break;

		case Logger::Info:
			prefix += "Info]: ";
			break;

		case Logger::Warning:
			prefix += "Warning]: ";
			break;

		case Logger::Error:
			prefix += "Error]: ";
			break;

		case Logger::Critical:
			prefix += "Critical]: ";
			break;
		}

		if ((int32)level >= MinFlushLevelFile)
		{
			LogFile << prefix << message << "\n";
			LogFile.flush();
		}
	}

	if (bConsoleOpened)
	{
		int32 color = 0;

		switch (level)
		{
		case Logger::Display:
			std::cout << "\033[90m";
			break;

		case Logger::Info:
			std::cout << "\033[92m";
			break;

		case Logger::Warning:
			std::cout << "\033[93m";
			break;

		case Logger::Error:
			std::cout << "\033[91m";
			break;

		case Logger::Critical:
			std::cout << "\033[97m\033[41m";
			break;
		}

		if ((int32)level >= MinFlushLevelConsole)
		{
			std::cout << defaultPrefix << ": " << message << "\n";
			std::cout << "\033[0m";
		}
	}
}