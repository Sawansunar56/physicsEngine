workspace "physicsEngine"
    architecture "x64"
    startproject "physicsEngine"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirs = {}
LibDirs = {}

IncludeDirs["GLFW"] = "physicsEngine/vendor/GLFW/include"
IncludeDirs["Glad"] = "physicsEngine/vendor/glad/include"

LibDirs["GLFW"] = "physicsEngine/vendor/GLFW/lib-vc2022"

include "physicsEngine/vendor/Glad"

project "physicsEngine"
    location "physicsEngine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "precompPch.h"
    pchsource "physicsEngine/src/precompPch.cpp"


    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDirs.GLFW}",
        "%{IncludeDirs.Glad}",
    }
    libdirs {
        "%{LibDirs.GLFW}",
    }
    links {
        "glad",
        "glfw3",
        "opengl32"
    }

	filter "system:windows"
        systemversion "latest"

        defines {
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "DEBUG_MODE"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "RELEASE_MODE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "DIST_MODE"
        runtime "Release"
        optimize "On"


