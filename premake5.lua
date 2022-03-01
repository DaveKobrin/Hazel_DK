workspace "Hazel_DK"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
-- Include directories relative to root(solution) folder
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel_DK/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel_DK/vendor/Glad/include"
IncludeDir["ImGui"] = "Hazel_DK/vendor/ImGui"
IncludeDir["glm"] = "Hazel_DK/vendor/glm"


include "Hazel_DK/vendor/GLFW"
include "Hazel_DK/vendor/Glad"
include "Hazel_DK/vendor/ImGui"

project "Hazel_DK"
    location "Hazel_DK"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hzpch.h"
    pchsource "Hazel_DK/src/hzpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    defines 
    { 
        "_CRT_SECURE_NO_WARNINGS"
    }
    
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines {"HZ_DEBUG", "HZ_ENABLE_ASSERTS"}
        symbols "On"
        runtime "Debug"


    filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On"
        runtime "Release"


    filter "configurations:Dist"
        defines "HZ_DIST"
        optimize "On"
        runtime "Release"



project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs
    {
        "Hazel_DK/vendor/spdlog/include",
        "Hazel_DK/src",
        "Hazel_DK/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Hazel_DK"
    }
    
    filter "system:windows"
        systemversion "latest"
    
        defines
        {
            "HZ_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        symbols "On"
        runtime "Debug"
    
    filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On"
        runtime "Release"
    
    filter "configurations:Dist"
        defines "HZ_DIST"
        optimize "On"
        runtime "Release"



        