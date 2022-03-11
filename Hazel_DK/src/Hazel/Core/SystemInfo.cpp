#include "hzpch.h"
#include "SystemInfo.h"

namespace Hazel
{
	SystemInfo::SystemPlatform SystemInfo::s_SystemPlatform = SystemInfo::SystemPlatform::Windows;
	SystemInfo::RenderingAPI SystemInfo::s_RenderingAPI = SystemInfo::RenderingAPI::OpenGL;
}