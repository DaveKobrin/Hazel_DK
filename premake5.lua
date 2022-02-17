workspace "Hazel_DK"
    architecture "x64"

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

include "Hazel_DK/vendor/GLFW"

project "Hazel_DK"
    location "Hazel_DK"
    kind "SharedLib"
    language "C++"

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
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines {"HZ_DEBUG", "HZ_ENABLE_ASSERTS"}
        symbols "On"
        buildoptions "/MDd"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On"
        buildoptions "/MD"

    filter "configurations:Dist"
        defines "HZ_DIST"
        optimize "On"
        buildoptions "/MD"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    
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
        "Hazel_DK/src"
    }

    links
    {
        "Hazel_DK"
    }
    
    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "HZ_PLATFORM_WINDOWS"
        }
        
    filter "configurations:Debug"
        defines "HZ_DEBUG"
        symbols "On"
        buildoptions "/MDd"
    
    filter "configurations:Release"
        defines "HZ_RELEASE"
        optimize "On"
        buildoptions "/MD"
    
    filter "configurations:Dist"
        defines "HZ_DIST"
        optimize "On"
        buildoptions "/MD"

        