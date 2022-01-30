#pragma once
// Required include for all Internal Hazel Engine src files
#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif // HZ_BUILD_DLL
#else 
	#error Hazel only supports windows for now!
#endif // HZ_PLATFORM_WINDOWS