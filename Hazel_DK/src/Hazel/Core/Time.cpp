#include "hzpch.h"
#include "Time.h"

#include "SystemInfo.h"
#include "Hazel/Platform/Windows/WindowsTime.h"

namespace Hazel
{
	Time* Hazel::Time::Create()
	{
		switch (SystemInfo::GetSystemPlatform())
		{

		case SystemInfo::SystemPlatform::None:
			HZ_CORE_ASSERT(false, "System Platform None is not supported!");
			return nullptr;
		case SystemInfo::SystemPlatform::Windows:
			return new WindowsTime();

		default:
			HZ_CORE_ASSERT(false, "System Platform is not currently supported!");
			return nullptr;
		}
	}
}