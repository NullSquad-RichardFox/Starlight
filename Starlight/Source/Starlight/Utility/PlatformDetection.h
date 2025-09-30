#pragma once


#ifdef _WIN32
	#define PT_WINDOWS
	#ifdef _WIN64
		#include "Windows.h"
		#define PT_WINDOWS_64
	#else
		#error "Windows x86 is currently not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#error "Any apple platform is currently not supported!"
#elif defined(__ANDROID__)
	#error "Android is not supported!"
#elif defined(__linux__)
	#error "Linux currently not supported!"
#else
	#error "Unknown platform!"
#endif