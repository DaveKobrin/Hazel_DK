#pragma once
#include "Hazel/Core/Time.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	class WindowsTime : public Time
	{
	public:
		WindowsTime() {}

		virtual float GetTime() const override { return (float)glfwGetTime(); }
	};
}