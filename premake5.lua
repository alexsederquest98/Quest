outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to the root (solution)
IncludeDir = {}
IncludeDir["glfw"] = "Quest/vendor/glfw/include"
IncludeDir["imgui"] = "Quest/vendor/imgui/"
IncludeDir["glm"] = "Quest/vendor/glm"
IncludeDir["spdlog"] = "Quest/vendor/spdlog/include"
IncludeDir["glad"] = "Quest/vendor/glad/include"

workspace "QuestEngine"
    architecture "x64"
    startproject "Sandbox"
    configurations {
        "Debug", "Release", "Distribution"
    }

-- Include premake5.lua in vendor libs
include "Quest/vendor/glfw"
include "Quest/vendor/glad"
include "Quest/vendor/imgui"

project "Quest"
    location "Quest"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "qepch.h"
    pchsource "Quest/src/qepch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",

        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl"
    }

    includedirs {
        "%{prj.name}/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glad}",
        "$(VULKAN_SDK)/Include",
    }

    links {
        "glfw",
        "glad",
        "ImGui",
        "opengl32.lib",
        "$(VULKAN_SDK)/Lib/vulkan-1.lib"
    }

    defines {
        "GLFW_INCLUDE_NONE"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "QE_PLATFORM_WINDOWS"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "QE_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "QE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Distribution"
        defines "QE_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Quest/src",
        "Quest/vendor/spdlog/include",
        "Quest/vendor/",
        "Quest/vendor/glfw/include",
        "Quest/vendor/glm"
    }

    links {
        "Quest"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "QE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SB_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SB_RELEASE"
        optimize "On"

    filter "configurations:Distribution"
        defines "SB_DIST"
        optimize "On"